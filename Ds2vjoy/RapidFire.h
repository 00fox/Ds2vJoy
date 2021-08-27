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

	int Enable;
	vJoyButtonID ButtonID;
	vJoyButtonID ButtonID2;
	int Firsttime;
	int Releasetime;
	int Presstime;

private:
	vJoyButton* m_button;
	vJoyButton* m_button2;
	double m_time;
	int randPresstime;
	int randReleasetime;
};

typedef std::vector<RapidFire> RapidFires;
