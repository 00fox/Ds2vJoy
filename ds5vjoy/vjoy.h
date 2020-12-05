#pragma once
#include "vJoyButton.h"


class vJoyDevice
{
	int m_devID;
	JOYSTICK_POSITION_V2 m_iReport, m_iReportDefault;

	vJoyButton m_buttons[vJoyButtonID::button_Count];
	void loadAxis(vJoyButtonID id, int hid_axis, LONG *val);

public:

	vJoyDevice();
	bool Init(HWND);
	bool Active();
	bool Open(int DevID=1);
	bool Update();
	bool ClearState();
	vJoyButton* GetButton(vJoyButtonID);
	void Close();
	void SetFFBCallback(FfbGenCB,PVOID);
	~vJoyDevice();
};

