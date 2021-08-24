#include "stdafx.h"
#include "Mapping.h"
#include "Ds2vJoy.h"

Mapping::Mapping()
	:Enable(false)
	, dsID()
	, vjID()
	, Target()
	, Disable()
	, OrXorNot()
	, Ifmouse(0)
	, Force(0)
	, Led(0)
	, Short(false)
	, Double(false)
	, Long(false)
	, Macro(0)
	, Pause(false)
	, Toggle(0)
	, OnRelease()
	, Start()
	, Stop()
	, MouseAction()
	, Mouse()
	, Grid()
	, Tab(0)
{
	for (int i = 0; i < 5; i++) { dsID[i] = dsButtonID::none; }
	for (int i = 0; i < 13; i++) { vjID[i] = vJoyButtonID::none; }
	for (int i = 0; i < 5; i++) { Target[i] = false; }
	for (int i = 0; i < 13; i++) { Disable[i] = 0; }
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
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	std::wstring str;
	if (Target[0])
	{
		if (vjID[0] != 0)
			str = vJoyButton::String((vJoyButtonID)vjID[0]);
	}
	else
	{
		if (dsID[0] != 0)
			str = dsButton::String((dsButtonID)dsID[0]);
	}

	head += wsprintf(head, L"%s", str.c_str());

	if (Disable[0])
	{
		if (str.length() > 7)
			*(--head) = 0;
		head += wsprintf(head, L"#");
	}

	return buf;
}

const WCHAR* Mapping::dsLastString()
{
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	std::wstring str;
	for (int i = 1; i < 5; i++)
	{
		str = L"";
		if (Target[i])
		{
			if (vjID[i] != 0)
				str = vJoyButton::String((vJoyButtonID)vjID[i]);
			else
				continue;
		}
		else
		{
			if (dsID[i] != 0)
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

		if (Disable[i])
		{
			if (str.length() > 7)
				*(--head) = 0;
			head += wsprintf(head, L"#");
		}
	}

	return buf;
}

const WCHAR* Mapping::dsNotString()
{
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	std::wstring str;
	for (int i = 3; i < 5; i++)
	{
		str = L"";
		if (Target[i])
		{
			if (vjID[i] != 0)
				str = vJoyButton::String((vJoyButtonID)vjID[i]);
			else
				continue;
		}
		else
		{
			if (dsID[i] != 0)
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

		if (Disable[i])
		{
			if (str.length() > 7)
				*(--head) = 0;
			head += wsprintf(head, L"#");
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
				head += wsprintf(head, L" %s", String((MouseActionID)MouseAction[i - 5]));
			else if(vjID[i] != 0)
				head += wsprintf(head, L" %s", vJoyButton::String((vJoyButtonID)vjID[i]));
		}
		else
		{
			if (i < 9 && MouseAction[i - 5])
				{ head += wsprintf(head, L"%s", String((MouseActionID)MouseAction[i - 5])); firstplus = true; }
			else if (vjID[i] != 0)
				{ head += wsprintf(head, L"%s", vJoyButton::String((vJoyButtonID)vjID[i])); firstplus = true; }
		}

		if (Disable[i] == 1)
			head += wsprintf(head, L"#");
		else if (Disable[i])
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

const WCHAR* Mapping::TagsString()
{
	bool firstplus = false;
	static WCHAR buf[256];
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

	if (Pause)
		head += wsprintf(head, L"P");
	else
		head += wsprintf(head, L"  ");

	if (Toggle == 1)
		head += wsprintf(head, L"T");
	else if (Toggle)
		head += wsprintf(head, L"t");
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

	lastmode = 1;
	mode = 1;
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

	for (int i = 5; i < 13; i++)
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

	exists0 = (Target[0]) ? ((m_vj[0]) ? true : false) : ((m_ds[0]) ? true : false);
	exists1 = (Target[1]) ? ((m_vj[1]) ? true : false) : ((m_ds[1]) ? true : false);
	exists2 = (Target[2]) ? ((m_vj[2]) ? true : false) : ((m_ds[2]) ? true : false);

	release0 = (BYTE)((exists0) ? ((Target[0]) ? (m_vj[0] ? m_vj[0]->GetReleasedVal() : 0) : (m_ds[0] ? m_ds[0]->GetReleasedVal() : 0)) : 0);
	OnReleaseValue = (Macro == 2) ? release0 : 0xFF;

	GridCanbeUsed =
		MouseAction[0] != MOVE_TO_XY && MouseAction[0] != SAVE_AND_MOVE_TO_XY && MouseAction[0] != MOVE_TO_WH && MouseAction[0] != SAVE_AND_MOVE_TO_WH &&
		MouseAction[1] != MOVE_TO_XY && MouseAction[1] != SAVE_AND_MOVE_TO_XY && MouseAction[1] != MOVE_TO_WH && MouseAction[1] != SAVE_AND_MOVE_TO_WH &&
		MouseAction[2] != MOVE_TO_XY && MouseAction[2] != SAVE_AND_MOVE_TO_XY && MouseAction[2] != MOVE_TO_WH && MouseAction[2] != SAVE_AND_MOVE_TO_WH &&
		MouseAction[3] != MOVE_TO_XY && MouseAction[3] != SAVE_AND_MOVE_TO_XY && MouseAction[3] != MOVE_TO_WH && MouseAction[3] != SAVE_AND_MOVE_TO_WH;

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
		if (m_toggle[i])
		{
			vjoy->GetButton((vJoyButtonID)i)->SetVal(0xFF);
			vjoy->GetButton((vJoyButtonID)i)->SetPushed();
		}
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

	if (tape.Mode[Tab] != 0 && tape.Mode[Tab] != mode)
		legit = false;
	else if (!OrXorNot[0] && !OrXorNot[1])
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
			((OrXorNot[0] == 2) ? (legits[0] ^ legits[1]) : ((OrXorNot[0]) ? (legits[0] || legits[1]) : (legits[0] && legits[1]))) &&
			legits[2] &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}
	else if (!OrXorNot[0] && OrXorNot[1])
	{
		legit =
			((Ifmouse) ? ((mouseactivated) ? Ifmouse == 1 : Ifmouse == 2) : true) &&
			legits[0] &&
			((OrXorNot[1] == 2) ? (legits[1] ^ legits[2]) : ((OrXorNot[1]) ? (legits[1] || legits[2]) : (legits[1] && legits[2]))) &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}
	else
	{
		legit =
			((Ifmouse) ? ((mouseactivated) ? Ifmouse == 1 : Ifmouse == 2) : true) &&
			((OrXorNot[0] == 2) ? (legits[0] ^ legits[1]) : ((OrXorNot[0]) ? (legits[0] || legits[1]) : (legits[0] && legits[1]))) &&
			((OrXorNot[1] == 2) ? (legits[0] ^ legits[2]) : ((OrXorNot[1]) ? (legits[0] || legits[2]) : (legits[0] && legits[2]))) &&
			((OrXorNot[2] == 2) ? (isRunning || !legits[3]) : !(OrXorNot[2] == (int)legits[3])) &&
			((OrXorNot[3] == 2) ? (isRunning || !legits[4]) : !(OrXorNot[3] == (int)legits[4]));
	}

	pushed0 = (exists0) ? ((Target[0]) ? ((m_vj[0]->isPushed()) ? true : false) : ((m_ds[0]->isPushed()) ? true : false)) : false;
	pushed1 = (exists1) ? ((Target[1]) ? ((m_vj[1]->isPushed()) ? true : false) : ((m_ds[1]->isPushed()) ? true : false)) : false;
	pushed2 = (exists2) ? ((Target[2]) ? ((m_vj[2]->isPushed()) ? true : false) : ((m_ds[2]->isPushed()) ? true : false)) : false;

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

		if (legit && ((secondpass) ? ((secondpass == 1) ? (killed0 || pushed0) : (killed1 && pushed1)) : true))
		{
			if (!isFired && !available)
			{
				start = std::chrono::system_clock::now();
				killed = false;
			}
			else if ((killed) ? ((secondpass) ? false : (OrXorNot[0] && !OrXorNot[1])) : false)
			{
				if (pushed0 && !killed0)
				{
					secondpass = 1;
					start = std::chrono::system_clock::now();
					killed = false;
				}
				else if (pushed1 && !killed1)
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
						if (pushed0) { killed0 = true; }
						if (pushed1) { killed1 = true; }
					}
				break;
			case 4: //Long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start >= std::chrono::milliseconds(tape.LongPress) && !killed)
					activated = true;
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
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed0) { killed0 = true; }
						if (pushed1) { killed1 = true; }
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
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed0) { killed0 = true; }
						if (pushed1) { killed1 = true; }
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
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
					{
						killed = true;
						if (pushed0) { killed0 = true; }
						if (pushed1) { killed1 = true; }
					}
				break;
			case 7: //Medium long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start > std::chrono::milliseconds(tape.LongPress * 2) && !killed)
					activated = true;
				break;
			case 8: //Very long
				if (end - release < std::chrono::milliseconds(tape.LongPress))
					killed = true;
				if (end - start > std::chrono::milliseconds(tape.VeryLongPress) && !killed)
					activated = true;
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
							activated = true;
						available = false;
					}
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
					available = true;
					end = std::chrono::system_clock::now();
					if (end - start >= std::chrono::milliseconds(tape.LongPress))
						available = false;
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
				randStart[i] = std::chrono::milliseconds(Start[i] + ((Start[i] & 1) ? (rand() % 9) : 0));
				randStop[i] = std::chrono::milliseconds(Stop[i] + ((Stop[i] & 1) ? (rand() % 9) : 0));
			}
			for (int i = 0; i < 4; i++)
				MouseActiondone[i] = false;
		}
		else if (!legit && !released)
		{
			released = true;
			release2 = std::chrono::system_clock::now();
		}

		end2 = std::chrono::system_clock::now();

		if (Led)
			Ledactive[Led - 1] = true;

		BYTE value0 = (BYTE)((pushed0) ? ((Target[0]) ? m_vj[0]->GetVal() : m_ds[0]->GetVal()) : 0);
		BYTE value1 = (BYTE)((pushed1) ? ((Target[1]) ? m_vj[1]->GetVal() : m_ds[1]->GetVal()) : 0);
		BYTE value2 = (BYTE)((pushed2) ? ((Target[2]) ? m_vj[2]->GetVal() : m_ds[2]->GetVal()) : 0);

		if (!OrXorNot[0])
			m_data = (exists0) ?
			((pushed0) ? value0 : ((released) ? OnReleaseValue : release0)) :
			((released) ? 0xFF : 0);
		else if (!OrXorNot[1])
			m_data = (exists0) ?
			((pushed0) ? value0 : ((released) ? OnReleaseValue : ((exists1) ? ((pushed1) ? value1 : release0) : release0))) :
			((released) ? 0xFF : ((exists1) ? ((pushed1) ? value1 : 0) : 0));
		else
			m_data = (exists0) ?
			((pushed0) ? value0 : ((released) ? OnReleaseValue : ((exists1) ? ((pushed1) ? value1 : ((exists2) ? ((pushed2) ? value2 : release0) : release0)) : ((exists2) ? ((pushed2) ? value2 : release0) : release0)))) :
			((released) ? 0xFF : ((exists1) ? ((pushed1) ? value1 : ((exists2) ? ((pushed2) ? value2 : 0) : 0)) : ((exists2) ? ((pushed2) ? value2 : 0) : 0)));

		for (int i = 0; i < 8; i++)
		{
			if (Macro == 1 && released && OnRelease[i] != 1)
			{
				started[i] = false;
				done[i] = true;
			}
			else
			{
				started[i] = (OnRelease[i] == 1) ? ((released) ? (end2 - release2 >= randStart[i]) : false) : (end2 - start2 >= randStart[i]);
				done[i] = ran[i] ? ((OnRelease[i]) ? ((released) ? ((end2 - release2 >= randStop[i])) : false) : ((Stop[i]) ? (end2 - start2 >= randStop[i]) : released)) : false;
			}

			if ((OrXorNot[2] && legits[3]) || (OrXorNot[3] && legits[4]))
			{
				if (Pause)
					started[i] = false;
				else if ((OrXorNot[2] == 1 && legits[3]) || (OrXorNot[3] == 1 && legits[4]))
				{
					started[i] = false;
					done[i] = true;
				}
			}

			if (i < 4 && MouseAction[i])
			{
				if (started[i] && !done[i] && (!ran[i] || MouseAction[i] == SCROLL_UP_VARIABLE || MouseAction[i] == SCROLL_DOWN_VARIABLE || MouseAction[i] == VOLUME_UP || MouseAction[i] == VOLUME_DOWN))
				{
					ran[i] = true;
					switch (MouseAction[i])
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
					case SCROLL_UP_VARIABLE:
					case SCROLL_DOWN_VARIABLE:
					{
						int modulo = Target[0] ? (m_vj[0] ? m_vj[0]->GetScrollVal() : -1) : (m_ds[0] ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % 5))
								{
									double delta = cycle;
									delta = delta * delta / 1600;
									std::thread(MouseActions, MouseAction[i], min(240, delta), 0, 0).detach();
								}
							}
							else
							{
								if (!(cycle % 18))
									std::thread(MouseActions, MouseAction[i], 600 - (modulo * 5), 0, 0).detach();
							}
						break;
					}
					case VOLUME_UP:
					case VOLUME_DOWN:
					{
						int modulo = Target[0] ? (m_vj[0] ? m_vj[0]->GetScrollVal() : -1) : (m_ds[0] ? m_ds[0]->GetScrollVal() : -1);
						if (modulo)
							if (modulo == -1)
							{
								if (!(cycle % (int)(2222 / min(450, sqrt(cycle * cycle)))))
									std::thread(MouseActions, MouseAction[i], 0, 0, 0).detach();
							}
							else
							{
								if (!(cycle % modulo))
									std::thread(MouseActions, MouseAction[i], 0, 0, 0).detach();
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
					case MEMORIZE_MODE: { lastmode = mode; break;}
					case TO_MODE1: { mode = 1; break;}
					case TO_MODE2: { mode = 2; break;}
					case TO_MODE3: { mode = 3; break;}
					case TO_MODE4: { mode = 4; break;}
					case TO_MODE5: { mode = 5; break;}
					case TO_MODE6: { mode = 6; break;}
					case TO_MODE7: { mode = 7; break;}
					case TO_MODE8: { mode = 8; break;}
					case TO_LAST_MODE: { mode = lastmode; break;}
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

		for (int i = 0; i < 4; i++)
			if (MouseAction[i] && done[i] && !MouseActiondone[i])
			{
				MouseActiondone[i] = true;
				std::thread(MouseActionEnd, MouseAction[i]).detach();
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
				if (Disable[i])
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
				if (Disable[i] == 1 && started[i - 5] && !done[i - 5])
				{
					if (m_vj[i])
						vjDisabled.push_back(vjID[i]);
				}
				else if (Disable[i] == 2)
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
	case MouseActionID::MUTE_SOUND:
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
	case MouseActionID::VOLUME_UP:
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
	case MouseActionID::VOLUME_DOWN:
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
