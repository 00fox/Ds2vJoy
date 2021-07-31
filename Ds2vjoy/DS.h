﻿#pragma once
#define dsVendorID 0x054C
#define MAX_Serial_Length 127
#define MAX_Input_Length 78
#define DS_Latency_Count 100
#include "dsButton.h"

class dsDevice
{
	typedef void(*dsInputCallback)(dsDevice*, bool, void*);

public:
	dsDevice();
	~dsDevice();

	void SetCallback(dsInputCallback cb, void* param);
	void InputLoop();
	void OutputLoop();

	BOOL Active();
	void PreOpen();
	BOOL SerialTest(int devicetype);
	void AssignOffsets();
	BOOL Open(HWND hWnd, bool verbose = false);
	BOOL Write();
	BOOL Close();

	int Battery();
	BOOL BatteryCharge();
	BOOL BatteryFull();

	BOOL SetTargetSerial(const WCHAR*);
	void SetLED(BYTE R, BYTE G, BYTE B);
	void SetOrangeLED(BYTE val);
	void SetWhiteLED(BYTE led);
	void SetTriggers(int val);
	BOOL SetMoter(BYTE left, BYTE right);

	BOOL isBT();
	void DisconnectBT();

	//i=0 or 1
	BOOL TouchActive(int i = 0);
	int TouchX(int i = 0);
	int TouchY(int i = 0);

	dsButton* GetButton(dsButtonID);

	void String();

private:
	void DisposeObject();
	BOOL _prewrite();
	BOOL _write();
	BOOL _read();
	BOOL _btcrc();
	BOOL _parse();

	WCHAR* GetSerial();
	void ToDualSense();
	void ToDualChock();
	BYTE TouchId(int i = 0);

	dsInputCallback m_callback;
	void* m_callbackdata;
	bool firstflag = false;

	HANDLE dsHandle;
	HANDLE m_hWEvent, m_hREvent;
	WCHAR dsSerial[MAX_Serial_Length];
	WCHAR m_TargetSerial[MAX_Serial_Length];

	int OffsetBatteryLevel = 9;
	int OffsetBatteryLevelData = 29;
	int OffsetTouch = 10;
	int OffsetTouchs = 32;

	BYTE m_Red = 0;
	BYTE m_Green = 0;
	BYTE m_Blue = 0;
	BYTE m_Right = 0;
	BYTE m_Left = 0;
	BYTE m_Orange = 0;
	BYTE m_White = 0;
	int m_Triggers = 0;

	BYTE* m_OutputBuf = 0;
	BYTE* m_InputBuf = 0;
	int m_outputOffset;

	HANDLE m_hThread;
	HANDLE m_hThread2;
	UINT32 m_threadID = 0;
	UINT32 m_threadID2 = 0;
	bool m_threadShutdown = 0;

	BYTE m_receivedData[MAX_Input_Length];
	BYTE m_receivedLastData[MAX_Input_Length];
	int m_receivedLength;

	bool m_bBluetooth;
	double m_latency[DS_Latency_Count];
	HDEVINFO hDevInfo;
	HIDD_ATTRIBUTES Attributes;
	PSP_DEVICE_INTERFACE_DETAIL_DATA detail;
	int m_latencyIdx = 0;
	int m_inputLen, m_outputLen;
	int m_crcerrorcount = 0;

	std::mutex m_mutex;
	std::condition_variable m_write_cv;
	OVERLAPPED m_oWrite, m_oRead;
	BYTE m_write_count, m_write_count2;

	dsButton m_buttons[dsButton::button_Count];
};

extern int battery;