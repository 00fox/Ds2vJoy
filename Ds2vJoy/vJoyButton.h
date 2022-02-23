#pragma once

class vJoyButton {

public:
	enum ButtonType
	{
		Type_None,
		Type_Button,
		Type_Trigger,
		Type_Axis,
		Type_AxisInv,
		Type_DPad,
		Type_Ring
	};

	enum ButtonID
	{
		none,
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
		XINV,
		YINV,
		ZINV,
		RXINV,
		RYINV,
		RZINV,
		SL0INV,
		SL1INV,
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
		button_Count
	};

	enum AxisMoveID
	{
		axismove_none,
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
		axismove_Count,
	};

	enum AxisID
	{
		axis_X,
		axis_Y,
		axis_Z,
		axis_RX,
		axis_RY,
		axis_RZ,
		axis_SL0,
		axis_SL1,
		axis_XY,
		axis_ZRZ,
		axis_RXRY,
		axis_SL0SL1,
		axis_Count
	};

	vJoyButton();
	~vJoyButton();

	void				setButton(long* data, unsigned int bitmask);
	void				setTrigger(long* data, unsigned char axis);
	void				setAxis(long* data, unsigned char axis);
	void				setAxisInv(long* data, unsigned char axis);
	void				setDPad(byte* data);
	void				setRing(long* data, long* data2, AxisMoveID id, unsigned char axis);

	void				SetPushed(bool ispushed = true);
	BOOL				isPushed();

	void				setOverwrite(bool isover = true);
	bool				isOverWrite();

	void				SetVal(long val);
	LONG				GetVal();
	void				SetVal2(long val2);
	LONG				GetVal2();
	void				SetValByte(byte);
	BYTE				GetValByte();

	void				Release();
	BYTE				GetReleasedVal();

	int					GetScrollVal();

	char				GetCounterType();
	int					GetCounter();
	void				ResetCounter();

	static WCHAR*		String(ButtonID);
	static WCHAR*		StringAxis(AxisMoveID);

private:
	ButtonType			m_type = Type_None;
	long*				m_data = 0;
	long*				m_data2 = 0;
	byte*				m_dataDPad = 0;
	byte				m_AxisID = 0;
	unsigned int		m_mask = 0;
	bool				m_isPushed = false;
	bool				m_overwrite = true;
	char				m_counter = -1;
	const double		π = 3.141592653589793238462643;
	double				anglesource = 0;
};

	static int			counter[8] = { 0 };
	static bool			pushed[8] = { false };
	static bool			overwrite[8] = { true };

	typedef				vJoyButton::ButtonID vJoyButtonID;
	typedef				vJoyButton::AxisMoveID vJoyAxisMoveID;
	typedef				vJoyButton::AxisID vJoyAxisID;
