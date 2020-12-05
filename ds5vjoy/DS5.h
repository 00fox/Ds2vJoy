#pragma once

#define DS5_VenderID 0x054C
#define MAX_Serial_Length 127
#define MAX_Input_Length 78
#define DS5_Latency_Count 100


#include "DS5Button.h"


class DS5Device
{
	HANDLE hDS5Handle = INVALID_HANDLE_VALUE;
	WCHAR m_DS5Serial[MAX_Serial_Length];
	WCHAR m_TargetSerial[MAX_Serial_Length];
	int m_inputLen, m_outputLen;
	bool m_bBluetooth;
	
	BYTE m_Red = 0;
	BYTE m_Green = 0;
	BYTE m_Blue = 0;
	BYTE m_Right = 0;
	BYTE m_Left = 0;

	HANDLE m_hWEvent,m_hREvent;
	OVERLAPPED m_oWrite,m_oRead;

	BYTE *m_OutputBuf = 0;
	BYTE *m_InputBuf = 0;
	int m_outputOffset;

	HANDLE m_hThread;
	UINT32 m_threadID = 0;
	HANDLE m_hThread2;
	UINT32 m_threadID2 = 0;
	bool m_threadShutdown = 0;

	BYTE m_receivedData[MAX_Input_Length];
	BYTE m_receivedLastData[MAX_Input_Length];
	int m_receivedLength;

	double m_latency[DS5_Latency_Count];
	int m_latencyIdx=0;

	std::mutex m_write_mutex;
	std::condition_variable m_write_cv;
	BYTE m_write_count, m_write_count2;

	bool _prewrite();
	bool _write();
	bool _read();
	bool _btcrc();
	bool _parse();
	int m_crcerrorcount=0;
	DS5Button m_buttons[DS5Button::button_Count];


	enum _parseBuffer {
		OffsetLX = 0,
		OffsetLY,
		OffsetRX,
		OffsetRY,
		OffsetLeftTrigger,
		OffsetRightTrigger,
		OffsetCounter,
		OffsetDPad = 7,
		OffsetSquare = 7,
		OffsetCross = 7,
		OffsetCircle = 7,
		OffsetTriangle = 7,

		OffsetL1 = 8,
		OffsetR1 = 8,
		OffsetL2 = 8,
		OffsetR2 = 8,
		OffsetCreate = 8,
		OffsetOption = 8,
		OffsetL3 = 8,
		OffsetR3 = 8,

		OffsetPS = 9,
		OffsetTouchPadClick = 9,
		OffsetMute = 9,

		OffsetBatteryLevel = 52,
		OffsetTouch = 32

	};

public:
	typedef void(*DS5InputCallback)(DS5Device*,BOOL, void*);

	DS5Device();

	bool Active();
	bool Open();
	bool Close();
	void SetCallback(DS5InputCallback cb, void *param);
	WCHAR * GetSerial();
	bool SetTargetSerial(const WCHAR *);
	bool SetLED(BYTE R, BYTE G, BYTE B);
	bool SetMoter(BYTE left, BYTE right);
	bool Write();
	void InputLoop();
	void OutputLoop();

	bool isBT();
	int Battery();
	bool BatteryCharge();
	bool BatteryFull();
	void DisconnectBT();
	DS5Button * GetButton(DS5ButtonID);

	//i=0 or 1
	bool TouchActive(int i = 0);
	BYTE TouchId(int i = 0);
	int TouchX(int i = 0);
	int TouchY(int i = 0);

	void String();
	~DS5Device();
private:
	DS5InputCallback m_callback;
	void *m_callbackdata;

};


