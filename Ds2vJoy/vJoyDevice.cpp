#include "stdafx.h"
#include "vJoyDevice.h"

CvJoyDevice::CvJoyDevice() :
	status(VJD_STAT_UNKN),
	ButtonNumber(0), DiscPovNumber(0), ContPovNumber(0),
	X_Exist(FALSE), Y_Exist(FALSE), Z_Exist(FALSE), RX_Exist(FALSE), RY_Exist(FALSE), RZ_Exist(FALSE), SL0_Exist(FALSE), SL1_Exist(FALSE),
	Id(0)
{
	CvJoyDevice(1);
}

CvJoyDevice::CvJoyDevice(int id) : 
	status(VJD_STAT_UNKN),
	ButtonNumber(0), DiscPovNumber(0), ContPovNumber(0),
	X_Exist(FALSE), Y_Exist(FALSE), Z_Exist(FALSE), RX_Exist(FALSE), RY_Exist(FALSE), RZ_Exist(FALSE), SL0_Exist(FALSE), SL1_Exist(FALSE)
{
	if (id <= 0 || id > MAX_N_DEVICES)
		Id = 0;
	else
		Id = id;
}

CvJoyDevice::~CvJoyDevice()
{
}

BOOL CvJoyDevice::GetStatus(int id)
{
	if (id <= 0 || id > MAX_N_DEVICES)
		return FALSE;

	status = GetVJDStatus(id);
	if (status != VJD_STAT_UNKN && status != VJD_STAT_MISS)
	{
		ButtonNumber = GetVJDButtonNumber(id);
		DiscPovNumber = GetVJDDiscPovNumber(id);
		ContPovNumber = GetVJDContPovNumber(id);
		X_Exist = GetVJDAxisExist(id, HID_USAGE_X);
		Y_Exist = GetVJDAxisExist(id, HID_USAGE_Y);
		Z_Exist = GetVJDAxisExist(id, HID_USAGE_Z);
		RX_Exist = GetVJDAxisExist(id, HID_USAGE_RX);
		RY_Exist = GetVJDAxisExist(id, HID_USAGE_RY);
		RZ_Exist = GetVJDAxisExist(id, HID_USAGE_RZ);
		SL0_Exist = GetVJDAxisExist(id, HID_USAGE_SL0);
		SL1_Exist = GetVJDAxisExist(id, HID_USAGE_SL1);
		return TRUE;
	};
	return FALSE;
}

BOOL CvJoyDevice::Exists()
{
	if (Id <= 0 || Id > MAX_N_DEVICES)
		return FALSE;

	status = GetVJDStatus(Id);
	if (status != VJD_STAT_UNKN && status != VJD_STAT_MISS)
		return TRUE;
	else
		return FALSE;
}

BOOL CvJoyDevice::AxisExists(UINT Axis)
{
	return  (GetVJDAxisExist(Id, Axis)==TRUE);
}

int CvJoyDevice::GetButtonNumber(void)
{
	int n = GetVJDButtonNumber(Id);
	if (n < 0)
		n = 0;
	return n;
}

int CvJoyDevice::GetDiscPovNumber(void)
{
	int n = GetVJDDiscPovNumber(Id);
	if (n < 0)
		n = 0;
	return n;
}

int CvJoyDevice::GetContPovNumber(void)
{
	int n = GetVJDContPovNumber(Id);
	if (n < 0)
		n = 0;
	return n;
}
