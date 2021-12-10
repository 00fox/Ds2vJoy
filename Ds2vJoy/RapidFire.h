#pragma once
#include "vJoy.h"

class RapidFire
{
public:
	RapidFire();
	~RapidFire();

	WCHAR* KeyString();
	WCHAR* ValueString(int column);
	BOOL LoadDevice(vJoyDevice*);
	BOOL Run(double now);

	unsigned char Enable;
	byte ButtonID;
	byte ButtonID2;
	long Firsttime;
	long Releasetime;
	long Presstime;

private:
	vJoyButton* m_button;
	vJoyButton* m_button2;
	long long m_time;
	long long randPresstime;
	long long randReleasetime;
};

typedef std::vector<RapidFire> RapidFires;
