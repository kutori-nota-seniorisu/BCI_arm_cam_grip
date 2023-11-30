#include "online_analysis/rnetstreamingreceiver.h"

#define SOCKET_ERROR -1

RNetStreamingReceiver::RNetStreamingReceiver()
{
	m_nSocketType				= SOCK_STREAM; //TCP

	m_bDoConnect				= false;
	m_usNetstreamPort			= 0;
	m_sNetstreamClientServerIP	= "";

	m_bClientInited				= false;
	m_SocketClient				= 0;
	m_nNetStreamingVersion		= -1;
	m_bBasicInfoValid			= false;
	m_nServerAmpStatus			= -1;
	m_pChannelInfoList			= NULL;
	m_nChannelInfoListSize		= 0;

	data_pub = n.advertise<std_msgs::Float32MultiArray>("/packet", 10);
	rate_pub = n.advertise<std_msgs::UInt16>("/samplerate", 10);
	chanNum_pub = n.advertise<std_msgs::UInt16>("/channum", 10);
	sampleNum_pub = n.advertise<std_msgs::UInt16>("/samplenum", 10);
	chan_pub = n.advertise<std_msgs::String>("/chanlabel", 10);
}

RNetStreamingReceiver::~RNetStreamingReceiver(void)
{
	CloseClient();
	if (m_pChannelInfoList)
	{
		free((void*)m_pChannelInfoList);
	}
	m_nChannelInfoListSize = 0;
}

bool RNetStreamingReceiver::IsConnected()						
{
	return m_bDoConnect;
}

void RNetStreamingReceiver::SetClient(bool bConnect, string sIP, long nPort)
{
	m_bDoConnect				= bConnect;
	m_sNetstreamClientServerIP	= sIP;
	m_usNetstreamPort			= (unsigned short)nPort;
}

HRESULT RNetStreamingReceiver::OpenClient(string* psError)
{
	long				nRetval;
	unsigned int		addr;
	struct sockaddr_in	server;
	size_t				nSize;
	string				sTmp;

	CloseClient();
	
	if (m_sNetstreamClientServerIP.empty())
	{
		*psError = "Client-Server IP is empty";
		return E_FAIL;
	}

	//copy the resolved information into the sockaddr_in structure
	memset(&server, 0, sizeof(server));
	inet_pton(AF_INET, m_sNetstreamClientServerIP.c_str(), &server.sin_addr);
	server.sin_family	= AF_INET;
	server.sin_port		= htons(m_usNetstreamPort);

	// 客户端套节字，用于打开客户端
	m_SocketClient		= socket(AF_INET, m_nSocketType, IPPROTO_TCP); //open socket
	if (m_SocketClient < 0)
	{
		return E_FAIL;
	}

	unsigned long unUnblocking = 1;

	//connect to server
	if (connect(m_SocketClient, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		std::cout << "Client: connect() is Wrong" << std::endl;
	}
	else
	{
		std::cout << "Client: connect() is OK" << std::endl;
 	}

	unUnblocking = 0;

	m_bClientInited = true;

	return S_OK;
}


HRESULT RNetStreamingReceiver::ListenClient(long nNumReceiveMessages,  std::atomic<bool>* pbActive)
{
	HRESULT	hr			= E_FAIL;
	char*	pcBuffer	= NULL;
	long	nSizeBuffer	= NETSTREAM_BUFFER_SIZE * SIZE_C;

	AcqMessage message;

	if (!(pcBuffer = (char*)calloc(NETSTREAM_BUFFER_SIZE, SIZE_C)))
	{
		return E_OUTOFMEMORY;
	}
	
	std::cout << "Connected to server." << std::endl;
   
	//nNumReceiveMessages == -1 for infinite loop (from thread)
	while ((nNumReceiveMessages == -1 || nNumReceiveMessages > 0) && ros::ok())
	{
		std::cout << "------------------------------------" << std::endl;
		if (!m_bClientInited)
		{
			hr = E_FAIL;
			break;
		}

		if (FAILED(hr = ReceiveNetStreamingMessage(m_SocketClient, &message)))
		{
			std::cout << "ERROR: Receive data failed!" << std::endl;
			break;
		}
		
		if (FAILED(HandleMessage(&message, m_SocketClient)))
		{
			std::cout << "ERROR: Handling Message!" << std::endl;
		}

		if (pbActive && !(*pbActive))
		{
			std::cout << "ListenClient stop received." << std::endl;
			break;
		}

		if (nNumReceiveMessages > 0)
		{
			--nNumReceiveMessages;
		}
	}

	return hr;
}

HRESULT RNetStreamingReceiver::CloseClient()
{
	if (m_bClientInited)
	{
		std::cout << "Closing Client." << std::endl;

		m_bClientInited			= false;
		close(m_SocketClient);

		m_bBasicInfoValid		= false;
		m_nChannelInfoListSize	= 0;
		if (m_pChannelInfoList)
		{
			free((void*)m_pChannelInfoList);
			m_pChannelInfoList = NULL;
		}
	}
	
	return S_OK;
}

//send header and data in two portions
HRESULT RNetStreamingReceiver::SendNetStreamingMessage(SOCKET socket, AcqMessage* pMessage)
{
	string s;

	if (!socket || !pMessage)
	{
		
		return E_INVALIDARG;
	}

	if (!pMessage->m_pBody)
	{
		pMessage->m_dwSize = 0;
	}
	DWORD dwSize = pMessage->m_dwSize;													//copy size because function Convert() will change m_dwSize variable
	pMessage->Convert(true);															//convert header to network order

	if (send(socket, pMessage->m_chId, pMessage->GetHeaderSize(), 0) == SOCKET_ERROR)	//send message header
	{
		std::cout << "header send() failed: error" << std::endl;
		return E_FAIL;
	}

	if (dwSize)
	{
		if (send(socket, pMessage->m_pBody, dwSize, 0) == SOCKET_ERROR)					//send data
		{
			std::cout << "data send() failed: error" << std::endl;
			return E_FAIL;
		}
		printf("Sent %d kBytes\n", dwSize / 1024);
	}

	return S_OK;
}

HRESULT RNetStreamingReceiver::ReceiveNetStreamingMessage(SOCKET socket, AcqMessage* pMessage)
{
	int		error			= 0;
	int		nRetval			= 0;
	DWORD	nBytesReceived	= 0;
	string s;

	if (!socket || !pMessage)
	{
		return E_INVALIDARG;
	}

	if ((nRetval = recv(socket, (char*)&pMessage->m_chId, pMessage->GetHeaderSize(), 0)) == SOCKET_ERROR)	//read header
	{
		std::cout << "header receive() failed: error" << std::endl;
		return E_FAIL;
	}

	if (nRetval == 0)
	{
		std::cout << "Server/Client closed connection" << std::endl;
		return E_FAIL;
	}

	pMessage->Convert(false);		//convert Network byte order to host byte order (Big-Endian -> Little-Endian)

	if (!pMessage->IsValid())
	{
		std::cout << "ERROR: Received invalid message." << std::endl;
		return E_FAIL; //received invalid message
	}

	if (pMessage->m_dwSize > 0)		//read body (if any)
	{
		if (pMessage->m_pBody)
		{
			free(pMessage->m_pBody);
			pMessage->m_pBody = NULL;
		}

		if (!(pMessage->m_pBody = (char*)calloc(pMessage->m_dwSize, SIZE_C)))
		{
			return E_OUTOFMEMORY;
		}
		
		nBytesReceived = 0;
		while (nBytesReceived < pMessage->m_dwSize)
		{
			if ((nRetval = recv(socket, (char*)pMessage->m_pBody + nBytesReceived, pMessage->m_dwSize - nBytesReceived, 0)) == SOCKET_ERROR)
			{
				std::cout << "body receive() failed: error" << std::endl;
				return E_FAIL;
			}

			nBytesReceived += nRetval;

			if (nRetval == 0)
			{
				std::cout << "Server/Client closed connection" << std::endl;
				return E_FAIL;
			}
		}

		if (nBytesReceived < 1024)
		{
			printf("Received %d Bytes\n", nBytesReceived);
		}
		else
		{
			printf("Received %d kBytes\n", nBytesReceived / 1024);
		}

		if (nBytesReceived != pMessage->m_dwSize)
		{
			std::cout << "ERROR: Didn't receive as much as expected. (maybe connection got closed)" << std::endl;
			return E_FAIL;
		}
	}

	return S_OK;
}

HRESULT RNetStreamingReceiver::HandleMessage(AcqMessage* pMessage, SOCKET nSocketReply)
{
	HRESULT		hr				= S_OK;
	bool		bMessageHandled	= false;
	string		s;

	if (!pMessage)
	{
		return E_INVALIDARG;
	}

//handle CTRL packet
	if (pMessage->IsCtrlPacket())	
	{
		printf("Control Packet: code=%d, request=%d\n", pMessage->m_wCode, pMessage->m_wRequest);
		switch (pMessage->m_wCode)
		{
			case CTRL_FromServer:
				switch (pMessage->m_wRequest)
				{
					case Server_AcquisitionStart:
						std::cout << "From Server: Start Acquisition\n" << std::endl;;
						m_bBasicInfoValid	= false;
						bMessageHandled		= true;
						break;
					case Server_AcquisitionStop:
						std::cout << "From Server: Stop Acquisition\nPress \"Disconnect\", then \"Connect\" to continue receiving data." << std::endl;
						m_bBasicInfoValid	= false;
						bMessageHandled		= true;
						break;
					case Server_ImpedanceStart:
						std::cout << "From Server: Start Impedance\n" << std::endl;
						bMessageHandled		= true;	
						break;
					case Server_ImpedanceStop:
						std::cout << "From Server: Stop Impedance\n" << std::endl;
						bMessageHandled		= true;
						break;
					case Server_RecordingStart:
						std::cout << "From Server: Start Recording\n" << std::endl;
						bMessageHandled		= true;
						break;
					case Server_RecordingStop:
						std::cout << "From Server: Stop Recording\n" << std::endl;

						bMessageHandled		= true;
						break;
					default:
						
						break;
				}
				break;

			case CTRL_FromClient:
				//not available in this demo
				break;

			default:
				break;
		}
	}
//handle DATA packet
	else if (pMessage->IsDataPacket())
	{
		printf("Control Packet: code=%d, request=%d\n", pMessage->m_wCode, pMessage->m_wRequest);
		switch (pMessage->m_wCode)
		{
			case DATA_Info:
				switch (pMessage->m_wRequest)
				{
					case InfoType_Version:
						{
							if (pMessage->m_pBody && pMessage->m_dwSize == sizeof(m_nNetStreamingVersion))
							{
								memcpy((void*)&m_nNetStreamingVersion, pMessage->m_pBody, sizeof(m_nNetStreamingVersion));
								bMessageHandled		= true;
							}					
							else
							{
								m_nNetStreamingVersion = -1;
								
							}
						}
						break;

					case InfoType_BasicInfoAcq:
						{
							BasicInfoAcq* pInfo = (BasicInfoAcq*)pMessage->m_pBody;
							if (pInfo->dwSize == sizeof(BasicInfoAcq))
							{
								memcpy((void*)&m_BasicInfo, pMessage->m_pBody, sizeof(m_BasicInfo));
								m_bBasicInfoValid	=	(m_BasicInfo.nEegChan > 0 && m_BasicInfo.nEegChan < MAX_CHANNELS && m_BasicInfo.nRate > 0) ||
														(m_BasicInfo.nEegChan == -1 && m_BasicInfo.nRate == -1);	//if values are -1, the amplifier is not connected yet
								bMessageHandled		= true;
							}					
						}
						break;

					case InfoType_ChannelInfo:
						{
							if (pMessage->m_dwSize > 0 && pMessage->m_dwSize % sizeof(NetStreamingChannelInfo) == 0)
							{
								if (m_pChannelInfoList)
								{
									free((void*)m_pChannelInfoList);
									m_pChannelInfoList = NULL;
								}
								
								m_nChannelInfoListSize = 0;
								if ((m_pChannelInfoList = (NetStreamingChannelInfo*)malloc(pMessage->m_dwSize)))
								{
									memcpy((void*)m_pChannelInfoList, pMessage->m_pBody, pMessage->m_dwSize);
									m_nChannelInfoListSize	= pMessage->m_dwSize;
									bMessageHandled			= true;
								}
								else
								{
									hr = E_OUTOFMEMORY;
								}
							}					
							else
							{
								
							}
						}
						break;

					case InfoType_StatusAmp:
						{
							if (pMessage->m_pBody && pMessage->m_dwSize == sizeof(m_nServerAmpStatus))
							{
								memcpy((void*)&m_nServerAmpStatus, pMessage->m_pBody, sizeof(m_nServerAmpStatus));
								bMessageHandled			= true;
							}					
						}
							break;

					case InfoType_Time:
						{
							if (pMessage->m_pBody && pMessage->m_dwSize == sizeof(m_dTimePackageReceived))
							{
								memcpy((void*)&m_dTimePackageReceived, pMessage->m_pBody, sizeof(m_dTimePackageReceived));
								bMessageHandled		= true;
							}					
							else
							{
								m_dTimePackageReceived = 0;
							}
						}
						break;

					default:
						//unexpected request
						break;
				}
				break;

			case DATA_Eeg:
				switch (pMessage->m_wRequest)
				{
					case DataTypeFloat32bit:
						if (pMessage->m_dwSize > 0 && pMessage->m_pBody && pMessage->m_dwSize % SIZE_F == 0)
						{
							//pass it to amp
							DataReady((float*)pMessage->m_pBody, pMessage->m_dwSize, pMessage->m_unSample);
							bMessageHandled = true;
						}
						break;

					case DataTypeFloat32bitZIP:
						if (pMessage->m_dwSize > 0 && pMessage->m_dwSizeUncompressed > 0 && pMessage->m_pBody)
						{
							std::cout << "ERROR: compressed data cannot be handled in this demo. Set the server to send uncompressed data" << std::endl;
							bMessageHandled = true;
						}
						break;

					default:
						std::cout << "ERROR: data format cannot be handled in this demo" << std::endl;
						break;
				}
				break;

			case DATA_Events:
				switch (pMessage->m_wRequest)
				{
					case DataTypeEventList:
						if (pMessage->m_dwSize > 0 && pMessage->m_pBody && pMessage->m_dwSize % sizeof(NetStreamingEvent) == 0)
						{
							//pass it to amp
							EventDataReady((NetStreamingEvent*)pMessage->m_pBody, pMessage->m_dwSize);
							bMessageHandled = true;
						}
						break;
					default:
						break;
				}
				break;

			case DATA_Impedances:
				switch (pMessage->m_wRequest)
				{
					case DataTypeFloat32bit:
						if (pMessage->m_dwSize > 0 && pMessage->m_pBody && pMessage->m_dwSize % SIZE_F == 0)
						{
							//pass it to amp
							ImpedanceDataReady((float*)pMessage->m_pBody, pMessage->m_dwSize);
							bMessageHandled = true;
						}
						break;
					default:
						break;
				}
				break;

			default:
				break;
		}
	}

	if (!bMessageHandled)
	{
		std::cout << "ERROR: Received unknown message." << std::endl;
	}

	hr = (SUCCEEDED(hr) && !bMessageHandled) ? E_FAIL : hr;

	return hr;
}

//client methods

//requests and receives newtview version from server
//returns S_OK when netstreaming server version matches the client version
HRESULT RNetStreamingReceiver::ClientCheckNetStreamingVersion()
{
	string s;

	if (!m_bClientInited)
	{
		return E_FAIL;
	}

	m_nNetStreamingVersion = -1;

	//send basic info request to server
	AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_Version);
	if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
	{
		return E_FAIL;
	}

	//receive some packets, hoping the server will reply
	long nCounter = 0;
	while (m_nNetStreamingVersion == -1 && nCounter < 10)
	{
		usleep(50000);
		if (FAILED(ListenClient(1, NULL)))
		{
			std::cout << "Failed to recieve NetStreaming Version." << std::endl;
			return E_FAIL;
		}
		nCounter++;
	}

	if (m_nNetStreamingVersion != -1 && m_nNetStreamingVersion != NETSTREAM_VERSION)
	{
		printf("ERROR: The NetStreaming server is running NetStreaming version %d while NetStreaming version %d was expected. (make sure Server and Client run compatible versions of NetStreaming)", m_nNetStreamingVersion, NETSTREAM_VERSION);
	}
	else if (m_nNetStreamingVersion == -1)
	{
		printf("ERROR: The NetStreaming server did not answer in time. (make sure client and server are correctly configured)");
	}
	else
	{
		printf("Server NetStreaming Version: %d\n", m_nNetStreamingVersion);
	}
	
	return (m_nNetStreamingVersion == NETSTREAM_VERSION) ? S_OK : E_FAIL;
}

//requests and receives basic information about the acquisition from server
HRESULT RNetStreamingReceiver::ClientGetBasicInfo(BasicInfoAcq* pnBasicInfo)
{
	if (!pnBasicInfo)
	{
		return E_INVALIDARG;
	}

	if (!m_bClientInited)
	{
		return E_FAIL;
	}

	m_bBasicInfoValid = false;

	//send basic info request to server
	AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_BasicInfoAcq);
	if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
	{
		return E_FAIL;
	}

	//receive some packets, hoping the server will reply
	long nCounter = 0;
	while (!m_bBasicInfoValid && nCounter < 10)
	{
		usleep(50000);
		if (FAILED(ListenClient(1, NULL)))
		{
			std::cout << "Failed to recieve NetStreaming Version." << std::endl;
			return E_FAIL;
		}
		nCounter++;
	}
	
	if (m_bBasicInfoValid)
	{
		//copy basicinfo
		memcpy(pnBasicInfo, (BasicInfoAcq*)&m_BasicInfo, sizeof(*pnBasicInfo)); //should be safe to cast away the volatile here, but still ugly
		
		std_msgs::UInt16 msg;
		msg.data = m_BasicInfo.nRate;
		ROS_INFO("I pub sample rate %u", msg.data);
		rate_pub.publish(msg);

		msg.data = m_BasicInfo.nEegChan;
		ROS_INFO("I pub eeg channel nums %u", msg.data);
		chanNum_pub.publish(msg);
		
		return S_OK;
	}

	return E_FAIL;
}

//requests and receives specific channel information from server
HRESULT RNetStreamingReceiver::ClientGetChannelInfoList(NetStreamingChannelInfo* pChannelInfoList, long nSize)
{
	if (!pChannelInfoList || nSize <= 0)
	{
		return E_INVALIDARG;
	}

	if (!m_bClientInited)
	{
		return E_FAIL;
	}

	if (m_pChannelInfoList)
	{
		free((void*)m_pChannelInfoList);
		m_pChannelInfoList = NULL;
	}
	m_nChannelInfoListSize = 0;

	//send label request to server
	AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_ChannelInfo);
	
	if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
	{
		return E_FAIL;
	}

	//receive some packets, hoping the server will reply
	long nCounter = 0;
	while (m_nChannelInfoListSize != nSize && nCounter < 10)
	{
		usleep(50000);
		if (FAILED(ListenClient(1, NULL)))
		{
			std::cout << "Failed to recieve NetStreaming Version." << std::endl;
			return E_FAIL;
		}
		nCounter++;
	}
	
	if (m_pChannelInfoList && m_nChannelInfoListSize == nSize)
	{
		//copy channel info list
		memcpy(pChannelInfoList, (NetStreamingChannelInfo*)m_pChannelInfoList, nSize); //should be save to cast away the volatile here, but it's still ugly
		for (long n = 0; n < m_BasicInfo.nEegChan; ++n)
		{
			std::string str;
			// 这样就可以自动检测标签长度
			int iii = 0;
			while (m_pChannelInfoList[n].wcLabel[iii])
			{
				str = str + char(m_pChannelInfoList[n].wcLabel[iii]);
				++iii;
			}
			std_msgs::String msg;
			msg.data = str;
			chan_pub.publish(msg);
		}
		
		return S_OK;
	}

	return E_FAIL;
}

//get info from server whether amplifier is currently connected or unconnected
HRESULT	RNetStreamingReceiver::ClientGetServerAmpStatus(long* pnAmpStatus)
{
	if (!pnAmpStatus)
	{
		return E_INVALIDARG;
	}

	if (!m_bClientInited)
	{
		return E_FAIL;
	}

	m_nServerAmpStatus = -1;

	//send basic info request to server
	AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_StatusAmp);
	if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
	{
		return E_FAIL;
	}

	//receive some packets, hoping the server will reply in time
	long nCounter = 0;
	while (nCounter < 10)
	{
		usleep(50000);
		if (FAILED(ListenClient(1, NULL)))
		{
			std::cout << "Failed to recieve amplifier status." << std::endl;
			return E_FAIL;
		}

		if (m_nServerAmpStatus != -1)
		{
			break;
		}

		nCounter++;
	}
	
	*pnAmpStatus = m_nServerAmpStatus;

	return m_nServerAmpStatus > -1 ? S_OK : E_FAIL;
}

//asks the server to start/stop sending datablocks (waveforms, events, impedances)
HRESULT RNetStreamingReceiver::ClientRequestStreamData(bool bStartStreaming)
{
	if (!m_bClientInited)
	{
		return E_FAIL;
	}

	AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, bStartStreaming ? Request_StreamingStart : Request_StreamingStop);
	return SendNetStreamingMessage(m_SocketClient, &message);
}

//handles block of waveform data
HRESULT RNetStreamingReceiver::DataReady(float* pfData, unsigned long unSize, unsigned long unBlockStartSample)
{
	HRESULT		hr = E_FAIL;
	string		s;
	long		nNumSamples;

	if (m_BasicInfo.nEegChan <= 0)
	{
		std::cout << "ERROR: number of channels is 0" << std::endl;
		return E_FAIL;
	}

	if (!pfData || unSize == 0 || 
		unSize % SIZE_F != 0 ||
		(unSize / SIZE_F) % m_BasicInfo.nEegChan != 0)
	{
		std::cout << "ERROR: data block has an invalid size" << std::endl;
		return E_INVALIDARG;
	}

	nNumSamples = (unSize / SIZE_F) / m_BasicInfo.nEegChan;

	if (nNumSamples <= 0)
	{
		std::cout << "ERROR: no samples in data block" << std::endl;
		return E_FAIL;
	}

	printf("Received Data (StartSample: %ld, %ld samples)\n", unBlockStartSample, nNumSamples);

	std::vector<float> vEegData(pfData, pfData + m_BasicInfo.nEegChan * nNumSamples);
	std_msgs::Float32MultiArray msg;
	msg.data = vEegData;
	ROS_INFO("I pub packet data!");
	data_pub.publish(msg);

	std_msgs::UInt16 msg2;
	msg2.data = nNumSamples;
	ROS_INFO("I pub sample nums %u", msg2.data);
	sampleNum_pub.publish(msg2);

	return S_OK;
}

//handles block of impedance data
HRESULT RNetStreamingReceiver::ImpedanceDataReady(float* pfData, unsigned long unSize)
{
	if (m_BasicInfo.nEegChan <= 0)
	{
		std::cout << "ERROR: number of channels is 0" << std::endl;
		return E_FAIL;
	}

	if (!pfData || unSize == 0 || unSize % SIZE_F != 0 || 
		(unSize / SIZE_F) % m_BasicInfo.nEegChan != 0 || 
		(unSize / SIZE_F) / m_BasicInfo.nEegChan != 1)
	{
		std::cout << "ERROR: data block has an invalid size" << std::endl;
		return E_INVALIDARG;
	}

	string sTmp;
	float	fImp;
	string s = "Impedances (kOhm): ";
	for (unsigned long n = 0; n < (unSize / SIZE_F); ++n)
	{
		fImp = pfData[n] / 1000.0f;
		printf("%ld: %.1f\t", n+1,   fImp < 0.0f	? 0.0f 
										: fImp > 250.0f	? 250.0f 
										: fImp);
	}
	return S_OK;
}

//handles block of event data
HRESULT RNetStreamingReceiver::EventDataReady(NetStreamingEvent* pEventData, unsigned long unSize)
{
	if (!pEventData || unSize == 0 || unSize % sizeof(NetStreamingEvent) != 0)
	{
		return E_INVALIDARG;
	}
	string s;
	return S_OK;
}