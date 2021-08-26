#pragma once
#include "dsButton.h"

class vJoyButton {

public:
	enum ButtonType
	{
		typeNone,
		typeButton,
		typeTrigger,
		typeAxis,
		typeAxisInv,
		typeDPad,
	};
	enum ButtonID {
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

	vJoyButton();
	~vJoyButton();

	void setButton(LONG* data, UINT32 bitmask);
	void setTrigger(LONG* data);
	void setAxis(LONG* data);
	void setAxisInv(LONG* data);
	void setDPad(BYTE* data);

	BOOL isPushed();
	void SetPushed(bool ispushed = true);
	void Release();

	LONG GetVal();
	BYTE GetVal2();
	BYTE GetReleasedVal();
	int GetScrollVal();
	void SetVal(BYTE);

	static WCHAR* String(ButtonID);

private:
	ButtonType m_type;
	LONG*	m_data;
	BYTE*	m_dataDPad;
	UINT32	m_mask;
	bool	m_isPushed;
};

typedef vJoyButton::ButtonID vJoyButtonID;
