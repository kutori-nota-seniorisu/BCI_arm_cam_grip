#ifndef RNETSTREAMINGRECEIVER_H
#define RNETSTREAMINGRECEIVER_H

#include <string>
#include <atomic>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/UInt16.h>
#include "Packets.h"

typedef int SOCKET;
using namespace std;

class RNetStreamingReceiver
{
public:
	RNetStreamingReceiver();
	~RNetStreamingReceiver(void);

	void		SetClient(bool bConnect, string sIP = "", long nPort = 0);
	bool		IsConnected();
	
	HRESULT		OpenClient(string* psError);
	BOOL		StartClientThread();
	HRESULT		CloseClient();

	HRESULT		ClientCheckNetStreamingVersion();
	HRESULT		ClientGetBasicInfo(BasicInfoAcq* pnBasicInfo);
	HRESULT		ClientGetChannelInfoList(NetStreamingChannelInfo* pChannelInfoList, long nSize);
	HRESULT		ClientGetServerAmpStatus(long* pnAmpStatus);

	HRESULT		ClientRequestStreamData(bool bStartStreaming);
	HRESULT		ClientRequestSetRecPath(string sRecPath);
	HRESULT		ClientRequestControlAmp(bool bStart);
	HRESULT		ClientRequestControlRecording(bool bStart);
	HRESULT		ClientRequestControlImpedanceTest(bool bStart);
	HRESULT		ClientGetDelay(double* pdDelayMS);

	bool		ClientIsInited() {return m_bClientInited;}
	bool		ClientIsReceivingData() {return m_bBasicInfoValid;}

	HRESULT		ListenClient(long nNumReceiveMessages, std::atomic<bool>* pbActive);

protected:
	void		AddLogLine(string sLogLine, long nLogID = 0);

	HRESULT		SendNetStreamingMessage(SOCKET socket, AcqMessage* pMessage);
	HRESULT		ReceiveNetStreamingMessage(SOCKET socket, AcqMessage* pMessage);
	HRESULT		HandleMessage(AcqMessage* pMessage, SOCKET nSocketReply);
	HRESULT		SendHTTPMessage(SOCKET socket, string sHTTP);

	//data block handlers
	HRESULT		DataReady(float* pfData, unsigned long unSize, unsigned long unBlockStartSample);
	HRESULT		ImpedanceDataReady(float* pfData, unsigned long unSize);
	HRESULT		EventDataReady(NetStreamingEvent* pEventData, unsigned long unSize);

	long								m_nSocketType;

	bool								m_bDoConnect;
	unsigned short						m_usNetstreamPort;
	string								m_sNetstreamClientServerIP;

	SOCKET								m_SocketClient;
	bool								m_bClientInited;

	volatile int						m_nNetStreamingVersion;

	volatile BasicInfoAcq				m_BasicInfo;
	volatile bool						m_bBasicInfoValid;
	volatile long						m_nServerAmpStatus;

	volatile NetStreamingChannelInfo*	m_pChannelInfoList;
	volatile long						m_nChannelInfoListSize;

	volatile double						m_dTimePackageReceived;

private:
	ros::NodeHandle n;
	ros::Publisher data_pub;
	ros::Publisher rate_pub;
	ros::Publisher chanNum_pub;
	ros::Publisher sampleNum_pub;
	ros::Publisher chan_pub;

};

#endif