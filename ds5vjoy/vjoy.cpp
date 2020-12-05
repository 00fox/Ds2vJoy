#include "stdafx.h"
#include "vjoy.h"
#include "Log.h"
#include "Language.h"

vJoyDevice::vJoyDevice()
{
	for (int i = 0; i < 32; i++) {
		UINT32 bitmask = 1 << i;
		GetButton((vJoyButtonID)(vJoyButtonID::Button1 + i))->setBit(&m_iReport.lButtons, bitmask);
	}
	for (int i = 0; i < 32; i++) {
		UINT32 bitmask = 1 << i;
		GetButton((vJoyButtonID)(vJoyButtonID::Button1 + i + 32))->setBit(&m_iReport.lButtonsEx1, bitmask);
	}
	for (int i = 0; i < 32; i++) {
		UINT32 bitmask = 1 << i;
		GetButton((vJoyButtonID)(vJoyButtonID::Button1 + i + 64))->setBit(&m_iReport.lButtonsEx2, bitmask);
	}
	for (int i = 0; i < 32; i++) {
		UINT32 bitmask = 1 << i;
		GetButton((vJoyButtonID)(vJoyButtonID::Button1 + i + 96))->setBit(&m_iReport.lButtonsEx3, bitmask);
	}
	GetButton(vJoyButtonID::POV1)->setPOV((LONG*)&m_iReport.bHats);
	GetButton(vJoyButtonID::POV2)->setPOV((LONG*)&m_iReport.bHatsEx1);
	GetButton(vJoyButtonID::POV3)->setPOV((LONG*)&m_iReport.bHatsEx2);
	GetButton(vJoyButtonID::POV4)->setPOV((LONG*)&m_iReport.bHatsEx3);
}

bool vJoyDevice::Init(HWND hWnd)
{
	if (!vJoyEnabled()) {
		MessageBox(NULL, I18N.vJoy_please_install, I18N.MBOX_ErrTitle , MB_OK);
		return false;
	}
	WORD dll, drv;
	if (DriverMatch(&dll, &drv)) {
		LogPrintf(I18N.vJoy_version, dll >> 8 & 0xF, dll >> 4 & 0xF, dll & 0xF);
	}
	else {
		LogPrintf(I18N.vJoy_version_notmatch, dll >> 8 & 0xF, dll >> 4 & 0xF, dll & 0xF, drv >> 8 & 0xF, drv >> 4 & 0xF, drv & 0xF);
	}

	return true;
}

bool vJoyDevice::Active()
{
	return m_devID > 0;
}

bool vJoyDevice::Open(int DevID)
{
	if (m_devID>0) {
		return false;
	}

	VjdStat status = GetVJDStatus(DevID);

	switch (status)
	{
	case VJD_STAT_OWN:
	case VJD_STAT_FREE:
		break;
	case VJD_STAT_BUSY:
		LogPrintf(I18N.vJoy_busy , DevID);
		return false;
	case VJD_STAT_MISS:
	default:
		LogPrintf(I18N.vJoy_cantuse , DevID);
		return false;
	};

	if (!AcquireVJD(DevID)){
		LogPrintf(I18N.vJoy_failed_acquire , DevID);
		return false;
	}

	//初期化
	memset(&m_iReport, 0, sizeof(m_iReport));
	m_iReport.bDevice = m_devID = DevID;
	loadAxis(vJoyButton::X, HID_USAGE_X, &m_iReport.wAxisX);
	loadAxis(vJoyButton::Y, HID_USAGE_Y, &m_iReport.wAxisY);
	loadAxis(vJoyButton::Z, HID_USAGE_Z, &m_iReport.wAxisZ);
	loadAxis(vJoyButton::RX, HID_USAGE_X, &m_iReport.wAxisXRot);
	loadAxis(vJoyButton::RY, HID_USAGE_Y, &m_iReport.wAxisYRot);
	loadAxis(vJoyButton::RZ, HID_USAGE_Z, &m_iReport.wAxisZRot);
	loadAxis(vJoyButton::SL0, HID_USAGE_SL0, &m_iReport.wSlider);
	loadAxis(vJoyButton::SL1, HID_USAGE_SL1, &m_iReport.wDial);
	GetButton(vJoyButton::POV1)->Release();
	GetButton(vJoyButton::POV2)->Release();
	GetButton(vJoyButton::POV3)->Release();
	GetButton(vJoyButton::POV4)->Release();

	LogPrintf(I18N.vJoy_acquire, DevID);

	memcpy(&m_iReportDefault, &m_iReport, sizeof(m_iReport));
	return Update();
}
//Axis情報を設定
void vJoyDevice::loadAxis(vJoyButtonID id, int hid_axis, LONG *data)
{
	if (GetVJDAxisExist(m_devID, hid_axis) != FALSE) {
		LONG max, min;
		if (GetVJDAxisMax(m_devID, hid_axis, &max) &&
			GetVJDAxisMin(m_devID, hid_axis, &min)) {
			m_buttons[id].setAxis(data, min, max);
			m_buttons[id].Release();
		}
	}
}
//vJoyに送信
bool vJoyDevice::Update()
{
	if (m_devID <= 0) {
		return false;
	}
	if (!UpdateVJD(m_devID, &m_iReport)){
		LogPrintf(I18N.vJoy_failed_update);
		Close();
		return false;
	}
	return true;
}

//ボタン情報をデフォルトに
bool vJoyDevice::ClearState()
{
	memcpy(&m_iReport, &m_iReportDefault, sizeof(m_iReport));
	return true;
}

//ボタンを取得
vJoyButton * vJoyDevice::GetButton(vJoyButtonID id)
{
	if (id >= vJoyButtonID::none && id < vJoyButtonID::button_Count)
		return &m_buttons[id];
	return &m_buttons[0];
}


void vJoyDevice::Close()
{
	if (m_devID > 0) {
		SetFFBCallback(NULL, NULL);
		RelinquishVJD(m_devID);
		m_devID = 0;
	}
}

void vJoyDevice::SetFFBCallback(FfbGenCB cb, PVOID data)
{
	FfbRegisterGenCB(cb, data);
}


vJoyDevice::~vJoyDevice()
{
	Close();
}
