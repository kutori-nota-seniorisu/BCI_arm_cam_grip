#include "qt_ros/qnetstreamingreceiver.hpp"
#include <QDateTime>
#include <ros/ros.h>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros
{

	/*****************************************************************************
	** Implementation
	*****************************************************************************/

	QNetStreamingReceiver::QNetStreamingReceiver()
	{
		m_bDoConnect = false;
		m_usNetstreamPort = 0;
		m_sNetstreamClientServerIP = "";

		m_bClientInited = false;
		//	m_SocketClient				= new QTcpSocket();
		m_nNetStreamingVersion = -1;
		m_bBasicInfoValid = false;
		m_nServerAmpStatus = -1;
		m_pChannelInfoList = NULL;
		m_nChannelInfoListSize = 0;
	}

	QNetStreamingReceiver::QNetStreamingReceiver(bool bConnect, QString sIP, long nPort)
	{
		m_bDoConnect = bConnect;
		m_sNetstreamClientServerIP = sIP;
		m_usNetstreamPort = (unsigned short)nPort;

		m_bClientInited = false;
		// 为什么不能在构造函数里创建QTcpSocket?
		// 因为QTcpSocket不能跨线程调用，在main_window.cpp中，若创建了QNetStreamingReceiver对象，构造函数一并调用，
		// QTcpSocket对象也是在main_window.cpp中初始化，属于主线程的变量，在Run函数中调用时便会报错。
		// 报错类型为Cannot create children for a parent that is in a different thread
		// 在Run函数中，手动初始化QTcpSocket对象，则该对象属于子线程，可以通过该线程自由读写。
		//	m_SocketClient				= new QTcpSocket();
		m_nNetStreamingVersion = -1;
		m_bBasicInfoValid = false;
		m_nServerAmpStatus = -1;
		m_pChannelInfoList = NULL;
		m_nChannelInfoListSize = 0;
	}

	QNetStreamingReceiver::~QNetStreamingReceiver()
	{
		CloseClient();
		if (m_pChannelInfoList)
		{
			free((void *)m_pChannelInfoList);
		}
		m_nChannelInfoListSize = 0;
	}

	void QNetStreamingReceiver::SetClient(bool bConnect, QString sIP, long nPort)
	{
		m_bDoConnect = bConnect;
		m_sNetstreamClientServerIP = sIP;
		m_usNetstreamPort = (unsigned short)nPort;
	}

	bool QNetStreamingReceiver::IsConnected()
	{
		return m_bDoConnect;
	}

	HRESULT QNetStreamingReceiver::OpenClient()
	{
		CloseClient();

		m_SocketClient->connectToHost(m_sNetstreamClientServerIP, m_usNetstreamPort);
		if (m_SocketClient->waitForConnected())
		{
			qDebug() << "Socket Connect Success";
			m_bClientInited = true;
		}
		else
			qDebug() << "Socket Connect Failed!";

		return S_OK;
	}

	HRESULT QNetStreamingReceiver::CloseClient()
	{
		if (m_bClientInited)
		{
			qDebug() << "Closing Client";

			//    m_Thread.End();

			m_bClientInited = false;
			m_SocketClient->close();
			//    WSACleanup();

			m_bBasicInfoValid = false;
			m_nChannelInfoListSize = 0;
			if (m_pChannelInfoList)
			{
				free((void *)m_pChannelInfoList);
				m_pChannelInfoList = NULL;
			}
		}

		return S_OK;
	}

	HRESULT QNetStreamingReceiver::ClientCheckNetStreamingVersion()
	{
		QString s;

		if (!m_bClientInited)
		{
			return E_FAIL;
		}

		m_nNetStreamingVersion = -1;

		// send basic info request to server
		AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_Version);
		if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
		{
			return E_FAIL;
		}

		// receive some packets, hoping the server will reply
		long nCounter = 0;
		while (m_nNetStreamingVersion == -1 && nCounter < 10)
		{
			m_SocketClient->waitForReadyRead(200);
			// usleep(50);
			if (FAILED(ListenClient(1, NULL)))
			{
				qDebug() << "Failed to receive NetStreaming Version";
				return E_FAIL;
			}
			++nCounter;
		}

		//	qDebug() << m_nNetStreamingVersion;

		Log(Config, "NetStreaming Version " + QString::number(m_nNetStreamingVersion));

		return (m_nNetStreamingVersion == NETSTREAM_VERSION) ? S_OK : E_FAIL;
	}

	HRESULT QNetStreamingReceiver::ClientGetBasicInfo(BasicInfoAcq *pnBasicInfo)
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

		// send basic info request to server
		AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_BasicInfoAcq);
		if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
		{
			return E_FAIL;
		}

		// receive some packets, hoping the server will reply
		long nCounter = 0;
		while (!m_bBasicInfoValid && nCounter < 10)
		{
			m_SocketClient->waitForReadyRead(200);
			if (FAILED(ListenClient(1, NULL)))
			{
				qDebug() << "Failed to receive NetStreaming Version.";
				return E_FAIL;
			}
			++nCounter;
		}

		//	qDebug() << "pnBasicInfo Rate: " + QString::number(m_BasicInfo.nRate);

		if (m_bBasicInfoValid)
		{
			// copy basicinfo
			memcpy(pnBasicInfo, (BasicInfoAcq *)&m_BasicInfo, sizeof(*pnBasicInfo)); // should be safe to cast away the volatile here, but still ugly
			Log(Config, QString::number(m_BasicInfo.nEegChan) + " Channels");
			Log(Config, QString::number(m_BasicInfo.nRate) + " Hz Sample Rate");
			emit SendRate(m_BasicInfo.nRate);

			return S_OK;
		}

		return E_FAIL;
	}

	HRESULT QNetStreamingReceiver::ClientGetChannelInfoList(NetStreamingChannelInfo *pChannelInfoList, long nSize)
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
			free((void *)m_pChannelInfoList);
			m_pChannelInfoList = NULL;
		}
		m_nChannelInfoListSize = 0;

		// send label request to server
		AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, Request_ChannelInfo);

		if (FAILED(SendNetStreamingMessage(m_SocketClient, &message)))
		{
			return E_FAIL;
		}

		// receive some packets, hoping the server will reply
		long nCounter = 0;
		while (m_nChannelInfoListSize != nSize && nCounter < 10)
		{
			m_SocketClient->waitForReadyRead(200);
			if (FAILED(ListenClient(1, NULL)))
			{
				qDebug() << "Failed to recieve NetStreaming Version.";
				return E_FAIL;
			}
			nCounter++;
		}

		if (m_pChannelInfoList && m_nChannelInfoListSize == nSize)
		{
			// copy channel info list
			memcpy(pChannelInfoList, (NetStreamingChannelInfo *)m_pChannelInfoList, nSize); // should be save to cast away the volatile here, but it's still ugly

			QString logChannel = "Labels: ";
			for (int i = 0; i < m_BasicInfo.nEegChan; ++i)
			{
				int j = 0;
				while (m_pChannelInfoList[i].wcLabel[j])
				{
					logChannel += m_pChannelInfoList[i].wcLabel[j];
					++j;
				}
				logChannel += ' ';

//                emit SendLabel(m_pChannelInfoList[i].wcLabel);
			}
			//		qDebug() << logChannel;
			Log(Config, logChannel);

			return S_OK;
		}

		return E_FAIL;
	}

	HRESULT QNetStreamingReceiver::ClientRequestStreamData(bool bStartStreaming)
	{
		if (!m_bClientInited)
		{
			return E_FAIL;
		}

		AcqMessage message(NETSTREAM_CTRL, CTRL_FromClient, bStartStreaming ? Request_StreamingStart : Request_StreamingStop);
		return SendNetStreamingMessage(m_SocketClient, &message);
	}

	HRESULT QNetStreamingReceiver::ListenClient(long nNumReceiveMessages, std::atomic<bool> *pbActive)
	{
		HRESULT hr = 0;
		char *pcBuffer = NULL;
		long nSizeBuffer = NETSTREAM_BUFFER_SIZE * SIZE_C;

		AcqMessage message;
		if (!(pcBuffer = (char *)calloc(NETSTREAM_BUFFER_SIZE, SIZE_C)))
		{
			return 0;
		}

		qDebug() << "Connected to server.";

		// nNumReceiveMessages == -1 for infinite loop (from thread)
		while (nNumReceiveMessages == -1 || nNumReceiveMessages > 0)
		{
			if (!m_bClientInited)
			{
				hr = 0;
				break;
			}

			if (FAILED(hr = ReceiveNetStreamingMessage(m_SocketClient, &message)))
			{
				qDebug() << "ERROR: Receive data failed!";
				break;
			}

			if (FAILED(HandleMessage(&message, m_SocketClient)))
			{
				qDebug() << "ERROR: Handling Message!";
			}

			if (pbActive && !(*pbActive))
			{
				qDebug() << "ListenClient stop received";
				break;
			}

			if (nNumReceiveMessages > 0)
			{
				--nNumReceiveMessages;
			}
		}

		return hr;
	}

	// send header and data in two portions
	HRESULT QNetStreamingReceiver::SendNetStreamingMessage(QTcpSocket *socket, AcqMessage *pMessage)
	{
		QString s;

		if (!socket->isValid() || !pMessage)
		{
			return E_INVALIDARG;
		}

		if (!pMessage->m_pBody)
		{
			pMessage->m_dwSize = 0;
		}

		DWORD dwSize = pMessage->m_dwSize;

		pMessage->Convert();
		//  pMessage->Convert(true);	应该用不到了

		if (socket->write(pMessage->m_chId, pMessage->GetHeaderSize()) == -1)
		{
			qDebug() << "header send failed";
			return E_FAIL;
		}

		if (dwSize)
		{
			if (socket->write(pMessage->m_pBody, dwSize) == -1)
			{
				qDebug() << "data send failed";
				return E_FAIL;
			}
			s = "Send" + QString::number(dwSize / 1024) + "kBytes";
			qDebug() << s;
		}

		return S_OK;
	}

	HRESULT QNetStreamingReceiver::ReceiveNetStreamingMessage(QTcpSocket *socket, AcqMessage *pMessage)
	{
		int error = 0;
		int nRetval = 0;
		DWORD nBytesReceived = 0;
		QString s;

		if (!socket->isValid() || !pMessage)
		{
			return E_INVALIDARG;
		}

		socket->waitForReadyRead();
		if ((nRetval = socket->read((char *)&pMessage->m_chId, pMessage->GetHeaderSize())) == -1)
		{
			qDebug() << "header receive failed";
			return E_FAIL;
		}

		if (nRetval == 0)
		{
			qDebug() << "Server/Client closed connection";
			return E_FAIL;
		}

		pMessage->Convert(); // convert Network byte order to host byte order (Big-Endian -> Little-Endian)

		if (!pMessage->IsValid())
		{
			qDebug() << "ERROR: Received invalid message.";
			return E_FAIL;
		}

		// read body (if any)
		if (pMessage->m_dwSize > 0)
		{
			if (pMessage->m_pBody)
			{
				free(pMessage->m_pBody);
				pMessage->m_pBody = NULL;
			}

			// ASSERT(pMessage->m_dwSize < 10 * 1024 * 1024); //we don't really expect more than 10 MB of data per block

			if (!(pMessage->m_pBody = (char *)calloc(pMessage->m_dwSize, SIZE_C)))
			{
				return E_OUTOFMEMORY;
			}

			nBytesReceived = 0;
			while (nBytesReceived < pMessage->m_dwSize)
			{
				socket->waitForReadyRead(50);
				if ((nRetval = socket->read(pMessage->m_pBody + nBytesReceived, pMessage->m_dwSize - nBytesReceived)) == -1)
				{
					qDebug() << "body receive() failed";
					return E_FAIL;
				}

				nBytesReceived += nRetval;

				if (nRetval == 0)
				{
					qDebug() << "Server/Client closed connection";
					return E_FAIL;
				}
			}

			if (nBytesReceived < 1024)
			{
				s = "Received" + QString::number(nBytesReceived) + "Bytes";
			}
			else
			{
				s = "Received" + QString::number(nBytesReceived / 1024) + "Bytes";
			}

			Log(Commu, s);
			qDebug() << s;

			if (nBytesReceived != pMessage->m_dwSize)
			{
				qDebug() << "ERROR: Didn't receive as much as expected. (maybe connection got closed)";
				return E_FAIL;
			}
		}
		return S_OK;
	}

	HRESULT QNetStreamingReceiver::HandleMessage(AcqMessage *pMessage, QTcpSocket *socket)
	{
		HRESULT hr = S_OK;
		bool bMessageHandled = false;
		QString s;

		if (!pMessage)
		{
			return E_INVALIDARG;
		}

		// handle CTRL packet
		if (pMessage->IsCtrlPacket())
		{
			s = "Control Packet: code = " + QString::number(pMessage->m_wCode) + ", request = " + QString::number(pMessage->m_wRequest);
			qDebug() << s;
			switch (pMessage->m_wCode)
			{
			case CTRL_FromServer:
				switch (pMessage->m_wRequest)
				{
				case Server_AcquisitionStart:
					qDebug() << "From Server: Start Acquisition\n";
					m_bBasicInfoValid = false;
					bMessageHandled = true;
					break;
				case Server_AcquisitionStop:
					qDebug() << "From Server: Stop Acquisition\nPress \"Disconnect\", then \"Connect\" to continue receiving data.";
					m_bBasicInfoValid = false;
					bMessageHandled = true;
					break;
				case Server_ImpedanceStart:
					qDebug() << "From Server: Start Impedance\n";
					bMessageHandled = true;
					break;
				case Server_ImpedanceStop:
					qDebug() << "From Server: Stop Impedance\n";
					bMessageHandled = true;
					break;
				case Server_RecordingStart:
					qDebug() << "From Server: Start Recording\n";
					bMessageHandled = true;
					break;
				case Server_RecordingStop:
					qDebug() << "From Server: Stop Recording\n";
					bMessageHandled = true;
					break;
				default:
					// ASSERT(false);
					break;
				}
				break;

			case CTRL_FromClient:
				// not available in this demo
				break;

			default:
				break;
			}
		}
		// handle DATA packet
		else if (pMessage->IsDataPacket())
		{
			s = "Control Packet: code = " + QString::number(pMessage->m_wCode) + ", request = " + QString::number(pMessage->m_wRequest);
			qDebug() << s;
			switch (pMessage->m_wCode)
			{
			case DATA_Info:
				switch (pMessage->m_wRequest)
				{
				case InfoType_Version:
				{
					qDebug() << sizeof(m_nNetStreamingVersion);
					if (pMessage->m_pBody && pMessage->m_dwSize == sizeof(m_nNetStreamingVersion))
					{
						memcpy((void *)&m_nNetStreamingVersion, pMessage->m_pBody, sizeof(m_nNetStreamingVersion));
						bMessageHandled = true;
					}
					else
					{
						m_nNetStreamingVersion = -1;
						//	          ASSERT(false);
					}
				}
				break;

				case InfoType_BasicInfoAcq:
				{
					BasicInfoAcq *pInfo = (BasicInfoAcq *)pMessage->m_pBody;
					if (pInfo->dwSize == sizeof(BasicInfoAcq))
					{
						memcpy((void *)&m_BasicInfo, pMessage->m_pBody, sizeof(m_BasicInfo));
						m_bBasicInfoValid = (m_BasicInfo.nEegChan > 0 && m_BasicInfo.nEegChan < MAX_CHANNELS && m_BasicInfo.nRate > 0) ||
											(m_BasicInfo.nEegChan == -1 && m_BasicInfo.nRate == -1); // if values are -1, the amplifier is not connected yet
						bMessageHandled = true;
					}
					else
					{
						//	          ASSERT(false);
					}
				}
				break;

				case InfoType_ChannelInfo:
				{
					if (pMessage->m_dwSize > 0 && pMessage->m_dwSize % sizeof(NetStreamingChannelInfo) == 0)
					{
						if (m_pChannelInfoList)
						{
							free((void *)m_pChannelInfoList);
							m_pChannelInfoList = NULL;
						}

						m_nChannelInfoListSize = 0;
						if ((m_pChannelInfoList = (NetStreamingChannelInfo *)malloc(pMessage->m_dwSize)))
						{
							memcpy((void *)m_pChannelInfoList, pMessage->m_pBody, pMessage->m_dwSize);
							m_nChannelInfoListSize = pMessage->m_dwSize;
							bMessageHandled = true;
						}
						else
						{
							hr = E_OUTOFMEMORY;
							//	            ASSERT(false);
						}
					}
					else
					{
						//	          ASSERT(false);
					}
				}
				break;

				case InfoType_StatusAmp:
				{
					if (pMessage->m_pBody && pMessage->m_dwSize == sizeof(m_nServerAmpStatus))
					{
						memcpy((void *)&m_nServerAmpStatus, pMessage->m_pBody, sizeof(m_nServerAmpStatus));
						bMessageHandled = true;
					}
					else
					{
						//	          ASSERT(false);
					}
				}
				break;

				case InfoType_Time:
				{
					if (pMessage->m_pBody && pMessage->m_dwSize == sizeof(m_dTimePackageReceived))
					{
						memcpy((void *)&m_dTimePackageReceived, pMessage->m_pBody, sizeof(m_dTimePackageReceived));
						bMessageHandled = true;
					}
					else
					{
						m_dTimePackageReceived = 0;
						//	          ASSERT(false);
					}
				}
				break;

				default:
					//	        ASSERT(false); //unexpected request
					break;
				}
				break;

			case DATA_Eeg:
				switch (pMessage->m_wRequest)
				{
				case DataTypeFloat32bit:
					if (pMessage->m_dwSize > 0 && pMessage->m_pBody && pMessage->m_dwSize % SIZE_F == 0)
					{
						// pass it to amp
						DataReady((float *)pMessage->m_pBody, pMessage->m_dwSize, pMessage->m_unSample);
						bMessageHandled = true;
					}
					break;

				case DataTypeFloat32bitZIP:
					if (pMessage->m_dwSize > 0 && pMessage->m_dwSizeUncompressed > 0 && pMessage->m_pBody)
					{
						qDebug() << "ERROR: compressed data cannot be handled in this demo. Set the server to send uncompressed data";
						bMessageHandled = true;
					}
					break;

				default:
					qDebug() << "ERROR: data format cannot be handled in this demo";
					break;
				}
				break;

			case DATA_Events:
				switch (pMessage->m_wRequest)
				{
				case DataTypeEventList:
					qDebug() << "dwSize: " << pMessage->m_dwSize << "size of :" << sizeof(NetStreamingEvent);
					qDebug() << "%%%: " << pMessage->m_dwSize % sizeof(NetStreamingEvent);
					if (pMessage->m_dwSize > 0 && pMessage->m_pBody && pMessage->m_dwSize % sizeof(NetStreamingEvent) == 0)
					{
						// pass it to amp
						EventDataReady((NetStreamingEvent *)pMessage->m_pBody, pMessage->m_dwSize);
						bMessageHandled = true;
					}
					break;
				default:
					//				ASSERT(false);
					break;
				}
				break;

			case DATA_Impedances:
				switch (pMessage->m_wRequest)
				{
				case DataTypeFloat32bit:
					if (pMessage->m_dwSize > 0 && pMessage->m_pBody && pMessage->m_dwSize % SIZE_F == 0)
					{
						// pass it to amp
						ImpedanceDataReady((float *)pMessage->m_pBody, pMessage->m_dwSize);
						bMessageHandled = true;
					}
					break;
				default:
					//				ASSERT(false);
					break;
				}
				break;

			default:
				//	      ASSERT(false);
				break;
			}
		}

		if (!bMessageHandled)
		{
			qDebug() << "ERROR: Received unknown message.";
		}

		hr = (SUCCEEDED(hr) && !bMessageHandled) ? E_FAIL : hr;

		return hr;
	}

	HRESULT QNetStreamingReceiver::DataReady(float *pfData, unsigned long unSize, unsigned long unBlockStartSample)
	{
		HRESULT hr = E_FAIL;
		QString s;

		long nNumSamples;

		if (m_BasicInfo.nEegChan <= 0)
		{
			qDebug() << "ERROR: number of channels is 0";
			return E_FAIL;
		}

		if (!pfData || unSize == 0 ||
			unSize % SIZE_F != 0 ||
			(unSize / SIZE_F) % m_BasicInfo.nEegChan != 0)
		{
			qDebug() << "ERROR: data block has an invalid size";
			return E_INVALIDARG;
		}

		nNumSamples = (unSize / SIZE_F) / m_BasicInfo.nEegChan;

		if (nNumSamples <= 0)
		{
			qDebug() << "ERROR: no samples in data block";
			return E_FAIL;
		}

		s = "Received Data (StartSample: " + QString::number(unBlockStartSample) + ", " + QString::number(nNumSamples) + " samples)";

		//	qDebug() << "Received Data (StartSample: " << unBlockStartSample << ", " << nNumSamples << " samples)";
		//	qDebug() << s;
		Log(Commu, s);

		/*
		QString path = "/home/wuyou/out_raw.txt";
		QFile file(path);
		file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
		QTextStream out(&file);
		for (int i = 0; i < m_BasicInfo.nEegChan; ++i)
		{
			for (int j = 0; j < nNumSamples; ++j)
			{
				out << pfData[i * m_BasicInfo.nEegChan + j] << '\t';
			}
			out << '\n';
		}
		file.close();
		*/

		emit SendData(pfData, m_BasicInfo.nEegChan, nNumSamples);
		return S_OK;
	}

	HRESULT QNetStreamingReceiver::ImpedanceDataReady(float *pfData, unsigned long unSize)
	{
		if (m_BasicInfo.nEegChan <= 0)
		{
			qDebug() << "ERROR: number of channels is 0";
			return E_FAIL;
		}

		if (!pfData || unSize == 0 || unSize % SIZE_F != 0 ||
			(unSize / SIZE_F) % m_BasicInfo.nEegChan != 0 ||
			(unSize / SIZE_F) / m_BasicInfo.nEegChan != 1)
		{
			qDebug() << "ERROR: data block has an invalid size";
			return E_INVALIDARG;
		}

		QString sTmp;
		float fImp;
		QString s = "Impedances (kOhm): ";
		for (unsigned long n = 0; n < (unSize / SIZE_F); ++n)
		{
			fImp = pfData[n] / 1000.0f;
			float re = fImp < 0.0f	   ? 0.0f
					   : fImp > 250.0f ? 250.0f
									   : fImp;
			sTmp = QString::number(n + 1) + ": " + QString::number(re) + '\t';
			s += sTmp;
			//		sTmp.Format(L"%d: %.1f\t", n+1,   fImp < 0.0f	? 0.0f
			//										: fImp > 250.0f	? 250.0f
			//										: fImp);
			//		s.Append(sTmp);
		}
		Log(Events, s);
		//	AddLogLine(s,1);

		return S_OK;
	}

	HRESULT QNetStreamingReceiver::EventDataReady(NetStreamingEvent *pEventData, unsigned long unSize)
	{
		if (!pEventData || unSize == 0 || unSize % sizeof(NetStreamingEvent) != 0)
		{
			return E_INVALIDARG;
		}

		QString s;

		for (unsigned long n = 0; n < unSize / sizeof(NetStreamingEvent); ++n)
		{
			// 这一步应该是有问题的 暂时未想到比较好的解决方法
			// 原代码用wcslen来统计字符串宽字符个数，但是由于我修改了类型，所以只能用循环的方式遍历数组并统计，这个方法应该有点问题
			size_t len = 0;
			for (int i = 0; i < 260; ++i)
			{
				if (pEventData[n].wcEventAnnotation[i] != '\0')
					++len;
			}
			// if (wcslen(pEventData[n].wcEventAnnotation) > 0)
			if (len > 0)
			{
				int j = 0;
				QString EventAnnotation = "";
				while (pEventData[n].wcEventAnnotation[j])
				{
					EventAnnotation += pEventData[n].wcEventAnnotation[j];
					++j;
				}
				s = "Event: " + QString::number(pEventData[n].nEventType) + " (" + EventAnnotation + ")\t sample: " + QString::number(pEventData[n].nEventStart) + "\n";
				//			s.Format(L"Event: %d (%s)\t sample: %d\n", pEventData[n].nEventType, pEventData[n].wcEventAnnotation, pEventData[n].nEventStart);
			}
			else
			{
				s = "Event: " + QString::number(pEventData[n].nEventType) + "\t sample: " + QString::number(pEventData[n].nEventStart) + "\n";
				//			s.Format(L"Event: %d\t sample: %d\n", pEventData[n].nEventType, pEventData[n].nEventStart);
			}

			//		AddLogLine(s,2);
			qDebug() << s;
			Log(Events, s);
		}

		return S_OK;
	}

	void QNetStreamingReceiver::Log(const LogType &type, QString msg)
	{
		switch (type)
		{
		case (Config):
		{
			logging_config.insertRows(logging_config.rowCount(), 1);
			QString modelmsg = QDateTime::currentDateTime().toString("hh:mm:ss") + ' ' + msg;
			qDebug() << modelmsg;
			QVariant new_row(modelmsg);
			logging_config.setData(logging_config.index(logging_config.rowCount() - 1), new_row);
			emit LoggingConfigUpdated();
			break;
		}
		case (Commu):
		{
			logging_com.insertRows(logging_com.rowCount(), 1);
			QString modelmsg = QDateTime::currentDateTime().toString("hh:mm:ss") + ' ' + msg;
			qDebug() << modelmsg;
			QVariant new_row(modelmsg);
			logging_com.setData(logging_com.index(logging_com.rowCount() - 1), new_row);
			emit LoggingComUpdated();
			break;
		}
		case (Events):
		{
			logging_eve.insertRows(logging_eve.rowCount(), 1);
			QString modelmsg = QDateTime::currentDateTime().toString("hh:mm:ss") + ' ' + msg;
			qDebug() << modelmsg;
			QVariant new_row(modelmsg);
			logging_eve.setData(logging_eve.index(logging_eve.rowCount() - 1), new_row);
			emit LoggingEveUpdated();
			break;
		}
		}
	}

	void QNetStreamingReceiver::Run()
	{
		HRESULT hr = S_OK;
		BasicInfoAcq m_basicInfo;

		m_SocketClient = new QTcpSocket;
		//	QThread::sleep(2);
		//	qDebug() << "QNetStream Run, wait 2s";
		//	qDebug() << m_sNetstreamClientServerIP;
		//	qDebug() << m_usNetstreamPort;

		//	if (SUCCEEDED(hr = OpenClient()))
		//		qDebug() << "Open Success";
		//	else
		//	{
		//		qDebug() << "Open Failed";
		//		//				break;
		//	}
		hr = OpenClient();

		if (SUCCEEDED(ClientCheckNetStreamingVersion()))
			qDebug() << "Check Success";
		else
		{
			qDebug() << "Check Failed";
			//				break;
		}

		if (SUCCEEDED(hr = ClientGetBasicInfo(&m_basicInfo)))
		{
			qDebug() << "Get Basic Info Success";
			emit SendChan(m_basicInfo.nEegChan);
		}
		else
		{
			qDebug() << "Get Basic Info Failed";
			//				break;
		}

		// get channel properties (label, group, 3D position, etc)
		NetStreamingChannelInfo *pNetStreamingChannelInfoList = NULL;
		long nNetStreamingChannelInfoListSize = m_basicInfo.nEegChan * sizeof(NetStreamingChannelInfo);
		pNetStreamingChannelInfoList = (NetStreamingChannelInfo *)malloc(nNetStreamingChannelInfoListSize);
		if (!pNetStreamingChannelInfoList)
		{
			hr = E_OUTOFMEMORY;
            //break;
		}
		//	QThread::sleep(1);
		if (FAILED(hr = ClientGetChannelInfoList(pNetStreamingChannelInfoList, nNetStreamingChannelInfoListSize)))
		{
            //break;
		}
		for (long n = 0; n < m_basicInfo.nEegChan; ++n)
		{
			qDebug() << pNetStreamingChannelInfoList[n].wcLabel[0]
					 << pNetStreamingChannelInfoList[n].wcLabel[1]
					 << pNetStreamingChannelInfoList[n].wcLabel[2]
					 << pNetStreamingChannelInfoList[n].wcLabel[3];
		}
		//	QThread::sleep(1);
		// notify server to start sending data
		if (FAILED(hr = ClientRequestStreamData(true)))
		{
			//	break;
		}
		std::atomic<bool> m_bActive;
		m_bActive = true;
		ListenClient(-1, &m_bActive);
	}

} // namespace qt_ros
