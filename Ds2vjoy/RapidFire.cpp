#include "stdafx.h"
#include "RapidFire.h"

RapidFire::RapidFire()
	:Enable(0)
	, ButtonID(vJoyButtonID::none)
	, ButtonID2(vJoyButtonID::none)
	, Firsttime(75)
	, Releasetime(75)
	, Presstime(150)
	, m_button(0)
	, m_button2(0)
	, m_time(0)
	, randPresstime(0)
	, randReleasetime(0)
{
}

RapidFire::~RapidFire()
{
}

WCHAR* RapidFire::KeyString()
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒▒▒";

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (ButtonID != 0)
	{
		head += wsprintf(head, L"%s", vJoyButton::String((vJoyButtonID)ButtonID));
		if (ButtonID2 != 0)
			head += wsprintf(head, L"+%s", vJoyButton::String((vJoyButtonID)ButtonID2));
	}
	else if (ButtonID2 != 0)
		head += wsprintf(head, L"%s", vJoyButton::String((vJoyButtonID)ButtonID2));

	return buf;
}

WCHAR* RapidFire::ValueString(int column)
{
	if (Enable == 2)
		return L"▒▒▒▒▒▒▒▒▒▒▒▒▒";

	static WCHAR buf[MAX_PATH];
	WCHAR* head = buf;
	switch (column)
	{
	case 1:head += wsprintf(buf, I18N.RapidFire_State1, Firsttime); break;
	case 2:head += wsprintf(buf, I18N.RapidFire_State2, Releasetime); break;
	case 3:head += wsprintf(buf, I18N.RapidFire_State3, Presstime); break;
	default: return L"";
	}

	return buf;
}

BOOL RapidFire::LoadDevice(vJoyDevice* vjoy)
{
	if (Enable != 1)
		return FALSE;

	if (!ButtonID && !ButtonID2)
		return FALSE;

	if (ButtonID)
	{
		m_button = vjoy->GetButton((vJoyButtonID)ButtonID);
		if (m_button == 0)
			return FALSE;
	}
	else
		m_button = 0;
	if (ButtonID2)
	{
		m_button2 = vjoy->GetButton((vJoyButtonID)ButtonID2);
		if (m_button2 == 0)
			return FALSE;
	}
	else
		m_button2 = 0;

	randReleasetime = (long long)Releasetime + ((Releasetime & 1) ? (rand() % 19) : 0);
	randPresstime = (long long)Presstime + ((Presstime & 1) ? (rand() % 19) : 0);

	return TRUE;
}

BOOL RapidFire::Run(double now)
{
	if (tape.RapidFirePaused)
		return FALSE;
	if (((ButtonID != 0) && (ButtonID2 != 0) && (m_button->isPushed()) && (m_button2->isPushed())) ||
		((ButtonID == 0) && (m_button2->isPushed())) ||
		((ButtonID2 == 0) && (m_button->isPushed())))
	{
		if (m_time == 0)
		{
			m_time = (long long)now;
			randReleasetime = (long long)Releasetime + ((Releasetime & 1) ? (rand() % 19) : 0);
		}
		else
		{
			long long time = (long long)(now - m_time - Firsttime);
			if (time > 0)
			{
				time = time % (randReleasetime + randPresstime);
				if (time <= randReleasetime)
				{
					randPresstime = (long long)Presstime + ((Presstime & 1) ? (rand() % 19) : 0);
					if (ButtonID == 0)
						m_button2->Release();
					else
						m_button->Release();
				}
			}
		}
		return TRUE;
	}
	else
		m_time = 0;
	return FALSE;
}
