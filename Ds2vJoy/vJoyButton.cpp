#include "stdafx.h"
#include "vJoyButton.h"

vJoyButton::vJoyButton()
{
}

vJoyButton::~vJoyButton()
{
}

void vJoyButton::setButton(long* data, unsigned int bitmask)
{
	m_type = Type_Button;
	m_data = data;
	m_mask = bitmask;
}

void vJoyButton::setTrigger(long* data, unsigned char axis)
{
	m_type = Type_Trigger;
	m_data = data;
	m_counter = axis;
}

void vJoyButton::setAxis(long* data, unsigned char axis)
{
	m_type = Type_Axis;
	m_data = data;
	m_counter = axis;
}

void vJoyButton::setAxisInv(long* data, unsigned char axis)
{
	m_type = Type_AxisInv;
	m_data = data;
	m_counter = axis;
}

void vJoyButton::setDPad(byte* data)
{
	m_type = Type_DPad;
	m_dataDPad = data;
}

void vJoyButton::setRing(long* data, long* data2, AxisMoveID id, unsigned char axis)
{
	m_type = Type_Ring;
	m_data = data;
	m_data2 = data2;
	m_AxisID = id;
	m_counter = axis;
}

void vJoyButton::SetPushed(bool ispushed)
{
	switch (m_counter)
	{
	case axis_X: { pushed[axis_X] = ispushed; break; }
	case axis_Y: { pushed[axis_Y] = ispushed; break; }
	case axis_Z: { pushed[axis_Z] = ispushed; break; }
	case axis_RX: { pushed[axis_RX] = ispushed; break; }
	case axis_RY: { pushed[axis_RY] = ispushed; break; }
	case axis_RZ: { pushed[axis_RZ] = ispushed; break; }
	case axis_SL0: { pushed[axis_SL0] = ispushed; break; }
	case axis_SL1: { pushed[axis_SL1] = ispushed; break; }
	case axis_XY:
	{
		pushed[axis_X] = ispushed;
		pushed[axis_Y] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case axis_ZRZ:
	{
		pushed[axis_Z] = ispushed;
		pushed[axis_RZ] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case axis_RXRY:
	{
		pushed[axis_RX] = ispushed;
		pushed[axis_RY] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case axis_SL0SL1:
	{
		pushed[axis_SL0] = ispushed;
		pushed[axis_SL1] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	default: m_isPushed = ispushed; break;
	}
}

BOOL vJoyButton::isPushed()
{
	switch (m_counter)
	{
	case axis_X: return pushed[axis_X];
	case axis_Y: return pushed[axis_Y];
	case axis_Z: return pushed[axis_Z];
	case axis_RX: return pushed[axis_RX];
	case axis_RY: return pushed[axis_RY];
	case axis_RZ: return pushed[axis_RZ];
	case axis_SL0: return pushed[axis_SL0];
	case axis_SL1: return pushed[axis_SL1];
	default: return m_isPushed;
	}
}

void vJoyButton::setOverwrite(bool isover)
{
	switch (m_counter)
	{
	case axis_X: { overwrite[axis_X] = isover; break; }
	case axis_Y: { overwrite[axis_Y] = isover; break; }
	case axis_Z: { overwrite[axis_Z] = isover; break; }
	case axis_RX: { overwrite[axis_RX] = isover; break; }
	case axis_RY: { overwrite[axis_RY] = isover; break; }
	case axis_RZ: { overwrite[axis_RZ] = isover; break; }
	case axis_SL0: { overwrite[axis_SL0] = isover; break; }
	case axis_SL1: { overwrite[axis_SL1] = isover; break; }
	case axis_XY: { overwrite[axis_X] = isover; overwrite[axis_Y] = isover; m_overwrite = isover; break; }
	case axis_ZRZ: { overwrite[axis_Z] = isover; overwrite[axis_RZ] = isover; m_overwrite = isover; break; }
	case axis_RXRY: { overwrite[axis_RX] = isover; overwrite[axis_RY] = isover; m_overwrite = isover; break; }
	case axis_SL0SL1: { overwrite[axis_SL0] = isover; overwrite[axis_SL1] = isover; m_overwrite = isover; break; }
	default: { m_overwrite = isover; break; }
	}
}

bool vJoyButton::isOverWrite()
{
	switch (m_counter)
	{
	case axis_X: return overwrite[axis_X];
	case axis_Y: return overwrite[axis_Y];
	case axis_Z: return overwrite[axis_Z];
	case axis_RX: return overwrite[axis_RX];
	case axis_RY: return overwrite[axis_RY];
	case axis_RZ: return overwrite[axis_RZ];
	case axis_SL0: return overwrite[axis_SL0];
	case axis_SL1: return overwrite[axis_SL1];
	default: return m_overwrite;
	}
	return m_overwrite;
}

void vJoyButton::SetVal(long val)
{
	if (m_overwrite)
		*m_data = val;
}

LONG vJoyButton::GetVal()
{
	switch (m_type)
	{
	case Type_Button: return (*m_data & m_mask) ? 32767 : 0;
	case Type_Trigger:
	case Type_Axis:
	case Type_AxisInv:
	case Type_Ring: return *m_data;
	case Type_DPad: return (*m_dataDPad) ? 32767 : 0;
	default: return 0;
	}
}

void vJoyButton::SetVal2(long val2)
{
	if (m_overwrite)
		*m_data2 = val2;
}

LONG vJoyButton::GetVal2()
{
	switch (m_type)
	{
	case Type_Trigger:
	case Type_Axis:
	case Type_AxisInv:
	case Type_Ring: return *m_data2;
	default: return 0;
	}
}

void vJoyButton::SetValByte(byte val)
{
	if (!m_overwrite)
		return;

	switch (m_counter)
	{
	case axis_X: counter[axis_X]++; break;
	case axis_Y: counter[axis_Y]++; break;
	case axis_Z: counter[axis_Z]++; break;
	case axis_RX: counter[axis_RX]++; break;
	case axis_RY: counter[axis_RY]++; break;
	case axis_RZ: counter[axis_RZ]++; break;
	case axis_SL0: counter[axis_SL0]++; break;
	case axis_SL1: counter[axis_SL1]++; break;
	case axis_XY: { counter[axis_X]++; counter[axis_Y]++; break; }
	case axis_ZRZ: { counter[axis_Z]++; counter[axis_RZ]++; break; }
	case axis_RXRY: { counter[axis_RX]++; counter[axis_RY]++; break; }
	case axis_SL0SL1: { counter[axis_SL0]++; counter[axis_SL1]++; break; }
	}

	switch (m_type)
	{
	case Type_Button:
	{
		if (val)
			*m_data |= m_mask;
		else
			*m_data &= ~m_mask;
		break;
	}
	case Type_Trigger: { *m_data = (val * 32767) / 255; break; }
	case Type_Axis: { *m_data = (val * 32767) / 255; break; }
	case Type_AxisInv: { *m_data = (32767) - ((val * 32767) / 255); break; }
	case Type_DPad: { *m_dataDPad = val; break; }
	case Type_Ring:
	{
		switch (m_AxisID)
		{
		case XY_CW:
		case ZRZ_CW:
		case RXRY_CW:
		case SL0SL1_CW: { anglesource = (((255 - (double)val) * 2 * π) / 255) + (π / 2); goto axismove_circle; break; }
		case XY_CN:
		case ZRZ_CN:
		case RXRY_CN:
		case SL0SL1_CN: { anglesource = (((double)val * 2 * π) / 255) + (π / 2); goto axismove_circle; break; }
		case XY_CENTER:
		case ZRZ_CENTER: { *m_data = 0; *m_data2 = 0; break; }
		case XY_LEFT:
		case ZRZ_LEFT: { *m_data = 0; *m_data2 = 16383; break; }
		case XY_UP_LEFT:
		case ZRZ_UP_LEFT: { *m_data = 4798; *m_data2 = 4798; break; }
		case XY_UP:
		case ZRZ_UP: { *m_data = 16383; *m_data2 = 0; break; }
		case XY_UP_RIGHT:
		case ZRZ_UP_RIGHT: { *m_data = 27968; *m_data2 = 4798; break; }
		case XY_RIGHT:
		case ZRZ_RIGHT: { *m_data = 32767; *m_data2 = 16383; break; }
		case XY_DOWN_RIGHT:
		case ZRZ_DOWN_RIGHT: { *m_data = 27968; *m_data2 = 27968; break; }
		case XY_DOWN:
		case ZRZ_DOWN: { *m_data = 16383; *m_data2 = 32767; break; }
		case XY_DOWN_LEFT:
		case ZRZ_DOWN_LEFT: { *m_data = 4798; *m_data2 = 27968; break; }
		case XY_Q1_CW:
		case ZRZ_Q1_CW: { anglesource = ((255 - val) * π) / 510; goto axismove_circle; break; }
		case XY_Q1_CN:
		case ZRZ_Q1_CN: { anglesource = (val * π) / 510; goto axismove_circle; break; }
		case XY_Q2_CW:
		case ZRZ_Q2_CW: { anglesource = (((255 - val) * π) / 510) - (π / 2); goto axismove_circle; break; }
		case XY_Q2_CN:
		case ZRZ_Q2_CN: { anglesource = ((val * π) / 510) - (π / 2); goto axismove_circle; break; }
		case XY_Q3_CW:
		case ZRZ_Q3_CW: { anglesource = (((255 - val) * π) / 510) - π; goto axismove_circle; break; }
		case XY_Q3_CN:
		case ZRZ_Q3_CN: { anglesource = ((val * π) / 510 - π); goto axismove_circle; break; }
		case XY_Q4_CW:
		case ZRZ_Q4_CW: { anglesource = (((255 - val) * π) / 510) + (π / 2); goto axismove_circle; break; }
		case XY_Q4_CN:
		case ZRZ_Q4_CN: { anglesource = ((val * π) / 510) + (π / 2); goto axismove_circle; break; }
		case XY_E1_CW:
		case ZRZ_E1_CW: { anglesource = (((255 - val) * π) / 1020) + (π / 4); goto axismove_circle; break; }
		case XY_E1_CN:
		case ZRZ_E1_CN: { anglesource = ((val * π) / 1020) + (π / 4); goto axismove_circle; break; }
		case XY_E2_CW:
		case ZRZ_E2_CW: { anglesource = ((255 - val) * π) / 1020; goto axismove_circle; break; }
		case XY_E2_CN:
		case ZRZ_E2_CN: { anglesource = (val * π) / 1020; goto axismove_circle; break; }
		case XY_E3_CW:
		case ZRZ_E3_CW: { anglesource = (((255 - val) * π) / 1020) - (π / 4); goto axismove_circle; break; }
		case XY_E3_CN:
		case ZRZ_E3_CN: { anglesource = ((val * π) / 1020) - (π / 4); goto axismove_circle; break; }
		case XY_E4_CW:
		case ZRZ_E4_CW: { anglesource = (((255 - val) * π) / 1020) - (π / 2); goto axismove_circle; break; }
		case XY_E4_CN:
		case ZRZ_E4_CN: { anglesource = ((val * π) / 1020) - (π / 2); goto axismove_circle; break; }
		case XY_E5_CW:
		case ZRZ_E5_CW: { anglesource = (((255 - val) * π) / 1020) - (3 * π / 4); goto axismove_circle; break; }
		case XY_E5_CN:
		case ZRZ_E5_CN: { anglesource = ((val * π) / 1020) - (3 * π / 4); goto axismove_circle; break; }
		case XY_E6_CW:
		case ZRZ_E6_CW: { anglesource = (((255 - val) * π) / 1020) - π; goto axismove_circle; break; }
		case XY_E6_CN:
		case ZRZ_E6_CN: { anglesource = ((val * π) / 1020) - π; goto axismove_circle; break; }
		case XY_E7_CW:
		case ZRZ_E7_CW: { anglesource = (((255 - val) * π) / 1020) + (3 * π / 4); goto axismove_circle; break; }
		case XY_E7_CN:
		case ZRZ_E7_CN: { anglesource = ((val * π) / 1020) + (3 * π / 4); goto axismove_circle; break; }
		case XY_E8_CW:
		case ZRZ_E8_CW: { anglesource = (((255 - val) * π) / 1020) + (π / 2); goto axismove_circle; break; }
		case XY_E8_CN:
		case ZRZ_E8_CN: { anglesource = ((val * π) / 1020) + (π / 2); goto axismove_circle; break; }
		case XY_C_L:
		case ZRZ_C_L: { *m_data = ((255 - val) * 16383) / 255; *m_data2 = 16383; break; }
		case XY_C_UL:
		case ZRZ_C_UL: { *m_data = 4798 + (((255 - val) * 11585) / 255); *m_data2 = 4798 + (((255 - val) * 11585) / 255); break; }
		case XY_C_U:
		case ZRZ_C_U: { *m_data = 16383; *m_data2 = ((255 - val) * 16383) / 255; break; }
		case XY_C_UR:
		case ZRZ_C_UR: { *m_data = 16384 + ((val * 11585) / 255); *m_data2 = 4798 + (((255 - val) * 11585) / 255); break; }
		case XY_C_R:
		case ZRZ_C_R: { *m_data = 16384 + ((val * 16383) / 255); *m_data2 = 16383; break; }
		case XY_C_DR:
		case ZRZ_C_DR: { *m_data = 16384 + ((val * 11585) / 255); *m_data2 = 16384 + ((val * 11585) / 255); break; }
		case XY_C_D:
		case ZRZ_C_D: { *m_data = 16383; *m_data2 = 16384 + ((val * 16383) / 255); break; }
		case XY_C_DL:
		case ZRZ_C_DL: { *m_data = 4798 + (((255 - val) * 11585) / 255); *m_data2 = 16384 + ((val * 11585) / 255); break; }
		case XY_2C_L:
		case ZRZ_2C_L: { *m_data = (val * 16383) / 255; *m_data2 = 16383; break; }
		case XY_2C_UL:
		case ZRZ_2C_UL: { *m_data = 4798 + ((val * 11585) / 255); *m_data2 = 4798 + ((val * 11585) / 255); break; }
		case XY_2C_U:
		case ZRZ_2C_U: { *m_data = 16383; *m_data2 = (val * 16383) / 255; break; }
		case XY_2C_UR:
		case ZRZ_2C_UR: { *m_data = 27969 - ((val * 11585) / 255); *m_data2 = 4798 + ((val * 11585) / 255); break; }
		case XY_2C_R:
		case ZRZ_2C_R: { *m_data = 32767 - ((val * 16384) / 255); *m_data2 = 16383; break; }
		case XY_2C_DR:
		case ZRZ_2C_DR: { *m_data = 27969 - ((val * 11585) / 255); *m_data2 = 27969 - ((val * 11585) / 255); break; }
		case XY_2C_D:
		case ZRZ_2C_D: { *m_data = 16383; *m_data2 = 32767 - ((val * 16384) / 255); break; }
		case XY_2C_DL:
		case ZRZ_2C_DL: { *m_data = 4798 + ((val * 11585) / 255); *m_data2 = 27969 - ((val * 11585) / 255); break; }
		case XY_D_L:
		case ZRZ_D_L: { *m_data = 32767 - ((val * 32767) / 255); *m_data2 = 16383; break; }
		case XY_D_UL:
		case ZRZ_D_UL: { *m_data = 27969 - ((val * 23171) / 255); *m_data2 = 27969 - ((val * 23171) / 255); break; }
		case XY_D_U:
		case ZRZ_D_U: { *m_data = 16383; *m_data2 = 32767 - ((val * 32767) / 255); break; }
		case XY_D_UR:
		case ZRZ_D_UR: { *m_data = 4798 + ((val * 23171) / 255); *m_data2 = 27969 - ((val * 23171) / 255); break; }
		case XY_D_R:
		case ZRZ_D_R: { *m_data = (val * 32767) / 255; *m_data2 = 16383; break; }
		case XY_D_DR:
		case ZRZ_D_DR: { *m_data = 4798 + ((val * 23171) / 255); *m_data2 = 4798 + ((val * 23171) / 255); break; }
		case XY_D_D:
		case ZRZ_D_D: { *m_data = 16383; *m_data2 = (val * 32767) / 255; break; }
		case XY_D_DL:
		case ZRZ_D_DL: { *m_data = 27969 - ((val * 23171) / 255); *m_data2 = 4798 + ((val * 23171) / 255); break; }
		case XY_T_UL_CW:
		case ZRZ_T_UL_CW: { *m_data = 4798 + ((val * 11585) / 255); *m_data2 = 27969 - ((val * 27969) / 255); break; }
		case XY_T_UL_CN:
		case ZRZ_T_UL_CN: { *m_data = 16383 - ((val * 11585) / 255); *m_data2 = (val * 27969) / 255; break; }
		case XY_T_UR_CW:
		case ZRZ_T_UR_CW: { *m_data = 16384 + ((val * 11585) / 255); *m_data2 = (val * 27969) / 255; break; }
		case XY_T_UR_CN:
		case ZRZ_T_UR_CN: { *m_data = 27969 - ((val * 11585) / 255); *m_data2 = 27969 - ((val * 27969) / 255); break; }
		case XY_T_DR_CW:
		case ZRZ_T_DR_CW: { *m_data = 27969 - ((val * 11585) / 255); *m_data2 = 4798 + ((val * 27969) / 255); break; }
		case XY_T_DR_CN:
		case ZRZ_T_DR_CN: { *m_data = 16384 + ((val * 11585) / 255); *m_data2 = 32767 - ((val * 27969) / 255); break; }
		case XY_T_DL_CW:
		case ZRZ_T_DL_CW: { *m_data = 16384 - ((val * 11585) / 255); *m_data2 = 32767 - ((val * 27969) / 255); break; }
		case XY_T_DL_CN:
		case ZRZ_T_DL_CN: { *m_data = 4798 + ((val * 11585) / 255); *m_data2 = 4798 + ((val * 27969) / 255); break; }
		case XY_S_L_CW:
		case ZRZ_S_L_CW: { *m_data = 4798; *m_data2 = 27969 - ((val * 23171) / 255); break; }
		case XY_S_L_CN:
		case ZRZ_S_L_CN: { *m_data = 4798; *m_data2 = 4798 + ((val * 23171) / 255); break; }
		case XY_S_U_CW:
		case ZRZ_S_U_CW: { *m_data = 4798 + ((val * 23171) / 255); *m_data2 = 4798; break; }
		case XY_S_U_CN:
		case ZRZ_S_U_CN: { *m_data = 27969 - ((val * 23171) / 255); *m_data2 = 4798; break; }
		case XY_S_R_CW:
		case ZRZ_S_R_CW: { *m_data = 27969; *m_data2 = 4798 + ((val * 23171) / 255); break; }
		case XY_S_R_CN:
		case ZRZ_S_R_CN: { *m_data = 27969; *m_data2 = 27969 - ((val * 23171) / 255); break; }
		case XY_S_D_CW:
		case ZRZ_S_D_CW: { *m_data = 27969 - ((val * 23171) / 255); *m_data2 = 27969; break; }
		case XY_S_D_CN:
		case ZRZ_S_D_CN: { *m_data = 4798 + ((val * 23171) / 255); *m_data2 = 27969; break; }
		case XY_L_UL_CW:
		case ZRZ_L_UL_CW: { *m_data = (val * 16383) / 255; *m_data2 = 16383 - ((val * 16383) / 255); break; }
		case XY_L_UL_CN:
		case ZRZ_L_UL_CN: { *m_data = 16383 - ((val * 16383) / 255); *m_data2 = (val * 16383) / 255; break; }
		case XY_L_UR_CW:
		case ZRZ_L_UR_CW: { *m_data = 16384 + ((val * 16383) / 255); *m_data2 = (val * 16383) / 255; break; }
		case XY_L_UR_CN:
		case ZRZ_L_UR_CN: { *m_data = 32767 - ((val * 16384) / 255); *m_data2 = 16383 - ((val * 16383) / 255); break; }
		case XY_L_DR_CW:
		case ZRZ_L_DR_CW: { *m_data = 32767 - ((val * 16384) / 255); *m_data2 = 16384 + ((val * 16383) / 255); break; }
		case XY_L_DR_CN:
		case ZRZ_L_DR_CN: { *m_data = 16384 + ((val * 16383) / 255); *m_data2 = 32767 - ((val * 16384) / 255); break; }
		case XY_L_DL_CW:
		case ZRZ_L_DL_CW: { *m_data = 16383 - ((val * 16383) / 255); *m_data2 = 32767 - ((val * 16384) / 255); break; }
		case XY_L_DL_CN:
		case ZRZ_L_DL_CN: { *m_data = (val * 16383) / 255; *m_data2 = 16384 + ((val * 16383) / 255); break; }
		}
		break;
	}
	}
	return;
axismove_circle:
	*m_data = (long)max(0, 16383 + (cos(anglesource) * 16384));
	*m_data2 = (long)max(0, 16383 - (sin(anglesource) * 16384));
}

BYTE vJoyButton::GetValByte()
{
	return (BYTE)((GetVal() * 255) / 32767);
}

void vJoyButton::Release()
{
	SetPushed(false);

	switch (m_type)
	{
	case Type_Button: { *m_data &= ~m_mask; break; }
	case Type_Trigger: { *m_data = 0; break; }
	case Type_Axis:
	case Type_AxisInv: { *m_data = 16383; break; }
	case Type_DPad: { *m_dataDPad = 0; break; }
	case Type_Ring: { *m_data = 16383; *m_data2 = 16383; break; }
	}
}

BYTE vJoyButton::GetReleasedVal()
{
	switch (m_type)
	{
	case Type_Button: return (BYTE)(*m_data &= ~m_mask);
	case Type_Trigger: return 0;
	case Type_Axis: return 127;
	case Type_AxisInv: return 127;
	case Type_DPad: return 0;
	case Type_Ring: return 127;
	default: return 0;
	}
}

int vJoyButton::GetScrollVal()
{
	switch (m_type)
	{
	case Type_Button: return 10;
	case Type_Trigger: return 120 - ((114 * *m_data) / 32767);
	case Type_Axis:
	case Type_AxisInv: return (*m_data - 17151 > 0) ? (120 - (114 * max(0, (*m_data - 17151))) / 15616) : 0;
	case Type_DPad: return 10;
	case Type_Ring: return (((*m_data - 16384) * (*m_data - 16384)) + ((*m_data2 - 16384) * (*m_data2 - 16384))) / 2236962;
	default: return 0;
	}
}

char vJoyButton::GetCounterType()
{
	return m_counter;
}

int vJoyButton::GetCounter()
{
	if (m_counter < 8)
		return counter[m_counter];
	else
		return 0;
}

void vJoyButton::ResetCounter()
{
	if (m_counter < 8)
		counter[m_counter] = 0;
}

WCHAR* vJoyButton::String(ButtonID id)
{
	switch (id)
	{
	case none: return WCHARI(L"");
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
		swprintf_s(buf, 10, L"%d", id - Button1 + 1);
		return buf;
	}
	return WCHARI(L"???");
}

WCHAR* vJoyButton::StringAxis(AxisMoveID id)
{
	switch (id)
	{
	case axismove_none: return WCHARI(L"");
	case XY_CW: return I18N.Axis_XY_CW;
	case XY_CN: return I18N.Axis_XY_CN;
	case ZRZ_CW: return I18N.Axis_ZRZ_CW;
	case ZRZ_CN: return I18N.Axis_ZRZ_CN;
	case RXRY_CW: return I18N.Axis_RXRY_CW;
	case RXRY_CN: return I18N.Axis_RXRY_CN;
	case SL0SL1_CW: return I18N.Axis_SL0SL1_CW;
	case SL0SL1_CN: return I18N.Axis_SL0SL1_CN;
	case XY_CENTER: return I18N.Axis_XY_CENTER;
	case XY_LEFT: return I18N.Axis_XY_LEFT;
	case XY_UP_LEFT: return I18N.Axis_XY_UP_LEFT;
	case XY_UP: return I18N.Axis_XY_UP;
	case XY_UP_RIGHT: return I18N.Axis_XY_UP_RIGHT;
	case XY_RIGHT: return I18N.Axis_XY_RIGHT;
	case XY_DOWN_RIGHT: return I18N.Axis_XY_DOWN_RIGHT;
	case XY_DOWN: return I18N.Axis_XY_DOWN;
	case XY_DOWN_LEFT: return I18N.Axis_XY_DOWN_LEFT;
	case XY_Q1_CW: return I18N.Axis_XY_Q1_CW;
	case XY_Q1_CN: return I18N.Axis_XY_Q1_CN;
	case XY_Q2_CW: return I18N.Axis_XY_Q2_CW;
	case XY_Q2_CN: return I18N.Axis_XY_Q2_CN;
	case XY_Q3_CW: return I18N.Axis_XY_Q3_CW;
	case XY_Q3_CN: return I18N.Axis_XY_Q3_CN;
	case XY_Q4_CW: return I18N.Axis_XY_Q4_CW;
	case XY_Q4_CN: return I18N.Axis_XY_Q4_CN;
	case XY_E1_CW: return I18N.Axis_XY_E1_CW;
	case XY_E1_CN: return I18N.Axis_XY_E1_CN;
	case XY_E2_CW: return I18N.Axis_XY_E2_CW;
	case XY_E2_CN: return I18N.Axis_XY_E2_CN;
	case XY_E3_CW: return I18N.Axis_XY_E3_CW;
	case XY_E3_CN: return I18N.Axis_XY_E3_CN;
	case XY_E4_CW: return I18N.Axis_XY_E4_CW;
	case XY_E4_CN: return I18N.Axis_XY_E4_CN;
	case XY_E5_CW: return I18N.Axis_XY_E5_CW;
	case XY_E5_CN: return I18N.Axis_XY_E5_CN;
	case XY_E6_CW: return I18N.Axis_XY_E6_CW;
	case XY_E6_CN: return I18N.Axis_XY_E6_CN;
	case XY_E7_CW: return I18N.Axis_XY_E7_CW;
	case XY_E7_CN: return I18N.Axis_XY_E7_CN;
	case XY_E8_CW: return I18N.Axis_XY_E8_CW;
	case XY_E8_CN: return I18N.Axis_XY_E8_CN;
	case XY_C_L: return I18N.Axis_XY_C_L;
	case XY_C_UL: return I18N.Axis_XY_C_UL;
	case XY_C_U: return I18N.Axis_XY_C_U;
	case XY_C_UR: return I18N.Axis_XY_C_UR;
	case XY_C_R: return I18N.Axis_XY_C_R;
	case XY_C_DR: return I18N.Axis_XY_C_DR;
	case XY_C_D: return I18N.Axis_XY_C_D;
	case XY_C_DL: return I18N.Axis_XY_C_DL;
	case XY_2C_L: return I18N.Axis_XY_2C_L;
	case XY_2C_UL: return I18N.Axis_XY_2C_UL;
	case XY_2C_U: return I18N.Axis_XY_2C_U;
	case XY_2C_UR: return I18N.Axis_XY_2C_UR;
	case XY_2C_R: return I18N.Axis_XY_2C_R;
	case XY_2C_DR: return I18N.Axis_XY_2C_DR;
	case XY_2C_D: return I18N.Axis_XY_2C_D;
	case XY_2C_DL: return I18N.Axis_XY_2C_DL;
	case XY_D_L: return I18N.Axis_XY_D_L;
	case XY_D_UL: return I18N.Axis_XY_D_UL;
	case XY_D_U: return I18N.Axis_XY_D_U;
	case XY_D_UR: return I18N.Axis_XY_D_UR;
	case XY_D_R: return I18N.Axis_XY_D_R;
	case XY_D_DR: return I18N.Axis_XY_D_DR;
	case XY_D_D: return I18N.Axis_XY_D_D;
	case XY_D_DL: return I18N.Axis_XY_D_DL;
	case XY_T_UL_CW: return I18N.Axis_XY_T_UL_CW;
	case XY_T_UL_CN: return I18N.Axis_XY_T_UL_CN;
	case XY_T_UR_CW: return I18N.Axis_XY_T_UR_CW;
	case XY_T_UR_CN: return I18N.Axis_XY_T_UR_CN;
	case XY_T_DR_CW: return I18N.Axis_XY_T_DR_CW;
	case XY_T_DR_CN: return I18N.Axis_XY_T_DR_CN;
	case XY_T_DL_CW: return I18N.Axis_XY_T_DL_CW;
	case XY_T_DL_CN: return I18N.Axis_XY_T_DL_CN;
	case XY_S_L_CW: return I18N.Axis_XY_S_L_CW;
	case XY_S_L_CN: return I18N.Axis_XY_S_L_CN;
	case XY_S_U_CW: return I18N.Axis_XY_S_U_CW;
	case XY_S_U_CN: return I18N.Axis_XY_S_U_CN;
	case XY_S_R_CW: return I18N.Axis_XY_S_R_CW;
	case XY_S_R_CN: return I18N.Axis_XY_S_R_CN;
	case XY_S_D_CW: return I18N.Axis_XY_S_D_CW;
	case XY_S_D_CN: return I18N.Axis_XY_S_D_CN;
	case XY_L_UL_CW: return I18N.Axis_XY_L_UL_CW;
	case XY_L_UL_CN: return I18N.Axis_XY_L_UL_CN;
	case XY_L_UR_CW: return I18N.Axis_XY_L_UR_CW;
	case XY_L_UR_CN: return I18N.Axis_XY_L_UR_CN;
	case XY_L_DR_CW: return I18N.Axis_XY_L_DR_CW;
	case XY_L_DR_CN: return I18N.Axis_XY_L_DR_CN;
	case XY_L_DL_CW: return I18N.Axis_XY_L_DL_CW;
	case XY_L_DL_CN: return I18N.Axis_XY_L_DL_CN;
	case ZRZ_CENTER: return I18N.Axis_ZRZ_CENTER;
	case ZRZ_LEFT: return I18N.Axis_ZRZ_LEFT;
	case ZRZ_UP_LEFT: return I18N.Axis_ZRZ_UP_LEFT;
	case ZRZ_UP: return I18N.Axis_ZRZ_UP;
	case ZRZ_UP_RIGHT: return I18N.Axis_ZRZ_UP_RIGHT;
	case ZRZ_RIGHT: return I18N.Axis_ZRZ_RIGHT;
	case ZRZ_DOWN_RIGHT: return I18N.Axis_ZRZ_DOWN_RIGHT;
	case ZRZ_DOWN: return I18N.Axis_ZRZ_DOWN;
	case ZRZ_DOWN_LEFT: return I18N.Axis_ZRZ_DOWN_LEFT;
	case ZRZ_Q1_CW: return I18N.Axis_ZRZ_Q1_CW;
	case ZRZ_Q1_CN: return I18N.Axis_ZRZ_Q1_CN;
	case ZRZ_Q2_CW: return I18N.Axis_ZRZ_Q2_CW;
	case ZRZ_Q2_CN: return I18N.Axis_ZRZ_Q2_CN;
	case ZRZ_Q3_CW: return I18N.Axis_ZRZ_Q3_CW;
	case ZRZ_Q3_CN: return I18N.Axis_ZRZ_Q3_CN;
	case ZRZ_Q4_CW: return I18N.Axis_ZRZ_Q4_CW;
	case ZRZ_Q4_CN: return I18N.Axis_ZRZ_Q4_CN;
	case ZRZ_E1_CW: return I18N.Axis_ZRZ_E1_CW;
	case ZRZ_E1_CN: return I18N.Axis_ZRZ_E1_CN;
	case ZRZ_E2_CW: return I18N.Axis_ZRZ_E2_CW;
	case ZRZ_E2_CN: return I18N.Axis_ZRZ_E2_CN;
	case ZRZ_E3_CW: return I18N.Axis_ZRZ_E3_CW;
	case ZRZ_E3_CN: return I18N.Axis_ZRZ_E3_CN;
	case ZRZ_E4_CW: return I18N.Axis_ZRZ_E4_CW;
	case ZRZ_E4_CN: return I18N.Axis_ZRZ_E4_CN;
	case ZRZ_E5_CW: return I18N.Axis_ZRZ_E5_CW;
	case ZRZ_E5_CN: return I18N.Axis_ZRZ_E5_CN;
	case ZRZ_E6_CW: return I18N.Axis_ZRZ_E6_CW;
	case ZRZ_E6_CN: return I18N.Axis_ZRZ_E6_CN;
	case ZRZ_E7_CW: return I18N.Axis_ZRZ_E7_CW;
	case ZRZ_E7_CN: return I18N.Axis_ZRZ_E7_CN;
	case ZRZ_E8_CW: return I18N.Axis_ZRZ_E8_CW;
	case ZRZ_E8_CN: return I18N.Axis_ZRZ_E8_CN;
	case ZRZ_C_L: return I18N.Axis_ZRZ_C_L;
	case ZRZ_C_UL: return I18N.Axis_ZRZ_C_UL;
	case ZRZ_C_U: return I18N.Axis_ZRZ_C_U;
	case ZRZ_C_UR: return I18N.Axis_ZRZ_C_UR;
	case ZRZ_C_R: return I18N.Axis_ZRZ_C_R;
	case ZRZ_C_DR: return I18N.Axis_ZRZ_C_DR;
	case ZRZ_C_D: return I18N.Axis_ZRZ_C_D;
	case ZRZ_C_DL: return I18N.Axis_ZRZ_C_DL;
	case ZRZ_2C_L: return I18N.Axis_ZRZ_2C_L;
	case ZRZ_2C_UL: return I18N.Axis_ZRZ_2C_UL;
	case ZRZ_2C_U: return I18N.Axis_ZRZ_2C_U;
	case ZRZ_2C_UR: return I18N.Axis_ZRZ_2C_UR;
	case ZRZ_2C_R: return I18N.Axis_ZRZ_2C_R;
	case ZRZ_2C_DR: return I18N.Axis_ZRZ_2C_DR;
	case ZRZ_2C_D: return I18N.Axis_ZRZ_2C_D;
	case ZRZ_2C_DL: return I18N.Axis_ZRZ_2C_DL;
	case ZRZ_D_L: return I18N.Axis_ZRZ_D_L;
	case ZRZ_D_UL: return I18N.Axis_ZRZ_D_UL;
	case ZRZ_D_U: return I18N.Axis_ZRZ_D_U;
	case ZRZ_D_UR: return I18N.Axis_ZRZ_D_UR;
	case ZRZ_D_R: return I18N.Axis_ZRZ_D_R;
	case ZRZ_D_DR: return I18N.Axis_ZRZ_D_DR;
	case ZRZ_D_D: return I18N.Axis_ZRZ_D_D;
	case ZRZ_D_DL: return I18N.Axis_ZRZ_D_DL;
	case ZRZ_T_UL_CW: return I18N.Axis_ZRZ_T_UL_CW;
	case ZRZ_T_UL_CN: return I18N.Axis_ZRZ_T_UL_CN;
	case ZRZ_T_UR_CW: return I18N.Axis_ZRZ_T_UR_CW;
	case ZRZ_T_UR_CN: return I18N.Axis_ZRZ_T_UR_CN;
	case ZRZ_T_DR_CW: return I18N.Axis_ZRZ_T_DR_CW;
	case ZRZ_T_DR_CN: return I18N.Axis_ZRZ_T_DR_CN;
	case ZRZ_T_DL_CW: return I18N.Axis_ZRZ_T_DL_CW;
	case ZRZ_T_DL_CN: return I18N.Axis_ZRZ_T_DL_CN;
	case ZRZ_S_L_CW: return I18N.Axis_ZRZ_S_L_CW;
	case ZRZ_S_L_CN: return I18N.Axis_ZRZ_S_L_CN;
	case ZRZ_S_U_CW: return I18N.Axis_ZRZ_S_U_CW;
	case ZRZ_S_U_CN: return I18N.Axis_ZRZ_S_U_CN;
	case ZRZ_S_R_CW: return I18N.Axis_ZRZ_S_R_CW;
	case ZRZ_S_R_CN: return I18N.Axis_ZRZ_S_R_CN;
	case ZRZ_S_D_CW: return I18N.Axis_ZRZ_S_D_CW;
	case ZRZ_S_D_CN: return I18N.Axis_ZRZ_S_D_CN;
	case ZRZ_L_UL_CW: return I18N.Axis_ZRZ_L_UL_CW;
	case ZRZ_L_UL_CN: return I18N.Axis_ZRZ_L_UL_CN;
	case ZRZ_L_UR_CW: return I18N.Axis_ZRZ_L_UR_CW;
	case ZRZ_L_UR_CN: return I18N.Axis_ZRZ_L_UR_CN;
	case ZRZ_L_DR_CW: return I18N.Axis_ZRZ_L_DR_CW;
	case ZRZ_L_DR_CN: return I18N.Axis_ZRZ_L_DR_CN;
	case ZRZ_L_DL_CW: return I18N.Axis_ZRZ_L_DL_CW;
	case ZRZ_L_DL_CN: return I18N.Axis_ZRZ_L_DL_CN;
	}
	return WCHARI(L"???");
}
