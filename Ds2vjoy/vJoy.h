#pragma once
#include "vJoyButton.h"

struct Point {
	double x, y;
};

class vJoyDevice
{
public:
	vJoyDevice();
	~vJoyDevice();

	BOOL Init(HWND, bool verbose = false);
	BOOL Open(int DevID = 1, bool verbose = false);
	void Close();
	BOOL Active();
	void ClearState();
	void UpdateState();
	BOOL Update();
	vJoyButton* GetButton(vJoyButtonID);

	void SetFFBCallback(FfbGenCB, PVOID);

private:
	double distSum(Point p, Point arr[], int n);
	Point geometricMedian(Point arr[], int n);

	void loadTriggers(vJoyButtonID id, int hid_axis, LONG* data);
	void loadAxis(vJoyButtonID id, int hid_axis, LONG* val);
	void loadAxisInv(vJoyButtonID id, int hid_axis, LONG* val);

	int m_devID;
	vJoyButton m_buttons[vJoyButtonID::button_Count];
	JOYSTICK_POSITION_V2 m_iReport, m_iReportDefault;

	bool DpadExists;
	BYTE Dpad[32];

	bool firsttime = true;
};

