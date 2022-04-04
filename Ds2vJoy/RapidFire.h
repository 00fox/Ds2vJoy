#pragma once
#include "vJoy.h"

class RapidFire
{
public:
	RapidFire();
	~RapidFire();

	WCHAR*				KeyString();
	WCHAR*				ValueString(int column);
	const WCHAR*		RapidFireButtons();
	BOOL				LoadDevice(vJoyDevice*);
	void				RunFirst();
	BOOL				Run(std::chrono::system_clock::time_point now);

	unsigned char		Enable = 0;
	byte				ButtonID = vJoyButtonID::none;
	byte				ButtonID2 = vJoyButtonID::none;
	long				Firsttime = 75;
	long				Releasetime = 75;
	long				Presstime = 150;

private:
	vJoyButton*			m_button = 0;
	vJoyButton*			m_button2 = 0;
	bool				m_pushed = false;
	bool				m_first = false;

	std::chrono::system_clock::time_point	start = std::chrono::system_clock::now();
	std::chrono::milliseconds				randRelease = std::chrono::milliseconds(0);
	std::chrono::milliseconds				randPress = std::chrono::milliseconds(0);
};

	//String of RapidFire buttons in use, to show in status bar
	static std::wstring				RapidFireButtonsString = L"";
	typedef std::vector<RapidFire>	RapidFires;
