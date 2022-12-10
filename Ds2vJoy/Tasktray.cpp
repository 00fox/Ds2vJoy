#include "stdafx.h"
#include "Tasktray.h"

Tasktray::Tasktray()
{
}

Tasktray::~Tasktray()
{
	DestroyMenu(m_menu);
}

void Tasktray::Init()
{
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = tape.Ds2hWnd;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_TASKTRAY;
	m_nid.hIcon = LoadIcon(tape.Ds2hInst, MAKEINTRESOURCE(IDI_DS2VJOY_ICON32));
	swprintf_s(m_nid.szTip, 128, I18N.APP_TITLE);
	CreateMenu();
}

void Tasktray::CreateMenu()
{
	DestroyMenu(m_menu);
	MenuOffset = 3;
	m_menu = CreatePopupMenu();
	{
		if (tape.Profile != 1)
			AppendMenu(m_menu, MF_POPUP, IDM_PROFILE1, I18N.Profile_1);
		if (tape.Profile != 2)
			AppendMenu(m_menu, MF_POPUP, IDM_PROFILE2, I18N.Profile_2);
		if (tape.Profile != 3)
			AppendMenu(m_menu, MF_POPUP, IDM_PROFILE3, I18N.Profile_3);
		AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
	}
	if (tape.App0Name != nullptr && *tape.App0Name != '\0')
	{
		AppendMenu(m_menu, MF_POPUP, IDM_APP0, tape.App0Name);
		MenuOffset++;
	}
	if (tape.App1Name != nullptr && *tape.App1Name != '\0')
	{
		AppendMenu(m_menu, MF_POPUP, IDM_APP1, tape.App1Name);
		MenuOffset++;
	}
	if (tape.App2Name != nullptr && *tape.App2Name != '\0')
	{
		AppendMenu(m_menu, MF_POPUP, IDM_APP2, tape.App2Name);
		MenuOffset++;
	}
	if (tape.App3Name != nullptr && *tape.App3Name != '\0')
	{
		AppendMenu(m_menu, MF_POPUP, IDM_APP3, tape.App3Name);
		MenuOffset++;
	}
	if (tape.App4Name != nullptr && *tape.App4Name != '\0')
	{
		AppendMenu(m_menu, MF_POPUP, IDM_APP4, tape.App4Name);
		MenuOffset++;
	}
	if (MenuOffset)
	{
		AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
		MenuOffset++;
	}
	AppendMenu(m_menu, MF_GRAYED, IDM_MAPPING, _T("Mapping"));
	AppendMenu(m_menu, MF_GRAYED, IDM_RAPIDFIRE, _T("RapidFire"));
	AppendMenu(m_menu, MF_GRAYED, IDM_VJOY, _T("vJoy"));
	AppendMenu(m_menu, MF_GRAYED, IDM_XOUTPUT, _T("Output"));
	AppendMenu(m_menu, MF_GRAYED, IDM_KEYMAP, _T("Keymap"));
	AppendMenu(m_menu, MF_GRAYED, IDM_GUARDIAN, _T("Guardian"));
	for (int i = 0; i < 6; i++) { SwapMenuitem(i); };
	AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(m_menu, MF_POPUP, IDM_MENU_IMPORT, I18N.IMPORT);
	AppendMenu(m_menu, MF_POPUP, IDM_MENU_EXPORT, I18N.EXPORT);
	AppendMenu(m_menu, MF_POPUP, IDM_MENU_ABOUT, I18N.ABOUT);
	AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(m_menu, MF_POPUP, IDM_MENU_EXIT, I18N.EXIT);
//	DeleteMenu(m_menu, 1, MF_BYPOSITION);
//	InsertMenu(m_menu, 1, MF_BYPOSITION | MF_SEPARATOR, NULL, NULL);
//	AppendMenu(m_menu, MF_POPUP, IDM_EXIT, _T("Exit"));
}

void Tasktray::SwapMenuitem(int item)
{
	switch (item)
	{
	case TasktrayItem_MappingPaused:
	{
		if (tape.MappingPaused)
			ModifyMenu(m_menu, MenuOffset, MF_BYPOSITION | MF_POPUP, IDM_MAPPING, I18N.MappingPaused_Off);
		else
			ModifyMenu(m_menu, MenuOffset, MF_BYPOSITION | MF_POPUP, IDM_MAPPING, I18N.MappingPaused_On);
		break;
	}
	case TasktrayItem_RapidFirePaused:
	{
		if (tape.RapidFirePaused)
			ModifyMenu(m_menu, MenuOffset + 1, MF_BYPOSITION | MF_POPUP, IDM_RAPIDFIRE, I18N.RapidFirePaused_Off);
		else
			ModifyMenu(m_menu, MenuOffset + 1, MF_BYPOSITION | MF_POPUP, IDM_RAPIDFIRE, I18N.RapidFirePaused_On);
		break;
	}
	case TasktrayItem_vJoyPaused:
	{
		if (tape.vJoyPaused)
			ModifyMenu(m_menu, MenuOffset + 2, MF_BYPOSITION | MF_POPUP, IDM_VJOY, I18N.vJoyPaused_Off);
		else
			ModifyMenu(m_menu, MenuOffset + 2, MF_BYPOSITION | MF_POPUP, IDM_VJOY, I18N.vJoyPaused_On);
		break;
	}
	case TasktrayItem_XOutputPaused:
	{
		if (tape.XOutputPaused)
			ModifyMenu(m_menu, MenuOffset + 3, MF_BYPOSITION | MF_POPUP, IDM_XOUTPUT, I18N.XOutputPaused_Off);
		else
			ModifyMenu(m_menu, MenuOffset + 3, MF_BYPOSITION | MF_POPUP, IDM_XOUTPUT, I18N.XOutputPaused_On);
		break;
	}
	case TasktrayItem_KeymapPaused:
	{
		if (tape.KeymapPaused)
			ModifyMenu(m_menu, MenuOffset + 4, MF_BYPOSITION | MF_POPUP, IDM_KEYMAP, I18N.KeymapPaused_Off);
		else
			ModifyMenu(m_menu, MenuOffset + 4, MF_BYPOSITION | MF_POPUP, IDM_KEYMAP, I18N.KeymapPaused_On);
		break;
	}
	case TasktrayItem_GuardianPaused:
	{
		if (tape.GuardianPaused)
			ModifyMenu(m_menu, MenuOffset + 5, MF_BYPOSITION | MF_POPUP, IDM_GUARDIAN, I18N.GuardianPaused_Off);
		else
			ModifyMenu(m_menu, MenuOffset + 5, MF_BYPOSITION | MF_POPUP, IDM_GUARDIAN, I18N.GuardianPaused_On);
		break;
	}
	}
}

void Tasktray::Show()
{
	if (!m_flag)
		Shell_NotifyIcon(NIM_ADD, &m_nid);
	m_flag = true;
}

void Tasktray::Hide()
{
	if (m_flag)
		Shell_NotifyIcon(NIM_DELETE, &m_nid);
	m_flag = false;

}

void Tasktray::Tip(WCHAR* buf)
{
	if (!m_flag)
		return;
	wcscpy_s(m_nid.szTip, wcslen(buf) + 1, buf);
	Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

void Tasktray::Message(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1)
	{
		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
		{
			ShowWindow(tape.Ds2hWnd, SW_SHOWNORMAL);
			SetForegroundWindow(tape.Ds2hWnd);
			PostMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			SetForegroundWindow(tape.Ds2hWnd);
			struct MenuPosition mp;
			GetMenuPosition(&mp);
			TrackPopupMenu(m_menu, mp.flags, mp.x, mp.y, 0, tape.Ds2hWnd, NULL);
			break;
		}
		}
	}
}

	UINT Tasktray::GetTaskBarLocation()
	{
		RECT rectangle;

		return GetTaskBarLocation(&rectangle);
	}

	UINT Tasktray::GetTaskBarLocation(RECT* rectangle)
	{
		UINT location = ABE_BOTTOM;
		APPBARDATA pData;
		pData.cbSize = sizeof(APPBARDATA);
		pData.hWnd = tape.Ds2hWnd;

		if (SHAppBarMessage(ABM_GETTASKBARPOS, &pData))
		{
			*rectangle = pData.rc;
			return pData.uEdge;
		}

		return location;
	}

	void Tasktray::GetMenuPosition(struct MenuPosition* menuposition)
	{
		POINT p;
		if (!GetCursorPos(&p))
		{
			p.x = GetSystemMetrics(SM_CXSCREEN) / 2;
			p.y = GetSystemMetrics(SM_CYSCREEN) / 2;
		}

		switch (GetTaskBarLocation())
		{
		case ABE_BOTTOM: { *menuposition = { TPM_CENTERALIGN | TPM_BOTTOMALIGN, p.x, p.y - 10 }; break; }
		case ABE_LEFT: { *menuposition = { TPM_LEFTALIGN | TPM_BOTTOMALIGN, p.x + 10, p.y }; break; }
		case ABE_RIGHT: { *menuposition = { TPM_RIGHTALIGN | TPM_BOTTOMALIGN, p.x - 10, p.y }; break; }
		case ABE_TOP: { *menuposition = { TPM_CENTERALIGN | TPM_TOPALIGN, p.x, p.y + 10 }; break; }
		}
	}
