#include "stdafx.h"
#include "vJoyButton.h"


vJoyButton::vJoyButton():m_exists(false)
{
}

void vJoyButton::setBit(LONG * data, UINT32 bitmask)
{
	m_type = typeBit;
	m_data = data;
	m_mask = bitmask;
	m_exists = true;
}

void vJoyButton::setAxis(LONG * data, LONG min, LONG max)
{
	if(max==0)
		max = 1;
	m_type = typeAxis;
	m_data = data;
	m_AxisMaxMin = max - min;
	m_AxisMin = min;
	m_AxisDefault = m_AxisMaxMin / 2 + min;
	m_AxisThreshold =(LONG) (m_AxisMaxMin * 0.04);
	m_exists = true;

}

void vJoyButton::setPOV(LONG * data)
{
	m_type = typePOV;
	m_data = data;
	m_exists = true;
}


vJoyButton::~vJoyButton()
{
}

BOOL vJoyButton::isPushed()
{
	if (!m_exists)
		return FALSE;
	switch (m_type)
	{
	case typeBit:
		return (*m_data & m_mask) != 0;
	case typeAxis:
		return *m_data > (m_AxisDefault + m_AxisThreshold) || *m_data < (m_AxisDefault - m_AxisThreshold);
	case typePOV:
		return *m_data != -1;
	default:
		return FALSE;
	}
}

void vJoyButton::Release()
{
	if (!m_exists)
		return;
	switch (m_type)
	{
	case typeBit:
		*m_data &= ~m_mask;
		break;
	case typeAxis:
		*m_data = m_AxisDefault;
		break;
	case typePOV:
		*m_data = -1;
		break;
	}
}

LONG vJoyButton::GetVal()
{
	if (!m_exists)
		return 0;
	switch (m_type)
	{
	case typeBit:
		return *m_data & m_mask;
	case typeAxis:
	case typePOV:
		return *m_data;
	default:
		return 0;
	}
}

//0x00~0xFFの範囲で。
void vJoyButton::SetVal(BYTE val)
{
	if (!m_exists)
		return;
	switch (m_type)
	{
	case typeBit:
		if (val) {
			*m_data |= m_mask;
		}
		else {
			*m_data &= ~m_mask;
		}
		break;
	case typeAxis:
		*m_data = val*m_AxisMaxMin/0xFF + m_AxisMin;
		break;
	case typePOV:
		*m_data= val > 7 ? -1 : val * 4500 ;
		break;
	}
}

WCHAR * vJoyButton::String(ButtonID id)
{
	switch (id)
	{
	case none: return L"";
	case X: return L"X";
	case Y: return L"Y";
	case Z: return L"Z";
	case RX: return L"RX";
	case RY: return L"RY";
	case RZ: return L"RZ";
	case SL0: return L"SL0";
	case SL1: return L"SL1";
	case POV1: return L"POV1";
	case POV2: return L"POV2";
	case POV3: return L"POV3";
	case POV4: return L"POV4";
	}
	if (Button1 <= id && id <= Button128) {
		static WCHAR buf[11];
		wsprintf(buf, L"Button %3d", id - Button1 + 1);
		return buf;
	}
	return L"???";
}


