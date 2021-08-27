#include "stdafx.h"
#include "vJoyButton.h"

vJoyButton::vJoyButton()
{
}

vJoyButton::~vJoyButton()
{
}

void vJoyButton::setButton(LONG* data, UINT32 bitmask)
{
	m_type = typeButton;
	m_data = data;
	m_mask = bitmask;
}

void vJoyButton::setTrigger(LONG* data)
{
	m_type = typeTrigger;
	m_data = data;
}

void vJoyButton::setAxis(LONG* data)
{
	m_type = typeAxis;
	m_data = data;
}

void vJoyButton::setAxisInv(LONG* data)
{
	m_type = typeAxisInv;
	m_data = data;
}

void vJoyButton::setDPad(BYTE* data)
{
	m_type = typeDPad;
	m_dataDPad = data;
}

BOOL vJoyButton::isPushed()
{
	return m_isPushed;
}

void vJoyButton::SetPushed(bool ispushed)
{
	m_isPushed = ispushed;
}

void vJoyButton::Release()
{
	m_isPushed = false;
	switch (m_type)
	{
	case typeButton:
		*m_data &= ~m_mask;
		break;
	case typeTrigger:
		*m_data = 0;
		break;
	case typeAxis:
	case typeAxisInv:
		*m_data = 16383;
		break;
	case typeDPad:
		*m_dataDPad = 0;
		break;
	}
}

LONG vJoyButton::GetVal()
{
	switch (m_type)
	{
	case typeButton:
		return (*m_data & m_mask) ? 32767 : 0;
	case typeTrigger:
		return *m_data;
	case typeAxis:
		return *m_data;
	case typeAxisInv:
		return 32767 - *m_data;
	case typeDPad:
		return (*m_dataDPad) ? 32767 : 0;
	default:
		return *m_data;
	}
}

BYTE vJoyButton::GetVal2()
{
	return (BYTE)(GetVal() * 255 / 32767);
}

BYTE vJoyButton::GetReleasedVal()
{
	switch (m_type)
	{
	case typeButton:
		return (BYTE)(*m_data &= ~m_mask);
	case typeTrigger:
		return 0;
	case typeAxis:
		return 128;
	case typeAxisInv:
		return 128;
	case typeDPad:
		return 0;
	default:
		return 0;
	}
}

int vJoyButton::GetScrollVal()
{
	switch (m_type)
	{
	case typeButton:
		return 10;
	case typeTrigger:
		return 120 - (114 * *m_data) / 32767;
	case typeAxis:
		return (*m_data - 17151 > 0) ? (120 - (114 * max(0, (*m_data - 17151))) / 15616) : 0;
	case typeAxisInv:
		return (15616 - *m_data > 0) ? (120 - (114 * max(0, (15616 - *m_data))) / 15616) : 0;
	case typeDPad:
		return 10;
	default:
		return 0;
	}
}

void vJoyButton::SetVal(BYTE val)
{
	switch (m_type)
	{
	case typeButton:
		if (val)
			*m_data |= m_mask;
		else
			*m_data &= ~m_mask;
		break;
	case typeTrigger:
		*m_data = val * 32767 / 255;
		break;
	case typeAxis:
		*m_data = val * 32767 / 255;
		break;
	case typeAxisInv:
		*m_data = (32767) - (val * 32767 / 255);
		break;
	case typeDPad:
		*m_dataDPad = val;
		break;
	}
}

WCHAR* vJoyButton::String(ButtonID id)
{
	switch (id)
	{
	case none: return L"";
	case X: return I18N.vJoy_X;
	case Y: return I18N.vJoy_Y;
	case Z: return I18N.vJoy_Z;
	case RX: return I18N.vJoy_RX;
	case RY: return I18N.vJoy_RY;
	case RZ: return I18N.vJoy_RZ;
	case SL0: return I18N.vJoy_SL0;
	case SL1: return I18N.vJoy_SL1;
	case XTR: return I18N.vJoy_XTR;
	case YTR: return I18N.vJoy_YTR;
	case ZTR: return I18N.vJoy_ZTR;
	case RXTR: return I18N.vJoy_RXTR;
	case RYTR: return I18N.vJoy_RYTR;
	case RZTR: return I18N.vJoy_RZTR;
	case SL0TR: return I18N.vJoy_SL0TR;
	case SL1TR: return I18N.vJoy_SL1TR;
	case XINV: return I18N.vJoy_XINV;
	case YINV: return I18N.vJoy_YINV;
	case ZINV: return I18N.vJoy_ZINV;
	case RXINV: return I18N.vJoy_RXINV;
	case RYINV: return I18N.vJoy_RYINV;
	case RZINV: return I18N.vJoy_RZINV;
	case SL0INV: return I18N.vJoy_SL0INV;
	case SL1INV: return I18N.vJoy_SL1INV;
	case DPAD1_LEFT: return I18N.vJoy_DPAD1_LEFT;
	case DPAD1_UP_LEFT: return I18N.vJoy_DPAD1_UP_LEFT;
	case DPAD1_UP: return I18N.vJoy_DPAD1_UP;
	case DPAD1_UP_RIGHT: return I18N.vJoy_DPAD1_UP_RIGHT;
	case DPAD1_RIGHT: return I18N.vJoy_DPAD1_RIGHT;
	case DPAD1_DOWN_RIGHT: return I18N.vJoy_DPAD1_DOWN_RIGHT;
	case DPAD1_DOWN: return I18N.vJoy_DPAD1_DOWN;
	case DPAD1_DOWN_LEFT: return I18N.vJoy_DPAD1_DOWN_LEFT;
	case DPAD2_LEFT: return I18N.vJoy_DPAD2_LEFT;
	case DPAD2_UP_LEFT: return I18N.vJoy_DPAD2_UP_LEFT;
	case DPAD2_UP: return I18N.vJoy_DPAD2_UP;
	case DPAD2_UP_RIGHT: return I18N.vJoy_DPAD2_UP_RIGHT;
	case DPAD2_RIGHT: return I18N.vJoy_DPAD2_RIGHT;
	case DPAD2_DOWN_RIGHT: return I18N.vJoy_DPAD2_DOWN_RIGHT;
	case DPAD2_DOWN: return I18N.vJoy_DPAD2_DOWN;
	case DPAD2_DOWN_LEFT: return I18N.vJoy_DPAD2_DOWN_LEFT;
	case DPAD3_LEFT: return I18N.vJoy_DPAD3_LEFT;
	case DPAD3_UP_LEFT: return I18N.vJoy_DPAD3_UP_LEFT;
	case DPAD3_UP: return I18N.vJoy_DPAD3_UP;
	case DPAD3_UP_RIGHT: return I18N.vJoy_DPAD3_UP_RIGHT;
	case DPAD3_RIGHT: return I18N.vJoy_DPAD3_RIGHT;
	case DPAD3_DOWN_RIGHT: return I18N.vJoy_DPAD3_DOWN_RIGHT;
	case DPAD3_DOWN: return I18N.vJoy_DPAD3_DOWN;
	case DPAD3_DOWN_LEFT: return I18N.vJoy_DPAD3_DOWN_LEFT;
	case DPAD4_LEFT: return I18N.vJoy_DPAD4_LEFT;
	case DPAD4_UP_LEFT: return I18N.vJoy_DPAD4_UP_LEFT;
	case DPAD4_UP: return I18N.vJoy_DPAD4_UP;
	case DPAD4_UP_RIGHT: return I18N.vJoy_DPAD4_UP_RIGHT;
	case DPAD4_RIGHT: return I18N.vJoy_DPAD4_RIGHT;
	case DPAD4_DOWN_RIGHT: return I18N.vJoy_DPAD4_DOWN_RIGHT;
	case DPAD4_DOWN: return I18N.vJoy_DPAD4_DOWN;
	case DPAD4_DOWN_LEFT: return I18N.vJoy_DPAD4_DOWN_LEFT;
	}
	if (Button1 <= id && id <= Button128)
	{
		static WCHAR buf[10];
		wsprintf(buf, L"%d", id - Button1 + 1);
		return buf;
	}
	return L"???";
}
