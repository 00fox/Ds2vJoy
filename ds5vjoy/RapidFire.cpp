#include "stdafx.h"
#include "RapidFire.h"
#include "Language.h"

bool RapidFire::LoadDevice(vJoyDevice *vjoy)
{
	if (!ButtonID||!Enable)
		return false;
	m_button = vjoy->GetButton(ButtonID);
	if (m_button == 0)
		return false;
	if (ButtonID2) {
		m_button2 = vjoy->GetButton(ButtonID2);
		if (m_button2 == 0)
			return false;
	}
	else
		m_button2 = 0;
	return true;
}

WCHAR * RapidFire::strKey()
{
	return vJoyButton::String(ButtonID);
}

WCHAR * RapidFire::strVal()
{
	static WCHAR buf[256];
	WCHAR *head=buf;
	head += wsprintf(buf, I18N.Rapidfire_State , Firsttime, Releasetime, Presstime);
	if (ButtonID2)
		wsprintf(head, I18N.Rapidfire_if_down , vJoyButton::String(ButtonID2));
	return buf;
}

bool RapidFire::Run(double now)
{
	if (ButtonID2 != 0 && !m_button2->isPushed())
		return false;
	if (ButtonID == 0 )
		return false;
	if (m_button->isPushed()) {
		if (m_time == 0) {
			m_time = now;
		}
		else {
			long time = (long)(now - m_time - Firsttime);
			if (time > 0) {
				time = time % (Releasetime + Presstime);
				if ((DWORD)time <= Releasetime) {
					m_button->Release();
				}
			}
		}
		return true;
	}
	else {
		m_time = 0;
	}
	return false;
}

RapidFire::RapidFire()
	:Firsttime(200)
	,Releasetime(60)
	,Presstime(60)
	,ButtonID(vJoyButtonID::none)
	,ButtonID2(vJoyButtonID::none)
	,Enable(false)
	,m_time(0)
{
}


RapidFire::~RapidFire()
{
}


