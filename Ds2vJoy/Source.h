#pragma once
#include "SourceButton.h"

#define dsVendorID		0x054C
#define MAX_Serial_Length	127
#define MAX_Input_Length	78
#define DS_Latency_Count	100
#define MAX_CONTROLLERS		4	//XInput handles up to 4 controllers
#define XINPUT_GAMEPAD_GUIDE	0x0400
#define XINPUT_GAMEPAD_UNKNOWN	0x0800

struct XINPUT_DEVICE_NODE
{
	DWORD dwVidPid;
	XINPUT_DEVICE_NODE* pNext;
};

struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG* pPreferredJoyCfg;
	bool bPreferredJoyCfgValid;
};

namespace
{
	struct bstr_deleter { void operator()(void* p) noexcept { SysFreeString(static_cast<BSTR>(p)); } };
	using ScopedBSTR = std::unique_ptr<OLECHAR[], bstr_deleter>;
}

class Source
{
	typedef void(*SourceCallback)(bool, void*);

public:
	enum DispatchID : byte
	{
		Dispatch_LX,
		Dispatch_LY,
		Dispatch_RX,
		Dispatch_RY,
		Dispatch_L2TR,
		Dispatch_R2TR,
		Dispatch_SL0,
		Dispatch_SL1,
		Dispatch_DPAD,
		Dispatch_DPAD2,
		Dispatch_DPAD3,
		Dispatch_DPAD4,
		Dispatch_SQUARE,
		Dispatch_CROSS,
		Dispatch_CIRCLE,
		Dispatch_TRIANGLE,
		Dispatch_L1,
		Dispatch_R1,
		Dispatch_L2,
		Dispatch_R2,
		Dispatch_SHARE,
		Dispatch_OPTIONS,
		Dispatch_L3,
		Dispatch_R3,
		Dispatch_PS,
		Dispatch_TOUCH,
		Dispatch_MUTE,
		Dispatch_BUTTON16,
		Dispatch_BUTTON17,
		Dispatch_BUTTON18,
		Dispatch_BUTTON19,
		Dispatch_BUTTON20,
		Dispatch_BUTTON21,
		Dispatch_BUTTON22,
		Dispatch_BUTTON23,
		Dispatch_BUTTON24,
		Dispatch_BUTTON25,
		Dispatch_BUTTON26,
		Dispatch_BUTTON27,
		Dispatch_BUTTON28,
		Dispatch_BUTTON29,
		Dispatch_BUTTON30,
		Dispatch_BUTTON31,
		Dispatch_BUTTON32,
		Dispatch_Count
	};

	enum DIAxisID : byte
	{
		DIAxisID_none,
		DIAxisID_1_X,
		DIAxisID_1_Y,
		DIAxisID_1_Z,
		DIAxisID_1_RX,
		DIAxisID_1_RY,
		DIAxisID_1_RZ,
		DIAxisID_1_SL0,
		DIAxisID_1_SL1,
		DIAxisID_2_X,
		DIAxisID_2_Y,
		DIAxisID_2_Z,
		DIAxisID_2_RX,
		DIAxisID_2_RY,
		DIAxisID_2_RZ,
		DIAxisID_2_SL0,
		DIAxisID_2_SL1,
		DIAxisID_Count
	};

	enum DIPOVID : byte
	{
		DIPOVID_none,
		DIPOVID_1_1,
		DIPOVID_1_2,
		DIPOVID_1_3,
		DIPOVID_1_4,
		DIPOVID_2_1,
		DIPOVID_2_2,
		DIPOVID_2_3,
		DIPOVID_2_4,
		DIPOVID_Count
	};

	enum DIButtonID : byte
	{
		DIButtonID_none,
		DIButtonID_1_1,
		DIButtonID_1_2,
		DIButtonID_1_3,
		DIButtonID_1_4,
		DIButtonID_1_5,
		DIButtonID_1_6,
		DIButtonID_1_7,
		DIButtonID_1_8,
		DIButtonID_1_9,
		DIButtonID_1_10,
		DIButtonID_1_11,
		DIButtonID_1_12,
		DIButtonID_1_13,
		DIButtonID_1_14,
		DIButtonID_1_15,
		DIButtonID_1_16,
		DIButtonID_1_64 = DIButtonID_1_16 + 48,
		DIButtonID_2_1,
		DIButtonID_2_2,
		DIButtonID_2_3,
		DIButtonID_2_4,
		DIButtonID_2_5,
		DIButtonID_2_6,
		DIButtonID_2_7,
		DIButtonID_2_8,
		DIButtonID_2_9,
		DIButtonID_2_10,
		DIButtonID_2_11,
		DIButtonID_2_12,
		DIButtonID_2_13,
		DIButtonID_2_14,
		DIButtonID_2_15,
		DIButtonID_2_16,
		DIButtonID_2_64 = DIButtonID_2_16 + 48,
		DIButtonID_Count
	};

	Source();
	~Source();

	void					SetCallback(SourceCallback cb, void* param);

	void					ListOfJoysticks();
	void					Init();
	BOOL					Active();
	BOOL					PreOpen(bool verbose = false);
	BOOL					SetSerial(const WCHAR*);
	BOOL					SerialTest(int devicetype, bool verbose = false);
	BOOL					Open(HWND hWnd, bool verbose = false);
	BOOL					Close(bool end = false);

	BOOL					Write();
	void					InputLoop();
	void					Clear();
	void					OutputLoop();

	void					SetLED(byte R, byte G, byte B);
	void					SetOrangeLED(byte val);
	void					SetWhiteLED(byte led);
	void					SetTriggers(int val);

	BOOL					isBT();
	void					DisconnectBT();

	BOOL					TouchActive(bool i = 0);
	int						TouchX(bool i = 0);
	int						TouchY(bool i = 0);

	SourceButton*			GetButton(SrceButtonID);

	void					String();
	
	static WCHAR*			DIAxisString(DIAxisID);
	static WCHAR*			DIPOVString(DIPOVID);
	static WCHAR*			DIButtonString(DIButtonID);

private:
	static BOOL CALLBACK	ListOfJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	static BOOL CALLBACK	EnumJoysticksCallback1(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	BOOL CALLBACK			_EnumJoysticksCallback1(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	static BOOL CALLBACK	EnumObjectsCallback1(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);
	BOOL CALLBACK			_EnumObjectsCallback1(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);
	static BOOL CALLBACK	EnumJoysticksCallback2(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	BOOL CALLBACK			_EnumJoysticksCallback2(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	static BOOL CALLBACK	EnumObjectsCallback2(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);
	BOOL CALLBACK			_EnumObjectsCallback2(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);

	BOOL					InitDIClient(bool verbose = false);
	BOOL					_read();
	BOOL					_btcrc();
	BOOL					_parse();
	BOOL					_parseDirectInput();
	BOOL					_parseXInput();
	BOOL					_parseMouse();
	BOOL					_parseKeyboard();
	BOOL					_prewrite();
	BOOL					_write();

	BYTE					TouchId(bool i = 0);

	bool					firstflag = true;
	bool					firstflaglost = true;

	SourceCallback			m_callback = NULL;
	void*					m_callbackdata = NULL;

	HANDLE					dsHandle = 0;
	HANDLE					m_hWEvent, m_hREvent;
	WCHAR					dsSerial[MAX_Serial_Length];
	WCHAR					m_TargetSerial[MAX_Serial_Length];

	bool								m_diTween = false;
	inline static LPDIRECTINPUT8		m_diInterface = nullptr;
	inline static LPDIRECTINPUTDEVICE8	m_diJoystick1 = nullptr;
	inline static LPDIRECTINPUTDEVICE8	m_diJoystick2 = nullptr;
	inline static LPDIRECTINPUTDEVICE8	m_diMouse = nullptr;
	inline static WCHAR					m_diProductName1[MAX_PATH];
	inline static WCHAR					m_diProductName2[MAX_PATH];
	inline static bool					m_dipoll1 = true;
	inline static bool					m_diXAxis1 = false;
	inline static bool					m_diYAxis1 = false;
	inline static bool					m_diZAxis1 = false;
	inline static bool					m_diRXAxis1 = false;
	inline static bool					m_diRYAxis1 = false;
	inline static bool					m_diRZAxis1 = false;
	inline static unsigned char			m_diSliderCount1 = 0;	// Number of slider controls
	inline static unsigned char			m_diPOVCount1 = 0;		// Number of POV controls
	inline static unsigned char			m_diButtonCount1 = 0;	// Number of buttons
	inline static bool					m_dipoll2 = true;
	inline static bool					m_diXAxis2 = false;
	inline static bool					m_diYAxis2 = false;
	inline static bool					m_diZAxis2 = false;
	inline static bool					m_diRXAxis2 = false;
	inline static bool					m_diRYAxis2 = false;
	inline static bool					m_diRZAxis2 = false;
	inline static unsigned char			m_diSliderCount2 = 0;	// Number of slider controls
	inline static unsigned char			m_diPOVCount2 = 0;		// Number of POV controls
	inline static unsigned char			m_diButtonCount2 = 0;	// Number of buttons
	inline static bool					m_diMouseActive = false;

	XINPUT_STATE						m_xiController;
	XINPUT_BATTERY_INFORMATION			m_xiBattery;
	bool								m_xiConnected = false;

	typedef DWORD(__stdcall* XIDLLFUNC) (DWORD, XINPUT_STATE*);
	XIDLLFUNC							XInputGetState_DLL;

	byte					m_Red = 0;
	byte					m_Green = 0;
	byte					m_Blue = 0;
	byte					m_Right = 0;
	byte					m_Left = 0;
	byte					m_Orange = 0;
	byte					m_White = 0;
	int						m_Triggers = 0;

	byte*					m_OutputBuf = 0;
	byte*					m_InputBuf = 0;
	int						m_outputOffset;

	HANDLE					m_hThread;
	HANDLE					m_hThread2;
	unsigned int			m_threadID = 0;
	unsigned int			m_threadID2 = 0;
	bool					m_threadShutdown = false;

	byte					m_receivedTouch[8];
	unsigned short			m_receivedLast[SrceOffsetsID::Offset_Count];
	int						m_receivedLength;

	bool					m_bBluetooth;
	double					m_latency[DS_Latency_Count];
	HDEVINFO				hDevInfo;
	HIDD_ATTRIBUTES			Attributes;
	PSP_DEVICE_INTERFACE_DETAIL_DATA detail;
	int						m_latencyIdx = 0;
	int						m_inputLen, m_outputLen;
	int						m_crcerrorcount = 0;

	std::mutex				m_mutex;
	std::condition_variable m_write_cv;
	OVERLAPPED				m_oRead, m_oWrite;
	byte					m_write_count;
	byte					m_write_count2;

};

	typedef					Source::DispatchID SrceDispatchID;
	typedef					Source::DIAxisID SrceDIAxisID;
	typedef					Source::DIPOVID SrceDIPOVID;
	typedef					Source::DIButtonID SrceDIButtonID;
