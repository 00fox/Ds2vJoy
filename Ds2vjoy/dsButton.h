#pragma once

class dsButton
{
public:
	enum ButtonType
	{
		typeNone = 0,
		typeConstant,
		typeButton,
		typeTrigger,
		typeSimultaneous,
		typeTouch,
		typeDPad,
		typeDPadUP,
		typeDPadRIGHT,
		typeDPadDOWN,
		typeDPadLEFT,
		typeAxis,
		typeAxisInv,
		typeAxisLU,
		typeAxisRD,
		typeAxisDUL,
		typeAxisDUR,
		typeAxisDDR,
		typeAxisDDL,
		typeData,
	};

	enum ButtonID {
		none = 0,
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

	dsButton();
	~dsButton();

	void setConstant(BYTE data);
	void setButton(BYTE* data, UINT32 bitmask);
	void setTrigger(BYTE* data, INT threshold);
	void setSimultaneous(BYTE* data, UINT32 bitmask, BYTE* data2, UINT32 bitmask2);
	void setTouch(BYTE* data, UINT32 bitmask, int box);
	void setDPad(BYTE* data, ButtonType type);
	void setAxis(BYTE* data, BYTE* data2);
	void setAxisInv(BYTE* data, BYTE* data2);
	void setAxisLU(BYTE* data);
	void setAxisRD(BYTE* data);
	void setAxisDUL(BYTE* data, BYTE* data2);
	void setAxisDUR(BYTE* data, BYTE* data2);
	void setAxisDDR(BYTE* data, BYTE* data2);
	void setAxisDDL(BYTE* data, BYTE* data2);
	void setData(BYTE* data, UINT32 bitmask);

	void SetTouch(int box, BYTE value);
	BOOL isPushed();
	BYTE GetVal();
	BYTE GetReleasedVal();
	int GetScrollVal();

	static WCHAR *String(ButtonID);

private:
	ButtonType m_type;
	BYTE* m_data;
	BYTE* m_data2;
	BYTE m_constant;
	int m_box;											//touch,1,2,3,4,L,R,all,up
	UINT32 m_mask;
	UINT32 m_mask2;
	INT m_thrz;
	BYTE m_typechoice;
	BYTE dpad;

	bool OrangeLedActive = false;
	clock_t L2R2_LastTimePushed;
	bool L2R2_Delay_On = false;
	bool L2R2_Eligible = true;
	bool L2R2_Pushed = false;
};

typedef dsButton::ButtonID dsButtonID;
static BYTE TouchAble[7] = { 0, 0, 0, 0, 0, 0, 0 };		//touch,1,2,3,4,L,R
