#pragma once
#include "Destination.h"

class RapidFire
{
public:
	RapidFire();
	~RapidFire();

	WCHAR*				KeyString();
	WCHAR*				ValueString(int column);
	const WCHAR*		RapidFireButtons();
	BOOL				LoadDevice(Destination*);
	void				RunFirst();
	BOOL				Run(std::chrono::system_clock::time_point now);

	unsigned char		Enable = 0;
	byte				ButtonID = DestButtonID::Destination_None;
	byte				ButtonID2 = DestButtonID::Destination_None;
	int					Firsttime = 75;
	int					Releasetime = 75;
	int					Presstime = 150;

private:
	DestinationButton*	m_button = 0;
	DestinationButton*	m_button2 = 0;
	bool				m_pushed = false;
	bool				m_first = false;

	std::chrono::system_clock::time_point	start = std::chrono::system_clock::now();
	std::chrono::milliseconds				randRelease = std::chrono::milliseconds(0);
	std::chrono::milliseconds				randPress = std::chrono::milliseconds(0);
};

	//String of RapidFire buttons in use, to show in status bar
	static std::wstring				RapidFireButtonsString = L"";
	typedef std::vector<RapidFire>	RapidFires;
