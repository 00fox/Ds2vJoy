#include "stdafx.h"
#include "Mapping.h"
#include "Ds2vJoy.h"

Mapping::Mapping()
	:Enable(false)
	, dsID()
	, vjID()
	, Target()
	, Disbale()
	, OrXorNot()
	, Ifmouse(false)
	, Force(0)
	, Led(0)
	, Short(false)
	, Double(false)
	, Long(false)
	, Macro(0)
	, Toggle(0)
	, OnRelease()
	, Start()
	, Stop()
	, MouseAction()
	, Mouse()
	, Grid()
{
	for (int i = 0; i < 5; i++) { dsID[i] = dsButtonID::none; }
	for (int i = 0; i < 13; i++) { vjID[i] = vJoyButtonID::none; }
	for (int i = 0; i < 5; i++) { Target[i] = false; }
	for (int i = 0; i < 13; i++) { Disbale[i] = 0; }
	for (int i = 0; i < 4; i++) { OrXorNot[i] = 0; }
	for (int i = 0; i < 4; i++) { MouseAction[i] = 0; }
	for (int i = 0; i < 8; i++) { OnRelease[i] = 0; }
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
	bool firstplus = false;
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	for (int i = 0; i < 5; i++)
	{
		if (Target[i])
		{
			if (vjID[i] != 0)
			{
				if (firstplus)
				{
					if (i > 0 && i < 3 && OrXorNot[i - 3] == 1)
						head += wsprintf(head, L"||%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					else if (i > 0 && i < 3 && OrXorNot[i - 3] == 2)
						head += wsprintf(head, L"⊕%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					else if (i > 2 && OrXorNot[i - 1])
						head += wsprintf(head, L"-%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					else
						head += wsprintf(head, L"+%s", vJoyButton::String((vJoyButtonID)vjID[i]));
				}
				else
				{
					if (i > 0 && i < 3 && OrXorNot[i - 3] == 1)
						head += wsprintf(head, L"||%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					else if (i > 0 && i < 3 && OrXorNot[i - 3] == 2)
						head += wsprintf(head, L"⊕%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					else if (i > 2 && OrXorNot[i - 1])
						head += wsprintf(head, L"-%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					else
						head += wsprintf(head, L"%s", vJoyButton::String((vJoyButtonID)vjID[i]));
					firstplus = true;
				}
			}
		}
		else
		{
			if (dsID[i] != 0)
			{
				if (firstplus)
				{
					if (i > 0 && i < 3 && OrXorNot[i - 3] == 1)
						head += wsprintf(head, L"||%s", dsButton::String((dsButtonID)dsID[i]));
					else if (i > 0 && i < 3 && OrXorNot[i - 3] == 2)
						head += wsprintf(head, L"⊕%s", dsButton::String((dsButtonID)dsID[i]));
					else if (i > 2 && OrXorNot[i - 1])
						head += wsprintf(head, L"-%s", dsButton::String((dsButtonID)dsID[i]));
					else
						head += wsprintf(head, L"+%s", dsButton::String((dsButtonID)dsID[i]));
				}
				else
				{
					if (i > 0 && i < 3 && OrXorNot[i - 3] == 1)
						head += wsprintf(head, L"||%s", dsButton::String((dsButtonID)dsID[i]));
					else if (i > 0 && i < 3 && OrXorNot[i - 3] == 2)
						head += wsprintf(head, L"⊕%s", dsButton::String((dsButtonID)dsID[i]));
					else if (i > 2 && OrXorNot[i - 1])
						head += wsprintf(head, L"-%s", dsButton::String((dsButtonID)dsID[i]));
					else
						head += wsprintf(head, L"%s", dsButton::String((dsButtonID)dsID[i]));
					firstplus = true;
				}
			}
		}
	}

	return buf;
}

const WCHAR* Mapping::vJoyString()
{
	bool firstplus = false;
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	for (int i = 5; i < 13; i++)
	{
		if (firstplus)
		{
			if (i < 9 && MouseAction[i - 5])
				head += wsprintf(head, L"+%s", String((MouseActionID)MouseAction[i - 5]));
//				head += wsprintf(head, L"+MA%d", i - 4);
			else if(vjID[i] != 0)
				head += wsprintf(head, L"+%s", vJoyButton::String((vJoyButtonID)vjID[i]));
		}
		else
		{
			if (i < 9 && MouseAction[i - 5])
				{ head += wsprintf(head, L"%s", String((MouseActionID)MouseAction[i - 5])); firstplus = true; }
//				{ head += wsprintf(head, L"MA%d", i - 4); firstplus = true; }
			else if (vjID[i] != 0)
				{ head += wsprintf(head, L"%s", vJoyButton::String((vJoyButtonID)vjID[i])); firstplus = true; }
		}
	}

	if (Led)
		if (firstplus)
		{
			head += wsprintf(head, L"+Led%d", Led);
		}
		else
		{
			head += wsprintf(head, L"Led%d", Led);
			firstplus = true;
		}

	return buf;
}

const WCHAR* Mapping::TagsString()
{
	bool firstplus = false;
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Ifmouse)
		head += wsprintf(head, L"I");
	else
		head += wsprintf(head, L" ");

	if (Force)
		head += wsprintf(head, L"F");
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

	if (Toggle)
		head += wsprintf(head, L"T");
	else
		head += wsprintf(head, L"  ");

	if (OnRelease[0] || OnRelease[1] || OnRelease[2] || OnRelease[3] || OnRelease[4] || OnRelease[5] || OnRelease[6] || OnRelease[7])
		head += wsprintf(head, L"R");
	else
		head += wsprintf(head, L"  ");

	if (Mouse[0] || Mouse[1] || Mouse[2])
		head += wsprintf(head, L"M");
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
	for (int i = 0; i < 4; i++)
		mouse_toggle[i] = false;
	for (int i = 0; i < 6; i++)
		Ledactive[i] = false ;
}

BOOL Mapping::LoadDevice(dsDevice* ds, vJoyDevice* vjoy)
{
	if (!Enable)
		return FALSE;

	m_ds[0] = dsID[0] ? ds->GetButton(dsID[0]) : 0;
	m_ds[1] = dsID[1] ? ds->GetButton(dsID[1]) : 0;
	m_ds[2] = dsID[2] ? ds->GetButton(dsID[2]) : 0;
	m_ds[3] = dsID[3] ? ds->GetButton(dsID[3]) : 0;
	m_ds[4] = dsID[4] ? ds->GetButton(dsID[4]) : 0;
	m_vj[0] = vjID[0] ? vjoy->GetButton(vjID[0]) : 0;
	m_vj[1] = vjID[1] ? vjoy->GetButton(vjID[1]) : 0;
	m_vj[2] = vjID[2] ? vjoy->GetButton(vjID[2]) : 0;
	m_vj[3] = vjID[3] ? vjoy->GetButton(vjID[3]) : 0;
	m_vj[4] = vjID[4] ? vjoy->GetButton(vjID[4]) : 0;
	m_vj[5] = vjID[5] ? vjoy->GetButton(vjID[5]) : 0;
	m_vj[6] = vjID[6] ? vjoy->GetButton(vjID[6]) : 0;
	m_vj[7] = vjID[7] ? vjoy->GetButton(vjID[7]) : 0;
	m_vj[8] = vjID[8] ? vjoy->GetButton(vjID[8]) : 0;
	m_vj[9] = vjID[9] ? vjoy->GetButton(vjID[9]) : 0;
	m_vj[10] = vjID[10] ? vjoy->GetButton(vjID[10]) : 0;
	m_vj[11] = vjID[11] ? vjoy->GetButton(vjID[11]) : 0;
	m_vj[12] = vjID[12] ? vjoy->GetButton(vjID[12]) : 0;

	if (vjID[5]) { vjUsed.push_back(vjID[5]); }
	if (vjID[6]) { vjUsed.push_back(vjID[6]); }
	if (vjID[7]) { vjUsed.push_back(vjID[7]); }
	if (vjID[8]) { vjUsed.push_back(vjID[8]); }
	if (vjID[9]) { vjUsed.push_back(vjID[9]); }
	if (vjID[10]) { vjUsed.push_back(vjID[10]); }
	if (vjID[11]) { vjUsed.push_back(vjID[11]); }
	if (vjID[12]) { vjUsed.push_back(vjID[12]); }

	if (Toggle == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (i < 4 && MouseAction[i])
			{
				if (MouseAction[i] == ACTIVE_MOUSE)
					mouse_toggle[i] = true;
				else
					continue;
			}
			if (m_vj[i + 5])
			{
				m_toggle[vjID[i + 5]] = true;
				m_vj[i + 5]->SetVal(0xFF);
				m_vj[i + 5]->SetPushed();
			}
		}
	}

	GridCanbeUsed =
		MouseAction[0] != MOVE_TO_XY && MouseAction[0] != SAVE_AND_MOVE_TO_XY && MouseAction[0] != MOVE_TO_WH && MouseAction[0] != SAVE_AND_MOVE_TO_WH &&
		MouseAction[1] != MOVE_TO_XY && MouseAction[1] != SAVE_AND_MOVE_TO_XY && MouseAction[1] != MOVE_TO_WH && MouseAction[1] != SAVE_AND_MOVE_TO_WH &&
		MouseAction[2] != MOVE_TO_XY && MouseAction[2] != SAVE_AND_MOVE_TO_XY && MouseAction[2] != MOVE_TO_WH && MouseAction[2] != SAVE_AND_MOVE_TO_WH &&
		MouseAction[3] != MOVE_TO_XY && MouseAction[3] != SAVE_AND_MOVE_TO_XY && MouseAction[3] != MOVE_TO_WH && MouseAction[3] != SAVE_AND_MOVE_TO_WH;

	release = std::chrono::system_clock::now();

	return TRUE;
}

void Mapping::RunFirst()
{
	dsDisabled.clear();
	vjDisabled.clear();
	mouseabolute = 1;
	for (int i = 0; i < 3; i++)
		mousemode[i] = 0;
	for (int i = 0; i < 5; i++)
		grid[i] = 0;
	defaultmouse = 0;
	mouseactivated = FALSE;
}

void Mapping::RunLast(dsDevice* ds, vJoyDevice* vjoy)
{
	vJoyButtonsString[0] = 0;
	WCHAR* head = vJoyButtonsString;

	for (int i = 0; i < vjUsed.size(); i++)
	{
		m_vjUsed = (vJoyButtonID)vjUsed[i];
		if (!vjoy->GetButton(m_vjUsed)->isPushed())
			vjoy->GetButton(m_vjUsed)->Release();
		else
			head += wsprintf(head, L"%s ", vJoyButton::String(m_vjUsed));
	}

	if (tape.ActualDS == 2)
	{
		byte m_Whitetmp = 0x00;

		if (!Ledactive[0] && !Ledactive[1] && !Ledactive[2] && !Ledactive[3] && !Ledactive[4] && Ledactive[5])
		{
			if (battery < 25)
				m_Whitetmp = 0x01;
			else if (battery < 50)
				m_Whitetmp = 0x03;
			else if (battery < 75)
				m_Whitetmp = 0x0b;
			else
				m_Whitetmp = 0x1b;
		}
		else
		{
			if (Ledactive[0])
				m_Whitetmp = 0x01;
			if (Ledactive[1])
				m_Whitetmp = m_Whitetmp | 0x02;
			if (Ledactive[2])
				m_Whitetmp = m_Whitetmp | 0x04;
			if (Ledactive[3])
				m_Whitetmp = m_Whitetmp | 0x08;
			if (Ledactive[4])
				m_Whitetmp = m_Whitetmp | 0x10;
		}

		ds->SetWhiteLED(m_Whitetmp);
	}
}

void Mapping::Run()
{
	if (tape.vJoyPaused)
		return;

	bool legits[5];
	if (Force == 1 || (Force == 2 && isRunning))
		for (int i = 0; i < 5; i++)
		{
			legits[i] =
				(Target[i] && (m_vj[i] == 0 || m_vj[i]->isPushed())) ||
				(!Target[i] && (m_ds[i] == 0 || m_ds[i]->isPushed()));
		}
	else
		for (int i = 0; i < 5; i++)
		{
			legits[i] =
				(Target[i] && (m_vj[i] == 0 || (m_vj[i]->isPushed() && !(std::find(vjDisabled.begin(), vjDisabled.end(), vjID[i]) != vjDisabled.end())))) ||
				(!Target[i] && (m_ds[i] == 0 || (m_ds[i]->isPushed() && !(std::find(dsDisabled.begin(), dsDisabled.end(), dsID[i]) != dsDisabled.end()))));
		}

	legit =
		((Ifmouse && mouseactivated) || !Ifmouse) &&
		((OrXorNot[0] == 2) ? (legits[0] ^ legits[1]) : (OrXorNot[0]) ? (legits[0] || legits[1]) : (legits[0] && legits[1])) &&
		((OrXorNot[1] == 2) ? (legits[0] ^ legits[2]) : (OrXorNot[0]) ? (legits[0] || legits[2]) : (legits[0] && legits[2])) &&
		((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
		((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));

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

		if (legit)
		{
			if (!isFired && !available)
			{
				start = std::chrono::system_clock::now();
				killed = FALSE;
			}
			isFired = TRUE;

			end = std::chrono::system_clock::now();
			switch (method)
			{
			case 1: //Simple
				activated = TRUE;
				break;
			case 3: //Short
				if (available)
					killed = TRUE;
				else
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						killed = TRUE;
				break;
			case 4: //Long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = TRUE;
				if (end - start >= std::chrono::milliseconds(tape.LongPress) && !killed)
					activated = TRUE;
				break;
			case 2: //Double
				if (available)
				{
					if (end - start < std::chrono::milliseconds(tape.LongPress))
					{
						method = 1;
						activated = TRUE;
					}
					else
						killed = TRUE;
				}
				else
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						killed = TRUE;
				break;
			case 5: //Double short
				if (available)
				{
					if (end - start < std::chrono::milliseconds(tape.LongPress))
					{
						start = std::chrono::system_clock::now();
						method = 3;
						available = FALSE;
					}
					else
						killed = TRUE;
				}
				else
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						killed = TRUE;
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
						killed = TRUE;
				}
				else
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						killed = TRUE;
				break;
			case 7: //Medium long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = TRUE;
				if (end - start > std::chrono::milliseconds(tape.LongPress * 2) && !killed)
					activated = TRUE;
				break;
			case 8: //Very long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = TRUE;
				if (end - start > std::chrono::milliseconds(tape.VeryLongPress) && !killed)
					activated = TRUE;
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
					available = TRUE;
					end = std::chrono::system_clock::now();
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						if (!killed)
							activated = TRUE;
						available = FALSE;
					}
				}
				break;
			case 4: //Long
				killed = TRUE;
				break;
			case 2: //Double
			case 5: //Double short
			case 6: //Double long
				if ((isFired && !killed) || available)
				{
					available = TRUE;
					end = std::chrono::system_clock::now();
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						available = FALSE;
				}
				break;
			}
			isFired = FALSE;
		}
	}

	if (activated || isRunning)
	{
		if (activated)
		{
			start2 = std::chrono::system_clock::now();
			cycle = 0;
			activated = FALSE;
			isRunning = TRUE;
			released = FALSE;
			for (int i = 0; i < 8; i++)
			{
				ran[i] = FALSE;
				Toggledone[i] = FALSE;
				randStart[i] = std::chrono::milliseconds(Start[i] + ((Start[i] & 1) ? (rand() % 9) : 0));
				randStop[i] = std::chrono::milliseconds(Stop[i] + ((Stop[i] & 1) ? (rand() % 9) : 0));
			}
			for (int i = 0; i < 4; i++)
				MouseActiondone[i] = FALSE;
		}
		else if (!legit && !released)
		{
			released = TRUE;
			release2 = std::chrono::system_clock::now();
		}

		end2 = std::chrono::system_clock::now();

		if (Led)
			Ledactive[Led - 1] = true;

		if (Target[0] ? (m_vj[0] ? ((m_vj[0]->isPushed()) ? true : false) : false) : (m_ds[0] ? ((m_ds[0]->isPushed()) ? true : false) : false))
			m_data = (BYTE)(Target[0] ? m_vj[0]->GetVal() : m_ds[0]->GetVal());
		else if (OrXorNot[0] && (Target[1] ? (m_vj[1] ? ((m_vj[1]->isPushed()) ? true : false) : false) : (m_ds[1] ? ((m_ds[1]->isPushed()) ? true : false) : false)))
			m_data = (BYTE)(Target[1] ? m_vj[1]->GetVal() : m_ds[1]->GetVal());
		else if (OrXorNot[1] && (Target[2] ? (m_vj[2] ? ((m_vj[2]->isPushed()) ? true : false) : false) : (m_ds[2] ? ((m_ds[2]->isPushed()) ? true : false) : false)))
			m_data = (BYTE)(Target[2] ? m_vj[2]->GetVal() : m_ds[2]->GetVal());
		else
			m_data = (BYTE)((method < 3) ? ((Target[0]) ? (m_vj[0] ? m_vj[0]->GetReleasedVal() : 0xFF) : (m_ds[0] ? m_ds[0]->GetReleasedVal() : 0xFF)) : 0xFF);

		for (int i = 0; i < 8; i++)
		{
			if (Macro == 1 && released && OnRelease[i] != 1)
			{
				started[i] = FALSE;
				done[i] = TRUE;
			}
			else
			{
				started[i] = (OnRelease[i] == 1) ? ((released) ? (end2 - release2 >= randStart[i]) : FALSE) : (end2 - start2 >= randStart[i]);
				done[i] = ran[i] ? ((OnRelease[i]) ? ((released) ? ((end2 - release2 >= randStop[i])) : FALSE) : ((Stop[i]) ? (end2 - start2 >= randStop[i]) : released)) : FALSE;
			}

			if (Macro == 2 && ((OrXorNot[2] == 2 && legits[3]) || (OrXorNot[3] == 2 && legits[4])))
				started[i] = FALSE;

			if (i < 4 && MouseAction[i])
			{
				if (started[i] && !done[i] && (!ran[i] || MouseAction[i] == SCROLL_UP_VARIABLE || MouseAction[i] == SCROLL_DOWN_VARIABLE))
				{
					ran[i] = TRUE;
					switch (MouseAction[i])
					{
					case ACTIVE_MOUSE:
						if (Toggle)
						{
							if (!Toggledone[0])
							{
								Toggledone[0] = TRUE;
								mouse_toggle[i] = !mouse_toggle[i];
							}
						}
						break;
					case SCROLL_UP_VARIABLE:
					case SCROLL_DOWN_VARIABLE:
					{
						int modulo = Target[0] ? (m_vj[0] ? m_vj[0]->GetScrollVal() : 10) : (m_ds[0] ? m_ds[0]->GetScrollVal() : 10);
						if (modulo)
							if (!(cycle % modulo))
							{
								double delta = cycle;
								delta = delta * delta / 600;
								std::thread (MouseActions, MouseAction[i], min(600, delta), 0, 0).detach();
							}
						break;
					}
					case MOVE_TO_XY:
					case SAVE_AND_MOVE_TO_XY:
						std::thread(MouseActions, MouseAction[i], 0, Grid[0], Grid[1]).detach();
						break;
					case MOVE_TO_WH:
					case SAVE_AND_MOVE_TO_WH:
						std::thread(MouseActions, MouseAction[i], 0, Grid[2], Grid[3]).detach();
						break;
					default:
						std::thread(MouseActions, MouseAction[i], 0, 0, 0).detach();
						break;
					}
				}
			}
			else
			{
				if (started[i] && !done[i])
				{
					ran[i] = true;
					if (m_vj[i + 5])
					{
						if (Toggle)
						{
							if (!Toggledone[i])
							{
								Toggledone[i] = true;
								m_toggle[vjID[i + 5]] = !m_toggle[vjID[i + 5]];
							}
						}
						else
						{
							m_vj[i + 5]->SetVal(m_data);
							m_vj[i + 5]->SetPushed();
						}
					}
				}
			}
		}

		if (MouseAction[0] && done[0] && !MouseActiondone[0])
		{
			MouseActiondone[0] = true;
			std::thread (MouseActionEnd, MouseAction[0]).detach();
		}
		if (MouseAction[1] && done[1] && !MouseActiondone[1])
		{
			MouseActiondone[1] = true;
			std::thread (MouseActionEnd, MouseAction[1]).detach();
		}
		if (MouseAction[2] && done[2] && !MouseActiondone[2])
		{
			MouseActiondone[2] = true;
			std::thread (MouseActionEnd, MouseAction[2]).detach();
		}
		if (MouseAction[3] && done[3] && !MouseActiondone[3])
		{
			MouseActiondone[3] = true;
			std::thread (MouseActionEnd, MouseAction[3]).detach();
		}

		if (done[0] && done[1] && done[2] && done[3] && done[4] && done[5] && done[6] && done[7])
		{
			method = 0;
			isRunning = false;

			if (Led)
				Ledactive[Led - 1] = false;
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (Disbale[i])
					if (Target[i])
					{
						if (m_vj[i])
							vjDisabled.push_back(vjID[i]);
					}
					else
					{
						if (m_ds[i])
							dsDisabled.push_back(dsID[i]);
					}
			}
			for (int i = 5; i < 13; i++)
			{
				if (Disbale[i] == 1 && started[i - 5] && !done[i - 5])
				{
					if (m_vj[i])
						vjDisabled.push_back(vjID[i]);
				}
				else if (Disbale[i] == 2)
				{
					if (m_vj[i])
						vjDisabled.push_back(vjID[i]);
				}
			}
		}

	}

	if (Toggle)
	{
		for (int i = 0; i < 8; i++)
		{
			if (i < 4 && MouseAction[i])
				continue;
			if (m_toggle[vjID[i + 5]])
			{
				m_vj[i + 5]->SetVal((m_data) ? m_data : ((done[i]) ? 0xFF : 0));
				m_vj[i + 5]->SetPushed();
			}
		}
	}

	if (((!Toggle && MouseAction[0] == 1 && started[0] && !done[0]) || (Toggle && mouse_toggle[0])) ||
		((!Toggle && MouseAction[1] == 1 && started[1] && !done[1]) || (Toggle && mouse_toggle[1])) ||
		((!Toggle && MouseAction[2] == 1 && started[2] && !done[2]) || (Toggle && mouse_toggle[2])) ||
		((!Toggle && MouseAction[3] == 1 && started[3] && !done[3]) || (Toggle && mouse_toggle[3])))
	{
		for (int i = 0; i < 3; i++)
			if (Mouse[i])
			{
				if (!Mouse[i + 3])
				{
					mouseactivated = TRUE;
					mousemode[i] = Mouse[i];
					if (mousemode[i] == 1)
						mouseabolute = i;
				}
				else if (mousemode[i] == Mouse[i])
				{
					mousemode[i] = 0;
					if (!mousemode[((i + 1) % 3)] && !mousemode[((i + 2) % 3)])
						mouseactivated = FALSE;
				}
			}

		if (GridCanbeUsed && ((Mouse[0] == 5 && !Mouse[3]) || (Mouse[1] == 5 && !Mouse[4]) || (Mouse[2] == 5 && !Mouse[5])))
			for (int i = 0; i < 6; i++)
				grid[i] = Grid[i];

		defaultmouse = (Mouse[6]) ? ((Mouse[6] == 1) ? true : false) : defaultmouse;
	}

	cycle = (cycle == 2147483639) ? 0 : cycle + 1;
}

WCHAR* Mapping::String(MouseActionID id)
{
	switch (id)
	{
	case none: return L"";
	case ACTIVE_MOUSE: return I18N.MouseAction_ACTIVE_MOUSE;
	case SAVE_POSITION: return I18N.MouseAction_SAVE_POSITION;
	case MOVE_TO_XY: return I18N.MouseAction_MOVE_TO_XY;
	case SAVE_AND_MOVE_TO_XY: return I18N.MouseAction_SAVE_AND_MOVE_TO_XY;
	case MOVE_TO_WH: return I18N.MouseAction_MOVE_TO_WH;
	case SAVE_AND_MOVE_TO_WH: return I18N.MouseAction_SAVE_AND_MOVE_TO_WH;
	case MOVE_BACK: return I18N.MouseAction_MOVE_BACK;
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
	default: return L"???";
	}
}

void MouseActions(int action, int delta, int x, int y)
{
	switch (action)
	{
	case MouseActionID::SAVE_POSITION:
	{
		GetCursorPos(&movebackpoint);
		break;
	}
	case MouseActionID::MOVE_BACK:
	{
		SetCursorPos(movebackpoint.x, movebackpoint.y);
		break;
	}
	case MouseActionID::MOVE_TO_XY:
	case MouseActionID::MOVE_TO_WH:
	{
		SetCursorPos(x, y);
		break;
	}
	case MouseActionID::SAVE_AND_MOVE_TO_XY:
	case MouseActionID::SAVE_AND_MOVE_TO_WH:
{
		GetCursorPos(&movebackpoint);
		SetCursorPos(x, y);
		break;
	}
	case MouseActionID::LEFT_CLICK:
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
	case MouseActionID::MIDDLE_CLICK:
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
	case MouseActionID::RIGHT_CLICK:
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
	case MouseActionID::X1_CLICK:
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
	case MouseActionID::X2_CLICK:
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
	case MouseActionID::SCROLL_UP:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = 120;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case MouseActionID::SCROLL_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = -120;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case MouseActionID::LEFT_DOUBLE_CLICK:
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
	case MouseActionID::MIDDLE_DOUBLE_CLICK:
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
	case MouseActionID::RIGHT_DOUBLE_CLICK:
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
	case MouseActionID::X1_DOUBLE_CLICK:
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
	case MouseActionID::X2_DOUBLE_CLICK:
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
	case MouseActionID::SCROLL_UP_x5:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = 600;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case MouseActionID::SCROLL_DOWN_x5:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = -600;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case MouseActionID::LEFT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::MIDDLE_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::RIGHT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::X1_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XDOWN;
		input.mi.mouseData = XBUTTON1;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::X2_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XDOWN;
		input.mi.mouseData = XBUTTON2;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::SCROLL_UP_VARIABLE:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		input.mi.mouseData = delta;
		SendInput(1, &input, sizeof(input));
		break;
	}
	case MouseActionID::SCROLL_DOWN_VARIABLE:
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
	case MouseActionID::LEFT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::MIDDLE_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::RIGHT_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::X1_DOWN:
	{
		INPUT input = { 0 };
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_XUP;
		input.mi.mouseData = XBUTTON1;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case MouseActionID::X2_DOWN:
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
