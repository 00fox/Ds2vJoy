#pragma once

#ifndef _VJOYDEVICE_H
#define _VJOYDEVICE_H

#define HIDP_ITEM_LONG           0xFE
#define HIDP_ITEM_LENGTH_DATA    0x03

#define HIDP_IS_MAIN_ITEM(item)  (((item) & 0xC) == 0x0)
#define HIDP_IS_GLOBAL_ITEM(item) (((item) & 0xC) == 0x4)
#define HIDP_IS_LOCAL_ITEM(item)  (((item) & 0xC) == 0x8)
#define HIDP_IS_RESERVED_ITEM(item) (((item) & 0xC) == 0xC)

// Main Items
// Only main items with one byte data (bSize = 1) are supported.
#define HIDP_MAIN_INPUT_1        0x81
#define HIDP_MAIN_INPUT_2        0x82
#define HIDP_MAIN_OUTPUT_1       0x91
#define HIDP_MAIN_OUTPUT_2       0x92
#define HIDP_MAIN_FEATURE_1      0xB1
#define HIDP_MAIN_FEATURE_2      0xB2
#define HIDP_MAIN_COLLECTION     0xA1
#define HIDP_MAIN_ENDCOLLECTION  0xC0
#define HIDP_ISMAIN(x) (0 == ((x) & 0x0C))
#define HIDP_MAIN_COLLECTION_LINK 0x00
#define HIDP_MAIN_COLLECTION_APP  0x01

// Global Items
#define HIDP_GLOBAL_USAGE_PAGE_1   0x05  // UsagePage of 1 byte
#define HIDP_GLOBAL_USAGE_PAGE_2   0x06  // UsagePage of 2 bytes
#define HIDP_GLOBAL_USAGE_PAGE_4   0x07  // UsagePage of 4 bytes
#define HIDP_GLOBAL_LOG_MIN_1      0x15  // minimum value of size 1 byte.
#define HIDP_GLOBAL_LOG_MIN_2      0x16  // minimum value of size 2 bytes.
#define HIDP_GLOBAL_LOG_MIN_4      0x17  // minimum value of size 4 bytes.
#define HIDP_GLOBAL_LOG_MAX_1      0X25  // maximum of size 1 byte.
#define HIDP_GLOBAL_LOG_MAX_2      0X26  // maximum of size 2 bytes.
#define HIDP_GLOBAL_LOG_MAX_4      0X27  // maximum of size 4 bytes.

#define HIDP_GLOBAL_PHY_MIN_1      0x35  // minimum value of size 1 byte.
#define HIDP_GLOBAL_PHY_MIN_2      0x36  // minimum value of size 2 bytes.
#define HIDP_GLOBAL_PHY_MIN_4      0x37  // minimum value of size 4 bytes.
#define HIDP_GLOBAL_PHY_MAX_1      0X45  // maximum of size 1 byte.
#define HIDP_GLOBAL_PHY_MAX_2      0X46  // maximum of size 2 bytes.
#define HIDP_GLOBAL_PHY_MAX_4      0X47  // maximum of size 4 bytes.

#define HIDP_GLOBAL_UNIT_EXP_1     0x55  // Exponent of size 1 byte.
#define HIDP_GLOBAL_UNIT_EXP_2     0x56  // Exponent of size 2 bytes.
#define HIDP_GLOBAL_UNIT_EXP_4     0x57  // Exponent of size 4 bytes.
#define HIDP_GLOBAL_UNIT_1         0x65  // UNIT of size 1 byte.
#define HIDP_GLOBAL_UNIT_2         0x66  // UNIT of size 2 bytes.
#define HIDP_GLOBAL_UNIT_4         0x67  // UNIT of size 4 bytes.

#define HIDP_GLOBAL_REPORT_SIZE    0x75  // Report size in bits
#define HIDP_GLOBAL_REPORT_ID      0x85  // ID only size 1 byte supported
#define HIDP_GLOBAL_REPORT_COUNT_1 0x95  // Number of data fields 1 byte
#define HIDP_GLOBAL_REPORT_COUNT_2 0x96  // Number of data fields 2 bytes
#define HIDP_GLOBAL_PUSH           0xA4  // The dreaded PUSH command
#define HIDP_GLOBAL_POP            0xB4  // And the dreaded POP command

// Local Items
#define HIDP_LOCAL_USAGE_1         0x09  //
#define HIDP_LOCAL_USAGE_2         0x0A  //
#define HIDP_LOCAL_USAGE_4         0x0B  //
#define HIDP_LOCAL_USAGE_MIN_1     0x19
#define HIDP_LOCAL_USAGE_MIN_2     0x1A
#define HIDP_LOCAL_USAGE_MIN_4     0x1B
#define HIDP_LOCAL_USAGE_MAX_1     0x29
#define HIDP_LOCAL_USAGE_MAX_2     0x2A
#define HIDP_LOCAL_USAGE_MAX_4     0x2B
#define HIDP_LOCAL_DESIG_INDEX     0x39  // Designators of byte size supported
#define HIDP_LOCAL_DESIG_MIN       0x49
#define HIDP_LOCAL_DESIG_MAX       0x59
#define HIDP_LOCAL_STRING_INDEX    0x79  // String indices of size byte supported
#define HIDP_LOCAL_STRING_MIN      0x89
#define HIDP_LOCAL_STRING_MAX      0x99
#define HIDP_LOCAL_DELIMITER       0xA9

// General declarations

// Axes:
// The following define the Internal names and fixed order of the axes (Based on structure DIJOYSTATE2)
#define AxesIDs {\
	L"X", L"Y", L"Z", L"Rx", L"Ry", L"Rz", L"S1", L"S2",\
	L"VX", L"VY", L"VZ", L"VRx", L"VRy", L"VRz", L"VS1", L"VS2",\
	L"AX", L"AY", L"AZ", L"ARx", L"ARy", L"ARz", L"AS1", L"AS2",\
	L"FX", L"FY", L"FZ", L"FRx", L"FRy", L"FRz", L"FS1", L"FS2"}

// Tooltip stringsTT_ 
#define TT_POVDIR L"Four Directions:\r\nNorth, East, South, West\r\nand a neutral state"
#define TT_TABAXES L"Set the active Axes and POV Hat type"

//////////////////////////////////////////////////////////

/* These macros are used to build the report by adding a byte/word at a time*/
#ifndef	 NEXT_BYTE
#define NEXT_BYTE(vReport,Data)   vReport.push_back(Data);
#endif

#ifndef	 NEXT_SHORT
#define NEXT_SHORT(vReport,Data)  vReport.push_back(Data&0xFF); vReport.push_back((Data&0xFF00)>>8);
#endif

#define MAX_N_FFB 	15 // Maximum number of vJoy devices that support FFB
#define MAX_N_DEVICES	16 // Maximum number of vJoy devices
#define MAX_BUTTONS	128
#define MAX_AXES	8

////////////////////////////////////////////////////////////////////
#define REG_PARAM		L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters"
#define REG_PARAM_DEV		L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device"
#define REG_PARAM_FFBDEV	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\FFBDevice"
#define DESC_NAME			L"HidReportDesctiptor"
#define DESC_SIZE			L"HidReportDesctiptorSize"

enum ACTION { config, del, del_all };

// HID Descriptor definitions
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

#endif

static BYTE TLID;
static std::vector<std::vector<BYTE>>  FfbDescriptor = { {
		/*********************** Force Feedback section Device 1 [Start] ***********************/
		/*
			Input
			Collection Datalink (sub-collection)
			Physical Interface (Usage: PID State report)
			ID: 2
			state report:		5X1bit
			Padding:			3bit
			PID Device Control:	1bit
			Effect Block Index:	7bit
			*/
		0x05, 0x0F,        //    Usage Page Physical Interface
		0x09, 0x92,        //    Usage PID State report 
		0xA1, 0x02,        //    Collection Datalink (logical)
		0x85, }, { static_cast<BYTE>(HID_ID_STATE + 0x10 * TLID),    //    Report ID 2
		0x09, 0x9F,    //    Usage Device is Pause 
		0x09, 0xA0,    //    Usage Actuators Enabled
		0x09, 0xA4,    //    Usage Safety Switch
		0x09, 0xA5,    //    Usage Actuator Override Switch
		0x09, 0xA6,    //    Usage Actuator Power
		0x15, 0x00,    //    Logical Minimum 0
		0x25, 0x01,    //    Logical Maximum 1
		0x35, 0x00,    //    Physical Minimum 0
		0x45, 0x01,    //    Physical Maximum 1
		0x75, 0x01,    //    Report Size 1
		0x95, 0x05,    //    Report Count 5
		0x81, 0x02,    //    Input (Variable)
		0x95, 0x03,    //    Report Count 3
		0x81, 0x03,    //    Input (Constant, Variable)
		0x09, 0x94,    //    Usage Effect Playing
		0x15, 0x00,    //    Logical Minimum 0
		0x25, 0x01,    //    Logical Maximum 1
		0x35, 0x00,    //    Physical Minimum 0
		0x45, 0x01,    //    Physical Maximum 1
		0x75, 0x01,    //    Report Size 1
		0x95, 0x01,    //    Report Count 1
		0x81, 0x02,    //    Input (Variable)
		0x09, 0x22,    //    Usage Effect Block Index
		0x15, 0x01,    //    Logical Minimum 1
		0x25, 0x28,    //    Logical Maximum 28h (40d)
		0x35, 0x01,    //    Physical Minimum 1
		0x45, 0x28,    //    Physical Maximum 28h (40d)
		0x75, 0x07,    //    Report Size 7
		0x95, 0x01,    //    Report Count 1
		0x81, 0x02,    //    Input (Variable)
		0xC0,    // End Collection

		/*
			Output
			Collection  Datalink:
			Usage Set Effect Report

			ID:1
			Effect Block Index:	8bit

			subcollection Effect Type
			12 effect types, 8bit each

			*/
			0x09, 0x21,    //    Usage Set Effect Report
			0xA1, 0x02,    //    Collection Datalink (Logical)
			0x85, },{ static_cast<BYTE>(HID_ID_EFFREP + 0x10 * TLID),    //    Report ID 1
			0x09, 0x22,    //    Usage Effect Block Index
			0x15, 0x01,    //    Logical Minimum 1
			0x25, 0x28,    //    Logical Maximum 28h (40d)
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x28,    //    Physical Maximum 28h (40d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x02,    //    Output (Variable)
			0x09, 0x25,    //    Usage Effect Type
			0xA1, 0x02,    //    Collection Datalink
			0x09, HID_USAGE_CONST,    //    Usage ET Constant Force
			0x09, HID_USAGE_RAMP,    //    Usage ET Ramp
			0x09, HID_USAGE_SQUR,    //    Usage ET Square
			0x09, HID_USAGE_SINE,    //    Usage ET Sine
			0x09, HID_USAGE_TRNG,    //    Usage ET Triangle
			0x09, HID_USAGE_STUP,    //    Usage ET Sawtooth Up
			0x09, HID_USAGE_STDN,    //    Usage ET Sawtooth Down
			0x09, HID_USAGE_SPRNG,    //    Usage ET Spring
			0x09, HID_USAGE_DMPR,    //    Usage ET Damper
			0x09, HID_USAGE_INRT,    //    Usage ET Inertia
			0x09, HID_USAGE_FRIC,    //    Usage ET Friction
			0x09, 0x29,    //    Usage ET RESERVED
//			0x09, 0x28,    //    Usage ET Custom Force Data
			0x25, 0x0C,    //    Logical Maximum Ch (12d)
			0x15, 0x01,    //    Logical Minimum 1
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x0C,    //    Physical Maximum Ch (12d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x00,    //    Output
			0xC0,          //    End Collection
			0x09, 0x50,         //    Usage Duration
			0x09, 0x54,         //    Usage Trigger Repeat Interval
			0x09, 0x51,         //    Usage Sample Period
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x7F,    //    Logical Maximum 7FFFh (32767d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x7F,    //    Physical Maximum 7FFFh (32767d)
			0x66, 0x03, 0x10,    //    Unit 1003h (4099d)
			0x55, 0xFD,         //    Unit Exponent FDh (253d)
			0x75, 0x10,         //    Report Size 10h (16d)
			0x95, 0x03,         //    Report Count 3
			0x91, 0x02,         //    Output (Variable)
			0x55, 0x00,         //    Unit Exponent 0
			0x66, 0x00, 0x00,    //    Unit 0
			0x09, 0x52,         //    Usage Gain
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x00,    //    Logical Maximum FFh (255d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x53,         //    Usage Trigger Button
			0x15, 0x01,         //    Logical Minimum 1
			0x25, 0x08,         //    Logical Maximum 8
			0x35, 0x01,         //    Physical Minimum 1
			0x45, 0x08,         //    Physical Maximum 8
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)

			0x09, 0x55,       //    Usage Axes Enable
			0xA1, 0x02,       //    Collection Datalink
			0x05, 0x01,    //    Usage Page Generic Desktop
			0x09, 0x30,    //    Usage X
			0x09, 0x31,    //    Usage Y
			0x15, 0x00,    //    Logical Minimum 0
			0x25, 0x01,    //    Logical Maximum 1
			0x75, 0x01,    //    Report Size 1
			0x95, 0x02,    //    Report Count 2
			0x91, 0x02,    //    Output (Variable)
			0xC0,    // End Collection

			0x05, 0x0F,    //    Usage Page Physical Interface
			0x09, 0x56,    //    Usage Direction Enable
			0x95, 0x01,    //    Report Count 1
			0x91, 0x02,    //    Output (Variable)
			0x95, 0x05,    //    Report Count 5
			0x91, 0x03,    //    Output (Constant, Variable)

			0x09, 0x57,    //    Usage Direction
			0xA1, 0x02,    //    Collection Datalink
			0x0B, 0x01, 0x00, 0x0A, 0x00,    //    Usage Ordinals: Instance 1
			0x0B, 0x02, 0x00, 0x0A, 0x00,    //    Usage Ordinals: Instance 2
			0x66, 0x14, 0x00,              //    Unit 14h (20d)
			0x55, 0xFE,                   //    Unit Exponent FEh (254d)
			0x15, 0x00,                   //    Logical Minimum 0
			0x26, 0xFF, 0x00,              //    Logical Maximum FFh (255d)
			0x35, 0x00,                   //    Physical Minimum 0
			0x47, 0xA0, 0x8C, 0x00, 0x00,    //    Physical Maximum 8CA0h (36000d)
			0x66, 0x00, 0x00,              //    Unit 0
			0x75, 0x08,                   //    Report Size 8
			0x95, 0x02,                   //    Report Count 2
			0x91, 0x02,                   //    Output (Variable)
			0x55, 0x00,                   //    Unit Exponent 0
			0x66, 0x00, 0x00,              //    Unit 0
			0xC0,                           //    End Collection

			0x05, 0x0F,        //     USAGE_PAGE (Physical Interface)
			0x09, 0x58,        //     USAGE (Type Specific Block Offset)
			0xA1, 0x02,        //     COLLECTION (Logical) 
			0x0B, 0x01, 0x00, 0x0A, 0x00, //USAGE (Ordinals:Instance 1
			0x0B, 0x02, 0x00, 0x0A, 0x00, //USAGE (Ordinals:Instance 2)
			0x26, 0xFD, 0x7F, //   LOGICAL_MAXIMUM (32765) ; 32K RAM or ROM max.
			0x75, 0x10,     //     REPORT_SIZE (16)
			0x95, 0x02,     //     REPORT_COUNT (2)
			0x91, 0x02,     //     OUTPUT (Data,Var,Abs)
			0xC0,              //     END_COLLECTION
			0xC0,                 //     END_COLLECTION

			// Envelope Report Definition
			0x09, 0x5A,    //    Usage Set Envelope Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_ENVREP + 0x10 * TLID),         //    Report ID 2
			0x09, 0x22,         //    Usage Effect Block Index
			0x15, 0x01,         //    Logical Minimum 1
			0x25, 0x28,         //    Logical Maximum 28h (40d)
			0x35, 0x01,         //    Physical Minimum 1
			0x45, 0x28,         //    Physical Maximum 28h (40d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x5B,         //    Usage Attack Level
			0x09, 0x5D,         //    Usage Fade Level
			0x16, 0x00, 0x00,    //    Logical Minimum 0
			0x26, 0x10, 0x27,    //    Logical Maximum 2710h (10000d)
			0x36, 0x00, 0x00,    //    Physical Minimum 0
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x75, 0x10,         //    Report Size 16
			0x95, 0x02,         //    Report Count 2
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x5C,         //    Usage Attack Time
			0x09, 0x5E,         //    Usage Fade Time
			0x66, 0x03, 0x10,    //    Unit 1003h (English Linear, Seconds)
			0x55,0xFD,         //    Unit Exponent FDh (X10^-3 ==> Milisecond)
			0x27, 0xFF, 0x7F, 0x00, 0x00,    //    Logical Maximum FFFFFFFFh (4294967295)
			0x47, 0xFF, 0x7F, 0x00, 0x00,    //    Physical Maximum FFFFFFFFh (4294967295)
			0x75, 0x20,         //    Report Size 20h (32d)
			0x91, 0x02,         //    Output (Variable)
			0x45, 0x00,         //    Physical Maximum 0
			0x66, 0x00, 0x00,    //    Unit 0
			0x55, 0x00,         //    Unit Exponent 0
			0xC0,            //    End Collection
			0x09, 0x5F,    //    Usage Set Condition Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_CONDREP + 0x10 * TLID),    //    Report ID 3
			0x09, 0x22,    //    Usage Effect Block Index
			0x15, 0x01,    //    Logical Minimum 1
			0x25, 0x28,    //    Logical Maximum 28h (40d)
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x28,    //    Physical Maximum 28h (40d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x02,    //    Output (Variable)
			0x09, 0x23,    //    Usage Parameter Block Offset
			0x15, 0x00,    //    Logical Minimum 0
			0x25, 0x03,    //    Logical Maximum 3
			0x35, 0x00,    //    Physical Minimum 0
			0x45, 0x03,    //    Physical Maximum 3
			0x75, 0x04,    //    Report Size 4
			0x95, 0x01,    //    Report Count 1
			0x91, 0x02,    //    Output (Variable)
			0x09, 0x58,    //    Usage Type Specific Block Off...
			0xA1, 0x02,    //    Collection Datalink
			0x0B, 0x01, 0x00, 0x0A, 0x00,    //    Usage Ordinals: Instance 1
			0x0B, 0x02, 0x00, 0x0A, 0x00,    //    Usage Ordinals: Instance 2
			0x75, 0x02,                   //    Report Size 2
			0x95, 0x02,                   //    Report Count 2
			0x91, 0x02,                   //    Output (Variable)
			0xC0,         //    End Collection
			0x16, 0xF0, 0xD8,    //    Logical Minimum D8F0h (-10000d)
			0x26, 0x10, 0x27,    //    Logical Maximum 2710h (10000d)
			0x36, 0xF0, 0xD8,    //    Physical Minimum D8F0h (-10000d)
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x09, 0x60,         //    Usage CP Offset
			0x75, 0x10,         //    Report Size 16
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x36, 0xF0, 0xD8,    //    Physical Minimum D8F0h (-10000d)
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x09, 0x61,         //    Usage Positive Coefficient
			0x09, 0x62,         //    Usage Negative Coefficient
			0x95, 0x02,         //    Report Count 2
			0x91, 0x02,         //    Output (Variable)
			0x16, 0x00, 0x00,    //    Logical Minimum 0
			0x26, 0x10, 0x27,	  //    Logical Maximum 2710h (10000d)
			0x36, 0x00, 0x00,    //    Physical Minimum 0
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x09, 0x63,         //    Usage Positive Saturation
			0x09, 0x64,         //    Usage Negative Saturation
			0x75, 0x10,         //    Report Size 16
			0x95, 0x02,         //    Report Count 2
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x65,         //    Usage Dead Band
			0x16, 0x00, 0x00,    //    Logical Minimum 0
			0x26, 0x10, 0x27,	  //    Logical Maximum 2710h (10000d)
			0x36, 0x00, 0x00,    //    Physical Minimum 0
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0xC0,    //    End Collection
			0x09, 0x6E,    //    Usage Set Periodic Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_PRIDREP + 0x10 * TLID),                   //    Report ID 4
			0x09, 0x22,                   //    Usage Effect Block Index
			0x15, 0x01,                   //    Logical Minimum 1
			0x25, 0x28,                   //    Logical Maximum 28h (40d)
			0x35, 0x01,                   //    Physical Minimum 1
			0x45, 0x28,                   //    Physical Maximum 28h (40d)
			0x75, 0x08,                   //    Report Size 8
			0x95, 0x01,                   //    Report Count 1
			0x91, 0x02,                   //    Output (Variable)
			0x09, 0x70,                   //    Usage Magnitude
			0x16, 0x00, 0x00,              //    Logical Minimum 0
			0x26, 0x10, 0x27,				//    Logical Maximum 2710h (10000d)
			0x36, 0x00, 0x00,              //    Physical Minimum 0
			0x46, 0x10, 0x27,              //    Physical Maximum 2710h (10000d)
			0x75, 0x10,                   //    Report Size 16
			0x95, 0x01,                   //    Report Count 1
			0x91, 0x02,                   //    Output (Variable)
			0x09, 0x6F,                   //    Usage Offset
			0x16, 0xF0, 0xD8,             //    Logical Minimum D8F0h (-10000d)
			0x26, 0x10, 0x27,             //    Logical Maximum D8F0h (-10000d)
			0x36, 0xF0, 0xD8,              //    Physical Minimum D8F0h (-10000d)
			0x46, 0x10, 0x27,              //    Physical Maximum D8F0h (-10000d)
			0x95, 0x01,                   //    Report Count 1
			0x75, 0x10,                   //    Report Size 16
			0x91, 0x02,                   //    Output (Variable)
			0x09, 0x71,                   //    Usage Phase
			0x66, 0x14, 0x00,             //    Unit 14h (Eng Rotation, Degrees)
			0x55, 0xFE,                   //    Unit Exponent FEh (X10^-2)
			0x15, 0x00,                   //    Logical Minimum 0
			0x27, 0x9F, 0x8C, 0x00, 0x00, //    Logical Maximum 8C9Fh (35999d)
			0x35, 0x00,                   //    Physical Minimum 0
			0x47, 0x9F, 0x8C, 0x00, 0x00, //    Physical Maximum 8C9Fh (35999d)
			0x75, 0x10,                   //    Report Size 16
			0x95, 0x01,                   //    Report Count 1
			0x91, 0x02,                   //    Output (Variable)
			0x09, 0x72,                   //    Usage Period
			0x15, 0x00,                   //    Logical Minimum 0
			0x27, 0xFF, 0x7F, 0x00, 0x00, //    Logical Maximum 7FFFh (32K)
			0x35, 0x00,                   //    Physical Minimum 0
			0x47, 0xFF, 0x7F, 0x00, 0x00, //    Physical Maximum 7FFFh (32K)
			0x66, 0x03, 0x10,             //    Unit 1003h (English Linear, Seconds)
			0x55, 0xFD,                   //    Unit Exponent FDh (X10^-3 ==> Milisecond)
			0x75, 0x20,                   //    Report Size 20h (32)
			0x95, 0x01,                   //    Report Count 1
			0x91, 0x02,                   //    Output (Variable)			
			0x66, 0x00, 0x00,              //    Unit 0
			0x55, 0x00,                   //    Unit Exponent 0
			0xC0,    // End Collection
			0x09, 0x73,    //    Usage Set Constant Force Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_CONSTREP + 0x10 * TLID),         //    Report ID 5
			0x09, 0x22,         //    Usage Effect Block Index
			0x15, 0x01,         //    Logical Minimum 1
			0x25, 0x28,         //    Logical Maximum 28h (40d)
			0x35, 0x01,         //    Physical Minimum 1
			0x45, 0x28,         //    Physical Maximum 28h (40d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x70,         //    Usage Magnitude
			0x16, 0xF0, 0xD8,    //    Logical Minimum D8F0h (-10000d)
			0x26, 0x10, 0x27,    //    Logical Maximum 2710h (10000d)
			0x36, 0xF0, 0xD8,    //    Physical Minimum D8F0h (-10000d)
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x75, 0x10,         //    Report Size 10h (16d)
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0xC0,    //    End Collection
			0x09, 0x74,    //    Usage Set Ramp Force Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_RAMPREP + 0x10 * TLID),         //    Report ID 6
			0x09, 0x22,         //    Usage Effect Block Index
			0x15, 0x01,         //    Logical Minimum 1
			0x25, 0x28,         //    Logical Maximum 28h (40d)
			0x35, 0x01,         //    Physical Minimum 1
			0x45, 0x28,         //    Physical Maximum 28h (40d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x75,         //    Usage Ramp Start
			0x09, 0x76,         //    Usage Ramp End
			0x16, 0xF0, 0xD8,    //    Logical Minimum D8F0h (-10000d)
			0x26, 0x10, 0x27,    //    Logical Maximum 2710h (10000d)
			0x36, 0xF0, 0xD8,    //    Physical Minimum D8F0h (-10000d)
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x75, 0x10,         //    Report Size 16
			0x95, 0x02,         //    Report Count 2
			0x91, 0x02,         //    Output (Variable)
			0xC0,    //    End Collection
			0x09, 0x68,    //    Usage Custom Force Data Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_CSTMREP + 0x10 * TLID),         //    Report ID 7
			0x09, 0x22,         //    Usage Effect Block Index
			0x15, 0x01,         //    Logical Minimum 1
			0x25, 0x28,         //    Logical Maximum 28h (40d)
			0x35, 0x01,         //    Physical Minimum 1
			0x45, 0x28,         //    Physical Maximum 28h (40d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x6C,         //    Usage Custom Force Data Offset
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0x10, 0x27,    //    Logical Maximum 2710h (10000d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x75, 0x10,         //    Report Size 10h (16d)
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x69,         //    Usage Custom Force Data
			0x15, 0x81,         //    Logical Minimum 81h (-127d)
			0x25, 0x7F,         //    Logical Maximum 7Fh (127d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x00,    //    Physical Maximum FFh (255d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x0C,         //    Report Count Ch (12d)
			0x92, 0x02, 0x01,    //       Output (Variable, Buffered)
			0xC0,    //    End Collection
			0x09, 0x66,    //    Usage Download Force Sample
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_SMPLREP + 0x10 * TLID),         //    Report ID 8
			0x05, 0x01,         //    Usage Page Generic Desktop
			0x09, 0x30,         //    Usage X
			0x09, 0x31,         //    Usage Y
			0x15, 0x81,         //    Logical Minimum 81h (-127d)
			0x25, 0x7F,         //    Logical Maximum 7Fh (127d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x00,    //    Physical Maximum FFh (255d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x02,         //    Report Count 2
			0x91, 0x02,         //    Output (Variable)
			0xC0,   //    End Collection
			0x05, 0x0F,   //    Usage Page Physical Interface
			0x09, 0x77,   //    Usage Effect Operation Report
			0xA1, 0x02,   //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_EFOPREP + 0x10 * TLID),    //    Report ID Ah (10d)
			0x09, 0x22,    //    Usage Effect Block Index
			0x15, 0x01,    //    Logical Minimum 1
			0x25, 0x28,    //    Logical Maximum 28h (40d)
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x28,    //    Physical Maximum 28h (40d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x02,    //    Output (Variable)
			0x09, 0x78,    //    Usage Effect Operation
			0xA1, 0x02,    //    Collection Datalink
			0x09, 0x79,    //    Usage Op Effect Start
			0x09, 0x7A,    //    Usage Op Effect Start Solo
			0x09, 0x7B,    //    Usage Op Effect Stop
			0x15, 0x01,    //    Logical Minimum 1
			0x25, 0x03,    //    Logical Maximum 3
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x00,    //    Output
			0xC0,         //    End Collection
			0x09, 0x7C,         //    Usage Loop Count
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x00,    //    Logical Maximum FFh (255d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x00,    //    Physical Maximum FFh (255d)
			0x91, 0x02,         //    Output (Variable)
			0xC0,    //    End Collection
			0x09, 0x90,    //    Usage PID Block Free Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_BLKFRREP + 0x10 * TLID),    //    Report ID Bh (11d)
			0x09, 0x22,    //    Usage Effect Block Index
			0x25, 0x28,    //    Logical Maximum 28h (40d)
			0x15, 0x01,    //    Logical Minimum 1
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x28,    //    Physical Maximum 28h (40d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x02,    //    Output (Variable)
			0xC0,    //    End Collection
			0x09, 0x96,    //    Usage PID Device Control
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_CTRLREP + 0x10 * TLID),    //    Report ID Ch (12d)
			0x09, 0x97,    //    Usage DC Enable Actuators
			0x09, 0x98,    //    Usage DC Disable Actuators
			0x09, 0x99,    //    Usage DC Stop All Effects
			0x09, 0x9A,    //    Usage DC Device Reset
			0x09, 0x9B,    //    Usage DC Device Pause
			0x09, 0x9C,    //    Usage DC Device Continue
			0x15, 0x01,    //    Logical Minimum 1
			0x25, 0x06,    //    Logical Maximum 6
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0x91, 0x00,    //    Output
			0xC0,    //    End Collection
			0x09, 0x7D,    //    Usage Device Gain Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_GAINREP + 0x10 * TLID),         //    Report ID Dh (13d)
			0x09, 0x7E,         //    Usage Device Gain
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x00,    //    Logical Maximum FFh (255d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0x10, 0x27,    //    Physical Maximum 2710h (10000d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0xC0,            //    End Collection
			0x09, 0x6B,    //    Usage Set Custom Force Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_SETCREP + 0x10 * TLID),         //    Report ID Eh (14d)
			0x09, 0x22,         //    Usage Effect Block Index
			0x15, 0x01,         //    Logical Minimum 1
			0x25, 0x28,         //    Logical Maximum 28h (40d)
			0x35, 0x01,         //    Physical Minimum 1
			0x45, 0x28,         //    Physical Maximum 28h (40d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x6D,         //    Usage Sample Count
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x00,    //    Logical Maximum FFh (255d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x00,    //    Physical Maximum FFh (255d)
			0x75, 0x08,         //    Report Size 8
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x09, 0x51,         //    Usage Sample Period
			0x66, 0x03, 0x10,    //    Unit 1003h (4099d)
			0x55, 0xFD,         //    Unit Exponent FDh (253d)
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x7F,    //    Logical Maximum 7FFFh (32767d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x7F,    //    Physical Maximum 7FFFh (32767d)
			0x75, 0x10,         //    Report Size 10h (16d)
			0x95, 0x01,         //    Report Count 1
			0x91, 0x02,         //    Output (Variable)
			0x55, 0x00,         //    Unit Exponent 0
			0x66, 0x00, 0x00,    //    Unit 0
			0xC0,    //    End Collection
			0x09, 0xAB,    //    Usage Create New Effect Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_NEWEFREP + 0x10 * TLID),    //    Report ID 1
			0x09, 0x25,    //    Usage Effect Type
			0xA1, 0x02,    //    Collection Datalink
			0x09, HID_USAGE_CONST,    //    Usage ET Constant Force
			0x09, HID_USAGE_RAMP,    //    Usage ET Ramp
			0x09, HID_USAGE_SQUR,    //    Usage ET Square
			0x09, HID_USAGE_SINE,    //    Usage ET Sine
			0x09, HID_USAGE_TRNG,    //    Usage ET Triangle
			0x09, HID_USAGE_STUP,    //    Usage ET Sawtooth Up
			0x09, HID_USAGE_STDN,    //    Usage ET Sawtooth Down
			0x09, HID_USAGE_SPRNG,    //    Usage ET Spring
			0x09, HID_USAGE_DMPR,    //    Usage ET Damper
			0x09, HID_USAGE_INRT,    //    Usage ET Inertia
			0x09, HID_USAGE_FRIC,    //    Usage ET Friction
			0x09, 0x29,    //    Usage ET RESERVED
//			0x09, 0x28,    //    Usage ET Custom Force Data
			0x25, 0x0C,    //    Logical Maximum Ch (12d)
			0x15, 0x01,    //    Logical Minimum 1
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x0C,    //    Physical Maximum Ch (12d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0xB1, 0x00,    //    Feature
			0xC0,    // End Collection
			0x05, 0x01,         //    Usage Page Generic Desktop
			0x09, 0x3B,         //    Usage Reserved
			0x15, 0x00,         //    Logical Minimum 0
			0x26, 0xFF, 0x01,    //    Logical Maximum 1FFh (511d)
			0x35, 0x00,         //    Physical Minimum 0
			0x46, 0xFF, 0x01,    //    Physical Maximum 1FFh (511d)
			0x75, 0x0A,         //    Report Size Ah (10d)
			0x95, 0x01,         //    Report Count 1
			0xB1, 0x02,         //    Feature (Variable)
			0x75, 0x06,         //    Report Size 6
			0xB1, 0x01,         //    Feature (Constant)
			0xC0,    //    End Collection
			0x05, 0x0F,    //    Usage Page Physical Interface
			0x09, 0x89,    //    Usage Block Load Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_BLKLDREP + 0x10 * TLID),    //    Report ID 2
			0x09, 0x22,    //    Usage Effect Block Index
			0x25, 0x28,    //    Logical Maximum 28h (40d)
			0x15, 0x01,    //    Logical Minimum 1
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x28,    //    Physical Maximum 28h (40d)
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0xB1, 0x02,    //    Feature (Variable)
			0x09, 0x8B,    //    Usage Block Load Status
			0xA1, 0x02,    //    Collection Datalink
			0x09, 0x8C,    //    Usage Block Load Success
			0x09, 0x8D,    //    Usage Block Load Full
			0x09, 0x8E,    //    Usage Block Load Error
			0x25, 0x03,    //    Logical Maximum 3
			0x15, 0x01,    //    Logical Minimum 1
			0x35, 0x01,    //    Physical Minimum 1
			0x45, 0x03,    //    Physical Maximum 3
			0x75, 0x08,    //    Report Size 8
			0x95, 0x01,    //    Report Count 1
			0xB1, 0x00,    //    Feature
			0xC0,                   // End Collection
			0x09, 0xAC,                   //    Usage Undefined
			0x15, 0x00,                   //    Logical Minimum 0
			0x27, 0xFF, 0xFF, 0x00, 0x00,    //    Logical Maximum FFFFh (65535d)
			0x35, 0x00,                   //    Physical Minimum 0
			0x47, 0xFF, 0xFF, 0x00, 0x00,    //    Physical Maximum FFFFh (65535d)
			0x75, 0x10,                   //    Report Size 10h (16d)
			0x95, 0x01,                   //    Report Count 1
			0xB1, 0x00,                   //    Feature
			0xC0,    //    End Collection
			0x09, 0x7F,    //    Usage PID Pool Report
			0xA1, 0x02,    //    Collection Datalink
			0x85, }, { static_cast<BYTE>(HID_ID_POOLREP + 0x10 * TLID),                   //    Report ID 3
			0x09, 0x80,                   //    Usage RAM Pool size
			0x75, 0x10,                   //    Report Size 10h (16d)
			0x95, 0x01,                   //    Report Count 1
			0x15, 0x00,                   //    Logical Minimum 0
			0x35, 0x00,                   //    Physical Minimum 0
			0x27, 0xFF, 0xFF, 0x00, 0x00,    //    Logical Maximum FFFFh (65535d)
			0x47, 0xFF, 0xFF, 0x00, 0x00,    //    Physical Maximum FFFFh (65535d)
			0xB1, 0x02,                   //    Feature (Variable)
			0x09, 0x83,                   //    Usage Simultaneous Effects Max
			0x26, 0xFF, 0x00,              //    Logical Maximum FFh (255d)
			0x46, 0xFF, 0x00,              //    Physical Maximum FFh (255d)
			0x75, 0x08,                   //    Report Size 8
			0x95, 0x01,                   //    Report Count 1
			0xB1, 0x02,                   //    Feature (Variable)
			0x09, 0xA9,                   //    Usage Device Managed Pool
			0x09, 0xAA,                   //    Usage Shared Parameter Blocks
			0x75, 0x01,                   //    Report Size 1
			0x95, 0x02,                   //    Report Count 2
			0x15, 0x00,                   //    Logical Minimum 0
			0x25, 0x01,                   //    Logical Maximum 1
			0x35, 0x00,                   //    Physical Minimum 0
			0x45, 0x01,                   //    Physical Maximum 1
			0xB1, 0x02,                   //    Feature (Variable)
			0x75, 0x06,                   //    Report Size 6
			0x95, 0x01,                   //    Report Count 1
			0xB1, 0x03,                   //    Feature (Constant, Variable)
			0xC0,    //    End Collection
			/*********************** Force Feedback section Device 1 [end] ***********************/
	} };

class CvJoyDevice
{
public:
	CvJoyDevice();
	CvJoyDevice(int);
	virtual ~CvJoyDevice();

private:
	VjdStat	status;
	int ButtonNumber, DiscPovNumber, ContPovNumber;
	BOOL X_Exist, Y_Exist, Z_Exist, RX_Exist, RY_Exist, RZ_Exist, SL0_Exist, SL1_Exist;
protected:
	// Get current status of the vJoy device and initialize status variables accordingly
	BOOL GetStatus(int id);
public:
	// Tests if vJoy device exists (Input is ID number)
	BOOL Exists();

	// Tests if axis implemented exists (Input is ID number)
	BOOL AxisExists(UINT Axis);

	// Get the number of buttons
	int GetButtonNumber(void);

	// Get the number of discrete POV buttons
	int GetDiscPovNumber(void);

	// Get the number of Continuous POV buttons
	int GetContPovNumber(void);

protected:
	// ID of this vJoy device
	int Id;
};
