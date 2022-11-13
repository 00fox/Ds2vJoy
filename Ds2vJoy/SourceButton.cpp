#include "stdafx.h"
#include "SourceButton.h"

SourceButton::SourceButton()
{
}

SourceButton::~SourceButton()
{
}

void SourceButton::setConstant(unsigned short constant)
{
	m_type = Type_Constant;
	m_mask2 = constant;
}

void SourceButton::setButton(byte offset, unsigned short bitmask)
{
	m_type = Type_Button;
	m_offset = offset;
	m_mask = bitmask;
}

void SourceButton::setTrigger(byte offset, unsigned short threshold)
{
	m_type = Type_Trigger;
	m_offset = offset;
	m_mask = threshold;
}

void SourceButton::setSimultaneous(byte offset, unsigned short bitmask, byte offset2, unsigned short bitmask2, ButtonID bumper)
{
	m_type = Type_Simultaneous;
	m_offset = offset;
	m_offset2 = offset2;
	m_mask = bitmask;
	m_mask2 = bitmask2;
	m_btid = bumper;
}

void SourceButton::setTouch(byte offset, unsigned short bitmask, unsigned char box)
{
	m_type = Type_Touch;
	m_offset = offset;
	m_offset2 = box;
	m_mask = bitmask;
}

void SourceButton::setAxis(byte offset, byte offset2, AxisID axis)
{
	m_type = Type_Axis;
	m_offset = offset;
	m_offset2 = offset2;
	m_axis = axis;
}

void SourceButton::setAxisInv(byte offset, byte offset2, AxisID axis)
{
	m_type = Type_AxisInv;
	m_offset = offset;
	m_offset2 = offset2;
	m_axis = axis;
}

void SourceButton::setAxisSolo(byte offset, AxisID axis)
{
	m_type = Type_AxisSolo;
	m_offset = offset;
	m_axis = axis;
}

void SourceButton::setAxisInvSolo(byte offset, AxisID axis)
{
	m_type = Type_AxisInvSolo;
	m_offset = offset;
	m_axis = axis;
}

void SourceButton::setAxisSniper(byte offset, byte offset2)
{
	m_type = Type_AxisSniper;
	m_offset = offset;
	m_offset2 = offset2;
}

void SourceButton::setAxisTriggerLU(byte offset)
{
	m_type = Type_AxisTriggerLU;
	m_offset = offset;
}

void SourceButton::setAxisTriggerRD(byte offset)
{
	m_type = Type_AxisTriggerRD;
	m_offset = offset;
}

void SourceButton::setAxisLU(byte offset)
{
	m_type = Type_AxisLU;
	m_offset = offset;
}

void SourceButton::setAxisRD(byte offset)
{
	m_type = Type_AxisRD;
	m_offset = offset;
}

void SourceButton::setAxisDUL(byte offset, byte offset2)
{
	m_type = Type_AxisDUL;
	m_offset = offset;
	m_offset2 = offset2;
}

void SourceButton::setAxisDUR(byte offset, byte offset2)
{
	m_type = Type_AxisDUR;
	m_offset = offset;
	m_offset2 = offset2;
}

void SourceButton::setAxisDDR(byte offset, byte offset2)
{
	m_type = Type_AxisDDR;
	m_offset = offset;
	m_offset2 = offset2;
}

void SourceButton::setAxisDDL(byte offset, byte offset2)
{
	m_type = Type_AxisDDL;
	m_offset = offset;
	m_offset2 = offset2;
}

void SourceButton::setData(ButtonID batterytype)
{
	m_type = Type_Data;
	m_btid = batterytype;
}

void SourceButton::SetTouchBox(unsigned char box, bool value)
{
	TouchAble[box] = value;
}

BOOL SourceButton::isPushed()
{
	switch (m_type)
	{
	case Type_Constant: return TRUE;
	case Type_Data:
	{
		switch (m_btid)
		{
		case BATTERY: return (tape.BatteryLevel) ? TRUE : FALSE;
		case SISAXIS_STANCE:
		case SISAXIS_ZONE:
		case SISAXIS_WHEEL:
		case SISAXIS_QUARTER: return TRUE;
		case DS_SELECTED: return (tape.PreferredSource == 1 || tape.PreferredSource == 2) ? TRUE : FALSE;
		case DS4_SELECTED: return (tape.PreferredSource == 1) ? TRUE : FALSE;
		case DS5_SELECTED: return (tape.PreferredSource == 2) ? TRUE : FALSE;
		case DI_SELECTED: return (tape.PreferredSource == 3) ? TRUE : FALSE;
		case XI_SELECTED: return (tape.PreferredSource == 4) ? TRUE : FALSE;
		case INACTIVITY_5MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastButton) > std::chrono::minutes{5}) ? TRUE : FALSE;
		case INACTIVITY_10MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastButton) > std::chrono::minutes{10}) ? TRUE : FALSE;
		case INACTIVITY_15MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastButton) > std::chrono::minutes{15}) ? TRUE : FALSE;
		case INACTIVITY_30MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastButton) > std::chrono::minutes{30}) ? TRUE : FALSE;
		case NO_MOVEMENT_5MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastMove) > std::chrono::minutes{5}) ? TRUE : FALSE;
		case NO_MOVEMENT_10MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastMove) > std::chrono::minutes{10}) ? TRUE : FALSE;
		case NO_MOVEMENT_15MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastMove) > std::chrono::minutes{15}) ? TRUE : FALSE;
		case NO_MOVEMENT_30MN: return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - tape.lastMove) > std::chrono::minutes{30}) ? TRUE : FALSE;
		case BATTERY0: return (tape.BatteryLevel < 11) ? TRUE : FALSE;
		case BATTERY1: return (tape.BatteryLevel > 10 && tape.BatteryLevel < 21) ? TRUE : FALSE;
		case BATTERY2: return (tape.BatteryLevel > 20 && tape.BatteryLevel < 31) ? TRUE : FALSE;
		case BATTERY3: return (tape.BatteryLevel > 30 && tape.BatteryLevel < 41) ? TRUE : FALSE;
		case BATTERY4: return (tape.BatteryLevel > 40 && tape.BatteryLevel < 51) ? TRUE : FALSE;
		case BATTERY5: return (tape.BatteryLevel > 50 && tape.BatteryLevel < 61) ? TRUE : FALSE;
		case BATTERY6: return (tape.BatteryLevel > 60 && tape.BatteryLevel < 71) ? TRUE : FALSE;
		case BATTERY7: return (tape.BatteryLevel > 70 && tape.BatteryLevel < 81) ? TRUE : FALSE;
		case BATTERY8: return (tape.BatteryLevel > 80 && tape.BatteryLevel < 91) ? TRUE : FALSE;
		case BATTERY9: return (tape.BatteryLevel > 90) ? TRUE : FALSE;
		case SISAXIS_STANCE1:
		case SISAXIS_STANCE2:
		case SISAXIS_STANCE3:
		case SISAXIS_STANCE4:
		case SISAXIS_STANCE5: return (tape.Stance == byte(m_btid - SISAXIS_STANCE1)) ? TRUE : FALSE;
		case SISAXIS_ZONE1: return (tape.Zone == 0) ? TRUE : FALSE;
		case SISAXIS_ZONE2: return (tape.Zone == 1) ? TRUE : FALSE;
		case SISAXIS_ZONE3: return (tape.Zone == 1 || tape.Zone == 2) ? TRUE : FALSE;
		case SISAXIS_ZONE4: return (tape.Zone == 2) ? TRUE : FALSE;
		case SISAXIS_ZONE5: return (tape.Zone == 3) ? TRUE : FALSE;
		}
	}
	case Type_Button:
	{
		return (tape.ReceivedData[m_offset] & m_mask);
	}
	case Type_Trigger: return (tape.ReceivedData[m_offset] > m_mask);
	case Type_Simultaneous:
	{
		if (m_btid == SourceButton::L1R1)
		{
			if (!(tape.ReceivedData[m_offset] & m_mask) && !(tape.ReceivedData[m_offset2] & m_mask2))
			{
				L1R1_Delay_On = 0;
				L1R1_Eligible = 1;
				L1R1_Pushed = 0;
				if (OrangeLedActive)
				{
					OrangeLedActive = false;
					PostMessage(tape.Ds2hWnd, WM_SETORANGELED, 0, 0);
				}
				return FALSE;
			}
			else if (L1R1_Eligible)
			{
				if ((tape.ReceivedData[m_offset] & m_mask) && (tape.ReceivedData[m_offset2] & m_mask2))
				{
					L1R1_Eligible = 0;
					L1R1_Delay_On = 1;
					if (!OrangeLedActive)
					{
						OrangeLedActive = true;
						PostMessage(tape.Ds2hWnd, WM_SETORANGELED, 1, 0);
					}
					return TRUE;
				}
				else if ((tape.ReceivedData[m_offset] & m_mask) || (tape.ReceivedData[m_offset2] & m_mask2))
				{
					if (L1R1_Pushed)
					{
						if ((clock() - L1R1_LastTimePushed) > tape.Simultaneous / 10)
							L1R1_Eligible = 0;
					}
					else
					{
						L1R1_Pushed = 1;
						L1R1_LastTimePushed = clock();
					}
					return FALSE;
				}
			}
			else if (L1R1_Delay_On)
				return TRUE;
		}
		else
		{
			if (!(tape.ReceivedData[m_offset] & m_mask) && !(tape.ReceivedData[m_offset2] & m_mask2))
			{
				L2R2_Delay_On = 0;
				L2R2_Eligible = 1;
				L2R2_Pushed = 0;
				if (OrangeLedActive)
				{
					OrangeLedActive = false;
					PostMessage(tape.Ds2hWnd, WM_SETORANGELED, 0, 0);
				}
				return FALSE;
			}
			else if (L2R2_Eligible)
			{
				if ((tape.ReceivedData[m_offset] & m_mask) && (tape.ReceivedData[m_offset2] & m_mask2))
				{
					L2R2_Eligible = 0;
					L2R2_Delay_On = 1;
					if (!OrangeLedActive)
					{
						OrangeLedActive = true;
						PostMessage(tape.Ds2hWnd, WM_SETORANGELED, 1, 0);
					}
					return TRUE;
				}
				else if ((tape.ReceivedData[m_offset] & m_mask) || (tape.ReceivedData[m_offset2] & m_mask2))
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
		}
		return FALSE;
	}
	case Type_Touch:
	{
		switch (m_offset2)
		{
		case 0: return (TouchAble[0] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 1: return (TouchAble[1] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 2: return (TouchAble[2] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 3: return (TouchAble[3] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 4: return (TouchAble[4] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 5: return (TouchAble[5] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 6: return (TouchAble[6] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		case 7: return (tape.ReceivedData[m_offset] & m_mask) ? true : 0;
		case 8: return (!TouchAble[0] && (tape.ReceivedData[m_offset] & m_mask)) ? true : false;
		default: return FALSE;
		}
	}
	case Type_Axis:
	case Type_AxisInv: return (((tape.ReceivedData[m_offset] - 32767.5) * (tape.ReceivedData[m_offset] - 32767.5)) + ((tape.ReceivedData[m_offset2] - 32767.5) * (tape.ReceivedData[m_offset2] - 32767.5))) > ((threshold[m_axis] && m_axis != Axis_None) ? (tape.Threshold * tape.Threshold) : 0);
	case Type_AxisSolo:
	case Type_AxisInvSolo: return abs(tape.ReceivedData[m_offset] - 32767.5) > ((threshold[m_axis]) ? tape.Threshold : 0);
	case Type_AxisSniper: return (((tape.ReceivedData[m_offset] - 32767.5) * (tape.ReceivedData[m_offset] - 32767.5)) + ((tape.ReceivedData[m_offset2] - 32767.5) * (tape.ReceivedData[m_offset2] - 32767.5))) > 594441; //3-255
	case Type_AxisTriggerRD:
	case Type_AxisTriggerLU: return ((tape.ReceivedData[m_offset] - 32767.5) * (tape.ReceivedData[m_offset] - 32767.5)) > (tape.Threshold * tape.Threshold);
	case Type_AxisLU: return (tape.ReceivedData[m_offset] < 1285);
	case Type_AxisRD: return (tape.ReceivedData[m_offset] > 64250);
	case Type_AxisDUL: return (tape.ReceivedData[m_offset] < 13364 && tape.ReceivedData[m_offset2] < 13364);
	case Type_AxisDUR: return (tape.ReceivedData[m_offset] < 13364 && tape.ReceivedData[m_offset2] > 52171);
	case Type_AxisDDR: return (tape.ReceivedData[m_offset] > 52171 && tape.ReceivedData[m_offset2] > 52171);
	case Type_AxisDDL: return (tape.ReceivedData[m_offset] > 52171 && tape.ReceivedData[m_offset2] < 13364);
	}

	return FALSE;
}

unsigned short SourceButton::GetVal()
{
	switch (m_type)
	{
	case Type_Constant: return m_mask2;
	case Type_Data:
	{
		switch (m_btid)
		{
		case BATTERY: return min(65535, tape.BatteryLevel * 65535 / 100);
		case SISAXIS_STANCE: return tape.Stance * 257 * 63.75;
		case SISAXIS_ZONE: return tape.Zone * 257 * 63.75;
		case BATTERY0:
		case BATTERY1:
		case BATTERY2:
		case BATTERY3:
		case BATTERY4:
		case BATTERY5:
		case BATTERY6:
		case BATTERY7:
		case BATTERY8:
		case BATTERY9:
		case SISAXIS_STANCE1:
		case SISAXIS_STANCE2:
		case SISAXIS_STANCE3:
		case SISAXIS_STANCE4:
		case SISAXIS_STANCE5:
		case SISAXIS_ZONE1:
		case SISAXIS_ZONE2:
		case SISAXIS_ZONE3:
		case SISAXIS_ZONE4:
		case SISAXIS_ZONE5:
		case DS4_SELECTED:
		case DS5_SELECTED:
		case DI_SELECTED:
		case XI_SELECTED:
		case INACTIVITY_5MN:
		case INACTIVITY_10MN:
		case INACTIVITY_15MN:
		case INACTIVITY_30MN:
		case NO_MOVEMENT_5MN:
		case NO_MOVEMENT_10MN:
		case NO_MOVEMENT_15MN:
		case NO_MOVEMENT_30MN: return 65535;
		case SISAXIS_WHEEL: return tape.ReceivedData[Offset_WHEEL];
		case SISAXIS_QUARTER: return tape.ReceivedData[Offset_QUARTER];
		}
	}
	case Type_Button: return (tape.ReceivedData[m_offset] & m_mask) ? 65535 : 0;
	case Type_Trigger: return (tape.ReceivedData[m_offset] * (65535 + m_mask) / 65535) - m_mask;
	case Type_Simultaneous:
	case Type_Touch: 65535;
	case Type_AxisSniper:
	{
		return (tape.ReceivedData[m_offset] > 33538.5) ? (32767.5 + (((tape.ReceivedData[m_offset] - 33538.5) * 32767.5) / 31996.5)) :
			((tape.ReceivedData[m_offset] < 31996.5) ? ((tape.ReceivedData[m_offset] * 32767.5) / 31996.5) : 32767.5);
	}
	case Type_Axis:
	case Type_AxisSolo:
	{
		if (tape.Threshold && threshold[m_axis])
			return (tape.ReceivedData[m_offset] > 32767.5 + tape.Threshold) ? (32767.5 + (((tape.ReceivedData[m_offset] - 32767.5 - tape.Threshold) * 32767.5) / (32767.5 - tape.Threshold))) :
			((tape.ReceivedData[m_offset] < 32767.5 - tape.Threshold) ? ((tape.ReceivedData[m_offset] * 32767.5) / (32767.5 - tape.Threshold)) : 32767.5);
		else
			return tape.ReceivedData[m_offset];
	}
	case Type_AxisInv:
	case Type_AxisInvSolo:
	{
		if (tape.Threshold && threshold[m_axis])
			return 65535 - ((tape.ReceivedData[m_offset] > 32767.5 + tape.Threshold) ? (32767.5 + (((tape.ReceivedData[m_offset] - 32767.5 - tape.Threshold) * 32767.5) / (32767.5 - tape.Threshold))) :
				((tape.ReceivedData[m_offset] < 32767.5 - tape.Threshold) ? ((tape.ReceivedData[m_offset] * 32767.5) / (32767.5 - tape.Threshold)) : 32767.5));
		else
			return 65535 - tape.ReceivedData[m_offset];
	}
	case Type_AxisTriggerLU: return (tape.ReceivedData[m_offset] < 32767.5) ? (((32767.5 - tape.ReceivedData[m_offset] - tape.Threshold) * 65536) / (32767.5 - tape.Threshold)) : 0;
	case Type_AxisTriggerRD: return (tape.ReceivedData[m_offset] > 32767.5) ? (((tape.ReceivedData[m_offset] - 32767.5 - tape.Threshold) * 65536) / (32767.5 - tape.Threshold)) : 0;
	case Type_AxisLU: return (tape.ReceivedData[m_offset] < 1285) ? 65535 : 0;
	case Type_AxisRD: return (tape.ReceivedData[m_offset] > 64250) ? 65535 : 0;
	case Type_AxisDUL: return (tape.ReceivedData[m_offset] < 13364 && tape.ReceivedData[m_offset2] < 13364) ? 65535 : 0;
	case Type_AxisDUR: return (tape.ReceivedData[m_offset] < 13364 && tape.ReceivedData[m_offset2] > 52171) ? 65535 : 0;
	case Type_AxisDDR: return (tape.ReceivedData[m_offset] > 52171 && tape.ReceivedData[m_offset2] > 52171) ? 65535 : 0;
	case Type_AxisDDL: return (tape.ReceivedData[m_offset] > 52171 && tape.ReceivedData[m_offset2] < 13364) ? 65535 : 0;
	}

	return 0;
}

unsigned short SourceButton::GetReleasedVal()
{
	switch (m_type)
	{
	case Type_Axis:
	case Type_AxisInv:
	case Type_AxisSolo:
	case Type_AxisInvSolo:
	case Type_AxisSniper: return 32767.5;
	case Type_AxisTriggerLU:
	case Type_AxisTriggerRD:
	case Type_Button:
	case Type_Trigger:
	case Type_Simultaneous:
	case Type_Touch:
	case Type_AxisLU:
	case Type_AxisRD:
	case Type_AxisDUL:
	case Type_AxisDUR:
	case Type_AxisDDR:
	case Type_AxisDDL:
	case Type_Data: return 0;
	case Type_Constant: return m_mask2;
	//case Type_DPad: return (tape.ReceivedData[m_offset] & 0xF0) | 8;
	}

	return 0;
}

int SourceButton::GetScrollVal()
{
	switch (m_type)
	{
	case Type_Trigger: return 120 - (114 * (((tape.ReceivedData[m_offset] / 257) * (255 - (m_mask / 257)) / 255) + (m_mask / 257))) / 255;
	case Type_Axis:
	case Type_AxisSolo:
	case Type_AxisSniper: return ((tape.ReceivedData[m_offset] / 257) - 133 > 0) ? (120 - (114 * max(0, ((tape.ReceivedData[m_offset] / 257) - 133))) / 122) : 0;
	case Type_AxisTriggerLU: return 120 - (114 * (((127 - (tape.ReceivedData[m_offset] / 257)) * 2 * (65535 - tape.Threshold) / 65535) + (tape.Threshold / 257))) / 255;
	case Type_AxisTriggerRD: return 120 - (114 * ((((tape.ReceivedData[m_offset] / 257) - 127) * 2 * (65535 - tape.Threshold) / 65535) + (tape.Threshold / 257))) / 255;
	case Type_AxisInv:
	case Type_AxisInvSolo: return (122 - (tape.ReceivedData[m_offset] / 257) > 0) ? (120 - (114 * max(0, (122 - (tape.ReceivedData[m_offset] / 257)))) / 122) : 0;
	case Type_Button:
	case Type_Touch:
	case Type_AxisLU:
	case Type_AxisRD:
	case Type_AxisDUL:
	case Type_AxisDUR:
	case Type_AxisDDR:
	case Type_AxisDDL:
	case Type_Data:
	case Type_Constant: return -1;
	}

	return 0;
}

void SourceButton::SetThreshold(bool thr)
{
	threshold[char(m_axis)] = thr;
}

const WCHAR* SourceButton::String(ButtonID id)
{
	switch (id)
	{
	case Button_None: return I18N.EMPTY;
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
	case L2_TRIGGER: return I18N.Button_L2_TRIGGER;
	case R2_TRIGGER: return I18N.Button_R2_TRIGGER;
	case LX_INV: return I18N.Button_LX_INV;
	case LY_INV: return I18N.Button_LY_INV;
	case RX_INV: return I18N.Button_RX_INV;
	case RY_INV: return I18N.Button_RY_INV;
	case LX_SNIPER: return I18N.Button_LX_SNIPER;
	case LY_SNIPER: return I18N.Button_LY_SNIPER;
	case RX_SNIPER: return I18N.Button_RX_SNIPER;
	case RY_SNIPER: return I18N.Button_RY_SNIPER;
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
	case L2_TRIGGER_33: return I18N.Button_L2_TRIGGER_33;
	case R2_TRIGGER_33: return I18N.Button_R2_TRIGGER_33;
	case L2_TRIGGER_66: return I18N.Button_L2_TRIGGER_66;
	case R2_TRIGGER_66: return I18N.Button_R2_TRIGGER_66;
	case L2_TRIGGER_100: return I18N.Button_L2_TRIGGER_100;
	case R2_TRIGGER_100: return I18N.Button_R2_TRIGGER_100;
	case L1R1: return I18N.Button_L1R1;
	case L2R2: return I18N.Button_L2R2;
	case EMPTY: return I18N.Button_EMPTY;
	case MIDDLE: return I18N.Button_MIDDLE;
	case FULL: return I18N.Button_FULL;
	case QUARTER1: return I18N.Button_QUARTER1;
	case QUARTER2: return I18N.Button_QUARTER2;
	case THIRD1: return I18N.Button_THIRD1;
	case THIRD2: return I18N.Button_THIRD2;
	case TEN: return I18N.Button_TEN;
	case TWENTY: return I18N.Button_TWENTY;
	case THIRTY: return I18N.Button_THIRTY;
	case FORTY: return I18N.Button_FORTY;
	case SIXTY: return I18N.Button_SIXTY;
	case SEVENTY: return I18N.Button_SEVENTY;
	case EIGHTY: return I18N.Button_EIGHTY;
	case NINETY: return I18N.Button_NINETY;
	case BATTERY: return I18N.Button_BATTERY;
	case BATTERY0: return I18N.Button_BATTERY0;
	case BATTERY1: return I18N.Button_BATTERY1;
	case BATTERY2: return I18N.Button_BATTERY2;
	case BATTERY3: return I18N.Button_BATTERY3;
	case BATTERY4: return I18N.Button_BATTERY4;
	case BATTERY5: return I18N.Button_BATTERY5;
	case BATTERY6: return I18N.Button_BATTERY6;
	case BATTERY7: return I18N.Button_BATTERY7;
	case BATTERY8: return I18N.Button_BATTERY8;
	case BATTERY9: return I18N.Button_BATTERY9;
	case USB: return I18N.Button_USB;
	case EARS: return I18N.Button_EARS;
	case MIC: return I18N.Button_MIC;
	case BT: return I18N.Button_BT;
	case FINGER: return I18N.Button_FINGER;
	case FINGERS: return I18N.Button_FINGERS;
	case DS_SELECTED: return I18N.Button_DS_SELECTED;
	case DS4_SELECTED: return I18N.Button_DS4_SELECTED;
	case DS5_SELECTED: return I18N.Button_DS5_SELECTED;
	case DI_SELECTED: return I18N.Button_DI_SELECTED;
	case XI_SELECTED: return I18N.Button_XI_SELECTED;
	case DS_ACTIVE: return I18N.Button_DS_ACTIVE;
	case DS4_ACTIVE: return I18N.Button_DS4_ACTIVE;
	case DS5_ACTIVE: return I18N.Button_DS5_ACTIVE;
	case DI_ACTIVE: return I18N.Button_DI_ACTIVE;
	case KBD_ACTIVE: return I18N.Button_KBD_ACTIVE;
	case MSE_ACTIVE: return I18N.Button_MSE_ACTIVE;
	case MSE_DI_ACTIVE: return I18N.Button_MSE_DI_ACTIVE;
	case INACTIVITY_5MN: return I18N.Button_INACTIVITY_5MN;
	case INACTIVITY_10MN: return I18N.Button_INACTIVITY_10MN;
	case INACTIVITY_15MN: return I18N.Button_INACTIVITY_15MN;
	case INACTIVITY_30MN: return I18N.Button_INACTIVITY_30MN;
	case NO_MOVEMENT_5MN: return I18N.Button_NO_MOVEMENT_5MN;
	case NO_MOVEMENT_10MN: return I18N.Button_NO_MOVEMENT_10MN;
	case NO_MOVEMENT_15MN: return I18N.Button_NO_MOVEMENT_15MN;
	case NO_MOVEMENT_30MN: return I18N.Button_NO_MOVEMENT_30MN;
	case SLO: return I18N.Button_SLO;
	case SLO_INV: return I18N.Button_SLO_INV;
	case SLO_SNIPER: return I18N.Button_SLO_SNIPER;
	case SL1: return I18N.Button_SL1;
	case SL1_INV: return I18N.Button_SL1_INV;
	case SL1_SNIPER: return I18N.Button_SL1_SNIPER;
	case DI_X: return I18N.Button_DI_X;
	case DI_X_INV: return I18N.Button_DI_X_INV;
	case DI_X_TRIGGER: return I18N.Button_DI_X_TRIGGER;
	case DI_Y: return I18N.Button_DI_Y;
	case DI_Y_INV: return I18N.Button_DI_Y_INV;
	case DI_Y_TRIGGER: return I18N.Button_DI_Y_TRIGGER;
	case DI_Z: return I18N.Button_DI_Z;
	case DI_Z_INV: return I18N.Button_DI_Z_INV;
	case DI_Z_TRIGGER: return I18N.Button_DI_Z_TRIGGER;
	case DI_RX: return I18N.Button_DI_RX;
	case DI_RX_INV: return I18N.Button_DI_RX_INV;
	case DI_RX_TRIGGER: return I18N.Button_DI_RX_TRIGGER;
	case DI_RY: return I18N.Button_DI_RY;
	case DI_RY_INV: return I18N.Button_DI_RY_INV;
	case DI_RY_TRIGGER: return I18N.Button_DI_RY_TRIGGER;
	case DI_RZ: return I18N.Button_DI_RZ;
	case DI_RZ_INV: return I18N.Button_DI_RZ_INV;
	case DI_RZ_TRIGGER: return I18N.Button_DI_RZ_TRIGGER;
	case DI_SL0: return I18N.Button_DI_SL0;
	case DI_SL0_INV: return I18N.Button_DI_SL0_INV;
	case DI_SL0_TRIGGER: return I18N.Button_DI_SL0_TRIGGER;
	case DI_SL1: return I18N.Button_DI_SL1;
	case DI_SL1_INV: return I18N.Button_DI_SL1_INV;
	case DI_SL1_TRIGGER: return I18N.Button_DI_SL1_TRIGGER;
	case DPAD2_LEFT: return I18N.Button_DPAD2_LEFT;
	case DPAD2_UP: return I18N.Button_DPAD2_UP;
	case DPAD2_RIGHT: return I18N.Button_DPAD2_RIGHT;
	case DPAD2_DOWN: return I18N.Button_DPAD2_DOWN;
	case DPAD3_LEFT: return I18N.Button_DPAD3_LEFT;
	case DPAD3_UP: return I18N.Button_DPAD3_UP;
	case DPAD3_RIGHT: return I18N.Button_DPAD3_RIGHT;
	case DPAD3_DOWN: return I18N.Button_DPAD3_DOWN;
	case DPAD4_LEFT: return I18N.Button_DPAD4_LEFT;
	case DPAD4_UP: return I18N.Button_DPAD4_UP;
	case DPAD4_RIGHT: return I18N.Button_DPAD4_RIGHT;
	case DPAD4_DOWN: return I18N.Button_DPAD4_DOWN;
	case Sisaxis_None: return I18N.EMPTY;
	case SISAXIS_STANCE: return I18N.Button_STANCE;
	case SISAXIS_ZONE: return I18N.Button_ZONE;
	case SISAXIS_STANCE1: return I18N.Button_STANCE1;
	case SISAXIS_STANCE2: return I18N.Button_STANCE2;
	case SISAXIS_STANCE3: return I18N.Button_STANCE3;
	case SISAXIS_STANCE4: return I18N.Button_STANCE4;
	case SISAXIS_STANCE5: return I18N.Button_STANCE5;
	case SISAXIS_ZONE1: return I18N.Button_ZONE1;
	case SISAXIS_ZONE2: return I18N.Button_ZONE2;
	case SISAXIS_ZONE3: return I18N.Button_ZONE3;
	case SISAXIS_ZONE4: return I18N.Button_ZONE4;
	case SISAXIS_ZONE5: return I18N.Button_ZONE5;
	case SISAXIS_ROLL: return I18N.Button_ROLL;
	case SISAXIS_ROLL_INV: return I18N.Button_ROLL_INV;
	case SISAXIS_ROLL_TRIGGER: return I18N.Button_ROLL_TRIGGER;
	case SISAXIS_ROLL_CENTER: return I18N.Button_ROLL_CENTER;
	case SISAXIS_LEFT1: return I18N.Button_LEFT1;
	case SISAXIS_LEFT2: return I18N.Button_LEFT2;
	case SISAXIS_LEFT3: return I18N.Button_LEFT3;
	case SISAXIS_LEFT4: return I18N.Button_LEFT4;
	case SISAXIS_LEFT5: return I18N.Button_LEFT5;
	case SISAXIS_LEFT6: return I18N.Button_LEFT6;
	case SISAXIS_LEFT7: return I18N.Button_LEFT7;
	case SISAXIS_RIGHT: return I18N.Button_RIGHT;
	case SISAXIS_RIGHT1: return I18N.Button_RIGHT1;
	case SISAXIS_RIGHT2: return I18N.Button_RIGHT2;
	case SISAXIS_RIGHT3: return I18N.Button_RIGHT3;
	case SISAXIS_RIGHT4: return I18N.Button_RIGHT4;
	case SISAXIS_RIGHT5: return I18N.Button_RIGHT5;
	case SISAXIS_RIGHT6: return I18N.Button_RIGHT6;
	case SISAXIS_RIGHT7: return I18N.Button_RIGHT7;
	case SISAXIS_YAW: return I18N.Button_YAW;
	case SISAXIS_YAW_INV: return I18N.Button_YAW_INV;
	case SISAXIS_YAW_TRIGGER: return I18N.Button_YAW_TRIGGER;
	case SISAXIS_YAW_CENTER: return I18N.Button_YAW_CENTER;
	case SISAXIS_ANTI1: return I18N.Button_ANTI1;
	case SISAXIS_ANTI2: return I18N.Button_ANTI2;
	case SISAXIS_ANTI3: return I18N.Button_ANTI3;
	case SISAXIS_ANTI4: return I18N.Button_ANTI4;
	case SISAXIS_ANTI5: return I18N.Button_ANTI5;
	case SISAXIS_ANTI6: return I18N.Button_ANTI6;
	case SISAXIS_ANTI7: return I18N.Button_ANTI7;
	case SISAXIS_CLOCK: return I18N.Button_CLOCK;
	case SISAXIS_CLOCK1: return I18N.Button_CLOCK1;
	case SISAXIS_CLOCK2: return I18N.Button_CLOCK2;
	case SISAXIS_CLOCK3: return I18N.Button_CLOCK3;
	case SISAXIS_CLOCK4: return I18N.Button_CLOCK4;
	case SISAXIS_CLOCK5: return I18N.Button_CLOCK5;
	case SISAXIS_CLOCK6: return I18N.Button_CLOCK6;
	case SISAXIS_CLOCK7: return I18N.Button_CLOCK7;
	case SISAXIS_PITCH: return I18N.Button_PITCH;
	case SISAXIS_PITCH_INV: return I18N.Button_PITCH_INV;
	case SISAXIS_PITCH_TRIGGER: return I18N.Button_PITCH_TRIGGER;
	case SISAXIS_PITCH_CENTER: return I18N.Button_PITCH_CENTER;
	case SISAXIS_REAR1: return I18N.Button_REAR1;
	case SISAXIS_REAR2: return I18N.Button_REAR2;
	case SISAXIS_REAR3: return I18N.Button_REAR3;
	case SISAXIS_REAR4: return I18N.Button_REAR4;
	case SISAXIS_REAR5: return I18N.Button_REAR5;
	case SISAXIS_REAR6: return I18N.Button_REAR6;
	case SISAXIS_REAR7: return I18N.Button_REAR7;
	case SISAXIS_FORE: return I18N.Button_FORE;
	case SISAXIS_FORE1: return I18N.Button_FORE1;
	case SISAXIS_FORE2: return I18N.Button_FORE2;
	case SISAXIS_FORE3: return I18N.Button_FORE3;
	case SISAXIS_FORE4: return I18N.Button_FORE4;
	case SISAXIS_FORE5: return I18N.Button_FORE5;
	case SISAXIS_FORE6: return I18N.Button_FORE6;
	case SISAXIS_FORE7: return I18N.Button_FORE7;
	case SISAXIS_SIDEWARD: return I18N.Button_SIDEWARD;
	case SISAXIS_SIDEWARD_INV: return I18N.Button_SIDEWARD_INV;
	case SISAXIS_SIDEWARD_TRIGGER: return I18N.Button_SIDEWARD_TRIGGER;
	case SISAXIS_SIDEWARD_CENTER: return I18N.Button_SIDEWARD_CENTER;
	case SISAXIS_WEST1: return I18N.Button_WEST1;
	case SISAXIS_WEST2: return I18N.Button_WEST2;
	case SISAXIS_WEST3: return I18N.Button_WEST3;
	case SISAXIS_WEST4: return I18N.Button_WEST4;
	case SISAXIS_WEST5: return I18N.Button_WEST5;
	case SISAXIS_WEST6: return I18N.Button_WEST6;
	case SISAXIS_EAST: return I18N.Button_EAST;
	case SISAXIS_EAST1: return I18N.Button_EAST1;
	case SISAXIS_EAST2: return I18N.Button_EAST2;
	case SISAXIS_EAST3: return I18N.Button_EAST3;
	case SISAXIS_EAST4: return I18N.Button_EAST4;
	case SISAXIS_EAST5: return I18N.Button_EAST5;
	case SISAXIS_EAST6: return I18N.Button_EAST6;
	case SISAXIS_TOWARD: return I18N.Button_TOWARD;
	case SISAXIS_TOWARD_INV: return I18N.Button_TOWARD_INV;
	case SISAXIS_TOWARD_TRIGGER: return I18N.Button_TOWARD_TRIGGER;
	case SISAXIS_TOWARD_CENTER: return I18N.Button_TOWARD_CENTER;
	case SISAXIS_BACKWARD1: return I18N.Button_BACKWARD1;
	case SISAXIS_BACKWARD2: return I18N.Button_BACKWARD2;
	case SISAXIS_BACKWARD3: return I18N.Button_BACKWARD3;
	case SISAXIS_BACKWARD4: return I18N.Button_BACKWARD4;
	case SISAXIS_BACKWARD5: return I18N.Button_BACKWARD5;
	case SISAXIS_BACKWARD6: return I18N.Button_BACKWARD6;
	case SISAXIS_FORWARD: return I18N.Button_FORWARD;
	case SISAXIS_FORWARD1: return I18N.Button_FORWARD1;
	case SISAXIS_FORWARD2: return I18N.Button_FORWARD2;
	case SISAXIS_FORWARD3: return I18N.Button_FORWARD3;
	case SISAXIS_FORWARD4: return I18N.Button_FORWARD4;
	case SISAXIS_FORWARD5: return I18N.Button_FORWARD5;
	case SISAXIS_FORWARD6: return I18N.Button_FORWARD6;
	case SISAXIS_LEVEL: return I18N.Button_LEVEL;
	case SISAXIS_LEVEL_INV: return I18N.Button_LEVEL_INV;
	case SISAXIS_LEVEL_TRIGGER: return I18N.Button_LEVEL_TRIGGER;
	case SISAXIS_LEVEL_CENTER: return I18N.Button_LEVEL_CENTER;
	case SISAXIS_SOUTH1: return I18N.Button_SOUTH1;
	case SISAXIS_SOUTH2: return I18N.Button_SOUTH2;
	case SISAXIS_SOUTH3: return I18N.Button_SOUTH3;
	case SISAXIS_SOUTH4: return I18N.Button_SOUTH4;
	case SISAXIS_SOUTH5: return I18N.Button_SOUTH5;
	case SISAXIS_SOUTH6: return I18N.Button_SOUTH6;
	case SISAXIS_NORTH: return I18N.Button_NORTH;
	case SISAXIS_NORTH1: return I18N.Button_NORTH1;
	case SISAXIS_NORTH2: return I18N.Button_NORTH2;
	case SISAXIS_NORTH3: return I18N.Button_NORTH3;
	case SISAXIS_NORTH4: return I18N.Button_NORTH4;
	case SISAXIS_NORTH5: return I18N.Button_NORTH5;
	case SISAXIS_NORTH6: return I18N.Button_NORTH6;
	case SISAXIS_WHEEL: return I18N.Button_WHEEL;
	case SISAXIS_QUARTER: return I18N.Button_QUARTER;
	case SISAXIS_GEAR_REAR: return I18N.Button_REAR;
	case SISAXIS_GEAR_1: return I18N.Button_GEAR_1;
	case SISAXIS_GEAR_2: return I18N.Button_GEAR_2;
	case SISAXIS_GEAR_3: return I18N.Button_GEAR_3;
	case SISAXIS_GEAR_4: return I18N.Button_GEAR_4;
	case SISAXIS_GEAR_5: return I18N.Button_GEAR_5;
	case Keyboard_None: return I18N.EMPTY;
	case MOUSE_AXEX: return I18N.Button_MOUSE_AXEX;
	case MOUSE_AXEY: return I18N.Button_MOUSE_AXEY;
	case MOUSE_SCROLL_UP: return I18N.Button_MOUSE_SCROLL_UP;
	case MOUSE_SCROLL_DOWN: return I18N.Button_MOUSE_SCROLL_DOWN;
	case MOUSE_SCROLL_UP_HIGH: return I18N.Button_MOUSE_SCROLL_UP_HIGH;
	case MOUSE_SCROLL_DOWN_HIGH: return I18N.Button_MOUSE_SCROLL_DOWN_HIGH;
	case MOUSE_LEFT: return I18N.Button_MOUSE_LEFT;
	case MOUSE_RIGHT: return I18N.Button_MOUSE_RIGHT;
	case MOUSE_UP: return I18N.Button_MOUSE_UP;
	case MOUSE_DOWN: return I18N.Button_MOUSE_DOWN;
	case MOUSE_LBUTTON: return I18N.Button_MOUSE_LBUTTON;
	case MOUSE_MBUTTON: return I18N.Button_MOUSE_MBUTTON;
	case MOUSE_RBUTTON: return I18N.Button_MOUSE_RBUTTON;
	case MOUSE_XBUTTON1: return I18N.Button_MOUSE_XBUTTON1;
	case MOUSE_XBUTTON2: return I18N.Button_MOUSE_XBUTTON2;
	case MOUSE_BUTTON6: return I18N.Button_MOUSE_BUTTON6;
	case MOUSE_BUTTON7: return I18N.Button_MOUSE_BUTTON7;
	case MOUSE_BUTTON8: return I18N.Button_MOUSE_BUTTON8;
	case KID_F1: return I18N.Button_KID_F1;
	case KID_F2: return I18N.Button_KID_F2;
	case KID_F3: return I18N.Button_KID_F3;
	case KID_F4: return I18N.Button_KID_F4;
	case KID_F5: return I18N.Button_KID_F5;
	case KID_F6: return I18N.Button_KID_F6;
	case KID_F7: return I18N.Button_KID_F7;
	case KID_F8: return I18N.Button_KID_F8;
	case KID_F9: return I18N.Button_KID_F9;
	case KID_F10: return I18N.Button_KID_F10;
	case KID_F11: return I18N.Button_KID_F11;
	case KID_F12: return I18N.Button_KID_F12;
	case KID_0: return I18N.Button_KID_0;
	case KID_1: return I18N.Button_KID_1;
	case KID_2: return I18N.Button_KID_2;
	case KID_3: return I18N.Button_KID_3;
	case KID_4: return I18N.Button_KID_4;
	case KID_5: return I18N.Button_KID_5;
	case KID_6: return I18N.Button_KID_6;
	case KID_7: return I18N.Button_KID_7;
	case KID_8: return I18N.Button_KID_8;
	case KID_9: return I18N.Button_KID_9;
	case KID_OEM_MINUS: return I18N.Button_KID_OEM_MINUS;
	case KID_OEM_PLUS: return I18N.Button_KID_OEM_PLUS;
	case KID_OEM_1: return I18N.Button_KID_OEM_1;
	case KID_OEM_2: return I18N.Button_KID_OEM_2;
	case KID_OEM_3: return I18N.Button_KID_OEM_3;
	case KID_OEM_4: return I18N.Button_KID_OEM_4;
	case KID_OEM_5: return I18N.Button_KID_OEM_5;
	case KID_OEM_6: return I18N.Button_KID_OEM_6;
	case KID_OEM_7: return I18N.Button_KID_OEM_7;
	case KID_OEM_8: return I18N.Button_KID_OEM_8;
	case KID_OEM_102: return I18N.Button_KID_OEM_102;
	case KID_OEM_COMMA: return I18N.Button_KID_OEM_COMMA;
	case KID_OEM_PERIOD: return I18N.Button_KID_OEM_PERIOD;
	case KID_A: return I18N.Button_KID_A;
	case KID_B: return I18N.Button_KID_B;
	case KID_C: return I18N.Button_KID_C;
	case KID_D: return I18N.Button_KID_D;
	case KID_E: return I18N.Button_KID_E;
	case KID_F: return I18N.Button_KID_F;
	case KID_G: return I18N.Button_KID_G;
	case KID_H: return I18N.Button_KID_H;
	case KID_I: return I18N.Button_KID_I;
	case KID_J: return I18N.Button_KID_J;
	case KID_K: return I18N.Button_KID_K;
	case KID_L: return I18N.Button_KID_L;
	case KID_M: return I18N.Button_KID_M;
	case KID_N: return I18N.Button_KID_N;
	case KID_O: return I18N.Button_KID_O;
	case KID_P: return I18N.Button_KID_P;
	case KID_Q: return I18N.Button_KID_Q;
	case KID_R: return I18N.Button_KID_R;
	case KID_S: return I18N.Button_KID_S;
	case KID_T: return I18N.Button_KID_T;
	case KID_U: return I18N.Button_KID_U;
	case KID_V: return I18N.Button_KID_V;
	case KID_W: return I18N.Button_KID_W;
	case KID_X: return I18N.Button_KID_X;
	case KID_Y: return I18N.Button_KID_Y;
	case KID_Z: return I18N.Button_KID_Z;
	case KID_ESCAPE: return I18N.Button_KID_ESCAPE;
	case KID_TAB: return I18N.Button_KID_TAB;
	case KID_RETURN: return I18N.Button_KID_RETURN;
	case KID_SPACE: return I18N.Button_KID_SPACE;
	case KID_BACK: return I18N.Button_KID_BACK;
	case KID_DELETE: return I18N.Button_KID_DELETE;
	case KID_INSERT: return I18N.Button_KID_INSERT;
	case KID_NUMLOCK: return I18N.Button_KID_NUMLOCK;
	case KID_LSHIFT: return I18N.Button_KID_LSHIFT;
	case KID_RSHIFT: return I18N.Button_KID_RSHIFT;
	case KID_LCONTROL: return I18N.Button_KID_LCONTROL;
	case KID_RCONTROL: return I18N.Button_KID_RCONTROL;
	case KID_LWIN: return I18N.Button_KID_LWIN;
	case KID_RWIN: return I18N.Button_KID_RWIN;
	case KID_LMENU: return I18N.Button_KID_LMENU;
	case KID_RMENU: return I18N.Button_KID_RMENU;
	case KID_LEFT: return I18N.Button_KID_LEFT;
	case KID_UP: return I18N.Button_KID_UP;
	case KID_RIGHT: return I18N.Button_KID_RIGHT;
	case KID_DOWN: return I18N.Button_KID_DOWN;
	case KID_PRIOR: return I18N.Button_KID_PRIOR;
	case KID_NEXT: return I18N.Button_KID_NEXT;
	case KID_END: return I18N.Button_KID_END;
	case KID_HOME: return I18N.Button_KID_HOME;
	case KID_NUMPAD0: return I18N.Button_KID_NUMPAD0;
	case KID_NUMPAD1: return I18N.Button_KID_NUMPAD1;
	case KID_NUMPAD2: return I18N.Button_KID_NUMPAD2;
	case KID_NUMPAD3: return I18N.Button_KID_NUMPAD3;
	case KID_NUMPAD4: return I18N.Button_KID_NUMPAD4;
	case KID_NUMPAD5: return I18N.Button_KID_NUMPAD5;
	case KID_NUMPAD6: return I18N.Button_KID_NUMPAD6;
	case KID_NUMPAD7: return I18N.Button_KID_NUMPAD7;
	case KID_NUMPAD8: return I18N.Button_KID_NUMPAD8;
	case KID_NUMPAD9: return I18N.Button_KID_NUMPAD9;
	case KID_DIVIDE: return I18N.Button_KID_DIVIDE;
	case KID_MULTIPLY: return I18N.Button_KID_MULTIPLY;
	case KID_SUBTRACT: return I18N.Button_KID_SUBTRACT;
	case KID_ADD: return I18N.Button_KID_ADD;
	case KID_SEPARATOR: return I18N.Button_KID_SEPARATOR;
	case KID_DECIMAL: return I18N.Button_KID_DECIMAL;
	}

	if (Button16 <= id && id <= Button32)
	{
		static WCHAR buf[10];
		swprintf_s(buf, 10, I18N.Dest_BUTTON, id - Button16 + 16);
		return buf;
	}

	return I18N.WHICH;
}
