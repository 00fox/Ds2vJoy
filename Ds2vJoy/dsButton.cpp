#include "stdafx.h"
#include "dsButton.h"

dsButton::dsButton()
{
}

dsButton::~dsButton()
{
}

void dsButton::setConstant(byte data)
{
	m_type = Type_Constant;
	m_constant = data;
}

void dsButton::setButton(byte* data, unsigned int bitmask, bool onlyds5)
{
	m_type = Type_Button;
	m_data = data;
	m_mask = bitmask;
	m_onlyds5 = onlyds5;
}

void dsButton::setTrigger(byte* data, int threshold)
{
	m_type = Type_Trigger;
	m_data = data;
	m_thrz = threshold;
}

void dsButton::setSimultaneous(byte* data, unsigned int bitmask, byte* data2, unsigned int bitmask2)
{
	m_type = Type_Simultaneous;
	m_data = data;
	m_data2 = data2;
	m_mask = bitmask;
	m_mask2 = bitmask2;
}

void dsButton::setTouch(byte* data, unsigned int bitmask, int box)
{
	m_type = Type_Touch;
	m_data = data;
	m_box = box;
	m_mask = bitmask;
}

void dsButton::setDPad(byte* data, ButtonType type)
{
	m_type = type;
	m_data = data;
}

void dsButton::setAxis(byte* data, byte* data2, unsigned char axis)
{
	m_type = Type_Axis;
	m_data = data;
	m_data2 = data2;
	m_axis = axis;
}

void dsButton::setAxisSniper(byte* data, byte* data2)
{
	m_type = Type_AxisSniper;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisInv(byte* data, byte* data2, unsigned char axis)
{
	m_type = Type_AxisInv;
	m_data = data;
	m_data2 = data2;
	m_axis = axis;
}

void dsButton::setAxisTriggerLU(byte* data)
{
	m_type = Type_AxisTriggerLU;
	m_data = data;
}

void dsButton::setAxisTriggerRD(byte* data)
{
	m_type = Type_AxisTriggerRD;
	m_data = data;
}

void dsButton::setAxisLU(byte* data)
{
	m_type = Type_AxisLU;
	m_data = data;
}

void dsButton::setAxisRD(byte* data)
{
	m_type = Type_AxisRD;
	m_data = data;
}

void dsButton::setAxisDUL(byte* data, byte* data2)
{
	m_type = Type_AxisDUL;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisDUR(byte* data, byte* data2)
{
	m_type = Type_AxisDUR;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisDDR(byte* data, byte* data2)
{
	m_type = Type_AxisDDR;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setAxisDDL(byte* data, byte* data2)
{
	m_type = Type_AxisDDL;
	m_data = data;
	m_data2 = data2;
}

void dsButton::setData(byte* data, unsigned int bitmask)
{
	m_type = Type_Data;
	m_data = data;
	m_mask = bitmask;
}

void dsButton::SetTouch(int box, byte value)
{
	TouchAble[box] = value;
}

void dsButton::SetMouseTrigger(byte* data)
{
	m_type = Type_MouseTrigger;
	m_data = data;
}

void dsButton::SetMouseAxis(byte* data)
{
	m_type = Type_MouseAxis;
	m_data = data;
}

void dsButton::SetKeyboard(byte* data, unsigned int bitmask)
{
	m_type = Type_Keyboard;
	m_data = data;
	m_mask = bitmask;
}

BOOL dsButton::isPushed()
{
	switch (m_type)
	{
	case Type_Constant: return TRUE;
	case Type_Data: return TRUE;
	}

	if (tape.PreferredDS)
	{
		switch (m_type)
		{
		case Type_Button:
		{
			if (m_onlyds5 && tape.PreferredDS != 2)
				return FALSE;
			else
				return (*m_data & m_mask);
		}
		case Type_Trigger: return (*m_data > m_thrz);
		case Type_Simultaneous:
		{
			if (!(*m_data & m_mask) && !(*m_data2 & m_mask2))
			{
				L2R2_Delay_On = 0;
				L2R2_Eligible = 1;
				L2R2_Pushed = 0;
				if (OrangeLedActive)
				{
					OrangeLedActive = 0;
					PostMessage(tape.Ds2hWnd, WM_SETORANGELED, 0, 0);
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
						PostMessage(tape.Ds2hWnd, WM_SETORANGELED, 1, 0);
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
		}
		case Type_Touch:
		{
			switch (m_box)
			{
			case 0: return TouchAble[0] && (*m_data & m_mask);
			case 1: return TouchAble[1] && (*m_data & m_mask);
			case 2: return TouchAble[2] && (*m_data & m_mask);
			case 3: return TouchAble[3] && (*m_data & m_mask);
			case 4: return TouchAble[4] && (*m_data & m_mask);
			case 5: return TouchAble[5] && (*m_data & m_mask);
			case 6: return TouchAble[6] && (*m_data & m_mask);
			case 7: return (*m_data & m_mask) ? 0xFF : 0;
			case 8: return !TouchAble[0] && (*m_data & m_mask);
			default: return FALSE;
			}
		}
		case Type_DPad: return (*m_data & 0xF) != 8;
		case Type_DPadUP: { dpad = (*m_data & 0xF); return (dpad == 7 || dpad == 0 || dpad == 1); }
		case Type_DPadRIGHT: { dpad = (*m_data & 0xF); return (dpad == 1 || dpad == 2 || dpad == 3); }
		case Type_DPadDOWN: { dpad = (*m_data & 0xF); return (dpad == 3 || dpad == 4 || dpad == 5); }
		case Type_DPadLEFT: { dpad = (*m_data & 0xF); return (dpad == 5 || dpad == 6 || dpad == 7); }
		case Type_Axis:
		case Type_AxisInv: return (((*m_data - 127) * (*m_data - 127)) + ((*m_data2 - 127) * (*m_data2 - 127))) > ((threshold[m_axis]) ? tape.Threshold * tape.Threshold : 0);
		case Type_AxisSniper: return (((*m_data - 127) * (*m_data - 127)) + ((*m_data2 - 127) * (*m_data2 - 127))) > 9;
		case Type_AxisTriggerRD:
		case Type_AxisTriggerLU: return ((*m_data - 127) * (*m_data - 127)) > (tape.Threshold * tape.Threshold);
		case Type_AxisLU: return (*m_data < 5);
		case Type_AxisRD: return (*m_data > 250);
		case Type_AxisDUL: return (*m_data < 20 && *m_data2 < 20);
		case Type_AxisDUR: return (*m_data < 20 && *m_data2 > 235);
		case Type_AxisDDR: return (*m_data > 235 && *m_data2 > 235);
		case Type_AxisDDL: return (*m_data > 235 && *m_data2 < 20);
		}
	}

	if (tape.KeyboardActive || tape.KeyboardActivetmp)
		switch (m_type)
		{
		case Type_Keyboard: return (*m_data & m_mask);
		}

	if (tape.MouseActive || tape.MouseActivetmp)
		switch (m_type)
		{
		case Type_MouseTrigger: return *m_data > tape.Threshold;
		case Type_MouseAxis: return ((*m_data - 127) * (*m_data - 127)) > (tape.Threshold * tape.Threshold);
		}

	return FALSE;
}

//In the range of 0x00 to 0xFF
BYTE dsButton::GetVal()
{
	switch (m_type)
	{
	case Type_Constant: return m_constant;
	case Type_Data: return (BYTE)((*m_data & m_mask) * 25.5);
	}

	if (tape.PreferredDS)
	{
		switch (m_type)
		{
		case Type_Button:
		{
			if (m_onlyds5 && tape.PreferredDS != 2)
				return 0;
			else
				return (abs(*m_data) & m_mask) ? 0xFF : 0;
		}
		case Type_Trigger: return (*m_data * (255 + m_thrz) / 255) - m_thrz;
		case Type_Simultaneous: return isPushed() ? 0xFF : 0;
		case Type_Touch:
		{
			switch (m_box)
			{
			case 0: return (TouchAble[0] && (*m_data & m_mask)) ? 0xFF : 0;
			case 1: return (TouchAble[1] && (*m_data & m_mask)) ? 0xFF : 0;
			case 2: return (TouchAble[2] && (*m_data & m_mask)) ? 0xFF : 0;
			case 3: return (TouchAble[3] && (*m_data & m_mask)) ? 0xFF : 0;
			case 4: return (TouchAble[4] && (*m_data & m_mask)) ? 0xFF : 0;
			case 5: return (TouchAble[5] && (*m_data & m_mask)) ? 0xFF : 0;
			case 6: return (TouchAble[6] && (*m_data & m_mask)) ? 0xFF : 0;
			case 7: return (*m_data & m_mask) ? 0xFF : 0;
			case 8: return (!TouchAble[0] && (*m_data & m_mask)) ? 0xFF : 0;
			}
			return 0;
		}
		case Type_DPad: return *m_data & 0xF;
		case Type_DPadUP: { dpad = (*m_data & 0xF); return (dpad == 7 || dpad == 0 || dpad == 1) ? 0xFF : 0; }
		case Type_DPadRIGHT: { dpad = (*m_data & 0xF); return (dpad == 1 || dpad == 2 || dpad == 3) ? 0xFF : 0; }
		case Type_DPadDOWN: { dpad = (*m_data & 0xF); return (dpad == 3 || dpad == 4 || dpad == 5) ? 0xFF : 0; }
		case Type_DPadLEFT: { dpad = (*m_data & 0xF); return (dpad == 5 || dpad == 6 || dpad == 7) ? 0xFF : 0; }
		case Type_Axis:
		{
			if (tape.Threshold && threshold[m_axis])
				return (*m_data > 127 + tape.Threshold) ? (127 + (((*m_data - 127 - tape.Threshold) * 128) / (128 - tape.Threshold))) :
				((*m_data < 128 - tape.Threshold) ? ((*m_data * 128) / (128 - tape.Threshold)) : 127);
			else
				return *m_data;
		}
		case Type_AxisInv:
		{
			if (tape.Threshold && threshold[m_axis])
				return 255 - ((*m_data > 127 + tape.Threshold) ? (127 + (((*m_data - 127 - tape.Threshold) * 128) / (128 - tape.Threshold))) :
					((*m_data < 128 - tape.Threshold) ? ((*m_data * 128) / (128 - tape.Threshold)) : 127));
			else
				return 255 - *m_data;
		}
		case Type_AxisSniper: return (*m_data - 85) % 255;
		case Type_AxisTriggerLU: return (*m_data < 127) ? (((127 - *m_data - tape.Threshold) * 256) / (128 - tape.Threshold)) : 0;
		case Type_AxisTriggerRD: return (*m_data > 127) ? (((*m_data - 128 - tape.Threshold) * 256) / (128 - tape.Threshold)) : 0;
		case Type_AxisLU: return (*m_data < 5) ? 0xFF : 0;
		case Type_AxisRD: return (*m_data > 250) ? 0xFF : 0;
		case Type_AxisDUL: return (*m_data < 20 && *m_data2 < 20) ? 0xFF : 0;
		case Type_AxisDUR: return (*m_data < 20 && *m_data2 > 235) ? 0xFF : 0;
		case Type_AxisDDR: return (*m_data > 235 && *m_data2 > 235) ? 0xFF : 0;
		case Type_AxisDDL: return (*m_data > 235 && *m_data2 < 20) ? 0xFF : 0;
		}
	}

	if (tape.KeyboardActive || tape.KeyboardActivetmp)
		switch (m_type)
		{
		case Type_Keyboard: return (*m_data & m_mask) ? 0xFF : 0;
		}

	if (tape.MouseActive || tape.MouseActivetmp)
		switch (m_type)
		{
		case Type_MouseTrigger: return (*m_data * (255 + m_thrz) / 255) - m_thrz;
		case Type_MouseAxis: return (*m_data > 127 + tape.Threshold) ? (127 + (((*m_data - 127 - tape.Threshold) * 128) / (128 - tape.Threshold))) :
									((*m_data < 128 - tape.Threshold) ? ((*m_data * 128) / (128 - tape.Threshold)) : 127);
		}

	return GetReleasedVal();
}

BYTE dsButton::GetReleasedVal()
{
	switch (m_type)
	{
	case Type_Axis:
	case Type_AxisSniper:
	case Type_AxisInv:
	case Type_MouseAxis: return 127;
	case Type_AxisTriggerLU:
	case Type_AxisTriggerRD:
	case Type_Button:
	case Type_Trigger:
	case Type_Simultaneous:
	case Type_Touch:
	case Type_DPadUP:
	case Type_DPadRIGHT:
	case Type_DPadDOWN:
	case Type_DPadLEFT:
	case Type_AxisLU:
	case Type_AxisRD:
	case Type_AxisDUL:
	case Type_AxisDUR:
	case Type_AxisDDR:
	case Type_AxisDDL:
	case Type_Data:
	case Type_MouseTrigger:
	case Type_Keyboard: return 0;
	case Type_Constant: return m_constant;
	case Type_DPad: return (*m_data & 0xF0) | 8;
	default: return 0;
	}
}

int dsButton::GetScrollVal()
{
	if (tape.PreferredDS)
	{
		switch (m_type)
		{
		case Type_Trigger: return 120 - (114 * ((*m_data * (255 - m_thrz) / 255) + m_thrz)) / 255;
		case Type_Axis:
		case Type_AxisSniper: return (*m_data - 133 > 0) ? (120 - (114 * max(0, (*m_data - 133))) / 122) : 0;
		case Type_AxisTriggerLU: return 120 - (114 * (((127 - *m_data) * 2 * (255 - tape.Threshold) / 255) + tape.Threshold)) / 255;
		case Type_AxisTriggerRD: return 120 - (114 * (((*m_data - 127) * 2 * (255 - tape.Threshold) / 255) + tape.Threshold)) / 255;
		case Type_AxisInv: return (122 - *m_data > 0) ? (120 - (114 * max(0, (122 - *m_data))) / 122) : 0;
		case Type_Constant:
		case Type_Button:
		case Type_Touch:
		case Type_DPadUP:
		case Type_DPadRIGHT:
		case Type_DPadDOWN:
		case Type_DPadLEFT:
		case Type_AxisLU:
		case Type_AxisRD:
		case Type_AxisDUL:
		case Type_AxisDUR:
		case Type_AxisDDR:
		case Type_AxisDDL: return -1;
		}
	}

	if (tape.KeyboardActive || tape.KeyboardActivetmp)
		switch (m_type)
		{
		case Type_Keyboard: return -1;
		}

	if (tape.MouseActive || tape.MouseActivetmp)
		switch (m_type)
		{
		case Type_MouseTrigger: return 120 - (114 * ((*m_data * (255 - m_thrz) / 255) + m_thrz)) / 255;
		case Type_MouseAxis: return (*m_data - 133 > 0) ? (120 - (114 * max(0, (*m_data - 133))) / 122) : 0;
		}

	return 0;
}

void dsButton::SetThreshold(bool thr)
{
	if (m_axis > -1)
		threshold[m_axis] = thr;
}

const WCHAR* dsButton::String(ButtonID id)
{
	switch (id)
	{
	case none: return I18N.EMPTY;
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
	case SNIPER_LX: return I18N.Button_SNIPER_LX;
	case SNIPER_LY: return I18N.Button_SNIPER_LY;
	case SNIPER_RX: return I18N.Button_SNIPER_RX;
	case SNIPER_RY: return I18N.Button_SNIPER_RY;
	case AXISL_TR_LEFT: return I18N.Button_AXISL_TR_LEFT;
	case AXISL_TR_UP: return I18N.Button_AXISL_TR_UP;
	case AXISL_TR_RIGHT: return I18N.Button_AXISL_TR_RIGHT;
	case AXISL_TR_DOWN: return I18N.Button_AXISL_TR_DOWN;
	case AXISR_TR_LEFT: return I18N.Button_AXISR_TR_LEFT;
	case AXISR_TR_UP: return I18N.Button_AXISR_TR_UP;
	case AXISR_TR_RIGHT: return I18N.Button_AXISR_TR_RIGHT;
	case AXISR_TR_DOWN: return I18N.Button_AXISR_TR_DOWN;
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
	}

	static std::wstring dsButtonStringResult = L"";
	switch (id)
	{
	case MOUSE_AXEX: { dsButtonStringResult = L"MOUSEAXEX"; break; }
	case MOUSE_AXEY: { dsButtonStringResult = L"MOUSEAXEY"; break; }
	case MOUSE_LEFT: { dsButtonStringResult = L"MOUSELEFT"; break; }
	case MOUSE_RIGHT: { dsButtonStringResult = L"MOUSERIGHT"; break; }
	case MOUSE_UP: { dsButtonStringResult = L"MOUSEUP"; break; }
	case MOUSE_DOWN: { dsButtonStringResult = L"MOUSEDOWN"; break; }
	case KID_LBUTTON: { dsButtonStringResult = L"LBUTTON"; break; }
	case KID_MBUTTON: { dsButtonStringResult = L"MBUTTON"; break; }
	case KID_RBUTTON: { dsButtonStringResult = L"RBUTTON"; break; }
	case KID_XBUTTON1: { dsButtonStringResult = L"XBUTTON1"; break; }
	case KID_XBUTTON2: { dsButtonStringResult = L"XBUTTON2"; break; }
	case KID_F1: { dsButtonStringResult = L"F1"; break; }
	case KID_F2: { dsButtonStringResult = L"F2"; break; }
	case KID_F3: { dsButtonStringResult = L"F3"; break; }
	case KID_F4: { dsButtonStringResult = L"F4"; break; }
	case KID_F5: { dsButtonStringResult = L"F5"; break; }
	case KID_F6: { dsButtonStringResult = L"F6"; break; }
	case KID_F7: { dsButtonStringResult = L"F7"; break; }
	case KID_F8: { dsButtonStringResult = L"F8"; break; }
	case KID_F9: { dsButtonStringResult = L"F9"; break; }
	case KID_F10: { dsButtonStringResult = L"F10"; break; }
	case KID_F11: { dsButtonStringResult = L"F11"; break; }
	case KID_F12: { dsButtonStringResult = L"F12"; break; }
	case KID_0: { dsButtonStringResult = L"0"; break; }
	case KID_1: { dsButtonStringResult = L"1"; break; }
	case KID_2: { dsButtonStringResult = L"2"; break; }
	case KID_3: { dsButtonStringResult = L"3"; break; }
	case KID_4: { dsButtonStringResult = L"4"; break; }
	case KID_5: { dsButtonStringResult = L"5"; break; }
	case KID_6: { dsButtonStringResult = L"6"; break; }
	case KID_7: { dsButtonStringResult = L"7"; break; }
	case KID_8: { dsButtonStringResult = L"8"; break; }
	case KID_9: { dsButtonStringResult = L"9"; break; }
	case KID_OEM_MINUS: { dsButtonStringResult = L"OEM_MINUS"; break; }
	case KID_OEM_PLUS: { dsButtonStringResult = L"OEM_PLUS"; break; }
	case KID_OEM_1: { dsButtonStringResult = L"OEM_1"; break; }
	case KID_OEM_2: { dsButtonStringResult = L"OEM_2"; break; }
	case KID_OEM_3: { dsButtonStringResult = L"OEM_3"; break; }
	case KID_OEM_4: { dsButtonStringResult = L"OEM_4"; break; }
	case KID_OEM_5: { dsButtonStringResult = L"OEM_5"; break; }
	case KID_OEM_6: { dsButtonStringResult = L"OEM_6"; break; }
	case KID_OEM_7: { dsButtonStringResult = L"OEM_7"; break; }
	case KID_OEM_8: { dsButtonStringResult = L"OEM_8"; break; }
	case KID_OEM_102: { dsButtonStringResult = L"OEM_102"; break; }
	case KID_OEM_COMMA: { dsButtonStringResult = L"OEM_COMMA"; break; }
	case KID_OEM_PERIOD: { dsButtonStringResult = L"OEM_PERIOD"; break; }
	case KID_A: { dsButtonStringResult = L"A"; break; }
	case KID_B: { dsButtonStringResult = L"B"; break; }
	case KID_C: { dsButtonStringResult = L"C"; break; }
	case KID_D: { dsButtonStringResult = L"D"; break; }
	case KID_E: { dsButtonStringResult = L"E"; break; }
	case KID_F: { dsButtonStringResult = L"F"; break; }
	case KID_G: { dsButtonStringResult = L"G"; break; }
	case KID_H: { dsButtonStringResult = L"H"; break; }
	case KID_I: { dsButtonStringResult = L"I"; break; }
	case KID_J: { dsButtonStringResult = L"J"; break; }
	case KID_K: { dsButtonStringResult = L"K"; break; }
	case KID_L: { dsButtonStringResult = L"L"; break; }
	case KID_M: { dsButtonStringResult = L"M"; break; }
	case KID_N: { dsButtonStringResult = L"N"; break; }
	case KID_O: { dsButtonStringResult = L"O"; break; }
	case KID_P: { dsButtonStringResult = L"P"; break; }
	case KID_Q: { dsButtonStringResult = L"Q"; break; }
	case KID_R: { dsButtonStringResult = L"R"; break; }
	case KID_S: { dsButtonStringResult = L"S"; break; }
	case KID_T: { dsButtonStringResult = L"T"; break; }
	case KID_U: { dsButtonStringResult = L"U"; break; }
	case KID_V: { dsButtonStringResult = L"V"; break; }
	case KID_W: { dsButtonStringResult = L"W"; break; }
	case KID_X: { dsButtonStringResult = L"X"; break; }
	case KID_Y: { dsButtonStringResult = L"Y"; break; }
	case KID_Z: { dsButtonStringResult = L"Z"; break; }
	case KID_ESCAPE: { dsButtonStringResult = L"ESCAPE"; break; }
	case KID_TAB: { dsButtonStringResult = L"TAB"; break; }
	case KID_RETURN: { dsButtonStringResult = L"RETURN"; break; }
	case KID_SPACE: { dsButtonStringResult = L"SPACE"; break; }
	case KID_BACK: { dsButtonStringResult = L"BACK"; break; }
	case KID_DELETE: { dsButtonStringResult = L"DELETE"; break; }
	case KID_INSERT: { dsButtonStringResult = L"INSERT"; break; }
	case KID_NUMLOCK: { dsButtonStringResult = L"NUMLOCK"; break; }
	case KID_LSHIFT: { dsButtonStringResult = L"LSHIFT"; break; }
	case KID_RSHIFT: { dsButtonStringResult = L"RSHIFT"; break; }
	case KID_LCONTROL: { dsButtonStringResult = L"LCONTROL"; break; }
	case KID_RCONTROL: { dsButtonStringResult = L"RCONTROL"; break; }
	case KID_LWIN: { dsButtonStringResult = L"LWIN"; break; }
	case KID_RWIN: { dsButtonStringResult = L"RWIN"; break; }
	case KID_LMENU: { dsButtonStringResult = L"LMENU"; break; }
	case KID_RMENU: { dsButtonStringResult = L"RMENU"; break; }
	case KID_LEFT: { dsButtonStringResult = L"LEFT"; break; }
	case KID_UP: { dsButtonStringResult = L"UP"; break; }
	case KID_RIGHT: { dsButtonStringResult = L"RIGHT"; break; }
	case KID_DOWN: { dsButtonStringResult = L"DOWN"; break; }
	case KID_PRIOR: { dsButtonStringResult = L"PRIOR"; break; }
	case KID_NEXT: { dsButtonStringResult = L"NEXT"; break; }
	case KID_END: { dsButtonStringResult = L"END"; break; }
	case KID_HOME: { dsButtonStringResult = L"HOME"; break; }
	case KID_NUMPAD0: { dsButtonStringResult = L"NUMPAD0"; break; }
	case KID_NUMPAD1: { dsButtonStringResult = L"NUMPAD1"; break; }
	case KID_NUMPAD2: { dsButtonStringResult = L"NUMPAD2"; break; }
	case KID_NUMPAD3: { dsButtonStringResult = L"NUMPAD3"; break; }
	case KID_NUMPAD4: { dsButtonStringResult = L"NUMPAD4"; break; }
	case KID_NUMPAD5: { dsButtonStringResult = L"NUMPAD5"; break; }
	case KID_NUMPAD6: { dsButtonStringResult = L"NUMPAD6"; break; }
	case KID_NUMPAD7: { dsButtonStringResult = L"NUMPAD7"; break; }
	case KID_NUMPAD8: { dsButtonStringResult = L"NUMPAD8"; break; }
	case KID_NUMPAD9: { dsButtonStringResult = L"NUMPAD9"; break; }
	case KID_DIVIDE: { dsButtonStringResult = L"DIVIDE"; break; }
	case KID_MULTIPLY: { dsButtonStringResult = L"MULTIPLY"; break; }
	case KID_SUBTRACT: { dsButtonStringResult = L"SUBTRACT"; break; }
	case KID_ADD: { dsButtonStringResult = L"ADD"; break; }
	case KID_SEPARATOR: { dsButtonStringResult = L"SEPARATOR"; break; }
	case KID_DECIMAL: { dsButtonStringResult = L"DECIMAL"; break; }
	default: return I18N.WHICH;
	}
	return dsButtonStringResult.c_str();
}
