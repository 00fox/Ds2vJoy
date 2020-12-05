#pragma once
#include "vJoy.h"

class RapidFire
{
	vJoyButton * m_button;
	vJoyButton * m_button2;
	double m_time;
public:
	bool Enable;
	vJoyButtonID ButtonID;
	vJoyButtonID ButtonID2;
	DWORD Firsttime;
	DWORD Releasetime;
	DWORD Presstime;
	bool LoadDevice(vJoyDevice*);
	WCHAR * strKey();
	WCHAR * strVal();
	bool Run(double now);
	RapidFire();
	~RapidFire();
};


typedef std::map<vJoyButtonID, RapidFire> RapidFires;

