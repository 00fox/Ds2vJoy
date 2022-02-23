#pragma once
#include "dsButton.h"

#define dsVendorID		0x054C
#define MAX_Serial_Length	127
#define MAX_Input_Length	78
#define DS_Latency_Count	100

class dsDevice
{
	typedef void(*dsInputCallback)(dsDevice*, bool, void*);

public:
	dsDevice();
	~dsDevice();

	void				SetCallback(dsInputCallback cb, void* param);
	void				InputLoop();
	void				OutputLoop();

	BOOL				Active();
	void				PreOpen();
	BOOL				SerialTest(int devicetype);
	void				AssignOffsets();
	BOOL				Open(HWND hWnd, bool verbose = false);
	BOOL				Write();
	BOOL				Close();

	int					Battery();
	BOOL				BatteryCharge();
	BOOL				BatteryFull();

	BOOL				SetTargetSerial(const WCHAR*);
	void				SetLED(byte R, byte G, byte B);
	void				SetOrangeLED(byte val);
	void				SetWhiteLED(byte led);
	void				SetTriggers(int val);
	BOOL				SetMoter(byte left, byte right);

	BOOL				isBT();
	void				DisconnectBT();

	//i=0 or 1
	BOOL				TouchActive(int i = 0);
	int					TouchX(int i = 0);
	int					TouchY(int i = 0);

	dsButton*			GetButton(dsButtonID);

	void				String();

private:
	BOOL				_prewrite();
	BOOL				_write();
	BOOL				_read();
	BOOL				_btcrc();
	BOOL				_parse(bool* updateflag);
	BOOL				_parseMouse(bool* updateflag);
	BOOL				_parseKeyboard(bool* updateflag);

	WCHAR*				GetSerial();
	BYTE				TouchId(int i = 0);

	dsInputCallback		m_callback = NULL;
	void*				m_callbackdata = NULL;
	bool				firstflag = false;

	HANDLE				dsHandle;
	HANDLE				m_hWEvent, m_hREvent;
	WCHAR				dsSerial[MAX_Serial_Length];
	WCHAR				m_TargetSerial[MAX_Serial_Length];

	int					OffsetBatteryLevel = 9;
	int					OffsetBatteryLevelData = 29;
	int					OffsetTouch = 10;
	int					OffsetTouchs = 32;

	byte				m_Red = 0;
	byte				m_Green = 0;
	byte				m_Blue = 0;
	byte				m_Right = 0;
	byte				m_Left = 0;
	byte				m_Orange = 0;
	byte				m_White = 0;
	int					m_Triggers = 0;

	byte*				m_OutputBuf = 0;
	byte*				m_InputBuf = 0;
	int					m_outputOffset;

	HANDLE				m_hThread;
	HANDLE				m_hThread2;
	unsigned int		m_threadID = 0;
	unsigned int		m_threadID2 = 0;
	bool				m_threadShutdown = 0;

	byte				m_receivedData[MAX_Input_Length];
	byte				m_receivedLastData[MAX_Input_Length];
	byte				m_receivedMData[7];
	byte				m_receivedMLastData[7];
	byte				m_receivedKData[13];
	byte				m_receivedKLastData[13];
	int					m_receivedLength;

	bool				m_bBluetooth;
	double				m_latency[DS_Latency_Count];
	HDEVINFO			hDevInfo;
	HIDD_ATTRIBUTES		Attributes;
	PSP_DEVICE_INTERFACE_DETAIL_DATA detail;
	int					m_latencyIdx = 0;
	int					m_inputLen, m_outputLen;
	int					m_crcerrorcount = 0;

	std::mutex			m_mutex;
	std::condition_variable m_write_cv;
	OVERLAPPED			m_oRead, m_oWrite;
	byte				m_write_count;
	byte				m_write_count2;

	dsButton			m_buttons[dsButton::button_Count];
};

	extern byte			battery;
