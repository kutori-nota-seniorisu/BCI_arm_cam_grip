#ifndef QNETSTREAMINGRECEIVER_H
#define QNETSTREAMINGRECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QThread>
#include <QStringListModel>
#include "qt_ros/Packets.h"
//#include "ui_main_window.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros {

/*****************************************************************************
** Class
*****************************************************************************/

class QNetStreamingReceiver : public QObject
{
	Q_OBJECT
public:
	explicit QNetStreamingReceiver();
	explicit QNetStreamingReceiver(bool bConnect, QString sIP = "", long nPort = 0);
	virtual ~QNetStreamingReceiver();

	void        SetClient(bool bConnect, QString sIP = "", long nPort = 0);
	bool        IsConnected();

	HRESULT     OpenClient();
	HRESULT     CloseClient();

	HRESULT     ClientCheckNetStreamingVersion();
	HRESULT		ClientGetBasicInfo(BasicInfoAcq* pnBasicInfo);
	HRESULT		ClientGetChannelInfoList(NetStreamingChannelInfo* pChannelInfoList, long nSize);
	HRESULT		ClientGetServerAmpStatus(long* pnAmpStatus);

	HRESULT		ClientRequestStreamData(bool bStartStreaming);
	HRESULT		ClientRequestSetRecPath(QString sRecPath);
	HRESULT		ClientRequestControlAmp(bool bStart);
	HRESULT		ClientRequestControlRecording(bool bStart);
	HRESULT		ClientRequestControlImpedanceTest(bool bStart);
	HRESULT		ClientGetDelay(double* pdDelayMS);

	bool		ClientIsInited() {return m_bClientInited;}
	bool		ClientIsReceivingData() {return m_bBasicInfoValid;}

	HRESULT		ListenClient(long nNumReceiveMessages, std::atomic<bool>* pbActive);
private slots:
	void Run();

protected:
	void		AddLogLine(QString sLogLine, long nLogID = 0);

	HRESULT 	SendNetStreamingMessage(QTcpSocket *socket, AcqMessage* pMessage);
	HRESULT 	ReceiveNetStreamingMessage(QTcpSocket *socket, AcqMessage* pMessage);
	HRESULT     HandleMessage(AcqMessage* pMessage, QTcpSocket *socket);
	HRESULT		SendHTTPMessage(QTcpSocket *socket, QString sHTTP);

	//data block handlers
	HRESULT		DataReady(float* pfData, unsigned long unSize, unsigned long unBlockStartSample);
	HRESULT		ImpedanceDataReady(float* pfData, unsigned long unSize);
	HRESULT		EventDataReady(NetStreamingEvent* pEventData, unsigned long unSize);
public:
	enum LogType
	{
		Config,
		Commu,
		Events
	};

	QStringListModel* LoggingConfigModel() { return &logging_config; }
	QStringListModel* LoggingComModel() { return &logging_com; }
	QStringListModel* LoggingEveModel() { return &logging_eve; }
private:
	void Log(const LogType &type, QString msg);

signals:
	void SendData(float* pfData, int nNumChannels, long nNumSamples);
	void SendChan(int nNumChannels);
	void SendRate(int nSampleRate);
    void SendLabel(WCLABEL wclabel);//没用上
	void LoggingConfigUpdated();
	void LoggingComUpdated();
	void LoggingEveUpdated();

private:
	long        m_nSocketType;

	bool        m_bDoConnect;
	unsigned short m_usNetstreamPort;
	QString m_sNetstreamClientServerIP;

	QTcpSocket *m_SocketClient;
	bool m_bClientInited;

	volatile int m_nNetStreamingVersion;

	volatile BasicInfoAcq m_BasicInfo;
	volatile bool m_bBasicInfoValid;
	volatile long m_nServerAmpStatus;

	volatile NetStreamingChannelInfo*	m_pChannelInfoList;
	volatile long m_nChannelInfoListSize;

	volatile double	m_dTimePackageReceived;

	QStringListModel logging_config;
	QStringListModel logging_com;
	QStringListModel logging_eve;
};

} // namespace qt_ros

#endif // QNETSTREAMINGRECEIVER_H
