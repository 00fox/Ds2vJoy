#include "stdafx.h"
#include "DS5Button.h"
#include "Language.h"

DS5Button::DS5Button():
	m_data(0),
	m_mask(0),
	m_type(typeNone)
{
}

DS5Button::~DS5Button()
{
}


void DS5Button::setBit(BYTE * data, UINT32 bitmask)
{
	m_type = typeBit;
	m_data = data;
	m_mask = bitmask;
}

void DS5Button::setStick(BYTE * data)
{
	m_type = typeStick;
	m_data = data;
}

void DS5Button::setTrigger(BYTE * data)
{
	m_type = typeTrigger;
	m_data = data;
}

void DS5Button::setDPad(BYTE * data)
{
	m_type = typeDPad;
	m_data = data;
}

void DS5Button::setDPadType(BYTE * data, ButtonType type)
{
	m_type = type;
	m_data = data;
}
BOOL DS5Button::Enable() {
	return m_data != 0;
}


BOOL DS5Button::isPushed()
{
	switch (m_type)
	{
	case typeBit:
		return (*m_data & m_mask) != 0;
	case typeStick:
		return *m_data > 135 || *m_data < 121;
	case typeTrigger:
		return *m_data > 0;
	case typeDPad:
		return (*m_data & 0xF) != 8;
	}
	BYTE dpad = (*m_data & 0xF);
	switch (m_type)
	{
	case typeDPadUP:
		return (dpad == 7 || dpad == 0 || dpad == 1);
	case typeDPadRIGHT:
		return (dpad == 1 || dpad == 2 || dpad == 3);
	case typeDPadDOWN:
		return (dpad == 3 || dpad == 4 || dpad == 5);
	case typeDPadLEFT:
		return (dpad == 5 || dpad == 6 || dpad == 7);
	default:
		return FALSE;
	}
}

void DS5Button::Release()
{
	switch (m_type)
	{
	case typeBit:
		*m_data &= ~m_mask;
		break;
	case typeStick:
		*m_data = 128;
		break;
	case typeTrigger:
		*m_data = 0;
		break;
	case typeDPad:
		*m_data = (*m_data & 0xF0) | 8;
		break;
	case typeDPadUP:
		switch (*m_data&0xF){
		case 7:
			*m_data = (*m_data & 0xF0) | 6;
			break;
		case 0:
			*m_data = (*m_data & 0xF0) | 8;
			break;
		case 1:
			*m_data = (*m_data & 0xF0) | 2;
			break;
		}
		break;
	case typeDPadRIGHT:
		switch (*m_data & 0xF) {
		case 1:
			*m_data = (*m_data & 0xF0) | 0;
			break;
		case 2:
			*m_data = (*m_data & 0xF0) | 8;
			break;
		case 3:
			*m_data = (*m_data & 0xF0) | 4;
			break;
		}
		break;
	case typeDPadDOWN:
		switch (*m_data & 0xF) {
		case 3:
			*m_data = (*m_data & 0xF0) | 2;
			break;
		case 4:
			*m_data = (*m_data & 0xF0) | 8;
			break;
		case 5:
			*m_data = (*m_data & 0xF0) | 6;
			break;
		}
		break;
	case typeDPadLEFT:
		switch (*m_data & 0xF) {
		case 5:
			*m_data = (*m_data & 0xF0) | 4;
			break;
		case 6:
			*m_data = (*m_data & 0xF0) | 8;
			break;
		case 7:
			*m_data = (*m_data & 0xF0) | 0;
			break;
		}
		break;
	}
}

BYTE DS5Button::GetVal()
{
	switch (m_type)
	{
	case typeBit:
		return (*m_data & m_mask )?0xFF:0;
	case typeStick:
	case typeTrigger:
		return *m_data;
	case typeDPad:
		return *m_data & 0xF;
	}
	BYTE dpad = (*m_data & 0xF);
	switch (m_type)
	{
	case typeDPadUP:
		return (dpad == 7 || dpad == 0 || dpad == 1) ? 0xFF : 0;
	case typeDPadRIGHT:
		return (dpad == 1 || dpad == 2 || dpad == 3) ? 0xFF : 0;
	case typeDPadDOWN:
		return (dpad == 3 || dpad == 4 || dpad == 5) ? 0xFF : 0;
	case typeDPadLEFT:
		return (dpad == 5 || dpad == 6 || dpad == 7) ? 0xFF : 0;
	}
	return 0;
}

WCHAR * DS5Button::String(ButtonID id)
{
	switch (id)
	{
	case none: return L"";
	case SQUARE: return I18N.Button_SQUARE;
	case TRIANGLE: return I18N.Button_TRIANGLE;
	case CROSS: return I18N.Button_CROSS;
	case CIRCLE: return I18N.Button_CIRCLE;
	case L1: return I18N.Button_L1;
	case R1: return I18N.Button_R1;
	case L2: return I18N.Button_L2;
	case R2: return I18N.Button_R2;
	case L3: return I18N.Button_L3;
	case R3: return I18N.Button_R3;
	case CREATE: return I18N.Button_CREATE;
	case OPTIONS: return I18N.Button_OPTIONS;
	case PS: return I18N.Button_PS;
	case TOUCH: return I18N.Button_TOUCH;
	case LX: return I18N.Button_LX;
	case LY: return I18N.Button_LY;
	case RX: return I18N.Button_RX;
	case RY: return I18N.Button_RY;
	case L2TRIGGER: return I18N.Button_L2TRIGGER;
	case R2TRIGGER: return I18N.Button_R2TRIGGER;
	case DPAD: return I18N.Button_DPAD;
	case DPAD_UP: return I18N.Button_DPAD_UP;
	case DPAD_RIGHT: return I18N.Button_DPAD_RIGHT;
	case DPAD_DOWN: return I18N.Button_DPAD_DOWN;
	case DPAD_LEFT: return I18N.Button_DPAD_LEFT;
	case MUTE: return I18N.Button_MUTE;
	default: return L"???";
	}
}

