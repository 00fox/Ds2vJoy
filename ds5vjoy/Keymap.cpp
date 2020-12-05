#include "stdafx.h"
#include "Keymap.h"

struct _virtualkey2str
{
	BYTE vk;
	WCHAR * string;
	bool map;
};
#define KS1(v) { v , L#v , false },
#define KS2(v) { #@v , L"VK_" #v , true },
static const struct _virtualkey2str keystr[] = {
KS1(VK_LBUTTON)
KS1(VK_RBUTTON)
KS1(VK_CANCEL)
KS1(VK_MBUTTON)
KS1(VK_XBUTTON1)
KS1(VK_XBUTTON2)
KS1(VK_BACK)
KS1(VK_TAB)
KS1(VK_CLEAR)
KS1(VK_RETURN)
KS1(VK_PAUSE)
KS1(VK_CAPITAL)
KS1(VK_KANA)
KS1(VK_KANJI)
KS1(VK_ESCAPE)
KS1(VK_CONVERT)
KS1(VK_NONCONVERT)
KS1(VK_ACCEPT)
KS1(VK_MODECHANGE)
KS1(VK_SPACE)
KS1(VK_PRIOR)
KS1(VK_NEXT)
KS1(VK_END)
KS1(VK_HOME)
KS1(VK_LEFT)
KS1(VK_UP)
KS1(VK_RIGHT)
KS1(VK_DOWN)
KS1(VK_SELECT)
KS1(VK_PRINT)
KS1(VK_EXECUTE)
KS1(VK_SNAPSHOT)
KS1(VK_INSERT)
KS1(VK_DELETE)
KS1(VK_HELP)
KS1(VK_LWIN)
KS1(VK_RWIN)
KS1(VK_APPS)
KS1(VK_SLEEP)
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
KS1(VK_MULTIPLY)
KS1(VK_ADD)
KS1(VK_SEPARATOR)
KS1(VK_SUBTRACT)
KS1(VK_DECIMAL)
KS1(VK_DIVIDE)
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
KS1(VK_NUMLOCK)
KS1(VK_SCROLL)
KS1(VK_LSHIFT)
KS1(VK_RSHIFT)
KS1(VK_LCONTROL)
KS1(VK_RCONTROL)
KS1(VK_LMENU)
KS1(VK_RMENU)
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
KS1(VK_LAUNCH_MAIL)
KS1(VK_LAUNCH_MEDIA_SELECT)
KS1(VK_LAUNCH_APP1)
KS1(VK_LAUNCH_APP2)
KS1(VK_OEM_1)
KS1(VK_OEM_PLUS)
KS1(VK_OEM_COMMA)
KS1(VK_OEM_MINUS)
KS1(VK_OEM_PERIOD)
KS1(VK_OEM_2)
KS1(VK_OEM_3)
KS1(VK_OEM_4)
KS1(VK_OEM_5)
KS1(VK_OEM_6)
KS1(VK_OEM_7)
KS1(VK_OEM_8)
KS1(VK_OEM_AX)
KS1(VK_OEM_102)
KS1(VK_ICO_HELP)
KS1(VK_ICO_00)
KS1(VK_PROCESSKEY)
KS1(VK_ICO_CLEAR)
KS1(VK_PACKET)
KS1(VK_OEM_RESET)
KS1(VK_OEM_JUMP)
KS1(VK_OEM_PA1)
KS1(VK_OEM_PA2)
KS1(VK_OEM_PA3)
KS1(VK_OEM_WSCTRL)
KS1(VK_OEM_CUSEL)
KS1(VK_OEM_FINISH)
KS1(VK_OEM_COPY)
KS1(VK_OEM_ENLW)
KS1(VK_OEM_BACKTAB)
KS1(VK_CRSEL)
KS1(VK_EXSEL)
KS1(VK_EREOF)
KS1(VK_PLAY)
KS1(VK_NONAME)
KS1(VK_PA1)
KS1(VK_OEM_CLEAR)
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
};



void Keymap::keydown()
{
	INPUT sendkeys[KEYMAP_MAX_KEYS];
	size_t count = 0;
	size_t max = vk.size();
	for (; count < max; count++) {
		sendkeys[count].type = INPUT_KEYBOARD;
		sendkeys[count].ki.wVk = vk[count];
		sendkeys[count].ki.wScan = (WORD)MapVirtualKey(vk[count], 0);
		sendkeys[count].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		sendkeys[count].ki.time = 0;
		sendkeys[count].ki.dwExtraInfo = 0;
	}
	if (count) {
		SendInput(count, sendkeys, sizeof(INPUT));
	}
	m_keydownflag = true;
}

void Keymap::keyup()
{
	INPUT sendkeys[KEYMAP_MAX_KEYS];
	int count = 0;
	for (int n = (int)vk.size() - 1; n >= 0; n--) {
		sendkeys[count].type = INPUT_KEYBOARD;
		sendkeys[count].ki.wVk = vk[n];
		sendkeys[count].ki.wScan = (WORD)MapVirtualKey(vk[n], 0);
		sendkeys[count].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
		sendkeys[count].ki.time = 0;
		sendkeys[count].ki.dwExtraInfo = 0;
		count++;
	}
	if (count) {
		SendInput(count, sendkeys, sizeof(INPUT));
	}
	m_keydownflag = false;
}



void Keymap::keydownPM()
{
	size_t max = vk.size();
	for (size_t count = 0; count < max; count++) {
		if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYDOWN, vk[count], 0) == 0) {
			postmessageTarget = findWindow.Find();
			if (postmessageTarget==NULL || PostMessage(postmessageTarget, WM_KEYDOWN, vk[count], 0) == 0) {
				break;
			}
		}
	}
	m_keydownflag = true;
}

void Keymap::keyupPM()
{
	for (int n = (int)vk.size() - 1; n >= 0; n--) {
		if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYUP, vk[n], 0) == 0) {
			postmessageTarget = findWindow.Find();
			if (postmessageTarget == NULL || PostMessage(postmessageTarget, WM_KEYUP, vk[n], 0) == 0) {
				break;
			}
		}
	}
	m_keydownflag = false;
}

Keymap::Keymap()
	:m_button(0)
{
}

bool Keymap::LoadDevice(vJoyDevice *vjoy)
{
	if (!ButtonID || !Enable)
		return false;
	m_button = vjoy->GetButton(ButtonID);
	if (m_button == 0)
		return false;
	return true;
}

bool Keymap::Run()
{
	if (m_button == 0)
		return false;

	if (m_keydownflag) {
		if (!m_button->isPushed()) {
			if (usePostmessage) {
				keyupPM();
			}
			else {
				keyup();
			}
		}
	}
	else if (m_button->isPushed()) {
		if (usePostmessage) {
			keydownPM();
		}
		else {
			keydown();
		}
		return true;
	}
	return false;
}

void Keymap::GetState()
{
	vk.clear();
	BYTE state[0x100];
	GetKeyboardState(state);
	int count = 0;
	for (int i = 0; i < sizeof(keystr) / sizeof(keystr[0]); i++) {
		if (state[keystr[i].vk] & 0x80) {
			vk.push_back(keystr[i].vk);
			state[keystr[i].vk] = 0;
			if (vk.size() >= KEYMAP_MAX_KEYS)
				break;
		}
	}
}

WCHAR * Keymap::StrKey()
{
	return vJoyButton::String(ButtonID);
}

WCHAR * Keymap::StrVal()
{
	static WCHAR buf[1024];
	buf[0] = 0;
	WCHAR *head = buf;
	size_t max = vk.size();
	bool state[0x100];
	memset(state, 0, sizeof(state));
	for(size_t i = 0; i < max; i++) {
		state[vk[i]] = true;
	}

	static const HKL layout = GetKeyboardLayout(0);
	for (int i = 0; i < sizeof(keystr) / sizeof(keystr[0]); i++) {
		if (state[keystr[i].vk] ) {
			UINT x = MapVirtualKeyEx(keystr[i].vk, 2, layout) & 0xFF;
			if (!keystr[i].map && x>0x20 && x < 0x7e) {
				WCHAR buf[2] = { 0,0 };
				buf[0] = x;
				head += wsprintfW(head, L"%s(%s)+", keystr[i].string, buf);
			}
			else {
				head += wsprintfW(head, L"%s+", keystr[i].string);
			}
		}
	}
	if (buf < head) {
		*(--head) = 0;
	}
	return buf;
}

