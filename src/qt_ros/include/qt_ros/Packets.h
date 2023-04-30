#pragma once

//****************************************************************************
// This file contains structs, enums and defines to build and handle the TCP/IP protocol from CURRY8 netstreaming servers.
// Do not change any structs or enums in this file!
//****************************************************************************

#include <QMainWindow>
#include <QtEndian>

#define SIZE_C (sizeof(char))
#define SIZE_F (sizeof(float))

#define NETSTREAM_VERSION (803)					// NetStreaming version
#define MAX_CHANNELS (4000)						// maximum number of channels
#define NETSTREAM_BUFFER_SIZE (1024 * 1024 * 1) // max buffer size in bytes

// Linux下 long:8 wchar_t:4
// Win下 long:4 wchar_t:2
// 故Win下long与wchar_t 均替换成Linux下的int与char16_t
// typedef wchar_t WCLABEL[ 40 ];						//wchar for labels
typedef char16_t WCLABEL[40];
typedef quint16 WORD;
typedef quint32 DWORD;
typedef int BOOL;
typedef long HRESULT;

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr) (((HRESULT)(hr)) < 0)

#define S_OK ((HRESULT)0L)
#define _HRESULT_TYPEDEF_(_sc) ((HRESULT)_sc)
#define E_FAIL _HRESULT_TYPEDEF_(0x80004005L)
#define E_OUTOFMEMORY _HRESULT_TYPEDEF_(0x8007000EL)
#define E_INVALIDARG _HRESULT_TYPEDEF_(0x80070057L)
//****************************************************************************
// do not change the following enums

// NetStreaming packet codes
#define NETSTREAM_CTRL ("CTRL")
#define NETSTREAM_DATA ("DATA")

// CTRL packet codes
enum
{
	CTRL_FromServer = 1,
	CTRL_FromClient = 2,
	CTRL_LAST
};

// messages from Server to Client (use with CTRL_FromServer)
enum
{
	Server_AcquisitionStart = 1, // server notifies client that an amplifier has been started
	Server_AcquisitionStop = 2,	 // server notifies client that an amplifier has been stopped
	Server_ImpedanceStart = 3,	 // server notifies client that an impedance check has been started
	Server_ImpedanceStop = 4,	 // server notifies client that an impedance check has been stopped
	Server_RecordingStart = 5,	 // server notifies client that a recording has been started
	Server_RecordingStop = 6,	 // server notifies client that a recording has been stopped/paused
};

// requests from client to server (use with CTRL_FromClient)
enum
{
	Request_Version = 1,		// request server to send NetStreaming protocol version supported by the server
	Request_ChannelInfo = 3,	// request server to send channel info structure (see NetStreamingChannelInfo)
	Request_StatusAmp = 4,		// request server to send amplifier status
	Request_BasicInfoAcq = 6,	// request server to send basic information about current amplifier configuration (see BasicInfoAcq)
	Request_StreamingStart = 8, // request server to start sending data packets (DATA_Eeg, DATA_Events or DATA_Impedances)
	Request_StreamingStop = 9,	// request server to stop sending data packets
	// the following requests require the server to allow those operations (bAllowClientToControlAmp and/or bAllowClientToControlRec must be TRUE)
	Request_AmpConnect = 10,	 // request server to start amplifier (equivalent to clicking Start Amplifier in CURRY)
	Request_AmpDisconnect = 11,	 // request server to stop amplifier (equivalent to clicking Stop Amplifier in CURRY)
	Request_ImpedanceStart = 12, // request server to start impedance check
	Request_ImpedanceStop = 13,	 // request server to stop impedance check
	Request_RecordingStart = 14, // request server to start recording
	Request_RecordingStop = 15,	 // request server to stop/pause current recording
	Request_Delay = 16,			 // request server to sent timing information that can be used to measure communication delay
	Request_SetRecPath = 17,	 // request server to set recording path for the next recording (can only be set when no amplifier is currently connected)
};

// DATA packet codes
enum
{
	DATA_Info = 1,
	DATA_Eeg = 2,
	DATA_Events = 3,
	DATA_Impedances = 4,
};

// types of DATA_Info blocks
enum
{
	InfoType_Version = 1,
	InfoType_BasicInfoAcq = 2,
	InfoType_ChannelInfo = 4,
	InfoType_StatusAmp = 7,
	InfoType_Time = 9,
};

// types of DATA_Eeg or DATA_Events
enum enumNetViewDataType
{
	DataTypeFloat32bit = 1,
	DataTypeFloat32bitZIP = 2, // not supported in this demo
	DataTypeEventList = 3,
};
//****************************************************************************

//****************************************************************************
// constructs the body of a TCP/IP message
class AcqMessage
{
public:
	// header struct (don't change)
	char m_chId[4];				// ID string, no trailing '\0'
	WORD m_wCode;				// Code
	WORD m_wRequest;			// Request
	DWORD m_unSample;			// sample of data block (only used for DataType_EegData)
	DWORD m_dwSize;				// Body size (in bytes)
	DWORD m_dwSizeUncompressed; // uncompressed Body size (in bytes)
	char *m_pBody;				// Ptr to body data

	// Implementation
	long GetHeaderSize() { return m_nHeaderSize; }
	BOOL IsCtrlPacket() { return (!memcmp(m_chId, NETSTREAM_CTRL, 4)); }
	BOOL IsDataPacket() { return (!memcmp(m_chId, NETSTREAM_DATA, 4)); }
	BOOL IsValid() { return (IsCtrlPacket() || IsDataPacket()) && m_wCode > 0 && m_wRequest > 0; }

	// Construction
public:
	AcqMessage()
	{
		Init(NETSTREAM_CTRL, 1, 1);
	}

	AcqMessage(const char *id, WORD code, WORD request)
	{
		Init(id, code, request);
	}

	~AcqMessage() { m_pBody = NULL; }

	void Convert()
	{
		m_wCode = qToBigEndian<WORD>(m_wCode);
		m_wRequest = qToBigEndian<WORD>(m_wRequest);
		m_dwSize = qToBigEndian<DWORD>(m_dwSize);
		m_dwSizeUncompressed = qToBigEndian<DWORD>(m_dwSizeUncompressed);
		m_unSample = qToBigEndian<DWORD>(m_unSample);
	}

	void SetID(char const *id)
	{
		// memcpy(m_chId, id, _countof(m_chId));
		memcpy(m_chId, id, 4);
	}
	/*
		HRESULT SetBody(char* pBody, DWORD dwSize)	//creates copy of body and adds it to this message
		{
		  if (!pBody || dwSize == 0)
		  {
			return E_INVALIDARG;
		  }

		  if (m_pBody)
		  {
			free(m_pBody);
			m_pBody = NULL;
		  }

		  m_dwSize = 0;

		  if (!(m_pBody = (char*)malloc(dwSize * SIZE_C)))
		  {
			return E_OUTOFMEMORY;
		  }

		  if (::memcpy_s(m_pBody, dwSize * SIZE_C, pBody, dwSize) != 0)
		  {
			m_pBody = NULL;
			return E_FAIL;
		  }

		  m_dwSize = dwSize;

		  return S_OK;
		}
	*/
	void Init(char const *id, WORD code, WORD request)
	{
		SetID(id);
		m_wCode = code;
		m_wRequest = request;
		m_unSample = 0;
		m_dwSize = 0;
		m_dwSizeUncompressed = 0;
		m_nHeaderSize = sizeof(m_chId) + sizeof(m_wCode) + sizeof(m_wRequest) + sizeof(m_dwSize) + sizeof(m_unSample) + sizeof(m_dwSizeUncompressed);
		m_pBody = NULL;
		// ASSERT(m_nHeaderSize == 20);// maybe in mswsockdef.h
		// ASSERT(IsValid());
	}

private:
	long m_nHeaderSize;
};
//****************************************************************************

//****************************************************************************
// struct of a basic info packet (don't change)
struct BasicInfoAcq
{
	DWORD dwSize;				   // size of structure
	int nEegChan;				   // number of EEG channels
	int nRate;					   // sampling rate in Hz
	int nDataSize;				   // 2 for "short", 4 for "int" type of data
	BOOL bAllowClientToControlAmp; // allow client to control amp on server (connect/disconnect/impedance)
	BOOL bAllowClientToControlRec; // allow client to control recording on server (start/pause)

	BasicInfoAcq() { Init(); }
	void Init() { memset((void *)&dwSize, 0, sizeof(BasicInfoAcq)); }
	BOOL Validate() { return (nRate && nEegChan && nDataSize); }
};
//****************************************************************************

//****************************************************************************
// struct of DataType_EventData data packet
struct NetStreamingEvent
{
	int nEventType;
	int nEventLatency;
	int nEventStart;
	int nEventEnd;
	char16_t wcEventAnnotation[260];
};
//****************************************************************************

//****************************************************************************
// types and struct of InfoType_ChannelInfo data packet

typedef enum enumCompumedicsChannelType
{
	CHANNEL_TYPE_EEG = 0,
	CHANNEL_TYPE_BIPOLAR = 1,
	CHANNEL_TYPE_HILEVEL = 2,
	CHANNEL_TYPE_TRIGGER = 3,
	CHANNEL_TYPE_EXTDC = 4,
	CHANNEL_TYPE_CURRY_OTHER = 100,
	CHANNEL_TYPE_CURRY_BP_EEG = 101
} enumCompumedicsChannelType;

typedef enum enumAcquireDeviceType
{
	GROUP_MGFP = -4,
	GROUP_TRIGGER = -3,
	GROUP_AUTO = -2,
	GROUP_OTHER = -1,
	GROUP_EEG = 0
} enumAcquireDeviceType;

typedef enum enumPositionStatus
{
	PS_INVALID = 0,
	PS_LABELMATCHED = 1,
	PS_UNTRANSFORMED = 2,
	PS_SVDTRANSFORMED = 3,
	PS_PANTRANSFORMED = 4,
	PS_CENTERED = 5,
	PS_INTERNAL = 6,
	PS_UNKNOWN = 7,
	PS_V2POSITION = 8,
	PS_FAILEDLABELMATCH = (PS_V2POSITION + 1),
	PS_ZERO = (PS_FAILEDLABELMATCH + 1),
	PS_INTERPOLATED = (PS_ZERO + 1)
} enumPositionStatus;

struct NetStreamingChannelInfo
{

	int nID;
	WCLABEL wcLabel;
	enumCompumedicsChannelType eType;
	enumAcquireDeviceType eDeviceType;

	int nEEGGroup;
	double dPosX;
	double dPosY;
	double dPosZ;
	enumPositionStatus ePosStatus;

	int nBipolarRefChannel;
	float fAdditionalScale; // currently used only on HL channels
	BOOL bIsDropdown;		// indicates electrodes that are not integrated into an electrode cap
	BOOL bIsNoFilter;		// indicates electrodes that shall not be filtered (may contain digital or discrete data such as TTL or SPO2 channels)
};
//****************************************************************************
