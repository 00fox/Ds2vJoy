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

	void				Init(HWND, bool verbose = false);
	BOOL				Open(int DevID = 1, bool verbose = false);
	void				Close();
	BOOL				Active();
	void				ClearState();
	void				UpdateState();
	BOOL				Update();
	vJoyButton*			GetButton(vJoyButtonID);
	vJoyButton*			GetAxis(vJoyAxisMoveID);

private:
	double				distSum(Point p, Point arr[], int n);
	Point				geometricMedian(Point arr[], int n);

	void				loadTriggers(vJoyButtonID id, int hid_axis, long* data, unsigned char axis);
	void				loadAxis(vJoyButtonID id, int hid_axis, long* data, unsigned char axis);
	void				loadAxisInv(vJoyButtonID id, int hid_axis, long* data, unsigned char axis);
	void				loadRing(vJoyAxisMoveID id, int hid_axis, long* data, int hid_axis2, long* data2, unsigned char axis);

	int					m_devID = 0;
	vJoyButton			m_buttons[vJoyButtonID::button_Count];
	vJoyButton			m_axis[vJoyAxisMoveID::axismove_Count];
	JOYSTICK_POSITION_V2 m_iReportDefault;
	JOYSTICK_POSITION_V2 m_iReport;
	byte				Dpad[32] = { 0 };

	bool				firsttime = true;
};
