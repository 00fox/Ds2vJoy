#pragma once
#include "Destination.h"

#define DS4_BUTTON_WEST				3
#define DS4_BUTTON_NORTH			4
#define DS4_BUTTON_EAST				5
#define DS4_BUTTON_SOUTH			6
#define DS4_BUTTON_LEFT_TR			7
#define DS4_BUTTON_RIGHT_TR			8
#define DS4_THUMB_LEFT_X			9
#define DS4_THUMB_LEFT_Y			10
#define DS4_THUMB_RIGHT_X			11
#define DS4_THUMB_RIGHT_Y			12

#define XUSB_GAMEPAD_LEFT_TRIGGER	9
#define XUSB_GAMEPAD_RIGHT_TRIGGER	10
#define XUSB_GAMEPAD_LEFT_X			11
#define XUSB_GAMEPAD_LEFT_Y			12
#define XUSB_GAMEPAD_RIGHT_X		13
#define XUSB_GAMEPAD_RIGHT_Y		14

class XOutput
{
public:
	XOutput();
	~XOutput();

	const				WCHAR* XOutputButtons();
	void				Init();
	void				InitClient(bool verbose = false);
	void				InitPad(bool verbose = false);
	void				CloseClient(bool verbose = false);
	void				ClosePad(bool verbose = false);
	void				LoadDevice(Destination*);
	void				Run();

	void				XOutputStates();
	char				GetXOutputState();
	BOOL				XOutputInstall(bool verbose = false);
	BOOL				XOutputUninstall(bool verbose = false);
	BOOL				XOutputEnable(bool verbose = false);
	BOOL				XOutputDisable(bool verbose = false);

	void				vJoyStates();
	char				GetvJoyState();
	BOOL				vJoyInstall(bool verbose = false);
	BOOL				vJoyUninstall(bool verbose = false);
	BOOL				vJoyEnable(bool verbose = false);
	BOOL				vJoyDisable(bool verbose = false);

	bool				xoutput_connected = false;

private:
	char				XOutputState(bool verbose = false);
	char				vJoyState(bool verbose = false);
	std::wstring		XOutputError(VIGEM_ERROR err);
	WCHAR*				X360_String(int id);
	WCHAR*				DS4_String(int id);

	HWND				m_hDlg = NULL;

	DestinationButton*	m_src[24] = { 0 };

	PVIGEM_CLIENT		client;
	PVIGEM_TARGET		pad;
	VIGEM_ERROR			err;
	XUSB_REPORT			report_X360;
	DS4_REPORT			report_DS4;
	DS4_DPAD_DIRECTIONS	Dpad;

	int					xiState = -1;
	int					vjState = -1;
};

	static WCHAR		XOutputButtonsString[80] = L"";
	extern XOutput		xi;
