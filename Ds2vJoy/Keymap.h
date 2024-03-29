﻿#pragma once
#include "Destination.h"
#include "Findwindow.h"

#define KEYMAP_MAX_KEYS	64
#define VK_0	0x30
#define VK_1	0x31
#define VK_2	0x32
#define VK_3	0x33
#define VK_4	0x34
#define VK_5	0x35
#define VK_6	0x36
#define VK_7	0x37
#define VK_8	0x38
#define VK_9	0x39
#define VK_A	0x41
#define VK_B	0x42
#define VK_C	0x43
#define VK_D	0x44
#define VK_E	0x45
#define VK_F	0x46
#define VK_G	0x47
#define VK_H	0x48
#define VK_I	0x49
#define VK_J	0x4A
#define VK_K	0x4B
#define VK_L	0x4C
#define VK_M	0x4D
#define VK_N	0x4E
#define VK_O	0x4F
#define VK_P	0x50
#define VK_Q	0x51
#define VK_R	0x52
#define VK_S	0x53
#define VK_T	0x54
#define VK_U	0x55
#define VK_V	0x56
#define VK_W	0x57
#define VK_X	0x58
#define VK_Y	0x59
#define VK_Z	0x5A

class Keymap
{
public:
	enum KeyboardID : byte
	{
		KeyboardID_None = 0,
		KID_LBUTTON,
		KID_RBUTTON,
		KID_CANCEL = 3,
		KID_MBUTTON,
		KID_XBUTTON1,
		KID_XBUTTON2,
		KID_BACK = 7,
		KID_TAB = 8,
		KID_CLEAR = 9,
		KID_RETURN = 10,
		KID_SHIFT = 11,
		KID_CONTROL,
		KID_MENU,
		KID_PAUSE = 14,
		KID_CAPITAL = 15,
		KID_HANGUL,
		KID_IME_ON,
		KID_JUNJA,
		KID_FINAL,
		KID_KANJI,
		KID_IME_OFF,
		KID_ESCAPE = 22,
		KID_CONVERT,
		KID_NONCONVERT,
		KID_ACCEPT,
		KID_MODECHANGE,
		KID_SPACE = 27,
		KID_PRIOR,
		KID_NEXT,
		KID_END,
		KID_HOME,
		KID_LEFT = 32,
		KID_UP,
		KID_RIGHT,
		KID_DOWN,
		KID_SELECT,
		KID_PRINT,
		KID_EXECUTE,
		KID_SNAPSHOT,
		KID_INSERT = 40,
		KID_DELETE = 41,
		KID_HELP,
		KID_0 = 43,
		KID_1,
		KID_2,
		KID_3,
		KID_4,
		KID_5,
		KID_6,
		KID_7,
		KID_8,
		KID_9,
		KID_A = 53,
		KID_B,
		KID_C,
		KID_D,
		KID_E,
		KID_F,
		KID_G,
		KID_H,
		KID_I,
		KID_J,
		KID_K,
		KID_L,
		KID_M,
		KID_N,
		KID_O,
		KID_P,
		KID_Q,
		KID_R,
		KID_S,
		KID_T,
		KID_U,
		KID_V,
		KID_W,
		KID_X,
		KID_Y,
		KID_Z,
		KID_LWIN = 79,
		KID_RWIN,
		KID_APPS,
		KID_SLEEP,
		KID_NUMPAD0 = 83,
		KID_NUMPAD1,
		KID_NUMPAD2,
		KID_NUMPAD3,
		KID_NUMPAD4,
		KID_NUMPAD5,
		KID_NUMPAD6,
		KID_NUMPAD7,
		KID_NUMPAD8,
		KID_NUMPAD9,
		KID_MULTIPLY = 93,
		KID_ADD,
		KID_SEPARATOR,
		KID_SUBTRACT,
		KID_DECIMAL,
		KID_DIVIDE,
		KID_F1 = 99,
		KID_F2,
		KID_F3,
		KID_F4,
		KID_F5,
		KID_F6,
		KID_F7,
		KID_F8,
		KID_F9,
		KID_F10,
		KID_F11,
		KID_F12,
		KID_F13,
		KID_F14,
		KID_F15,
		KID_F16,
		KID_F17,
		KID_F18,
		KID_F19,
		KID_F20,
		KID_F21,
		KID_F22,
		KID_F23,
		KID_F24,
		KID_NUMLOCK = 123,
		KID_SCROLL,
		KID_LSHIFT = 125,
		KID_RSHIFT,
		KID_LCONTROL,
		KID_RCONTROL,
		KID_LMENU,
		KID_RMENU,
		KID_BROWSER_BACK = 131,
		KID_BROWSER_FORWARD,
		KID_BROWSER_REFRESH,
		KID_BROWSER_STOP,
		KID_BROWSER_SEARCH,
		KID_BROWSER_FAVORITES,
		KID_BROWSER_HOME,
		KID_VOLUME_MUTE = 138,
		KID_VOLUME_DOWN,
		KID_VOLUME_UP,
		KID_MEDIA_NEXT_TRACK = 141,
		KID_MEDIA_PREV_TRACK,
		KID_MEDIA_STOP,
		KID_MEDIA_PLAY_PAUSE,
		KID_LAUNCH_MAIL = 145,
		KID_LAUNCH_MEDIA_SELECT,
		KID_LAUNCH_APP1,
		KID_LAUNCH_APP2,
		KID_OEM_1 = 149,
		KID_OEM_PLUS,
		KID_OEM_COMMA,
		KID_OEM_MINUS,
		KID_OEM_PERIOD,
		KID_OEM_2,
		KID_OEM_3,
		KID_OEM_4,
		KID_OEM_5,
		KID_OEM_6,
		KID_OEM_7,
		KID_OEM_8,
		KID_OEM_AX,
		KID_OEM_102,
		KID_ICO_HELP,
		KID_ICO_00,
		KID_PROCESSKEY,
		KID_ICO_CLEAR,
		KID_PACKET,
		KID_OEM_RESET,
		KID_OEM_JUMP,
		KID_OEM_PA1,
		KID_OEM_PA2,
		KID_OEM_PA3,
		KID_OEM_WSCTRL,
		KID_OEM_CUSEL,
		KID_OEM_FINISH,
		KID_OEM_COPY,
		KID_OEM_ENLW,
		KID_OEM_BACKTAB,
		KID_ATTN,
		KID_CRSEL,
		KID_EXSEL,
		KID_EREOF,
		KID_PLAY,
		KID_ZOOM,
		KID_NONAME,
		KID_PA1,
		KID_OEM_CLEAR,
		KeyboardID_Count
	};

	Keymap();
	~Keymap();

	WCHAR*				KeyString();
	WCHAR*				ValueString(int column);
	//| Tag   | Description
	//|:----- |:------------------------------------------------------------------------------
	//| Empty | Nothing is checked
	//| P     | \'Send to' is checked
	//| A     | \'By Postmessage / activation window' is checked
	//
	//| Tags  | In practice
	//|:----- |:------------------------------------------------------------------------------
	//| Empty | The keys will be sent to your actual focus
	//| P     | It will use Postmessage to send keys to specified process
	//| PA    | It will activate window of the specified process before
	//|  A    | Act like if nothing were checked, the keys will be sent to your actual focus
	const WCHAR*		KeymapButtons();
	BOOL				LoadDevice(Destination*);
	void				GetState();
	void				RunFirst();
	void				Run();
	KeyboardID			BytetoKeyboardID(byte id);
	BYTE				KeyboardIDtoByte(KeyboardID id);
	const WCHAR*		String(KeyboardID id);

	unsigned char		Enable = 0;
	byte				ButtonID = DestButtonID::Destination_None;
	std::vector<BYTE>	vk = { };
	unsigned char		WndRestore = 0;
	unsigned char		WndMaximize = 0;
	unsigned char		WndShow = 0;
	bool				NaturalTyping = false;
	bool				usePostmessage = false;
	bool				useActivating = false;
	bool				ExtendedKey = false;
	bool				Scancode = false;
	WCHAR				bufstring[1024];

	Findwindow			findWindow;

private:

	void				keydown();
	void				keydown_NaturalTyping();
	void				keyup();
	void				keydownPM();
	void				keyupPM();

	HWND				postmessageTarget = NULL;
	DestinationButton*	m_button = NULL;
	bool				m_keydownflag = false;
	bool				alt_down = false;
	bool				lalt_down = false;
	bool				ralt_down = false;
	bool				ctrl_down = false;
	bool				lctrl_down = false;
	bool				rctrl_down = false;
	bool				shift_down = false;
	bool				lshift_down = false;
	bool				rshift_down = false;
	bool				isShiftedKey = false;
	char				TreeInaWay = 0;

	std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
};

	//String of Keymap buttons in use, to show in status bar
	static std::wstring			KeymapButtonsString = L"";
	typedef std::vector<Keymap>	Keymaps;
	typedef Keymap::KeyboardID	KeyboardID;
