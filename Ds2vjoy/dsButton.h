#pragma once

class dsButton
{
public:
	enum ButtonType
	{
		Type_None,
		Type_Constant,
		Type_Button,
		Type_Trigger,
		Type_Simultaneous,
		Type_Touch,
		Type_DPad,
		Type_DPadUP,
		Type_DPadRIGHT,
		Type_DPadDOWN,
		Type_DPadLEFT,
		Type_Axis,
		Type_AxisInv,
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

	enum ButtonID {
		none,
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
		L2TRIGGER,
		R2TRIGGER,
		EMPTY,
		MIDDLE,
		FULL,
		LXINV,
		LYINV,
		RXINV,
		RYINV,
		SNIPER_LX,
		SNIPER_LY,
		SNIPER_RX,
		SNIPER_RY,
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
		L2TRIGGER_33,
		R2TRIGGER_33,
		L2TRIGGER_66,
		R2TRIGGER_66,
		L2TRIGGER_100,
		R2TRIGGER_100,
		L1R1,
		L2R2,
		BATTERY,
		button_Count
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
		axis_Count
	};

	dsButton();
	~dsButton();

	void setConstant(byte data);
	void setButton(byte* data, unsigned int bitmask);
	void setTrigger(byte* data, int threshold);
	void setSimultaneous(byte* data, unsigned int bitmask, byte* data2, unsigned int bitmask2);
	void setTouch(byte* data, unsigned int bitmask, int box);
	void setDPad(byte* data, ButtonType type);
	void setAxis(byte* data, byte* data2, unsigned char axis);
	void setAxisSniper(byte* data, byte* data2);
	void setAxisInv(byte* data, byte* data2, unsigned char axis);
	void setAxisTriggerLU(byte* data);
	void setAxisTriggerRD(byte* data);
	void setAxisLU(byte* data);
	void setAxisRD(byte* data);
	void setAxisDUL(byte* data, byte* data2);
	void setAxisDUR(byte* data, byte* data2);
	void setAxisDDR(byte* data, byte* data2);
	void setAxisDDL(byte* data, byte* data2);
	void setData(byte* data, unsigned int bitmask);

	void SetTouch(int box, byte value);
	BOOL isPushed();
	byte GetVal();
	byte GetReleasedVal();
	int GetScrollVal();

	void SetThreshold(bool thr = true);

	static WCHAR *String(ButtonID);

private:
	ButtonType m_type;
	byte* m_data;
	byte* m_data2;
	byte m_constant;
	int m_box;											//touch,1,2,3,4,L,R,all,up
	unsigned int m_mask;
	unsigned int m_mask2;
	int m_thrz;
	char m_axis;
	byte m_typechoice;
	byte dpad;

	bool OrangeLedActive;
	clock_t L2R2_LastTimePushed;
	bool L2R2_Delay_On;
	bool L2R2_Eligible;
	bool L2R2_Pushed;
};

static bool threshold[4] = { true };
static byte TouchAble[7] = { 0, 0, 0, 0, 0, 0, 0 };		//touch,1,2,3,4,L,R

typedef dsButton::ButtonID dsButtonID;
typedef dsButton::AxisID dsAxisID;
