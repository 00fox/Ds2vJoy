﻿#pragma once

class SourceButton
{
public:
	enum ButtonType : byte
	{
		Type_None,
		Type_Constant,
		Type_Button,
		Type_Trigger,
		Type_Simultaneous,
		Type_Touch,
		Type_Axis,
		Type_AxisInv,
		Type_AxisSolo,
		Type_AxisInvSolo,
		Type_AxisSniper,
		Type_AxisTriggerLU,
		Type_AxisTriggerRD,
		Type_AxisLU,
		Type_AxisRD,
		Type_AxisDUL,
		Type_AxisDUR,
		Type_AxisDDR,
		Type_AxisDDL,
		Type_Data,
	};

	enum ButtonID : unsigned short
	{
		Button_None,
		LX,
		LY,
		RX,
		RY,
		L3,
		DPAD_LEFT,
		DPAD_UP,
		DPAD_RIGHT,
		DPAD_DOWN,
		SHARE,
		OPTIONS,
		SQUARE,
		TRIANGLE,
		CIRCLE,
		CROSS,
		R3,
		PS,
		TOUCH,
		MUTE,
		L1,
		R1,
		L2,
		R2,
		L2_TRIGGER,
		R2_TRIGGER,
		LX_INV,
		LY_INV,
		RX_INV,
		RY_INV,
		LX_SNIPER,
		LY_SNIPER,
		RX_SNIPER,
		RY_SNIPER,
		AXISL_TR_LEFT,
		AXISL_TR_UP,
		AXISL_TR_RIGHT,
		AXISL_TR_DOWN,
		AXISR_TR_LEFT,
		AXISR_TR_UP,
		AXISR_TR_RIGHT,
		AXISR_TR_DOWN,
		AXISL_LEFT,
		AXISL_UP_LEFT,
		AXISL_UP,
		AXISL_UP_RIGHT,
		AXISL_RIGHT,
		AXISL_DOWN_RIGHT,
		AXISL_DOWN,
		AXISL_DOWN_LEFT,
		AXISR_LEFT,
		AXISR_UP_LEFT,
		AXISR_UP,
		AXISR_UP_RIGHT,
		AXISR_RIGHT,
		AXISR_DOWN_RIGHT,
		AXISR_DOWN,
		AXISR_DOWN_LEFT,
		TOUCHUP,
		TOUCHPAD,
		TOUCH1,
		TOUCH2,
		TOUCH3,
		TOUCH4,
		TOUCHL,
		TOUCHR,
		L2_TRIGGER_33,
		R2_TRIGGER_33,
		L2_TRIGGER_66,
		R2_TRIGGER_66,
		L2_TRIGGER_100,
		R2_TRIGGER_100,
		L1R1,
		L2R2,
		EMPTY,
		MIDDLE,
		FULL,
		QUARTER1,
		QUARTER2,
		THIRD1,
		THIRD2,
		TEN,
		TWENTY,
		THIRTY,
		FORTY,
		SIXTY,
		SEVENTY,
		EIGHTY,
		NINETY,
		BATTERY,
		BATTERY0,
		BATTERY1,
		BATTERY2,
		BATTERY3,
		BATTERY4,
		BATTERY5,
		BATTERY6,
		BATTERY7,
		BATTERY8,
		BATTERY9,
		USB,
		EARS,
		MIC,
		BT,
		FINGER,
		FINGERS,
		DS_SELECTED,
		DS4_SELECTED,
		DS5_SELECTED,
		DI_SELECTED,
		XI_SELECTED,
		DS_ACTIVE,
		DS4_ACTIVE,
		DS5_ACTIVE,
		DI_ACTIVE,
		KBD_ACTIVE,
		MSE_ACTIVE,
		MSE_DI_ACTIVE,
		INACTIVITY_5MN,
		INACTIVITY_10MN,
		INACTIVITY_15MN,
		INACTIVITY_30MN,
		NO_MOVEMENT_5MN,
		NO_MOVEMENT_10MN,
		NO_MOVEMENT_15MN,
		NO_MOVEMENT_30MN,
		SLO,
		SLO_INV,
		SLO_SNIPER,
		SL1,
		SL1_INV,
		SL1_SNIPER,
		DI_X,
		DI_X_INV,
		DI_X_TRIGGER,
		DI_Y,
		DI_Y_INV,
		DI_Y_TRIGGER,
		DI_Z,
		DI_Z_INV,
		DI_Z_TRIGGER,
		DI_RX,
		DI_RX_INV,
		DI_RX_TRIGGER,
		DI_RY,
		DI_RY_INV,
		DI_RY_TRIGGER,
		DI_RZ,
		DI_RZ_INV,
		DI_RZ_TRIGGER,
		DI_SL0,
		DI_SL0_INV,
		DI_SL0_TRIGGER,
		DI_SL1,
		DI_SL1_INV,
		DI_SL1_TRIGGER,
		DPAD2_LEFT,
		DPAD2_UP,
		DPAD2_RIGHT,
		DPAD2_DOWN,
		DPAD3_LEFT,
		DPAD3_UP,
		DPAD3_RIGHT,
		DPAD3_DOWN,
		DPAD4_LEFT,
		DPAD4_UP,
		DPAD4_RIGHT,
		DPAD4_DOWN,
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
		Button_Count,

		Sisaxis_None = 256,
		SISAXIS_STANCE,
		SISAXIS_ZONE,
		SISAXIS_STANCE1,
		SISAXIS_STANCE2,
		SISAXIS_STANCE3,
		SISAXIS_STANCE4,
		SISAXIS_STANCE5,
		SISAXIS_ZONE1,
		SISAXIS_ZONE2,
		SISAXIS_ZONE3,
		SISAXIS_ZONE4,
		SISAXIS_ZONE5,

		SISAXIS_ROLL,
		SISAXIS_ROLL_INV,
		SISAXIS_ROLL_TRIGGER,
		SISAXIS_ROLL_CENTER,
		SISAXIS_LEFT1,
		SISAXIS_LEFT2,
		SISAXIS_LEFT3,
		SISAXIS_LEFT4,
		SISAXIS_LEFT5,
		SISAXIS_LEFT6,
		SISAXIS_LEFT7,
		SISAXIS_RIGHT,
		SISAXIS_RIGHT1,
		SISAXIS_RIGHT2,
		SISAXIS_RIGHT3,
		SISAXIS_RIGHT4,
		SISAXIS_RIGHT5,
		SISAXIS_RIGHT6,
		SISAXIS_RIGHT7,

		SISAXIS_YAW,
		SISAXIS_YAW_INV,
		SISAXIS_YAW_TRIGGER,
		SISAXIS_YAW_CENTER,
		SISAXIS_ANTI1,
		SISAXIS_ANTI2,
		SISAXIS_ANTI3,
		SISAXIS_ANTI4,
		SISAXIS_ANTI5,
		SISAXIS_ANTI6,
		SISAXIS_ANTI7,
		SISAXIS_CLOCK,
		SISAXIS_CLOCK1,
		SISAXIS_CLOCK2,
		SISAXIS_CLOCK3,
		SISAXIS_CLOCK4,
		SISAXIS_CLOCK5,
		SISAXIS_CLOCK6,
		SISAXIS_CLOCK7,

		SISAXIS_PITCH,
		SISAXIS_PITCH_INV,
		SISAXIS_PITCH_TRIGGER,
		SISAXIS_PITCH_CENTER,
		SISAXIS_REAR1,
		SISAXIS_REAR2,
		SISAXIS_REAR3,
		SISAXIS_REAR4,
		SISAXIS_REAR5,
		SISAXIS_REAR6,
		SISAXIS_REAR7,
		SISAXIS_FORE,
		SISAXIS_FORE1,
		SISAXIS_FORE2,
		SISAXIS_FORE3,
		SISAXIS_FORE4,
		SISAXIS_FORE5,
		SISAXIS_FORE6,
		SISAXIS_FORE7,

		SISAXIS_SIDEWARD,
		SISAXIS_SIDEWARD_INV,
		SISAXIS_SIDEWARD_TRIGGER,
		SISAXIS_SIDEWARD_CENTER,
		SISAXIS_WEST1,
		SISAXIS_WEST2,
		SISAXIS_WEST3,
		SISAXIS_WEST4,
		SISAXIS_WEST5,
		SISAXIS_WEST6,
		SISAXIS_EAST,
		SISAXIS_EAST1,
		SISAXIS_EAST2,
		SISAXIS_EAST3,
		SISAXIS_EAST4,
		SISAXIS_EAST5,
		SISAXIS_EAST6,

		SISAXIS_TOWARD,
		SISAXIS_TOWARD_INV,
		SISAXIS_TOWARD_TRIGGER,
		SISAXIS_TOWARD_CENTER,
		SISAXIS_BACKWARD1,
		SISAXIS_BACKWARD2,
		SISAXIS_BACKWARD3,
		SISAXIS_BACKWARD4,
		SISAXIS_BACKWARD5,
		SISAXIS_BACKWARD6,
		SISAXIS_FORWARD,
		SISAXIS_FORWARD1,
		SISAXIS_FORWARD2,
		SISAXIS_FORWARD3,
		SISAXIS_FORWARD4,
		SISAXIS_FORWARD5,
		SISAXIS_FORWARD6,

		SISAXIS_LEVEL,
		SISAXIS_LEVEL_INV,
		SISAXIS_LEVEL_TRIGGER,
		SISAXIS_LEVEL_CENTER,
		SISAXIS_SOUTH1,
		SISAXIS_SOUTH2,
		SISAXIS_SOUTH3,
		SISAXIS_SOUTH4,
		SISAXIS_SOUTH5,
		SISAXIS_SOUTH6,
		SISAXIS_NORTH,
		SISAXIS_NORTH1,
		SISAXIS_NORTH2,
		SISAXIS_NORTH3,
		SISAXIS_NORTH4,
		SISAXIS_NORTH5,
		SISAXIS_NORTH6,

		SISAXIS_WHEEL,
		SISAXIS_QUARTER,
		SISAXIS_GEAR_REAR,
		SISAXIS_GEAR_1,
		SISAXIS_GEAR_2,
		SISAXIS_GEAR_3,
		SISAXIS_GEAR_4,
		SISAXIS_GEAR_5,
		Sisaxis_Count,

		Keyboard_None = 512,
		MOUSE_AXEX,
		MOUSE_AXEY,
		MOUSE_SCROLL_UP,
		MOUSE_SCROLL_DOWN,
		MOUSE_SCROLL_UP_HIGH,
		MOUSE_SCROLL_DOWN_HIGH,
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_UP,
		MOUSE_DOWN,
		MOUSE_LBUTTON,
		MOUSE_MBUTTON,
		MOUSE_RBUTTON,
		MOUSE_XBUTTON1,
		MOUSE_XBUTTON2,
		MOUSE_BUTTON6,
		MOUSE_BUTTON7,
		MOUSE_BUTTON8,
		KID_F1,
		KID_F2,
		KID_F3,
		KID_F4,
		KID_F5,
		KID_F6,
		KID_F7,
		KID_F8,
		KID_F9,
		KID_F10,
		KID_F11,
		KID_F12,
		KID_0,
		KID_1,
		KID_2,
		KID_3,
		KID_4,
		KID_5,
		KID_6,
		KID_7,
		KID_8,
		KID_9,
		KID_OEM_MINUS,
		KID_OEM_PLUS,
		KID_OEM_1,
		KID_OEM_2,
		KID_OEM_3,
		KID_OEM_4,
		KID_OEM_5,
		KID_OEM_6,
		KID_OEM_7,
		KID_OEM_8,
		KID_OEM_102,
		KID_OEM_COMMA,
		KID_OEM_PERIOD,
		KID_A,
		KID_B,
		KID_C,
		KID_D,
		KID_E,
		KID_F,
		KID_G,
		KID_H,
		KID_I,
		KID_J,
		KID_K,
		KID_L,
		KID_M,
		KID_N,
		KID_O,
		KID_P,
		KID_Q,
		KID_R,
		KID_S,
		KID_T,
		KID_U,
		KID_V,
		KID_W,
		KID_X,
		KID_Y,
		KID_Z,
		KID_ESCAPE,
		KID_TAB,
		KID_RETURN,
		KID_SPACE,
		KID_BACK,
		KID_DELETE,
		KID_INSERT,
		KID_NUMLOCK,
		KID_LSHIFT,
		KID_RSHIFT,
		KID_LCONTROL,
		KID_RCONTROL,
		KID_LWIN,
		KID_RWIN,
		KID_LMENU,
		KID_RMENU,
		KID_LEFT,
		KID_UP,
		KID_RIGHT,
		KID_DOWN,
		KID_PRIOR,
		KID_NEXT,
		KID_END,
		KID_HOME,
		KID_NUMPAD0,
		KID_NUMPAD1,
		KID_NUMPAD2,
		KID_NUMPAD3,
		KID_NUMPAD4,
		KID_NUMPAD5,
		KID_NUMPAD6,
		KID_NUMPAD7,
		KID_NUMPAD8,
		KID_NUMPAD9,
		KID_DIVIDE,
		KID_MULTIPLY,
		KID_SUBTRACT,
		KID_ADD,
		KID_SEPARATOR,
		KID_DECIMAL,
		Keyboard_Count
	};

	enum AxisID : byte
	{
		Axis_None,
		Axis_X,
		Axis_Y,
		Axis_Z,
		Axis_RX,
		Axis_RY,
		Axis_RZ,
		Axis_SL0,
		Axis_SL1,

		Axis_DIX,
		Axis_DIY,
		Axis_DIZ,
		Axis_DIRX,
		Axis_DIRY,
		Axis_DIRZ,
		Axis_SLIDER1,
		Axis_SLIDER2,

		Axis_ROLL,
		Axis_YAW,
		Axis_PITCH,
		Axis_SIDEWARD,
		Axis_TOWARD,
		Axis_LEVEL,
		
		Axis_MOUSEX,
		Axis_MOUSEY,
		Axis_MOUSEZ,
		Axis_Count
	};

	enum OffsetsID : byte
	{
		Offset_LX,
		Offset_LY,
		Offset_RX,
		Offset_RY,
		Offset_L2,
		Offset_R2,
		Offset_SL0,
		Offset_SL1,
		Offset_BUTTON1,
		Offset_BUTTON2,
		Offset_DPAD,
		Offset_DIVERSE,

		Offset_ROLL,
		Offset_ROLL_TRIGGER,
		Offset_ROLL_BUTTONS,
		Offset_YAW,
		Offset_YAW_TRIGGER,
		Offset_YAW_BUTTONS,
		Offset_PITCH,
		Offset_PITCH_TRIGGER,
		Offset_PITCH_BUTTONS,
		Offset_SIDEWARD,
		Offset_SIDEWARD_TRIGGER,
		Offset_SIDEWARD_BUTTONS,
		Offset_TOWARD,
		Offset_TOWARD_TRIGGER,
		Offset_TOWARD_BUTTONS,
		Offset_LEVEL,
		Offset_LEVEL_TRIGGER,
		Offset_LEVEL_BUTTONS,
		Offset_WHEEL,
		Offset_QUARTER,

		Offset_MOUSE_AXEX,
		Offset_MOUSE_AXEY,
		Offset_MOUSE_AXEZ,
		Offset_MOUSE_LEFT,
		Offset_MOUSE_RIGHT,
		Offset_MOUSE_UP,
		Offset_MOUSE_DOWN,
		Offset_KEYBOARD1,
		Offset_KEYBOARD2,
		Offset_KEYBOARD3,
		Offset_KEYBOARD4,
		Offset_KEYBOARD5,
		Offset_KEYBOARD6,
		Offset_KEYBOARD7,
		Offset_Count
	};

	SourceButton();
	~SourceButton();

	void					setConstant(unsigned short constant);
	void					setButton(byte offset, unsigned short bitmask);
	void					setTrigger(byte offset, unsigned short threshold);
	void					setSimultaneous(byte offset, unsigned short bitmask, byte offset2, unsigned short bitmask2, ButtonID bumper);
	void					setTouch(byte offset, unsigned short bitmask, unsigned char box);
	void					setAxis(byte offset, byte offset2, AxisID axis);
	void					setAxisInv(byte offset, byte offset2, AxisID axis);
	void					setAxisSolo(byte offset, AxisID axis);
	void					setAxisInvSolo(byte offset, AxisID axis);
	void					setAxisSniper(byte offset, byte offset2);
	void					setAxisTriggerLU(byte offset);
	void					setAxisTriggerRD(byte offset);
	void					setAxisLU(byte offset);
	void					setAxisRD(byte offset);
	void					setAxisDUL(byte offset, byte offset2);
	void					setAxisDUR(byte offset, byte offset2);
	void					setAxisDDR(byte offset, byte offset2);
	void					setAxisDDL(byte offset, byte offset2);
	void					setData(ButtonID batterytype);

	void					SetTouchBox(unsigned char box, bool value);
	BOOL					isPushed();
	unsigned short			GetVal();
	unsigned short			GetReleasedVal();
	int						GetScrollVal();
	void					SetThreshold(bool thr = true);

	static const WCHAR*		String(ButtonID);

private:
	byte					m_offset = 0;
	byte					m_offset2 = 0;				// >> & box touch,1,2,3,4,L,R,all,up (setTouch)
	unsigned short			m_mask = 0;					// >> & threshold (setTrigger)
	unsigned short			m_mask2 = 0;				// >> & constant (setConstant)
	ButtonType				m_type = Type_None;
	ButtonID				m_btid = Button_None;
	AxisID					m_axis = Axis_None;
};

	static clock_t			L1R1_LastTimePushed = clock();
	static bool				L1R1_Delay_On = false;
	static bool				L1R1_Eligible = true;
	static bool				L1R1_Pushed = false;
	static clock_t			L2R2_LastTimePushed = clock();
	static bool				L2R2_Delay_On = false;
	static bool				L2R2_Eligible = true;
	static bool				L2R2_Pushed = false;

	static bool				OrangeLedActive = false;
	static bool				threshold[SourceButton::Axis_Count] = { true };
	static byte				TouchAble[7] = { 0, 0, 0, 0, 0, 0, 0 };		//touch,1,2,3,4,L,R
	
	typedef					SourceButton::ButtonID SrceButtonID;
	typedef					SourceButton::AxisID SrceAxisID;
	typedef					SourceButton::OffsetsID SrceOffsetsID;
	static SourceButton		m_buttons[SourceButton::Keyboard_Count];