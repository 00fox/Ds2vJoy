#pragma once

// GUID identifying the bus device. Used by client library to detect and communicate
// 
// IMPORTANT: make sure to change this value if you fork it or introduce 
//				breaking changes!
// 
// {96E42B22-F5E9-42F8-B043-ED0F932F014F}
DEFINE_GUID(GUID_DEVINTERFACE_BUSENUM_VIGEM,
    0x96E42B22, 0xF5E9, 0x42F8, 0xB0, 0x43, 0xED, 0x0F, 0x93, 0x2F, 0x01, 0x4F);

// Represents the desired target type for the emulated device
typedef enum _VIGEM_TARGET_TYPE
{
    // Microsoft Xbox 360 Controller (wired)
    Xbox360Wired = 0,
    // Sony DualShock 4 (wired)
    DualShock4Wired = 2
    // NOTE: 1 skipped on purpose to maintain compatibility

} VIGEM_TARGET_TYPE, * PVIGEM_TARGET_TYPE;

// Values that represent ViGEm errors
typedef enum _VIGEM_ERRORS
{
    VIGEM_ERROR_NONE = 0x20000000,
    VIGEM_ERROR_BUS_NOT_FOUND = 0xE0000001,
    VIGEM_ERROR_NO_FREE_SLOT = 0xE0000002,
    VIGEM_ERROR_INVALID_TARGET = 0xE0000003,
    VIGEM_ERROR_REMOVAL_FAILED = 0xE0000004,
    VIGEM_ERROR_ALREADY_CONNECTED = 0xE0000005,
    VIGEM_ERROR_TARGET_UNINITIALIZED = 0xE0000006,
    VIGEM_ERROR_TARGET_NOT_PLUGGED_IN = 0xE0000007,
    VIGEM_ERROR_BUS_VERSION_MISMATCH = 0xE0000008,
    VIGEM_ERROR_BUS_ACCESS_FAILED = 0xE0000009,
    VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED = 0xE0000010,
    VIGEM_ERROR_CALLBACK_NOT_FOUND = 0xE0000011,
    VIGEM_ERROR_BUS_ALREADY_CONNECTED = 0xE0000012,
    VIGEM_ERROR_BUS_INVALID_HANDLE = 0xE0000013,
    VIGEM_ERROR_XUSB_USERINDEX_OUT_OF_RANGE = 0xE0000014,
    VIGEM_ERROR_INVALID_PARAMETER = 0xE0000015,
    VIGEM_ERROR_NOT_SUPPORTED = 0xE0000016

} VIGEM_ERROR;

/**
 * A macro that defines if the API succeeded
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	01.09.2020
 *
 * @param 	_val_	The error value.
 */
#define VIGEM_SUCCESS(_val_) (_val_ == VIGEM_ERROR_NONE)

 // Defines an alias representing a driver connection object
typedef struct _VIGEM_CLIENT_T* PVIGEM_CLIENT;

// Defines an alias representing a target device object
typedef struct _VIGEM_TARGET_T* PVIGEM_TARGET;

typedef
_Function_class_(EVT_VIGEM_TARGET_ADD_RESULT)
VOID CALLBACK
EVT_VIGEM_TARGET_ADD_RESULT(
    PVIGEM_CLIENT Client,
    PVIGEM_TARGET Target,
    VIGEM_ERROR Result
);

typedef EVT_VIGEM_TARGET_ADD_RESULT* PFN_VIGEM_TARGET_ADD_RESULT;

typedef
_Function_class_(EVT_VIGEM_X360_NOTIFICATION)
VOID CALLBACK
EVT_VIGEM_X360_NOTIFICATION(
    PVIGEM_CLIENT Client,
    PVIGEM_TARGET Target,
    UCHAR LargeMotor,
    UCHAR SmallMotor,
    UCHAR LedNumber,
    LPVOID UserData
);

typedef EVT_VIGEM_X360_NOTIFICATION* PFN_VIGEM_X360_NOTIFICATION;

// The color value (RGB) of a DualShock 4 Lightbar
typedef struct _DS4_LIGHTBAR_COLOR
{
    // Red part of the Lightbar (0-255)
    UCHAR Red;

    // Green part of the Lightbar (0-255)
    UCHAR Green;

    // Blue part of the Lightbar (0-255)
    UCHAR Blue;

} DS4_LIGHTBAR_COLOR, * PDS4_LIGHTBAR_COLOR;

typedef
_Function_class_(EVT_VIGEM_DS4_NOTIFICATION)
VOID CALLBACK
EVT_VIGEM_DS4_NOTIFICATION(
    PVIGEM_CLIENT Client,
    PVIGEM_TARGET Target,
    UCHAR LargeMotor,
    UCHAR SmallMotor,
    DS4_LIGHTBAR_COLOR LightbarColor,
    LPVOID UserData
);

typedef EVT_VIGEM_DS4_NOTIFICATION* PFN_VIGEM_DS4_NOTIFICATION;

// Possible XUSB report buttons
typedef enum _XUSB_BUTTON
{
    XUSB_GAMEPAD_DPAD_UP = 0x0001,
    XUSB_GAMEPAD_DPAD_DOWN = 0x0002,
    XUSB_GAMEPAD_DPAD_LEFT = 0x0004,
    XUSB_GAMEPAD_DPAD_RIGHT = 0x0008,
    XUSB_GAMEPAD_START = 0x0010,
    XUSB_GAMEPAD_BACK = 0x0020,
    XUSB_GAMEPAD_LEFT_THUMB = 0x0040,
    XUSB_GAMEPAD_RIGHT_THUMB = 0x0080,
    XUSB_GAMEPAD_LEFT_SHOULDER = 0x0100,
    XUSB_GAMEPAD_RIGHT_SHOULDER = 0x0200,
    XUSB_GAMEPAD_GUIDE = 0x0400,
    XUSB_GAMEPAD_A = 0x1000,
    XUSB_GAMEPAD_B = 0x2000,
    XUSB_GAMEPAD_X = 0x4000,
    XUSB_GAMEPAD_Y = 0x8000

} XUSB_BUTTON, * PXUSB_BUTTON;

// Represents an XINPUT_GAMEPAD-compatible report structure
typedef struct _XUSB_REPORT
{
    USHORT wButtons;
    BYTE bLeftTrigger;
    BYTE bRightTrigger;
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;

} XUSB_REPORT, * PXUSB_REPORT;

// Initializes a _XUSB_REPORT structure
VOID FORCEINLINE XUSB_REPORT_INIT(
    _Out_ PXUSB_REPORT Report
)
{
    RtlZeroMemory(Report, sizeof(XUSB_REPORT));
}

// DualShock 4 digital buttons
typedef enum _DS4_BUTTONS
{
    DS4_BUTTON_THUMB_RIGHT = 1 << 15,
    DS4_BUTTON_THUMB_LEFT = 1 << 14,
    DS4_BUTTON_OPTIONS = 1 << 13,
    DS4_BUTTON_SHARE = 1 << 12,
    DS4_BUTTON_TRIGGER_RIGHT = 1 << 11,
    DS4_BUTTON_TRIGGER_LEFT = 1 << 10,
    DS4_BUTTON_SHOULDER_RIGHT = 1 << 9,
    DS4_BUTTON_SHOULDER_LEFT = 1 << 8,
    DS4_BUTTON_TRIANGLE = 1 << 7,
    DS4_BUTTON_CIRCLE = 1 << 6,
    DS4_BUTTON_CROSS = 1 << 5,
    DS4_BUTTON_SQUARE = 1 << 4

} DS4_BUTTONS, * PDS4_BUTTONS;

// DualShock 4 special buttons
typedef enum _DS4_SPECIAL_BUTTONS
{
    DS4_SPECIAL_BUTTON_PS = 1 << 0,
    DS4_SPECIAL_BUTTON_TOUCHPAD = 1 << 1

} DS4_SPECIAL_BUTTONS, * PDS4_SPECIAL_BUTTONS;

// DualShock 4 directional pad (HAT) values
typedef enum _DS4_DPAD_DIRECTIONS
{
    DS4_BUTTON_DPAD_NONE = 0x8,
    DS4_BUTTON_DPAD_NORTHWEST = 0x7,
    DS4_BUTTON_DPAD_WEST = 0x6,
    DS4_BUTTON_DPAD_SOUTHWEST = 0x5,
    DS4_BUTTON_DPAD_SOUTH = 0x4,
    DS4_BUTTON_DPAD_SOUTHEAST = 0x3,
    DS4_BUTTON_DPAD_EAST = 0x2,
    DS4_BUTTON_DPAD_NORTHEAST = 0x1,
    DS4_BUTTON_DPAD_NORTH = 0x0

} DS4_DPAD_DIRECTIONS, * PDS4_DPAD_DIRECTIONS;

// DualShock 4 HID Input report
typedef struct _DS4_REPORT
{
    BYTE bThumbLX;
    BYTE bThumbLY;
    BYTE bThumbRX;
    BYTE bThumbRY;
    USHORT wButtons;
    BYTE bSpecial;
    BYTE bTriggerL;
    BYTE bTriggerR;

} DS4_REPORT, * PDS4_REPORT;

// Sets the current state of the D-PAD on a DualShock 4 report
VOID FORCEINLINE DS4_SET_DPAD(
    _Out_ PDS4_REPORT Report,
    _In_ DS4_DPAD_DIRECTIONS Dpad
)
{
    Report->wButtons &= ~0xF;
    Report->wButtons |= (USHORT)Dpad;
}

VOID FORCEINLINE DS4_REPORT_INIT(
    _Out_ PDS4_REPORT Report
)
{
    RtlZeroMemory(Report, sizeof(DS4_REPORT));

    Report->bThumbLX = 0x80;
    Report->bThumbLY = 0x80;
    Report->bThumbRX = 0x80;
    Report->bThumbRY = 0x80;

    DS4_SET_DPAD(Report, DS4_BUTTON_DPAD_NONE);
}

#include <pshpack1.h> // pack structs tightly

// DualShock 4 HID Touchpad structure
typedef struct _DS4_TOUCH
{
    BYTE bPacketCounter;    // timestamp / packet counter associated with touch event
    BYTE bIsUpTrackingNum1; // 0 means down; active low
                            // unique to each finger down, so for a lift and repress the value is incremented
    BYTE bTouchData1[3];    // Two 12 bits values (for X and Y) 
                            // middle byte holds last 4 bits of X and the starting 4 bits of Y
    BYTE bIsUpTrackingNum2; // second touch data immediately follows data of first touch 
    BYTE bTouchData2[3];    // resolution is 1920x943
} DS4_TOUCH, * PDS4_TOUCH;

// DualShock 4 v1 complete HID Input report
typedef struct _DS4_REPORT_EX
{
    union
    {
        struct
        {
            BYTE bThumbLX;
            BYTE bThumbLY;
            BYTE bThumbRX;
            BYTE bThumbRY;
            USHORT wButtons;
            BYTE bSpecial;
            BYTE bTriggerL;
            BYTE bTriggerR;
            USHORT wTimestamp;
            BYTE bBatteryLvl;
            SHORT wGyroX;
            SHORT wGyroY;
            SHORT wGyroZ;
            SHORT wAccelX;
            SHORT wAccelY;
            SHORT wAccelZ;
            BYTE _bUnknown1[5];
            BYTE bBatteryLvlSpecial;
            // really should have a enum to show everything that this can represent (USB charging, battery level; EXT, headset, microphone connected)
            BYTE _bUnknown2[2];
            BYTE bTouchPacketsN; // 0x00 to 0x03 (USB max)
            DS4_TOUCH sCurrentTouch;
            DS4_TOUCH sPreviousTouch[2];
        } Report;

        UCHAR ReportBuffer[63];
    };
} DS4_REPORT_EX, * PDS4_REPORT_EX;

#include <poppack.h>

// Common version for user-mode library and driver compatibility
// 
// On initialization, the user-mode library has this number embedded
// and sends it to the bus on its enumeration. The bus compares this
// number to the one it was compiled with. If they match, the bus
// access is permitted and success reported. If they mismatch, an
// error is reported and the user-mode library skips this instance
#define VIGEM_COMMON_VERSION            0x0001

#define FILE_DEVICE_BUSENUM             FILE_DEVICE_BUS_EXTENDER
#define BUSENUM_IOCTL(_index_)          CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_READ_DATA)
#define BUSENUM_W_IOCTL(_index_)        CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_WRITE_DATA)
#define BUSENUM_R_IOCTL(_index_)        CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_READ_DATA)
#define BUSENUM_RW_IOCTL(_index_)       CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_WRITE_DATA | FILE_READ_DATA)

#define IOCTL_VIGEM_BASE 0x801

// IO control codes
#define IOCTL_VIGEM_PLUGIN_TARGET       BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x000)
#define IOCTL_VIGEM_UNPLUG_TARGET       BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x001)
#define IOCTL_VIGEM_CHECK_VERSION       BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x002)
#define IOCTL_VIGEM_WAIT_DEVICE_READY   BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x003)

#define IOCTL_XUSB_REQUEST_NOTIFICATION BUSENUM_RW_IOCTL(IOCTL_VIGEM_BASE + 0x200)
#define IOCTL_XUSB_SUBMIT_REPORT        BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x201)
#define IOCTL_DS4_SUBMIT_REPORT         BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x202)
#define IOCTL_DS4_REQUEST_NOTIFICATION  BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x203)
//#define IOCTL_XGIP_SUBMIT_REPORT        BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x204)
//#define IOCTL_XGIP_SUBMIT_INTERRUPT     BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x205)
#define IOCTL_XUSB_GET_USER_INDEX       BUSENUM_RW_IOCTL(IOCTL_VIGEM_BASE + 0x206)


//  Data structure used in PlugIn and UnPlug ioctls

#pragma region Plugin

// Data structure used in IOCTL_VIGEM_PLUGIN_TARGET requests
typedef struct _VIGEM_PLUGIN_TARGET
{
    // sizeof (struct _BUSENUM_HARDWARE)
    IN ULONG Size;

    // Serial number of target device
    IN ULONG SerialNo;

    // Type of the target device to emulate
    VIGEM_TARGET_TYPE TargetType;

    //
    // If set, the vendor ID the emulated device is reporting
    // 
    USHORT VendorId;

    // If set, the product ID the emulated device is reporting
    USHORT ProductId;

} VIGEM_PLUGIN_TARGET, * PVIGEM_PLUGIN_TARGET;

// Initializes a VIGEM_PLUGIN_TARGET structure
VOID FORCEINLINE VIGEM_PLUGIN_TARGET_INIT(
    _Out_ PVIGEM_PLUGIN_TARGET PlugIn,
    _In_ ULONG SerialNo,
    _In_ VIGEM_TARGET_TYPE TargetType
)
{
    RtlZeroMemory(PlugIn, sizeof(VIGEM_PLUGIN_TARGET));

    PlugIn->Size = sizeof(VIGEM_PLUGIN_TARGET);
    PlugIn->SerialNo = SerialNo;
    PlugIn->TargetType = TargetType;
}

#pragma endregion 

#pragma region Unplug

// Data structure used in IOCTL_VIGEM_UNPLUG_TARGET requests
typedef struct _VIGEM_UNPLUG_TARGET
{
    // sizeof (struct _REMOVE_HARDWARE)
    IN ULONG Size;

    // Serial number of target device
    ULONG SerialNo;

} VIGEM_UNPLUG_TARGET, * PVIGEM_UNPLUG_TARGET;

// Initializes a VIGEM_UNPLUG_TARGET structure
VOID FORCEINLINE VIGEM_UNPLUG_TARGET_INIT(
    _Out_ PVIGEM_UNPLUG_TARGET UnPlug,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(UnPlug, sizeof(VIGEM_UNPLUG_TARGET));

    UnPlug->Size = sizeof(VIGEM_UNPLUG_TARGET);
    UnPlug->SerialNo = SerialNo;
}

#pragma endregion

#pragma region Check version

typedef struct _VIGEM_CHECK_VERSION
{
    IN ULONG Size;

    IN ULONG Version;

} VIGEM_CHECK_VERSION, * PVIGEM_CHECK_VERSION;

VOID FORCEINLINE VIGEM_CHECK_VERSION_INIT(
    _Out_ PVIGEM_CHECK_VERSION CheckVersion,
    _In_ ULONG Version
)
{
    RtlZeroMemory(CheckVersion, sizeof(VIGEM_CHECK_VERSION));

    CheckVersion->Size = sizeof(VIGEM_CHECK_VERSION);
    CheckVersion->Version = Version;
}

#pragma endregion

#pragma region Wait device ready

typedef struct _VIGEM_WAIT_DEVICE_READY
{
    IN ULONG Size;

    IN ULONG SerialNo;

} VIGEM_WAIT_DEVICE_READY, * PVIGEM_WAIT_DEVICE_READY;

VOID FORCEINLINE VIGEM_WAIT_DEVICE_READY_INIT(
    _Out_ PVIGEM_WAIT_DEVICE_READY WaitReady,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(WaitReady, sizeof(VIGEM_WAIT_DEVICE_READY));

    WaitReady->Size = sizeof(VIGEM_WAIT_DEVICE_READY);
    WaitReady->SerialNo = SerialNo;
}

#pragma endregion 

#pragma region XUSB (aka Xbox 360 device) section

// Data structure used in IOCTL_XUSB_REQUEST_NOTIFICATION requests
typedef struct _XUSB_REQUEST_NOTIFICATION
{
    // sizeof(struct _XUSB_REQUEST_NOTIFICATION)
    ULONG Size;

    // Serial number of target device
    ULONG SerialNo;

    // Vibration intensity value of the large motor (0-255)
    UCHAR LargeMotor;

    // Vibration intensity value of the small motor (0-255)
    UCHAR SmallMotor;

    // Index number of the slot/LED that XUSB.sys has assigned
    UCHAR LedNumber;

} XUSB_REQUEST_NOTIFICATION, * PXUSB_REQUEST_NOTIFICATION;

// Initializes a XUSB_REQUEST_NOTIFICATION structure
VOID FORCEINLINE XUSB_REQUEST_NOTIFICATION_INIT(
    _Out_ PXUSB_REQUEST_NOTIFICATION Request,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Request, sizeof(XUSB_REQUEST_NOTIFICATION));

    Request->Size = sizeof(XUSB_REQUEST_NOTIFICATION);
    Request->SerialNo = SerialNo;
}

// Data structure used in IOCTL_XUSB_SUBMIT_REPORT requests
typedef struct _XUSB_SUBMIT_REPORT
{
    // sizeof(struct _XUSB_SUBMIT_REPORT)
    ULONG Size;

    // Serial number of target device
    ULONG SerialNo;

    // Report to submit to the target device
    XUSB_REPORT Report;

} XUSB_SUBMIT_REPORT, * PXUSB_SUBMIT_REPORT;

// Initializes an XUSB report
VOID FORCEINLINE XUSB_SUBMIT_REPORT_INIT(
    _Out_ PXUSB_SUBMIT_REPORT Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(XUSB_SUBMIT_REPORT));

    Report->Size = sizeof(XUSB_SUBMIT_REPORT);
    Report->SerialNo = SerialNo;
}

typedef struct _XUSB_GET_USER_INDEX
{
    // sizeof(struct _XUSB_GET_USER_INDEX)
    ULONG Size;

    // Serial number of target device
    ULONG SerialNo;

    // User index of target device
    OUT ULONG UserIndex;

} XUSB_GET_USER_INDEX, * PXUSB_GET_USER_INDEX;

// Initializes XUSB_GET_USER_INDEX structure
VOID FORCEINLINE XUSB_GET_USER_INDEX_INIT(
    _Out_ PXUSB_GET_USER_INDEX GetRequest,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(GetRequest, sizeof(XUSB_GET_USER_INDEX));

    GetRequest->Size = sizeof(XUSB_GET_USER_INDEX);
    GetRequest->SerialNo = SerialNo;
}

#pragma endregion

#pragma region DualShock 4 section

typedef struct _DS4_OUTPUT_REPORT
{
    // Vibration intensity value of the small motor (0-255)
    UCHAR SmallMotor;

    // Vibration intensity value of the large motor (0-255)
    UCHAR LargeMotor;

    // Color values of the Lightbar
    DS4_LIGHTBAR_COLOR LightbarColor;

} DS4_OUTPUT_REPORT, * PDS4_OUTPUT_REPORT;

// Data structure used in IOCTL_DS4_REQUEST_NOTIFICATION requests
typedef struct _DS4_REQUEST_NOTIFICATION
{
    // sizeof(struct _XUSB_REQUEST_NOTIFICATION)
    ULONG Size;

    // Serial number of target device
    ULONG SerialNo;

    // The HID output report
    DS4_OUTPUT_REPORT Report;

} DS4_REQUEST_NOTIFICATION, * PDS4_REQUEST_NOTIFICATION;

// Initializes a DS4_REQUEST_NOTIFICATION structure
VOID FORCEINLINE DS4_REQUEST_NOTIFICATION_INIT(
    _Out_ PDS4_REQUEST_NOTIFICATION Request,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Request, sizeof(DS4_REQUEST_NOTIFICATION));

    Request->Size = sizeof(DS4_REQUEST_NOTIFICATION);
    Request->SerialNo = SerialNo;
}

// DualShock 4 request data
typedef struct _DS4_SUBMIT_REPORT
{
    // sizeof(struct _DS4_SUBMIT_REPORT)
    ULONG Size;

    // Serial number of target device
    ULONG SerialNo;

    // HID Input report
    DS4_REPORT Report;

} DS4_SUBMIT_REPORT, * PDS4_SUBMIT_REPORT;

// Initializes a DualShock 4 report
VOID FORCEINLINE DS4_SUBMIT_REPORT_INIT(
    _Out_ PDS4_SUBMIT_REPORT Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(DS4_SUBMIT_REPORT));

    Report->Size = sizeof(DS4_SUBMIT_REPORT);
    Report->SerialNo = SerialNo;

    DS4_REPORT_INIT(&Report->Report);
}

#include <pshpack1.h>

// DualShock 4 extended report request
typedef struct _DS4_SUBMIT_REPORT_EX
{
    // sizeof(struct _DS4_SUBMIT_REPORT_EX)
    _In_ ULONG Size;

    // Serial number of target device
    _In_ ULONG SerialNo;

    // Full size HID report excluding fixed Report ID
    _In_ DS4_REPORT_EX Report;

} DS4_SUBMIT_REPORT_EX, * PDS4_SUBMIT_REPORT_EX;

#include <poppack.h>

// Initializes a DualShock 4 extended report
VOID FORCEINLINE DS4_SUBMIT_REPORT_EX_INIT(
    _Out_ PDS4_SUBMIT_REPORT_EX Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(DS4_SUBMIT_REPORT_EX));

    Report->Size = sizeof(DS4_SUBMIT_REPORT_EX);
    Report->SerialNo = SerialNo;
}

#pragma endregion

// TODO: this is... not optimal. Improve in the future
#define VIGEM_TARGETS_MAX   USHRT_MAX

// Represents a driver connection object
typedef struct _VIGEM_CLIENT_T
{
    HANDLE hBusDevice;

} VIGEM_CLIENT;

// Represents the (connection) state of a target device object
typedef enum _VIGEM_TARGET_STATE
{
    VIGEM_TARGET_NEW,
    VIGEM_TARGET_INITIALIZED,
    VIGEM_TARGET_CONNECTED,
    VIGEM_TARGET_DISCONNECTED
} VIGEM_TARGET_STATE, * PVIGEM_TARGET_STATE;

// Represents a virtual gamepad object
typedef struct _VIGEM_TARGET_T
{
    ULONG Size;
    ULONG SerialNo;
    VIGEM_TARGET_STATE State;
    USHORT VendorId;
    USHORT ProductId;
    VIGEM_TARGET_TYPE Type;
    FARPROC Notification;
    LPVOID NotificationUserData;
    BOOLEAN IsWaitReadyUnsupported;

    HANDLE cancelNotificationThreadEvent;
} VIGEM_TARGET;

#include "ViGEmClient.h"

// Uncomment to compile in crash dump handler
//#define VIGEM_USE_CRASH_HANDLER

#ifdef VIGEM_USE_CRASH_HANDLER
typedef BOOL(WINAPI* MINIDUMPWRITEDUMP)(
    HANDLE hProcess,
    DWORD dwPid,
    HANDLE hFile,
    MINIDUMP_TYPE DumpType,
    CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
    CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
    CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam
    );

LONG WINAPI vigem_internal_exception_handler(struct _EXCEPTION_POINTERS* apExceptionInfo);
#endif

/**
 *  Allocates an object representing a driver connection
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @returns	A PVIGEM_CLIENT object.
 */
PVIGEM_CLIENT vigem_alloc(void);

/**
 * Frees up memory used by the driver connection object
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @param 	vigem	The PVIGEM_CLIENT object.
 */
void vigem_free(PVIGEM_CLIENT vigem);

/**
 * Initializes the driver object and establishes a connection to the emulation bus
 *          driver. Returns an error if no compatible bus device has been found.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @param 	vigem	The PVIGEM_CLIENT object.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_connect(PVIGEM_CLIENT vigem);

/**
 * Disconnects from the bus device and resets the driver object state. The driver object
 *           may be reused again after calling this function. When called, all targets which may
 *           still be connected will be destroyed automatically. Be aware, that allocated target
 *           objects won't be automatically freed, this has to be taken care of by the caller.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @param 	vigem	The PVIGEM_CLIENT object.
 */
void vigem_disconnect(PVIGEM_CLIENT vigem);

/**
 * A useful utility function to check if pre 1.17 driver, meant to be replaced in the future by
 *          more robust version checks, only able to be checked after at least one device has been
 *          successfully plugged in.
 *
 * @author	Jason "megadrago88" Hart
 * @date	17.08.2021
 *
 * @param   target  The PVIGEM_TARGET to check against.
 *
 * @returns	A BOOLEAN, true if the device wait ready ioctl is supported (1.17+) or false if not ( =< 1.16)
 */
BOOLEAN vigem_target_is_waitable_add_supported(PVIGEM_TARGET target);

/**
 * Allocates an object representing an Xbox 360 Controller device.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @returns	A PVIGEM_TARGET representing an Xbox 360 Controller device.
 */
PVIGEM_TARGET vigem_target_x360_alloc(void);

/**
 * Allocates an object representing a DualShock 4 Controller device.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @returns	A PVIGEM_TARGET representing a DualShock 4 Controller device.
 */
PVIGEM_TARGET vigem_target_ds4_alloc(void);

/**
 * Frees up memory used by the target device object. This does not automatically remove
 *          the associated device from the bus, if present. If the target device doesn't get
 *          removed before this call, the device becomes orphaned until the owning process is
 *          terminated.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 */
void vigem_target_free(PVIGEM_TARGET target);

/**
 * Adds a provided target device to the bus driver, which is equal to a device plug-in
 *          event of a physical hardware device. This function blocks until the target device is
 *          in full operational mode.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_add(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);

/**
 * Adds a provided target device to the bus driver, which is equal to a device plug-in
 *          event of a physical hardware device. This function immediately returns. An optional
 *          callback may be registered which gets called on error or if the target device has
 *          become fully operational.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	28.08.2017
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 * @param 	result	An optional function getting called when the target device becomes available.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_add_async(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_TARGET_ADD_RESULT result);

/**
 * Removes a provided target device from the bus driver, which is equal to a device
 *           unplug event of a physical hardware device. The target device object may be reused
 *           after this function is called. If this function is never called on target device
 *           objects, they will be removed from the bus when the owning process terminates.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_remove(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);

/**
 * Registers a function which gets called, when LED index or vibration state changes
 *                 occur on the provided target device. This function fails if the provided
 *                 target device isn't fully operational or in an erroneous state.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	vigem			The driver connection object.
 * @param 	target			The target device object.
 * @param 	notification	The notification callback.
 * @param 	userData		The user data passed to the notification callback.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_x360_register_notification(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_X360_NOTIFICATION notification, LPVOID userData);

/**
 * Registers a function which gets called, when LightBar or vibration state changes
 *                 occur on the provided target device. This function fails if the provided
 *                 target device isn't fully operational or in an erroneous state.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	vigem			The driver connection object.
 * @param 	target			The target device object.
 * @param 	notification	The notification callback.
 * @param 	userData		The user data passed to the notification callback.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_ds4_register_notification(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_DS4_NOTIFICATION notification, LPVOID userData);

/**
 * Removes a previously registered callback function from the provided target object.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 */
void vigem_target_x360_unregister_notification(PVIGEM_TARGET target);

/**
 * Removes a previously registered callback function from the provided target object.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 */
void vigem_target_ds4_unregister_notification(PVIGEM_TARGET target);

/**
 * Overrides the default Vendor ID value with the provided one.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 * @param 	vid   	The Vendor ID to set.
 */
void vigem_target_set_vid(PVIGEM_TARGET target, USHORT vid);

/**
 * Overrides the default Product ID value with the provided one.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 * @param 	pid   	The Product ID to set.
 */
void vigem_target_set_pid(PVIGEM_TARGET target, USHORT pid);

/**
 * Returns the Vendor ID of the provided target device object.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 *
 * @returns	The Vendor ID.
 */
USHORT vigem_target_get_vid(PVIGEM_TARGET target);

/**
 * Returns the Product ID of the provided target device object.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 *
 * @returns	The Product ID.
 */
USHORT vigem_target_get_pid(PVIGEM_TARGET target);

/**
 * Sends a state report to the provided target device.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 * @param 	report	The report to send to the target device.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_x360_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, XUSB_REPORT report);

/**
 * Sends a state report to the provided target device.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 * @param 	report	The report to send to the target device.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_ds4_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, DS4_REPORT report);

/**
 * Sends a full size state report to the provided target device.
 *
 * @author	Benjamin "Nefarius" Höglinger-Stelzer
 * @date	07.09.2020
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 * @param 	report	The report buffer.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_ds4_update_ex(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, DS4_REPORT_EX report);

/**
 * Returns the internal index (serial number) the bus driver assigned to the provided
 *               target device object. Note that this value is specific to the inner workings of
 *               the bus driver, it does not reflect related values like player index or device
 *               arrival order experienced by other APIs. It may be used to identify the target
 *               device object for its lifetime. This value becomes invalid once the target
 *               device is removed from the bus and may change on the next addition of the
 *               device.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 *
 * @returns	The internally used index of the target device.
 */
ULONG vigem_target_get_index(PVIGEM_TARGET target);

/**
 * Returns the type of the provided target device object.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	28.08.2017
 *
 * @param 	target	The target device object.
 *
 * @returns	A VIGEM_TARGET_TYPE.
 */
VIGEM_TARGET_TYPE vigem_target_get_type(PVIGEM_TARGET target);

/**
 * Returns TRUE if the provided target device object is currently attached to the bus,
 *              FALSE otherwise.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	30.08.2017
 *
 * @param 	target	The target device object.
 *
 * @returns	TRUE if device is attached to the bus, FALSE otherwise.
 */
BOOL vigem_target_is_attached(PVIGEM_TARGET target);

/**
 * Returns the user index of the emulated Xenon device. This value correspondents to the
 *                (zero-based) index number representing the player number via LED present on a
 *                physical controller and is compatible to the dwUserIndex property of the
 *                XInput* APIs.
 *
 * @author	Benjamin "Nefarius" Höglinger
 * @date	10.05.2018
 *
 * @param 	vigem 	The driver connection object.
 * @param 	target	The target device object.
 * @param 	index 	The (zero-based) user index of the Xenon device.
 *
 * @returns	A VIGEM_ERROR.
 */
VIGEM_ERROR vigem_target_x360_get_user_index(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PULONG index);
