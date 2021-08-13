#pragma once
#include "vJoy.h"

class RapidFire
{

public:
	RapidFire();
	~RapidFire();

	BOOL LoadDevice(vJoyDevice*);
	WCHAR* KeyString();
	WCHAR* ValueString();
	BOOL Run(double now);

	bool Enable;
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
