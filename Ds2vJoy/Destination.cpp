#include "stdafx.h"
#include "Destination.h"

Destination::Destination()
{
	//Initialization
	memset(&m_iReport, 0, sizeof(m_iReport));
	for (int i = 0; i < 32; i++)
		Dpad[i] = 0;

	for (int i = 0; i < 32; i++)
	{
		unsigned int bitmask = 1 << i;
		GetButton((DestButtonID)(DestButtonID::Button1 + i))->setButton(&m_iReport.lButtons, bitmask);
	}
	for (int i = 0; i < 32; i++)
	{
		unsigned int bitmask = 1 << i;
		GetButton((DestButtonID)(DestButtonID::Button1 + i + 32))->setButton(&m_iReport.lButtonsEx1, bitmask);
	}
	for (int i = 0; i < 32; i++)
	{
		unsigned int bitmask = 1 << i;
		GetButton((DestButtonID)(DestButtonID::Button1 + i + 64))->setButton(&m_iReport.lButtonsEx2, bitmask);
	}
	for (int i = 0; i < 32; i++)
	{
		unsigned int bitmask = 1 << i;
		GetButton((DestButtonID)(DestButtonID::Button1 + i + 96))->setButton(&m_iReport.lButtonsEx3, bitmask);
	}
	for (int i = 0; i < 16; i++)
	{
		unsigned int bitmask = 1 << i;
		GetButton((DestButtonID)(DestButtonID::WORK1 + i))->setButton(&m_iReport.wThrottle, bitmask);
	}

	GetButton(DestButtonID::DPAD1_LEFT)->setDPad(&Dpad[0]);
	GetButton(DestButtonID::DPAD1_UP_LEFT)->setDPad(&Dpad[1]);
	GetButton(DestButtonID::DPAD1_UP)->setDPad(&Dpad[2]);
	GetButton(DestButtonID::DPAD1_UP_RIGHT)->setDPad(&Dpad[3]);
	GetButton(DestButtonID::DPAD1_RIGHT)->setDPad(&Dpad[4]);
	GetButton(DestButtonID::DPAD1_DOWN_RIGHT)->setDPad(&Dpad[5]);
	GetButton(DestButtonID::DPAD1_DOWN)->setDPad(&Dpad[6]);
	GetButton(DestButtonID::DPAD1_DOWN_LEFT)->setDPad(&Dpad[7]);

	GetButton(DestButtonID::DPAD2_LEFT)->setDPad(&Dpad[8]);
	GetButton(DestButtonID::DPAD2_UP_LEFT)->setDPad(&Dpad[9]);
	GetButton(DestButtonID::DPAD2_UP)->setDPad(&Dpad[10]);
	GetButton(DestButtonID::DPAD2_UP_RIGHT)->setDPad(&Dpad[11]);
	GetButton(DestButtonID::DPAD2_RIGHT)->setDPad(&Dpad[12]);
	GetButton(DestButtonID::DPAD2_DOWN_RIGHT)->setDPad(&Dpad[13]);
	GetButton(DestButtonID::DPAD2_DOWN)->setDPad(&Dpad[14]);
	GetButton(DestButtonID::DPAD2_DOWN_LEFT)->setDPad(&Dpad[15]);

	GetButton(DestButtonID::DPAD3_LEFT)->setDPad(&Dpad[16]);
	GetButton(DestButtonID::DPAD3_UP_LEFT)->setDPad(&Dpad[17]);
	GetButton(DestButtonID::DPAD3_UP)->setDPad(&Dpad[18]);
	GetButton(DestButtonID::DPAD3_UP_RIGHT)->setDPad(&Dpad[19]);
	GetButton(DestButtonID::DPAD3_RIGHT)->setDPad(&Dpad[20]);
	GetButton(DestButtonID::DPAD3_DOWN_RIGHT)->setDPad(&Dpad[21]);
	GetButton(DestButtonID::DPAD3_DOWN)->setDPad(&Dpad[22]);
	GetButton(DestButtonID::DPAD3_DOWN_LEFT)->setDPad(&Dpad[23]);

	GetButton(DestButtonID::DPAD4_LEFT)->setDPad(&Dpad[24]);
	GetButton(DestButtonID::DPAD4_UP_LEFT)->setDPad(&Dpad[25]);
	GetButton(DestButtonID::DPAD4_UP)->setDPad(&Dpad[26]);
	GetButton(DestButtonID::DPAD4_UP_RIGHT)->setDPad(&Dpad[27]);
	GetButton(DestButtonID::DPAD4_RIGHT)->setDPad(&Dpad[28]);
	GetButton(DestButtonID::DPAD4_DOWN_RIGHT)->setDPad(&Dpad[29]);
	GetButton(DestButtonID::DPAD4_DOWN)->setDPad(&Dpad[30]);
	GetButton(DestButtonID::DPAD4_DOWN_LEFT)->setDPad(&Dpad[31]);

	loadAxis(DestinationButton::X, &m_iReport.wAxisX, DestAxisID::Axis_X);
	loadAxis(DestinationButton::Y, &m_iReport.wAxisY, DestAxisID::Axis_Y);
	loadAxis(DestinationButton::Z, &m_iReport.wAxisZ, DestAxisID::Axis_Z);
	loadAxis(DestinationButton::RX, &m_iReport.wAxisXRot, DestAxisID::Axis_RX);
	loadAxis(DestinationButton::RY, &m_iReport.wAxisYRot, DestAxisID::Axis_RY);
	loadAxis(DestinationButton::RZ, &m_iReport.wAxisZRot, DestAxisID::Axis_RZ);
	loadAxis(DestinationButton::SL0, &m_iReport.wSlider, DestAxisID::Axis_SL0);
	loadAxis(DestinationButton::SL1, &m_iReport.wDial, DestAxisID::Axis_SL1);

	loadTrigger(DestinationButton::XTR, &m_iReport.wAxisX, DestAxisID::Axis_X);
	loadTrigger(DestinationButton::YTR, &m_iReport.wAxisY, DestAxisID::Axis_Y);
	loadTrigger(DestinationButton::ZTR, &m_iReport.wAxisZ, DestAxisID::Axis_Z);
	loadTrigger(DestinationButton::RXTR, &m_iReport.wAxisXRot, DestAxisID::Axis_RX);
	loadTrigger(DestinationButton::RYTR, &m_iReport.wAxisYRot, DestAxisID::Axis_RY);
	loadTrigger(DestinationButton::RZTR, &m_iReport.wAxisZRot, DestAxisID::Axis_RZ);
	loadTrigger(DestinationButton::SL0TR, &m_iReport.wSlider, DestAxisID::Axis_SL0);
	loadTrigger(DestinationButton::SL1TR, &m_iReport.wDial, DestAxisID::Axis_SL1);

	loadAxisToTrigger(DestinationButton::XAXTOTR, &m_iReport.wAxisX, DestAxisID::Axis_X);
	loadAxisToTrigger(DestinationButton::YAXTOTR, &m_iReport.wAxisY, DestAxisID::Axis_Y);
	loadAxisToTrigger(DestinationButton::ZAXTOTR, &m_iReport.wAxisZ, DestAxisID::Axis_Z);
	loadAxisToTrigger(DestinationButton::RXAXTOTR, &m_iReport.wAxisXRot, DestAxisID::Axis_RX);
	loadAxisToTrigger(DestinationButton::RYAXTOTR, &m_iReport.wAxisYRot, DestAxisID::Axis_RY);
	loadAxisToTrigger(DestinationButton::RZAXTOTR, &m_iReport.wAxisZRot, DestAxisID::Axis_RZ);
	loadAxisToTrigger(DestinationButton::SL0AXTOTR, &m_iReport.wSlider, DestAxisID::Axis_SL0);
	loadAxisToTrigger(DestinationButton::SL1AXTOTR, &m_iReport.wDial, DestAxisID::Axis_SL1);

	loadAxisInv(DestinationButton::XINV, &m_iReport.wAxisX, DestAxisID::Axis_X);
	loadAxisInv(DestinationButton::YINV, &m_iReport.wAxisY, DestAxisID::Axis_Y);
	loadAxisInv(DestinationButton::ZINV, &m_iReport.wAxisZ, DestAxisID::Axis_Z);
	loadAxisInv(DestinationButton::RXINV, &m_iReport.wAxisXRot, DestAxisID::Axis_RX);
	loadAxisInv(DestinationButton::RYINV, &m_iReport.wAxisYRot, DestAxisID::Axis_RY);
	loadAxisInv(DestinationButton::RZINV, &m_iReport.wAxisZRot, DestAxisID::Axis_RZ);
	loadAxisInv(DestinationButton::SL0INV, &m_iReport.wSlider, DestAxisID::Axis_SL0);
	loadAxisInv(DestinationButton::SL1INV, &m_iReport.wDial, DestAxisID::Axis_SL1);

	loadTriggerInv(DestinationButton::XTRINV, &m_iReport.wAxisX, DestAxisID::Axis_X);
	loadTriggerInv(DestinationButton::YTRINV, &m_iReport.wAxisY, DestAxisID::Axis_Y);
	loadTriggerInv(DestinationButton::ZTRINV, &m_iReport.wAxisZ, DestAxisID::Axis_Z);
	loadTriggerInv(DestinationButton::RXTRINV, &m_iReport.wAxisXRot, DestAxisID::Axis_RX);
	loadTriggerInv(DestinationButton::RYTRINV, &m_iReport.wAxisYRot, DestAxisID::Axis_RY);
	loadTriggerInv(DestinationButton::RZTRINV, &m_iReport.wAxisZRot, DestAxisID::Axis_RZ);
	loadTriggerInv(DestinationButton::SL0TRINV, &m_iReport.wSlider, DestAxisID::Axis_SL0);
	loadTriggerInv(DestinationButton::SL1TRINV, &m_iReport.wDial, DestAxisID::Axis_SL1);

	loadAxisToTriggerInv(DestinationButton::XAXTOTRINV, &m_iReport.wAxisX, DestAxisID::Axis_X);
	loadAxisToTriggerInv(DestinationButton::YAXTOTRINV, &m_iReport.wAxisY, DestAxisID::Axis_Y);
	loadAxisToTriggerInv(DestinationButton::ZAXTOTRINV, &m_iReport.wAxisZ, DestAxisID::Axis_Z);
	loadAxisToTriggerInv(DestinationButton::RXAXTOTRINV, &m_iReport.wAxisXRot, DestAxisID::Axis_RX);
	loadAxisToTriggerInv(DestinationButton::RYAXTOTRINV, &m_iReport.wAxisYRot, DestAxisID::Axis_RY);
	loadAxisToTriggerInv(DestinationButton::RZAXTOTRINV, &m_iReport.wAxisZRot, DestAxisID::Axis_RZ);
	loadAxisToTriggerInv(DestinationButton::SL0AXTOTRINV, &m_iReport.wSlider, DestAxisID::Axis_SL0);
	loadAxisToTriggerInv(DestinationButton::SL1AXTOTRINV, &m_iReport.wDial, DestAxisID::Axis_SL1);

	loadAxis(DestinationButton::WORK1AX, &m_iReport.wAxisVX, DestAxisID::Axis_WORK1);
	loadAxis(DestinationButton::WORK2AX, &m_iReport.wAxisVY, DestAxisID::Axis_WORK2);
	loadAxis(DestinationButton::WORK3AX, &m_iReport.wAxisVZ, DestAxisID::Axis_WORK3);
	loadAxis(DestinationButton::WORK4AX, &m_iReport.wAxisVBRX, DestAxisID::Axis_WORK4);
	loadAxis(DestinationButton::WORK5AX, &m_iReport.wAxisVBRY, DestAxisID::Axis_WORK5);
	loadAxis(DestinationButton::WORK6AX, &m_iReport.wAxisVBRZ, DestAxisID::Axis_WORK6);
	loadAxis(DestinationButton::WORK7AX, &m_iReport.wRudder, DestAxisID::Axis_WORK7);
	loadAxis(DestinationButton::WORK8AX, &m_iReport.wAileron, DestAxisID::Axis_WORK8);

	loadTrigger(DestinationButton::WORK1TR, &m_iReport.wAxisVX, DestAxisID::Axis_WORK1);
	loadTrigger(DestinationButton::WORK2TR, &m_iReport.wAxisVY, DestAxisID::Axis_WORK2);
	loadTrigger(DestinationButton::WORK3TR, &m_iReport.wAxisVZ, DestAxisID::Axis_WORK3);
	loadTrigger(DestinationButton::WORK4TR, &m_iReport.wAxisVBRX, DestAxisID::Axis_WORK4);
	loadTrigger(DestinationButton::WORK5TR, &m_iReport.wAxisVBRY, DestAxisID::Axis_WORK5);
	loadTrigger(DestinationButton::WORK6TR, &m_iReport.wAxisVBRZ, DestAxisID::Axis_WORK6);
	loadTrigger(DestinationButton::WORK7TR, &m_iReport.wRudder, DestAxisID::Axis_WORK7);
	loadTrigger(DestinationButton::WORK8TR, &m_iReport.wAileron, DestAxisID::Axis_WORK8);

	loadRing(DestAxisMoveID::XY_CW, &m_iReport.wAxisX, &m_iReport.wAxisY, DestAxisID::Axis_XY);
	loadRing(DestAxisMoveID::XY_CN, &m_iReport.wAxisX, &m_iReport.wAxisY, DestAxisID::Axis_XY);
	loadRing(DestAxisMoveID::ZRZ_CW, &m_iReport.wAxisZ, &m_iReport.wAxisZRot, DestAxisID::Axis_ZRZ);
	loadRing(DestAxisMoveID::ZRZ_CN, &m_iReport.wAxisZ, &m_iReport.wAxisZRot, DestAxisID::Axis_ZRZ);
	loadRing(DestAxisMoveID::RXRY_CW, &m_iReport.wAxisXRot, &m_iReport.wAxisYRot, DestAxisID::Axis_RXRY);
	loadRing(DestAxisMoveID::RXRY_CN, &m_iReport.wAxisXRot, &m_iReport.wAxisYRot, DestAxisID::Axis_RXRY);
	loadRing(DestAxisMoveID::SL0SL1_CW, &m_iReport.wSlider, &m_iReport.wDial, DestAxisID::Axis_SL0SL1);
	loadRing(DestAxisMoveID::SL0SL1_CN, &m_iReport.wSlider, &m_iReport.wDial, DestAxisID::Axis_SL0SL1);
	for (int i = DestAxisMoveID::XY_CENTER; i <= DestAxisMoveID::XY_L_DL_CN; i++)
		loadRing((DestAxisMoveID)i, &m_iReport.wAxisX, &m_iReport.wAxisY, DestAxisID::Axis_XY);
	for (int i = DestAxisMoveID::ZRZ_CENTER; i <= DestAxisMoveID::ZRZ_L_DL_CN; i++)
		loadRing((DestAxisMoveID)i, &m_iReport.wAxisZ, &m_iReport.wAxisZRot, DestAxisID::Axis_ZRZ);

	loadEffet(DestAfterEffectID::X_INV, &m_iReport.wAxisX, NULL);
	loadEffet(DestAfterEffectID::Y_INV, &m_iReport.wAxisY, NULL);
	loadEffet(DestAfterEffectID::Z_INV, &m_iReport.wAxisZ, NULL);
	loadEffet(DestAfterEffectID::RZ_INV, &m_iReport.wAxisZRot, NULL);
	loadEffet(DestAfterEffectID::RX_INV, &m_iReport.wAxisXRot, NULL);
	loadEffet(DestAfterEffectID::RY_INV, &m_iReport.wAxisYRot, NULL);
	loadEffet(DestAfterEffectID::X_PLUS, &m_iReport.wAxisX, NULL);
	loadEffet(DestAfterEffectID::Y_PLUS, &m_iReport.wAxisY, NULL);
	loadEffet(DestAfterEffectID::Z_PLUS, &m_iReport.wAxisZ, NULL);
	loadEffet(DestAfterEffectID::RZ_PLUS, &m_iReport.wAxisZRot, NULL);
	loadEffet(DestAfterEffectID::RX_PLUS, &m_iReport.wAxisXRot, NULL);
	loadEffet(DestAfterEffectID::RY_PLUS, &m_iReport.wAxisYRot, NULL);
	loadEffet(DestAfterEffectID::X_MINUS, &m_iReport.wAxisX, NULL);
	loadEffet(DestAfterEffectID::Y_MINUS, &m_iReport.wAxisY, NULL);
	loadEffet(DestAfterEffectID::Z_MINUS, &m_iReport.wAxisZ, NULL);
	loadEffet(DestAfterEffectID::RZ_MINUS, &m_iReport.wAxisZRot, NULL);
	loadEffet(DestAfterEffectID::RX_MINUS, &m_iReport.wAxisXRot, NULL);
	loadEffet(DestAfterEffectID::RY_MINUS, &m_iReport.wAxisYRot, NULL);
	for (int i = DestAfterEffectID::X_DIM; i <= DestAfterEffectID::X_DIM_P2; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisX, NULL);
	for (int i = DestAfterEffectID::Y_DIM; i <= DestAfterEffectID::Y_DIM_P2; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisY, NULL);
	for (int i = DestAfterEffectID::Z_DIM; i <= DestAfterEffectID::Z_DIM_P2; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisZ, NULL);
	for (int i = DestAfterEffectID::RZ_DIM; i <= DestAfterEffectID::RZ_DIM_P2; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisZRot, NULL);
	for (int i = DestAfterEffectID::RX_DIM_P1; i <= DestAfterEffectID::RX_DIM_P2; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisXRot, NULL);
	for (int i = DestAfterEffectID::RY_DIM_P1; i <= DestAfterEffectID::RY_DIM_P2; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisYRot, NULL);
	for (int i = DestAfterEffectID::XY_DEL_12_1; i <= DestAfterEffectID::XY_DEL_12_12; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisX, &m_iReport.wAxisY);
	for (int i = DestAfterEffectID::ZRZ_DEL_12_1; i <= DestAfterEffectID::ZRZ_DEL_12_12; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisZ, &m_iReport.wAxisZRot);
	for (int i = DestAfterEffectID::XY_DEL_16_1; i <= DestAfterEffectID::XY_DEL_16_16; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisX, &m_iReport.wAxisY);
	for (int i = DestAfterEffectID::ZRZ_DEL_16_1; i <= DestAfterEffectID::ZRZ_DEL_16_16; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisZ, &m_iReport.wAxisZRot);
	for (int i = DestAfterEffectID::RX_DEL_3_1; i <= DestAfterEffectID::RX_DEL_4_4; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisXRot, NULL);
	for (int i = DestAfterEffectID::RY_DEL_3_1; i <= DestAfterEffectID::RY_DEL_4_4; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisYRot, NULL);
	for (int i = DestAfterEffectID::XY_DISTORT_U___; i <= DestAfterEffectID::XY_DISTORT__DDDDD; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisX, &m_iReport.wAxisY);
	for (int i = DestAfterEffectID::ZRZ_DISTORT_U___; i <= DestAfterEffectID::ZRZ_DISTORT__DDDDD; i++)
		loadEffet((DestAfterEffectID)i, &m_iReport.wAxisZ, &m_iReport.wAxisZRot);

	m_iReport.bHats = -1;
	m_iReport.bHatsEx1 = -1;
	m_iReport.bHatsEx2 = -1;
	m_iReport.bHatsEx3 = -1;

	GetButton(DestinationButton::DPAD1_LEFT)->Release();
	GetButton(DestinationButton::DPAD1_UP_LEFT)->Release();
	GetButton(DestinationButton::DPAD1_UP)->Release();
	GetButton(DestinationButton::DPAD1_UP_RIGHT)->Release();
	GetButton(DestinationButton::DPAD1_RIGHT)->Release();
	GetButton(DestinationButton::DPAD1_DOWN_RIGHT)->Release();
	GetButton(DestinationButton::DPAD1_DOWN)->Release();
	GetButton(DestinationButton::DPAD1_DOWN_LEFT)->Release();
	GetButton(DestinationButton::DPAD2_LEFT)->Release();
	GetButton(DestinationButton::DPAD2_UP_LEFT)->Release();
	GetButton(DestinationButton::DPAD2_UP)->Release();
	GetButton(DestinationButton::DPAD2_UP_RIGHT)->Release();
	GetButton(DestinationButton::DPAD2_RIGHT)->Release();
	GetButton(DestinationButton::DPAD2_DOWN_RIGHT)->Release();
	GetButton(DestinationButton::DPAD2_DOWN)->Release();
	GetButton(DestinationButton::DPAD2_DOWN_LEFT)->Release();
	GetButton(DestinationButton::DPAD3_LEFT)->Release();
	GetButton(DestinationButton::DPAD3_UP_LEFT)->Release();
	GetButton(DestinationButton::DPAD3_UP)->Release();
	GetButton(DestinationButton::DPAD3_UP_RIGHT)->Release();
	GetButton(DestinationButton::DPAD3_RIGHT)->Release();
	GetButton(DestinationButton::DPAD3_DOWN_RIGHT)->Release();
	GetButton(DestinationButton::DPAD3_DOWN)->Release();
	GetButton(DestinationButton::DPAD3_DOWN_LEFT)->Release();
	GetButton(DestinationButton::DPAD4_LEFT)->Release();
	GetButton(DestinationButton::DPAD4_UP_LEFT)->Release();
	GetButton(DestinationButton::DPAD4_UP)->Release();
	GetButton(DestinationButton::DPAD4_UP_RIGHT)->Release();
	GetButton(DestinationButton::DPAD4_RIGHT)->Release();
	GetButton(DestinationButton::DPAD4_DOWN_RIGHT)->Release();
	GetButton(DestinationButton::DPAD4_DOWN)->Release();
	GetButton(DestinationButton::DPAD4_DOWN_LEFT)->Release();
}

Destination::~Destination()
{
}

void Destination::Init(bool verbose)
{
	WORD dll, drv;
	DriverMatch(&dll, &drv);
	if (verbose)
		echo(I18N.vJoy_version, dll >> 8 & 0xF, dll >> 4 & 0xF, dll & 0xF, drv >> 8 & 0xF, drv >> 4 & 0xF, drv & 0xF);
}

BOOL Destination::Active()
{
	return m_devID > 0;
}

BOOL Destination::Open(int DevID, bool verbose)
{
	VjdStat status = GetVJDStatus(DevID);

	switch (status)
	{
	case VJD_STAT_OWN:
	case VJD_STAT_FREE: break;
	case VJD_STAT_BUSY: { echo(I18N.vJoy_busy, DevID); return FALSE; }
	case VJD_STAT_MISS:
	default: { if (verbose) { echo(I18N.vJoy_initialization_failed, DevID); } return FALSE; }
	}

	if (!AcquireVJD(DevID))
	{
		echo(I18N.vJoy_failed_acquire, DevID);
		return FALSE;
	}

	m_iReport.bDevice = m_devID = DevID;
		if (verbose)
			echo(I18N.vJoy_acquired, DevID);

	memcpy(&m_iReportDefault, &m_iReport, sizeof(m_iReport));
	return Update();
}

void Destination::loadAxis(DestButtonID id, long* data, byte axis)
{
	m_buttons[id].setAxis(data, axis);
	m_buttons[id].Release();
}

void Destination::loadTrigger(DestButtonID id, long* data, byte axis)
{
	m_buttons[id].setTrigger(data, axis);
	m_buttons[id].Release();
}

void Destination::loadAxisToTrigger(DestButtonID id, long* data, byte axis)
{
	m_buttons[id].setAxisToTrigger(data, axis);
	m_buttons[id].Release();
}

void Destination::loadAxisInv(DestButtonID id, long* data, byte axis)
{
	m_buttons[id].setAxisInv(data, axis);
	m_buttons[id].Release();
}

void Destination::loadTriggerInv(DestButtonID id, long* data, byte axis)
{
	m_buttons[id].setTriggerInv(data, axis);
	m_buttons[id].Release();
}

void Destination::loadAxisToTriggerInv(DestButtonID id, long* data, byte axis)
{
	m_buttons[id].setAxisToTriggerInv(data, axis);
	m_buttons[id].Release();
}

void Destination::loadRing(DestAxisMoveID id, long* data, long* data2, byte axis)
{
	m_axis[id].setRing(data, data2, id, axis);
	m_axis[id].Release();
}

void Destination::loadEffet(DestAfterEffectID id, long* data, long* data2)
{
	m_effect[id].setEffect(data, data2, id);
}

double Destination::distSum(Point p, Point arr[], int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		double distx = abs(arr[i].x - p.x);
		double disty = abs(arr[i].y - p.y);
		sum += sqrt((distx * distx) + (disty * disty));
	}

	// Return the sum of Euclidean Distances
	return sum;
}

Point Destination::geometricMedian(Point arr[], int n)
{
	double lower_limit = 0.01;
	double test_distance = 2;
	Point current_point = { 0, 0 };
	Point test_point[] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

	for (int i = 0; i < n; i++)
	{
		current_point.x += arr[i].x;
		current_point.y += arr[i].y;
	}

	current_point.x /= n;
	current_point.y /= n;
	double minimum_distance = distSum(current_point, arr, n);

	int k = 0;
	while (k < n)
	{
		for (int i = 0; /*i < n, */i != k; i++)
		{
			Point newpoint;
			newpoint.x = arr[i].x;
			newpoint.y = arr[i].y;
			double newd = distSum(newpoint, arr, n);

			if (newd < minimum_distance)
			{
				minimum_distance = newd;
				current_point.x = newpoint.x;
				current_point.y = newpoint.y;
			}
		}
		k++;
	}

	int flag = 0;
	while (test_distance > lower_limit)
	{
		flag = 0;

		for (int i = 0; i < 4; i++)
		{
			Point newpoint;
			newpoint.x = current_point.x + (double)test_distance * test_point[i].x;
			newpoint.y = current_point.y + (double)test_distance * test_point[i].y;
			double newd = distSum(newpoint, arr, n);

			if (newd < minimum_distance)
			{
				minimum_distance = newd;
				current_point.x = newpoint.x;
				current_point.y = newpoint.y;
				flag = 1;
				break;
			}
		}

		if (flag == 0)
			test_distance /= 2;
	}

	// Return the geometric median
	return { current_point.x, current_point.y };
}

void Destination::Clear()
{
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
		GetButton((DestButtonID)i)->SetPushed(false);

	memcpy(&m_iReport, &m_iReportDefault, sizeof(m_iReport));
	memset(&Dpad, 0, sizeof(Dpad));
	Update();
}

void Destination::ClearState()
{
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
		GetButton((DestButtonID)i)->SetPushed(false);

	memcpy(&m_iReport, &m_iReportDefault, sizeof(m_iReport));

	if (!GetButton(DestButtonID::DPAD1_LEFT)->isPushed()) { Dpad[0] = 0; }
	if (!GetButton(DestButtonID::DPAD1_UP_LEFT)->isPushed()) { Dpad[1] = 0; }
	if (!GetButton(DestButtonID::DPAD1_UP)->isPushed()) { Dpad[2] = 0; }
	if (!GetButton(DestButtonID::DPAD1_UP_RIGHT)->isPushed()) { Dpad[3] = 0; }
	if (!GetButton(DestButtonID::DPAD1_RIGHT)->isPushed()) { Dpad[4] = 0; }
	if (!GetButton(DestButtonID::DPAD1_DOWN_RIGHT)->isPushed()) { Dpad[5] = 0; }
	if (!GetButton(DestButtonID::DPAD1_DOWN)->isPushed()) { Dpad[6] = 0; }
	if (!GetButton(DestButtonID::DPAD1_DOWN_LEFT)->isPushed()) { Dpad[7] = 0; }
	if (!GetButton(DestButtonID::DPAD2_LEFT)->isPushed()) { Dpad[8] = 0; }
	if (!GetButton(DestButtonID::DPAD2_UP_LEFT)->isPushed()) { Dpad[9] = 0; }
	if (!GetButton(DestButtonID::DPAD2_UP)->isPushed()) { Dpad[10] = 0; }
	if (!GetButton(DestButtonID::DPAD2_UP_RIGHT)->isPushed()) { Dpad[11] = 0; }
	if (!GetButton(DestButtonID::DPAD2_RIGHT)->isPushed()) { Dpad[12] = 0; }
	if (!GetButton(DestButtonID::DPAD2_DOWN_RIGHT)->isPushed()) { Dpad[13] = 0; }
	if (!GetButton(DestButtonID::DPAD2_DOWN)->isPushed()) { Dpad[14] = 0; }
	if (!GetButton(DestButtonID::DPAD2_DOWN_LEFT)->isPushed()) { Dpad[15] = 0; }
	if (!GetButton(DestButtonID::DPAD3_LEFT)->isPushed()) { Dpad[16] = 0; }
	if (!GetButton(DestButtonID::DPAD3_UP_LEFT)->isPushed()) { Dpad[17] = 0; }
	if (!GetButton(DestButtonID::DPAD3_UP)->isPushed()) { Dpad[18] = 0; }
	if (!GetButton(DestButtonID::DPAD3_UP_RIGHT)->isPushed()) { Dpad[19] = 0; }
	if (!GetButton(DestButtonID::DPAD3_RIGHT)->isPushed()) { Dpad[20] = 0; }
	if (!GetButton(DestButtonID::DPAD3_DOWN_RIGHT)->isPushed()) { Dpad[21] = 0; }
	if (!GetButton(DestButtonID::DPAD3_DOWN)->isPushed()) { Dpad[22] = 0; }
	if (!GetButton(DestButtonID::DPAD3_DOWN_LEFT)->isPushed()) { Dpad[23] = 0; }
	if (!GetButton(DestButtonID::DPAD4_LEFT)->isPushed()) { Dpad[24] = 0; }
	if (!GetButton(DestButtonID::DPAD4_UP_LEFT)->isPushed()) { Dpad[25] = 0; }
	if (!GetButton(DestButtonID::DPAD4_UP)->isPushed()) { Dpad[26] = 0; }
	if (!GetButton(DestButtonID::DPAD4_UP_RIGHT)->isPushed()) { Dpad[27] = 0; }
	if (!GetButton(DestButtonID::DPAD4_RIGHT)->isPushed()) { Dpad[28] = 0; }
	if (!GetButton(DestButtonID::DPAD4_DOWN_RIGHT)->isPushed()) { Dpad[29] = 0; }
	if (!GetButton(DestButtonID::DPAD4_DOWN)->isPushed()) { Dpad[30] = 0; }
	if (!GetButton(DestButtonID::DPAD4_DOWN_LEFT)->isPushed()) { Dpad[31] = 0; }
}

void Destination::UpdateState()
{
	const double π = 3.141592653589793;
	const double λ = 0.707106781186547;

	for (int i = 0; i < 32; i += 8)
	{
		Point arr[8];
		int n = 0;
		double result = -1;
		if (Dpad[0 + i]) { arr[n].x = -1; arr[n].y = 0; n++; }
		if (Dpad[1 + i]) { arr[n].x = -λ; arr[n].y = λ; n++; }
		if (Dpad[2 + i]) { arr[n].x = 0; arr[n].y = 1; n++; }
		if (Dpad[3 + i]) { arr[n].x = λ; arr[n].y = λ; n++; }
		if (Dpad[4 + i]) { arr[n].x = 1; arr[n].y = 0; n++; }
		if (Dpad[5 + i]) { arr[n].x = λ; arr[n].y = -λ; n++; }
		if (Dpad[6 + i]) { arr[n].x = 0; arr[n].y = -1; n++; }
		if (Dpad[7 + i]) { arr[n].x = -λ; arr[n].y = -λ; n++; }

		Point median = geometricMedian(arr, n);

		if ((abs(median.x) > 0.001 || abs(median.y) > 0.001) && n)
		{
			result = atan2(median.x, median.y);
			if (result < 0)
				result += (2 * π);
			result = result * (4 / π);
		}

		switch (i)
		{
		case 0: { m_iReport.bHats = (result == -1) ? -1 : int(result * 4500); break; }
		case 8: { m_iReport.bHatsEx1 = (result == -1) ? -1 : int(result * 4500); break; }
		case 16: { m_iReport.bHatsEx2 = (result == -1) ? -1 : int(result * 4500); break; }
		case 24: { m_iReport.bHatsEx3 = (result == -1) ? -1 : int(result * 4500); break; }
		}
	}
}

BOOL Destination::Update()
{
	if (m_devID <= 0)
		return FALSE;

	JOYSTICK_POSITION_V2 Reporttmp;
	Reporttmp.bHats = m_iReport.bHats;
	Reporttmp.bHatsEx1 = m_iReport.bHatsEx1;
	Reporttmp.bHatsEx2 = m_iReport.bHatsEx2;
	Reporttmp.bHatsEx3 = m_iReport.bHatsEx3;

	Reporttmp.lButtons = m_iReport.lButtons;
	Reporttmp.lButtonsEx1 = m_iReport.lButtonsEx1;
	Reporttmp.lButtonsEx2 = m_iReport.lButtonsEx2;
	Reporttmp.lButtonsEx3 = m_iReport.lButtonsEx3;
	Reporttmp.wThrottle = m_iReport.wThrottle;

	Reporttmp.wAxisX = m_iReport.wAxisX * 32767 / 65535;
	Reporttmp.wAxisY = m_iReport.wAxisY * 32767 / 65535;
	Reporttmp.wAxisZ = m_iReport.wAxisZ * 32767 / 65535;
	Reporttmp.wAxisXRot = m_iReport.wAxisXRot * 32767 / 65535;
	Reporttmp.wAxisYRot = m_iReport.wAxisYRot * 32767 / 65535;
	Reporttmp.wAxisZRot = m_iReport.wAxisZRot * 32767 / 65535;
	Reporttmp.wSlider = m_iReport.wSlider * 32767 / 65535;
	Reporttmp.wDial = m_iReport.wDial * 32767 / 65535;

	Reporttmp.wAxisVX = m_iReport.wAxisVX * 32767 / 65535;
	Reporttmp.wAxisVY = m_iReport.wAxisVY * 32767 / 65535;
	Reporttmp.wAxisVZ = m_iReport.wAxisVZ * 32767 / 65535;
	Reporttmp.wAxisVBRX = m_iReport.wAxisVBRX * 32767 / 65535;
	Reporttmp.wAxisVBRY = m_iReport.wAxisVBRY * 32767 / 65535;
	Reporttmp.wAxisVBRZ = m_iReport.wAxisVBRZ * 32767 / 65535;
	Reporttmp.wRudder = m_iReport.wRudder * 32767 / 65535;
	Reporttmp.wAileron = m_iReport.wAileron * 32767 / 65535;

	Reporttmp.wWheel = m_iReport.wWheel * 32767 / 65535;

	if (!UpdateVJD(m_devID, &Reporttmp))
	{
		echo(I18N.vJoy_failed_update, m_devID);
		Close();
		return FALSE;
	}

	return TRUE;
}

DestinationButton* Destination::GetButton(DestButtonID id)
{
	if (id >= DestButtonID::Destination_None && id < DestButtonID::Destination_Count)
		return &m_buttons[id];
	return &m_buttons[0];
}

DestinationButton* Destination::GetAxis(DestAxisMoveID id)
{
	if (id >= DestAxisMoveID::AxisMove_None && id < DestAxisMoveID::AxisMove_Count)
		return &m_axis[id];
	return &m_axis[0];
}

DestinationButton* Destination::GetEffect(DestAfterEffectID id)
{
	if (id >= DestAfterEffectID::AfterEffect_None && id < DestAfterEffectID::AfterEffect_Count)
		return &m_effect[id];
	return &m_effect[0];
}

void Destination::Close()
{
	if (m_devID > 0)
	{
		m_devID = 0;
		static std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		if (std::chrono::system_clock::now() - start < std::chrono::milliseconds(1000))
			return;
		else
			start = std::chrono::system_clock::now();
		Clear();
		RelinquishVJD(m_devID);
	}
}
