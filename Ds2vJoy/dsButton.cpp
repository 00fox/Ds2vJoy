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

WCHAR* dsButton::String(ButtonID id)
{
	switch (id)
	{
	case none: return WCHARI(L"");
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
	case MOUSE_AXEX: return WCHARI(L"MOUSEAXEX");
	case MOUSE_AXEY: return WCHARI(L"MOUSEAXEY");
	case MOUSE_LEFT: return WCHARI(L"MOUSELEFT");
	case MOUSE_RIGHT: return WCHARI(L"MOUSERIGHT");
	case MOUSE_UP: return WCHARI(L"MOUSEUP");
	case MOUSE_DOWN: return WCHARI(L"MOUSEDOWN");
	case KID_LBUTTON: return WCHARI(L"LBUTTON");
	case KID_MBUTTON: return WCHARI(L"MBUTTON");
	case KID_RBUTTON: return WCHARI(L"RBUTTON");
	case KID_XBUTTON1: return WCHARI(L"XBUTTON1");
	case KID_XBUTTON2: return WCHARI(L"XBUTTON2");
	case KID_F1: return WCHARI(L"F1");
	case KID_F2: return WCHARI(L"F2");
	case KID_F3: return WCHARI(L"F3");
	case KID_F4: return WCHARI(L"F4");
	case KID_F5: return WCHARI(L"F5");
	case KID_F6: return WCHARI(L"F6");
	case KID_F7: return WCHARI(L"F7");
	case KID_F8: return WCHARI(L"F8");
	case KID_F9: return WCHARI(L"F9");
	case KID_F10: return WCHARI(L"F10");
	case KID_F11: return WCHARI(L"F11");
	case KID_F12: return WCHARI(L"F12");
	case KID_0: return WCHARI(L"0");
	case KID_1: return WCHARI(L"1");
	case KID_2: return WCHARI(L"2");
	case KID_3: return WCHARI(L"3");
	case KID_4: return WCHARI(L"4");
	case KID_5: return WCHARI(L"5");
	case KID_6: return WCHARI(L"6");
	case KID_7: return WCHARI(L"7");
	case KID_8: return WCHARI(L"8");
	case KID_9: return WCHARI(L"9");
	case KID_OEM_MINUS: return WCHARI(L"OEM_MINUS");
	case KID_OEM_PLUS: return WCHARI(L"OEM_PLUS");
	case KID_OEM_1: return WCHARI(L"OEM_1");
	case KID_OEM_2: return WCHARI(L"OEM_2");
	case KID_OEM_3: return WCHARI(L"OEM_3");
	case KID_OEM_4: return WCHARI(L"OEM_4");
	case KID_OEM_5: return WCHARI(L"OEM_5");
	case KID_OEM_6: return WCHARI(L"OEM_6");
	case KID_OEM_7: return WCHARI(L"OEM_7");
	case KID_OEM_8: return WCHARI(L"OEM_8");
	case KID_OEM_102: return WCHARI(L"OEM_102");
	case KID_OEM_COMMA: return WCHARI(L"OEM_COMMA");
	case KID_OEM_PERIOD: return WCHARI(L"OEM_PERIOD");
	case KID_A: return WCHARI(L"A");
	case KID_B: return WCHARI(L"B");
	case KID_C: return WCHARI(L"C");
	case KID_D: return WCHARI(L"D");
	case KID_E: return WCHARI(L"E");
	case KID_F: return WCHARI(L"F");
	case KID_G: return WCHARI(L"G");
	case KID_H: return WCHARI(L"H");
	case KID_I: return WCHARI(L"I");
	case KID_J: return WCHARI(L"J");
	case KID_K: return WCHARI(L"K");
	case KID_L: return WCHARI(L"L");
	case KID_M: return WCHARI(L"M");
	case KID_N: return WCHARI(L"N");
	case KID_O: return WCHARI(L"O");
	case KID_P: return WCHARI(L"P");
	case KID_Q: return WCHARI(L"Q");
	case KID_R: return WCHARI(L"R");
	case KID_S: return WCHARI(L"S");
	case KID_T: return WCHARI(L"T");
	case KID_U: return WCHARI(L"U");
	case KID_V: return WCHARI(L"V");
	case KID_W: return WCHARI(L"W");
	case KID_X: return WCHARI(L"X");
	case KID_Y: return WCHARI(L"Y");
	case KID_Z: return WCHARI(L"Z");
	case KID_ESCAPE: return WCHARI(L"ESCAPE");
	case KID_TAB: return WCHARI(L"TAB");
	case KID_RETURN: return WCHARI(L"RETURN");
	case KID_SPACE: return WCHARI(L"SPACE");
	case KID_BACK: return WCHARI(L"BACK");
	case KID_DELETE: return WCHARI(L"DELETE");
	case KID_INSERT: return WCHARI(L"INSERT");
	case KID_NUMLOCK: return WCHARI(L"NUMLOCK");
	case KID_LSHIFT: return WCHARI(L"LSHIFT");
	case KID_RSHIFT: return WCHARI(L"RSHIFT");
	case KID_LCONTROL: return WCHARI(L"LCONTROL");
	case KID_RCONTROL: return WCHARI(L"RCONTROL");
	case KID_LWIN: return WCHARI(L"LWIN");
	case KID_RWIN: return WCHARI(L"RWIN");
	case KID_LMENU: return WCHARI(L"LMENU");
	case KID_RMENU: return WCHARI(L"RMENU");
	case KID_LEFT: return WCHARI(L"LEFT");
	case KID_UP: return WCHARI(L"UP");
	case KID_RIGHT: return WCHARI(L"RIGHT");
	case KID_DOWN: return WCHARI(L"DOWN");
	case KID_PRIOR: return WCHARI(L"PRIOR");
	case KID_NEXT: return WCHARI(L"NEXT");
	case KID_END: return WCHARI(L"END");
	case KID_HOME: return WCHARI(L"HOME");
	case KID_NUMPAD0: return WCHARI(L"NUMPAD0");
	case KID_NUMPAD1: return WCHARI(L"NUMPAD1");
	case KID_NUMPAD2: return WCHARI(L"NUMPAD2");
	case KID_NUMPAD3: return WCHARI(L"NUMPAD3");
	case KID_NUMPAD4: return WCHARI(L"NUMPAD4");
	case KID_NUMPAD5: return WCHARI(L"NUMPAD5");
	case KID_NUMPAD6: return WCHARI(L"NUMPAD6");
	case KID_NUMPAD7: return WCHARI(L"NUMPAD7");
	case KID_NUMPAD8: return WCHARI(L"NUMPAD8");
	case KID_NUMPAD9: return WCHARI(L"NUMPAD9");
	case KID_DIVIDE: return WCHARI(L"DIVIDE");
	case KID_MULTIPLY: return WCHARI(L"MULTIPLY");
	case KID_SUBTRACT: return WCHARI(L"SUBTRACT");
	case KID_ADD: return WCHARI(L"ADD");
	case KID_SEPARATOR: return WCHARI(L"SEPARATOR");
	case KID_DECIMAL: return WCHARI(L"DECIMAL");
	default: return WCHARI(L"???");
	}
}
