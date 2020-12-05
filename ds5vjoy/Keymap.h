#pragma once

#define KEYMAP_MAX_KEYS 10
#include "vJoy.h"
#include "Findwindow.h"

class Keymap {
	bool m_keydownflag;
	vJoyButton *m_button;
	void keydown();
	void keyup();
	HWND postmessageTarget;
	void keydownPM();
	void keyupPM();
public:
	Keymap();
	vJoyButtonID ButtonID;
	bool Enable;
	std::vector<BYTE> vk;

	bool usePostmessage;
	Findwindow findWindow;

	bool LoadDevice(vJoyDevice* vj);
	bool Run();
	void GetState();
	WCHAR* StrVal();
	WCHAR* StrKey();
};
typedef std::vector<Keymap> Keymaps;



