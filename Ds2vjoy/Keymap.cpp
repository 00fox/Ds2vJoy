#include "stdafx.h"
#include "Keymap.h"

Keymap::Keymap()
	:Enable(0)
	, ButtonID(vJoyButtonID::none)
	, vk()
	, usePostmessage(false)
	, useActivating(false)
	, findWindow()
	, m_button(0)
{
	Findwindow fw;
	findWindow = fw;
}

Keymap::~Keymap()
{
}

struct _virtualkey2str
{
	BYTE vk;
	WCHAR* string;
	bool map;
};

#define KS1(v) { v , L#v , false },
#define KS2(v) { #@v , L"VK_" #v , true },

WCHAR* Keymap::KeyString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒";

	return vJoyButton::String(ButtonID);
}

WCHAR* Keymap::ValueString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";

	WCHAR* head = bufstring;

	for (int i = 0; i < vk.size(); i++)
		head += wsprintfW(head, L"%s ", String(BytetoKeyboardID(vk[i])));

	if (bufstring < head)
		*(--head) = 0;

	return bufstring;
}

static const struct _virtualkey2str keystr[] = {
//KS1(VK_LBUTTON)
//KS1(VK_RBUTTON)
//KS1(VK_MBUTTON)
//KS1(VK_XBUTTON1)
//KS1(VK_XBUTTON2)
KS1(VK_SLEEP)
KS1(VK_NUMLOCK)
KS1(VK_CAPITAL)
KS1(VK_KANA)	//VK_HANGUEL & VK_HANGUL
KS1(VK_IME_ON)
KS1(VK_JUNJA)
KS1(VK_FINAL)
KS1(VK_KANJI)	//VK_HANJA & VK_KANJI
KS1(VK_IME_OFF)
//KS1(VK_SHIFT)
//KS1(VK_CONTROL)
//KS1(VK_MENU)
KS1(VK_LWIN)
KS1(VK_RWIN)
KS1(VK_LSHIFT)
KS1(VK_RSHIFT)
KS1(VK_LCONTROL)
KS1(VK_RCONTROL)
KS1(VK_LMENU)
KS1(VK_RMENU)
KS1(VK_ACCEPT)
KS1(VK_APPS)
KS1(VK_ATTN)
KS1(VK_BACK)
KS1(VK_CANCEL)
KS1(VK_CLEAR)
KS1(VK_CONVERT)
KS1(VK_CRSEL)
KS1(VK_DELETE)
KS1(VK_DOWN)
KS1(VK_END)
KS1(VK_EREOF)
KS1(VK_ESCAPE)
KS1(VK_EXECUTE)
KS1(VK_EXSEL)
KS1(VK_HELP)
KS1(VK_HOME)
KS1(VK_ICO_00)
KS1(VK_ICO_CLEAR)
KS1(VK_ICO_HELP)
KS1(VK_INSERT)
KS1(VK_LEFT)
KS1(VK_MODECHANGE)
KS1(VK_NEXT)
KS1(VK_NONAME)
KS1(VK_NONCONVERT)
KS1(VK_PA1)
KS1(VK_PACKET)
KS1(VK_PAUSE)
KS1(VK_PRINT)
KS1(VK_PRIOR)
KS1(VK_PROCESSKEY)
KS1(VK_RIGHT)
KS1(VK_SCROLL)
KS1(VK_SELECT)
KS1(VK_SNAPSHOT)
KS1(VK_SPACE)
KS1(VK_TAB)
KS1(VK_UP)
KS1(VK_BROWSER_BACK)
KS1(VK_BROWSER_FORWARD)
KS1(VK_BROWSER_REFRESH)
KS1(VK_BROWSER_STOP)
KS1(VK_BROWSER_SEARCH)
KS1(VK_BROWSER_FAVORITES)
KS1(VK_BROWSER_HOME)
KS1(VK_VOLUME_MUTE)
KS1(VK_VOLUME_DOWN)
KS1(VK_VOLUME_UP)
KS1(VK_MEDIA_NEXT_TRACK)
KS1(VK_MEDIA_PREV_TRACK)
KS1(VK_MEDIA_STOP)
KS1(VK_MEDIA_PLAY_PAUSE)
KS1(VK_PLAY)
KS1(VK_LAUNCH_MAIL)
KS1(VK_LAUNCH_MEDIA_SELECT)
KS1(VK_LAUNCH_APP1)
KS1(VK_LAUNCH_APP2)
KS1(VK_F1)
KS1(VK_F2)
KS1(VK_F3)
KS1(VK_F4)
KS1(VK_F5)
KS1(VK_F6)
KS1(VK_F7)
KS1(VK_F8)
KS1(VK_F9)
KS1(VK_F10)
KS1(VK_F11)
KS1(VK_F12)
KS1(VK_F13)
KS1(VK_F14)
KS1(VK_F15)
KS1(VK_F16)
KS1(VK_F17)
KS1(VK_F18)
KS1(VK_F19)
KS1(VK_F20)
KS1(VK_F21)
KS1(VK_F22)
KS1(VK_F23)
KS1(VK_F24)
KS1(VK_OEM_PLUS)
KS1(VK_OEM_COMMA)
KS1(VK_OEM_MINUS)
KS1(VK_OEM_PERIOD)
KS1(VK_OEM_1)
KS1(VK_OEM_2)
KS1(VK_OEM_3)
KS1(VK_OEM_4)
KS1(VK_OEM_5)
KS1(VK_OEM_6)
KS1(VK_OEM_7)
KS1(VK_OEM_8)
KS1(VK_OEM_102)
KS1(VK_OEM_AX)
KS1(VK_OEM_BACKTAB)
KS1(VK_OEM_CLEAR)
KS1(VK_OEM_COPY)
KS1(VK_OEM_CUSEL)
KS1(VK_OEM_ENLW)
KS1(VK_OEM_FINISH)
KS1(VK_OEM_JUMP)
KS1(VK_OEM_PA1)
KS1(VK_OEM_PA2)
KS1(VK_OEM_PA3)
KS1(VK_OEM_RESET)
KS1(VK_OEM_WSCTRL)
KS2(0)
KS2(1)
KS2(2)
KS2(3)
KS2(4)
KS2(5)
KS2(6)
KS2(7)
KS2(8)
KS2(9)
KS2(A)
KS2(B)
KS2(C)
KS2(D)
KS2(E)
KS2(F)
KS2(G)
KS2(H)
KS2(I)
KS2(J)
KS2(K)
KS2(L)
KS2(M)
KS2(N)
KS2(O)
KS2(P)
KS2(Q)
KS2(R)
KS2(S)
KS2(T)
KS2(U)
KS2(V)
KS2(W)
KS2(X)
KS2(Y)
KS2(Z)
KS1(VK_MULTIPLY)
KS1(VK_ADD)
KS1(VK_SEPARATOR)
KS1(VK_SUBTRACT)
KS1(VK_DECIMAL)
KS1(VK_DIVIDE)
KS1(VK_NUMPAD0)
KS1(VK_NUMPAD1)
KS1(VK_NUMPAD2)
KS1(VK_NUMPAD3)
KS1(VK_NUMPAD4)
KS1(VK_NUMPAD5)
KS1(VK_NUMPAD6)
KS1(VK_NUMPAD7)
KS1(VK_NUMPAD8)
KS1(VK_NUMPAD9)
KS1(VK_RETURN)
};

void Keymap::keydown()
{
	postmessageTarget = findWindow.Find();
	SetActiveWindow(postmessageTarget);
	INPUT sendkeys[KEYMAP_MAX_KEYS];
	int count = 0;
	size_t max = vk.size();
	for (; count < max; count++)
	{
		sendkeys[count].type = INPUT_KEYBOARD;
		sendkeys[count].ki.wVk = vk[count];
		sendkeys[count].ki.wScan = (WORD)MapVirtualKey(vk[count], 0);
		sendkeys[count].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		sendkeys[count].ki.time = 0;
		sendkeys[count].ki.dwExtraInfo = 0;
	}
	if (count)
		SendInput(count, sendkeys, sizeof(INPUT));
	m_keydownflag = true;
}

void Keymap::keyup()
{
	INPUT sendkeys[KEYMAP_MAX_KEYS];
	int count = 0;
	for (int n = (int)vk.size() - 1; n >= 0; n--)
	{
		sendkeys[count].type = INPUT_KEYBOARD;
		sendkeys[count].ki.wVk = vk[n];
		sendkeys[count].ki.wScan = (WORD)MapVirtualKey(vk[n], 0);
		sendkeys[count].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
		sendkeys[count].ki.time = 0;
		sendkeys[count].ki.dwExtraInfo = 0;
		count++;
	}
	if (count)
		SendInput(count, sendkeys, sizeof(INPUT));
	m_keydownflag = false;
}

void Keymap::keydownPM()
{
	size_t max = vk.size();
	for (int count = 0; count < max; count++)
	{
		if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYDOWN, vk[count], 0) == 0)
		{
			postmessageTarget = findWindow.Find();
			if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYDOWN, vk[count], 0) == 0)
				break;
		}
	}
	m_keydownflag = true;
}

void Keymap::keyupPM()
{
	for (int n = (int)vk.size() - 1; n >= 0; n--)
	{
		if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYUP, vk[n], 0) == 0)
		{
			postmessageTarget = findWindow.Find();
			if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYUP, vk[n], 0) == 0)
				break;
		}
	}
	m_keydownflag = false;
}

BOOL Keymap::LoadDevice(vJoyDevice* vjoy)
{
	if (Enable != 1)
		return FALSE;

	if (!ButtonID)
		return FALSE;

	m_button = vjoy->GetButton(ButtonID);

	if (m_button == 0)
		return FALSE;

	return TRUE;
}

void Keymap::Run()
{
	if (tape.KeymapPaused)
		return;

	if (m_button == 0)
		return;

	if (m_keydownflag)
	{
		if (!m_button->isPushed())
		{
			if (usePostmessage)
			{
				if (useActivating)
				{
					postmessageTarget = findWindow.Find();
					if (postmessageTarget == NULL)
						return;
					SetForegroundWindow(postmessageTarget);
					SetActiveWindow(postmessageTarget);
					keyup();
				}
				else
					keyupPM();
			}
			else
				keyup();
		}
	}
	else if (m_button->isPushed())
	{
		if (usePostmessage)
		{
			if (useActivating)
			{
				postmessageTarget = findWindow.Find();
				if (postmessageTarget == NULL)
					return;
				SetForegroundWindow(postmessageTarget);
				SetActiveWindow(postmessageTarget);
				keydown();
			}
			else
				keydownPM();
		}
		else
			keydown();
		return;
	}
	return;
}

void Keymap::GetState()
{
	for (int i = 0; i < 1024; i++)
		bufstring[i] = {};

	BYTE state[0x100];
	if (GetKeyboardState(state))
	{
		for (int i = 0; i < 182; i++)
		{
			BYTE j = keystr[i].vk;
			if (state[j] & 0xFF)
			{
				if (GetAsyncKeyState(j) & 0x01)
				{
					vk.push_back(j);
					state[j] = 0;
				}
			}
		}
	}
}

KeyboardID Keymap::BytetoKeyboardID(BYTE id)
{
	switch (id)
	{
	case VK_LBUTTON: return KID_LBUTTON;
	case VK_RBUTTON: return KID_RBUTTON;
	case VK_CANCEL: return KID_CANCEL;
	case VK_MBUTTON: return KID_MBUTTON;
	case VK_XBUTTON1: return KID_XBUTTON1;
	case VK_XBUTTON2: return KID_XBUTTON2;
	case VK_BACK: return KID_BACK;
	case VK_TAB: return KID_TAB;
	case VK_CLEAR: return KID_CLEAR;
	case VK_RETURN: return KID_RETURN;
	case VK_SHIFT: return KID_SHIFT;
	case VK_CONTROL: return KID_CONTROL;
	case VK_MENU: return KID_MENU;
	case VK_PAUSE: return KID_PAUSE;
	case VK_CAPITAL: return KID_CAPITAL;
	case VK_KANA: return KID_HANGUL;
	case VK_IME_ON: return KID_IME_ON;
	case VK_JUNJA: return KID_JUNJA;
	case VK_FINAL: return KID_FINAL;
	case VK_KANJI: return KID_KANJI;
	case VK_IME_OFF: return KID_IME_OFF;
	case VK_ESCAPE: return KID_ESCAPE;
	case VK_CONVERT: return KID_CONVERT;
	case VK_NONCONVERT: return KID_NONCONVERT;
	case VK_ACCEPT: return KID_ACCEPT;
	case VK_MODECHANGE: return KID_MODECHANGE;
	case VK_SPACE: return KID_SPACE;
	case VK_PRIOR: return KID_PRIOR;
	case VK_NEXT: return KID_NEXT;
	case VK_END: return KID_END;
	case VK_HOME: return KID_HOME;
	case VK_LEFT: return KID_LEFT;
	case VK_UP: return KID_UP;
	case VK_RIGHT: return KID_RIGHT;
	case VK_DOWN: return KID_DOWN;
	case VK_SELECT: return KID_SELECT;
	case VK_PRINT: return KID_PRINT;
	case VK_EXECUTE: return KID_EXECUTE;
	case VK_SNAPSHOT: return KID_SNAPSHOT;
	case VK_INSERT: return KID_INSERT;
	case VK_DELETE: return KID_DELETE;
	case VK_HELP: return KID_HELP;
	case VK_0: return KID_0;
	case VK_1: return KID_1;
	case VK_2: return KID_2;
	case VK_3: return KID_3;
	case VK_4: return KID_4;
	case VK_5: return KID_5;
	case VK_6: return KID_6;
	case VK_7: return KID_7;
	case VK_8: return KID_8;
	case VK_9: return KID_9;
	case VK_A: return KID_A;
	case VK_B: return KID_B;
	case VK_C: return KID_C;
	case VK_D: return KID_D;
	case VK_E: return KID_E;
	case VK_F: return KID_F;
	case VK_G: return KID_G;
	case VK_H: return KID_H;
	case VK_I: return KID_I;
	case VK_J: return KID_J;
	case VK_K: return KID_K;
	case VK_L: return KID_L;
	case VK_M: return KID_M;
	case VK_N: return KID_N;
	case VK_O: return KID_O;
	case VK_P: return KID_P;
	case VK_Q: return KID_Q;
	case VK_R: return KID_R;
	case VK_S: return KID_S;
	case VK_T: return KID_T;
	case VK_U: return KID_U;
	case VK_V: return KID_V;
	case VK_W: return KID_W;
	case VK_X: return KID_X;
	case VK_Y: return KID_Y;
	case VK_Z: return KID_Z;
	case VK_LWIN: return KID_LWIN;
	case VK_RWIN: return KID_RWIN;
	case VK_APPS: return KID_APPS;
	case VK_SLEEP: return KID_SLEEP;
	case VK_NUMPAD0: return KID_NUMPAD0;
	case VK_NUMPAD1: return KID_NUMPAD1;
	case VK_NUMPAD2: return KID_NUMPAD2;
	case VK_NUMPAD3: return KID_NUMPAD3;
	case VK_NUMPAD4: return KID_NUMPAD4;
	case VK_NUMPAD5: return KID_NUMPAD5;
	case VK_NUMPAD6: return KID_NUMPAD6;
	case VK_NUMPAD7: return KID_NUMPAD7;
	case VK_NUMPAD8: return KID_NUMPAD8;
	case VK_NUMPAD9: return KID_NUMPAD9;
	case VK_MULTIPLY: return KID_MULTIPLY;
	case VK_ADD: return KID_ADD;
	case VK_SEPARATOR: return KID_SEPARATOR;
	case VK_SUBTRACT: return KID_SUBTRACT;
	case VK_DECIMAL: return KID_DECIMAL;
	case VK_DIVIDE: return KID_DIVIDE;
	case VK_F1: return KID_F1;
	case VK_F2: return KID_F2;
	case VK_F3: return KID_F3;
	case VK_F4: return KID_F4;
	case VK_F5: return KID_F5;
	case VK_F6: return KID_F6;
	case VK_F7: return KID_F7;
	case VK_F8: return KID_F8;
	case VK_F9: return KID_F9;
	case VK_F10: return KID_F10;
	case VK_F11: return KID_F11;
	case VK_F12: return KID_F12;
	case VK_F13: return KID_F13;
	case VK_F14: return KID_F14;
	case VK_F15: return KID_F15;
	case VK_F16: return KID_F16;
	case VK_F17: return KID_F17;
	case VK_F18: return KID_F18;
	case VK_F19: return KID_F19;
	case VK_F20: return KID_F20;
	case VK_F21: return KID_F21;
	case VK_F22: return KID_F22;
	case VK_F23: return KID_F23;
	case VK_F24: return KID_F24;
	case VK_NUMLOCK: return KID_NUMLOCK;
	case VK_SCROLL: return KID_SCROLL;
	case VK_LSHIFT: return KID_LSHIFT;
	case VK_RSHIFT: return KID_RSHIFT;
	case VK_LCONTROL: return KID_LCONTROL;
	case VK_RCONTROL: return KID_RCONTROL;
	case VK_LMENU: return KID_LMENU;
	case VK_RMENU: return KID_RMENU;
	case VK_BROWSER_BACK: return KID_BROWSER_BACK;
	case VK_BROWSER_FORWARD: return KID_BROWSER_FORWARD;
	case VK_BROWSER_REFRESH: return KID_BROWSER_REFRESH;
	case VK_BROWSER_STOP: return KID_BROWSER_STOP;
	case VK_BROWSER_SEARCH: return KID_BROWSER_SEARCH;
	case VK_BROWSER_FAVORITES: return KID_BROWSER_FAVORITES;
	case VK_BROWSER_HOME: return KID_BROWSER_HOME;
	case VK_VOLUME_MUTE: return KID_VOLUME_MUTE;
	case VK_VOLUME_DOWN: return KID_VOLUME_DOWN;
	case VK_VOLUME_UP: return KID_VOLUME_UP;
	case VK_MEDIA_NEXT_TRACK: return KID_MEDIA_NEXT_TRACK;
	case VK_MEDIA_PREV_TRACK: return KID_MEDIA_PREV_TRACK;
	case VK_MEDIA_STOP: return KID_MEDIA_STOP;
	case VK_MEDIA_PLAY_PAUSE: return KID_MEDIA_PLAY_PAUSE;
	case VK_LAUNCH_MAIL: return KID_LAUNCH_MAIL;
	case VK_LAUNCH_MEDIA_SELECT: return KID_LAUNCH_MEDIA_SELECT;
	case VK_LAUNCH_APP1: return KID_LAUNCH_APP1;
	case VK_LAUNCH_APP2: return KID_LAUNCH_APP2;
	case VK_OEM_1: return KID_OEM_1;
	case VK_OEM_PLUS: return KID_OEM_PLUS;
	case VK_OEM_COMMA: return KID_OEM_COMMA;
	case VK_OEM_MINUS: return KID_OEM_MINUS;
	case VK_OEM_PERIOD: return KID_OEM_PERIOD;
	case VK_OEM_2: return KID_OEM_2;
	case VK_OEM_3: return KID_OEM_3;
	case VK_OEM_4: return KID_OEM_4;
	case VK_OEM_5: return KID_OEM_5;
	case VK_OEM_6: return KID_OEM_6;
	case VK_OEM_7: return KID_OEM_7;
	case VK_OEM_8: return KID_OEM_8;
	case VK_OEM_AX: return KID_OEM_AX;
	case VK_OEM_102: return KID_OEM_102;
	case VK_ICO_HELP: return KID_ICO_HELP;
	case VK_ICO_00: return KID_ICO_00;
	case VK_PROCESSKEY: return KID_PROCESSKEY;
	case VK_ICO_CLEAR: return KID_ICO_CLEAR;
	case VK_PACKET: return KID_PACKET;
	case VK_OEM_RESET: return KID_OEM_RESET;
	case VK_OEM_JUMP: return KID_OEM_JUMP;
	case VK_OEM_PA1: return KID_OEM_PA1;
	case VK_OEM_PA2: return KID_OEM_PA2;
	case VK_OEM_PA3: return KID_OEM_PA3;
	case VK_OEM_WSCTRL: return KID_OEM_WSCTRL;
	case VK_OEM_CUSEL: return KID_OEM_CUSEL;
	case VK_OEM_FINISH: return KID_OEM_FINISH;
	case VK_OEM_COPY: return KID_OEM_COPY;
	case VK_OEM_ENLW: return KID_OEM_ENLW;
	case VK_OEM_BACKTAB: return KID_OEM_BACKTAB;
	case VK_ATTN: return KID_ATTN;
	case VK_CRSEL: return KID_CRSEL;
	case VK_EXSEL: return KID_EXSEL;
	case VK_EREOF: return KID_EREOF;
	case VK_PLAY: return KID_PLAY;
	case VK_ZOOM: return KID_ZOOM;
	case VK_NONAME: return KID_NONAME;
	case VK_PA1: return KID_PA1;
	case VK_OEM_CLEAR: return KID_OEM_CLEAR;
	default: return none;
	}
}

BYTE Keymap::KeyboardIDtoByte(KeyboardID id)
{
	switch (id)
	{
	case KID_LBUTTON: return VK_LBUTTON;
	case KID_RBUTTON: return VK_RBUTTON;
	case KID_CANCEL: return VK_CANCEL;
	case KID_MBUTTON: return VK_MBUTTON;
	case KID_XBUTTON1: return VK_XBUTTON1;
	case KID_XBUTTON2: return VK_XBUTTON2;
	case KID_BACK: return VK_BACK;
	case KID_TAB: return VK_TAB;
	case KID_CLEAR: return VK_CLEAR;
	case KID_RETURN: return VK_RETURN;
	case KID_SHIFT: return VK_SHIFT;
	case KID_CONTROL: return VK_CONTROL;
	case KID_MENU: return VK_MENU;
	case KID_PAUSE: return VK_PAUSE;
	case KID_CAPITAL: return VK_CAPITAL;
	case KID_HANGUL: return VK_KANA;
	case KID_IME_ON: return VK_IME_ON;
	case KID_JUNJA: return VK_JUNJA;
	case KID_FINAL: return VK_FINAL;
	case KID_KANJI: return VK_KANJI;
	case KID_IME_OFF: return VK_IME_OFF;
	case KID_ESCAPE: return VK_ESCAPE;
	case KID_CONVERT: return VK_CONVERT;
	case KID_NONCONVERT: return VK_NONCONVERT;
	case KID_ACCEPT: return VK_ACCEPT;
	case KID_MODECHANGE: return VK_MODECHANGE;
	case KID_SPACE: return VK_SPACE;
	case KID_PRIOR: return VK_PRIOR;
	case KID_NEXT: return VK_NEXT;
	case KID_END: return VK_END;
	case KID_HOME: return VK_HOME;
	case KID_LEFT: return VK_LEFT;
	case KID_UP: return VK_UP;
	case KID_RIGHT: return VK_RIGHT;
	case KID_DOWN: return VK_DOWN;
	case KID_SELECT: return VK_SELECT;
	case KID_PRINT: return VK_PRINT;
	case KID_EXECUTE: return VK_EXECUTE;
	case KID_SNAPSHOT: return VK_SNAPSHOT;
	case KID_INSERT: return VK_INSERT;
	case KID_DELETE: return VK_DELETE;
	case KID_HELP: return VK_HELP;
	case KID_0: return VK_0;
	case KID_1: return VK_1;
	case KID_2: return VK_2;
	case KID_3: return VK_3;
	case KID_4: return VK_4;
	case KID_5: return VK_5;
	case KID_6: return VK_6;
	case KID_7: return VK_7;
	case KID_8: return VK_8;
	case KID_9: return VK_9;
	case KID_A: return VK_A;
	case KID_B: return VK_B;
	case KID_C: return VK_C;
	case KID_D: return VK_D;
	case KID_E: return VK_E;
	case KID_F: return VK_F;
	case KID_G: return VK_G;
	case KID_H: return VK_H;
	case KID_I: return VK_I;
	case KID_J: return VK_J;
	case KID_K: return VK_K;
	case KID_L: return VK_L;
	case KID_M: return VK_M;
	case KID_N: return VK_N;
	case KID_O: return VK_O;
	case KID_P: return VK_P;
	case KID_Q: return VK_Q;
	case KID_R: return VK_R;
	case KID_S: return VK_S;
	case KID_T: return VK_T;
	case KID_U: return VK_U;
	case KID_V: return VK_V;
	case KID_W: return VK_W;
	case KID_X: return VK_X;
	case KID_Y: return VK_Y;
	case KID_Z: return VK_Z;
	case KID_LWIN: return VK_LWIN;
	case KID_RWIN: return VK_RWIN;
	case KID_APPS: return VK_APPS;
	case KID_SLEEP: return VK_SLEEP;
	case KID_NUMPAD0: return VK_NUMPAD0;
	case KID_NUMPAD1: return VK_NUMPAD1;
	case KID_NUMPAD2: return VK_NUMPAD2;
	case KID_NUMPAD3: return VK_NUMPAD3;
	case KID_NUMPAD4: return VK_NUMPAD4;
	case KID_NUMPAD5: return VK_NUMPAD5;
	case KID_NUMPAD6: return VK_NUMPAD6;
	case KID_NUMPAD7: return VK_NUMPAD7;
	case KID_NUMPAD8: return VK_NUMPAD8;
	case KID_NUMPAD9: return VK_NUMPAD9;
	case KID_MULTIPLY: return VK_MULTIPLY;
	case KID_ADD: return VK_ADD;
	case KID_SEPARATOR: return VK_SEPARATOR;
	case KID_SUBTRACT: return VK_SUBTRACT;
	case KID_DECIMAL: return VK_DECIMAL;
	case KID_DIVIDE: return VK_DIVIDE;
	case KID_F1: return VK_F1;
	case KID_F2: return VK_F2;
	case KID_F3: return VK_F3;
	case KID_F4: return VK_F4;
	case KID_F5: return VK_F5;
	case KID_F6: return VK_F6;
	case KID_F7: return VK_F7;
	case KID_F8: return VK_F8;
	case KID_F9: return VK_F9;
	case KID_F10: return VK_F10;
	case KID_F11: return VK_F11;
	case KID_F12: return VK_F12;
	case KID_F13: return VK_F13;
	case KID_F14: return VK_F14;
	case KID_F15: return VK_F15;
	case KID_F16: return VK_F16;
	case KID_F17: return VK_F17;
	case KID_F18: return VK_F18;
	case KID_F19: return VK_F19;
	case KID_F20: return VK_F20;
	case KID_F21: return VK_F21;
	case KID_F22: return VK_F22;
	case KID_F23: return VK_F23;
	case KID_F24: return VK_F24;
	case KID_NUMLOCK: return VK_NUMLOCK;
	case KID_SCROLL: return VK_SCROLL;
	case KID_LSHIFT: return VK_LSHIFT;
	case KID_RSHIFT: return VK_RSHIFT;
	case KID_LCONTROL: return VK_LCONTROL;
	case KID_RCONTROL: return VK_RCONTROL;
	case KID_LMENU: return VK_LMENU;
	case KID_RMENU: return VK_RMENU;
	case KID_BROWSER_BACK: return VK_BROWSER_BACK;
	case KID_BROWSER_FORWARD: return VK_BROWSER_FORWARD;
	case KID_BROWSER_REFRESH: return VK_BROWSER_REFRESH;
	case KID_BROWSER_STOP: return VK_BROWSER_STOP;
	case KID_BROWSER_SEARCH: return VK_BROWSER_SEARCH;
	case KID_BROWSER_FAVORITES: return VK_BROWSER_FAVORITES;
	case KID_BROWSER_HOME: return VK_BROWSER_HOME;
	case KID_VOLUME_MUTE: return VK_VOLUME_MUTE;
	case KID_VOLUME_DOWN: return VK_VOLUME_DOWN;
	case KID_VOLUME_UP: return VK_VOLUME_UP;
	case KID_MEDIA_NEXT_TRACK: return VK_MEDIA_NEXT_TRACK;
	case KID_MEDIA_PREV_TRACK: return VK_MEDIA_PREV_TRACK;
	case KID_MEDIA_STOP: return VK_MEDIA_STOP;
	case KID_MEDIA_PLAY_PAUSE: return VK_MEDIA_PLAY_PAUSE;
	case KID_LAUNCH_MAIL: return VK_LAUNCH_MAIL;
	case KID_LAUNCH_MEDIA_SELECT: return VK_LAUNCH_MEDIA_SELECT;
	case KID_LAUNCH_APP1: return VK_LAUNCH_APP1;
	case KID_LAUNCH_APP2: return VK_LAUNCH_APP2;
	case KID_OEM_1: return VK_OEM_1;
	case KID_OEM_PLUS: return VK_OEM_PLUS;
	case KID_OEM_COMMA: return VK_OEM_COMMA;
	case KID_OEM_MINUS: return VK_OEM_MINUS;
	case KID_OEM_PERIOD: return VK_OEM_PERIOD;
	case KID_OEM_2: return VK_OEM_2;
	case KID_OEM_3: return VK_OEM_3;
	case KID_OEM_4: return VK_OEM_4;
	case KID_OEM_5: return VK_OEM_5;
	case KID_OEM_6: return VK_OEM_6;
	case KID_OEM_7: return VK_OEM_7;
	case KID_OEM_8: return VK_OEM_8;
	case KID_OEM_AX: return VK_OEM_AX;
	case KID_OEM_102: return VK_OEM_102;
	case KID_ICO_HELP: return VK_ICO_HELP;
	case KID_ICO_00: return VK_ICO_00;
	case KID_PROCESSKEY: return VK_PROCESSKEY;
	case KID_ICO_CLEAR: return VK_ICO_CLEAR;
	case KID_PACKET: return VK_PACKET;
	case KID_OEM_RESET: return VK_OEM_RESET;
	case KID_OEM_JUMP: return VK_OEM_JUMP;
	case KID_OEM_PA1: return VK_OEM_PA1;
	case KID_OEM_PA2: return VK_OEM_PA2;
	case KID_OEM_PA3: return VK_OEM_PA3;
	case KID_OEM_WSCTRL: return VK_OEM_WSCTRL;
	case KID_OEM_CUSEL: return VK_OEM_CUSEL;
	case KID_OEM_FINISH: return VK_OEM_FINISH;
	case KID_OEM_COPY: return VK_OEM_COPY;
	case KID_OEM_ENLW: return VK_OEM_ENLW;
	case KID_OEM_BACKTAB: return VK_OEM_BACKTAB;
	case KID_ATTN: return VK_ATTN;
	case KID_CRSEL: return VK_CRSEL;
	case KID_EXSEL: return VK_EXSEL;
	case KID_EREOF: return VK_EREOF;
	case KID_PLAY: return VK_PLAY;
	case KID_ZOOM: return VK_ZOOM;
	case KID_NONAME: return VK_NONAME;
	case KID_PA1: return VK_PA1;
	case KID_OEM_CLEAR: return VK_OEM_CLEAR;
	default: return 0x00;
	}
}

WCHAR* Keymap::String(KeyboardID id)
{
	switch (id)
	{
	case none: return L"";
	case KID_LBUTTON: return L"LBUTTON";
	case KID_RBUTTON: return L"RBUTTON";
	case KID_CANCEL: return L"CANCEL";
	case KID_MBUTTON: return L"MBUTTON";
	case KID_XBUTTON1: return L"XBUTTON1";
	case KID_XBUTTON2: return L"XBUTTON2";
	case KID_BACK: return L"BACK";
	case KID_TAB: return L"TAB";
	case KID_CLEAR: return L"CLEAR";
	case KID_RETURN: return L"RETURN";
	case KID_SHIFT: return L"SHIFT";
	case KID_CONTROL: return L"CONTROL";
	case KID_MENU: return L"MENU";
	case KID_PAUSE: return L"PAUSE";
	case KID_CAPITAL: return L"CAPITAL";
	case KID_HANGUL: return L"KANA";
	case KID_IME_ON: return L"IME_ON";
	case KID_JUNJA: return L"JUNJA";
	case KID_FINAL: return L"FINAL";
	case KID_KANJI: return L"KANJI";
	case KID_IME_OFF: return L"IME_OFF";
	case KID_ESCAPE: return L"ESCAPE";
	case KID_CONVERT: return L"CONVERT";
	case KID_NONCONVERT: return L"NONCONVERT";
	case KID_ACCEPT: return L"ACCEPT";
	case KID_MODECHANGE: return L"MODECHANGE";
	case KID_SPACE: return L"SPACE";
	case KID_PRIOR: return L"PRIOR";
	case KID_NEXT: return L"NEXT";
	case KID_END: return L"END";
	case KID_HOME: return L"HOME";
	case KID_LEFT: return L"LEFT";
	case KID_UP: return L"UP";
	case KID_RIGHT: return L"RIGHT";
	case KID_DOWN: return L"DOWN";
	case KID_SELECT: return L"SELECT";
	case KID_PRINT: return L"PRINT";
	case KID_EXECUTE: return L"EXECUTE";
	case KID_SNAPSHOT: return L"SNAPSHOT";
	case KID_INSERT: return L"INSERT";
	case KID_DELETE: return L"DELETE";
	case KID_HELP: return L"HELP";
	case KID_0: return L"0";
	case KID_1: return L"1";
	case KID_2: return L"2";
	case KID_3: return L"3";
	case KID_4: return L"4";
	case KID_5: return L"5";
	case KID_6: return L"6";
	case KID_7: return L"7";
	case KID_8: return L"8";
	case KID_9: return L"9";
	case KID_A: return L"A";
	case KID_B: return L"B";
	case KID_C: return L"C";
	case KID_D: return L"D";
	case KID_E: return L"E";
	case KID_F: return L"F";
	case KID_G: return L"G";
	case KID_H: return L"H";
	case KID_I: return L"I";
	case KID_J: return L"J";
	case KID_K: return L"K";
	case KID_L: return L"L";
	case KID_M: return L"M";
	case KID_N: return L"N";
	case KID_O: return L"O";
	case KID_P: return L"P";
	case KID_Q: return L"Q";
	case KID_R: return L"R";
	case KID_S: return L"S";
	case KID_T: return L"T";
	case KID_U: return L"U";
	case KID_V: return L"V";
	case KID_W: return L"W";
	case KID_X: return L"X";
	case KID_Y: return L"Y";
	case KID_Z: return L"Z";
	case KID_LWIN: return L"LWIN";
	case KID_RWIN: return L"RWIN";
	case KID_APPS: return L"APPS";
	case KID_SLEEP: return L"SLEEP";
	case KID_NUMPAD0: return L"NUMPAD0";
	case KID_NUMPAD1: return L"NUMPAD1";
	case KID_NUMPAD2: return L"NUMPAD2";
	case KID_NUMPAD3: return L"NUMPAD3";
	case KID_NUMPAD4: return L"NUMPAD4";
	case KID_NUMPAD5: return L"NUMPAD5";
	case KID_NUMPAD6: return L"NUMPAD6";
	case KID_NUMPAD7: return L"NUMPAD7";
	case KID_NUMPAD8: return L"NUMPAD8";
	case KID_NUMPAD9: return L"NUMPAD9";
	case KID_MULTIPLY: return L"MULTIPLY";
	case KID_ADD: return L"ADD";
	case KID_SEPARATOR: return L"SEPARATOR";
	case KID_SUBTRACT: return L"SUBTRACT";
	case KID_DECIMAL: return L"DECIMAL";
	case KID_DIVIDE: return L"DIVIDE";
	case KID_F1: return L"F1";
	case KID_F2: return L"F2";
	case KID_F3: return L"F3";
	case KID_F4: return L"F4";
	case KID_F5: return L"F5";
	case KID_F6: return L"F6";
	case KID_F7: return L"F7";
	case KID_F8: return L"F8";
	case KID_F9: return L"F9";
	case KID_F10: return L"F10";
	case KID_F11: return L"F11";
	case KID_F12: return L"F12";
	case KID_F13: return L"F13";
	case KID_F14: return L"F14";
	case KID_F15: return L"F15";
	case KID_F16: return L"F16";
	case KID_F17: return L"F17";
	case KID_F18: return L"F18";
	case KID_F19: return L"F19";
	case KID_F20: return L"F20";
	case KID_F21: return L"F21";
	case KID_F22: return L"F22";
	case KID_F23: return L"F23";
	case KID_F24: return L"F24";
	case KID_NUMLOCK: return L"NUMLOCK";
	case KID_SCROLL: return L"SCROLL";
	case KID_LSHIFT: return L"LSHIFT";
	case KID_RSHIFT: return L"RSHIFT";
	case KID_LCONTROL: return L"LCONTROL";
	case KID_RCONTROL: return L"RCONTROL";
	case KID_LMENU: return L"LMENU";
	case KID_RMENU: return L"RMENU";
	case KID_BROWSER_BACK: return L"BROWSER_BACK";
	case KID_BROWSER_FORWARD: return L"BROWSER_FORWARD";
	case KID_BROWSER_REFRESH: return L"BROWSER_REFRESH";
	case KID_BROWSER_STOP: return L"BROWSER_STOP";
	case KID_BROWSER_SEARCH: return L"BROWSER_SEARCH";
	case KID_BROWSER_FAVORITES: return L"BROWSER_FAVORITES";
	case KID_BROWSER_HOME: return L"BROWSER_HOME";
	case KID_VOLUME_MUTE: return L"VOLUME_MUTE";
	case KID_VOLUME_DOWN: return L"VOLUME_DOWN";
	case KID_VOLUME_UP: return L"VOLUME_UP";
	case KID_MEDIA_NEXT_TRACK: return L"MEDIA_NEXT_TRACK";
	case KID_MEDIA_PREV_TRACK: return L"MEDIA_PREV_TRACK";
	case KID_MEDIA_STOP: return L"MEDIA_STOP";
	case KID_MEDIA_PLAY_PAUSE: return L"MEDIA_PLAY_PAUSE";
	case KID_LAUNCH_MAIL: return L"LAUNCH_MAIL";
	case KID_LAUNCH_MEDIA_SELECT: return L"LAUNCH_MEDIA_SELECT";
	case KID_LAUNCH_APP1: return L"LAUNCH_APP1";
	case KID_LAUNCH_APP2: return L"LAUNCH_APP2";
	case KID_OEM_1: return L"OEM_1";
	case KID_OEM_PLUS: return L"OEM_PLUS";
	case KID_OEM_COMMA: return L"OEM_COMMA";
	case KID_OEM_MINUS: return L"OEM_MINUS";
	case KID_OEM_PERIOD: return L"OEM_PERIOD";
	case KID_OEM_2: return L"OEM_2";
	case KID_OEM_3: return L"OEM_3";
	case KID_OEM_4: return L"OEM_4";
	case KID_OEM_5: return L"OEM_5";
	case KID_OEM_6: return L"OEM_6";
	case KID_OEM_7: return L"OEM_7";
	case KID_OEM_8: return L"OEM_8";
	case KID_OEM_AX: return L"OEM_AX";
	case KID_OEM_102: return L"OEM_102";
	case KID_ICO_HELP: return L"ICO_HELP";
	case KID_ICO_00: return L"ICO_00";
	case KID_PROCESSKEY: return L"PROCESSKEY";
	case KID_ICO_CLEAR: return L"ICO_CLEAR";
	case KID_PACKET: return L"PACKET";
	case KID_OEM_RESET: return L"OEM_RESET";
	case KID_OEM_JUMP: return L"OEM_JUMP";
	case KID_OEM_PA1: return L"OEM_PA1";
	case KID_OEM_PA2: return L"OEM_PA2";
	case KID_OEM_PA3: return L"OEM_PA3";
	case KID_OEM_WSCTRL: return L"OEM_WSCTRL";
	case KID_OEM_CUSEL: return L"OEM_CUSEL";
	case KID_OEM_FINISH: return L"OEM_FINISH";
	case KID_OEM_COPY: return L"OEM_COPY";
	case KID_OEM_ENLW: return L"OEM_ENLW";
	case KID_OEM_BACKTAB: return L"OEM_BACKTAB";
	case KID_ATTN: return L"ATTN";
	case KID_CRSEL: return L"CRSEL";
	case KID_EXSEL: return L"EXSEL";
	case KID_EREOF: return L"EREOF";
	case KID_PLAY: return L"PLAY";
	case KID_ZOOM: return L"ZOOM";
	case KID_NONAME: return L"NONAME";
	case KID_PA1: return L"PA1";
	case KID_OEM_CLEAR: return L"OEM_CLEAR";
	default: return L"???";
	}
}
