#pragma once
#include "DS5.h"
#include "vJoy.h"


class Mapping {
	DS5Button * m_ds5[4] = { 0 };
	vJoyButton * m_vjoy = 0;
	int m_toggle;
	BYTE m_data;
public:
	Mapping();

	DS5ButtonID  DS5ID[4] = { DS5ButtonID::none };
	bool Enable;
	bool Disbale[4];
	bool Force;
	bool Toggle;
	vJoyButtonID vJoyID;
	const WCHAR * StrDS5();
	const WCHAR * StrvJoy();
	bool LoadDevice(DS5Device*,vJoyDevice*);
	bool Run();
};


typedef std::vector<Mapping> Mappings;
