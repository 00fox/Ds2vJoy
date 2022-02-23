#pragma once
#include "Source.h"
#include "vJoy.h"

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

class ViGEm
{
public:
	ViGEm();
	~ViGEm();

	const				WCHAR* ViGEmButtons();
	void				Init(HWND);
	void				InitClient(bool verbose = false);
	void				InitPad(bool verbose = false);
	void				CloseClient(bool verbose = false);
	void				ClosePad(bool verbose = false);
	void				LoadDevice(dsDevice*, vJoyDevice*);
	void				Run();

	void				ViGEmStates();
	int					GetViGEmState();
	BOOL				ViGEmInstall(bool verbose = false);
	BOOL				ViGEmUninstall(bool verbose = false);
	BOOL				ViGEmEnable(bool verbose = false);
	BOOL				ViGEmDisable(bool verbose = false);

	bool				vigem_connected = false;

private:
	int					ViGEmState(bool verbose = false);
	std::wstring		ViGEmError(VIGEM_ERROR err);
	WCHAR*				X360_String(int id);
	WCHAR*				DS4_String(int id);

	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;

	dsButton*			m_ds[24] = { 0 };
	vJoyButton*			m_vj[24] = { 0 };

	PVIGEM_CLIENT		client;
	PVIGEM_TARGET		pad;
	VIGEM_ERROR			err;
	XUSB_REPORT			report_X360;
	DS4_REPORT			report_DS4;
	DS4_DPAD_DIRECTIONS	Dpad;

	int					vgState = -1;
};

	static WCHAR		ViGEmButtonsString[80] = L"";
	extern ViGEm		vg;
