﻿#include "stdafx.h"
#include "RapidFire.h"

RapidFire::RapidFire()
{
}

RapidFire::~RapidFire()
{
}

WCHAR* RapidFire::KeyString()
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (Enable == 2)
		head += swprintf_s(head, MAX_PATH, L"%s", L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");
	else if (ButtonID != 0)
	{
		head += swprintf_s(head, MAX_PATH, L"%s", DestinationButton::String((DestButtonID)ButtonID));
		if (ButtonID2 != 0)
			head += swprintf_s(head, MAX_PATH, L"+%s", DestinationButton::String((DestButtonID)ButtonID2));
	}
	else if (ButtonID2 != 0)
		head += swprintf_s(head, MAX_PATH, L"%s", DestinationButton::String((DestButtonID)ButtonID2));

	return buf;
}

WCHAR* RapidFire::ValueString(int column)
{
	static WCHAR buf[MAX_PATH];
	WCHAR* head = buf;
	if (Enable == 2)
		head += swprintf_s(head, MAX_PATH, L"%s", L"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");
	else
		switch (column)
		{
		case 1: { head += swprintf_s(buf, MAX_PATH, I18N.RapidFire_State1, Firsttime); break; }
		case 2: { head += swprintf_s(buf, MAX_PATH, I18N.RapidFire_State2, Releasetime); break; }
		case 3: { head += swprintf_s(buf, MAX_PATH, I18N.RapidFire_State3, Presstime); break; }
		}

	return buf;
}

const WCHAR* RapidFire::RapidFireButtons()
{
	return RapidFireButtonsString.c_str();
}

BOOL RapidFire::LoadDevice(Destination* srce)
{
	if (Enable != 1)
		return FALSE;

	if (!ButtonID && !ButtonID2)
		return FALSE;

	if (ButtonID)
	{
		m_button = srce->GetButton((DestButtonID)ButtonID);
		if (m_button == 0)
			return FALSE;
	}
	else
		m_button = 0;
	if (ButtonID2)
	{
		m_button2 = srce->GetButton((DestButtonID)ButtonID2);
		if (m_button2 == 0)
			return FALSE;
	}
	else
		m_button2 = 0;

	return TRUE;
}

void RapidFire::RunFirst()
{
	RapidFireButtonsString = I18N.RapidFireButtonsString;
}

BOOL RapidFire::Run(std::chrono::system_clock::time_point now)
{
	if (tape.RapidFirePaused)
		return FALSE;
	if (((ButtonID != 0) && (ButtonID2 != 0) && (m_button->isPushed()) && (m_button2->isPushed())) ||
		((ButtonID == 0) && (m_button2->isPushed())) ||
		((ButtonID2 == 0) && (m_button->isPushed())))
	{
		RapidFireButtonsString = RapidFireButtonsString + L" " + DestinationButton::String(DestButtonID((ButtonID == 0) ? ButtonID2 : ButtonID));
		if (!m_pushed)
		{
			m_pushed = true;
			m_first = false;
			start = now;
		}
		else
		{
			if (m_first)
			{
				if (now - start > std::chrono::milliseconds(randRelease))
				{
					if (now - start > std::chrono::milliseconds(randRelease + randPress))
					{
						start = now;
						randRelease = std::chrono::milliseconds(Releasetime + ((Releasetime & 1) ? (rand() % 19) : 0));
						randPress = std::chrono::milliseconds(Presstime + ((Presstime & 1) ? (rand() % 19) : 0));
					}
				}
				else
				{
					if (ButtonID == 0)
						m_button2->Release();
					else
						m_button->Release();
				}
			}
			else if (now - start > std::chrono::milliseconds(Firsttime))
			{
				start = now;
				m_first = true;
				randRelease = std::chrono::milliseconds(Releasetime + ((Releasetime & 1) ? (rand() % 19) : 0));
				randPress = std::chrono::milliseconds(Presstime + ((Presstime & 1) ? (rand() % 19) : 0));
			}
		}
		return TRUE;
	}
	else
		m_pushed = false;

	return FALSE;
}
