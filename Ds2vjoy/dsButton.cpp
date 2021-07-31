#include "stdafx.h"
#include "dsButton.h"
#include "Ds2vJoy.h"

dsButton::dsButton()
	: m_data(0),
	m_mask(0),
	m_type(typeNone)
{
}

dsButton::~dsButton()
{
}

void dsButton::setConstant(BYTE data)
{
	m_type = typeConstant;
	m_constant = data;
}

void dsButton::setButton(BYTE* data, UINT32 bitmask)
{
	m_type = typeButton;
	m_data = data;
	m_mask = bitmask;
}

void dsButton::setTrigger(BYTE* data, INT threshold)
{
	m_type = typeTrigger;
	m_data = data;
	m_thrz = threshold;
}

void dsButton::setSimultaneous(BYTE* data, UINT32 bitmask, BYTE* data2, UINT32 bitmask2)
{
	m_type = typeSimultaneous;
	m_data = data;
	m_data2 = data2;
	m_mask = bitmask;
	m_mask2 = bitmask2;
}

void dsButton::setTouch(BYTE* data, UINT32 bitmask, int box)
{
	m_type = typeTouch;
	m_data = data;
	m_box = box;
	m_mask = bitmask;
}

void dsButton::setDPad(BYTE* data, ButtonType type)
{
	m_type = type;
	m_data = data;
}

void dsButton::setAxis(BYTE* data, BYTE* data2)
{
	m_type = typeAxis;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisInv(BYTE* data, BYTE* data2)
{
	m_type = typeAxisInv;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisLU(BYTE* data)
{
	m_type = typeAxisLU;
	m_data = data;
}

void dsButton::setAxisRD(BYTE* data)
{
	m_type = typeAxisRD;
	m_data = data;
}

void dsButton::setAxisDUL(BYTE* data, BYTE* data2)
{
	m_type = typeAxisDUL;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisDUR(BYTE* data, BYTE* data2)
{
	m_type = typeAxisDUR;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisDDR(BYTE* data, BYTE* data2)
{
	m_type = typeAxisDDR;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisDDL(BYTE* data, BYTE* data2)
{
	m_type = typeAxisDDL;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setData(BYTE* data, UINT32 bitmask)
{
	m_type = typeData;
	m_data = data;
	m_mask = bitmask;
}

void dsButton::SetTouch(int box, BYTE value)
{
	TouchAble[box] = value;
}

BOOL dsButton::isPushed()
{
	switch (m_type)
	{
	case typeConstant:
		return TRUE;
	case typeButton:
		return (*m_data & m_mask);
	case typeTrigger:
		return (*m_data > m_thrz);
	case typeSimultaneous:
		if (!(*m_data & m_mask) && !(*m_data2 & m_mask2))
		{
			L2R2_Delay_On = 0;
			L2R2_Eligible = 1;
			L2R2_Pushed = 0;
			if (OrangeLedActive)
			{
				OrangeLedActive = 0;
				PostMessage(tape.ActualhWnd, WM_SETORANGELED, 0, 0);
			}
			return FALSE;
		}
		else if (L2R2_Eligible)
		{
			if ((*m_data & m_mask) && (*m_data2 & m_mask2))
			{
				L2R2_Eligible = 0;
				L2R2_Delay_On = 1;
				if (!OrangeLedActive)
				{
					OrangeLedActive = 1;
					PostMessage(tape.ActualhWnd, WM_SETORANGELED, 1, 0);
				}
				return TRUE;
			}
			else if ((*m_data & m_mask) || (*m_data2 & m_mask2))
			{
				if (L2R2_Pushed)
				{
					if ((clock() - L2R2_LastTimePushed) > tape.Simultaneous / 10)
						L2R2_Eligible = 0;
				}
				else
				{
					L2R2_Pushed = 1;
					L2R2_LastTimePushed = clock();
				}
				return FALSE;
			}
		}
		else if (L2R2_Delay_On)
			return TRUE;
		return FALSE;
	case typeTouch:
		switch (m_box)
		{
		case 0:
			return TouchAble[0] && (*m_data & m_mask);
		case 1:
			return TouchAble[1] && (*m_data & m_mask);
		case 2:
			return TouchAble[2] && (*m_data & m_mask);
		case 3:
			return TouchAble[3] && (*m_data & m_mask);
		case 4:
			return TouchAble[4] && (*m_data & m_mask);
		case 5:
			return TouchAble[5] && (*m_data & m_mask);
		case 6:
			return TouchAble[6] && (*m_data & m_mask);
		case 7:
			return (*m_data & m_mask) ? 0xFF : 0;
		case 8:
			return !TouchAble[0] && (*m_data & m_mask);
		default:
			return FALSE;
		}
	case typeDPad:
		return (*m_data & 0xF) != 8;
	case typeDPadUP:
		dpad = (*m_data & 0xF);
		return (dpad == 7 || dpad == 0 || dpad == 1);
	case typeDPadRIGHT:
		dpad = (*m_data & 0xF);
		return (dpad == 1 || dpad == 2 || dpad == 3);
	case typeDPadDOWN:
		dpad = (*m_data & 0xF);
		return (dpad == 3 || dpad == 4 || dpad == 5);
	case typeDPadLEFT:
		dpad = (*m_data & 0xF);
		return (dpad == 5 || dpad == 6 || dpad == 7);
	case typeAxis:
	case typeAxisInv:
		return (((*m_data - 127) * (*m_data - 127)) + ((*m_data2 - 127) * (*m_data2 - 127))) > 81;
	case typeAxisLU:
		return (*m_data < 5);
	case typeAxisRD:
		return (*m_data > 250);
	case typeAxisDUL:
		return (*m_data < 20 && *m_data2 < 20);
	case typeAxisDUR:
		return (*m_data < 20 && *m_data2 > 235);
	case typeAxisDDR:
		return (*m_data > 235 && *m_data2 > 235);
	case typeAxisDDL:
		return (*m_data > 235 && *m_data2 < 20);
	case typeData:
		return TRUE;
	default:
		return FALSE;
	}
}

//In the range of 0x00 to 0xFF
BYTE dsButton::GetVal()
{
	switch (m_type)
	{
	case typeConstant:
		return m_constant;
	case typeButton:
		return (abs(*m_data) & m_mask) ? 0xFF : 0;
	case typeTrigger:
		return (*m_data * (255 - m_thrz) / 255) + m_thrz;
	case typeSimultaneous:
		return isPushed() ? 0xFF : 0;
	case typeTouch:
		switch (m_box)
		{
		case 0:
			return (TouchAble[0] && (*m_data & m_mask)) ? 0xFF : 0;
		case 1:
			return (TouchAble[1] && (*m_data & m_mask)) ? 0xFF : 0;
		case 2:
			return (TouchAble[2] && (*m_data & m_mask)) ? 0xFF : 0;
		case 3:
			return (TouchAble[3] && (*m_data & m_mask)) ? 0xFF : 0;
		case 4:
			return (TouchAble[4] && (*m_data & m_mask)) ? 0xFF : 0;
		case 5:
			return (TouchAble[5] && (*m_data & m_mask)) ? 0xFF : 0;
		case 6:
			return (TouchAble[6] && (*m_data & m_mask)) ? 0xFF : 0;
		case 7:
			return (*m_data & m_mask) ? 0xFF : 0;
		case 8:
			return (!TouchAble[0] && (*m_data & m_mask)) ? 0xFF : 0;
		}
		return 0;
	case typeDPad:
		return *m_data & 0xF;
	case typeDPadUP:
		dpad = (*m_data & 0xF);
		return (dpad == 7 || dpad == 0 || dpad == 1) ? 0xFF : 0;
	case typeDPadRIGHT:
		dpad = (*m_data & 0xF);
		return (dpad == 1 || dpad == 2 || dpad == 3) ? 0xFF : 0;
	case typeDPadDOWN:
		dpad = (*m_data & 0xF);
		return (dpad == 3 || dpad == 4 || dpad == 5) ? 0xFF : 0;
	case typeDPadLEFT:
		dpad = (*m_data & 0xF);
		return (dpad == 5 || dpad == 6 || dpad == 7) ? 0xFF : 0;
	case typeAxis:
		return *m_data;
	case typeAxisInv:
		return 255 - *m_data;
	case typeAxisLU:
		return (*m_data < 5) ? 0xFF : 0;
	case typeAxisRD:
		return (*m_data > 250) ? 0xFF : 0;
	case typeAxisDUL:
		return (*m_data < 20 && *m_data2 < 20) ? 0xFF : 0;
	case typeAxisDUR:
		return (*m_data < 20 && *m_data2 > 235) ? 0xFF : 0;
	case typeAxisDDR:
		return (*m_data > 235 && *m_data2 > 235) ? 0xFF : 0;
	case typeAxisDDL:
		return (*m_data > 235 && *m_data2 < 20) ? 0xFF : 0;
	case typeData:
		return (BYTE)((*m_data & m_mask) * 25.5);
	default:
		return 0;
	}
}

BYTE dsButton::GetReleasedVal()
{
	switch (m_type)
	{
	case typeConstant:
		return m_constant;
	case typeButton:
		return *m_data &= ~m_mask;
	case typeTrigger:
		return 0;
	case typeSimultaneous:
		*m_data &= ~m_mask;
		return *m_data2 &= ~m_mask2;
	case typeTouch:
		return *m_data &= ~m_mask;
	case typeDPad:
		return (*m_data & 0xF0) | 8;
	case typeDPadUP:
		switch (*m_data & 0xF)
		{
		case 7:
			return (*m_data & 0xF0) | 6;
		case 0:
			return (*m_data & 0xF0) | 8;
		case 1:
			return (*m_data & 0xF0) | 2;
		}
	case typeDPadRIGHT:
		switch (*m_data & 0xF)
		{
		case 1:
			return (*m_data & 0xF0) | 0;
		case 2:
			return (*m_data & 0xF0) | 8;
		case 3:
			return (*m_data & 0xF0) | 4;
		}
	case typeDPadDOWN:
		switch (*m_data & 0xF)
		{
		case 3:
			return (*m_data & 0xF0) | 2;
		case 4:
			return (*m_data & 0xF0) | 8;
		case 5:
			return (*m_data & 0xF0) | 6;
		}
	case typeDPadLEFT:
		switch (*m_data & 0xF)
		{
		case 5:
			return (*m_data & 0xF0) | 4;
		case 6:
			return (*m_data & 0xF0) | 8;
		case 7:
			return (*m_data & 0xF0) | 0;
		}
	case typeAxis:
	case typeAxisInv:
		return 128;
	case typeAxisLU:
	case typeAxisRD:
	case typeAxisDUL:
	case typeAxisDUR:
	case typeAxisDDR:
	case typeAxisDDL:
	case typeData:
		return 0;
	default:
		return 0;
	}
}

int dsButton::GetScrollVal()
{
	switch (m_type)
	{
	case typeTrigger:
		return 120 - (114 * ((*m_data * (255 - m_thrz) / 255) + m_thrz)) / 255;
	case typeAxis:
		return (*m_data - 133 > 0) ? (120 - (114 * max(0, (*m_data - 133))) / 122) : 0;
	case typeAxisInv:
		return (122 - *m_data > 0) ? (120 - (114 * max(0, (122 - *m_data))) / 122) : 0;
	case typeConstant:
	case typeButton:
	case typeTouch:
	case typeDPadUP:
	case typeDPadRIGHT:
	case typeDPadDOWN:
	case typeDPadLEFT:
	case typeAxisLU:
	case typeAxisRD:
	case typeAxisDUL:
	case typeAxisDUR:
	case typeAxisDDR:
	case typeAxisDDL:
		return 10;
	case typeSimultaneous:
	case typeDPad:
	case typeData:
		return 0;
	default:
		return 0;
	}
}

WCHAR* dsButton::String(ButtonID id)
{
	switch (id)
	{
	case none: return L"";
	case LX: return I18N.Button_LX;
	case LY: return I18N.Button_LY;
	case RX: return I18N.Button_RX;
	case RY: return I18N.Button_RY;
	case L3: return I18N.Button_L3;
	case DPAD_LEFT: return I18N.Button_DPAD_LEFT;
	case DPAD_UP: return I18N.Button_DPAD_UP;
	case DPAD_RIGHT: return I18N.Button_DPAD_RIGHT;
	case DPAD_DOWN: return I18N.Button_DPAD_DOWN;
	case SHARE: return I18N.Button_SHARE;
	case OPTIONS: return I18N.Button_OPTIONS;
	case SQUARE: return I18N.Button_SQUARE;
	case TRIANGLE: return I18N.Button_TRIANGLE;
	case CIRCLE: return I18N.Button_CIRCLE;
	case CROSS: return I18N.Button_CROSS;
	case R3: return I18N.Button_R3;
	case PS: return I18N.Button_PS;
	case TOUCH: return I18N.Button_TOUCH;
	case MUTE: return I18N.Button_MUTE;
	case L1: return I18N.Button_L1;
	case R1: return I18N.Button_R1;
	case L2: return I18N.Button_L2;
	case R2: return I18N.Button_R2;
	case L2TRIGGER: return I18N.Button_L2TRIGGER;
	case R2TRIGGER: return I18N.Button_R2TRIGGER;
	case EMPTY: return I18N.Button_EMPTY;
	case MIDDLE: return I18N.Button_MIDDLE;
	case FULL: return I18N.Button_FULL;
	case LXINV: return I18N.Button_LX_INV;
	case LYINV: return I18N.Button_LY_INV;
	case RXINV: return I18N.Button_RX_INV;
	case RYINV: return I18N.Button_RY_INV;
	case AXISL_LEFT: return I18N.Button_AXISL_LEFT;
	case AXISL_UP_LEFT: return I18N.Button_AXISL_UP_LEFT;
	case AXISL_UP: return I18N.Button_AXISL_UP;
	case AXISL_UP_RIGHT: return I18N.Button_AXISL_UP_RIGHT;
	case AXISL_RIGHT: return I18N.Button_AXISL_RIGHT;
	case AXISL_DOWN_RIGHT: return I18N.Button_AXISL_DOWN_RIGHT;
	case AXISL_DOWN: return I18N.Button_AXISL_DOWN;
	case AXISL_DOWN_LEFT: return I18N.Button_AXISL_DOWN_LEFT;
	case AXISR_LEFT: return I18N.Button_AXISR_LEFT;
	case AXISR_UP_LEFT: return I18N.Button_AXISR_UP_LEFT;
	case AXISR_UP: return I18N.Button_AXISR_UP;
	case AXISR_UP_RIGHT: return I18N.Button_AXISR_UP_RIGHT;
	case AXISR_RIGHT: return I18N.Button_AXISR_RIGHT;
	case AXISR_DOWN_RIGHT: return I18N.Button_AXISR_DOWN_RIGHT;
	case AXISR_DOWN: return I18N.Button_AXISR_DOWN;
	case AXISR_DOWN_LEFT: return I18N.Button_AXISR_DOWN_LEFT;
	case TOUCHUP: return I18N.Button_TOUCH_UP;
	case TOUCHPAD: return I18N.Button_TOUCHPAD;
	case TOUCH1: return I18N.Button_TOUCH_1;
	case TOUCH2: return I18N.Button_TOUCH_2;
	case TOUCH3: return I18N.Button_TOUCH_3;
	case TOUCH4: return I18N.Button_TOUCH_4;
	case TOUCHL: return I18N.Button_TOUCH_L;
	case TOUCHR: return I18N.Button_TOUCH_R;
	case L2TRIGGER_33: return I18N.Button_L2TRIGGER_33;
	case R2TRIGGER_33: return I18N.Button_R2TRIGGER_33;
	case L2TRIGGER_66: return I18N.Button_L2TRIGGER_66;
	case R2TRIGGER_66: return I18N.Button_R2TRIGGER_66;
	case L2TRIGGER_100: return I18N.Button_L2TRIGGER_100;
	case R2TRIGGER_100: return I18N.Button_R2TRIGGER_100;
	case L1R1: return I18N.Button_L1R1;
	case L2R2: return I18N.Button_L2R2;
	case BATTERY: return I18N.Button_BATTERY;
	default: return L"???";
	}
}
