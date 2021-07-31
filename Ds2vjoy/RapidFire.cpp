#include "stdafx.h"
#include "RapidFire.h"

RapidFire::RapidFire()
	:Firsttime(75)
	, Releasetime(75)
	, Presstime(150)
	, ButtonID(vJoyButtonID::none)
	, ButtonID2(vJoyButtonID::none)
	, Enable(false)
	, m_time(0)
	, m_button(0)
	, m_button2(0)
{
}

RapidFire::~RapidFire()
{
}

BOOL RapidFire::LoadDevice(vJoyDevice* vjoy)
{
	if ((!ButtonID && !ButtonID2) || !Enable)
		return FALSE;
	if (ButtonID)
	{
		m_button = vjoy->GetButton(ButtonID);
		if (m_button == 0)
			return FALSE;
	}
	else
		m_button = 0;
	if (ButtonID2)
	{
		m_button2 = vjoy->GetButton(ButtonID2);
		if (m_button2 == 0)
			return FALSE;
	}
	else
		m_button2 = 0;
	return TRUE;
}

WCHAR* RapidFire::KeyString()
{
	static WCHAR buf[256];
	buf[0] = 0;
	WCHAR* head = buf;

	if (ButtonID != 0)
	{
		head += wsprintf(head, L"%s", vJoyButton::String(ButtonID));
		if (ButtonID2 != 0)
			head += wsprintf(head, L"+%s", vJoyButton::String(ButtonID2));
	}
	else if (ButtonID2 != 0)
		head += wsprintf(head, L"%s", vJoyButton::String(ButtonID2));

	return buf;
}

WCHAR* RapidFire::ValueString()
{
	static WCHAR buf[256];
	WCHAR* head = buf;
	head += wsprintf(buf, I18N.RapidFire_State, Firsttime, Releasetime, Presstime);
	return buf;
}

BOOL RapidFire::Run(double now)
{
	if (tape.RapidFirePaused)
		return FALSE;
	if (ButtonID != 0 && !m_button->isPushed())
		return FALSE;
	if (ButtonID2 != 0 && !m_button2->isPushed())
		return FALSE;
	if (((ButtonID != 0) && (ButtonID2 != 0) && (m_button->isPushed()) && (m_button2->isPushed())) ||
		((ButtonID == 0) && (m_button2->isPushed())) ||
		((ButtonID2 == 0) && (m_button->isPushed())))
	{
		if (m_time == 0)
			m_time = now;
		else
		{
			long time = (long)(now - m_time - Firsttime);
			if (time > 0)
			{
				time = time % (Releasetime + Presstime);
				if (time <= Releasetime)
				{
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
