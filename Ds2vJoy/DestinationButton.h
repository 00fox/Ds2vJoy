﻿#pragma once

class DestinationButton {

public:
	enum ButtonType : unsigned char
	{
		Type_None,
		Type_Button,
		Type_Axis,
		Type_AxisInv,
		Type_Trigger,
		Type_TriggerInv,
		Type_AxisToTrigger,
		Type_AxisToTriggerInv,
		Type_DPad,
		Type_Ring,
		Type_Effect
	};

	enum ButtonID : byte
	{
		Destination_None,
		X,
		Y,
		Z,
		RX,
		RY,
		RZ,
		SL0,
		SL1,

		XTR,
		YTR,
		ZTR,
		RXTR,
		RYTR,
		RZTR,
		SL0TR,
		SL1TR,

		XAXTOTR,
		YAXTOTR,
		ZAXTOTR,
		RXAXTOTR,
		RYAXTOTR,
		RZAXTOTR,
		SL0AXTOTR,
		SL1AXTOTR,

		XINV,
		YINV,
		ZINV,
		RXINV,
		RYINV,
		RZINV,
		SL0INV,
		SL1INV,

		XTRINV,
		YTRINV,
		ZTRINV,
		RXTRINV,
		RYTRINV,
		RZTRINV,
		SL0TRINV,
		SL1TRINV,

		XAXTOTRINV,
		YAXTOTRINV,
		ZAXTOTRINV,
		RXAXTOTRINV,
		RYAXTOTRINV,
		RZAXTOTRINV,
		SL0AXTOTRINV,
		SL1AXTOTRINV,

		DPAD1_LEFT,
		DPAD1_UP_LEFT,
		DPAD1_UP,
		DPAD1_UP_RIGHT,
		DPAD1_RIGHT,
		DPAD1_DOWN_RIGHT,
		DPAD1_DOWN,
		DPAD1_DOWN_LEFT,
		DPAD2_LEFT,
		DPAD2_UP_LEFT,
		DPAD2_UP,
		DPAD2_UP_RIGHT,
		DPAD2_RIGHT,
		DPAD2_DOWN_RIGHT,
		DPAD2_DOWN,
		DPAD2_DOWN_LEFT,
		DPAD3_LEFT,
		DPAD3_UP_LEFT,
		DPAD3_UP,
		DPAD3_UP_RIGHT,
		DPAD3_RIGHT,
		DPAD3_DOWN_RIGHT,
		DPAD3_DOWN,
		DPAD3_DOWN_LEFT,
		DPAD4_LEFT,
		DPAD4_UP_LEFT,
		DPAD4_UP,
		DPAD4_UP_RIGHT,
		DPAD4_RIGHT,
		DPAD4_DOWN_RIGHT,
		DPAD4_DOWN,
		DPAD4_DOWN_LEFT,

		Button1,
		Button2,
		Button3,
		Button4,
		Button5,
		Button6,
		Button7,
		Button8,
		Button9,
		Button10,
		Button11,
		Button12,
		Button13,
		Button14,
		Button15,
		Button16,
		Button17,
		Button18,
		Button19,
		Button20,
		Button21,
		Button22,
		Button23,
		Button24,
		Button25,
		Button26,
		Button27,
		Button28,
		Button29,
		Button30,
		Button31,
		Button32,
		Button128 = Button32 + 96,

		WORK1AX,
		WORK2AX,
		WORK3AX,
		WORK4AX,
		WORK5AX,
		WORK6AX,
		WORK7AX,
		WORK8AX,

		WORK1TR,
		WORK2TR,
		WORK3TR,
		WORK4TR,
		WORK5TR,
		WORK6TR,
		WORK7TR,
		WORK8TR,

		WORK1,
		WORK16 = WORK1 + 15,
		Destination_Count
	};

	enum AxisMoveID : byte
	{
		AxisMove_None,
		XY_CW,
		XY_CN,
		ZRZ_CW,
		ZRZ_CN,
		RXRY_CW,
		RXRY_CN,
		SL0SL1_CW,
		SL0SL1_CN,
		XY_CENTER,
		XY_LEFT,
		XY_UP_LEFT,
		XY_UP,
		XY_UP_RIGHT,
		XY_RIGHT,
		XY_DOWN_RIGHT,
		XY_DOWN,
		XY_DOWN_LEFT,
		XY_Q1_CW,
		XY_Q1_CN,
		XY_Q2_CW,
		XY_Q2_CN,
		XY_Q3_CW,
		XY_Q3_CN,
		XY_Q4_CW,
		XY_Q4_CN,
		XY_E1_CW,
		XY_E1_CN,
		XY_E2_CW,
		XY_E2_CN,
		XY_E3_CW,
		XY_E3_CN,
		XY_E4_CW,
		XY_E4_CN,
		XY_E5_CW,
		XY_E5_CN,
		XY_E6_CW,
		XY_E6_CN,
		XY_E7_CW,
		XY_E7_CN,
		XY_E8_CW,
		XY_E8_CN,
		XY_C_L,
		XY_C_UL,
		XY_C_U,
		XY_C_UR,
		XY_C_R,
		XY_C_DR,
		XY_C_D,
		XY_C_DL,
		XY_2C_L,
		XY_2C_UL,
		XY_2C_U,
		XY_2C_UR,
		XY_2C_R,
		XY_2C_DR,
		XY_2C_D,
		XY_2C_DL,
		XY_D_L,
		XY_D_UL,
		XY_D_U,
		XY_D_UR,
		XY_D_R,
		XY_D_DR,
		XY_D_D,
		XY_D_DL,
		XY_T_UL_CW,
		XY_T_UL_CN,
		XY_T_UR_CW,
		XY_T_UR_CN,
		XY_T_DR_CW,
		XY_T_DR_CN,
		XY_T_DL_CW,
		XY_T_DL_CN,
		XY_S_L_CW,
		XY_S_L_CN,
		XY_S_U_CW,
		XY_S_U_CN,
		XY_S_R_CW,
		XY_S_R_CN,
		XY_S_D_CW,
		XY_S_D_CN,
		XY_L_UL_CW,
		XY_L_UL_CN,
		XY_L_UR_CW,
		XY_L_UR_CN,
		XY_L_DR_CW,
		XY_L_DR_CN,
		XY_L_DL_CW,
		XY_L_DL_CN,
		ZRZ_CENTER,
		ZRZ_LEFT,
		ZRZ_UP_LEFT,
		ZRZ_UP,
		ZRZ_UP_RIGHT,
		ZRZ_RIGHT,
		ZRZ_DOWN_RIGHT,
		ZRZ_DOWN,
		ZRZ_DOWN_LEFT,
		ZRZ_Q1_CW,
		ZRZ_Q1_CN,
		ZRZ_Q2_CW,
		ZRZ_Q2_CN,
		ZRZ_Q3_CW,
		ZRZ_Q3_CN,
		ZRZ_Q4_CW,
		ZRZ_Q4_CN,
		ZRZ_E1_CW,
		ZRZ_E1_CN,
		ZRZ_E2_CW,
		ZRZ_E2_CN,
		ZRZ_E3_CW,
		ZRZ_E3_CN,
		ZRZ_E4_CW,
		ZRZ_E4_CN,
		ZRZ_E5_CW,
		ZRZ_E5_CN,
		ZRZ_E6_CW,
		ZRZ_E6_CN,
		ZRZ_E7_CW,
		ZRZ_E7_CN,
		ZRZ_E8_CW,
		ZRZ_E8_CN,
		ZRZ_C_L,
		ZRZ_C_UL,
		ZRZ_C_U,
		ZRZ_C_UR,
		ZRZ_C_R,
		ZRZ_C_DR,
		ZRZ_C_D,
		ZRZ_C_DL,
		ZRZ_2C_L,
		ZRZ_2C_UL,
		ZRZ_2C_U,
		ZRZ_2C_UR,
		ZRZ_2C_R,
		ZRZ_2C_DR,
		ZRZ_2C_D,
		ZRZ_2C_DL,
		ZRZ_D_L,
		ZRZ_D_UL,
		ZRZ_D_U,
		ZRZ_D_UR,
		ZRZ_D_R,
		ZRZ_D_DR,
		ZRZ_D_D,
		ZRZ_D_DL,
		ZRZ_T_UL_CW,
		ZRZ_T_UL_CN,
		ZRZ_T_UR_CW,
		ZRZ_T_UR_CN,
		ZRZ_T_DR_CW,
		ZRZ_T_DR_CN,
		ZRZ_T_DL_CW,
		ZRZ_T_DL_CN,
		ZRZ_S_L_CW,
		ZRZ_S_L_CN,
		ZRZ_S_U_CW,
		ZRZ_S_U_CN,
		ZRZ_S_R_CW,
		ZRZ_S_R_CN,
		ZRZ_S_D_CW,
		ZRZ_S_D_CN,
		ZRZ_L_UL_CW,
		ZRZ_L_UL_CN,
		ZRZ_L_UR_CW,
		ZRZ_L_UR_CN,
		ZRZ_L_DR_CW,
		ZRZ_L_DR_CN,
		ZRZ_L_DL_CW,
		ZRZ_L_DL_CN,
		AxisMove_Count
	};

	enum AfterEffectID : byte
	{
		AfterEffect_None,
		X_INV,
		Y_INV,
		Z_INV,
		RZ_INV,
		RX_INV,
		RY_INV,
		X_PLUS,
		Y_PLUS,
		Z_PLUS,
		RZ_PLUS,
		RX_PLUS,
		RY_PLUS,
		X_MINUS,
		Y_MINUS,
		Z_MINUS,
		RZ_MINUS,
		RX_MINUS,
		RY_MINUS,
		X_DIM,
		X_DIM_P1,
		X_DIM_P2,
		Y_DIM,
		Y_DIM_P1,
		Y_DIM_P2,
		Z_DIM,
		Z_DIM_P1,
		Z_DIM_P2,
		RZ_DIM,
		RZ_DIM_P1,
		RZ_DIM_P2,
		RX_DIM_P1,
		RX_DIM_P2,
		RY_DIM_P1,
		RY_DIM_P2,
		XY_DEL_12_1,
		XY_DEL_12_2,
		XY_DEL_12_3,
		XY_DEL_12_4,
		XY_DEL_12_5,
		XY_DEL_12_6,
		XY_DEL_12_7,
		XY_DEL_12_8,
		XY_DEL_12_9,
		XY_DEL_12_10,
		XY_DEL_12_11,
		XY_DEL_12_12,
		ZRZ_DEL_12_1,
		ZRZ_DEL_12_2,
		ZRZ_DEL_12_3,
		ZRZ_DEL_12_4,
		ZRZ_DEL_12_5,
		ZRZ_DEL_12_6,
		ZRZ_DEL_12_7,
		ZRZ_DEL_12_8,
		ZRZ_DEL_12_9,
		ZRZ_DEL_12_10,
		ZRZ_DEL_12_11,
		ZRZ_DEL_12_12,
		XY_DEL_16_1,
		XY_DEL_16_2,
		XY_DEL_16_3,
		XY_DEL_16_4,
		XY_DEL_16_5,
		XY_DEL_16_6,
		XY_DEL_16_7,
		XY_DEL_16_8,
		XY_DEL_16_9,
		XY_DEL_16_10,
		XY_DEL_16_11,
		XY_DEL_16_12,
		XY_DEL_16_13,
		XY_DEL_16_14,
		XY_DEL_16_15,
		XY_DEL_16_16,
		ZRZ_DEL_16_1,
		ZRZ_DEL_16_2,
		ZRZ_DEL_16_3,
		ZRZ_DEL_16_4,
		ZRZ_DEL_16_5,
		ZRZ_DEL_16_6,
		ZRZ_DEL_16_7,
		ZRZ_DEL_16_8,
		ZRZ_DEL_16_9,
		ZRZ_DEL_16_10,
		ZRZ_DEL_16_11,
		ZRZ_DEL_16_12,
		ZRZ_DEL_16_13,
		ZRZ_DEL_16_14,
		ZRZ_DEL_16_15,
		ZRZ_DEL_16_16,
		RX_DEL_3_1,
		RX_DEL_3_2,
		RX_DEL_3_3,
		RX_DEL_4_1,
		RX_DEL_4_2,
		RX_DEL_4_3,
		RX_DEL_4_4,
		RY_DEL_3_1,
		RY_DEL_3_2,
		RY_DEL_3_3,
		RY_DEL_4_1,
		RY_DEL_4_2,
		RY_DEL_4_3,
		RY_DEL_4_4,
		XY_DISTORT_U___,
		XY_DISTORT__U__,
		XY_DISTORT___U_,
		XY_DISTORT____U,
		XY_DISTORT_UU__,
		XY_DISTORT__UU_,
		XY_DISTORT___UU,
		XY_DISTORT_UUU_,
		XY_DISTORT__UUU,
		XY_DISTORT_UUUU,
		XY_DISTORT_D___,
		XY_DISTORT__D__,
		XY_DISTORT___D_,
		XY_DISTORT____D,
		XY_DISTORT_DD__,
		XY_DISTORT__DD_,
		XY_DISTORT___DD,
		XY_DISTORT_DDD_,
		XY_DISTORT__DDD,
		XY_DISTORT_DDDD,
		XY_DISTORT_U_____,
		XY_DISTORT__U____,
		XY_DISTORT___U___,
		XY_DISTORT____U__,
		XY_DISTORT_____U_,
		XY_DISTORT______U,
		XY_DISTORT_UU____,
		XY_DISTORT__UU___,
		XY_DISTORT___UU__,
		XY_DISTORT____UU_,
		XY_DISTORT_____UU,
		XY_DISTORT__UUU__,
		XY_DISTORT___UUU_,
		XY_DISTORT_UUUU__,
		XY_DISTORT__UUUU_,
		XY_DISTORT___UUUU,
		XY_DISTORT_UUUUU_,
		XY_DISTORT__UUUUU,
		XY_DISTORT_D_____,
		XY_DISTORT__D____,
		XY_DISTORT___D___,
		XY_DISTORT____D__,
		XY_DISTORT_____D_,
		XY_DISTORT______D,
		XY_DISTORT_DD____,
		XY_DISTORT__DD___,
		XY_DISTORT___DD__,
		XY_DISTORT____DD_,
		XY_DISTORT_____DD,
		XY_DISTORT__DDD__,
		XY_DISTORT___DDD_,
		XY_DISTORT_DDDD__,
		XY_DISTORT__DDDD_,
		XY_DISTORT___DDDD,
		XY_DISTORT_DDDDD_,
		XY_DISTORT__DDDDD,
		ZRZ_DISTORT_U___,
		ZRZ_DISTORT__U__,
		ZRZ_DISTORT___U_,
		ZRZ_DISTORT____U,
		ZRZ_DISTORT_UU__,
		ZRZ_DISTORT__UU_,
		ZRZ_DISTORT___UU,
		ZRZ_DISTORT_UUU_,
		ZRZ_DISTORT__UUU,
		ZRZ_DISTORT_UUUU,
		ZRZ_DISTORT_D___,
		ZRZ_DISTORT__D__,
		ZRZ_DISTORT___D_,
		ZRZ_DISTORT____D,
		ZRZ_DISTORT_DD__,
		ZRZ_DISTORT__DD_,
		ZRZ_DISTORT___DD,
		ZRZ_DISTORT_DDD_,
		ZRZ_DISTORT__DDD,
		ZRZ_DISTORT_DDDD,
		ZRZ_DISTORT_U_____,
		ZRZ_DISTORT__U____,
		ZRZ_DISTORT___U___,
		ZRZ_DISTORT____U__,
		ZRZ_DISTORT_____U_,
		ZRZ_DISTORT______U,
		ZRZ_DISTORT_UU____,
		ZRZ_DISTORT__UU___,
		ZRZ_DISTORT___UU__,
		ZRZ_DISTORT____UU_,
		ZRZ_DISTORT_____UU,
		ZRZ_DISTORT__UUU__,
		ZRZ_DISTORT___UUU_,
		ZRZ_DISTORT_UUUU__,
		ZRZ_DISTORT__UUUU_,
		ZRZ_DISTORT___UUUU,
		ZRZ_DISTORT_UUUUU_,
		ZRZ_DISTORT__UUUUU,
		ZRZ_DISTORT_D_____,
		ZRZ_DISTORT__D____,
		ZRZ_DISTORT___D___,
		ZRZ_DISTORT____D__,
		ZRZ_DISTORT_____D_,
		ZRZ_DISTORT______D,
		ZRZ_DISTORT_DD____,
		ZRZ_DISTORT__DD___,
		ZRZ_DISTORT___DD__,
		ZRZ_DISTORT____DD_,
		ZRZ_DISTORT_____DD,
		ZRZ_DISTORT__DDD__,
		ZRZ_DISTORT___DDD_,
		ZRZ_DISTORT_DDDD__,
		ZRZ_DISTORT__DDDD_,
		ZRZ_DISTORT___DDDD,
		ZRZ_DISTORT_DDDDD_,
		ZRZ_DISTORT__DDDDD,
		AfterEffect_Count
	};

	enum AxisID : byte
	{
		Axis_X,
		Axis_Y,
		Axis_Z,
		Axis_RX,
		Axis_RY,
		Axis_RZ,
		Axis_SL0,
		Axis_SL1,
		Axis_WORK1,
		Axis_WORK2,
		Axis_WORK3,
		Axis_WORK4,
		Axis_WORK5,
		Axis_WORK6,
		Axis_WORK7,
		Axis_WORK8,
		Axis_XY,
		Axis_ZRZ,
		Axis_RXRY,
		Axis_SL0SL1,
		Axis_Count
	};

	DestinationButton();
	~DestinationButton();

	void				setButton(long* data, unsigned int bitmask);
	void				setAxis(long* data, byte axis);
	void				setAxisInv(long* data, byte axis);
	void				setTrigger(long* data, byte axis);
	void				setTriggerInv(long* data, byte axis);
	void				setAxisToTrigger(long* data, byte axis);
	void				setAxisToTriggerInv(long* data, byte axis);
	void				setDPad(byte* data);
	void				setRing(long* data, long* data2, AxisMoveID id, byte axis);
	void				setEffect(long* data, long* data2, AfterEffectID id);

	void				SetPushed(bool ispushed = true);
	BOOL				isPushed();

	void				setOverwrite(bool isover = true);
	bool				isOverWrite();
	bool				isOverWrite2();

	void				SetVal(float val);
	LONG				GetVal();
	void				SetVal1(float val1);
	void				SetVal2(float val2);
	LONG				GetVal2();
	BYTE				GetValByte();

	void				Release();
	unsigned short		GetReleasedVal();

	int					GetScrollVal();

	byte				GetCounterType();
	int					GetCounter();
	void				ResetCounter();

	static WCHAR*		String(ButtonID);
	static WCHAR*		StringAxis(AxisMoveID);
	static WCHAR*		StringEffect(AfterEffectID);

private:
	ButtonType			m_type = Type_None;
	long*				m_data = 0;
	long*				m_data2 = 0;
	byte*				m_dataDPad = 0;
	byte				m_AxisID = 0;
	unsigned int		m_mask = 0;
	bool				m_isPushed = false;
	bool				m_overwrite = true;
	byte				m_counter = -1;
	const double		π = 3.141592653589793;
	double				anglesource = 0;
};

	static int			counter[16] = { 0 };
	static bool			pushed[16] = { false };
	static bool			overwrite[16] = { true };

	typedef				DestinationButton::ButtonID DestButtonID;
	typedef				DestinationButton::AxisMoveID DestAxisMoveID;
	typedef				DestinationButton::AfterEffectID DestAfterEffectID;
	typedef				DestinationButton::AxisID DestAxisID;