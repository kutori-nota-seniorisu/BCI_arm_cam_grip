#include <ros/ros.h>
#include "online_analysis/rnetstreamingreceiver.h"
#include <string>
int main(int argc, char *argv[])
{
	ros::init(argc, argv, "datareceive");
	// ROS_INFO("hello");

	HRESULT hr = S_OK;
	BasicInfoAcq m_basicInfo;
	std::string error = "";

	RNetStreamingReceiver m_NetStreaming;
	std::string sIP = "169.254.103.214";
	m_NetStreaming.SetClient(true, sIP, 4455);

	if (FAILED(hr = m_NetStreaming.OpenClient(&error)) ||
		FAILED(hr = m_NetStreaming.ClientCheckNetStreamingVersion()))
	{
		std::cout << "ERROR" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Open Client Success!" << std::endl;
		std::cout << "We Get the Version!" << std::endl;
	}
	sleep(1);
	if (FAILED(hr = m_NetStreaming.ClientGetBasicInfo(&m_basicInfo)))
	{
		std::cout << "ERROR: ClientGetBasicInfo failed" << std::endl;
		return 0;
	}

	if ((m_basicInfo.nEegChan <= 0 || m_basicInfo.nRate <= 0) &&
		FAILED(hr = m_NetStreaming.ClientGetBasicInfo(&m_basicInfo)))
	{
		std::cout << "ERROR: ClientGetBasicInfo failed." << std::endl;
		return 0;
	}
	sleep(1);
	NetStreamingChannelInfo *pNetStreamingChannelInfoList = NULL;
	long nNetStreamingChannelInfoListSize = m_basicInfo.nEegChan * sizeof(NetStreamingChannelInfo);
	
	pNetStreamingChannelInfoList = (NetStreamingChannelInfo *)malloc(nNetStreamingChannelInfoListSize);
	if (!pNetStreamingChannelInfoList)
	{
		hr = E_OUTOFMEMORY;
		return 0;
	}

	if (FAILED(hr = m_NetStreaming.ClientGetChannelInfoList(pNetStreamingChannelInfoList, nNetStreamingChannelInfoListSize)))
	{
		return 0;
	}

	for (long n = 0; n < m_basicInfo.nEegChan; ++n)
	{
		// 这样就可以自动检测标签长度
		int iii = 0;
		while (pNetStreamingChannelInfoList[n].wcLabel[iii])
		{
			std::cout << char(pNetStreamingChannelInfoList[n].wcLabel[iii]);
			++iii;
		}
		std::cout << std::endl;
	}

	sleep(1);
	if (FAILED(hr = m_NetStreaming.ClientRequestStreamData(true)))
	{
		std::cout << "Get Stream Data Failed" << std::endl;
	}

	std::atomic<bool> m_bActive;
	m_bActive = true;
	m_NetStreaming.ListenClient(-1, &m_bActive);
	std::cout << "桀桀桀桀桀桀桀桀桀" << std::endl;
	
	return 0;
}