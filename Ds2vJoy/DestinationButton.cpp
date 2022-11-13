#include "stdafx.h"
#include "DestinationButton.h"

DestinationButton::DestinationButton()
{
}

DestinationButton::~DestinationButton()
{
}

void DestinationButton::setButton(long* data, unsigned int bitmask)
{
	m_type = Type_Button;
	m_data = data;
	m_mask = bitmask;
}

void DestinationButton::setAxis(long* data, byte axis)
{
	m_type = Type_Axis;
	m_data = data;
	m_counter = axis;
}

void DestinationButton::setAxisInv(long* data, byte axis)
{
	m_type = Type_AxisInv;
	m_data = data;
	m_counter = axis;
}

void DestinationButton::setTrigger(long* data, byte axis)
{
	m_type = Type_Trigger;
	m_data = data;
	m_counter = axis;
}

void DestinationButton::setTriggerInv(long* data, byte axis)
{
	m_type = Type_TriggerInv;
	m_data = data;
	m_counter = axis;
}

void DestinationButton::setAxisToTrigger(long* data, byte axis)
{
	m_type = Type_AxisToTrigger;
	m_data = data;
	m_counter = axis;
}

void DestinationButton::setAxisToTriggerInv(long* data, byte axis)
{
	m_type = Type_AxisToTriggerInv;
	m_data = data;
	m_counter = axis;
}

void DestinationButton::setDPad(byte* data)
{
	m_type = Type_DPad;
	m_dataDPad = data;
}

void DestinationButton::setRing(long* data, long* data2, AxisMoveID id, byte axis)
{
	m_type = Type_Ring;
	m_data = data;
	m_data2 = data2;
	m_AxisID = id;
	m_counter = axis;
}

void DestinationButton::setEffect(long* data, long* data2, AfterEffectID id)
{
	m_type = Type_Effect;
	m_data = data;
	m_data2 = data2;
	m_AxisID = id;
}

void DestinationButton::SetPushed(bool ispushed)
{
	switch (m_counter)
	{
	case Axis_X: { pushed[Axis_X] = ispushed; break; }
	case Axis_Y: { pushed[Axis_Y] = ispushed; break; }
	case Axis_Z: { pushed[Axis_Z] = ispushed; break; }
	case Axis_RX: { pushed[Axis_RX] = ispushed; break; }
	case Axis_RY: { pushed[Axis_RY] = ispushed; break; }
	case Axis_RZ: { pushed[Axis_RZ] = ispushed; break; }
	case Axis_SL0: { pushed[Axis_SL0] = ispushed; break; }
	case Axis_SL1: { pushed[Axis_SL1] = ispushed; break; }
	case Axis_XY:
	{
		pushed[Axis_X] = ispushed;
		pushed[Axis_Y] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case Axis_ZRZ:
	{
		pushed[Axis_Z] = ispushed;
		pushed[Axis_RZ] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case Axis_RXRY:
	{
		pushed[Axis_RX] = ispushed;
		pushed[Axis_RY] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case Axis_SL0SL1:
	{
		pushed[Axis_SL0] = ispushed;
		pushed[Axis_SL1] = ispushed;
		m_isPushed = ispushed;
		break;
	}
	case Axis_WORK1: { pushed[Axis_WORK1] = ispushed; break; }
	case Axis_WORK2: { pushed[Axis_WORK2] = ispushed; break; }
	case Axis_WORK3: { pushed[Axis_WORK3] = ispushed; break; }
	case Axis_WORK4: { pushed[Axis_WORK4] = ispushed; break; }
	case Axis_WORK5: { pushed[Axis_WORK5] = ispushed; break; }
	case Axis_WORK6: { pushed[Axis_WORK6] = ispushed; break; }
	case Axis_WORK7: { pushed[Axis_WORK7] = ispushed; break; }
	case Axis_WORK8: { pushed[Axis_WORK8] = ispushed; break; }
	default: m_isPushed = ispushed; break;
	}
}

BOOL DestinationButton::isPushed()
{
	switch (m_counter)
	{
	case Axis_X: return pushed[Axis_X];
	case Axis_Y: return pushed[Axis_Y];
	case Axis_Z: return pushed[Axis_Z];
	case Axis_RX: return pushed[Axis_RX];
	case Axis_RY: return pushed[Axis_RY];
	case Axis_RZ: return pushed[Axis_RZ];
	case Axis_SL0: return pushed[Axis_SL0];
	case Axis_SL1: return pushed[Axis_SL1];
	case Axis_WORK1: return pushed[Axis_WORK1];
	case Axis_WORK2: return pushed[Axis_WORK2];
	case Axis_WORK3: return pushed[Axis_WORK3];
	case Axis_WORK4: return pushed[Axis_WORK4];
	case Axis_WORK5: return pushed[Axis_WORK5];
	case Axis_WORK6: return pushed[Axis_WORK6];
	case Axis_WORK7: return pushed[Axis_WORK7];
	case Axis_WORK8: return pushed[Axis_WORK8];
	default: return m_isPushed;
	}
}

void DestinationButton::setOverwrite(bool isover)
{
	switch (m_counter)
	{
	case Axis_X: { overwrite[Axis_X] = isover; break; }
	case Axis_Y: { overwrite[Axis_Y] = isover; break; }
	case Axis_Z: { overwrite[Axis_Z] = isover; break; }
	case Axis_RX: { overwrite[Axis_RX] = isover; break; }
	case Axis_RY: { overwrite[Axis_RY] = isover; break; }
	case Axis_RZ: { overwrite[Axis_RZ] = isover; break; }
	case Axis_SL0: { overwrite[Axis_SL0] = isover; break; }
	case Axis_SL1: { overwrite[Axis_SL1] = isover; break; }
	case Axis_XY: { overwrite[Axis_X] = isover; overwrite[Axis_Y] = isover; m_overwrite = isover; break; }
	case Axis_ZRZ: { overwrite[Axis_Z] = isover; overwrite[Axis_RZ] = isover; m_overwrite = isover; break; }
	case Axis_RXRY: { overwrite[Axis_RX] = isover; overwrite[Axis_RY] = isover; m_overwrite = isover; break; }
	case Axis_SL0SL1: { overwrite[Axis_SL0] = isover; overwrite[Axis_SL1] = isover; m_overwrite = isover; break; }
	case Axis_WORK1: { overwrite[Axis_WORK1] = isover; break; }
	case Axis_WORK2: { overwrite[Axis_WORK2] = isover; break; }
	case Axis_WORK3: { overwrite[Axis_WORK3] = isover; break; }
	case Axis_WORK4: { overwrite[Axis_WORK4] = isover; break; }
	case Axis_WORK5: { overwrite[Axis_WORK5] = isover; break; }
	case Axis_WORK6: { overwrite[Axis_WORK6] = isover; break; }
	case Axis_WORK7: { overwrite[Axis_WORK7] = isover; break; }
	case Axis_WORK8: { overwrite[Axis_WORK8] = isover; break; }
	default: { m_overwrite = isover; break; }
	}
}

bool DestinationButton::isOverWrite()
{
	switch (m_counter)
	{
	case Axis_X: return overwrite[Axis_X];
	case Axis_Y: return overwrite[Axis_Y];
	case Axis_Z: return overwrite[Axis_Z];
	case Axis_RX: return overwrite[Axis_RX];
	case Axis_RY: return overwrite[Axis_RY];
	case Axis_RZ: return overwrite[Axis_RZ];
	case Axis_SL0: return overwrite[Axis_SL0];
	case Axis_SL1: return overwrite[Axis_SL1];
	case Axis_XY: return overwrite[Axis_X];
	case Axis_ZRZ: return overwrite[Axis_Z];
	case Axis_RXRY: return overwrite[Axis_RX];
	case Axis_SL0SL1: return overwrite[Axis_SL0];
	case Axis_WORK1: return overwrite[Axis_WORK1];
	case Axis_WORK2: return overwrite[Axis_WORK2];
	case Axis_WORK3: return overwrite[Axis_WORK3];
	case Axis_WORK4: return overwrite[Axis_WORK4];
	case Axis_WORK5: return overwrite[Axis_WORK5];
	case Axis_WORK6: return overwrite[Axis_WORK6];
	case Axis_WORK7: return overwrite[Axis_WORK7];
	case Axis_WORK8: return overwrite[Axis_WORK8];
	}
	return m_overwrite;
}

bool DestinationButton::isOverWrite2()
{
	switch (m_counter)
	{
	case Axis_X: return overwrite[Axis_X];
	case Axis_Y: return overwrite[Axis_Y];
	case Axis_Z: return overwrite[Axis_Z];
	case Axis_RX: return overwrite[Axis_RX];
	case Axis_RY: return overwrite[Axis_RY];
	case Axis_RZ: return overwrite[Axis_RZ];
	case Axis_SL0: return overwrite[Axis_SL0];
	case Axis_SL1: return overwrite[Axis_SL1];
	case Axis_XY: return overwrite[Axis_Y];
	case Axis_ZRZ: return overwrite[Axis_RZ];
	case Axis_RXRY: return overwrite[Axis_RY];
	case Axis_SL0SL1: return overwrite[Axis_SL1];
	case Axis_WORK1: return overwrite[Axis_WORK1];
	case Axis_WORK2: return overwrite[Axis_WORK2];
	case Axis_WORK3: return overwrite[Axis_WORK3];
	case Axis_WORK4: return overwrite[Axis_WORK4];
	case Axis_WORK5: return overwrite[Axis_WORK5];
	case Axis_WORK6: return overwrite[Axis_WORK6];
	case Axis_WORK7: return overwrite[Axis_WORK7];
	case Axis_WORK8: return overwrite[Axis_WORK8];
	}
	return m_overwrite;
}

void DestinationButton::SetVal(float val)
{
	if (!m_overwrite)
		return;

	switch (m_counter)
	{
	case Axis_X: counter[Axis_X]++; break;
	case Axis_Y: counter[Axis_Y]++; break;
	case Axis_Z: counter[Axis_Z]++; break;
	case Axis_RX: counter[Axis_RX]++; break;
	case Axis_RY: counter[Axis_RY]++; break;
	case Axis_RZ: counter[Axis_RZ]++; break;
	case Axis_SL0: counter[Axis_SL0]++; break;
	case Axis_SL1: counter[Axis_SL1]++; break;
	case Axis_WORK1: counter[Axis_WORK1]++; break;
	case Axis_WORK2: counter[Axis_WORK2]++; break;
	case Axis_WORK3: counter[Axis_WORK3]++; break;
	case Axis_WORK4: counter[Axis_WORK4]++; break;
	case Axis_WORK5: counter[Axis_WORK5]++; break;
	case Axis_WORK6: counter[Axis_WORK6]++; break;
	case Axis_WORK7: counter[Axis_WORK7]++; break;
	case Axis_WORK8: counter[Axis_WORK8]++; break;
	case Axis_XY: { counter[Axis_X]++; counter[Axis_Y]++; break; }
	case Axis_ZRZ: { counter[Axis_Z]++; counter[Axis_RZ]++; break; }
	case Axis_RXRY: { counter[Axis_RX]++; counter[Axis_RY]++; break; }
	case Axis_SL0SL1: { counter[Axis_SL0]++; counter[Axis_SL1]++; break; }
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
	case Type_Axis: { *m_data = val; break; }
	case Type_AxisInv:
	case Type_TriggerInv: { *m_data = 65535 - val; break; }
	case Type_Trigger: { *m_data = val; break; }
	case Type_AxisToTrigger: { *m_data = (val < 32767.5) ? (65535 - (val * 2)) : ((val - 32767.5) * 2); break; }
	case Type_AxisToTriggerInv: { *m_data = ((65535 - val) < 32767.5) ? ((val - 32767.5) * 2) : (65535 - (val * 2)); break; }
	case Type_DPad: { *m_dataDPad = val; break; }
	case Type_Ring:
	{
		switch (m_AxisID)
		{
		case XY_CW:
		case ZRZ_CW:
		case RXRY_CW:
		case SL0SL1_CW: { anglesource = (((65535 - (unsigned short)val) * 2 * π) / 65535) + (π / 2); goto axismove_circle; break; }
		case XY_CN:
		case ZRZ_CN:
		case RXRY_CN:
		case SL0SL1_CN: { anglesource = (((unsigned short)val * 2 * π) / 65535) + (π / 2); goto axismove_circle; break; }
		case XY_CENTER:
		case ZRZ_CENTER: { *m_data = 32767.5; *m_data2 = 32767.5; break; }
		case XY_LEFT:
		case ZRZ_LEFT: { *m_data = 0; *m_data2 = 32767.5; break; }
		case XY_UP_LEFT:
		case ZRZ_UP_LEFT: { *m_data = 9597; *m_data2 = 9597; break; }
		case XY_UP:
		case ZRZ_UP: { *m_data = 32767.5; *m_data2 = 0; break; }
		case XY_UP_RIGHT:
		case ZRZ_UP_RIGHT: { *m_data = 55938; *m_data2 = 9597; break; }
		case XY_RIGHT:
		case ZRZ_RIGHT: { *m_data = 65535; *m_data2 = 32767.5; break; }
		case XY_DOWN_RIGHT:
		case ZRZ_DOWN_RIGHT: { *m_data = 55938; *m_data2 = 55938; break; }
		case XY_DOWN:
		case ZRZ_DOWN: { *m_data = 32767.5; *m_data2 = 65535; break; }
		case XY_DOWN_LEFT:
		case ZRZ_DOWN_LEFT: { *m_data = 9597; *m_data2 = 55938; break; }

		case XY_Q1_CW:
		case ZRZ_Q1_CW: { anglesource = ((65535 - val) * π) / 131070; goto axismove_circle; break; }
		case XY_Q1_CN:
		case ZRZ_Q1_CN: { anglesource = (val * π) / 131070; goto axismove_circle; break; }
		case XY_Q2_CW:
		case ZRZ_Q2_CW: { anglesource = (((65535 - val) * π) / 131070) - (π / 2); goto axismove_circle; break; }
		case XY_Q2_CN:
		case ZRZ_Q2_CN: { anglesource = ((val * π) / 131070) - (π / 2); goto axismove_circle; break; }
		case XY_Q3_CW:
		case ZRZ_Q3_CW: { anglesource = (((65535 - val) * π) / 131070) - π; goto axismove_circle; break; }
		case XY_Q3_CN:
		case ZRZ_Q3_CN: { anglesource = ((val * π) / 131070 - π); goto axismove_circle; break; }
		case XY_Q4_CW:
		case ZRZ_Q4_CW: { anglesource = (((65535 - val) * π) / 131070) + (π / 2); goto axismove_circle; break; }
		case XY_Q4_CN:
		case ZRZ_Q4_CN: { anglesource = ((val * π) / 131070) + (π / 2); goto axismove_circle; break; }

		case XY_E1_CW:
		case ZRZ_E1_CW: { anglesource = (((65535 - val) * π) / 262140) + (π / 4); goto axismove_circle; break; }
		case XY_E1_CN:
		case ZRZ_E1_CN: { anglesource = ((val * π) / 262140) + (π / 4); goto axismove_circle; break; }
		case XY_E2_CW:
		case ZRZ_E2_CW: { anglesource = ((65535 - val) * π) / 262140; goto axismove_circle; break; }
		case XY_E2_CN:
		case ZRZ_E2_CN: { anglesource = (val * π) / 262140; goto axismove_circle; break; }
		case XY_E3_CW:
		case ZRZ_E3_CW: { anglesource = (((65535 - val) * π) / 262140) - (π / 4); goto axismove_circle; break; }
		case XY_E3_CN:
		case ZRZ_E3_CN: { anglesource = ((val * π) / 262140) - (π / 4); goto axismove_circle; break; }
		case XY_E4_CW:
		case ZRZ_E4_CW: { anglesource = (((65535 - val) * π) / 262140) - (π / 2); goto axismove_circle; break; }
		case XY_E4_CN:
		case ZRZ_E4_CN: { anglesource = ((val * π) / 262140) - (π / 2); goto axismove_circle; break; }
		case XY_E5_CW:
		case ZRZ_E5_CW: { anglesource = (((65535 - val) * π) / 262140) - (3 * π / 4); goto axismove_circle; break; }
		case XY_E5_CN:
		case ZRZ_E5_CN: { anglesource = ((val * π) / 262140) - (3 * π / 4); goto axismove_circle; break; }
		case XY_E6_CW:
		case ZRZ_E6_CW: { anglesource = (((65535 - val) * π) / 262140) - π; goto axismove_circle; break; }
		case XY_E6_CN:
		case ZRZ_E6_CN: { anglesource = ((val * π) / 262140) - π; goto axismove_circle; break; }
		case XY_E7_CW:
		case ZRZ_E7_CW: { anglesource = (((65535 - val) * π) / 262140) + (3 * π / 4); goto axismove_circle; break; }
		case XY_E7_CN:
		case ZRZ_E7_CN: { anglesource = ((val * π) / 262140) + (3 * π / 4); goto axismove_circle; break; }
		case XY_E8_CW:
		case ZRZ_E8_CW: { anglesource = (((65535 - val) * π) / 262140) + (π / 2); goto axismove_circle; break; }
		case XY_E8_CN:
		case ZRZ_E8_CN: { anglesource = ((val * π) / 262140) + (π / 2); goto axismove_circle; break; }

		case XY_C_L:
		case ZRZ_C_L: { *m_data = ((65535 - val) / 2); *m_data2 = 32767.5; break; }
		case XY_C_UL:
		case ZRZ_C_UL: { *m_data = 9597 + (((65535 - val) * 23170.5) / 65535); *m_data2 = 9597 + (((65535 - val) * 23170.5) / 65535); break; }
		case XY_C_U:
		case ZRZ_C_U: { *m_data = 32767.5; *m_data2 = ((65535 - val) / 2); break; }
		case XY_C_UR:
		case ZRZ_C_UR: { *m_data = 32767.5 + ((val * 23170.5) / 65535); *m_data2 = 9597 + (((65535 - val) * 23170.5) / 65535); break; }
		case XY_C_R:
		case ZRZ_C_R: { *m_data = 32767.5 + ((val * 32767.5) / 65535); *m_data2 = 32767.5; break; }
		case XY_C_DR:
		case ZRZ_C_DR: { *m_data = 32767.5 + ((val * 23170.5) / 65535); *m_data2 = 32767.5 + ((val * 23170.5) / 65535); break; }
		case XY_C_D:
		case ZRZ_C_D: { *m_data = 32767.5; *m_data2 = 32767.5 + (val / 2); break; }
		case XY_C_DL:
		case ZRZ_C_DL: { *m_data = 9597 + (((65535 - val) * 23170.5) / 65535); *m_data2 = 32767.5 + ((val * 23170.5) / 65535); break; }

		case XY_2C_L:
		case ZRZ_2C_L: { *m_data = (val / 2); *m_data2 = 32767.5; break; }
		case XY_2C_UL:
		case ZRZ_2C_UL: { *m_data = 9597 + ((val * 23170.5) / 65535); *m_data2 = 9597 + ((val * 23170.5) / 65535); break; }
		case XY_2C_U:
		case ZRZ_2C_U: { *m_data = 32767.5; *m_data2 = (val / 2); break; }
		case XY_2C_UR:
		case ZRZ_2C_UR: { *m_data = 55938 - ((val * 23170.5) / 65535); *m_data2 = 9597 + ((val * 23170.5) / 65535); break; }
		case XY_2C_R:
		case ZRZ_2C_R: { *m_data = 65535 - (val / 2); *m_data2 = 32767.5; break; }
		case XY_2C_DR:
		case ZRZ_2C_DR: { *m_data = 55938 - ((val * 23170.5) / 65535); *m_data2 = 55938 - ((val * 23170.5) / 65535); break; }
		case XY_2C_D:
		case ZRZ_2C_D: { *m_data = 32767.5; *m_data2 = 65535 - (val / 2); break; }
		case XY_2C_DL:
		case ZRZ_2C_DL: { *m_data = 9597 + ((val * 23170.5) / 65535); *m_data2 = 55938 - ((val * 23170.5) / 65535); break; }

		case XY_D_L:
		case ZRZ_D_L: { *m_data = 65535 - val; *m_data2 = 32767.5; break; }
		case XY_D_UL:
		case ZRZ_D_UL: { *m_data = 55938 - ((val * 42364.5) / 65535); *m_data2 = 55938 - ((val * 42364.5) / 65535); break; }
		case XY_D_U:
		case ZRZ_D_U: { *m_data = 32767.5; *m_data2 = 65535 - val; break; }
		case XY_D_UR:
		case ZRZ_D_UR: { *m_data = 9597 + ((val * 42364.5) / 65535); *m_data2 = 55938 - ((val * 42364.5) / 65535); break; }
		case XY_D_R:
		case ZRZ_D_R: { *m_data = val; *m_data2 = 32767.5; break; }
		case XY_D_DR:
		case ZRZ_D_DR: { *m_data = 9597 + ((val * 42364.5) / 65535); *m_data2 = 9597 + ((val * 42364.5) / 65535); break; }
		case XY_D_D:
		case ZRZ_D_D: { *m_data = 32767.5; *m_data2 = val; break; }
		case XY_D_DL:
		case ZRZ_D_DL: { *m_data = 55938 - ((val * 42364.5) / 65535); *m_data2 = 9597 + ((val * 42364.5) / 65535); break; }

		case XY_T_UL_CW:
		case ZRZ_T_UL_CW: { *m_data = 9597 + ((val * 23170.5) / 65535); *m_data2 = 55938 - ((val * 55938) / 65535); break; }
		case XY_T_UL_CN:
		case ZRZ_T_UL_CN: { *m_data = 32767.5 - ((val * 23170.5) / 65535); *m_data2 = ((val * 55938) / 65535); break; }
		case XY_T_UR_CW:
		case ZRZ_T_UR_CW: { *m_data = 32767.5 + ((val * 23170.5) / 65535); *m_data2 = (val * 55938) / 65535; break; }
		case XY_T_UR_CN:
		case ZRZ_T_UR_CN: { *m_data = 55938 - ((val * 23170.5) / 65535); *m_data2 = 55938 - ((val * 55938) / 65535); break; }
		case XY_T_DR_CW:
		case ZRZ_T_DR_CW: { *m_data = 55938 - ((val * 23170.5) / 65535); *m_data2 = 9597 + ((val * 55938) / 65535); break; }
		case XY_T_DR_CN:
		case ZRZ_T_DR_CN: { *m_data = 32767.5 + ((val * 23170.5) / 65535); *m_data2 = 65535 - ((val * 55938) / 65535); break; }
		case XY_T_DL_CW:
		case ZRZ_T_DL_CW: { *m_data = 32767.5 - ((val * 23170.5) / 65535); *m_data2 = 65535 - ((val * 55938) / 65535); break; }
		case XY_T_DL_CN:
		case ZRZ_T_DL_CN: { *m_data = 9597 + ((val * 23170.5) / 65535); *m_data2 = 9597 + ((val * 55938) / 65535); break; }

		case XY_S_L_CW:
		case ZRZ_S_L_CW: { *m_data = 9597; *m_data2 = 55938 - ((val * 42364.5) / 65535); break; }
		case XY_S_L_CN:
		case ZRZ_S_L_CN: { *m_data = 9597; *m_data2 = 9597 + ((val * 42364.5) / 65535); break; }
		case XY_S_U_CW:
		case ZRZ_S_U_CW: { *m_data = 9597 + ((val * 42364.5) / 65535); *m_data2 = 9597; break; }
		case XY_S_U_CN:
		case ZRZ_S_U_CN: { *m_data = 55938 - ((val * 42364.5) / 65535); *m_data2 = 9597; break; }
		case XY_S_R_CW:
		case ZRZ_S_R_CW: { *m_data = 55938; *m_data2 = 9597 + ((val * 42364.5) / 65535); break; }
		case XY_S_R_CN:
		case ZRZ_S_R_CN: { *m_data = 55938; *m_data2 = 55938 - ((val * 42364.5) / 65535); break; }
		case XY_S_D_CW:
		case ZRZ_S_D_CW: { *m_data = 55938 - ((val * 42364.5) / 65535); *m_data2 = 55938; break; }
		case XY_S_D_CN:
		case ZRZ_S_D_CN: { *m_data = 9597 + ((val * 42364.5) / 65535); *m_data2 = 55938; break; }

		case XY_L_UL_CW:
		case ZRZ_L_UL_CW: { *m_data = (val / 2); *m_data2 = 32767.5 - (val / 2); break; }
		case XY_L_UL_CN:
		case ZRZ_L_UL_CN: { *m_data = 32767.5 - (val / 2); *m_data2 = (val / 2); break; }
		case XY_L_UR_CW:
		case ZRZ_L_UR_CW: { *m_data = 32767.5 + (val / 2); *m_data2 = (val / 2); break; }
		case XY_L_UR_CN:
		case ZRZ_L_UR_CN: { *m_data = 65535 - (val / 2); *m_data2 = 32767.5 - (val / 2); break; }
		case XY_L_DR_CW:
		case ZRZ_L_DR_CW: { *m_data = 65535 - (val / 2); *m_data2 = 32767.5 + (val / 2); break; }
		case XY_L_DR_CN:
		case ZRZ_L_DR_CN: { *m_data = 32767.5 + (val / 2); *m_data2 = 65535 - (val / 2); break; }
		case XY_L_DL_CW:
		case ZRZ_L_DL_CW: { *m_data = 32767.5 - (val / 2); *m_data2 = 65535 - (val / 2); break; }
		case XY_L_DL_CN:
		case ZRZ_L_DL_CN: { *m_data = (val / 2); *m_data2 = 32767.5 + (val / 2); break; }
		}
		break;
	}
	case Type_Effect:
	{
		if (*m_data == 0 && *m_data2 == 0)
			return;

		if (m_AxisID >= XY_DEL_12_1 and m_AxisID <= ZRZ_DEL_16_16)
		{
			const double π = 3.141592653589793;
			double result = atan2(32767.5 - *m_data2, *m_data - 32767.5);

			switch (m_AxisID)
			{
			case XY_DEL_12_1:
			case ZRZ_DEL_12_1: { if ((result > π / 3) && (result <= π / 2)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_2:
			case ZRZ_DEL_12_2: { if ((result > π / 6) && (result <= π / 3)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_3:
			case ZRZ_DEL_12_3: { if ((result > 0) && (result <= π / 6)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_4:
			case ZRZ_DEL_12_4: { if ((result > -π / 6) && (result <= 0)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_5:
			case ZRZ_DEL_12_5: { if ((result > -π / 3) && (result <= -π / 6)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_6:
			case ZRZ_DEL_12_6: { if ((result > -π / 2) && (result <= -π / 3)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_7:
			case ZRZ_DEL_12_7: { if ((result > -2 * π / 3) && (result <= -π / 2)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_8:
			case ZRZ_DEL_12_8: { if ((result > -5 * π / 6) && (result <= -2 * π / 3)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_9:
			case ZRZ_DEL_12_9: { if (result <= -5 * π / 6) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_10:
			case ZRZ_DEL_12_10: { if (result > 5 * π / 6) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_11:
			case ZRZ_DEL_12_11: { if ((result > 2 * π / 3) && (result <= 5 * π / 6)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_12_12:
			case ZRZ_DEL_12_12: { if ((result > π / 2) && (result <= 2 * π / 3)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_1:
			case ZRZ_DEL_16_1: { if ((result > 3 * π / 8) && (result <= π / 2)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_2:
			case ZRZ_DEL_16_2: { if ((result > π / 4) && (result <= 3 * π / 8)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_3:
			case ZRZ_DEL_16_3: { if ((result > π / 8) && (result <= π / 4)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_4:
			case ZRZ_DEL_16_4: { if ((result > 0) && (result <= π / 8)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_5:
			case ZRZ_DEL_16_5: { if ((result > -π / 8) && (result <= 0)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_6:
			case ZRZ_DEL_16_6: { if ((result > -π / 4) && (result <= -π / 8)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_7:
			case ZRZ_DEL_16_7: { if ((result > -3 * π / 8) && (result <= -π / 4)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_8:
			case ZRZ_DEL_16_8: { if ((result > -π / 2) && (result <= -3 * π / 8)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_9:
			case ZRZ_DEL_16_9: { if ((result > -5 * π / 8) && (result <= -π / 2)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_10:
			case ZRZ_DEL_16_10: { if ((result > -3 * π / 4) && (result <= -5 * π / 8)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_11:
			case ZRZ_DEL_16_11: { if ((result > -7 * π / 8) && (result <= -3 * π / 4)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_12:
			case ZRZ_DEL_16_12: { if (result <= -7 * π / 8) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_13:
			case ZRZ_DEL_16_13: { if (result > 7 * π / 8) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_14:
			case ZRZ_DEL_16_14: { if ((result > 3 * π / 4) && (result <= 7 * π / 8)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_15:
			case ZRZ_DEL_16_15: { if ((result > 5 * π / 8) && (result <= 3 * π / 4)) *m_data2 = *m_data = 32767.5; return; }

			case XY_DEL_16_16:
			case ZRZ_DEL_16_16: { if ((result > π / 2) && (result <= 5 * π / 8)) *m_data2 = *m_data = 32767.5; return; }
			}
		}
		else if (m_AxisID >= XY_DISTORT_U___ and m_AxisID <= ZRZ_DISTORT__DDDDD)
		{
			const double π = 3.141592653589793;
			long x = 32767.5 - *m_data;
			long y = 32767.5 - *m_data2;
			double result = abs(atan2(x, y));
			double r = min(32767.5, sqrtl((x * x) + (y * y)));

			
			double zonestart = 0;
			double zoneend = 0;
			bool isup = true;

			switch (m_AxisID)
			{
			case XY_DISTORT_U___:
			case ZRZ_DISTORT_U___: { zonestart = 0; zoneend = π / 4; };
			case XY_DISTORT__U__:
			case ZRZ_DISTORT__U__: { zonestart = π / 4; zoneend = π / 2; };
			case XY_DISTORT___U_:
			case ZRZ_DISTORT___U_: { zonestart = π / 2; zoneend = (3 * π) / 4; };
			case XY_DISTORT____U:
			case ZRZ_DISTORT____U: { zonestart = (3 * π) / 4; zoneend = π; };
			case XY_DISTORT_UU__:
			case ZRZ_DISTORT_UU__: { zonestart = 0; zoneend = π / 2; };
			case XY_DISTORT__UU_:
			case ZRZ_DISTORT__UU_: { zonestart = π / 4; zoneend = (3 * π) / 4; };
			case XY_DISTORT___UU:
			case ZRZ_DISTORT___UU: { zonestart = π / 2; zoneend = π; };
			case XY_DISTORT_UUU_:
			case ZRZ_DISTORT_UUU_: { zonestart = 0; zoneend = (3 * π) / 4; };
			case XY_DISTORT__UUU:
			case ZRZ_DISTORT__UUU: { zonestart = π / 4; zoneend = π; };
			case XY_DISTORT_UUUU:
			case ZRZ_DISTORT_UUUU: { zonestart = 0; zoneend = π; };

			case XY_DISTORT_D___:
			case ZRZ_DISTORT_D___: { isup = false; zonestart = 0; zoneend = π / 4; };
			case XY_DISTORT__D__:
			case ZRZ_DISTORT__D__: { isup = false; zonestart = π / 4; zoneend = π / 2; };
			case XY_DISTORT___D_:
			case ZRZ_DISTORT___D_: { isup = false; zonestart = π / 2; zoneend = (3 * π) / 4; };
			case XY_DISTORT____D:
			case ZRZ_DISTORT____D: { isup = false; zonestart = (3 * π) / 4; zoneend = π; };
			case XY_DISTORT_DD__:
			case ZRZ_DISTORT_DD__: { isup = false; zonestart = 0; zoneend = π / 2; };
			case XY_DISTORT__DD_:
			case ZRZ_DISTORT__DD_: { isup = false; zonestart = π / 4; zoneend = (3 * π) / 4; };
			case XY_DISTORT___DD:
			case ZRZ_DISTORT___DD: { isup = false; zonestart = π / 2; zoneend = π; };
			case XY_DISTORT_DDD_:
			case ZRZ_DISTORT_DDD_: { isup = false; zonestart = 0; zoneend = (3 * π) / 4; };
			case XY_DISTORT__DDD:
			case ZRZ_DISTORT__DDD: { isup = false; zonestart = π / 4; zoneend = π; };
			case XY_DISTORT_DDDD:
			case ZRZ_DISTORT_DDDD: { isup = false; zonestart = 0; zoneend = π; };

			case XY_DISTORT_U_____:
			case ZRZ_DISTORT_U_____: { zonestart = 0; zoneend = π / 6; };
			case XY_DISTORT__U____:
			case ZRZ_DISTORT__U____: { zonestart = π / 6; zoneend = π / 3; };
			case XY_DISTORT___U___:
			case ZRZ_DISTORT___U___: { zonestart = π / 3; zoneend = π / 2; };
			case XY_DISTORT____U__:
			case ZRZ_DISTORT____U__: { zonestart = π / 2; zoneend = (2 * π) / 3; };
			case XY_DISTORT_____U_:
			case ZRZ_DISTORT_____U_: { zonestart = (2 * π) / 3; zoneend = (5 * π) / 6; };
			case XY_DISTORT______U:
			case ZRZ_DISTORT______U: { zonestart = (5 * π) / 6; zoneend = π; };
			case XY_DISTORT_UU____:
			case ZRZ_DISTORT_UU____: { zonestart = 0; zoneend = π / 3; };
			case XY_DISTORT__UU___:
			case ZRZ_DISTORT__UU___: { zonestart = π / 6; zoneend = π / 2; };
			case XY_DISTORT___UU__:
			case ZRZ_DISTORT___UU__: { zonestart = π / 3; zoneend = (2 * π) / 3; };
			case XY_DISTORT____UU_:
			case ZRZ_DISTORT____UU_: { zonestart = π / 2; zoneend = (5 * π) / 6; };
			case XY_DISTORT_____UU:
			case ZRZ_DISTORT_____UU: { zonestart = (2 * π) / 3; zoneend = π; };
			case XY_DISTORT__UUU__:
			case ZRZ_DISTORT__UUU__: { zonestart = π / 6; zoneend = (2 * π) / 3; };
			case XY_DISTORT___UUU_:
			case ZRZ_DISTORT___UUU_: { zonestart = π / 3; zoneend = (5 * π) / 6; };
			case XY_DISTORT_UUUU__:
			case ZRZ_DISTORT_UUUU__: { zonestart = 0; zoneend = (2 * π) / 3; };
			case XY_DISTORT__UUUU_:
			case ZRZ_DISTORT__UUUU_: { zonestart = π / 6; zoneend = (5 * π) / 6; };
			case XY_DISTORT___UUUU:
			case ZRZ_DISTORT___UUUU: { zonestart = π / 3; zoneend = π; };
			case XY_DISTORT_UUUUU_:
			case ZRZ_DISTORT_UUUUU_: { zonestart = 0; zoneend = (5 * π) / 6; };
			case XY_DISTORT__UUUUU:
			case ZRZ_DISTORT__UUUUU: { zonestart = π / 6; zoneend = π; };

			case XY_DISTORT_D_____:
			case ZRZ_DISTORT_D_____: { isup = false; zonestart = 0; zoneend = π / 6; };
			case XY_DISTORT__D____:
			case ZRZ_DISTORT__D____: { isup = false; zonestart = π / 6; zoneend = π / 3; };
			case XY_DISTORT___D___:
			case ZRZ_DISTORT___D___: { isup = false; zonestart = π / 3; zoneend = π / 2; };
			case XY_DISTORT____D__:
			case ZRZ_DISTORT____D__: { isup = false; zonestart = π / 2; zoneend = (2 * π) / 3; };
			case XY_DISTORT_____D_:
			case ZRZ_DISTORT_____D_: { isup = false; zonestart = (2 * π) / 3; zoneend = (5 * π) / 6; };
			case XY_DISTORT______D:
			case ZRZ_DISTORT______D: { isup = false; zonestart = (5 * π) / 6; zoneend = π; };
			case XY_DISTORT_DD____:
			case ZRZ_DISTORT_DD____: { isup = false; zonestart = 0; zoneend = π / 3; };
			case XY_DISTORT__DD___:
			case ZRZ_DISTORT__DD___: { isup = false; zonestart = π / 6; zoneend = π / 2; };
			case XY_DISTORT___DD__:
			case ZRZ_DISTORT___DD__: { isup = false; zonestart = π / 3; zoneend = (2 * π) / 3; };
			case XY_DISTORT____DD_:
			case ZRZ_DISTORT____DD_: { isup = false; zonestart = π / 2; zoneend = (5 * π) / 6; };
			case XY_DISTORT_____DD:
			case ZRZ_DISTORT_____DD: { isup = false; zonestart = (2 * π) / 3; zoneend = π; };
			case XY_DISTORT__DDD__:
			case ZRZ_DISTORT__DDD__: { isup = false; zonestart = π / 6; zoneend = (2 * π) / 3; };
			case XY_DISTORT___DDD_:
			case ZRZ_DISTORT___DDD_: { isup = false; zonestart = π / 3; zoneend = (5 * π) / 6; };
			case XY_DISTORT_DDDD__:
			case ZRZ_DISTORT_DDDD__: { isup = false; zonestart = 0; zoneend = (2 * π) / 3; };
			case XY_DISTORT__DDDD_:
			case ZRZ_DISTORT__DDDD_: { isup = false; zonestart = π / 6; zoneend = (5 * π) / 6; };
			case XY_DISTORT___DDDD:
			case ZRZ_DISTORT___DDDD: { isup = false; zonestart = π / 3; zoneend = π; };
			case XY_DISTORT_DDDDD_:
			case ZRZ_DISTORT_DDDDD_: { isup = false; zonestart = 0; zoneend = (5 * π) / 6; };
			case XY_DISTORT__DDDDD:
			case ZRZ_DISTORT__DDDDD: { isup = false; zonestart = π / 6; zoneend = π; };
			}

			if ((result > zonestart) && (result < zoneend))
			{
				double zone = (zoneend - zonestart) / 2;
				if (isup)
					result = result - (((π * val) * (1 - (abs(1 + ((zonestart - result) / zone))))) / 1800);
				else
					result = result + (((π * val) * (1 - (abs(1 + ((zonestart - result) / zone))))) / 1800);
			}
			*m_data = (x < 0) ? (32767.5 - r * cos(result + (π / 2))) : (r * cos(result + (π / 2)) + 32767.5);
			*m_data2 = 32767.5 - r * sin(result + (π / 2));
		}
		else
		{
			switch (m_AxisID)
			{
			case X_INV:
			case Y_INV:
			case Z_INV:
			case RZ_INV:
			case RX_INV:
			case RY_INV: { *m_data = 65535 - *m_data;  return; }

			case X_PLUS:
			case Y_PLUS:
			case Z_PLUS:
			case RZ_PLUS: { *m_data = max(0, min(65535, *m_data + val));  return; }

			case X_MINUS:
			case Y_MINUS:
			case Z_MINUS:
			case RZ_MINUS: { *m_data = max(0, min(65535, *m_data - val));  return; }

			case X_DIM:
			case Y_DIM:
			case Z_DIM:
			case RZ_DIM: { *m_data = max(0, min(65535, ((((*m_data - 32767.5) * val) / 100) + 32767.5)));  return; }

			case X_DIM_P1:
			case Y_DIM_P1:
			case Z_DIM_P1:
			case RZ_DIM_P1:
			{
				if (*m_data < 32767.5)
					*m_data = max(0, min(65535, ((((*m_data - 32767.5) * val) / 100) + 32767.5)));
				return;
			}

			case X_DIM_P2:
			case Y_DIM_P2:
			case Z_DIM_P2:
			case RZ_DIM_P2:
			{
				if (*m_data > 32767.5)
					*m_data = max(0, min(65535, ((((*m_data - 32767.5) * val) / 100) + 32767.5)));
				return;
			}

			case RX_DIM_P1:
			case RY_DIM_P1: { *m_data = max(0, min(65535, ((*m_data * val) / 100)));  return; }

			case RX_DIM_P2:
			case RY_DIM_P2: { *m_data = 65535 - max(0, min(65535, (((65535 - *m_data) * val) / 100)));  return; }

			case RX_DEL_3_1:
			case RY_DEL_3_1: { if ((*m_data > 0) && (*m_data <= 21845)) *m_data = 0; return; }

			case RX_DEL_3_2:
			case RY_DEL_3_2: { if ((*m_data > 21845) && (*m_data <= 43690)) *m_data = 0; return; }

			case RX_DEL_3_3:
			case RY_DEL_3_3: { if (*m_data > 43690) *m_data = 0; return; }

			case RX_DEL_4_1:
			case RY_DEL_4_1: { if ((*m_data > 0) && (*m_data <= 16383.75)) *m_data = 0; return; }

			case RX_DEL_4_2:
			case RY_DEL_4_2: { if ((*m_data > 16383.75) && (*m_data <= 32767.5)) *m_data = 0; return; }

			case RX_DEL_4_3:
			case RY_DEL_4_3: { if ((*m_data > 32767.5) && (*m_data <= 49151.25)) *m_data = 0; return; }

			case RX_DEL_4_4:
			case RY_DEL_4_4: { if (*m_data > 49151.25) *m_data = 0; return; }
			}
		}
		break;
	}
	default:
	{
		*m_data = val;
		break;
	}
	}
	return;
axismove_circle:
	*m_data = int(32767.5 + (cos(anglesource) * 32767.5));
	*m_data2 = int(32767.5 - (sin(anglesource) * 32767.5));
}

LONG DestinationButton::GetVal()
{
	switch (m_type)
	{
	case Type_Button: return (*m_data & m_mask) ? 65535 : 0;
	case Type_Axis:
	case Type_AxisInv:
	case Type_Trigger:
	case Type_TriggerInv:
	case Type_AxisToTrigger:
	case Type_AxisToTriggerInv:
	case Type_Ring: return *m_data;
	case Type_DPad: return (*m_dataDPad) ? 65535 : 0;
	default: return 0;
	}
}

void DestinationButton::SetVal1(float val1)
{
	if (m_overwrite)
		*m_data = val1;
}

void DestinationButton::SetVal2(float val2)
{
	if (m_overwrite)
		*m_data2 = val2;
}

LONG DestinationButton::GetVal2()
{
	switch (m_type)
	{
	case Type_Axis:
	case Type_AxisInv:
	case Type_Trigger:
	case Type_TriggerInv:
	case Type_AxisToTrigger:
	case Type_AxisToTriggerInv:
	case Type_Ring: return *m_data2;
	default: return 0;
	}
}

BYTE DestinationButton::GetValByte()
{
	return BYTE((min(255, GetVal() / 257)));
}

void DestinationButton::Release()
{
	SetPushed(false);

	switch (m_type)
	{
	case Type_Button: { *m_data &= ~m_mask; break; }
	case Type_Axis:
	case Type_AxisInv: { *m_data = 32767.5; break; }
	case Type_Trigger:
	case Type_TriggerInv:
	case Type_AxisToTrigger:
	case Type_AxisToTriggerInv: { *m_data = 0; break; }
	case Type_DPad: { *m_dataDPad = 0; break; }
	case Type_Ring: { *m_data = 32767.5; *m_data2 = 32767.5; break; }
	}
}

unsigned short DestinationButton::GetReleasedVal()
{
	switch (m_type)
	{
	case Type_Button: return (BYTE)(*m_data &= ~m_mask);
	case Type_Axis:
	case Type_AxisInv: return 32767.5;
	case Type_Trigger:
	case Type_TriggerInv:
	case Type_AxisToTrigger:
	case Type_AxisToTriggerInv:
	case Type_DPad: return 0;
	case Type_Ring: return 32767.5;
	default: return 0;
	}
}

int DestinationButton::GetScrollVal()
{
	switch (m_type)
	{
	case Type_Button: return 10;
	case Type_Axis:
	case Type_AxisInv: return (*m_data - 34309.5 > 0) ? (120 - (114 * max(0, (*m_data - 34309.5))) / 31225.5) : 0;
	case Type_Trigger:
	case Type_TriggerInv:
	case Type_AxisToTrigger:
	case Type_AxisToTriggerInv: return 120 - ((114 * *m_data) / 65535);
	case Type_DPad: return 10;
	case Type_Ring: return (((*m_data - 32767.5) * (*m_data - 32767.5)) + ((*m_data2 - 32767.5) * (*m_data2 - 32767.5))) / 8947848;
	default: return 0;
	}
}

byte DestinationButton::GetCounterType()
{
	return m_counter;
}

int DestinationButton::GetCounter()
{
	if (m_counter < 16)
		return counter[m_counter];
	else
		return 0;
}

void DestinationButton::ResetCounter()
{
	if (m_counter < 16)
		counter[m_counter] = 0;
}

WCHAR* DestinationButton::String(ButtonID id)
{
	switch (id)
	{
	case Destination_None: return I18N.EMPTY;
	case X: return I18N.Dest_X;
	case Y: return I18N.Dest_Y;
	case Z: return I18N.Dest_Z;
	case RX: return I18N.Dest_RX;
	case RY: return I18N.Dest_RY;
	case RZ: return I18N.Dest_RZ;
	case SL0: return I18N.Dest_SL0;
	case SL1: return I18N.Dest_SL1;

	case XTR: return I18N.Dest_XTR;
	case YTR: return I18N.Dest_YTR;
	case ZTR: return I18N.Dest_ZTR;
	case RXTR: return I18N.Dest_RXTR;
	case RYTR: return I18N.Dest_RYTR;
	case RZTR: return I18N.Dest_RZTR;
	case SL0TR: return I18N.Dest_SL0TR;
	case SL1TR: return I18N.Dest_SL1TR;

	case XAXTOTR: return I18N.Dest_XAXTOTR;
	case YAXTOTR: return I18N.Dest_YAXTOTR;
	case ZAXTOTR: return I18N.Dest_ZAXTOTR;
	case RXAXTOTR: return I18N.Dest_RXAXTOTR;
	case RYAXTOTR: return I18N.Dest_RYAXTOTR;
	case RZAXTOTR: return I18N.Dest_RZAXTOTR;
	case SL0AXTOTR: return I18N.Dest_SL0AXTOTR;
	case SL1AXTOTR: return I18N.Dest_SL1AXTOTR;

	case XINV: return I18N.Dest_XINV;
	case YINV: return I18N.Dest_YINV;
	case ZINV: return I18N.Dest_ZINV;
	case RXINV: return I18N.Dest_RXINV;
	case RYINV: return I18N.Dest_RYINV;
	case RZINV: return I18N.Dest_RZINV;
	case SL0INV: return I18N.Dest_SL0INV;
	case SL1INV: return I18N.Dest_SL1INV;

	case XTRINV: return I18N.Dest_XTRINV;
	case YTRINV: return I18N.Dest_YTRINV;
	case ZTRINV: return I18N.Dest_ZTRINV;
	case RXTRINV: return I18N.Dest_RXTRINV;
	case RYTRINV: return I18N.Dest_RYTRINV;
	case RZTRINV: return I18N.Dest_RZTRINV;
	case SL0TRINV: return I18N.Dest_SL0TRINV;
	case SL1TRINV: return I18N.Dest_SL1TRINV;

	case XAXTOTRINV: return I18N.Dest_XAXTOTRINV;
	case YAXTOTRINV: return I18N.Dest_YAXTOTRINV;
	case ZAXTOTRINV: return I18N.Dest_ZAXTOTRINV;
	case RXAXTOTRINV: return I18N.Dest_RXAXTOTRINV;
	case RYAXTOTRINV: return I18N.Dest_RYAXTOTRINV;
	case RZAXTOTRINV: return I18N.Dest_RZAXTOTRINV;
	case SL0AXTOTRINV: return I18N.Dest_SL0AXTOTRINV;
	case SL1AXTOTRINV: return I18N.Dest_SL1AXTOTRINV;

	case DPAD1_LEFT: return I18N.Dest_DPAD1_LEFT;
	case DPAD1_UP_LEFT: return I18N.Dest_DPAD1_UP_LEFT;
	case DPAD1_UP: return I18N.Dest_DPAD1_UP;
	case DPAD1_UP_RIGHT: return I18N.Dest_DPAD1_UP_RIGHT;
	case DPAD1_RIGHT: return I18N.Dest_DPAD1_RIGHT;
	case DPAD1_DOWN_RIGHT: return I18N.Dest_DPAD1_DOWN_RIGHT;
	case DPAD1_DOWN: return I18N.Dest_DPAD1_DOWN;
	case DPAD1_DOWN_LEFT: return I18N.Dest_DPAD1_DOWN_LEFT;
	case DPAD2_LEFT: return I18N.Dest_DPAD2_LEFT;
	case DPAD2_UP_LEFT: return I18N.Dest_DPAD2_UP_LEFT;
	case DPAD2_UP: return I18N.Dest_DPAD2_UP;
	case DPAD2_UP_RIGHT: return I18N.Dest_DPAD2_UP_RIGHT;
	case DPAD2_RIGHT: return I18N.Dest_DPAD2_RIGHT;
	case DPAD2_DOWN_RIGHT: return I18N.Dest_DPAD2_DOWN_RIGHT;
	case DPAD2_DOWN: return I18N.Dest_DPAD2_DOWN;
	case DPAD2_DOWN_LEFT: return I18N.Dest_DPAD2_DOWN_LEFT;
	case DPAD3_LEFT: return I18N.Dest_DPAD3_LEFT;
	case DPAD3_UP_LEFT: return I18N.Dest_DPAD3_UP_LEFT;
	case DPAD3_UP: return I18N.Dest_DPAD3_UP;
	case DPAD3_UP_RIGHT: return I18N.Dest_DPAD3_UP_RIGHT;
	case DPAD3_RIGHT: return I18N.Dest_DPAD3_RIGHT;
	case DPAD3_DOWN_RIGHT: return I18N.Dest_DPAD3_DOWN_RIGHT;
	case DPAD3_DOWN: return I18N.Dest_DPAD3_DOWN;
	case DPAD3_DOWN_LEFT: return I18N.Dest_DPAD3_DOWN_LEFT;
	case DPAD4_LEFT: return I18N.Dest_DPAD4_LEFT;
	case DPAD4_UP_LEFT: return I18N.Dest_DPAD4_UP_LEFT;
	case DPAD4_UP: return I18N.Dest_DPAD4_UP;
	case DPAD4_UP_RIGHT: return I18N.Dest_DPAD4_UP_RIGHT;
	case DPAD4_RIGHT: return I18N.Dest_DPAD4_RIGHT;
	case DPAD4_DOWN_RIGHT: return I18N.Dest_DPAD4_DOWN_RIGHT;
	case DPAD4_DOWN: return I18N.Dest_DPAD4_DOWN;
	case DPAD4_DOWN_LEFT: return I18N.Dest_DPAD4_DOWN_LEFT;
	case WORK1AX: return I18N.Dest_WORK1AX;
	case WORK2AX: return I18N.Dest_WORK2AX;
	case WORK3AX: return I18N.Dest_WORK3AX;
	case WORK4AX: return I18N.Dest_WORK4AX;
	case WORK5AX: return I18N.Dest_WORK5AX;
	case WORK6AX: return I18N.Dest_WORK6AX;
	case WORK7AX: return I18N.Dest_WORK7AX;
	case WORK8AX: return I18N.Dest_WORK8AX;
	case WORK1TR: return I18N.Dest_WORK1TR;
	case WORK2TR: return I18N.Dest_WORK2TR;
	case WORK3TR: return I18N.Dest_WORK3TR;
	case WORK4TR: return I18N.Dest_WORK4TR;
	case WORK5TR: return I18N.Dest_WORK5TR;
	case WORK6TR: return I18N.Dest_WORK6TR;
	case WORK7TR: return I18N.Dest_WORK5TR;
	case WORK8TR: return I18N.Dest_WORK6TR;
	}

	if (Button1 <= id && id <= Button128)
	{
		static WCHAR buf[10];
		swprintf_s(buf, 10, I18N.Dest_BUTTON, id - Button1 + 1);
		return buf;
	}
	if (WORK1 <= id && id <= WORK16)
	{
		static WCHAR buf[10];
		swprintf_s(buf, 10, I18N.Dest_BUTTON_WORK, id - WORK1 + 1);
		return buf;
	}

	return I18N.WHICH;
}

WCHAR* DestinationButton::StringAxis(AxisMoveID id)
{
	switch (id)
	{
	case AxisMove_None: return I18N.EMPTY;
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
	default: return I18N.WHICH;
	}
}

WCHAR* DestinationButton::StringEffect(AfterEffectID id)
{
	switch (id)
	{
	case AfterEffect_None: return I18N.EMPTY;
	case X_INV: return I18N.Effect_X_INV;
	case Y_INV: return I18N.Effect_Y_INV;
	case Z_INV: return I18N.Effect_Z_INV;
	case RZ_INV: return I18N.Effect_RZ_INV;
	case RX_INV: return I18N.Effect_RX_INV;
	case RY_INV: return I18N.Effect_RY_INV;
	case X_PLUS: return I18N.Effect_X_PLUS;
	case Y_PLUS: return I18N.Effect_Y_PLUS;
	case Z_PLUS: return I18N.Effect_Z_PLUS;
	case RZ_PLUS: return I18N.Effect_RZ_PLUS;
	case RX_PLUS: return I18N.Effect_RX_PLUS;
	case RY_PLUS: return I18N.Effect_RY_PLUS;
	case X_MINUS: return I18N.Effect_X_MINUS;
	case Y_MINUS: return I18N.Effect_Y_MINUS;
	case Z_MINUS: return I18N.Effect_Z_MINUS;
	case RZ_MINUS: return I18N.Effect_RZ_MINUS;
	case RX_MINUS: return I18N.Effect_RX_MINUS;
	case RY_MINUS: return I18N.Effect_RY_MINUS;
	case X_DIM: return I18N.Effect_X_DIM;
	case X_DIM_P1: return I18N.Effect_X_DIM_P1;
	case X_DIM_P2: return I18N.Effect_X_DIM_P2;
	case Y_DIM: return I18N.Effect_Y_DIM;
	case Y_DIM_P1: return I18N.Effect_Y_DIM_P1;
	case Y_DIM_P2: return I18N.Effect_Y_DIM_P2;
	case Z_DIM: return I18N.Effect_Z_DIM;
	case Z_DIM_P1: return I18N.Effect_Z_DIM_P1;
	case Z_DIM_P2: return I18N.Effect_Z_DIM_P2;
	case RZ_DIM: return I18N.Effect_RZ_DIM;
	case RZ_DIM_P1: return I18N.Effect_RZ_DIM_P1;
	case RZ_DIM_P2: return I18N.Effect_RZ_DIM_P2;
	case RX_DIM_P1: return I18N.Effect_RX_DIM_P1;
	case RX_DIM_P2: return I18N.Effect_RX_DIM_P2;
	case RY_DIM_P1: return I18N.Effect_RY_DIM_P1;
	case RY_DIM_P2: return I18N.Effect_RY_DIM_P2;
	case XY_DEL_12_1: return I18N.Effect_XY_DEL_12_1;
	case XY_DEL_12_2: return I18N.Effect_XY_DEL_12_2;
	case XY_DEL_12_3: return I18N.Effect_XY_DEL_12_3;
	case XY_DEL_12_4: return I18N.Effect_XY_DEL_12_4;
	case XY_DEL_12_5: return I18N.Effect_XY_DEL_12_5;
	case XY_DEL_12_6: return I18N.Effect_XY_DEL_12_6;
	case XY_DEL_12_7: return I18N.Effect_XY_DEL_12_7;
	case XY_DEL_12_8: return I18N.Effect_XY_DEL_12_8;
	case XY_DEL_12_9: return I18N.Effect_XY_DEL_12_9;
	case XY_DEL_12_10: return I18N.Effect_XY_DEL_12_10;
	case XY_DEL_12_11: return I18N.Effect_XY_DEL_12_11;
	case XY_DEL_12_12: return I18N.Effect_XY_DEL_12_12;
	case ZRZ_DEL_12_1: return I18N.Effect_ZRZ_DEL_12_1;
	case ZRZ_DEL_12_2: return I18N.Effect_ZRZ_DEL_12_2;
	case ZRZ_DEL_12_3: return I18N.Effect_ZRZ_DEL_12_3;
	case ZRZ_DEL_12_4: return I18N.Effect_ZRZ_DEL_12_4;
	case ZRZ_DEL_12_5: return I18N.Effect_ZRZ_DEL_12_5;
	case ZRZ_DEL_12_6: return I18N.Effect_ZRZ_DEL_12_6;
	case ZRZ_DEL_12_7: return I18N.Effect_ZRZ_DEL_12_7;
	case ZRZ_DEL_12_8: return I18N.Effect_ZRZ_DEL_12_8;
	case ZRZ_DEL_12_9: return I18N.Effect_ZRZ_DEL_12_9;
	case ZRZ_DEL_12_10: return I18N.Effect_ZRZ_DEL_12_10;
	case ZRZ_DEL_12_11: return I18N.Effect_ZRZ_DEL_12_11;
	case ZRZ_DEL_12_12: return I18N.Effect_ZRZ_DEL_12_12;
	case XY_DEL_16_1: return I18N.Effect_XY_DEL_16_1;
	case XY_DEL_16_2: return I18N.Effect_XY_DEL_16_2;
	case XY_DEL_16_3: return I18N.Effect_XY_DEL_16_3;
	case XY_DEL_16_4: return I18N.Effect_XY_DEL_16_4;
	case XY_DEL_16_5: return I18N.Effect_XY_DEL_16_5;
	case XY_DEL_16_6: return I18N.Effect_XY_DEL_16_6;
	case XY_DEL_16_7: return I18N.Effect_XY_DEL_16_7;
	case XY_DEL_16_8: return I18N.Effect_XY_DEL_16_8;
	case XY_DEL_16_9: return I18N.Effect_XY_DEL_16_9;
	case XY_DEL_16_10: return I18N.Effect_XY_DEL_16_10;
	case XY_DEL_16_11: return I18N.Effect_XY_DEL_16_11;
	case XY_DEL_16_12: return I18N.Effect_XY_DEL_16_12;
	case XY_DEL_16_13: return I18N.Effect_XY_DEL_16_13;
	case XY_DEL_16_14: return I18N.Effect_XY_DEL_16_14;
	case XY_DEL_16_15: return I18N.Effect_XY_DEL_16_15;
	case XY_DEL_16_16: return I18N.Effect_XY_DEL_16_16;
	case ZRZ_DEL_16_1: return I18N.Effect_ZRZ_DEL_16_1;
	case ZRZ_DEL_16_2: return I18N.Effect_ZRZ_DEL_16_2;
	case ZRZ_DEL_16_3: return I18N.Effect_ZRZ_DEL_16_3;
	case ZRZ_DEL_16_4: return I18N.Effect_ZRZ_DEL_16_4;
	case ZRZ_DEL_16_5: return I18N.Effect_ZRZ_DEL_16_5;
	case ZRZ_DEL_16_6: return I18N.Effect_ZRZ_DEL_16_6;
	case ZRZ_DEL_16_7: return I18N.Effect_ZRZ_DEL_16_7;
	case ZRZ_DEL_16_8: return I18N.Effect_ZRZ_DEL_16_8;
	case ZRZ_DEL_16_9: return I18N.Effect_ZRZ_DEL_16_9;
	case ZRZ_DEL_16_10: return I18N.Effect_ZRZ_DEL_16_10;
	case ZRZ_DEL_16_11: return I18N.Effect_ZRZ_DEL_16_11;
	case ZRZ_DEL_16_12: return I18N.Effect_ZRZ_DEL_16_12;
	case ZRZ_DEL_16_13: return I18N.Effect_ZRZ_DEL_16_13;
	case ZRZ_DEL_16_14: return I18N.Effect_ZRZ_DEL_16_14;
	case ZRZ_DEL_16_15: return I18N.Effect_ZRZ_DEL_16_15;
	case ZRZ_DEL_16_16: return I18N.Effect_ZRZ_DEL_16_16;
	case RX_DEL_3_1: return I18N.Effect_RX_DEL_3_1;
	case RX_DEL_3_2: return I18N.Effect_RX_DEL_3_2;
	case RX_DEL_3_3: return I18N.Effect_RX_DEL_3_3;
	case RX_DEL_4_1: return I18N.Effect_RX_DEL_4_1;
	case RX_DEL_4_2: return I18N.Effect_RX_DEL_4_2;
	case RX_DEL_4_3: return I18N.Effect_RX_DEL_4_3;
	case RX_DEL_4_4: return I18N.Effect_RX_DEL_4_4;
	case RY_DEL_3_1: return I18N.Effect_RY_DEL_3_1;
	case RY_DEL_3_2: return I18N.Effect_RY_DEL_3_2;
	case RY_DEL_3_3: return I18N.Effect_RY_DEL_3_3;
	case RY_DEL_4_1: return I18N.Effect_RY_DEL_4_1;
	case RY_DEL_4_2: return I18N.Effect_RY_DEL_4_2;
	case RY_DEL_4_3: return I18N.Effect_RY_DEL_4_3;
	case RY_DEL_4_4: return I18N.Effect_RY_DEL_4_4;
	case XY_DISTORT_U___: return I18N.Effect_XY_DISTORT_U___;
	case XY_DISTORT__U__: return I18N.Effect_XY_DISTORT__U__;
	case XY_DISTORT___U_: return I18N.Effect_XY_DISTORT___U_;
	case XY_DISTORT____U: return I18N.Effect_XY_DISTORT____U;
	case XY_DISTORT_UU__: return I18N.Effect_XY_DISTORT_UU__;
	case XY_DISTORT__UU_: return I18N.Effect_XY_DISTORT__UU_;
	case XY_DISTORT___UU: return I18N.Effect_XY_DISTORT___UU;
	case XY_DISTORT_UUU_: return I18N.Effect_XY_DISTORT_UUU_;
	case XY_DISTORT__UUU: return I18N.Effect_XY_DISTORT__UUU;
	case XY_DISTORT_UUUU: return I18N.Effect_XY_DISTORT_UUUU;
	case XY_DISTORT_D___: return I18N.Effect_XY_DISTORT_D___;
	case XY_DISTORT__D__: return I18N.Effect_XY_DISTORT__D__;
	case XY_DISTORT___D_: return I18N.Effect_XY_DISTORT___D_;
	case XY_DISTORT____D: return I18N.Effect_XY_DISTORT____D;
	case XY_DISTORT_DD__: return I18N.Effect_XY_DISTORT_DD__;
	case XY_DISTORT__DD_: return I18N.Effect_XY_DISTORT__DD_;
	case XY_DISTORT___DD: return I18N.Effect_XY_DISTORT___DD;
	case XY_DISTORT_DDD_: return I18N.Effect_XY_DISTORT_DDD_;
	case XY_DISTORT__DDD: return I18N.Effect_XY_DISTORT__DDD;
	case XY_DISTORT_DDDD: return I18N.Effect_XY_DISTORT_DDDD;
	case XY_DISTORT_U_____: return I18N.Effect_XY_DISTORT_U_____;
	case XY_DISTORT__U____: return I18N.Effect_XY_DISTORT__U____;
	case XY_DISTORT___U___: return I18N.Effect_XY_DISTORT___U___;
	case XY_DISTORT____U__: return I18N.Effect_XY_DISTORT____U__;
	case XY_DISTORT_____U_: return I18N.Effect_XY_DISTORT_____U_;
	case XY_DISTORT______U: return I18N.Effect_XY_DISTORT______U;
	case XY_DISTORT_UU____: return I18N.Effect_XY_DISTORT_UU____;
	case XY_DISTORT__UU___: return I18N.Effect_XY_DISTORT__UU___;
	case XY_DISTORT___UU__: return I18N.Effect_XY_DISTORT___UU__;
	case XY_DISTORT____UU_: return I18N.Effect_XY_DISTORT____UU_;
	case XY_DISTORT_____UU: return I18N.Effect_XY_DISTORT_____UU;
	case XY_DISTORT__UUU__: return I18N.Effect_XY_DISTORT__UUU__;
	case XY_DISTORT___UUU_: return I18N.Effect_XY_DISTORT___UUU_;
	case XY_DISTORT_UUUU__: return I18N.Effect_XY_DISTORT_UUUU__;
	case XY_DISTORT__UUUU_: return I18N.Effect_XY_DISTORT__UUUU_;
	case XY_DISTORT___UUUU: return I18N.Effect_XY_DISTORT___UUUU;
	case XY_DISTORT_UUUUU_: return I18N.Effect_XY_DISTORT_UUUUU_;
	case XY_DISTORT__UUUUU: return I18N.Effect_XY_DISTORT__UUUUU;
	case XY_DISTORT_D_____: return I18N.Effect_XY_DISTORT_D_____;
	case XY_DISTORT__D____: return I18N.Effect_XY_DISTORT__D____;
	case XY_DISTORT___D___: return I18N.Effect_XY_DISTORT___D___;
	case XY_DISTORT____D__: return I18N.Effect_XY_DISTORT____D__;
	case XY_DISTORT_____D_: return I18N.Effect_XY_DISTORT_____D_;
	case XY_DISTORT______D: return I18N.Effect_XY_DISTORT______D;
	case XY_DISTORT_DD____: return I18N.Effect_XY_DISTORT_DD____;
	case XY_DISTORT__DD___: return I18N.Effect_XY_DISTORT__DD___;
	case XY_DISTORT___DD__: return I18N.Effect_XY_DISTORT___DD__;
	case XY_DISTORT____DD_: return I18N.Effect_XY_DISTORT____DD_;
	case XY_DISTORT_____DD: return I18N.Effect_XY_DISTORT_____DD;
	case XY_DISTORT__DDD__: return I18N.Effect_XY_DISTORT__DDD__;
	case XY_DISTORT___DDD_: return I18N.Effect_XY_DISTORT___DDD_;
	case XY_DISTORT_DDDD__: return I18N.Effect_XY_DISTORT_DDDD__;
	case XY_DISTORT__DDDD_: return I18N.Effect_XY_DISTORT__DDDD_;
	case XY_DISTORT___DDDD: return I18N.Effect_XY_DISTORT___DDDD;
	case XY_DISTORT_DDDDD_: return I18N.Effect_XY_DISTORT_DDDDD_;
	case XY_DISTORT__DDDDD: return I18N.Effect_XY_DISTORT__DDDDD;
	case ZRZ_DISTORT_U___: return I18N.Effect_ZRZ_DISTORT_U___;
	case ZRZ_DISTORT__U__: return I18N.Effect_ZRZ_DISTORT__U__;
	case ZRZ_DISTORT___U_: return I18N.Effect_ZRZ_DISTORT___U_;
	case ZRZ_DISTORT____U: return I18N.Effect_ZRZ_DISTORT____U;
	case ZRZ_DISTORT_UU__: return I18N.Effect_ZRZ_DISTORT_UU__;
	case ZRZ_DISTORT__UU_: return I18N.Effect_ZRZ_DISTORT__UU_;
	case ZRZ_DISTORT___UU: return I18N.Effect_ZRZ_DISTORT___UU;
	case ZRZ_DISTORT_UUU_: return I18N.Effect_ZRZ_DISTORT_UUU_;
	case ZRZ_DISTORT__UUU: return I18N.Effect_ZRZ_DISTORT__UUU;
	case ZRZ_DISTORT_UUUU: return I18N.Effect_ZRZ_DISTORT_UUUU;
	case ZRZ_DISTORT_D___: return I18N.Effect_ZRZ_DISTORT_D___;
	case ZRZ_DISTORT__D__: return I18N.Effect_ZRZ_DISTORT__D__;
	case ZRZ_DISTORT___D_: return I18N.Effect_ZRZ_DISTORT___D_;
	case ZRZ_DISTORT____D: return I18N.Effect_ZRZ_DISTORT____D;
	case ZRZ_DISTORT_DD__: return I18N.Effect_ZRZ_DISTORT_DD__;
	case ZRZ_DISTORT__DD_: return I18N.Effect_ZRZ_DISTORT__DD_;
	case ZRZ_DISTORT___DD: return I18N.Effect_ZRZ_DISTORT___DD;
	case ZRZ_DISTORT_DDD_: return I18N.Effect_ZRZ_DISTORT_DDD_;
	case ZRZ_DISTORT__DDD: return I18N.Effect_ZRZ_DISTORT__DDD;
	case ZRZ_DISTORT_DDDD: return I18N.Effect_ZRZ_DISTORT_DDDD;
	case ZRZ_DISTORT_U_____: return I18N.Effect_ZRZ_DISTORT_U_____;
	case ZRZ_DISTORT__U____: return I18N.Effect_ZRZ_DISTORT__U____;
	case ZRZ_DISTORT___U___: return I18N.Effect_ZRZ_DISTORT___U___;
	case ZRZ_DISTORT____U__: return I18N.Effect_ZRZ_DISTORT____U__;
	case ZRZ_DISTORT_____U_: return I18N.Effect_ZRZ_DISTORT_____U_;
	case ZRZ_DISTORT______U: return I18N.Effect_ZRZ_DISTORT______U;
	case ZRZ_DISTORT_UU____: return I18N.Effect_ZRZ_DISTORT_UU____;
	case ZRZ_DISTORT__UU___: return I18N.Effect_ZRZ_DISTORT__UU___;
	case ZRZ_DISTORT___UU__: return I18N.Effect_ZRZ_DISTORT___UU__;
	case ZRZ_DISTORT____UU_: return I18N.Effect_ZRZ_DISTORT____UU_;
	case ZRZ_DISTORT_____UU: return I18N.Effect_ZRZ_DISTORT_____UU;
	case ZRZ_DISTORT__UUU__: return I18N.Effect_ZRZ_DISTORT__UUU__;
	case ZRZ_DISTORT___UUU_: return I18N.Effect_ZRZ_DISTORT___UUU_;
	case ZRZ_DISTORT_UUUU__: return I18N.Effect_ZRZ_DISTORT_UUUU__;
	case ZRZ_DISTORT__UUUU_: return I18N.Effect_ZRZ_DISTORT__UUUU_;
	case ZRZ_DISTORT___UUUU: return I18N.Effect_ZRZ_DISTORT___UUUU;
	case ZRZ_DISTORT_UUUUU_: return I18N.Effect_ZRZ_DISTORT_UUUUU_;
	case ZRZ_DISTORT__UUUUU: return I18N.Effect_ZRZ_DISTORT__UUUUU;
	case ZRZ_DISTORT_D_____: return I18N.Effect_ZRZ_DISTORT_D_____;
	case ZRZ_DISTORT__D____: return I18N.Effect_ZRZ_DISTORT__D____;
	case ZRZ_DISTORT___D___: return I18N.Effect_ZRZ_DISTORT___D___;
	case ZRZ_DISTORT____D__: return I18N.Effect_ZRZ_DISTORT____D__;
	case ZRZ_DISTORT_____D_: return I18N.Effect_ZRZ_DISTORT_____D_;
	case ZRZ_DISTORT______D: return I18N.Effect_ZRZ_DISTORT______D;
	case ZRZ_DISTORT_DD____: return I18N.Effect_ZRZ_DISTORT_DD____;
	case ZRZ_DISTORT__DD___: return I18N.Effect_ZRZ_DISTORT__DD___;
	case ZRZ_DISTORT___DD__: return I18N.Effect_ZRZ_DISTORT___DD__;
	case ZRZ_DISTORT____DD_: return I18N.Effect_ZRZ_DISTORT____DD_;
	case ZRZ_DISTORT_____DD: return I18N.Effect_ZRZ_DISTORT_____DD;
	case ZRZ_DISTORT__DDD__: return I18N.Effect_ZRZ_DISTORT__DDD__;
	case ZRZ_DISTORT___DDD_: return I18N.Effect_ZRZ_DISTORT___DDD_;
	case ZRZ_DISTORT_DDDD__: return I18N.Effect_ZRZ_DISTORT_DDDD__;
	case ZRZ_DISTORT__DDDD_: return I18N.Effect_ZRZ_DISTORT__DDDD_;
	case ZRZ_DISTORT___DDDD: return I18N.Effect_ZRZ_DISTORT___DDDD;
	case ZRZ_DISTORT_DDDDD_: return I18N.Effect_ZRZ_DISTORT_DDDDD_;
	case ZRZ_DISTORT__DDDDD: return I18N.Effect_ZRZ_DISTORT__DDDDD;
	default: return I18N.WHICH;
	}
}
