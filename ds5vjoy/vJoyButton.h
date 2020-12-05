#pragma once
#include "DS5Button.h"

class vJoyButton {
public:

	enum ButtonType
	{
		typeNone = 0,
		typeBit,
		typeAxis,
		typePOV,
		typeButton
	};
	enum ButtonID {
		none = 0,
		X,
		Y,
		Z,
		RX,
		RY,
		RZ,
		SL0,
		SL1,
		POV1,
		POV2,
		POV3,
		POV4,
		Button1,
		Button128= Button1 + 127,
		button_Count,
	};
private:
	ButtonType m_type;
	LONG *m_data;
	UINT32 m_mask;//bit
	bool	m_exists;
	LONG	m_AxisMin;
	LONG	m_AxisMaxMin;
	LONG	m_AxisDefault;
	LONG	m_AxisThreshold;
public:
	vJoyButton();
	void setBit(LONG*data, UINT32 bitmask);
	void setAxis(LONG *data,LONG min,LONG max);
	void setPOV(LONG*data);
	~vJoyButton();
	BOOL isPushed();
	void Release();
	LONG GetVal();
	void SetVal(BYTE);
	static WCHAR * String(ButtonID);
};

typedef vJoyButton::ButtonID vJoyButtonID;
