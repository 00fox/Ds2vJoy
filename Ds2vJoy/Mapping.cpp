#include "stdafx.h"
#include "Mapping.h"

Mapping::Mapping()
{
}

Mapping::~Mapping()
{
}

WCHAR* Mapping::dsString(unsigned char nbutton)
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Enable == 2)
		return buf;

	std::wstring str = L"";
	if (Target[nbutton])
	{
		if (dsID[nbutton] != vJoyButton::none)
			str = vJoyButton::String((vJoyButtonID)dsID[nbutton]);
	}
	else
	{
		if (dsID[nbutton] != dsButton::none)
			str = dsButton::String((dsButtonID)dsID[nbutton]);
	}

	if (nbutton)
	{
		if (nbutton < 3 && OrXorNot[nbutton - 1] == 1)
			head += swprintf_s(head, MAX_PATH, L"|| ");
		else if (nbutton < 3 && OrXorNot[nbutton - 1] == 2)
			head += swprintf_s(head, MAX_PATH, L"⊕");
		else if (nbutton > 2 && OrXorNot[nbutton - 1] == 1)
			head += swprintf_s(head, MAX_PATH, L"‒ ");
		else if (nbutton > 2 && OrXorNot[nbutton - 1])
			head += swprintf_s(head, MAX_PATH, L"=");
		else if (str.size())
			head += swprintf_s(head, MAX_PATH, L"+");
	}

	head += swprintf_s(head, MAX_PATH, L"%s", str.c_str());

	if (dsDisable[nbutton])
	{
		if (dsDisable[nbutton] == 2)
			head += swprintf_s(head, MAX_PATH, L"✱");
		else
			head += swprintf_s(head, MAX_PATH, L"#");
	}

	return buf;
}

const WCHAR* Mapping::vJoyString()
{
	bool firstplus = false;
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Enable == 2)
		return buf;

	for (int i = 0; i < 8; i++)
	{
		if (firstplus)
		{
			if (ActionType[i] == 1)
				head += swprintf_s(head, MAX_PATH, L" %s", MouseString((MouseActionID)vjID[i]));
			else if (ActionType[i] == 2)
				head += swprintf_s(head, MAX_PATH, L" %s", SpecialString((SpecialActionID)vjID[i]));
			else if (ActionType[i] == 3)
				head += swprintf_s(head, MAX_PATH, L" %s", vJoyButton::StringAxis((vJoyAxisMoveID)vjID[i]));
			else if (ActionType[i] == 4)
				head += swprintf_s(head, MAX_PATH, L" %s", ModulesString((ModulesActionID)vjID[i]));
			else if(vjID[i] != vJoyButton::none)
				head += swprintf_s(head, MAX_PATH, L" %s", vJoyButton::String((vJoyButtonID)vjID[i]));
		}
		else
		{
			if (ActionType[i] == 1)
				{ head += swprintf_s(head, MAX_PATH, L"%s", MouseString((MouseActionID)vjID[i])); firstplus = true; }
			else if (ActionType[i] == 2)
				{ head += swprintf_s(head, MAX_PATH, L"%s", SpecialString((SpecialActionID)vjID[i])); firstplus = true; }
			else if (ActionType[i] == 3)
				{ head += swprintf_s(head, MAX_PATH, L"%s", vJoyButton::StringAxis((vJoyAxisMoveID)vjID[i])); firstplus = true; }
			else if (ActionType[i] == 4)
				{ head += swprintf_s(head, MAX_PATH, L"%s", ModulesString((ModulesActionID)vjID[i])); firstplus = true; }
			else if (vjID[i] != vJoyButton::none)
				{ head += swprintf_s(head, MAX_PATH, L"%s", vJoyButton::String((vJoyButtonID)vjID[i])); firstplus = true; }
		}

		if (vjDisable[i] == 1)
			head += swprintf_s(head, MAX_PATH, L"#");
		else if (vjDisable[i])
			head += swprintf_s(head, MAX_PATH, L">");

		if (Switch[i] == 1)
			head += swprintf_s(head, MAX_PATH, L"✓");
		else if (Switch[i])
			head += swprintf_s(head, MAX_PATH, L"✕");
	}

	if (Led)
		if (firstplus)
		{
			if (Led == 6)
				head += swprintf_s(head, MAX_PATH, L" Battery status");
			else
				head += swprintf_s(head, MAX_PATH, L" Led%d", Led);
		}
		else
		{
			if (Led == 6)
				head += swprintf_s(head, MAX_PATH, L"Battery status");
			else
				head += swprintf_s(head, MAX_PATH, L"Led%d", Led);
			firstplus = true;
		}

	return buf;
}

const WCHAR* Mapping::NoticeString()
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Enable == 2)
		return buf;

	wcscpy_s(head, wcslen(Notice) + 1, Notice);

	return buf;
}

const WCHAR* Mapping::TagsString()
{
	bool firstplus = false;
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Enable == 2)
		return buf;

	if (Ifmouse == 1)
		head += swprintf_s(head, MAX_PATH, L"I");
	else if (Ifmouse)
		head += swprintf_s(head, MAX_PATH, L"i");
	else
		head += swprintf_s(head, MAX_PATH, L" ");

	if (Force == 1)
		head += swprintf_s(head, MAX_PATH, L"F");
	else if (Force)
		head += swprintf_s(head, MAX_PATH, L"f");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Short)
		head += swprintf_s(head, MAX_PATH, L"S");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Double)
		head += swprintf_s(head, MAX_PATH, L"D");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Long)
		head += swprintf_s(head, MAX_PATH, L"L");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Macro == 1)
		head += swprintf_s(head, MAX_PATH, L"C");
	else if (Macro)
		head += swprintf_s(head, MAX_PATH, L"c");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Pause == 1)
		head += swprintf_s(head, MAX_PATH, L"1");
	else if (Pause == 2)
		head += swprintf_s(head, MAX_PATH, L"2");
	else if (Pause)
		head += swprintf_s(head, MAX_PATH, L"B");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Transitivity == 1)
		head += swprintf_s(head, MAX_PATH, L"►");
	else if (Transitivity == 2)
		head += swprintf_s(head, MAX_PATH, L"Y");
	else if (Transitivity == 3)
		head += swprintf_s(head, MAX_PATH, L"y");
	else if (Transitivity == 4)
		head += swprintf_s(head, MAX_PATH, L"R");
	else if (Transitivity)
		head += swprintf_s(head, MAX_PATH, L"r");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (Toggle == 1)
		head += swprintf_s(head, MAX_PATH, L"T");
	else if (Toggle)
		head += swprintf_s(head, MAX_PATH, L"t");
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	if (NoRelease[0] || NoRelease[1] || NoRelease[2] || NoRelease[3] || NoRelease[4] || NoRelease[5] || NoRelease[6] || NoRelease[7])
	{
		if (OnRelease[0] == 1 || OnRelease[1] == 1 || OnRelease[2] == 1 || OnRelease[3] == 1 || OnRelease[4] == 1 || OnRelease[5] == 1 || OnRelease[6] == 1 || OnRelease[7] == 1)
		{
			if (NlRelease[0] || NlRelease[1] || NlRelease[2] || NlRelease[3] || NlRelease[4] || NlRelease[5] || NlRelease[6] || NlRelease[7])
				head += swprintf_s(head, MAX_PATH, L"W");
			else
				head += swprintf_s(head, MAX_PATH, L"Z");
		}
		else if (OnRelease[0] || OnRelease[1] || OnRelease[2] || OnRelease[3] || OnRelease[4] || OnRelease[5] || OnRelease[6] || OnRelease[7])
		{
			if (NlRelease[0] || NlRelease[1] || NlRelease[2] || NlRelease[3] || NlRelease[4] || NlRelease[5] || NlRelease[6] || NlRelease[7])
				head += swprintf_s(head, MAX_PATH, L"w");
			else
				head += swprintf_s(head, MAX_PATH, L"z");
		}
		else
			head += swprintf_s(head, MAX_PATH, L"  ");
	}
	else
	{
		if (OnRelease[0] == 1 || OnRelease[1] == 1 || OnRelease[2] == 1 || OnRelease[3] == 1 || OnRelease[4] == 1 || OnRelease[5] == 1 || OnRelease[6] == 1 || OnRelease[7] == 1)
			head += swprintf_s(head, MAX_PATH, L"R");
		else if (OnRelease[0] || OnRelease[1] || OnRelease[2] || OnRelease[3] || OnRelease[4] || OnRelease[5] || OnRelease[6] || OnRelease[7])
			head += swprintf_s(head, MAX_PATH, L"r");
		else
			head += swprintf_s(head, MAX_PATH, L"  ");
	}

	if (Mouse[0] || Mouse[1] || Mouse[2] || Mouse[6])
	{
		if (!Mouse[3] && !Mouse[4] && !Mouse[5])
			head += swprintf_s(head, MAX_PATH, L"M");
		else
			head += swprintf_s(head, MAX_PATH, L"m");

	}
	else
		head += swprintf_s(head, MAX_PATH, L"  ");

	return buf;
}

const WCHAR* Mapping::MappingButtons()
{
	return MappingButtonsString;
}

void Mapping::PreLoad()
{
	vjUsed.clear();
	MappingButtonsString[0] = 0;
	for (int i = 0; i < vJoyButtonID::button_Count; i++)
		m_toggle[i] = false;
	for (int i = 0; i < 8; i++)
		mouse_toggle[i] = false;
	for (int i = 0; i < Led_Action_Count; i++)
		Ledactive[i] = false;
}

BOOL Mapping::LoadDevice(HWND hWnd, dsDevice* ds, vJoyDevice* vjoy)
{
	m_hWnd = hWnd;
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
	memmode = 1;
	basemode = 1;
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
	m_vj[5] = (vjID[0] && !ActionType[0]) ? vjoy->GetButton((vJoyButtonID)vjID[0]) : ((vjID[0] && ActionType[0] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[0]) : 0);
	m_vj[6] = (vjID[1] && !ActionType[1]) ? vjoy->GetButton((vJoyButtonID)vjID[1]) : ((vjID[1] && ActionType[1] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[1]) : 0);
	m_vj[7] = (vjID[2] && !ActionType[2]) ? vjoy->GetButton((vJoyButtonID)vjID[2]) : ((vjID[2] && ActionType[2] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[2]) : 0);
	m_vj[8] = (vjID[3] && !ActionType[3]) ? vjoy->GetButton((vJoyButtonID)vjID[3]) : ((vjID[3] && ActionType[3] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[3]) : 0);
	m_vj[9] = (vjID[4] && !ActionType[4]) ? vjoy->GetButton((vJoyButtonID)vjID[4]) : ((vjID[4] && ActionType[4] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[4]) : 0);
	m_vj[10] = (vjID[5] && !ActionType[5]) ? vjoy->GetButton((vJoyButtonID)vjID[5]) : ((vjID[5] && ActionType[5] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[5]) : 0);
	m_vj[11] = (vjID[6] && !ActionType[6]) ? vjoy->GetButton((vJoyButtonID)vjID[6]) : ((vjID[6] && ActionType[6] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[6]) : 0);
	m_vj[12] = (vjID[7] && !ActionType[7]) ? vjoy->GetButton((vJoyButtonID)vjID[7]) : ((vjID[7] && ActionType[7] == 3) ? vjoy->GetAxis((vJoyAxisMoveID)vjID[7]) : 0);


	for (int i = 0; i < 8; i++)
	{
		if (m_vj[i + 5] && Overcontrol[i] == 1)
		{
			if (ActionType[i] == 0)
				switch (vjID[i])
				{
				case vJoyButtonID::X:
				case vJoyButtonID::XTR:
				case vJoyButtonID::XINV: { ds->GetButton(dsButtonID::LX)->SetThreshold(false); break; }
				case vJoyButtonID::Y:
				case vJoyButtonID::YTR:
				case vJoyButtonID::YINV: { ds->GetButton(dsButtonID::LY)->SetThreshold(false); break; }
				case vJoyButtonID::Z:
				case vJoyButtonID::ZTR:
				case vJoyButtonID::ZINV: { ds->GetButton(dsButtonID::RX)->SetThreshold(false); break; }
				case vJoyButtonID::RZ:
				case vJoyButtonID::RZTR:
				case vJoyButtonID::RZINV: { ds->GetButton(dsButtonID::RY)->SetThreshold(false); break; }
				}
			else if (ActionType[i] == 3)
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

		if (!ActionType[i])
		{
			if (!(std::find(vjUsed.begin(), vjUsed.end(), vjID[i]) != vjUsed.end()))
				if (vjID[i])
				{
					vjUsed.push_back(vjID[i]);
					switch (vjID[i])
					{
					case vJoyButton::ButtonID::Button1: { tape.vJoyUsed[0] = true; break; }
					case vJoyButton::ButtonID::Button2: { tape.vJoyUsed[1] = true; break; }
					case vJoyButton::ButtonID::Button3: { tape.vJoyUsed[2] = true; break; }
					case vJoyButton::ButtonID::Button4: { tape.vJoyUsed[3] = true; break; }
					case vJoyButton::ButtonID::Button5: { tape.vJoyUsed[4] = true; break; }
					case vJoyButton::ButtonID::Button6: { tape.vJoyUsed[5] = true; break; }
					case vJoyButton::ButtonID::Button7: { tape.vJoyUsed[6] = true; break; }
					case vJoyButton::ButtonID::Button8: { tape.vJoyUsed[7] = true; break; }
					case vJoyButton::ButtonID::Button9: { tape.vJoyUsed[8] = true; break; }
					case vJoyButton::ButtonID::Button10: { tape.vJoyUsed[9] = true; break; }
					case vJoyButton::ButtonID::Button11: { tape.vJoyUsed[10] = true; break; }
					case vJoyButton::ButtonID::Button12: { tape.vJoyUsed[11] = true; break; }
					case vJoyButton::ButtonID::Button13: { tape.vJoyUsed[12] = true; break; }
					case vJoyButton::ButtonID::Button14: { tape.vJoyUsed[13] = true; break; }
					case vJoyButton::ButtonID::Button15: { tape.vJoyUsed[14] = true; break; }
					case vJoyButton::ButtonID::Button16: { tape.vJoyUsed[15] = true; break; }
					case vJoyButton::ButtonID::Button17: { tape.vJoyUsed[16] = true; break; }
					case vJoyButton::ButtonID::Button18: { tape.vJoyUsed[17] = true; break; }
					case vJoyButton::ButtonID::Button19: { tape.vJoyUsed[18] = true; break; }
					case vJoyButton::ButtonID::Button20: { tape.vJoyUsed[19] = true; break; }
					case vJoyButton::ButtonID::Button21: { tape.vJoyUsed[20] = true; break; }
					case vJoyButton::ButtonID::Button22: { tape.vJoyUsed[21] = true; break; }
					case vJoyButton::ButtonID::Button23: { tape.vJoyUsed[22] = true; break; }
					case vJoyButton::ButtonID::Button24: { tape.vJoyUsed[23] = true; break; }
					case vJoyButton::ButtonID::Button25: { tape.vJoyUsed[24] = true; break; }
					case vJoyButton::ButtonID::Button26: { tape.vJoyUsed[25] = true; break; }
					case vJoyButton::ButtonID::Button27: { tape.vJoyUsed[26] = true; break; }
					case vJoyButton::ButtonID::Button28: { tape.vJoyUsed[27] = true; break; }
					case vJoyButton::ButtonID::Button29: { tape.vJoyUsed[28] = true; break; }
					case vJoyButton::ButtonID::Button30: { tape.vJoyUsed[29] = true; break; }
					case vJoyButton::ButtonID::Button31: { tape.vJoyUsed[30] = true; break; }
					case vJoyButton::ButtonID::Button32: { tape.vJoyUsed[31] = true; break; }
					}
				}
		}
	}

	if (Toggle == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (ActionType[i] == 1)
			{
				if ((MouseActionID)vjID[i] == ACTIVE_MOUSE)
					mouse_toggle[i] = true;
				else
					continue;
			}
			else if (!ActionType[i] && !Switch[i])
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
	MappingButtonsString[0] = '\0';
	WCHAR* head = MappingButtonsString;
	head += swprintf_s(head, MAX_PATH, L"%s", L"vJoy:");

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
			head += swprintf_s(head, MAX_PATH, L" %s", vJoyButton::String((vJoyButtonID)vjUsed[i]));
	}

	if (tape.ActualDS == 2 && tape.PreferredDS)
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
	if (tape.MappingPaused)
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
			if (Transitivity == 5)
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
		if (isRunning || (!isRunning && Transitivity == 1))
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
		if (OnRelease[i] && locked == 1 && tape.Mode[Tab] == mode && Transitivity == 1)
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
	bool lasttest = (legit && Transitivity == 2 && modechanged);
	if ((tape.Mode[Tab] == mode && !legit) || lasttest)
	{
		locked = 0;
		tomode = -1;
		if (lasttest)
			modechanged = 1;
		else
			modechanged = 0;
	}
	else if (!lasttest)
		if (tape.Mode[Tab] && tape.Mode[Tab] != mode)
		{
			if (Transitivity == 1)
			{
				locked = 0;
				tomode = -1;
				modechanged = 0;
				legit = false;
				for (int i = 0; i < 8; i++)
					modedest[i] = 0;
			}
			else if (!(isRunning && Transitivity == 3))
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
			case 1: { activated = true; break; } //Simple
			case 3: //Short
			{
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
			}
			case 4: //Long
			{
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start >= std::chrono::milliseconds(tape.LongPress) && !killed)
					activated = true;
				if (!killed)
					PreLaunchDisable();
				break;
			}
			case 2: //Double
			{
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
			}
			case 5: //Double short
			{
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
			}
			case 6: //Double long
			{
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
			}
			case 7: //Medium long
			{
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start > std::chrono::milliseconds(tape.LongPress * 2) && !killed)
					activated = true;
				if (!killed)
					PreLaunchDisable();
				break;
			}
			case 8: //Very long
			{
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start > std::chrono::milliseconds(tape.VeryLongPress) && !killed)
					activated = true;
				if (!killed)
					PreLaunchDisable();
				break;
			}
			}
		}
		else
		{
			if (isFired)
				release = std::chrono::system_clock::now();

			switch (method)
			{
			case 3: //Short
			{
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
			}
			case 4: { killed = true; break; } //Long
			case 2: //Double
			case 5: //Double short
			case 6: //Double long
			{
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
			MagFactor = Grid[4];
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
			if (ActionType[i] == 2)
				if (started[i] && !done[i])
					switch (vjID[i])
					{
					case INTERRUPT: { Interrupttmp = true; ran[i] = true; break; }
					case NO_SUSTAIN: { NoSustain = true; ran[i] = true; break; }
					case PAUSE: { Pausetmp = true; ran[i] = true; break; }
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

			if (OrXorNot[2] && legits[3])
			{
				if (Pause == 1 || Pause == 3 || Pausetmp)
					started[i] = false;
				else if (OrXorNot[2] == 1 && legits[3])
				{
					started[i] = false;
					done[i] = true;
				}
			}

			if (OrXorNot[3] && legits[4])
			{
				if (Pause >= 2 || Pausetmp)
					started[i] = false;
				else if (OrXorNot[3] == 1 && legits[4])
				{
					started[i] = false;
					done[i] = true;
				}
			}

			if (ActionType[i] == 1)
			{
				if (started[i] && !done[i] && (!ran[i] ||
					vjID[i] == SCROLL_UP_VARIABLE || vjID[i] == SCROLL_DOWN_VARIABLE ||
					vjID[i] == MAGNIFY_PLUS || vjID[i] == MAGNIFY_MINUS ||
					vjID[i] == MAGNIFY_UP || vjID[i] == MAGNIFY_DOWN ||
					vjID[i] == MAGNIFY_LEFT || vjID[i] == MAGNIFY_RIGHT ||
					(Stop[i] && (
						vjID[i] == MOVE_TO_XY || vjID[i] == SAVE_AND_MOVE_TO_XY ||
						vjID[i] == MOVE_TO_WH || vjID[i] == SAVE_AND_MOVE_TO_WH ||
						vjID[i] == MOVE_TO_NN || vjID[i] == SAVE_AND_MOVE_TO_NN))))
				{
					switch (vjID[i])
					{
					case ACTIVE_MOUSE:
					{
						if (Toggle)
						{
							if (!Toggledone[i])
							{
								Toggledone[i] = true;
								mouse_toggle[i] = !mouse_toggle[i];
							}
						}
						break;
					}
					case Mapping::SAVE_POSITION: { GetCursorPos(&movebackpoint); break; }
					case Mapping::MOVE_BACK: { SetCursorPos(movebackpoint.x, movebackpoint.y); break; }
					case SAVE_AND_MOVE_TO_XY:
					{
						if (!ran[i])
							GetCursorPos(&movebackpoint);
						[[fallthrough]];
					}
					case MOVE_TO_XY:
					{
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
					}
					case SAVE_AND_MOVE_TO_WH:
					{
						if (!ran[i])
							GetCursorPos(&movebackpoint);
						[[fallthrough]];
					}
					case MOVE_TO_WH:
					{
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
					}
					case SAVE_AND_MOVE_TO_NN:
					{
						if (!ran[i])
							GetCursorPos(&movebackpoint);
						[[fallthrough]];
					}
					case MOVE_TO_NN:
					{
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
					}
					case GRID_LEFT: { gridmove.push_back(1); break; }
					case GRID_UP: { gridmove.push_back(2); break; }
					case GRID_RIGHT: { gridmove.push_back(3); break; }
					case GRID_DOWN: { gridmove.push_back(4); break; }
					case SCROLL_UP_VARIABLE:
					case SCROLL_DOWN_VARIABLE:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
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
					case MAGNIFY:
					{
						float Level = 0;
						int xOffset = 0;
						int	yOffset = 0;
						unsigned char Method = ((Grid[0]) ? 1 : 0) + ((Grid[1]) ? 2 : 0);
						if (Method == 3)
						{
							xOffset = Grid[2];
							yOffset = Grid[3];
						}
						if (MagFactor > 0)
						{
							//Level = min(4096, Grid[4] + ((Grid[5]) ? (float(Grid[5]) / float(pow(10, floor(log10(Grid[5])) + 1))) : 0));
							PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_SET, 0), MAKELPARAM(Grid[4], Grid[5]));
							MagFactor = 0;
						}
						PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(Method, 0), MAKELPARAM(xOffset, yOffset));
						break;
					}
					case MAGNIFY_PLUS:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(1, 0)); break; }
							}
							else
							{
								if (!(cycle % modulo))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(1, 0)); break; }
							}
						break;
					}
					case MAGNIFY_MINUS:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(0, 1)); break; }
							}
							else
							{
								if (!(cycle % modulo))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(0, 1)); break; }
							}
						break;
					}
					case MAGNIFY_RESET: { PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_RESET, 0), MAKELPARAM(0, 0)); break; }
					case MAGNIFY_UP:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 3), MAKELPARAM(0, 10)); break; }
							}
							else
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 3), MAKELPARAM(0, unsigned short(100 / modulo))); break; }
							}
						break;
					}
					case MAGNIFY_DOWN:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM(0, 10)); break; }
							}
							else
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM(0, (100 / modulo))); break; }
							}
						break;
					}
					case MAGNIFY_LEFT:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 1), MAKELPARAM(10, 0)); break; }
							}
							else
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 1), MAKELPARAM(unsigned short(100 / modulo), 0)); break; }
							}
						break;
					}
					case MAGNIFY_RIGHT:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM(10, 0)); break; }
							}
							else
							{
								if (!(cycle % 5))
									{ PostMessage(m_hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM((100 / modulo), 0)); break; }
							}
						break;
					}
					default: { std::thread(MouseActions, (MouseActionID)vjID[i], 0).detach(); break; }
					}
					ran[i] = true;
				}
			}
			else if (ActionType[i] == 2)
			{
				if (vjID[i] == TO_LAST_MODE || vjID[i] == IF_RELEASED_GOTO || vjID[i] == IF_PUSHED_GOTO)
					if (ran[i])
						done[i] = true;
				if (started[i] && !done[i] && (!ran[i] || vjID[i] == VOLUME_UP || vjID[i] == VOLUME_DOWN))
				{
					switch (vjID[i])
					{
					case VOLUME_UP:
					case VOLUME_DOWN:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt(cycle * cycle)))))
									std::thread(SpecialActions, (MouseActionID)vjID[i]).detach();
							}
							else
							{
								if (!(cycle % modulo))
									std::thread(SpecialActions, (MouseActionID)vjID[i]).detach();
							}
						break;
					}
					case MEMORIZE_MODE: { memmode = mode; done[i] = true; break; }
					case TO_MEM_MODE: { lastmode = mode; tomode = memmode; mode = memmode; done[i] = true; break; }
					case TO_MODE1: { lastmode = mode; tomode = 1; mode = 1; done[i] = true; break; }
					case TO_MODE2: { lastmode = mode; tomode = 2; mode = 2; done[i] = true; break; }
					case TO_MODE3: { lastmode = mode; tomode = 3; mode = 3; done[i] = true; break; }
					case TO_MODE4: { lastmode = mode; tomode = 4; mode = 4; done[i] = true; break; }
					case TO_MODE5: { lastmode = mode; tomode = 5; mode = 5; done[i] = true; break; }
					case TO_MODE6: { lastmode = mode; tomode = 6; mode = 6; done[i] = true; break; }
					case TO_MODE7: { lastmode = mode; tomode = 7; mode = 7; done[i] = true; break; }
					case TO_MODE8: { lastmode = mode; tomode = 8; mode = 8; done[i] = true; break; }
					case TO_LAST_MODE: { unsigned char lastmodetmp = lastmode; lastmode = mode; tomode = lastmodetmp; mode = lastmodetmp; done[i] = true; break; }
					case FORGOT_RELEASED: { released = false; done[i] = true; break; }
					case BASE_TO_MODE1: { basemode = 1; done[i] = true; break; }
					case BASE_TO_MODE2: { basemode = 2; done[i] = true; break; }
					case BASE_TO_MODE3: { basemode = 3; done[i] = true; break; }
					case BASE_TO_MODE4: { basemode = 4; done[i] = true; break; }
					case BASE_TO_MODE5: { basemode = 5; done[i] = true; break; }
					case BASE_TO_MODE6: { basemode = 6; done[i] = true; break; }
					case BASE_TO_MODE7: { basemode = 7; done[i] = true; break; }
					case BASE_TO_MODE8: { basemode = 8; done[i] = true; break; }
					case TO_BASE_MODE: { lastmode = mode; tomode = basemode; mode = basemode; done[i] = true; break; }
					case IF_RELEASED_GOTO: { if (TimeActiondone == -1 && released) TimeActiondone = i; done[i] = true; break; }
					case IF_PUSHED_GOTO: { if (TimeActiondone == -1 && !released) TimeActiondone = i; done[i] = true; break; }
					case RETURN_TO: { if (TimeActiondone == -1) TimeActiondone = i; done[i] = true; break; }
					case RESET_STATS: { for (int i = 0; i < 8; i++) tape.Stat[i] = 0; break; }
					case ADDSTAT1: { tape.Stat[0] += 1; break; }
					case ADDSTAT2: { tape.Stat[1] += 1; break; }
					case ADDSTAT3: { tape.Stat[2] += 1; break; }
					case ADDSTAT4: { tape.Stat[3] += 1; break; }
					case ADDSTAT5: { tape.Stat[4] += 1; break; }
					case ADDSTAT6: { tape.Stat[5] += 1; break; }
					case ADDSTAT7: { tape.Stat[6] += 1; break; }
					case ADDSTAT8: { tape.Stat[7] += 1; break; }
					case SCREENSHOT: { PostMessage(m_hWnd, WM_SCREENSHOT, MAKEWPARAM(Grid[0], Grid[1]), MAKELPARAM(Grid[2], Grid[3])); break; }
					case MINIMIZE: { PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); break; }
					case RESTORE: { PostMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0); break; }
					case TRANSPARENCY: { PostMessage(m_hWnd, WM_TRANSPARENCY, 0, 1); break; }
					default: { std::thread(SpecialActions, (SpecialActionID)vjID[i]).detach(); break; }
					}
					ran[i] = true;
				}
			}
			else if (ActionType[i] == 3)
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
								case vJoyAxisID::axis_XY: { counter1 = m_vj_X->GetCounter(); counter2 = m_vj_Y->GetCounter(); break; }
								case vJoyAxisID::axis_ZRZ: { counter1 = m_vj_Z->GetCounter(); counter2 = m_vj_RZ->GetCounter(); break; }
								case vJoyAxisID::axis_RXRY: { counter1 = m_vj_RX->GetCounter(); counter2 = m_vj_RY->GetCounter(); break; }
								case vJoyAxisID::axis_SL0SL1: { counter1 = m_vj_SL0->GetCounter(); counter2 = m_vj_SL1->GetCounter(); break; }
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
			else if (ActionType[i] == 4)
			{
				if (started[i] && !done[i] && (!ran[i] || vjID[i] == WEB_ZOOMMINUS || vjID[i] == WEB_ZOOMPLUS ||
						vjID[i] == WEB_DOWN || vjID[i] == WEB_UP || vjID[i] == WEB_LEFT || vjID[i] == WEB_RIGHT))
				{
					switch (vjID[i])
					{
					case NOTEPAD: { PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); break; }
					case NOTEPAD_DOWN: { PostMessage(m_hWnd, WM_NOTEPAD_SCROLL, 0, 0); break; }
					case NOTEPAD_UP: { PostMessage(m_hWnd, WM_NOTEPAD_SCROLL, 0, 1); break; }
					}

					if (tape.isExplorerLoaded)
					switch (vjID[i])
					{
					case WEB_DOWN:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % 18))
						{
							if (modulo == -1)
								PostMessage(m_hWnd, WM_WEB_SCROLL, 0, 90);
							else
								PostMessage(m_hWnd, WM_WEB_SCROLL, 0, (540 / modulo));
						}
						break;
					}
					case WEB_UP:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % 18))
						{
							if (modulo == -1)
								PostMessage(m_hWnd, WM_WEB_SCROLL, 0, -90);
							else
								PostMessage(m_hWnd, WM_WEB_SCROLL, 0, (-540 / modulo));
						}
						break;
					}
					case WEB_LEFT:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % 18))
						{
							if (modulo == -1)
								PostMessage(m_hWnd, WM_WEB_SCROLL, -90, 0);
							else
								PostMessage(m_hWnd, WM_WEB_SCROLL, (-540 / modulo), 0);
						}
						break;
					}
					case WEB_RIGHT:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % 18))
						{
							if (modulo == -1)
								PostMessage(m_hWnd, WM_WEB_SCROLL, 90, 0);
							else
								PostMessage(m_hWnd, WM_WEB_SCROLL, (540 / modulo), 0);
						}
						break;
					}
					case WEB_PREVIOUSTAB: { PostMessage(m_hWnd, WM_WEB_CHANGETAB, 0, 0); break; }
					case WEB_NEXTTAB: { PostMessage(m_hWnd, WM_WEB_CHANGETAB, 0, 1); break; }
					case WEB_CLOSETAB: { PostMessage(m_hWnd, WM_COMMAND, ID_WEBCLOSE, -1); break; }
					case WEB_FULLSCREEN: { PostMessage(m_hWnd, WM_WEB_FULLSCREEN, 0, 0); break; }
					case WEB_FAVORITE1: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 1); break; }
					case WEB_FAVORITE2: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 2); break; }
					case WEB_FAVORITE3: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 3); break; }
					case WEB_FAVORITE4: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 4); break; }
					case WEB_FAVORITE5: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 5); break; }
					case WEB_FAVORITE6: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 6); break; }
					case WEB_FAVORITE7: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 7); break; }
					case WEB_FAVORITE8: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 8); break; }
					case WEB_FAVORITE9: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 9); break; }
					case WEB_HOME: { PostMessage(m_hWnd, WM_WEB_FAVORITE, 0, 0); break; }
					case WEB_BACK: { PostMessage(m_hWnd, WM_WEB_BACK, 0, 0); break; }
					case WEB_NEXT: { PostMessage(m_hWnd, WM_WEB_NEXT, 0, 0); break; }
					case WEB_REFRESH: { PostMessage(m_hWnd, WM_WEB_REFRESH, 0, 0); break; }
					case WEB_CANCEL: { PostMessage(m_hWnd, WM_WEB_CANCEL, 0, 0); break; }
					case WEB_AUTOREFRESH: { PostMessage(m_hWnd, WM_WEB_AUTOREFRESH, 0, 0); break; }
					case WEB_ZOOMMINUS:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt(cycle * cycle)))))
									PostMessage(m_hWnd, WM_WEB_ZOOM, 0, 0);
							}
							else
							{
								if (!(cycle % (modulo)))
									PostMessage(m_hWnd, WM_WEB_ZOOM, 0, 0);
							}
						break;
					}
					case WEB_ZOOMPLUS:
					{
						short modulo = (Target[0]) ? ((m_vj[0]) ? m_vj[0]->GetScrollVal() : -1) : ((m_ds[0]) ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt(cycle * cycle)))))
									PostMessage(m_hWnd, WM_WEB_ZOOM, 0, 1);
							}
							else
							{
								if (!(cycle % (modulo)))
									PostMessage(m_hWnd, WM_WEB_ZOOM, 0, 1);
							}
						break;
					}
					case WEB_ZOOMRESET: { PostMessage(m_hWnd, WM_WEB_ZOOMRESET, 0, 0); break; }
					case WEB_ZOOMSET: { PostMessage(m_hWnd, WM_WEB_ZOOMSET, 0, 0); break; }
					case WEB_VISIBILITY: { PostMessage(m_hWnd, WM_WEB_VISIBILITY, 0, 0); break; }
					case WEB_SCREENSHOT: { PostMessage(m_hWnd, WM_WEB_SCREENSHOT, 0, 0); break; }
					case WEB_DARKMODE: { PostMessage(m_hWnd, WM_WEB_DARKMODE, 0, 1); break; }
					case WEB_DARKMODE2: { PostMessage(m_hWnd, WM_WEB_DARKMODE, 0, 2); break; }
					}
					ran[i] = true;
				}
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
			if (ActionType[i] == 1 && done[i] && !MouseActiondone[i])
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

			if (modechanged && Transitivity < 4 && tomode != mode)
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

	if (((!Toggle && (ActionType[0] == 1 || ActionType[0] == 2) && started[0] && !done[0]) || (Toggle && mouse_toggle[0])) ||
		((!Toggle && (ActionType[1] == 1 || ActionType[1] == 2) && started[1] && !done[1]) || (Toggle && mouse_toggle[1])) ||
		((!Toggle && (ActionType[2] == 1 || ActionType[2] == 2) && started[2] && !done[2]) || (Toggle && mouse_toggle[2])) ||
		((!Toggle && (ActionType[3] == 1 || ActionType[3] == 2) && started[3] && !done[3]) || (Toggle && mouse_toggle[3])) ||
		((!Toggle && (ActionType[4] == 1 || ActionType[4] == 2) && started[0] && !done[4]) || (Toggle && mouse_toggle[4])) ||
		((!Toggle && (ActionType[5] == 1 || ActionType[5] == 2) && started[1] && !done[5]) || (Toggle && mouse_toggle[5])) ||
		((!Toggle && (ActionType[6] == 1 || ActionType[6] == 2) && started[2] && !done[6]) || (Toggle && mouse_toggle[6])) ||
		((!Toggle && (ActionType[7] == 1 || ActionType[7] == 2) && started[3] && !done[7]) || (Toggle && mouse_toggle[7])))
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
	case Led_Action_none: return I18N.EMPTY;
	case Led_Action_Led1: return I18N.LedAction_Led_1;
	case Led_Action_Led2: return I18N.LedAction_Led_2;
	case Led_Action_Led3: return I18N.LedAction_Led_3;
	case Led_Action_Led4: return I18N.LedAction_Led_4;
	case Led_Action_Led5: return I18N.LedAction_Led_5;
	case Led_Action_Battery: return I18N.LedAction_BATTERY;
	default: return I18N.WHICH;
	}
}

WCHAR* Mapping::MouseString(MouseActionID id)
{
	switch (id)
	{
	case mouse_none: return I18N.EMPTY;
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
	case MAGNIFY: return I18N.MouseAction_MAGNIFY;
	case MAGNIFY_PLUS: return I18N.MouseAction_MAGNIFY_PLUS;
	case MAGNIFY_MINUS: return I18N.MouseAction_MAGNIFY_MINUS;
	case MAGNIFY_RESET: return I18N.MouseAction_MAGNIFY_RESET;
	case MAGNIFY_UP: return I18N.MouseAction_MAGNIFY_UP;
	case MAGNIFY_DOWN: return I18N.MouseAction_MAGNIFY_DOWN;
	case MAGNIFY_LEFT: return I18N.MouseAction_MAGNIFY_LEFT;
	case MAGNIFY_RIGHT: return I18N.MouseAction_MAGNIFY_RIGHT;
	default: return I18N.WHICH;
	}
}

WCHAR* Mapping::SpecialString(SpecialActionID id)
{
	switch (id)
	{
	case mouse_none: return I18N.EMPTY;
	case MUTE_SOUND: return I18N.SpecialAction_MUTE_SOUND;
	case VOLUME_UP: return I18N.SpecialAction_VOLUME_UP;
	case VOLUME_DOWN: return I18N.SpecialAction_VOLUME_DOWN;
	case MEMORIZE_MODE: return I18N.SpecialAction_MEMORIZE_MODE;
	case TO_MEM_MODE: return I18N.SpecialAction_TO_MEM_MODE;
	case TO_MODE1: return I18N.SpecialAction_TO_MODE1;
	case TO_MODE2: return I18N.SpecialAction_TO_MODE2;
	case TO_MODE3: return I18N.SpecialAction_TO_MODE3;
	case TO_MODE4: return I18N.SpecialAction_TO_MODE4;
	case TO_MODE5: return I18N.SpecialAction_TO_MODE5;
	case TO_MODE6: return I18N.SpecialAction_TO_MODE6;
	case TO_MODE7: return I18N.SpecialAction_TO_MODE7;
	case TO_MODE8: return I18N.SpecialAction_TO_MODE8;
	case TO_LAST_MODE: return I18N.SpecialAction_TO_LAST_MODE;
	case BASE_TO_MODE1: return I18N.SpecialAction_BASE_TO_MODE1;
	case BASE_TO_MODE2: return I18N.SpecialAction_BASE_TO_MODE2;
	case BASE_TO_MODE3: return I18N.SpecialAction_BASE_TO_MODE3;
	case BASE_TO_MODE4: return I18N.SpecialAction_BASE_TO_MODE4;
	case BASE_TO_MODE5: return I18N.SpecialAction_BASE_TO_MODE5;
	case BASE_TO_MODE6: return I18N.SpecialAction_BASE_TO_MODE6;
	case BASE_TO_MODE7: return I18N.SpecialAction_BASE_TO_MODE7;
	case BASE_TO_MODE8: return I18N.SpecialAction_BASE_TO_MODE8;
	case TO_BASE_MODE: return I18N.SpecialAction_TO_BASE_MODE;
	case FORGOT_RELEASED: return I18N.SpecialAction_FORGOT_RELEASED;
	case IF_RELEASED_GOTO: return I18N.SpecialAction_IF_RELEASED_GOTO;
	case IF_PUSHED_GOTO: return I18N.SpecialAction_IF_PUSHED_GOTO;
	case RETURN_TO: return I18N.SpecialAction_RETURN_TO;
	case INTERRUPT: return I18N.SpecialAction_MOUSE_INTERRUPT;
	case NO_SUSTAIN: return I18N.SpecialAction_MOUSE_NO_SUSTAIN;
	case PAUSE: return I18N.SpecialAction_MOUSE_PAUSE;
	case BEEP1: return I18N.SpecialAction_BEEP1;
	case BEEP2: return I18N.SpecialAction_BEEP2;
	case BEEP3: return I18N.SpecialAction_BEEP3;
	case RESET_STATS: return I18N.SpecialAction_RESET_STATS;
	case ADDSTAT1: return I18N.SpecialAction_ADDSTAT1;
	case ADDSTAT2: return I18N.SpecialAction_ADDSTAT2;
	case ADDSTAT3: return I18N.SpecialAction_ADDSTAT3;
	case ADDSTAT4: return I18N.SpecialAction_ADDSTAT4;
	case ADDSTAT5: return I18N.SpecialAction_ADDSTAT5;
	case ADDSTAT6: return I18N.SpecialAction_ADDSTAT6;
	case ADDSTAT7: return I18N.SpecialAction_ADDSTAT7;
	case ADDSTAT8: return I18N.SpecialAction_ADDSTAT8;
	case KBD_INPUT_ON: return I18N.SpecialAction_KBD_INPUT_ON;
	case KBD_INPUT_OFF: return I18N.SpecialAction_KBD_INPUT_OFF;
	case MSE_INPUT_ON: return I18N.SpecialAction_MSE_INPUT_ON;
	case MSE_INPUT_OFF: return I18N.SpecialAction_MSE_INPUT_OFF;
	case SCREENSHOT: return I18N.SpecialAction_SCREENSHOT;
	case MINIMIZE: return I18N.SpecialAction_MINIMIZE;
	case RESTORE: return I18N.SpecialAction_RESTORE;
	case TRANSPARENCY: return I18N.SpecialAction_TRANSPARENCY;
	default: return I18N.WHICH;
	}
}

WCHAR* Mapping::ModulesString(ModulesActionID id)
{
	switch (id)
	{
	case modules_none: return I18N.EMPTY;
	case NOTEPAD: return I18N.ModulesAction_NOTEPAD;
	case NOTEPAD_DOWN: return I18N.ModulesAction_NOTEPAD_DOWN;
	case NOTEPAD_UP: return I18N.ModulesAction_NOTEPAD_UP;
	case WEB_DOWN: return I18N.ModulesAction_WEB_DOWN;
	case WEB_UP: return I18N.ModulesAction_WEB_UP;
	case WEB_LEFT: return I18N.ModulesAction_WEB_LEFT;
	case WEB_RIGHT: return I18N.ModulesAction_WEB_RIGHT;
	case WEB_PREVIOUSTAB: return I18N.ModulesAction_WEB_PREVIOUSTAB;
	case WEB_NEXTTAB: return I18N.ModulesAction_WEB_NEXTTAB;
	case WEB_CLOSETAB: return I18N.ModulesAction_WEB_CLOSETAB;
	case WEB_FULLSCREEN: return I18N.ModulesAction_WEB_FULLSCREEN;
	case WEB_HOME: return I18N.ModulesAction_WEB_HOME;
	case WEB_FAVORITE1: return I18N.ModulesAction_WEB_FAVORITE1;
	case WEB_FAVORITE2: return I18N.ModulesAction_WEB_FAVORITE2;
	case WEB_FAVORITE3: return I18N.ModulesAction_WEB_FAVORITE3;
	case WEB_FAVORITE4: return I18N.ModulesAction_WEB_FAVORITE4;
	case WEB_FAVORITE5: return I18N.ModulesAction_WEB_FAVORITE5;
	case WEB_FAVORITE6: return I18N.ModulesAction_WEB_FAVORITE6;
	case WEB_FAVORITE7: return I18N.ModulesAction_WEB_FAVORITE7;
	case WEB_FAVORITE8: return I18N.ModulesAction_WEB_FAVORITE8;
	case WEB_FAVORITE9: return I18N.ModulesAction_WEB_FAVORITE9;
	case WEB_BACK: return I18N.ModulesAction_WEB_BACK;
	case WEB_NEXT: return I18N.ModulesAction_WEB_NEXT;
	case WEB_REFRESH: return I18N.ModulesAction_WEB_REFRESH;
	case WEB_CANCEL: return I18N.ModulesAction_WEB_CANCEL;
	case WEB_AUTOREFRESH: return I18N.ModulesAction_WEB_AUTOREFRESH;
	case WEB_ZOOMMINUS: return I18N.ModulesAction_WEB_ZOOMMINUS;
	case WEB_ZOOMPLUS: return I18N.ModulesAction_WEB_ZOOMPLUS;
	case WEB_ZOOMRESET: return I18N.ModulesAction_WEB_ZOOMRESET;
	case WEB_ZOOMSET: return I18N.ModulesAction_WEB_ZOOMSET;
	case WEB_VISIBILITY: return I18N.ModulesAction_WEB_VISIBILITY;
	case WEB_SCREENSHOT: return I18N.ModulesAction_WEB_SCREENSHOT;
	case WEB_DARKMODE: return I18N.ModulesAction_WEB_DARKMODE;
	case WEB_DARKMODE2: return I18N.ModulesAction_WEB_DARKMODE2;
	default: return I18N.WHICH;
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

void SpecialActions(int action)
{
	switch (action)
	{
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
	case Mapping::BEEP1: { Beep(234.9, 112); break; }
	case Mapping::BEEP2: { Beep(385.3, 112); break; }
	case Mapping::BEEP3: { Beep(551.8, 112); break; }
	case Mapping::KBD_INPUT_ON: { tape.KeyboardActivetmp = true; tape.Save(tape.Setting_KeyboardActive); break; }
	case Mapping::KBD_INPUT_OFF: { tape.KeyboardActivetmp = false; tape.Save(tape.Setting_KeyboardActive); break; }
	case Mapping::MSE_INPUT_ON: { tape.MouseActivetmp = true; tape.Save(tape.Setting_MouseActive); break; }
	case Mapping::MSE_INPUT_OFF: { tape.MouseActivetmp = false; tape.Save(tape.Setting_MouseActive); break; }
	}
}
