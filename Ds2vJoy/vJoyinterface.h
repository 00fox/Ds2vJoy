#pragma once

// Sideband comunication with vJoy Device
// {781EF630-72B2-11d2-B852-00C04FAD5101}
DEFINE_GUID(GUID_DEVINTERFACE_VJOY, 0x781EF630, 0x72B2, 0x11d2, 0xB8, 0x52, 0x00, 0xC0, 0x4F, 0xAD, 0x51, 0x01);

// Usage example:
#define DEVICENAME_STRING			"vJoy"
#define NTDEVICE_NAME_STRING		"\\Device\\"DEVICENAME_STRING
#define SYMBOLIC_NAME_STRING		"\\DosDevices\\"DEVICENAME_STRING
#define	DOS_FILE_NAME				"\\\\.\\"DEVICENAME_STRING
#define VJOY_INTERFACE				L"Device_"

// Version parts
#define VER_X_				0
#define VER_H_				2
#define VER_M_				1
#define VER_L_				9

#define STRINGIFY_1(x)		#x
#define STRINGIFY(x)		STRINGIFY_1(x)
#define PASTE(x, y)			x##y
#define MAKEWIDE(x)			PASTE(L,x)

// Device Attributes
#define VENDOR_N_ID			0x1234
#define	PRODUCT_N_ID		0xBEAD
#define	VERSION_N			(VER_L_ + 0x10*VER_M_ + 0x100*VER_H_ + 0x1000*VER_X_)

// Device Strings
#define VENDOR_STR_ID		L"Shaul Eizikovich"
#define PRODUCT_STR_ID		L"vJoy - Virtual Joystick"
#define	SERIALNUMBER_STR	MAKEWIDE(STRINGIFY(VER_H_)) L"." MAKEWIDE(STRINGIFY(VER_M_)) L"."  MAKEWIDE(STRINGIFY(VER_L_))

// Function codes;
#define F_LOAD_POSITIONS	0x910
#define F_GETATTRIB			0x911
#define F_GET_FFB_DATA		0x912
#define F_SET_FFB_STAT		0x913
#define F_GET_FFB_STAT		0x916
#define F_GET_DEV_INFO      0x917
#define F_IS_DRV_FFB_CAP	0x918
#define F_IS_DRV_FFB_EN		0x919
#define F_GET_DRV_DEV_MAX	0x91A
#define F_GET_DRV_DEV_EN	0x91B
#define F_IS_DEV_FFB_START	0x91C
#define F_GET_DEV_STAT		0x91D
#define F_GET_DRV_INFO		0x91E
#define F_RESET_DEV			0x91F
#define F_GET_POSITIONS		0x920

// IO Device Control codes;
#define IOCTL_VJOY_GET_ATTRIB		CTL_CODE (FILE_DEVICE_UNKNOWN, GETATTRIB, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define LOAD_POSITIONS	            CTL_CODE (FILE_DEVICE_UNKNOWN, F_LOAD_POSITIONS, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define GET_POSITIONS	            CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_POSITIONS, METHOD_BUFFERED, FILE_READ_ACCESS)
#define GET_FFB_DATA	            CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_FFB_DATA, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define SET_FFB_STAT	            CTL_CODE (FILE_DEVICE_UNKNOWN, F_SET_FFB_STAT, METHOD_NEITHER, FILE_ANY_ACCESS)
#define GET_FFB_STAT	            CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_FFB_STAT, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define GET_DEV_INFO			    CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_DEV_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IS_DRV_FFB_CAP			    CTL_CODE (FILE_DEVICE_UNKNOWN, F_IS_DRV_FFB_CAP, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IS_DRV_FFB_EN			    CTL_CODE (FILE_DEVICE_UNKNOWN, F_IS_DRV_FFB_EN, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define GET_DRV_DEV_MAX			    CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_DRV_DEV_MAX, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define GET_DRV_DEV_EN			    CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_DRV_DEV_EN, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IS_DEV_FFB_START			CTL_CODE (FILE_DEVICE_UNKNOWN, F_IS_DEV_FFB_START, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define GET_DEV_STAT				CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_DEV_STAT, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define GET_DRV_INFO				CTL_CODE (FILE_DEVICE_UNKNOWN, F_GET_DRV_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define RESET_DEV					CTL_CODE (FILE_DEVICE_UNKNOWN, F_RESET_DEV, METHOD_BUFFERED, FILE_WRITE_ACCESS)

// Copied from hidport.h
#define IOCTL_HID_SET_FEATURE	0xB0191
#define IOCTL_HID_WRITE_REPORT	0xB000F
#define MAX_N_DEVICES			16 // Maximum number of vJoy devices

typedef struct _HID_DEVICE_ATTRIBUTES
{
	ULONG           Size;
	// sizeof (struct _HID_DEVICE_ATTRIBUTES)

	// Vendor ids of this hid device
	USHORT          VendorID;
	USHORT          ProductID;
	USHORT          VersionNumber;
	USHORT          Reserved[11];

} HID_DEVICE_ATTRIBUTES, * PHID_DEVICE_ATTRIBUTES;

// Error levels for status report
enum ERRLEVEL
{
	INFO,
	WARN,
	ERR,
	FATAL,
	APP
};

// Status report function prototype
#ifdef WINAPI
typedef BOOL(WINAPI* StatusMessageFunc)(void* output, TCHAR* buffer, enum ERRLEVEL level);
#endif

/////////////////////// Joystick Position ///////////////////////
//
// This structure holds data that is passed to the device from
// an external application such as SmartPropoPlus.
//
// Usage example:
//	JOYSTICK_POSITION iReport;
//	:
//	DeviceIoControl (hDevice, 100, &iReport, sizeof(HID_INPUT_REPORT), NULL, 0, &bytes, NULL)
typedef struct _JOYSTICK_POSITION
{
	BYTE	bDevice;	// Index of device. 1-based.
	LONG	wThrottle;
	LONG	wRudder;
	LONG	wAileron;
	LONG	wAxisX;
	LONG	wAxisY;
	LONG	wAxisZ;
	LONG	wAxisXRot;
	LONG	wAxisYRot;
	LONG	wAxisZRot;
	LONG	wSlider;
	LONG	wDial;
	LONG	wWheel;
	LONG	wAxisVX;
	LONG	wAxisVY;
	LONG	wAxisVZ;
	LONG	wAxisVBRX;
	LONG	wAxisVBRY;
	LONG	wAxisVBRZ;
	LONG	lButtons;	// 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
	DWORD	bHats;		// Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
	DWORD	bHatsEx1;	// 16-bit of continuous HAT switch
	DWORD	bHatsEx2;	// 16-bit of continuous HAT switch
	DWORD	bHatsEx3;	// 16-bit of continuous HAT switch
} JOYSTICK_POSITION, * PJOYSTICK_POSITION;

// Superset of JOYSTICK_POSITION
// Extension of JOYSTICK_POSITION with Buttons 33-128 appended to the end of the structure.
typedef struct _JOYSTICK_POSITION_V2
{
	/// JOYSTICK_POSITION
	BYTE	bDevice;	// Index of device. 1-based.
	LONG	wThrottle;
	LONG	wRudder;
	LONG	wAileron;
	LONG	wAxisX;
	LONG	wAxisY;
	LONG	wAxisZ;
	LONG	wAxisXRot;
	LONG	wAxisYRot;
	LONG	wAxisZRot;
	LONG	wSlider;
	LONG	wDial;
	LONG	wWheel;
	LONG	wAxisVX;
	LONG	wAxisVY;
	LONG	wAxisVZ;
	LONG	wAxisVBRX;
	LONG	wAxisVBRY;
	LONG	wAxisVBRZ;
	LONG	lButtons;	// 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
	DWORD	bHats;		// Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
	DWORD	bHatsEx1;	// Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
	DWORD	bHatsEx2;	// Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
	DWORD	bHatsEx3;	// Lower 4 bits: HAT switch or 16-bit of continuous HAT switch LONG lButtonsEx1; // Buttons 33-64

	/// JOYSTICK_POSITION_V2 Extenssion
	LONG lButtonsEx1;	// Buttons 33-64
	LONG lButtonsEx2;	// Buttons 65-96
	LONG lButtonsEx3;	// Buttons 97-128
} JOYSTICK_POSITION_V2, * PJOYSTICK_POSITION_V2;

// HID Descriptor definitions - Axes
#define HID_USAGE_X		0x30
#define HID_USAGE_Y		0x31
#define HID_USAGE_Z		0x32
#define HID_USAGE_RX	0x33
#define HID_USAGE_RY	0x34
#define HID_USAGE_RZ	0x35
#define HID_USAGE_SL0	0x36
#define HID_USAGE_SL1	0x37
#define HID_USAGE_WHL	0x38
#define HID_USAGE_POV	0x39

// HID Descriptor definitions - FFB Effects
#define HID_USAGE_CONST 0x26    // Usage ET Constant Force
#define HID_USAGE_RAMP  0x27    // Usage ET Ramp
#define HID_USAGE_SQUR  0x30    // Usage ET Square
#define HID_USAGE_SINE  0x31    // Usage ET Sine
#define HID_USAGE_TRNG  0x32    // Usage ET Triangle
#define HID_USAGE_STUP  0x33    // Usage ET Sawtooth Up
#define HID_USAGE_STDN  0x34    // Usage ET Sawtooth Down
#define HID_USAGE_SPRNG 0x40    // Usage ET Spring
#define HID_USAGE_DMPR  0x41    // Usage ET Damper
#define HID_USAGE_INRT  0x42    // Usage ET Inertia
#define HID_USAGE_FRIC  0x43    // Usage ET Friction


// HID Descriptor definitions - FFB Report IDs
#define HID_ID_STATE	0x02	// Usage PID State report
#define HID_ID_EFFREP	0x01	// Usage Set Effect Report
#define HID_ID_ENVREP	0x02	// Usage Set Envelope Report
#define HID_ID_CONDREP	0x03	// Usage Set Condition Report
#define HID_ID_PRIDREP	0x04	// Usage Set Periodic Report
#define HID_ID_CONSTREP	0x05	// Usage Set Constant Force Report
#define HID_ID_RAMPREP	0x06	// Usage Set Ramp Force Report
#define HID_ID_CSTMREP	0x07	// Usage Custom Force Data Report
#define HID_ID_SMPLREP	0x08	// Usage Download Force Sample
#define HID_ID_EFOPREP	0x0A	// Usage Effect Operation Report
#define HID_ID_BLKFRREP	0x0B	// Usage PID Block Free Report
#define HID_ID_CTRLREP	0x0C	// Usage PID Device Control
#define HID_ID_GAINREP	0x0D	// Usage Device Gain Report
#define HID_ID_SETCREP	0x0E	// Usage Set Custom Force Report
#define HID_ID_NEWEFREP	0x01	// Usage Create New Effect Report
#define HID_ID_BLKLDREP	0x02	// Usage Block Load Report
#define HID_ID_POOLREP	0x03	// Usage PID Pool Report

///////////////////////////// vJoy device (collection) status ////////////////////////////////////////////
#ifndef VJDSTAT
#define VJDSTAT
enum VjdStat  /* Declares an enumeration data type */
{
	VJD_STAT_OWN,	// The  vJoy Device is owned by this application.
	VJD_STAT_FREE,	// The  vJoy Device is NOT owned by any application (including this one).
	VJD_STAT_BUSY,	// The  vJoy Device is owned by another application. It cannot be acquired by this application.
	VJD_STAT_MISS,	// The  vJoy Device is missing. It either does not exist or the driver is down.
	VJD_STAT_UNKN	// Unknown
};

/* Error codes for some of the functions */
#define NO_HANDLE_BY_INDEX				 -1
#define BAD_PREPARSED_DATA				 -2
#define NO_CAPS				 			 -3
#define BAD_N_BTN_CAPS				 	 -4
#define BAD_CALLOC				 	 	 -5
#define BAD_BTN_CAPS				 	 -6
#define BAD_BTN_RANGE				 	 -7
#define BAD_N_VAL_CAPS				 	 -8
#define BAD_ID_RANGE				 	 -9
#define NO_SUCH_AXIS				 	 -10
#define BAD_DEV_STAT				 	 -11
#define NO_DEV_EXIST				 	 -12
#define NO_FILE_EXIST				 	 -13

/* Registry Constants */
#define REG_PARAM		L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters"
#define REG_PARAM_DEV0	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device0"
#define REG_PARAM_DEV	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device"
#define REG_DEVICE		L"Device"
#define REG_INIT		L"Init"
#define BTN_INIT		L"BTNS"

/* Environment Variables */
#define INTERFACE_LOG_LEVEL		"VJOYINTERFACELOGLEVEL"
#define INTERFACE_LOG_FILE		"VJOYINTERFACELOGFILE"
#define INTERFACE_DEF_LOG_FILE	"vJoyInterface.log"

/* Compatibility definitions */
#define FFB_EFF_CONST 	FFB_EFF_REPORT
#define PFFB_EFF_CONST 	PFFB_EFF_REPORT
#define Ffb_h_Eff_Const Ffb_h_Eff_Report

// Device Axis/POVs/Buttons
struct DEVCTRLS
{
	BOOL	Init;
	BOOL	Rudder;
	BOOL	Aileron;
	BOOL	AxisX;
	BOOL	AxisY;
	BOOL	AxisZ;
	BOOL	AxisXRot;
	BOOL	AxisYRot;
	BOOL	AxisZRot;
	BOOL	Slider;
	BOOL	Dial;
	BOOL	Wheel;
	BOOL	AxisVX;
	BOOL	AxisVY;
	BOOL	AxisVZ;
	BOOL	AxisVBRX;
	BOOL	AxisVBRY;
	BOOL	AxisVBRZ;
	INT		nButtons;
	INT		nDescHats;
	INT		nContHats;
};

struct DeviceStat
{
	HANDLE h;							// Handle to the PDO interface that represents the virtual device
	VjdStat stat;						// Status of the device
	JOYSTICK_POSITION_V2 position;		// Current Position of the device
	HDEVNOTIFY hDeviceNotifyHandle;		// Device Notification Handle
	DEVCTRLS	DeviceControls;			// Structure Holding the data about the device's controls
	PVOID		 pPreParsedData;		// structure contains a top-level collection's preparsed data.
};

struct DEV_INFO
{
	BYTE	DeviceID;		// Device ID: Valid values are 1-16
	BYTE	nImplemented;	// Number of implemented device: Valid values are 1-16
	BYTE	isImplemented;	// Is this device implemented?
	BYTE	MaxDevices;		// Maximum number of devices that may be implemented (16)
	BYTE	DriverFFB;		// Does this driver support FFB (False)
	BYTE	DeviceFFB;		// Does this device support FFB (False)
};

typedef void (CALLBACK* RemovalCB)(BOOL, BOOL, PVOID);

enum FFBEType // FFB Effect Type
{
	// Effect Type
	ET_NONE = 0,	//    No Force
	ET_CONST = 1,	//    Constant Force
	ET_RAMP = 2,	//    Ramp
	ET_SQR = 3,		//    Square
	ET_SINE = 4,    //    Sine
	ET_TRNGL = 5,	//    Triangle
	ET_STUP = 6,	//    Sawtooth Up
	ET_STDN = 7,	//    Sawtooth Down
	ET_SPRNG = 8,	//    Spring
	ET_DMPR = 9,	//    Damper
	ET_INRT = 10,	//    Inertia
	ET_FRCTN = 11,	//    Friction
	ET_CSTM = 12,	//    Custom Force Data
};

enum FFBPType // FFB Packet Type
{
	// Write
	PT_EFFREP = HID_ID_EFFREP,		// Usage Set Effect Report
	PT_ENVREP = HID_ID_ENVREP,		// Usage Set Envelope Report
	PT_CONDREP = HID_ID_CONDREP,	// Usage Set Condition Report
	PT_PRIDREP = HID_ID_PRIDREP,	// Usage Set Periodic Report
	PT_CONSTREP = HID_ID_CONSTREP,	// Usage Set Constant Force Report
	PT_RAMPREP = HID_ID_RAMPREP,	// Usage Set Ramp Force Report
	PT_CSTMREP = HID_ID_CSTMREP,	// Usage Custom Force Data Report
	PT_SMPLREP = HID_ID_SMPLREP,	// Usage Download Force Sample
	PT_EFOPREP = HID_ID_EFOPREP,	// Usage Effect Operation Report
	PT_BLKFRREP = HID_ID_BLKFRREP,	// Usage PID Block Free Report
	PT_CTRLREP = HID_ID_CTRLREP,	// Usage PID Device Control
	PT_GAINREP = HID_ID_GAINREP,	// Usage Device Gain Report
	PT_SETCREP = HID_ID_SETCREP,	// Usage Set Custom Force Report

	// Feature
	PT_NEWEFREP = HID_ID_NEWEFREP + 0x10,	// Usage Create New Effect Report
	PT_BLKLDREP = HID_ID_BLKLDREP + 0x10,	// Usage Block Load Report
	PT_POOLREP = HID_ID_POOLREP + 0x10,		// Usage PID Pool Report
};

enum FFBOP
{
	EFF_START = 1,		// EFFECT START
	EFF_SOLO = 2,		// EFFECT SOLO START
	EFF_STOP = 3,		// EFFECT STOP
};

enum FFB_CTRL
{
	CTRL_ENACT = 1,		// Enable all device actuators.
	CTRL_DISACT = 2,	// Disable all the device actuators.
	CTRL_STOPALL = 3,	// Stop All Effects­ Issues a stop on every running effect.
	CTRL_DEVRST = 4,	// Device Reset– Clears any device paused condition, enables all actuators and clears all effects from memory.
	CTRL_DEVPAUSE = 5,	// Device Pause– The all effects on the device are paused at the current time step.
	CTRL_DEVCONT = 6,	// Device Continue– The all effects that running when the device was paused are restarted from their last time step.
};

enum FFB_EFFECTS
{
	Constant = 0x0001,
	Ramp = 0x0002,
	Square = 0x0004,
	Sine = 0x0008,
	Triangle = 0x0010,
	Sawtooth_Up = 0x0020,
	Sawtooth_Dn = 0x0040,
	Spring = 0x0080,
	Damper = 0x0100,
	Inertia = 0x0200,
	Friction = 0x0400,
	Custom = 0x0800,
};

typedef struct _FFB_DATA
{
	ULONG	size;
	ULONG	cmd;
	UCHAR* data;
} FFB_DATA, * PFFB_DATA;

typedef struct _FFB_EFF_CONSTANT
{
	BYTE EffectBlockIndex;
	LONG Magnitude; 			  // Constant force magnitude: 	-10000 - 10000
} FFB_EFF_CONSTANT, * PFFB_EFF_CONSTANT;

typedef struct _FFB_EFF_RAMP
{
	BYTE		EffectBlockIndex;
	LONG 		Start;             // The Normalized magnitude at the start of the effect (-10000 - 10000)
	LONG 		End;               // The Normalized magnitude at the end of the effect	(-10000 - 10000)
} FFB_EFF_RAMP, * PFFB_EFF_RAMP;

typedef struct _FFB_EFF_REPORT
{
	BYTE		EffectBlockIndex;
	FFBEType	EffectType;
	WORD		Duration;			// Value in milliseconds. 0xFFFF means infinite
	WORD		TrigerRpt;
	WORD		SamplePrd;
	BYTE		Gain;
	BYTE		TrigerBtn;
	BOOL		Polar;				// How to interpret force direction Polar (0-360°) or Cartesian (X,Y)
	union
	{
		BYTE	Direction;			// Polar direction: (0x00-0xFF correspond to 0-360°)
		BYTE	DirX;				// X direction: Positive values are To the right of the center (X); Negative are Two's complement
	};
	BYTE		DirY;				// Y direction: Positive values are below the center (Y); Negative are Two's complement
} FFB_EFF_REPORT, * PFFB_EFF_REPORT;

typedef struct _FFB_EFF_OP
{
	BYTE		EffectBlockIndex;
	FFBOP		EffectOp;
	BYTE		LoopCount;
} FFB_EFF_OP, * PFFB_EFF_OP;

typedef struct _FFB_EFF_PERIOD
{
	BYTE		EffectBlockIndex;
	DWORD		Magnitude;			// Range: 0 - 10000
	LONG 		Offset;				// Range: –10000 - 10000
	DWORD 		Phase;				// Range: 0 - 35999
	DWORD 		Period;				// Range: 0 - 32767
} FFB_EFF_PERIOD, * PFFB_EFF_PERIOD;

typedef struct _FFB_EFF_COND
{
	BYTE		EffectBlockIndex;
	BOOL		isY;
	LONG 		CenterPointOffset;	// CP Offset:  Range -­10000 ­- 10000
	LONG 		PosCoeff;			// Positive Coefficient: Range -­10000 ­- 10000
	LONG 		NegCoeff;			// Negative Coefficient: Range -­10000 ­- 10000
	DWORD 		PosSatur;			// Positive Saturation: Range 0 – 10000
	DWORD 		NegSatur;			// Negative Saturation: Range 0 – 10000
	LONG 		DeadBand;			// Dead Band: : Range 0 – 1000
} FFB_EFF_COND, * PFFB_EFF_COND;

typedef struct _FFB_EFF_ENVLP
{
	BYTE		EffectBlockIndex;
	DWORD 		AttackLevel;		// The Normalized magnitude of the stating point: 0 - 10000
	DWORD 		FadeLevel;			// The Normalized magnitude of the stopping point: 0 - 10000
	DWORD 		AttackTime;			// Time of the attack: 0 - 4294967295
	DWORD 		FadeTime;			// Time of the fading: 0 - 4294967295
} FFB_EFF_ENVLP, * PFFB_EFF_ENVLP;

#define FFB_DATA_READY	 WM_USER+31

typedef void (CALLBACK* FfbGenCB)(PVOID, PVOID);
#endif

///////////////////////////// vJoy device (collection) Control interface /////////////////////////////////
/*
	These functions allow writing feeders and other applications that interface with vJoy
	It is assumed that only one vJoy top-device (= Raw PDO) exists.
	This top-level device can have up to 16 siblings (=top-level Reports/collections)
	Each sibling is refered to as a "vJoy Device" and is attributed a unique Report ID (Range: 1-16).

	Naming convetion:
		VJD = vJoy Device
		rID = Report ID
*/

// Structure that holds initial values of device controls
struct DEVICE_INIT_VALS
{
	UCHAR cb;				// Size in bytes of this structure
	USHORT id;				// Device ID
	UCHAR InitValAxis[8];	// Initial Value of axes (X, Y, Z, RX, RY, RZ, SL1, SL2)  in %
	UCHAR InitValPov[4];	// Initial Value of POVs in % (0xFF means neutral point)
	UCHAR ButtonMask[16];	// Each bit represents a button
};

typedef std::map<int, DeviceStat> vJoyDeviceMap;

void			DeviceChange(WPARAM wParam, LPARAM lParam);
bool			FfbStartThread(HANDLE h);
void			FfbProcessData(WPARAM wParam, LPARAM lParam);
int				WINAPI FfbWaitForData(HANDLE*);
void			FfbSendData(UCHAR* FfbData, DWORD	nBytesTranss);

// Prototypes (Helper Functions)
bool			ExtractNamespace(const WCHAR* SrcDevicePath, WCHAR* DestDevicePath, int* DestSize);
bool			CreateDevicePath(const WCHAR* SrcDevicePath, int Index, WCHAR* DestDevicePath, int DestSize);
bool			isRawDevice(const WCHAR* DevicePath, int Index);
HANDLE			OpenDeviceInterface(UINT iInterFace, DWORD* error);
HANDLE			GetGenControlHadle(void);
bool			GetDevStat(BYTE id, int* nbytes, BYTE* buffer);
bool			GetDrvStat(int* nbytes, BYTE* buffer);
BOOL			GetDeviceNameSpace(WCHAR** NameSpace, int* Size, BOOL Refresh, DWORD* error);
int				GetDeviceIndexById(USHORT VendorId, USHORT ProductId, int BaseIndex);
int				GetDeviceIndexByReportId(USHORT VendorId, USHORT ProductId, BYTE ReportId);
BOOL			GetDeviceVersionNumber(int Index, PUSHORT version);
BOOL			GetDeviceProductString(int Index, PWSTR* pProductString);
BOOL			GetDeviceManufacturerString(int Index, PWSTR* pManufacturerString);
BOOL			GetDeviceSerialNumberString(int Index, PWSTR* pSerialNumberString);
BOOL			GetDeviceAttributes(int Index, PUSHORT VendorID, PUSHORT ProductID, PUSHORT version);
int				GetvJoyReportId(int Index);
HANDLE			GetHandleByIndex(int index);
int				WINAPI CreateDummyWindow(void);
LRESULT			CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void			InitDll(void);
HDEVNOTIFY		RegistervJoyNotification(HWND hWin);
HDEVNOTIFY		RegisterHandleNotification(HWND hWin, HANDLE hDev);
BOOL			InitPosition(int Index);
void			CalcInitValue(USHORT id, DEVICE_INIT_VALS* data_buf);
UINT			GetInitValueFromRegistry(USHORT id, DEVICE_INIT_VALS* data_buf);
void			SavePosition(UINT rID, PVOID pData);
BOOL			GetDevPosition(BYTE id, PJOYSTICK_POSITION_V2 pPosition);
BOOL			Update(UINT rID);
BOOL			GetAxisCaps(UINT rID, UINT Axis, HIDP_VALUE_CAPS* ValCaps);
LONG			GetAxisLogMin(UINT rID, UINT Axis);
LONG			GetAxisLogMax(UINT rID, UINT Axis);
LONG			GetAxisLogMid(UINT rID, UINT Axis);
bool			GetDevInfo(HANDLE h, PVOID data);
int				DbgGetCaps(void);
INT				GetControls(UINT rID);
BOOL			AreControlsInit(UINT rID);

BOOL			vJoyDeviceEntry(int rID);
BOOL			vJoyDeviceRemove(int rID);
void			vJoyDeviceClear(void);
BOOL			Set_PreparsedData(int rID);
BOOL			Get_PreparsedData(int rID, PHIDP_PREPARSED_DATA* pPPData);
void			Set_h(int rID, HANDLE h);
void			Sync_Position(int rID);
HANDLE			Get_h(int rID);
void			Set_stat(int rID, VjdStat status);
VjdStat			Get_stat(int rID);
void			Set_hNotify(int rID, HDEVNOTIFY h);
HDEVNOTIFY		Get_hNotify(int rID);

/////	General driver data
SHORT			GetvJoyVersion(void);
BOOL			vJoyEnabled(void);
PVOID			GetvJoyProductString(void);
PVOID			GetvJoyManufacturerString(void);
PVOID			GetvJoySerialNumberString(void);
BOOL			DriverMatch(WORD* DllVer, WORD* DrvVer);
VOID			RegisterRemovalCB(RemovalCB cb, PVOID data);
BOOL			vJoyFfbCap(BOOL* Supported);					// Is this version of vJoy capable of FFB?
BOOL			GetvJoyMaxDevices(int* n);						// What is the maximum possible number of vJoy devices
BOOL			GetNumberExistingVJD(int* n);					// What is the number of vJoy devices currently enabled

/////	vJoy Device properties
int				GetVJDButtonNumber(UINT rID);					// Get the number of buttons defined in the specified VDJ
int				GetVJDDiscPovNumber(UINT rID);					// Get the number of descrete-type POV hats defined in the specified VDJ
int				GetVJDContPovNumber(UINT rID);					// Get the number of descrete-type POV hats defined in the specified VDJ
BOOL			GetVJDAxisExist(UINT rID, UINT Axis);			// Test if given axis defined in the specified VDJ
BOOL			GetVJDAxisMax(UINT rID, UINT Axis, LONG* Max);	// Get logical Maximum value for a given axis defined in the specified VDJ
BOOL			GetVJDAxisMin(UINT rID, UINT Axis, LONG* Min);	// Get logical Minimum value for a given axis defined in the specified VDJ
enum VjdStat	GetVJDStatus(UINT rID);							// Get the status of the specified vJoy Device.
BOOL			isVJDExists(UINT rID);							// TRUE if the specified vJoy Device exists
int				GetOwnerPid(UINT rID);							// Reurn owner's Process ID if the specified vJoy Device exists

/////	Write access to vJoy Device - Basic
BOOL			AcquireVJD(UINT rID);							// Acquire the specified vJoy Device.
VOID			RelinquishVJD(UINT rID);						// Relinquish the specified vJoy Device.
BOOL			UpdateVJD(UINT rID, PVOID pData);				// Update the position data of the specified vJoy Device.

//// Reset functions
BOOL			ResetVJD(UINT rID);								// Reset all controls to predefined values in the specified VDJ
VOID			ResetAll(void);									// Reset all controls to predefined values in all VDJ
BOOL			ResetButtons(UINT rID);							// Reset all buttons (To 0) in the specified VDJ
BOOL			ResetPovs(UINT rID);							// Reset all POV Switches (To -1) in the specified VDJ

// Write data
BOOL			SetAxis(LONG Value, UINT rID, UINT Axis);		// Write Value to a given axis defined in the specified VDJ 
BOOL			SetBtn(BOOL Value, UINT rID, UCHAR nBtn);		// Write Value to a given button defined in the specified VDJ 
BOOL			SetDiscPov(int Value, UINT rID, UCHAR nPov);	// Write Value to a given descrete POV defined in the specified VDJ 
BOOL			SetContPov(DWORD Value, UINT rID, UCHAR nPov);	// Write Value to a given continuous POV defined in the specified VDJ 

// Force Feedback (FFB) functions
FFBEType		FfbGetEffect();									// Returns effect serial number if active, 0 if inactive
VOID			FfbRegisterGenCB(FfbGenCB cb, PVOID data);
BOOL			FfbStart(UINT rID);								// Start the FFB queues of the specified vJoy Device. deprecated 
VOID			FfbStop(UINT rID);								// Stop the FFB queues of the specified vJoy Device. deprecated
BOOL			IsDeviceFfb(UINT rID);
BOOL			IsDeviceFfbEffect(UINT rID, UINT Effect);

//  Force Feedback (FFB) helper functions
DWORD			Ffb_h_DeviceID(const FFB_DATA* Packet, int* DeviceID);
DWORD			Ffb_h_Type(const FFB_DATA* Packet, FFBPType* Type);
DWORD			Ffb_h_Packet(const FFB_DATA* Packet, WORD* Type, int* DataSize, BYTE* Data[]);
DWORD			Ffb_h_EBI(const FFB_DATA* Packet, int* Index);
DWORD			Ffb_h_Eff_Report(const FFB_DATA* Packet, FFB_EFF_REPORT* Effect);
DWORD			Ffb_h_Eff_Ramp(const FFB_DATA* Packet, FFB_EFF_RAMP* RampEffect);
DWORD			Ffb_h_EffOp(const FFB_DATA* Packet, FFB_EFF_OP* Operation);
DWORD			Ffb_h_DevCtrl(const FFB_DATA* Packet, FFB_CTRL* Control);
DWORD			Ffb_h_Eff_Period(const FFB_DATA* Packet, FFB_EFF_PERIOD* Effect);
DWORD			Ffb_h_Eff_Cond(const FFB_DATA* Packet, FFB_EFF_COND* Condition);
DWORD			Ffb_h_DevGain(const FFB_DATA* Packet, BYTE* Gain);
DWORD			Ffb_h_Eff_Envlp(const FFB_DATA* Packet, FFB_EFF_ENVLP* Envelope);
DWORD			Ffb_h_EffNew(const FFB_DATA* Packet, FFBEType* Effect);
DWORD			Ffb_h_Eff_Constant(const FFB_DATA* Packet, FFB_EFF_CONSTANT* ConstantEffect);
