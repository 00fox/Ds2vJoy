#include "stdafx.h"
#include "Mapping.h"

Mapping::Mapping()
{
}

Mapping::~Mapping()
{
}

WCHAR* Mapping::SrceString(unsigned char nbutton)
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Enable == 2)
		return buf;

	std::wstring str = L"";
	if (Target[nbutton] == 3)
	{
		if (srceID[nbutton] != DestinationButton::Destination_None)
			str = DestinationButton::String((DestButtonID)srceID[nbutton]);
	}
	else
	{
		if (srceID[nbutton] != SourceButton::Button_None)
			str = SourceButton::String((SrceButtonID)srceID[nbutton]);
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

	if (srceDisable[nbutton])
	{
		if (srceDisable[nbutton] == 2)
			head += swprintf_s(head, MAX_PATH, L"✱");
		else
			head += swprintf_s(head, MAX_PATH, L"#");
	}

	return buf;
}

const WCHAR* Mapping::DestString()
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
				head += swprintf_s(head, MAX_PATH, L" %s", MouseString((MouseActionID)destID[i]));
			else if (ActionType[i] == 2)
				head += swprintf_s(head, MAX_PATH, L" %s", SpecialString((SpecialActionID)destID[i]));
			else if (ActionType[i] == 3)
				head += swprintf_s(head, MAX_PATH, L" %s", DestinationButton::StringAxis((DestAxisMoveID)destID[i]));
			else if (ActionType[i] == 4)
				head += swprintf_s(head, MAX_PATH, L" %s", DestinationButton::StringEffect((DestAfterEffectID)destID[i]));
			else if (ActionType[i] == 5)
				head += swprintf_s(head, MAX_PATH, L" %s", ModulesString((ModulesActionID)destID[i]));
			else if(destID[i] != DestinationButton::Destination_None)
				head += swprintf_s(head, MAX_PATH, L" %s", DestinationButton::String((DestButtonID)destID[i]));
		}
		else
		{
			if (ActionType[i] == 1)
				{ head += swprintf_s(head, MAX_PATH, L"%s", MouseString((MouseActionID)destID[i])); firstplus = true; }
			else if (ActionType[i] == 2)
				{ head += swprintf_s(head, MAX_PATH, L"%s", SpecialString((SpecialActionID)destID[i])); firstplus = true; }
			else if (ActionType[i] == 3)
				{ head += swprintf_s(head, MAX_PATH, L"%s", DestinationButton::StringAxis((DestAxisMoveID)destID[i])); firstplus = true; }
			else if (ActionType[i] == 4)
				{ head += swprintf_s(head, MAX_PATH, L"%s", DestinationButton::StringEffect((DestAfterEffectID)destID[i])); firstplus = true; }
			else if (ActionType[i] == 5)
				{ head += swprintf_s(head, MAX_PATH, L"%s", ModulesString((ModulesActionID)destID[i])); firstplus = true; }
			else if (destID[i] != DestinationButton::Destination_None)
				{ head += swprintf_s(head, MAX_PATH, L"%s", DestinationButton::String((DestButtonID)destID[i])); firstplus = true; }
		}

		if (destDisable[i] == 1)
			head += swprintf_s(head, MAX_PATH, L"#");
		else if (destDisable[i])
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
	destUsed.clear();
	MappingButtonsString[0] = 0;
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
		m_toggle[i] = false;
	for (int i = 0; i < 8; i++)
		mouse_toggle[i] = false;
	for (int i = 0; i < LedAction_Count; i++)
		Ledactive[i] = false;
}

BOOL Mapping::LoadDevice(Source* srce, Destination* dest)
{
	if (Enable != 1)
		return FALSE;

	m_dest_X = dest->GetButton(DestButtonID::X);
	m_dest_Y = dest->GetButton(DestButtonID::Y);
	m_dest_Z = dest->GetButton(DestButtonID::Z);
	m_dest_RX = dest->GetButton(DestButtonID::RX);
	m_dest_RY = dest->GetButton(DestButtonID::RY);
	m_dest_RZ = dest->GetButton(DestButtonID::RZ);
	m_dest_SL0 = dest->GetButton(DestButtonID::SL0);
	m_dest_SL1 = dest->GetButton(DestButtonID::SL1);
	m_dest_WORK1 = dest->GetButton(DestButtonID::WORK1AX);
	m_dest_WORK2 = dest->GetButton(DestButtonID::WORK2AX);
	m_dest_WORK3 = dest->GetButton(DestButtonID::WORK3AX);
	m_dest_WORK4 = dest->GetButton(DestButtonID::WORK4AX);
	m_dest_WORK5 = dest->GetButton(DestButtonID::WORK5AX);
	m_dest_WORK6 = dest->GetButton(DestButtonID::WORK6AX);
	m_dest_WORK7 = dest->GetButton(DestButtonID::WORK7AX);
	m_dest_WORK8 = dest->GetButton(DestButtonID::WORK8AX);

	mode = 1;
	lastmode = 1;
	memmode = 1;
	basemode = 1;
	locked = 0;
	modechanged = 0;
	for (int i = 0; i < 8; i++)
		modedest[i] = 0;
	tomode = -1;
	m_srce[0] = (srceID[0] && Target[0] < 3) ? srce->GetButton((SrceButtonID)srceID[0]) : 0;
	m_srce[1] = (srceID[1] && Target[1] < 3) ? srce->GetButton((SrceButtonID)srceID[1]) : 0;
	m_srce[2] = (srceID[2] && Target[2] < 3) ? srce->GetButton((SrceButtonID)srceID[2]) : 0;
	m_srce[3] = (srceID[3] && Target[3] < 3) ? srce->GetButton((SrceButtonID)srceID[3]) : 0;
	m_srce[4] = (srceID[4] && Target[4] < 3) ? srce->GetButton((SrceButtonID)srceID[4]) : 0;
	m_dest[0] = (srceID[0] && Target[0] == 3) ? dest->GetButton((DestButtonID)srceID[0]): 0;
	m_dest[1] = (srceID[1] && Target[1] == 3) ? dest->GetButton((DestButtonID)srceID[1]): 0;
	m_dest[2] = (srceID[2] && Target[2] == 3) ? dest->GetButton((DestButtonID)srceID[2]): 0;
	m_dest[3] = (srceID[3] && Target[3] == 3) ? dest->GetButton((DestButtonID)srceID[3]): 0;
	m_dest[4] = (srceID[4] && Target[4] == 3) ? dest->GetButton((DestButtonID)srceID[4]): 0;
	m_dest[5] = (destID[0] && !ActionType[0]) ? dest->GetButton((DestButtonID)destID[0]) : ((destID[0] && ActionType[0] == 3) ? dest->GetAxis((DestAxisMoveID)destID[0]) : ((destID[0] && ActionType[0] == 4) ? dest->GetEffect((DestAfterEffectID)destID[0]) : 0));
	m_dest[6] = (destID[1] && !ActionType[1]) ? dest->GetButton((DestButtonID)destID[1]) : ((destID[1] && ActionType[1] == 3) ? dest->GetAxis((DestAxisMoveID)destID[1]) : ((destID[1] && ActionType[1] == 4) ? dest->GetEffect((DestAfterEffectID)destID[1]) : 0));
	m_dest[7] = (destID[2] && !ActionType[2]) ? dest->GetButton((DestButtonID)destID[2]) : ((destID[2] && ActionType[2] == 3) ? dest->GetAxis((DestAxisMoveID)destID[2]) : ((destID[2] && ActionType[2] == 4) ? dest->GetEffect((DestAfterEffectID)destID[2]) : 0));
	m_dest[8] = (destID[3] && !ActionType[3]) ? dest->GetButton((DestButtonID)destID[3]) : ((destID[3] && ActionType[3] == 3) ? dest->GetAxis((DestAxisMoveID)destID[3]) : ((destID[3] && ActionType[3] == 4) ? dest->GetEffect((DestAfterEffectID)destID[3]) : 0));
	m_dest[9] = (destID[4] && !ActionType[4]) ? dest->GetButton((DestButtonID)destID[4]) : ((destID[4] && ActionType[4] == 3) ? dest->GetAxis((DestAxisMoveID)destID[4]) : ((destID[4] && ActionType[4] == 4) ? dest->GetEffect((DestAfterEffectID)destID[4]) : 0));
	m_dest[10] = (destID[5] && !ActionType[5]) ? dest->GetButton((DestButtonID)destID[5]) : ((destID[5] && ActionType[5] == 3) ? dest->GetAxis((DestAxisMoveID)destID[5]) : ((destID[5] && ActionType[5] == 4) ? dest->GetEffect((DestAfterEffectID)destID[5]) : 0));
	m_dest[11] = (destID[6] && !ActionType[6]) ? dest->GetButton((DestButtonID)destID[6]) : ((destID[6] && ActionType[6] == 3) ? dest->GetAxis((DestAxisMoveID)destID[6]) : ((destID[6] && ActionType[6] == 4) ? dest->GetEffect((DestAfterEffectID)destID[6]) : 0));
	m_dest[12] = (destID[7] && !ActionType[7]) ? dest->GetButton((DestButtonID)destID[7]) : ((destID[7] && ActionType[7] == 3) ? dest->GetAxis((DestAxisMoveID)destID[7]) : ((destID[7] && ActionType[7] == 4) ? dest->GetEffect((DestAfterEffectID)destID[7]) : 0));

	for (int i = 0; i < 8; i++)
	{
		if (m_dest[i + 5] && Overcontrol[i] == 1)
		{
			if (ActionType[i] == 0)
				switch (destID[i])
				{
				case DestButtonID::X:
				case DestButtonID::XTR:
				case DestButtonID::XINV: { srce->GetButton(SrceButtonID::LX)->SetThreshold(false); break; }
				case DestButtonID::Y:
				case DestButtonID::YTR:
				case DestButtonID::YINV: { srce->GetButton(SrceButtonID::LY)->SetThreshold(false); break; }
				case DestButtonID::Z:
				case DestButtonID::ZTR:
				case DestButtonID::ZINV: { srce->GetButton(SrceButtonID::RX)->SetThreshold(false); break; }
				case DestButtonID::RZ:
				case DestButtonID::RZTR:
				case DestButtonID::RZINV: { srce->GetButton(SrceButtonID::RY)->SetThreshold(false); break; }
				}
			else if (ActionType[i] == 3)
				if (destID[i] == DestAxisMoveID::XY_CW || destID[i] == DestAxisMoveID::XY_CN || (destID[i] >= DestAxisMoveID::XY_CENTER && destID[i] <= DestAxisMoveID::XY_L_DL_CN))
				{
					srce->GetButton(SrceButtonID::LX)->SetThreshold(false);
					srce->GetButton(SrceButtonID::LY)->SetThreshold(false);
				}
				else if (destID[i] == DestAxisMoveID::ZRZ_CW || destID[i] == DestAxisMoveID::ZRZ_CN || (destID[i] >= DestAxisMoveID::ZRZ_CENTER && destID[i] <= DestAxisMoveID::ZRZ_L_DL_CN))
				{
					srce->GetButton(SrceButtonID::RX)->SetThreshold(false);
					srce->GetButton(SrceButtonID::RY)->SetThreshold(false);
				}
		}

		if (!ActionType[i])
		{
			if (!(std::find(destUsed.begin(), destUsed.end(), destID[i]) != destUsed.end()))
				if (destID[i])
				{
					destUsed.push_back(destID[i]);
					switch (destID[i])
					{
					case DestinationButton::ButtonID::Button1: { tape.destUsed[0] = true; break; }
					case DestinationButton::ButtonID::Button2: { tape.destUsed[1] = true; break; }
					case DestinationButton::ButtonID::Button3: { tape.destUsed[2] = true; break; }
					case DestinationButton::ButtonID::Button4: { tape.destUsed[3] = true; break; }
					case DestinationButton::ButtonID::Button5: { tape.destUsed[4] = true; break; }
					case DestinationButton::ButtonID::Button6: { tape.destUsed[5] = true; break; }
					case DestinationButton::ButtonID::Button7: { tape.destUsed[6] = true; break; }
					case DestinationButton::ButtonID::Button8: { tape.destUsed[7] = true; break; }
					case DestinationButton::ButtonID::Button9: { tape.destUsed[8] = true; break; }
					case DestinationButton::ButtonID::Button10: { tape.destUsed[9] = true; break; }
					case DestinationButton::ButtonID::Button11: { tape.destUsed[10] = true; break; }
					case DestinationButton::ButtonID::Button12: { tape.destUsed[11] = true; break; }
					case DestinationButton::ButtonID::Button13: { tape.destUsed[12] = true; break; }
					case DestinationButton::ButtonID::Button14: { tape.destUsed[13] = true; break; }
					case DestinationButton::ButtonID::Button15: { tape.destUsed[14] = true; break; }
					case DestinationButton::ButtonID::Button16: { tape.destUsed[15] = true; break; }
					case DestinationButton::ButtonID::Button17: { tape.destUsed[16] = true; break; }
					case DestinationButton::ButtonID::Button18: { tape.destUsed[17] = true; break; }
					case DestinationButton::ButtonID::Button19: { tape.destUsed[18] = true; break; }
					case DestinationButton::ButtonID::Button20: { tape.destUsed[19] = true; break; }
					case DestinationButton::ButtonID::Button21: { tape.destUsed[20] = true; break; }
					case DestinationButton::ButtonID::Button22: { tape.destUsed[21] = true; break; }
					case DestinationButton::ButtonID::Button23: { tape.destUsed[22] = true; break; }
					case DestinationButton::ButtonID::Button24: { tape.destUsed[23] = true; break; }
					case DestinationButton::ButtonID::Button25: { tape.destUsed[24] = true; break; }
					case DestinationButton::ButtonID::Button26: { tape.destUsed[25] = true; break; }
					case DestinationButton::ButtonID::Button27: { tape.destUsed[26] = true; break; }
					case DestinationButton::ButtonID::Button28: { tape.destUsed[27] = true; break; }
					case DestinationButton::ButtonID::Button29: { tape.destUsed[28] = true; break; }
					case DestinationButton::ButtonID::Button30: { tape.destUsed[29] = true; break; }
					case DestinationButton::ButtonID::Button31: { tape.destUsed[30] = true; break; }
					case DestinationButton::ButtonID::Button32: { tape.destUsed[31] = true; break; }
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
				if ((MouseActionID)destID[i] == ACTIVE_MOUSE)
					mouse_toggle[i] = true;
				else
					continue;
			}
			else if (!ActionType[i] && !Switch[i])
				if (m_dest[i + 5])
				{
					m_toggle[destID[i]] = true;
					m_dest[i + 5]->SetVal(0xFFFF);
					m_dest[i + 5]->SetPushed();
				}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		exists[i] = (Target[i] == 3) ? ((m_dest[i]) ? true : false) : ((m_srce[i]) ? true : false);
		releasedVal[i] = (unsigned short)((exists[i]) ? ((Target[i] == 3) ? (m_dest[i] ? m_dest[i]->GetReleasedVal() : 0) : (m_srce[i] ? m_srce[i]->GetReleasedVal() : 0)) : 0);
	}

	GridCanbeUsed =
		destID[0] != MOVE_TO_XY && destID[0] != SAVE_AND_MOVE_TO_XY &&
		destID[0] != MOVE_TO_WH && destID[0] != SAVE_AND_MOVE_TO_WH &&
		destID[0] != MOVE_TO_NN && destID[0] != SAVE_AND_MOVE_TO_NN &&
			destID[1] != MOVE_TO_XY && destID[1] != SAVE_AND_MOVE_TO_XY &&
			destID[1] != MOVE_TO_WH && destID[1] != SAVE_AND_MOVE_TO_WH &&
			destID[1] != MOVE_TO_NN && destID[1] != SAVE_AND_MOVE_TO_NN &&
		destID[2] != MOVE_TO_XY && destID[2] != SAVE_AND_MOVE_TO_XY &&
		destID[2] != MOVE_TO_WH && destID[2] != SAVE_AND_MOVE_TO_WH &&
		destID[2] != MOVE_TO_NN && destID[2] != SAVE_AND_MOVE_TO_NN &&
			destID[3] != MOVE_TO_XY && destID[3] != SAVE_AND_MOVE_TO_XY &&
			destID[3] != MOVE_TO_WH && destID[3] != SAVE_AND_MOVE_TO_WH &&
			destID[3] != MOVE_TO_NN && destID[3] != SAVE_AND_MOVE_TO_NN &&
		destID[4] != MOVE_TO_XY && destID[4] != SAVE_AND_MOVE_TO_XY &&
		destID[4] != MOVE_TO_WH && destID[4] != SAVE_AND_MOVE_TO_WH &&
		destID[4] != MOVE_TO_NN && destID[4] != SAVE_AND_MOVE_TO_NN &&
			destID[5] != MOVE_TO_XY && destID[5] != SAVE_AND_MOVE_TO_XY &&
			destID[5] != MOVE_TO_WH && destID[5] != SAVE_AND_MOVE_TO_WH &&
			destID[5] != MOVE_TO_NN && destID[5] != SAVE_AND_MOVE_TO_NN &&
		destID[6] != MOVE_TO_XY && destID[6] != SAVE_AND_MOVE_TO_XY &&
		destID[6] != MOVE_TO_WH && destID[6] != SAVE_AND_MOVE_TO_WH &&
		destID[6] != MOVE_TO_NN && destID[6] != SAVE_AND_MOVE_TO_NN &&
			destID[7] != MOVE_TO_XY && destID[7] != SAVE_AND_MOVE_TO_XY &&
			destID[7] != MOVE_TO_WH && destID[7] != SAVE_AND_MOVE_TO_WH &&
			destID[7] != MOVE_TO_NN && destID[7] != SAVE_AND_MOVE_TO_NN;

	release = std::chrono::system_clock::now();

	return TRUE;
}

void Mapping::RunFirst(Destination* dest)
{
	srceDisabled.clear();
	destDisabled.clear();
	mouseabolute = 1;
	for (int i = 0; i < 3; i++)
		mousemode[i] = 0;
	for (int i = 0; i < 5; i++)
		grid[i] = 0;
	isGridNeeded = 0;
	mouseactivated = false;
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
	{
		if (m_toggle[i])
		{
			dest->GetButton((DestButtonID)i)->SetVal(0xFFFF);
			dest->GetButton((DestButtonID)i)->SetPushed();
		}
		dest->GetButton((DestButtonID)i)->setOverwrite();
	}
	for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
		dest->GetAxis((DestAxisMoveID)i)->setOverwrite();
}

void Mapping::RunLast(Source* srce, Destination* dest)
{
	tape.MagCanUninitialize = magnifyUnLock;

	MappingButtonsString[0] = '\0';
	WCHAR* head = MappingButtonsString;
	head += swprintf_s(head, MAX_PATH, L"%s", I18N.MappingButtonsString);

	m_dest_X->ResetCounter();
	m_dest_Y->ResetCounter();
	m_dest_Z->ResetCounter();
	m_dest_RX->ResetCounter();
	m_dest_RY->ResetCounter();
	m_dest_RZ->ResetCounter();
	m_dest_SL0->ResetCounter();
	m_dest_SL1->ResetCounter();
	m_dest_WORK1->ResetCounter();
	m_dest_WORK2->ResetCounter();
	m_dest_WORK3->ResetCounter();
	m_dest_WORK4->ResetCounter();
	m_dest_WORK5->ResetCounter();
	m_dest_WORK6->ResetCounter();
	m_dest_WORK7->ResetCounter();
	m_dest_WORK8->ResetCounter();

	for (int i = 0; i < destUsed.size(); i++)
	{
		if (!dest->GetButton((DestButtonID)destUsed[i])->isPushed())
			dest->GetButton((DestButtonID)destUsed[i])->Release();
		else
			head += swprintf_s(head, MAX_PATH, L" %s", DestinationButton::String((DestButtonID)destUsed[i]));
	}

	if (tape.ActualSource == 2)
	{
		byte m_Whitetmp = 0x00;

		if (!Ledactive[LedAction_Led1] && !Ledactive[LedAction_Led2] && !Ledactive[LedAction_Led3] && !Ledactive[LedAction_Led4] && !Ledactive[LedAction_Led5] && Ledactive[LedAction_Battery])
		{
			if (tape.BatteryLevel < 21)
				m_Whitetmp = 0x01;
			else if (tape.BatteryLevel < 41)
				m_Whitetmp = 0x03;
			else if (tape.BatteryLevel < 61)
				m_Whitetmp = 0x07;
			else if (tape.BatteryLevel < 81)
				m_Whitetmp = 0x0b;
			else
				m_Whitetmp = 0x1b;
		}
		else
		{
			if (Ledactive[LedAction_Led1])
				m_Whitetmp = 0x01;
			if (Ledactive[LedAction_Led2])
				m_Whitetmp = m_Whitetmp | 0x02;
			if (Ledactive[LedAction_Led3])
				m_Whitetmp = m_Whitetmp | 0x04;
			if (Ledactive[LedAction_Led4])
				m_Whitetmp = m_Whitetmp | 0x08;
			if (Ledactive[LedAction_Led5])
				m_Whitetmp = m_Whitetmp | 0x10;
		}

		srce->SetWhiteLED(m_Whitetmp);
	}
}

void Mapping::Run(double average)
{
	if (tape.MappingPaused)
		return;

	for (int i = 0; i < 5; i++)
		pushed[i] = (exists[i]) ? ((Target[i] == 3) ? ((m_dest[i]->isPushed()) ? true : false) : ((m_srce[i]->isPushed()) ? true : false)) : false;

	for (int i = 0; i < 5; i++)
	{
		disabled[i] = false;
		if (Target[i] == 3)
		{
			if (m_dest[i])
			{
				if (std::find(destDisabled.begin(), destDisabled.end(), srceID[i]) != destDisabled.end())
					disabled[i] = true;
			}
		}
		else
		{
			if (m_srce[i])
				if (std::find(srceDisabled.begin(), srceDisabled.end(), srceID[i]) != srceDisabled.end())
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

		unsigned short value0 = (unsigned short)((pushed[0]) ? ((Target[0] == 3) ? m_dest[0]->GetVal() : m_srce[0]->GetVal()) : 0);
		unsigned short value1 = (unsigned short)((pushed[1]) ? ((Target[1] == 3) ? m_dest[1]->GetVal() : m_srce[1]->GetVal()) : 0);
		unsigned short value2 = (unsigned short)((pushed[2]) ? ((Target[2] == 3) ? m_dest[2]->GetVal() : m_srce[2]->GetVal()) : 0);

		Interrupttmp = false;
		NoSustain = false;
		Pausetmp = false;
		for (int i = 0; i < 8; i++)
		{
			started[i] = (OnRelease[i] == 1) ? ((released) ? (end2 - release2 >= randStart[i]) : false) : (end2 - start2 >= randStart[i]);
			done[i] = (ran[i]) ? ((ActionType[i] == 4) ? released : ((OnRelease[i]) ? ((released) ? ((end2 - release2 >= randStop[i])) : false) : ((Stop[i]) ? (end2 - start2 >= randStop[i]) : released))) : false;
			if (modedest[i] == 2 && released) done[i] = true;
			if (ActionType[i] == 2)
				if (started[i] && !done[i])
					switch (destID[i])
					{
					case INTERRUPT: { Interrupttmp = true; ran[i] = true; break; }
					case NO_SUSTAIN: { NoSustain = true; ran[i] = true; break; }
					case PAUSE: { Pausetmp = true; ran[i] = true; break; }
					}
		}

		m_data = (exists[0]) ?
			((released && Macro != 2 && !NoSustain) ?
				0xFFFF :
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
				0xFFFF :
				((exists[1]) ?
					releasedVal[1] :
					((exists[2]) ?
						releasedVal[2] :
						0)));

		magnifyUnLock = true;
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
					destID[i] == SCROLL_UP_VARIABLE || destID[i] == SCROLL_DOWN_VARIABLE ||
					destID[i] == MAGNIFY_PLUS || destID[i] == MAGNIFY_MINUS ||
					destID[i] == MAGNIFY_UP || destID[i] == MAGNIFY_DOWN ||
					destID[i] == MAGNIFY_LEFT || destID[i] == MAGNIFY_RIGHT ||
					destID[i] == MAGNIFY_LOCK ||
					(Stop[i] && (
						destID[i] == MOVE_TO_XY || destID[i] == SAVE_AND_MOVE_TO_XY ||
						destID[i] == MOVE_TO_WH || destID[i] == SAVE_AND_MOVE_TO_WH ||
						destID[i] == MOVE_TO_NN || destID[i] == SAVE_AND_MOVE_TO_NN))))
				{
					switch (destID[i])
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
							double x = actualpoint.x;
							double y = actualpoint.y;
							double steps = (double)floor(max(1, ((randStop[i] - (end2 - ((OnRelease[i] == 1) ? release2 : start2))) / std::chrono::nanoseconds(int(average * 1000000)))));
							if ((Macro == 1 || Interrupttmp) && released)
							{
								steps = 1;
								randStop[i] = std::chrono::milliseconds(0);
								ran[i] = 0;
							}
							SetCursorPos(int(x + (((double)Grid[0] - x) / steps)), int(y + (((double)Grid[1] - y) / steps)));
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
							double x = actualpoint.x;
							double y = actualpoint.y;
							double steps = (double)floor(max(1, ((randStop[i] - (end2 - ((OnRelease[i] == 1) ? release2 : start2))) / std::chrono::nanoseconds(int(average * 1000000)))));
							if ((Macro == 1 || Interrupttmp) && released)
							{
								steps = 1;
								randStop[i] = std::chrono::milliseconds(0);
								ran[i] = 0;
							}
							SetCursorPos(int(x + (((double)Grid[2] - x) / steps)), int(y + (((double)Grid[3] - y) / steps)));
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
						if (Stop[i] && destID[i] == SAVE_AND_MOVE_TO_NN)
						{
							POINT actualpoint;
							GetCursorPos(&actualpoint);
							double x = actualpoint.x;
							double y = actualpoint.y;
							double steps = (double)floor(max(1, ((randStop[i] - (end2 - ((OnRelease[i] == 1) ? release2 : start2))) / std::chrono::nanoseconds(int(average * 1000000)))));
							if ((Macro == 1 || Interrupttmp) && released)
							{
								steps = 1;
								randStop[i] = std::chrono::milliseconds(0);
								ran[i] = 0;
							}
							SetCursorPos(int(x + (((double)Grid[4] - x) / steps)), int(y + (((double)Grid[5] - y) / steps)));
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
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
								{
									unsigned long long delta = cycle;
									delta = delta * delta / 1600;
									std::thread(MouseActions, (MouseActionID)destID[i], (int)min(240, delta)).detach();
								}
							}
							else
							{
								if (!(cycle % llround(1 + 72 / average)))
									std::thread(MouseActions, (MouseActionID)destID[i], 600 - (modulo * 5)).detach();
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
							PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_SET, 0), MAKELPARAM(Grid[4], Grid[5]));
							MagFactor = 0;
						}
						PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(Method, 0), MAKELPARAM(xOffset, yOffset));
						break;
					}
					case MAGNIFY_PLUS:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(1, 0)); break; }
							}
							else
							{
								if (!(cycle % llround(1 + modulo * 4 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(1, 0)); break; }
							}
						break;
					}
					case MAGNIFY_MINUS:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(0, 1)); break; }
							}
							else
							{
								if (!(cycle % llround(1 + modulo * 4 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_ZOOM, 0), MAKELPARAM(0, 1)); break; }
							}
						break;
					}
					case MAGNIFY_RESET: { PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_RESET, 0), MAKELPARAM(0, 0)); break; }
					case MAGNIFY_UP:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 3), MAKELPARAM(0, 10)); break; }
							}
							else
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 3), MAKELPARAM(0, unsigned short(100 / modulo))); break; }
							}
						break;
					}
					case MAGNIFY_DOWN:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM(0, 10)); break; }
							}
							else
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM(0, (100 / modulo))); break; }
							}
						break;
					}
					case MAGNIFY_LEFT:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 1), MAKELPARAM(10, 0)); break; }
							}
							else
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 1), MAKELPARAM(unsigned short(100 / modulo), 0)); break; }
							}
						break;
					}
					case MAGNIFY_RIGHT:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM(10, 0)); break; }
							}
							else
							{
								if (!(cycle % llround(1 + 20 / average)))
									{ PostMessage(tape.Ds2hWnd, WM_SET_MAGNIFY, MAKEWPARAM(MAG_METHOD_MOVE, 0), MAKELPARAM((100 / modulo), 0)); break; }
							}
						break;
					}
					case MAGNIFY_LOCK:
					{
						magnifyUnLock = false;
						if (!(cycle % llround(1 + 72 / average)))
						{
							if (!tape.MagInitialized)
								if (MagInitialize())
									tape.MagInitialized = true;
						}
						break;
					}
					case MAGNIFY_CURSOR_ON:
					{
						tape.MagCursor = true;
						MagShowSystemCursor(true);
						break;
					}
					case MAGNIFY_CURSOR_OFF:
					{
						tape.MagCursor = false;
						MagShowSystemCursor(false);
						break;
					}
					case MAGNIFY_CURSOR_SWITCH:
					{
						tape.MagCursor = !tape.MagCursor;
						MagShowSystemCursor(tape.MagCursor);
						break;
					}
					case MSE_CAN_BYPASS_ON: { tape.MouseCanBypasstmp = true; break; }
					case MSE_CAN_BYPASS_OFF: { tape.MouseCanBypasstmp = false; break; }
					default: { std::thread(MouseActions, (MouseActionID)destID[i], 0).detach(); break; }
					}
					ran[i] = true;
				}
			}
			else if (ActionType[i] == 2)
			{
				if (destID[i] == TO_LAST_MODE || destID[i] == IF_RELEASED_GOTO || destID[i] == IF_PUSHED_GOTO)
					if (ran[i])
						done[i] = true;
				if (started[i] && !done[i] && (!ran[i] || destID[i] == VOLUME_UP || destID[i] == VOLUME_DOWN || destID[i] == CHANGE_POSITION))
				{
					switch (destID[i])
					{
					case VOLUME_UP:
					case VOLUME_DOWN:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt((cycle * cycle * 16 / average) / average)))))
									std::thread(SpecialActions, (MouseActionID)destID[i]).detach();
							}
							else
							{
								if (!(cycle % llround(1 + modulo * 4 / average)))
									std::thread(SpecialActions, (MouseActionID)destID[i]).detach();
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
					case CHANGE_POSITION: { tape.zoneChange = true; break;}
					case STANCE1: { tape.Stance = 0; break;}
					case STANCE2: { tape.Stance = 1; break;}
					case STANCE3: { tape.Stance = 2; break;}
					case STANCE4: { tape.Stance = 3; break;}
					case STANCE5: { tape.Stance = 4; break;}
					case RESET_STATS: { for (int i = 0; i < 8; i++) tape.Stat[i] = 0; break; }
					case ADDSTAT1: { tape.Stat[0] += 1; break; }
					case ADDSTAT2: { tape.Stat[1] += 1; break; }
					case ADDSTAT3: { tape.Stat[2] += 1; break; }
					case ADDSTAT4: { tape.Stat[3] += 1; break; }
					case ADDSTAT5: { tape.Stat[4] += 1; break; }
					case ADDSTAT6: { tape.Stat[5] += 1; break; }
					case ADDSTAT7: { tape.Stat[6] += 1; break; }
					case ADDSTAT8: { tape.Stat[7] += 1; break; }
					case KBD_INPUT_ON: { tape.KeyboardActivetmp = true; break; }
					case KBD_INPUT_OFF: { tape.KeyboardActivetmp = false; break; }
					case MSE_INPUT_ON: { tape.MouseActivetmp = true; break; }
					case MSE_INPUT_OFF: { tape.MouseActivetmp = false; break; }
					case SCREENSHOT: { PostMessage(tape.Ds2hWnd, WM_SCREENSHOT, MAKEWPARAM(Grid[0], Grid[1]), MAKELPARAM(Grid[2], Grid[3])); break; }
					case MINIMIZE: { PostMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); break; }
					case RESTORE: { PostMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_RESTORE, 0); break; }
					case TRANSPARENCY: { PostMessage(tape.Ds2hWnd, WM_TRANSPARENCY, 0, 1); break; }
					case INPUT_OFF: { tape.PreferredSource = 0; tape.Save(tape.Setting_PreferredSource); PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);; break; }
					case DS4_INPUT_ON: { tape.PreferredSource = 1; tape.Save(tape.Setting_PreferredSource); PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);; break; }
					case DS5_INPUT_ON: { tape.PreferredSource = 2; tape.Save(tape.Setting_PreferredSource); PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);; break; }
					case DI_INPUT_ON: { tape.PreferredSource = 3; tape.Save(tape.Setting_PreferredSource); PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);; break; }
					case XI_INPUT_ON: { tape.PreferredSource = 4; tape.Save(tape.Setting_PreferredSource); PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);; break; }
					case EXIT: { PostMessage(tape.Ds2hWnd, WM_DESTROY, 0, 0); break; }
					default: { std::thread(SpecialActions, (SpecialActionID)destID[i]).detach(); break; }
					}
					ran[i] = true;
				}
			}
			else if (ActionType[i] == 3)
			{
				if (started[i] && !done[i])
				{
					if (m_dest[i + 5])
					{
						if (m_dest[i + 5]->isOverWrite() && m_dest[i + 5]->isOverWrite2())
						{
							double initialval1 = m_dest[i + 5]->GetVal();
							double initialval2 = m_dest[i + 5]->GetVal2();
							if (Start[i] || Stop[i])
							{
								unsigned short m_dataRing = (unsigned short)((OnRelease[i] == 2) ?
									((((min(randStop[i] - randStart[i], end2 - randStart[i] - start2))) * 65535) / (randStop[i] - randStart[i])) :
									((((end2 - randStart[i] - ((OnRelease[i] == 1) ? release2 : start2))) * 65535) / (randStop[i] - randStart[i])));
								m_dest[i + 5]->SetVal(m_dataRing);
							}
							else
								m_dest[i + 5]->SetVal(m_data);
							m_dest[i + 5]->SetPushed();

							if (Overcontrol[i] == 1)
							{
								int counter1 = 0;
								int counter2 = 0;
								switch (m_dest[i + 5]->GetCounterType())
								{
								case DestAxisID::Axis_XY: { counter1 = m_dest_X->GetCounter(); counter2 = m_dest_Y->GetCounter(); break; }
								case DestAxisID::Axis_ZRZ: { counter1 = m_dest_Z->GetCounter(); counter2 = m_dest_RZ->GetCounter(); break; }
								case DestAxisID::Axis_RXRY: { counter1 = m_dest_RX->GetCounter(); counter2 = m_dest_RY->GetCounter(); break; }
								case DestAxisID::Axis_SL0SL1: { counter1 = m_dest_SL0->GetCounter(); counter2 = m_dest_SL1->GetCounter(); break; }
								}
								if (counter1 > 1)
									m_dest[i + 5]->SetVal1((m_dest[i + 5]->GetVal() + (initialval1 * (counter1 - 1))) / counter1);
								if (counter2 > 1)
									m_dest[i + 5]->SetVal2((m_dest[i + 5]->GetVal2() + (initialval2 * (counter2 - 1))) / counter2);
							}
							else if (Overcontrol[i] == 2)
								m_dest[i + 5]->setOverwrite(false);
						}
					}
				}
				ran[i] = true;
			}
			else if (ActionType[i] == 4)
			{
				if (started[i] && !done[i])
					if (m_dest[i + 5])
						m_dest[i + 5]->SetVal(max(0, min(1000, int(Stop[i]))));
				ran[i] = true;
			}
			else if (ActionType[i] == 5)
			{
				if (started[i] && !done[i] && (!ran[i] || destID[i] == WEB_ZOOMMINUS || destID[i] == WEB_ZOOMPLUS ||
						destID[i] == WEB_DOWN || destID[i] == WEB_UP || destID[i] == WEB_LEFT || destID[i] == WEB_RIGHT))
				{
					switch (destID[i])
					{
					case NOTEPAD: { PostMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); break; }
					case NOTEPAD_DOWN: { PostMessage(tape.Ds2hWnd, WM_NOTEPAD_SCROLL, 0, 0); break; }
					case NOTEPAD_UP: { PostMessage(tape.Ds2hWnd, WM_NOTEPAD_SCROLL, 0, 1); break; }
					case LINKS_APPLICATION0: { PostMessage(tape.Ds2hWnd, WM_COMMAND, IDM_APP0, 0); break; }
					case LINKS_APPLICATION1: { PostMessage(tape.Ds2hWnd, WM_COMMAND, IDM_APP1, 0); break; }
					case LINKS_APPLICATION2: { PostMessage(tape.Ds2hWnd, WM_COMMAND, IDM_APP2, 0); break; }
					case LINKS_APPLICATION3: { PostMessage(tape.Ds2hWnd, WM_COMMAND, IDM_APP3, 0); break; }
					case LINKS_APPLICATION4: { PostMessage(tape.Ds2hWnd, WM_COMMAND, IDM_APP4, 0); break; }
					}

					if (tape.isExplorerLoaded)
					switch (destID[i])
					{
					case WEB_DOWN:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % llround(1 + 72 / average)))
						{
							if (modulo == -1)
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, 0, 90);
							else
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, 0, (540 / modulo));
						}
						break;
					}
					case WEB_UP:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % llround(1 + 72 / average)))
						{
							if (modulo == -1)
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, 0, -90);
							else
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, 0, (-540 / modulo));
						}
						break;
					}
					case WEB_LEFT:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % llround(1 + 72 / average)))
						{
							if (modulo == -1)
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, -90, 0);
							else
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, (-540 / modulo), 0);
						}
						break;
					}
					case WEB_RIGHT:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo && !(cycle % llround(1 + 72 / average)))
						{
							if (modulo == -1)
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, 90, 0);
							else
								PostMessage(tape.Ds2hWnd, WM_WEB_SCROLL, (540 / modulo), 0);
						}
						break;
					}
					case WEB_PREVIOUSTAB: { PostMessage(tape.Ds2hWnd, WM_WEB_CHANGETAB, 0, 0); break; }
					case WEB_NEXTTAB: { PostMessage(tape.Ds2hWnd, WM_WEB_CHANGETAB, 0, 1); break; }
					case WEB_CLOSETAB: { PostMessage(tape.Ds2hWnd, WM_COMMAND, ID_WEBCLOSE, -1); break; }
					case WEB_FULLSCREEN: { PostMessage(tape.Ds2hWnd, WM_WEB_FULLSCREEN, 0, 0); break; }
					case WEB_FAVORITE1: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 1); break; }
					case WEB_FAVORITE2: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 2); break; }
					case WEB_FAVORITE3: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 3); break; }
					case WEB_FAVORITE4: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 4); break; }
					case WEB_FAVORITE5: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 5); break; }
					case WEB_FAVORITE6: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 6); break; }
					case WEB_FAVORITE7: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 7); break; }
					case WEB_FAVORITE8: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 8); break; }
					case WEB_FAVORITE9: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 9); break; }
					case WEB_HOME: { PostMessage(tape.Ds2hWnd, WM_WEB_FAVORITE, 0, 0); break; }
					case WEB_BACK: { PostMessage(tape.Ds2hWnd, WM_WEB_BACK, 0, 0); break; }
					case WEB_NEXT: { PostMessage(tape.Ds2hWnd, WM_WEB_NEXT, 0, 0); break; }
					case WEB_REFRESH: { PostMessage(tape.Ds2hWnd, WM_WEB_REFRESH, 0, 0); break; }
					case WEB_CANCEL: { PostMessage(tape.Ds2hWnd, WM_WEB_CANCEL, 0, 0); break; }
					case WEB_AUTOREFRESH: { PostMessage(tape.Ds2hWnd, WM_WEB_AUTOREFRESH, 0, 0); break; }
					case WEB_ZOOMMINUS:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt((cycle * cycle * 16 / average) / average)))))
									PostMessage(tape.Ds2hWnd, WM_WEB_ZOOM, 0, 0);
							}
							else
							{
								if (!(cycle % llround(1 + modulo * 4 / average)))
									PostMessage(tape.Ds2hWnd, WM_WEB_ZOOM, 0, 0);
							}
						break;
					}
					case WEB_ZOOMPLUS:
					{
						short modulo = (Target[0] == 3) ? ((m_dest[0]) ? m_dest[0]->GetScrollVal() : -1) : ((m_srce[0]) ? m_srce[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt((cycle * cycle / average) / average)))))
									PostMessage(tape.Ds2hWnd, WM_WEB_ZOOM, 0, 1);
							}
							else
							{
								if (!(cycle % llround(1 + modulo * 4 / average)))
									PostMessage(tape.Ds2hWnd, WM_WEB_ZOOM, 0, 1);
							}
						break;
					}
					case WEB_ZOOMRESET: { PostMessage(tape.Ds2hWnd, WM_WEB_ZOOMRESET, 0, 0); break; }
					case WEB_ZOOMSET: { PostMessage(tape.Ds2hWnd, WM_WEB_ZOOMSET, 0, 0); break; }
					case WEB_VISIBILITY: { PostMessage(tape.Ds2hWnd, WM_WEB_VISIBILITY, 0, 0); break; }
					case WEB_SCREENSHOT: { PostMessage(tape.Ds2hWnd, WM_WEB_SCREENSHOT, 0, 0); break; }
					case WEB_DARKMODE: { PostMessage(tape.Ds2hWnd, WM_WEB_DARKMODE, 0, 1); break; }
					case WEB_DARKMODE2: { PostMessage(tape.Ds2hWnd, WM_WEB_DARKMODE, 0, 2); break; }
					}
					ran[i] = true;
				}
			}
			else
			{
				if (started[i] && !done[i])
				{
					if (m_dest[i + 5])
					{
						if (Switch[i])
						{
							if (!ran[i])
								m_toggle[destID[i]] = (Switch[i] == 1) ? true : false;
						}
						else if (Toggle)
						{
							if (!Toggledone[i])
							{
								Toggledone[i] = true;
								m_toggle[destID[i]] = !m_toggle[destID[i]];
							}
						}
						else
						{
							if (m_dest[i + 5]->isOverWrite())
							{
								int initialval = m_dest[i + 5]->GetVal();
								m_dest[i + 5]->SetVal(m_data);
								m_dest[i + 5]->SetPushed();

								if (Overcontrol[i] == 1)
								{
									int counter = m_dest[i + 5]->GetCounter();
									if (counter > 1)
										m_dest[i + 5]->SetVal((m_dest[i + 5]->GetVal() + (initialval * (counter - 1))) / counter);
								}
								else if (Overcontrol[i] == 2)
									m_dest[i + 5]->setOverwrite(false);
							}
						}
					}
					ran[i] = true;
				}
				if (m_toggle[destID[i]])
				{
					m_dest[i + 5]->SetVal((m_data) ? m_data : ((done[i]) ? 0xFFFF : 0));
					m_dest[i + 5]->SetPushed();
				}
			}
		}

		for (int i = 0; i < 8; i++)
			if (ActionType[i] == 1 && done[i] && !MouseActiondone[i])
			{
				MouseActiondone[i] = true;
				std::thread(MouseActionEnd, (MouseActionID)destID[i]).detach();
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
				if (srceDisable[i])
					if (Target[i] == 3)
					{
						if (m_dest[i])
						{
							destDisabled.push_back(srceID[i]);
							m_dest[i]->SetPushed(false);
						}
					}
					else
					{
						if (m_srce[i])
							srceDisabled.push_back(srceID[i]);
					}
			}
			for (int i = 0; i < 8; i++)
			{
				if ((destDisable[i] == 2) || (destDisable[i] == 1 && started[i] && !done[i]))
				{
					if (m_dest[i + 5])
					{
						destDisabled.push_back(destID[i]);
						m_dest[i + 5]->SetPushed(false);
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

		isGridNeeded = (Mouse[6]) ? ((Mouse[6] == 1) ? true : false) : isGridNeeded;
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
		cycle = double((floor((Stop[TimeActiondone] / average)) - 1));
		std::chrono::system_clock::time_point start2tmp = std::chrono::system_clock::now() - std::chrono::milliseconds(Stop[TimeActiondone]);
		release2 = start2tmp + (release2 - start2);
		start2 = start2tmp;
	}

	cycle += 1;
}

void Mapping::PreLaunchDisable()
{
	for (int i = 0; i < 5; i++)
	{
		if (srceDisable[i] == 2)
			if (Target[i] == 3)
			{
				if (m_dest[i])
				{
					destDisabled.push_back(srceID[i]);
					m_dest[i]->SetPushed(false);
				}
			}
			else
			{
				if (m_srce[i])
					srceDisabled.push_back(srceID[i]);
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
	case LedAction_None: return I18N.EMPTY;
	case LedAction_Led1: return I18N.LedAction_Led_1;
	case LedAction_Led2: return I18N.LedAction_Led_2;
	case LedAction_Led3: return I18N.LedAction_Led_3;
	case LedAction_Led4: return I18N.LedAction_Led_4;
	case LedAction_Led5: return I18N.LedAction_Led_5;
	case LedAction_Battery: return I18N.LedAction_BATTERY;
	default: return I18N.WHICH;
	}
}

WCHAR* Mapping::MouseString(MouseActionID id)
{
	switch (id)
	{
	case MouseAction_None: return I18N.EMPTY;
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
	case MAGNIFY_LOCK: return I18N.MouseAction_MAGNIFY_LOCK;
	case MAGNIFY_CURSOR_ON: return I18N.MouseAction_MAGNIFY_CURSOR_ON;
	case MAGNIFY_CURSOR_OFF: return I18N.MouseAction_MAGNIFY_CURSOR_OFF;
	case MAGNIFY_CURSOR_SWITCH: return I18N.MouseAction_MAGNIFY_CURSOR_SWITCH;
	case MSE_CAN_BYPASS_ON: return I18N.MouseAction_MSE_CAN_BYPASS_ON;
	case MSE_CAN_BYPASS_OFF: return I18N.MouseAction_MSE_CAN_BYPASS_OFF;
	default: return I18N.WHICH;
	}
}

WCHAR* Mapping::SpecialString(SpecialActionID id)
{
	switch (id)
	{
	case MouseAction_None: return I18N.EMPTY;
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
	case INTERRUPT: return I18N.SpecialAction_INTERRUPT;
	case NO_SUSTAIN: return I18N.SpecialAction_NO_SUSTAIN;
	case PAUSE: return I18N.SpecialAction_PAUSE;
	case CHANGE_POSITION: return I18N.SpecialAction_CHANGE_POSITION;
	case STANCE1: return I18N.SpecialAction_STANCE1;
	case STANCE2: return I18N.SpecialAction_STANCE2;
	case STANCE3: return I18N.SpecialAction_STANCE3;
	case STANCE4: return I18N.SpecialAction_STANCE4;
	case STANCE5: return I18N.SpecialAction_STANCE5;
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
	case INPUT_OFF: return I18N.SpecialAction_INPUT_OFF;
	case DS4_INPUT_ON: return I18N.SpecialAction_DS4_INPUT_ON;
	case DS5_INPUT_ON: return I18N.SpecialAction_DS5_INPUT_ON;
	case DI_INPUT_ON: return I18N.SpecialAction_DI_INPUT_ON;
	case XI_INPUT_ON: return I18N.SpecialAction_XI_INPUT_ON;
	case EXIT: return I18N.SpecialAction_EXIT;
	default: return I18N.WHICH;
	}
}

WCHAR* Mapping::ModulesString(ModulesActionID id)
{
	switch (id)
	{
	case ModulesAction_None: return I18N.EMPTY;
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
	case LINKS_APPLICATION0: return I18N.ModulesAction_LINKS_APPLICATION0;
	case LINKS_APPLICATION1: return I18N.ModulesAction_LINKS_APPLICATION1;
	case LINKS_APPLICATION2: return I18N.ModulesAction_LINKS_APPLICATION2;
	case LINKS_APPLICATION3: return I18N.ModulesAction_LINKS_APPLICATION3;
	case LINKS_APPLICATION4: return I18N.ModulesAction_LINKS_APPLICATION4;
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
	}
}
