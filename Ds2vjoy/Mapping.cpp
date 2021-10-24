#include "stdafx.h"
#include "Mapping.h"
#include "Ds2vJoy.h"

Mapping::Mapping()
	:Enable(0)
	, Tab(0)
	, Ifmouse(0)
	, Force(0)
	, Short(false)
	, Double(false)
	, Long(false)
	, Led(0)
	, Macro(0)
	, Pause(0)
	, Transitivity(0)
	, Toggle(0)
	, Target()
	, dsID()
	, OrXorNot()
	, dsDisable()
	, MouseAction()
	, vjID()
	, Overcontrol()
	, Switch()
	, OnRelease()
	, NoRelease()
	, NlRelease()
	, vjDisable()
	, Start()
	, Stop()
	, Mouse()
	, Grid()
	, Notice(L"")
{
	for (int i = 0; i < 5; i++) { Target[i] = false; }
	for (int i = 0; i < 5; i++) { dsID[i] = dsButtonID::none; }
	for (int i = 0; i < 4; i++) { OrXorNot[i] = 0; }
	for (int i = 0; i < 5; i++) { dsDisable[i] = 0; }
	for (int i = 0; i < 8; i++) { MouseAction[i] = 0; }
	for (int i = 0; i < 8; i++) { vjID[i] = vJoyButtonID::none; }
	for (int i = 0; i < 8; i++) { Overcontrol[i] = 0; }
	for (int i = 0; i < 8; i++) { Switch[i] = 0; }
	for (int i = 0; i < 8; i++) { OnRelease[i] = 0; }
	for (int i = 0; i < 8; i++) { NoRelease[i] = 0; }
	for (int i = 0; i < 8; i++) { NlRelease[i] = 0; }
	for (int i = 0; i < 8; i++) { vjDisable[i] = 0; }
	for (int i = 0; i < 8; i++) { Start[i] = 0; }
	for (int i = 0; i < 8; i++) { Stop[i] = 0; }
	for (int i = 0; i < 7; i++) { Mouse[i] = 0; }
	for (int i = 0; i < 6; i++) { Grid[i] = 0; }
}

Mapping::~Mapping()
{
}

const WCHAR* Mapping::dsString()
{
	if (Enable == 2)
	    return L"▒▒▒▒▒▒";

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	std::wstring str;
	if (Target[0])
	{
		if (dsID[0] != vJoyButton::none)
			str = vJoyButton::String((vJoyButtonID)dsID[0]);
	}
	else
	{
		if (dsID[0] != dsButton::none)
			str = dsButton::String((dsButtonID)dsID[0]);
	}

	head += wsprintf(head, L"%s", str.c_str());

	if (dsDisable[0])
	{
		if (str.length() > 7)
			*(--head) = 0;
		if (dsDisable[0] == 2)
			head += wsprintf(head, L"✱");
		else
			head += wsprintf(head, L"#");
	}

	return buf;
}

const WCHAR* Mapping::dsLastString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒";

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	std::wstring str;
	for (int i = 1; i < 5; i++)
	{
		str = L"";
		if (Target[i])
		{
			if (dsID[i] != vJoyButton::none)
				str = vJoyButton::String((vJoyButtonID)dsID[i]);
			else
				continue;
		}
		else
		{
			if (dsID[i] != dsButton::none)
				str = dsButton::String((dsButtonID)dsID[i]);
			else
				continue;
		}

		if (i < 3 && OrXorNot[i - 1] == 1)
			head += wsprintf(head, L"||");
		else if (i < 3 && OrXorNot[i - 1] == 2)
			head += wsprintf(head, L" ⊕");
		else if (i > 2 && OrXorNot[i - 1])
			continue;
		else
			head += wsprintf(head, L" +");

		head += wsprintf(head, L"%s", str.c_str());

		if (dsDisable[i])
		{
			if (str.length() > 7)
				*(--head) = 0;
			if (dsDisable[i] == 2)
				head += wsprintf(head, L"✱");
			else
				head += wsprintf(head, L"#");
		}
	}

	return buf;
}

const WCHAR* Mapping::dsNotString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒";

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	std::wstring str;
	for (int i = 3; i < 5; i++)
	{
		str = L"";
		if (Target[i])
		{
			if (dsID[i] != vJoyButton::none)
				str = vJoyButton::String((vJoyButtonID)dsID[i]);
			else
				continue;
		}
		else
		{
			if (dsID[i] != dsButton::none)
				str = dsButton::String((dsButtonID)dsID[i]);
			else
				continue;
		}

		if (i > 2 && OrXorNot[i - 1] == 1)
			head += wsprintf(head, L" -");
		else if (i > 2 && OrXorNot[i - 1])
			head += wsprintf(head, L"--");
		else
			continue;

		head += wsprintf(head, L"%s", str.c_str());

		if (dsDisable[i])
		{
			if (str.length() > 7)
				*(--head) = 0;
			if (dsDisable[i] == 2)
				head += wsprintf(head, L"✱");
			else
				head += wsprintf(head, L"#");
		}
	}

	return buf;
}

const WCHAR* Mapping::vJoyString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒▒▒▒";

	bool firstplus = false;
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	for (int i = 0; i < 8; i++)
	{
		if (firstplus)
		{
			if (MouseAction[i] == 1)
				head += wsprintf(head, L" %s", MouseString((MouseActionID)vjID[i]));
			else if (MouseAction[i] == 2)
				head += wsprintf(head, L" %s", vJoyButton::StringAxis((vJoyAxisMoveID)vjID[i]));
			else if(vjID[i] != vJoyButton::none)
				head += wsprintf(head, L" %s", vJoyButton::String((vJoyButtonID)vjID[i]));
		}
		else
		{
			if (MouseAction[i] == 1)
				{ head += wsprintf(head, L"%s", MouseString((MouseActionID)vjID[i])); firstplus = true; }
			else if (MouseAction[i] == 2)
				{ head += wsprintf(head, L"%s", vJoyButton::StringAxis((vJoyAxisMoveID)vjID[i])); firstplus = true; }
			else if (vjID[i] != vJoyButton::none)
				{ head += wsprintf(head, L"%s", vJoyButton::String((vJoyButtonID)vjID[i])); firstplus = true; }
		}

		if (vjDisable[i] == 1)
			head += wsprintf(head, L"#");
		else if (vjDisable[i])
			head += wsprintf(head, L">");
	}

	if (Led)
		if (firstplus)
		{
			if (Led == 6)
				head += wsprintf(head, L" Battery status");
			else
				head += wsprintf(head, L" Led%d", Led);
		}
		else
		{
			if (Led == 6)
				head += wsprintf(head, L"Battery status");
			else
				head += wsprintf(head, L"Led%d", Led);
			firstplus = true;
		}

	return buf;
}

const WCHAR* Mapping::NoticeString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	WCHAR* ret = lstrcpynW(head, Notice, MAX_PATH);

	return buf;
}

const WCHAR* Mapping::TagsString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒";

	bool firstplus = false;
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Ifmouse == 1)
		head += wsprintf(head, L"I");
	else if (Ifmouse)
		head += wsprintf(head, L"i");
	else
		head += wsprintf(head, L" ");

	if (Force == 1)
		head += wsprintf(head, L"F");
	else if (Force)
		head += wsprintf(head, L"f");
	else
		head += wsprintf(head, L"  ");

	if (Short)
		head += wsprintf(head, L"S");
	else
		head += wsprintf(head, L"  ");

	if (Double)
		head += wsprintf(head, L"D");
	else
		head += wsprintf(head, L"  ");

	if (Long)
		head += wsprintf(head, L"L");
	else
		head += wsprintf(head, L"  ");

	if (Macro == 1)
		head += wsprintf(head, L"C");
	else if (Macro)
		head += wsprintf(head, L"c");
	else
		head += wsprintf(head, L"  ");

	if (Pause == 1)
		head += wsprintf(head, L"P");
	else if (Pause)
		head += wsprintf(head, L"p");
	else
		head += wsprintf(head, L"  ");

	if (Transitivity == 1)
		head += wsprintf(head, L"Y");
	else if (Transitivity)
		head += wsprintf(head, L"y");
	else
		head += wsprintf(head, L"  ");

	if (Toggle == 1)
		head += wsprintf(head, L"T");
	else if (Toggle)
		head += wsprintf(head, L"t");
	else
		head += wsprintf(head, L"  ");

	if (NoRelease[0] || NoRelease[1] || NoRelease[2] || NoRelease[3] || NoRelease[4] || NoRelease[5] || NoRelease[6] || NoRelease[7])
	{
		if (OnRelease[0] == 1 || OnRelease[1] == 1 || OnRelease[2] == 1 || OnRelease[3] == 1 || OnRelease[4] == 1 || OnRelease[5] == 1 || OnRelease[6] == 1 || OnRelease[7] == 1)
		{
			if (NlRelease[0] || NlRelease[1] || NlRelease[2] || NlRelease[3] || NlRelease[4] || NlRelease[5] || NlRelease[6] || NlRelease[7])
				head += wsprintf(head, L"W");
			else
				head += wsprintf(head, L"Z");
		}
		else if (OnRelease[0] || OnRelease[1] || OnRelease[2] || OnRelease[3] || OnRelease[4] || OnRelease[5] || OnRelease[6] || OnRelease[7])
		{
			if (NlRelease[0] || NlRelease[1] || NlRelease[2] || NlRelease[3] || NlRelease[4] || NlRelease[5] || NlRelease[6] || NlRelease[7])
				head += wsprintf(head, L"w");
			else
				head += wsprintf(head, L"z");
		}
		else
			head += wsprintf(head, L"  ");
	}
	else
	{
		if (OnRelease[0] == 1 || OnRelease[1] == 1 || OnRelease[2] == 1 || OnRelease[3] == 1 || OnRelease[4] == 1 || OnRelease[5] == 1 || OnRelease[6] == 1 || OnRelease[7] == 1)
			head += wsprintf(head, L"R");
		else if (OnRelease[0] || OnRelease[1] || OnRelease[2] || OnRelease[3] || OnRelease[4] || OnRelease[5] || OnRelease[6] || OnRelease[7])
			head += wsprintf(head, L"r");
		else
			head += wsprintf(head, L"  ");
	}

	if (Mouse[0] || Mouse[1] || Mouse[2] || Mouse[6])
	{
		if (!Mouse[3] && !Mouse[4] && !Mouse[5])
			head += wsprintf(head, L"M");
		else
			head += wsprintf(head, L"m");

	}
	else
		head += wsprintf(head, L"  ");

	return buf;
}

const WCHAR* Mapping::vJoyButtons()
{
	return vJoyButtonsString;
}

void Mapping::PreLoad()
{
	vjUsed.clear();
	vJoyButtonsString[0] = 0;
	for (int i = 0; i < vJoyButtonID::button_Count; i++)
		m_toggle[i] = false;
	for (int i = 0; i < 8; i++)
		mouse_toggle[i] = false;
	for (int i = 0; i < Led_Action_Count; i++)
		Ledactive[i] = false ;
}

BOOL Mapping::LoadDevice(dsDevice* ds, vJoyDevice* vjoy)
{
	if (Enable != 1)
		return FALSE;

	m_vj_X = vjoy->GetButton(vJoyButtonID::X);
	m_vj_Y = vjoy->GetButton(vJoyButtonID::Y);
	m_vj_Z = vjoy->GetButton(vJoyButtonID::Z);
	m_vj_RX = vjoy->GetButton(vJoyButtonID::RX);
	m_vj_RY = vjoy->GetButton(vJoyButtonID::RY);
	m_vj_RZ = vjoy->GetButton(vJoyButtonID::RZ);
	m_vj_SL0 = vjoy->GetButton(vJoyButtonID::SL0);
	m_vj_SL1 = vjoy->GetButton(vJoyButtonID::SL1);

	mode = 1;
	lastmode = 1;
	locked = 0;
	modechanged = 0;
	for (int i = 0; i < 8; i++)
		modedest[i] = 0;
	tomode = -1;
	m_ds[0] = (dsID[0] && !Target[0]) ? ds->GetButton((dsButtonID)dsID[0]) : 0;
	m_ds[1] = (dsID[1] && !Target[1]) ? ds->GetButton((dsButtonID)dsID[1]) : 0;
	m_ds[2] = (dsID[2] && !Target[2]) ? ds->GetButton((dsButtonID)dsID[2]) : 0;
	m_ds[3] = (dsID[3] && !Target[3]) ? ds->GetButton((dsButtonID)dsID[3]) : 0;
	m_ds[4] = (dsID[4] && !Target[4]) ? ds->GetButton((dsButtonID)dsID[4]) : 0;
	m_vj[0] = (dsID[0] && Target[0]) ? vjoy->GetButton((vJoyButtonID)dsID[0]) : 0;
	m_vj[1] = (dsID[1] && Target[1]) ? vjoy->GetButton((vJoyButtonID)dsID[1]) : 0;
	m_vj[2] = (dsID[2] && Target[2]) ? vjoy->GetButton((vJoyButtonID)dsID[2]) : 0;
	m_vj[3] = (dsID[3] && Target[3]) ? vjoy->GetButton((vJoyButtonID)dsID[3]) : 0;
	m_vj[4] = (dsID[4] && Target[4]) ? vjoy->GetButton((vJoyButtonID)dsID[4]) : 0;
	m_vj[5] = (vjID[0] && !MouseAction[0]) ? vjoy->GetButton((vJoyButtonID)vjID[0]) : ((vjID[0] && MouseAction[0] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[0]) : 0);
	m_vj[6] = (vjID[1] && !MouseAction[1]) ? vjoy->GetButton((vJoyButtonID)vjID[1]) : ((vjID[1] && MouseAction[1] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[1]) : 0);
	m_vj[7] = (vjID[2] && !MouseAction[2]) ? vjoy->GetButton((vJoyButtonID)vjID[2]) : ((vjID[2] && MouseAction[2] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[2]) : 0);
	m_vj[8] = (vjID[3] && !MouseAction[3]) ? vjoy->GetButton((vJoyButtonID)vjID[3]) : ((vjID[3] && MouseAction[3] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[3]) : 0);
	m_vj[9] = (vjID[4] && !MouseAction[4]) ? vjoy->GetButton((vJoyButtonID)vjID[4]) : ((vjID[4] && MouseAction[4] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[4]) : 0);
	m_vj[10] = (vjID[5] && !MouseAction[5]) ? vjoy->GetButton((vJoyButtonID)vjID[5]) : ((vjID[5] && MouseAction[5] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[5]) : 0);
	m_vj[11] = (vjID[6] && !MouseAction[6]) ? vjoy->GetButton((vJoyButtonID)vjID[6]) : ((vjID[6] && MouseAction[6] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[6]) : 0);
	m_vj[12] = (vjID[7] && !MouseAction[7]) ? vjoy->GetButton((vJoyButtonID)vjID[7]) : ((vjID[7] && MouseAction[7] == 2) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[7]) : 0);


	for (int i = 0; i < 8; i++)
	{
		if (m_vj[i + 5] && Overcontrol[i] == 1)
		{
			if (MouseAction[i] == 0)
				switch (vjID[i])
				{
				case vJoyButtonID::X:
				case vJoyButtonID::XTR:
				case vJoyButtonID::XINV:
					ds->GetButton(dsButtonID::LX)->SetThreshold(false);
					break;
				case vJoyButtonID::Y:
				case vJoyButtonID::YTR:
				case vJoyButtonID::YINV:
					ds->GetButton(dsButtonID::LY)->SetThreshold(false);
					break;
				case vJoyButtonID::Z:
				case vJoyButtonID::ZTR:
				case vJoyButtonID::ZINV:
					ds->GetButton(dsButtonID::RX)->SetThreshold(false);
					break;
				case vJoyButtonID::RZ:
				case vJoyButtonID::RZTR:
				case vJoyButtonID::RZINV:
					ds->GetButton(dsButtonID::RY)->SetThreshold(false);
					break;
				}
			else if (MouseAction[i] == 2)
				if (vjID[i] == vJoyAxisMoveID::XY_CW || vjID[i] == vJoyAxisMoveID::XY_CN || (vjID[i] >= vJoyAxisMoveID::XY_CENTER && vjID[i] <= vJoyAxisMoveID::XY_L_DL_CN))
				{
					ds->GetButton(dsButtonID::LX)->SetThreshold(false);
					ds->GetButton(dsButtonID::LY)->SetThreshold(false);
				}
				else if (vjID[i] == vJoyAxisMoveID::ZRZ_CW || vjID[i] == vJoyAxisMoveID::ZRZ_CN || (vjID[i] >= vJoyAxisMoveID::ZRZ_CENTER && vjID[i] <= vJoyAxisMoveID::ZRZ_L_DL_CN))
				{
					ds->GetButton(dsButtonID::RX)->SetThreshold(false);
					ds->GetButton(dsButtonID::RY)->SetThreshold(false);
				}
		}

		if (!MouseAction[i])
		{
			if (!(std::find(vjUsed.begin(), vjUsed.end(), vjID[i]) != vjUsed.end()))
				if (vjID[i])
				{
					vjUsed.push_back(vjID[i]);
					switch (vjID[i])
					{
					case vJoyButton::ButtonID::Button1:tape.vJoyUsed[0] = true; break;
					case vJoyButton::ButtonID::Button2:tape.vJoyUsed[1] = true; break;
					case vJoyButton::ButtonID::Button3:tape.vJoyUsed[2] = true; break;
					case vJoyButton::ButtonID::Button4:tape.vJoyUsed[3] = true; break;
					case vJoyButton::ButtonID::Button5:tape.vJoyUsed[4] = true; break;
					case vJoyButton::ButtonID::Button6:tape.vJoyUsed[5] = true; break;
					case vJoyButton::ButtonID::Button7:tape.vJoyUsed[6] = true; break;
					case vJoyButton::ButtonID::Button8:tape.vJoyUsed[7] = true; break;
					case vJoyButton::ButtonID::Button9:tape.vJoyUsed[8] = true; break;
					case vJoyButton::ButtonID::Button10:tape.vJoyUsed[9] = true; break;
					case vJoyButton::ButtonID::Button11:tape.vJoyUsed[10] = true; break;
					case vJoyButton::ButtonID::Button12:tape.vJoyUsed[11] = true; break;
					case vJoyButton::ButtonID::Button13:tape.vJoyUsed[12] = true; break;
					case vJoyButton::ButtonID::Button14:tape.vJoyUsed[13] = true; break;
					case vJoyButton::ButtonID::Button15:tape.vJoyUsed[14] = true; break;
					case vJoyButton::ButtonID::Button16:tape.vJoyUsed[15] = true; break;
					case vJoyButton::ButtonID::Button17:tape.vJoyUsed[16] = true; break;
					case vJoyButton::ButtonID::Button18:tape.vJoyUsed[17] = true; break;
					case vJoyButton::ButtonID::Button19:tape.vJoyUsed[18] = true; break;
					case vJoyButton::ButtonID::Button20:tape.vJoyUsed[19] = true; break;
					case vJoyButton::ButtonID::Button21:tape.vJoyUsed[20] = true; break;
					case vJoyButton::ButtonID::Button22:tape.vJoyUsed[21] = true; break;
					case vJoyButton::ButtonID::Button23:tape.vJoyUsed[22] = true; break;
					case vJoyButton::ButtonID::Button24:tape.vJoyUsed[23] = true; break;
					case vJoyButton::ButtonID::Button25:tape.vJoyUsed[24] = true; break;
					case vJoyButton::ButtonID::Button26:tape.vJoyUsed[25] = true; break;
					case vJoyButton::ButtonID::Button27:tape.vJoyUsed[26] = true; break;
					case vJoyButton::ButtonID::Button28:tape.vJoyUsed[27] = true; break;
					case vJoyButton::ButtonID::Button29:tape.vJoyUsed[28] = true; break;
					case vJoyButton::ButtonID::Button30:tape.vJoyUsed[29] = true; break;
					case vJoyButton::ButtonID::Button31:tape.vJoyUsed[30] = true; break;
					case vJoyButton::ButtonID::Button32:tape.vJoyUsed[31] = true; break;
					}
				}
		}
	}

	if (Toggle == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (MouseAction[i] == 1)
			{
				if ((MouseActionID)vjID[i] == ACTIVE_MOUSE)
					mouse_toggle[i] = true;
				else
					continue;
			}
			else if (!MouseAction[i] && !Switch[i])
				if (m_vj[i + 5])
				{
					m_toggle[vjID[i]] = true;
					m_vj[i + 5]->SetValByte(0xFF);
					m_vj[i + 5]->SetPushed();
				}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		exists[i] = (Target[i]) ? ((m_vj[i]) ? true : false) : ((m_ds[i]) ? true : false);
		releasedVal[i] = (byte)((exists[i]) ? ((Target[i]) ? (m_vj[i] ? m_vj[i]->GetReleasedVal() : 0) : (m_ds[i] ? m_ds[i]->GetReleasedVal() : 0)) : 0);
	}


	GridCanbeUsed =
		vjID[0] != MOVE_TO_XY && vjID[0] != SAVE_AND_MOVE_TO_XY &&
		vjID[0] != MOVE_TO_WH && vjID[0] != SAVE_AND_MOVE_TO_WH &&
		vjID[0] != MOVE_TO_NN && vjID[0] != SAVE_AND_MOVE_TO_NN &&
			vjID[1] != MOVE_TO_XY && vjID[1] != SAVE_AND_MOVE_TO_XY &&
			vjID[1] != MOVE_TO_WH && vjID[1] != SAVE_AND_MOVE_TO_WH &&
			vjID[1] != MOVE_TO_NN && vjID[1] != SAVE_AND_MOVE_TO_NN &&
		vjID[2] != MOVE_TO_XY && vjID[2] != SAVE_AND_MOVE_TO_XY &&
		vjID[2] != MOVE_TO_WH && vjID[2] != SAVE_AND_MOVE_TO_WH &&
		vjID[2] != MOVE_TO_NN && vjID[2] != SAVE_AND_MOVE_TO_NN &&
			vjID[3] != MOVE_TO_XY && vjID[3] != SAVE_AND_MOVE_TO_XY &&
			vjID[3] != MOVE_TO_WH && vjID[3] != SAVE_AND_MOVE_TO_WH &&
			vjID[3] != MOVE_TO_NN && vjID[3] != SAVE_AND_MOVE_TO_NN &&
		vjID[4] != MOVE_TO_XY && vjID[4] != SAVE_AND_MOVE_TO_XY &&
		vjID[4] != MOVE_TO_WH && vjID[4] != SAVE_AND_MOVE_TO_WH &&
		vjID[4] != MOVE_TO_NN && vjID[4] != SAVE_AND_MOVE_TO_NN &&
			vjID[5] != MOVE_TO_XY && vjID[5] != SAVE_AND_MOVE_TO_XY &&
			vjID[5] != MOVE_TO_WH && vjID[5] != SAVE_AND_MOVE_TO_WH &&
			vjID[5] != MOVE_TO_NN && vjID[5] != SAVE_AND_MOVE_TO_NN &&
		vjID[6] != MOVE_TO_XY && vjID[6] != SAVE_AND_MOVE_TO_XY &&
		vjID[6] != MOVE_TO_WH && vjID[6] != SAVE_AND_MOVE_TO_WH &&
		vjID[6] != MOVE_TO_NN && vjID[6] != SAVE_AND_MOVE_TO_NN &&
			vjID[7] != MOVE_TO_XY && vjID[7] != SAVE_AND_MOVE_TO_XY &&
			vjID[7] != MOVE_TO_WH && vjID[7] != SAVE_AND_MOVE_TO_WH &&
			vjID[7] != MOVE_TO_NN && vjID[7] != SAVE_AND_MOVE_TO_NN;

	release = std::chrono::system_clock::now();

	return TRUE;
}

void Mapping::RunFirst(vJoyDevice* vjoy)
{
	dsDisabled.clear();
	vjDisabled.clear();
	mouseabolute = 1;
	for (int i = 0; i < 3; i++)
		mousemode[i] = 0;
	for (int i = 0; i < 5; i++)
		grid[i] = 0;
	defaultmouse = 0;
	mouseactivated = false;
	for (int i = 0; i < vJoyButtonID::button_Count; i++)
	{
		if (m_toggle[i])
		{
			vjoy->GetButton((vJoyButtonID)i)->SetValByte(0xFF);
			vjoy->GetButton((vJoyButtonID)i)->SetPushed();
		}
		vjoy->GetButton((vJoyButtonID)i)->setOverwrite();
	}
	for (int i = 0; i < vJoyAxisMoveID::axismove_Count; i++)
		vjoy->GetAxis((vJoyAxisMoveID)i)->setOverwrite();
}

void Mapping::RunLast(dsDevice* ds, vJoyDevice* vjoy)
{
	vJoyButtonsString[0] = 0;
	WCHAR* head = vJoyButtonsString;

	m_vj_X->ResetCounter();
	m_vj_Y->ResetCounter();
	m_vj_Z->ResetCounter();
	m_vj_RX->ResetCounter();
	m_vj_RY->ResetCounter();
	m_vj_RZ->ResetCounter();
	m_vj_SL0->ResetCounter();
	m_vj_SL1->ResetCounter();

	for (int i = 0; i < vjUsed.size(); i++)
	{
		if (!vjoy->GetButton((vJoyButtonID)vjUsed[i])->isPushed())
			vjoy->GetButton((vJoyButtonID)vjUsed[i])->Release();
		else
			head += wsprintf(head, L"%s ", vJoyButton::String((vJoyButtonID)vjUsed[i]));
	}

	if (tape.ActualDS == 2)
	{
		byte m_Whitetmp = 0x00;

		if (!Ledactive[Led_Action_Led1] && !Ledactive[Led_Action_Led2] && !Ledactive[Led_Action_Led3] && !Ledactive[Led_Action_Led4] && !Ledactive[Led_Action_Led5] && Ledactive[Led_Action_Battery])
		{
			if (battery < 20)
				m_Whitetmp = 0x01;
			else if (battery < 40)
				m_Whitetmp = 0x03;
			else if (battery < 60)
				m_Whitetmp = 0x07;
			else if (battery < 80)
				m_Whitetmp = 0x0b;
			else
				m_Whitetmp = 0x1b;
		}
		else
		{
			if (Ledactive[Led_Action_Led1])
				m_Whitetmp = 0x01;
			if (Ledactive[Led_Action_Led2])
				m_Whitetmp = m_Whitetmp | 0x02;
			if (Ledactive[Led_Action_Led3])
				m_Whitetmp = m_Whitetmp | 0x04;
			if (Ledactive[Led_Action_Led4])
				m_Whitetmp = m_Whitetmp | 0x08;
			if (Ledactive[Led_Action_Led5])
				m_Whitetmp = m_Whitetmp | 0x10;
		}

		ds->SetWhiteLED(m_Whitetmp);
	}
}

void Mapping::Run(double average)
{
	if (tape.vJoyPaused)
		return;

	for (int i = 0; i < 5; i++)
		pushed[i] = (exists[i]) ? ((Target[i]) ? ((m_vj[i]->isPushed()) ? true : false) : ((m_ds[i]->isPushed()) ? true : false)) : false;

	for (int i = 0; i < 5; i++)
	{
		disabled[i] = false;
		if (Target[i])
		{
			if (m_vj[i])
				if (std::find(vjDisabled.begin(), vjDisabled.end(), dsID[i]) != vjDisabled.end())
					disabled[i] = true;
		}
		else
		{
			if (m_ds[i])
				if (std::find(dsDisabled.begin(), dsDisabled.end(), dsID[i]) != dsDisabled.end())
					disabled[i] = true;
		}
	}

	bool legits[5];
	if (Force == 1 || (Force == 2 && isRunning))
		for (int i = 0; i < 5; i++)
			legits[i] = (exists[i]) ? pushed[i] : true;
	else
		for (int i = 0; i < 5; i++)
			legits[i] = (exists[i]) ? (pushed[i] && !disabled[i]) : true;

	if (modechanged)
	{
		if (modechangedto != mode)
		{
			if (Transitivity == 2 && Pause == 2)
			{
				if (!(modechangedto != tape.Mode[Tab] && modechangedto != mode && mode != tape.Mode[Tab]))
					modechanged = min(3, modechanged++);
			}
			else
				modechanged = 2;
			modechangedto = mode;
		}
	}
//	else if (isRunning && tape.Mode[Tab] && tape.Mode[Tab] != mode && tomode != mode)
	else if (tape.Mode[Tab] && tape.Mode[Tab] != mode && tomode != mode)
	{
		if (isRunning || (!isRunning && !Transitivity && Pause == 2))
		{
			modechanged = 1;
			modechangedto = mode;
		}
		else
		{
//			modechanged = 3;
			locked = 3;
		}
	}
	else if (tomode)
		tomode = -1;

	for (int i = 0; i < 8; i++)
	{
		if (NoRelease[i])
		{
			(modedest[i]) = (modedest[i] && released && tomode != mode) ? 2 :
				((modechanged && !(NlRelease[i] == 1 && tape.Mode[Tab] == mode) && !(NlRelease[i] == 2 && tape.Mode[Tab] != mode)) ? ((NoRelease[i] == 2) ? 1 : 2) : 0);
		}
		if (OnRelease[i] && locked == 1 && tape.Mode[Tab] == mode && !Transitivity && Pause == 2)
			modedest[i] = 0;
	}

	if (!OrXorNot[0] && !OrXorNot[1])
	{
		legit =
			((Ifmouse) ? ((mouseactivated) ? Ifmouse == 1 : Ifmouse == 2) : true) &&
			legits[0] &&
			legits[1] &&
			legits[2] &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}
	else if (OrXorNot[0] && !OrXorNot[1])
	{
		legit =
			((Ifmouse) ? ((mouseactivated) ? Ifmouse == 1 : Ifmouse == 2) : true) &&
			((OrXorNot[0] == 2) ?
				(legits[0] ^ (exists[1] && legits[1])) :
				(legits[0] || (exists[1] && legits[1]))) &&
			legits[2] &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}
	else if (!OrXorNot[0] && OrXorNot[1])
	{
		legit =
			((Ifmouse) ? ((mouseactivated) ? Ifmouse == 1 : Ifmouse == 2) : true) &&
			legits[0] &&
			((OrXorNot[1] == 2) ?
				(legits[1] ^ (exists[2] && legits[2])) :
				(legits[1] || (exists[2] && legits[2]))) &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}
	else
	{
		legit =
			((Ifmouse) ? ((mouseactivated) ? Ifmouse == 1 : Ifmouse == 2) : true) &&
			((OrXorNot[0] == 2) ?
				(legits[0] ^ (exists[1] && legits[1])) :
				(legits[0] || (exists[1] && legits[1]))) &&
			((OrXorNot[1] == 2) ?
				(legits[0] ^ (exists[2] && legits[2])) :
				(legits[0] || (exists[2] && legits[2]))) &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}
	if (locked == 0)
		if (modechanged == 1)
			locked = 1;
	if (modechanged > 2)
		locked = 3;
	if (locked == 1 && !legit && released)
		locked = 2;
	if (locked == 2 && mode != tomode && legit)
		locked = 3;
	bool lasttest = (legit && Transitivity == 1 && Pause != 2 && modechanged);
//	if (((tape.Mode[Tab] == mode) && (!legit || (!Transitivity && Pause == 2))) || lasttest)
	if ((tape.Mode[Tab] == mode && !legit) || lasttest)
	{
		locked = 0;
		tomode = -1;
		if (lasttest)
			modechanged = 1;
//		else if (Transitivity || Pause != 2)
		else
			modechanged = 0;
	}
	else if (!lasttest)
		if (tape.Mode[Tab] && tape.Mode[Tab] != mode)
		{
			//if (legit && isRunning && !Transitivity && Pause == 2 && modechanged)
			if (!Transitivity && Pause == 2)
			{
				locked = 0;
				tomode = -1;
				modechanged = 0;
				legit = false;
				for (int i = 0; i < 8; i++)
					modedest[i] = 0;
			}
			else if (!(isRunning && Transitivity == 1 && Pause == 2))
				legit = false;
		}
	if (locked == 3)
		legit = false;

	if (!isRunning)
	{
		if (!method || killed)
		{
			if (Short && Long && Double) method = 8;
			else if (Short && Long) method = 7;
			else if (Double && Long) method = 6;
			else if (Double && Short) method = 5;
			else if (Long) method = 4;
			else if (Short) method = 3;
			else if (Double) method = 2;
			else method = 1;
		}

		if (legit && ((secondpass) ? ((secondpass == 1) ? (killed0 || pushed[0]) : (killed1 && pushed[1])) : true))
		{
			if (!isFired && !available)
			{
				start = std::chrono::system_clock::now();
				killed = false;
				for (int i = 0; i < 5; i++)
					lastpushed[i] = pushed[i];
			}
			else if ((killed) ? ((secondpass) ? false : (OrXorNot[0] && !OrXorNot[1])) : false)
			{
				if (pushed[0] && !killed0)
				{
					secondpass = 1;
					start = std::chrono::system_clock::now();
					killed = false;
				}
				else if (pushed[1] && !killed1)
				{
					secondpass = 2;
					start = std::chrono::system_clock::now();
					killed = false;
				}
			}
			isFired = true;

			end = std::chrono::system_clock::now();
			switch (method)
			{
			case 1: //Simple
				activated = true;
				break;
			case 3: //Short
				if (available)
					killed = true;
				else
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed[0]) { killed0 = true; }
						if (pushed[1]) { killed1 = true; }
					}
				if (!killed)
					PreLaunchDisable();
				break;
			case 4: //Long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start >= std::chrono::milliseconds(tape.LongPress) && !killed)
					activated = true;
				if (!killed)
					PreLaunchDisable();
				break;
			case 2: //Double
				if (available)
				{
					if (end - start < std::chrono::milliseconds(tape.LongPress))
					{
						method = 1;
						activated = true;
					}
					else
						killed = true;
				}
				else
				{
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed[0]) { killed0 = true; }
						if (pushed[1]) { killed1 = true; }
					}
					if (!killed)
						PreLaunchDisable();
				}
				break;
			case 5: //Double short
				if (available)
				{
					if (end - start < std::chrono::milliseconds(tape.LongPress))
					{
						start = std::chrono::system_clock::now();
						method = 3;
						available = false;
					}
					else
						killed = true;
				}
				else
				{
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed[0]) { killed0 = true; }
						if (pushed[1]) { killed1 = true; }
					}
					if (!killed)
						PreLaunchDisable();
				}
				break;
			case 6: //Double long
				if (available)
				{
					if (end - start < std::chrono::milliseconds(tape.LongPress))
					{
						start = std::chrono::system_clock::now();
						release = start - std::chrono::milliseconds(tape.LongPress);
						method = 4;
					}
					else
						killed = true;
				}
				else
				{
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed[0]) { killed0 = true; }
						if (pushed[1]) { killed1 = true; }
					}
					if (!killed)
						PreLaunchDisable();
				}
				break;
			case 7: //Medium long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start > std::chrono::milliseconds(tape.LongPress * 2) && !killed)
					activated = true;
				if (!killed)
					PreLaunchDisable();
				break;
			case 8: //Very long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start > std::chrono::milliseconds(tape.VeryLongPress) && !killed)
					activated = true;
				if (!killed)
					PreLaunchDisable();
				break;
			}
		}
		else
		{
			if (isFired)
				release = std::chrono::system_clock::now();

			switch (method)
			{
			case 3: //Short
				if ((isFired && !killed) || available)
				{
					available = true;
					end = std::chrono::system_clock::now();
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						if (!killed)
						{
							if (CanBeActivated())
								activated = true;
						}
						available = false;
					}
					else
						PreLaunchDisable();
				}
				break;
			case 4: //Long
				killed = true;
				break;
			case 2: //Double
			case 5: //Double short
			case 6: //Double long
				if ((isFired && !killed) || available)
				{
					end = std::chrono::system_clock::now();
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						available = false;
					else
					{
						if (CanBeActivated())
							available = true;
						PreLaunchDisable();
					}
				}
				break;
			}
			isFired = false;
			if (!legit)
			{
				killed0 = false;
				killed1 = false;
				secondpass = 0;
			}
		}
	}

	if (activated || isRunning)
	{
		if (activated)
		{
			start2 = std::chrono::system_clock::now();
			cycle = 1;
			activated = false;
			isRunning = true;
			released = false;
			for (int i = 0; i < 8; i++)
			{
				ran[i] = false;
				Toggledone[i] = false;
				MouseActiondone[i] = false;
				randStart[i] = std::chrono::milliseconds(Start[i] + ((Start[i] & 1) ? (rand() % 9) : 0));
				randStop[i] = std::chrono::milliseconds(Stop[i] + ((Stop[i] & 1) ? (rand() % 9) : 0));
			}
		}
		else if (!legit && !released)
		{
			released = true;
			release2 = std::chrono::system_clock::now();
		}

		end2 = std::chrono::system_clock::now();

		if (Led)
			Ledactive[Led] = true;

		byte value0 = (byte)((pushed[0]) ? ((Target[0]) ? m_vj[0]->GetVal() : m_ds[0]->GetVal()) : 0);
		byte value1 = (byte)((pushed[1]) ? ((Target[1]) ? m_vj[1]->GetVal() : m_ds[1]->GetVal()) : 0);
		byte value2 = (byte)((pushed[2]) ? ((Target[2]) ? m_vj[2]->GetVal() : m_ds[2]->GetVal()) : 0);

		Interrupttmp = false;
		NoSustain = false;
		Pausetmp = false;
		for (int i = 0; i < 8; i++)
		{
			started[i] = (OnRelease[i] == 1) ? ((released) ? (end2 - release2 >= randStart[i]) : false) : (end2 - start2 >= randStart[i]);
			done[i] = ran[i] ? ((OnRelease[i]) ? ((released) ? ((end2 - release2 >= randStop[i])) : false) : ((Stop[i]) ? (end2 - start2 >= randStop[i]) : released)) : false;
			if (modedest[i] == 2 && released) done[i] = true;
			if (MouseAction[i] == 1)
				if (started[i] && !done[i])
					switch (vjID[i])
					{
					case INTERRUPT: Interrupttmp = true; ran[i] = true; break;
					case NO_SUSTAIN: NoSustain = true; ran[i] = true; break;
					case PAUSE: Pausetmp = true; ran[i] = true; break;
					}
		}

		m_data = (exists[0]) ?
			((released && Macro != 2 && !NoSustain) ?
				0xFF :
				((pushed[0]) ?
					value0 :
					((OrXorNot[0] && exists[1]) ?
						((pushed[1]) ?
							value1 :
							((OrXorNot[1] && exists[2]) ?
								((pushed[2]) ?
									value2 :
									releasedVal[0]) :
								releasedVal[0])) :
						releasedVal[0]))) :
			((released && Macro != 2 && !NoSustain) ?
				0xFF :
				((exists[1]) ?
					releasedVal[1] :
					((exists[2]) ?
						releasedVal[2] :
						0)));

		TimeActiondone = -1;
		for (int i = 0; i < 8; i++)
		{
			if ((Macro == 1 || Interrupttmp) && released && OnRelease[i] != 1)
			{
				started[i] = false;
				done[i] = true;
			}
			if (modechanged == 3 && OnRelease[i])
				done[i] = true;

			if ((OrXorNot[2] && legits[3]) || (OrXorNot[3] && legits[4]))
			{
				if (Pause == 1 || Pausetmp)
					started[i] = false;
				else if ((OrXorNot[2] == 1 && legits[3]) || (OrXorNot[3] == 1 && legits[4]))
				{
					started[i] = false;
					done[i] = true;
				}
			}

			if (MouseAction[i] == 1)
			{
				if (vjID[i] == TO_LAST_MODE || vjID[i] == IF_RELEASED_GOTO || vjID[i] == IF_PUSHED_GOTO)
					if (ran[i])
						done[i] = true;
				if (started[i] && !done[i] && (!ran[i] ||
					vjID[i] == SCROLL_UP_VARIABLE || vjID[i] == SCROLL_DOWN_VARIABLE ||
					vjID[i] == VOLUME_UP || vjID[i] == VOLUME_DOWN ||
					(Stop[i] && (
					vjID[i] == MOVE_TO_XY || vjID[i] == SAVE_AND_MOVE_TO_XY ||
					vjID[i] == MOVE_TO_WH || vjID[i] == SAVE_AND_MOVE_TO_WH ||
					vjID[i] == MOVE_TO_NN || vjID[i] == SAVE_AND_MOVE_TO_NN))))
				{
					switch (vjID[i])
					{
					case ACTIVE_MOUSE:
						if (Toggle)
						{
							if (!Toggledone[i])
							{
								Toggledone[i] = true;
								mouse_toggle[i] = !mouse_toggle[i];
							}
						}
						break;
					case Mapping::SAVE_POSITION:
						GetCursorPos(&movebackpoint);
						break;
					case Mapping::MOVE_BACK:
						SetCursorPos(movebackpoint.x, movebackpoint.y);
						break;
					case SAVE_AND_MOVE_TO_XY: if (!ran[i]) GetCursorPos(&movebackpoint);
					case MOVE_TO_XY:
						if (Stop[i])
						{
							POINT actualpoint;
							GetCursorPos(&actualpoint);
							long long x = actualpoint.x;
							long long y = actualpoint.y;
							long long steps = (long long)floor(max(1, ((randStop[i] - (end2 - ((OnRelease[i] == 1) ? release2 : start2))) / std::chrono::nanoseconds(int(average * 1000000)))));
							if ((Macro == 1 || Interrupttmp) && released)
							{
								steps = 1;
								randStop[i] = std::chrono::milliseconds(0);
								ran[i] = 0;
							}
							SetCursorPos(int(x + (((long long)Grid[0] - x) / steps)), int(y + (((long long)Grid[1] - y) / steps)));
						}
						else
							SetCursorPos(Grid[0], Grid[1]);
						break;
					case SAVE_AND_MOVE_TO_WH: if (!ran[i]) GetCursorPos(&movebackpoint);
					case MOVE_TO_WH:
						if (Stop[i])
						{
							POINT actualpoint;
							GetCursorPos(&actualpoint);
							long long x = actualpoint.x;
							long long y = actualpoint.y;
							long long steps = (long long)floor(max(1, ((randStop[i] - (end2 - ((OnRelease[i] == 1) ? release2 : start2))) / std::chrono::nanoseconds(int(average * 1000000)))));
							if ((Macro == 1 || Interrupttmp) && released)
							{
								steps = 1;
								randStop[i] = std::chrono::milliseconds(0);
								ran[i] = 0;
							}
							SetCursorPos(int(x + (((long long)Grid[2] - x) / steps)), int(y + (((long long)Grid[3] - y) / steps)));
						}
						else
							SetCursorPos(Grid[2], Grid[3]);
						break;
					case SAVE_AND_MOVE_TO_NN: if (!ran[i]) GetCursorPos(&movebackpoint);
					case MOVE_TO_NN:
						if (Stop[i] && vjID[i] == SAVE_AND_MOVE_TO_NN)
						{
							POINT actualpoint;
							GetCursorPos(&actualpoint);
							long long x = actualpoint.x;
							long long y = actualpoint.y;
							long long steps = (long long)floor(max(1, ((randStop[i] - (end2 - ((OnRelease[i] == 1) ? release2 : start2))) / std::chrono::nanoseconds(int(average * 1000000)))));
							if ((Macro == 1 || Interrupttmp) && released)
							{
								steps = 1;
								randStop[i] = std::chrono::milliseconds(0);
								ran[i] = 0;
							}
							SetCursorPos(int(x + (((long long)Grid[4] - x) / steps)), int(y + (((long long)Grid[5] - y) / steps)));
						}
						else
							SetCursorPos(Grid[4], Grid[5]);
						break;
					case GRID_LEFT: gridmove.push_back(1); break;
					case GRID_UP: gridmove.push_back(2); break;
					case GRID_RIGHT: gridmove.push_back(3); break;
					case GRID_DOWN: gridmove.push_back(4); break;
					case SCROLL_UP_VARIABLE:
					case SCROLL_DOWN_VARIABLE:
					{
						short modulo = Target[0] ? (m_vj[0] ? m_vj[0]->GetScrollVal() : -1) : (m_ds[0] ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
								{
									unsigned long long delta = cycle;
									delta = delta * delta / 1600;
									std::thread(MouseActions, (MouseActionID)vjID[i], (int)min(240, delta)).detach();
								}
							}
							else
							{
								if (!(cycle % 18))
									std::thread(MouseActions, (MouseActionID)vjID[i], 600 - (modulo * 5)).detach();
							}
						break;
					}
					case VOLUME_UP:
					case VOLUME_DOWN:
					{
						short modulo = Target[0] ? (m_vj[0] ? m_vj[0]->GetScrollVal() : -1) : (m_ds[0] ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt(cycle * cycle)))))
									std::thread(MouseActions, (MouseActionID)vjID[i], 0).detach();
							}
							else
							{
								if (!(cycle % modulo))
									std::thread(MouseActions, (MouseActionID)vjID[i], 0).detach();
							}
						break;
					}
					case MEMORIZE_MODE: lastmode = mode; done[i] = true; break;
					case TO_MODE1: tomode = 1; mode = 1; done[i] = true; break;
					case TO_MODE2: tomode = 2; mode = 2; done[i] = true; break;
					case TO_MODE3: tomode = 3; mode = 3; done[i] = true; break;
					case TO_MODE4: tomode = 4; mode = 4; done[i] = true; break;
					case TO_MODE5: tomode = 5; mode = 5; done[i] = true; break;
					case TO_MODE6: tomode = 6; mode = 6; done[i] = true; break;
					case TO_MODE7: tomode = 7; mode = 7; done[i] = true; break;
					case TO_MODE8: tomode = 8; mode = 8; done[i] = true; break;
					case TO_LAST_MODE: tomode = lastmode; mode = lastmode; done[i] = true; break;
					case FORGOT_RELEASED: released = false; done[i] = true; break;
					case IF_RELEASED_GOTO: if (TimeActiondone == -1 && released) TimeActiondone = i; done[i] = true; break;
					case IF_PUSHED_GOTO: if (TimeActiondone == -1 && !released) TimeActiondone = i; done[i] = true; break;
					case RETURN_TO: if (TimeActiondone == -1) TimeActiondone = i; done[i] = true; break;
					default:
						std::thread(MouseActions, (MouseActionID)vjID[i], 0).detach();
						break;
					}
					ran[i] = true;
				}
			}
			else if (MouseAction[i] == 2)
			{
				if (started[i] && !done[i])
				{
					if (m_vj[i + 5])
					{
						if (m_vj[i + 5]->isOverWrite())
						{
							long initialval1 = m_vj[i + 5]->GetVal();
							long initialval2 = m_vj[i + 5]->GetVal2();
							if (Start[i] || Stop[i])
							{
								byte m_dataRing = (byte)((OnRelease[i] == 2) ? ((((min(randStop[i] - randStart[i], end2 - randStart[i] - start2))) * 255) / (randStop[i] - randStart[i])) :
									((((end2 - randStart[i] - ((OnRelease[i] == 1) ? release2 : start2))) * 255) / (randStop[i] - randStart[i])));
								m_vj[i + 5]->SetValByte(m_dataRing);
							}
							else
								m_vj[i + 5]->SetValByte(m_data);
							m_vj[i + 5]->SetPushed();

							if (Overcontrol[i] == 1)
							{
								int counter1 = 0;
								int counter2 = 0;
								switch (m_vj[i + 5]->GetCounterType())
								{
								case vJoyAxisID::axis_XY:
									counter1 = m_vj_X->GetCounter();
									counter2 = m_vj_Y->GetCounter();
									break;
								case vJoyAxisID::axis_ZRZ:
									counter1 = m_vj_Z->GetCounter();
									counter2 = m_vj_RZ->GetCounter();
									break;
								case vJoyAxisID::axis_RXRY:
									counter1 = m_vj_RX->GetCounter();
									counter2 = m_vj_RY->GetCounter();
									break;
								case vJoyAxisID::axis_SL0SL1:
									counter1 = m_vj_SL0->GetCounter();
									counter2 = m_vj_SL1->GetCounter();
									break;
								}
								if (counter1 > 1)
									m_vj[i + 5]->SetVal((m_vj[i + 5]->GetVal() + (initialval1 * (counter1 - 1))) / counter1);
								if (counter2 > 1)
									m_vj[i + 5]->SetVal2((m_vj[i + 5]->GetVal() + (initialval2 * (counter2 - 1))) / counter2);
							}
							else if (Overcontrol[i] == 2)
								m_vj[i + 5]->setOverwrite(false);
						}
					}
				}
				ran[i] = true;
			}
			else
			{
				if (started[i] && !done[i])
				{
					if (m_vj[i + 5])
					{
						if (Switch[i])
						{
							if (!ran[i])
								m_toggle[vjID[i]] = (Switch[i] == 1) ? true : false;
						}
						else if (Toggle)
						{
							if (!Toggledone[i])
							{
								Toggledone[i] = true;
								m_toggle[vjID[i]] = !m_toggle[vjID[i]];
							}
						}
						else
						{
							if (m_vj[i + 5]->isOverWrite())
							{
								long initialval = m_vj[i + 5]->GetVal();
								m_vj[i + 5]->SetValByte(m_data);
								m_vj[i + 5]->SetPushed();

								if (Overcontrol[i] == 1)
								{
									int counter = m_vj[i + 5]->GetCounter();
									if (counter > 1)
										m_vj[i + 5]->SetVal((m_vj[i + 5]->GetVal() + (initialval * (counter - 1))) / counter);
								}
								else if (Overcontrol[i] == 2)
									m_vj[i + 5]->setOverwrite(false);
							}
						}
					}
					ran[i] = true;
				}
				if (m_toggle[vjID[i]])
				{
					m_vj[i + 5]->SetValByte((m_data) ? m_data : ((done[i]) ? 0xFF : 0));
					m_vj[i + 5]->SetPushed();
				}
			}
		}

		for (int i = 0; i < 8; i++)
			if (MouseAction[i] == 1 && done[i] && !MouseActiondone[i])
			{
				MouseActiondone[i] = true;
				std::thread(MouseActionEnd, (MouseActionID)vjID[i]).detach();
			}

		if (done[0] && done[1] && done[2] && done[3] && done[4] && done[5] && done[6] && done[7] && TimeActiondone == -1)
		{
			method = 0;
			isRunning = false;

			if (Led)
				Ledactive[Led] = false;

			if (modechanged && Transitivity != 2 && tomode != mode)
				locked = 3;

			if (released)
			{
				for (int i = 0; i < 8; i++)
					modedest[i] = 0;
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (dsDisable[i])
					if (Target[i])
					{
						if (m_vj[i])
						{
							vjDisabled.push_back(dsID[i]);
							m_vj[i]->SetPushed(false);
						}
					}
					else
					{
						if (m_ds[i])
							dsDisabled.push_back(dsID[i]);
					}
			}
			for (int i = 0; i < 8; i++)
			{
				if ((vjDisable[i] == 2) || (vjDisable[i] == 1 && started[i] && !done[i]))
				{
					if (m_vj[i + 5])
					{
						vjDisabled.push_back(vjID[i]);
						m_vj[i + 5]->SetPushed(false);
					}
				}
			}
		}
	}

	if (((!Toggle && MouseAction[0] == 1 && started[0] && !done[0]) || (Toggle && mouse_toggle[0])) ||
		((!Toggle && MouseAction[1] == 1 && started[1] && !done[1]) || (Toggle && mouse_toggle[1])) ||
		((!Toggle && MouseAction[2] == 1 && started[2] && !done[2]) || (Toggle && mouse_toggle[2])) ||
		((!Toggle && MouseAction[3] == 1 && started[3] && !done[3]) || (Toggle && mouse_toggle[3])) ||
		((!Toggle && MouseAction[4] == 1 && started[0] && !done[4]) || (Toggle && mouse_toggle[4])) ||
		((!Toggle && MouseAction[5] == 1 && started[1] && !done[5]) || (Toggle && mouse_toggle[5])) ||
		((!Toggle && MouseAction[6] == 1 && started[2] && !done[6]) || (Toggle && mouse_toggle[6])) ||
		((!Toggle && MouseAction[7] == 1 && started[3] && !done[7]) || (Toggle && mouse_toggle[7])))
	{
		for (int i = 0; i < 3; i++)
			if (Mouse[i])
			{
				if (!Mouse[i + 3])
				{
					mouseactivated = true;
					mousemode[i] = Mouse[i];
					if (mousemode[i] == 1)
						mouseabolute = i;
				}
				else if (mousemode[i] == Mouse[i])
				{
					mousemode[i] = 0;
					if (!mousemode[((i + 1) % 3)] && !mousemode[((i + 2) % 3)])
						mouseactivated = false;
				}
			}

		if (GridCanbeUsed && ((Mouse[0] == 5 && !Mouse[3]) || (Mouse[1] == 5 && !Mouse[4]) || (Mouse[2] == 5 && !Mouse[5])))
			for (int i = 0; i < 6; i++)
				grid[i] = Grid[i];

		defaultmouse = (Mouse[6]) ? ((Mouse[6] == 1) ? true : false) : defaultmouse;
	}

	if (TimeActiondone > -1)
	{
		locked = 0;
		if (release2 > start2 + std::chrono::milliseconds(Stop[TimeActiondone]))
			released = false;
		for (int i = 0; i < 8; i++)
		{
			if (Start[i] >= Stop[TimeActiondone])
			{
				ran[i] = false;
				Toggledone[i] = false;
				MouseActiondone[i] = false;
			}
			else if (Stop[i] >= Stop[TimeActiondone])
			{

				ran[i] = true;
				Toggledone[i] = true;
				MouseActiondone[i] = false;
			}
			else
			{
				ran[i] = true;
				Toggledone[i] = true;
				MouseActiondone[i] = true;
			}
		}
		cycle = (unsigned long long)(floor((Stop[TimeActiondone] / average)) - 1);
		std::chrono::system_clock::time_point start2tmp = std::chrono::system_clock::now() - std::chrono::milliseconds(Stop[TimeActiondone]);
		release2 = start2tmp + (release2 - start2);
		start2 = start2tmp;
	}

	cycle = (cycle == 18446744073709551615) ? 0 : cycle + 1;
}

void Mapping::PreLaunchDisable()
{
	for (int i = 0; i < 5; i++)
	{
		if (dsDisable[i] == 2)
			if (Target[i])
			{
				if (m_vj[i])
				{
					vjDisabled.push_back(dsID[i]);
					m_vj[i]->SetPushed(false);
				}
			}
			else
			{
				if (m_ds[i])
					dsDisabled.push_back(dsID[i]);
			}
	}
}

BOOL Mapping::CanBeActivated()
{
	if (!OrXorNot[0] && !OrXorNot[1])
	{
		if ((lastpushed[0] && disabled[0]) ||
			(lastpushed[1] && disabled[1]) ||
			(lastpushed[2] && disabled[2]))
			return FALSE;
	}
	else if (OrXorNot[0] && !OrXorNot[1])
	{
		if (lastpushed[0] && lastpushed[1])
		{
			if ((disabled[0] && disabled[1]) || (lastpushed[2] && disabled[2]))
				return FALSE;
		}
		else
		{
			if ((lastpushed[0] && disabled[0]) ||
				(lastpushed[1] && disabled[1]) ||
				(lastpushed[2] && disabled[2]))
				return FALSE;
		}
	}
	else if (!OrXorNot[0] && OrXorNot[1])
	{
		if (lastpushed[1] && lastpushed[2])
		{
			if ((disabled[1] && disabled[2]) || (lastpushed[0] && disabled[0]))
				return FALSE;
		}
		else
		{
			if ((lastpushed[0] && disabled[0]) ||
				(lastpushed[1] && disabled[1]) ||
				(lastpushed[2] && disabled[2]))
				return FALSE;
		}
	}
	else
	{
		if (lastpushed[0])
		{
			if (lastpushed[1] && lastpushed[2])
			{
				if (disabled[0] && disabled[1] && disabled[2])
					return FALSE;
			}
			else if (lastpushed[1])
			{
				if (disabled[0] && disabled[1])
					return FALSE;
			}
			else if (lastpushed[2])
			{
				if (disabled[0] && disabled[2])
					return FALSE;
			}
			else if (disabled[0])
				return FALSE;
		}
		else if (lastpushed[1] && lastpushed[2])
		{
			if (disabled[1] && disabled[2])
				return FALSE;
		}
		else
		{
			if ((lastpushed[0] && disabled[0]) ||
				(lastpushed[1] && disabled[1]) ||
				(lastpushed[2] && disabled[2]))
				return FALSE;
		}
	}
	if ((!OrXorNot[2] && lastpushed[3] && disabled[3]) ||
		(!OrXorNot[3] && lastpushed[4] && disabled[4]))
		return FALSE;

	return TRUE;
}

WCHAR* Mapping::LedString(LedActionID id)
{
	switch (id)
	{
	case Led_Action_none: return L"";
	case Led_Action_Led1: return I18N.LedAction_Led_1;
	case Led_Action_Led2: return I18N.LedAction_Led_2;
	case Led_Action_Led3: return I18N.LedAction_Led_3;
	case Led_Action_Led4: return I18N.LedAction_Led_4;
	case Led_Action_Led5: return I18N.LedAction_Led_5;
	case Led_Action_Battery: return I18N.LedAction_BATTERY;
	default: return L"???";
	}
}

WCHAR* Mapping::MouseString(MouseActionID id)
{
	switch (id)
	{
	case mouse_none: return L"";
	case ACTIVE_MOUSE: return I18N.MouseAction_ACTIVE_MOUSE;
	case SAVE_POSITION: return I18N.MouseAction_SAVE_POSITION;
	case MOVE_BACK: return I18N.MouseAction_MOVE_BACK;
	case MOVE_TO_XY: return I18N.MouseAction_MOVE_TO_XY;
	case MOVE_TO_WH: return I18N.MouseAction_MOVE_TO_WH;
	case MOVE_TO_NN: return I18N.MouseAction_MOVE_TO_NN;
	case SAVE_AND_MOVE_TO_XY: return I18N.MouseAction_SAVE_AND_MOVE_TO_XY;
	case SAVE_AND_MOVE_TO_WH: return I18N.MouseAction_SAVE_AND_MOVE_TO_WH;
	case SAVE_AND_MOVE_TO_NN: return I18N.MouseAction_SAVE_AND_MOVE_TO_NN;
	case GRID_LEFT: return I18N.MouseAction_GRID_LEFT;
	case GRID_UP: return I18N.MouseAction_GRID_UP;
	case GRID_RIGHT: return I18N.MouseAction_GRID_RIGHT;
	case GRID_DOWN: return I18N.MouseAction_GRID_DOWN;
	case LEFT_CLICK: return I18N.MouseAction_LEFT_CLICK;
	case MIDDLE_CLICK: return I18N.MouseAction_MIDDLE_CLICK;
	case RIGHT_CLICK: return I18N.MouseAction_RIGHT_CLICK;
	case X1_CLICK: return I18N.MouseAction_X1_CLICK;
	case X2_CLICK: return I18N.MouseAction_X2_CLICK;
	case SCROLL_UP: return I18N.MouseAction_SCROLL_UP;
	case SCROLL_DOWN: return I18N.MouseAction_SCROLL_DOWN;
	case LEFT_DOUBLE_CLICK: return I18N.MouseAction_LEFT_DOUBLE_CLICK;
	case MIDDLE_DOUBLE_CLICK: return I18N.MouseAction_MIDDLE_DOUBLE_CLICK;
	case RIGHT_DOUBLE_CLICK: return I18N.MouseAction_RIGHT_DOUBLE_CLICK;
	case X1_DOUBLE_CLICK: return I18N.MouseAction_X1_DOUBLE_CLICK;
	case X2_DOUBLE_CLICK: return I18N.MouseAction_X2_DOUBLE_CLICK;
	case SCROLL_UP_x5: return I18N.MouseAction_SCROLL_UP_x5;
	case SCROLL_DOWN_x5: return I18N.MouseAction_SCROLL_DOWN_x5;
	case LEFT_DOWN: return I18N.MouseAction_LEFT_DOWN;
	case MIDDLE_DOWN: return I18N.MouseAction_MIDDLE_DOWN;
	case RIGHT_DOWN: return I18N.MouseAction_RIGHT_DOWN;
	case X1_DOWN: return I18N.MouseAction_X1_DOWN;
	case X2_DOWN: return I18N.MouseAction_X2_DOWN;
	case SCROLL_UP_VARIABLE: return I18N.MouseAction_SCROLL_UP_VARIABLE;
	case SCROLL_DOWN_VARIABLE: return I18N.MouseAction_SCROLL_DOWN_VARIABLE;
	case MUTE_SOUND: return I18N.MouseAction_MUTE_SOUND;
	case VOLUME_UP: return I18N.MouseAction_VOLUME_UP;
	case VOLUME_DOWN: return I18N.MouseAction_VOLUME_DOWN;
	case MEMORIZE_MODE: return I18N.MouseAction_MEMORIZE_MODE;
	case TO_MODE1: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(1)).c_str());
	case TO_MODE2: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(2)).c_str());
	case TO_MODE3: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(3)).c_str());
	case TO_MODE4: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(4)).c_str());
	case TO_MODE5: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(5)).c_str());
	case TO_MODE6: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(6)).c_str());
	case TO_MODE7: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(7)).c_str());
	case TO_MODE8: return (WCHAR*)((I18N.MouseAction_TO_MODE + std::to_wstring(8)).c_str());
	case TO_LAST_MODE: return I18N.MouseAction_TO_LAST_MODE;
	case FORGOT_RELEASED: return I18N.MouseAction_FORGOT_RELEASED;
	case IF_RELEASED_GOTO: return I18N.MouseAction_IF_RELEASED_GOTO;
	case IF_PUSHED_GOTO: return I18N.MouseAction_IF_PUSHED_GOTO;
	case RETURN_TO: return I18N.MouseAction_RETURN_TO;
	case INTERRUPT: return I18N.MouseAction_MOUSE_INTERRUPT;
	case NO_SUSTAIN: return I18N.MouseAction_MOUSE_NO_SUSTAIN;
	case PAUSE: return I18N.MouseAction_MOUSE_PAUSE;
	default: return L"???";
	}
}

void MouseActions(int action, int delta)
{
	switch (action)
	{
	case Mapping::LEFT_CLICK:
	{
		INPUT inputs[2] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::MIDDLE_CLICK:
	{
		INPUT inputs[2] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::RIGHT_CLICK:
	{
		INPUT inputs[2] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::X1_CLICK:
	{
		INPUT inputs[2] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[0].mi.mouseData = XBUTTON1;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[1].mi.mouseData = XBUTTON1;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::X2_CLICK:
	{
		INPUT inputs[2] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[0].mi.mouseData = XBUTTON2;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[1].mi.mouseData = XBUTTON2;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::SCROLL_UP:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = 120;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case Mapping::SCROLL_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = -120;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case Mapping::LEFT_DOUBLE_CLICK:
	{
		INPUT inputs[4] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		inputs[3].type = INPUT_MOUSE;
		inputs[3].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::MIDDLE_DOUBLE_CLICK:
	{
		INPUT inputs[4] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		inputs[3].type = INPUT_MOUSE;
		inputs[3].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::RIGHT_DOUBLE_CLICK:
	{
		INPUT inputs[4] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		inputs[3].type = INPUT_MOUSE;
		inputs[3].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::X1_DOUBLE_CLICK:
	{
		INPUT inputs[4] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[0].mi.mouseData = XBUTTON1;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[1].mi.mouseData = XBUTTON1;
		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[2].mi.mouseData = XBUTTON1;
		inputs[3].type = INPUT_MOUSE;
		inputs[3].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[3].mi.mouseData = XBUTTON1;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::X2_DOUBLE_CLICK:
	{
		INPUT inputs[4] = {};
		ZeroMemory(inputs, sizeof(inputs));
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[0].mi.mouseData = XBUTTON2;
		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[1].mi.mouseData = XBUTTON2;
		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[2].mi.mouseData = XBUTTON2;
		inputs[3].type = INPUT_MOUSE;
		inputs[3].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[3].mi.mouseData = XBUTTON2;
		SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		break;
	}
	case Mapping::SCROLL_UP_x5:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = 600;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case Mapping::SCROLL_DOWN_x5:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = -600;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case Mapping::LEFT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::MIDDLE_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::RIGHT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::X1_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XDOWN;
		input.mi.mouseData = XBUTTON1;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::X2_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XDOWN;
		input.mi.mouseData = XBUTTON2;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::SCROLL_UP_VARIABLE:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = delta;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case Mapping::SCROLL_DOWN_VARIABLE:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = -delta;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case Mapping::MUTE_SOUND:
	{
		INPUT sendkeys = { 0 };
		ZeroMemory(&sendkeys, sizeof(sendkeys));
		sendkeys.type = INPUT_KEYBOARD;
		sendkeys.ki.wVk = VK_VOLUME_MUTE;
		sendkeys.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		sendkeys.ki.time = 0;
		sendkeys.ki.dwExtraInfo = 0;
		SendInput(1, &sendkeys, sizeof(INPUT));
		sendkeys.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
		SendInput(1, &sendkeys, sizeof(INPUT));
		break;
	}
	case Mapping::VOLUME_UP:
	{
		INPUT sendkeys = { 0 };
		ZeroMemory(&sendkeys, sizeof(sendkeys));
		sendkeys.type = INPUT_KEYBOARD;
		sendkeys.ki.wVk = VK_VOLUME_UP;
		sendkeys.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		sendkeys.ki.time = 0;
		sendkeys.ki.dwExtraInfo = 0;
		SendInput(1, &sendkeys, sizeof(INPUT));
		sendkeys.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
		SendInput(1, &sendkeys, sizeof(INPUT));
		break;
	}
	case Mapping::VOLUME_DOWN:
	{
		INPUT sendkeys = { 0 };
		ZeroMemory(&sendkeys, sizeof(sendkeys));
		sendkeys.type = INPUT_KEYBOARD;
		sendkeys.ki.wVk = VK_VOLUME_DOWN;
		sendkeys.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		sendkeys.ki.time = 0;
		sendkeys.ki.dwExtraInfo = 0;
		SendInput(1, &sendkeys, sizeof(INPUT));
		sendkeys.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
		SendInput(1, &sendkeys, sizeof(INPUT));
		break;
	}
	}
}

void MouseActionEnd(int action)
{
	switch (action)
	{
	case Mapping::LEFT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::MIDDLE_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::RIGHT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::X1_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XUP;
		input.mi.mouseData = XBUTTON1;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case Mapping::X2_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XUP;
		input.mi.mouseData = XBUTTON2;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	}
}
