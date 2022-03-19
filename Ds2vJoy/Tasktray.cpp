#include "stdafx.h"
#include "Tasktray.h"

Tasktray::Tasktray()
{
}

Tasktray::~Tasktray()
{
	DestroyMenu(m_menu);
}

void Tasktray::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = hWnd;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_TASKTRAY;
	m_nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DS2VJOY_ICON));
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
			AppendMenu(m_menu, MF_POPUP, IDM_PROFILE1, _T("Profile 1"));
		if (tape.Profile != 2)
			AppendMenu(m_menu, MF_POPUP, IDM_PROFILE2, _T("Profile 2"));
		if (tape.Profile != 3)
			AppendMenu(m_menu, MF_POPUP, IDM_PROFILE3, _T("Profile 3"));
		AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
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
	if (tape.App5Name != nullptr && *tape.App5Name != '\0')
	{
		AppendMenu(m_menu, MF_POPUP, IDM_APP5, tape.App5Name);
		MenuOffset++;
	}
	if (MenuOffset)
	{
		AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
		MenuOffset++;
	}
	AppendMenu(m_menu, MF_GRAYED, IDM_MAPPING, _T("vJoy"));
	AppendMenu(m_menu, MF_GRAYED, IDM_VIGEM, _T("ViGEm"));
	AppendMenu(m_menu, MF_GRAYED, IDM_KEYMAP, _T("Keymap"));
	AppendMenu(m_menu, MF_GRAYED, IDM_RAPIDFIRE, _T("RapidFire"));
	AppendMenu(m_menu, MF_GRAYED, IDM_GUARDIAN, _T("Guardian"));
	for (int i = 0; i < 5; i++) { SwapMenuitem(i); };
	AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(m_menu, MF_POPUP, IDM_MENU_ABOUT, _T("About"));
	AppendMenu(m_menu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(m_menu, MF_POPUP, IDM_MENU_EXIT, _T("Exit"));
//	DeleteMenu(m_menu, 1, MF_BYPOSITION);
//	InsertMenu(m_menu, 1, MF_BYPOSITION | MF_SEPARATOR, NULL, NULL);
//	AppendMenu(m_menu, MF_POPUP, IDM_EXIT, _T("Exit"));
}

void Tasktray::SwapMenuitem(int item)
{
	switch (item)
	{
	case 0:
	{
		if (tape.vJoyPaused)
			ModifyMenu(m_menu, MenuOffset + 4, MF_BYPOSITION | MF_POPUP, IDM_MAPPING, _T("Start vJoy"));
		else
			ModifyMenu(m_menu, MenuOffset + 4, MF_BYPOSITION | MF_POPUP, IDM_MAPPING, _T("Pause vJoy"));
		break;
	}
	case 1:
	{
		if (tape.ViGEmPaused)
			ModifyMenu(m_menu, MenuOffset + 1, MF_BYPOSITION | MF_POPUP, IDM_VIGEM, _T("Start ViGEm"));
		else
			ModifyMenu(m_menu, MenuOffset + 1, MF_BYPOSITION | MF_POPUP, IDM_VIGEM, _T("Pause ViGEm"));
		break;
	}
	case 2:
	{
		if (tape.KeymapPaused)
			ModifyMenu(m_menu, MenuOffset + 2, MF_BYPOSITION | MF_POPUP, IDM_KEYMAP, _T("Start Keymap"));
		else
			ModifyMenu(m_menu, MenuOffset + 2, MF_BYPOSITION | MF_POPUP, IDM_KEYMAP, _T("Pause Keymap"));
		break;
	}
	case 3:
	{
		if (tape.RapidFirePaused)
			ModifyMenu(m_menu, MenuOffset + 3, MF_BYPOSITION | MF_POPUP, IDM_RAPIDFIRE, _T("Start RapidFire"));
		else
			ModifyMenu(m_menu, MenuOffset + 3, MF_BYPOSITION | MF_POPUP, IDM_RAPIDFIRE, _T("Pause RapidFire"));
		break;
	}
	case 4:
	{
		if (tape.GuardianPaused)
			ModifyMenu(m_menu, MenuOffset, MF_BYPOSITION | MF_POPUP, IDM_GUARDIAN, _T("Start Guardian"));
		else
			ModifyMenu(m_menu, MenuOffset, MF_BYPOSITION | MF_POPUP, IDM_GUARDIAN, _T("Pause Guardian"));
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
			ShowWindow(m_hWnd, SW_SHOWNORMAL);
			SetForegroundWindow(m_hWnd);
			PostMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			SetForegroundWindow(m_hWnd);
			struct MenuPosition mp;
			GetMenuPosition(&mp);
			TrackPopupMenu(m_menu, mp.flags, mp.x, mp.y, 0, m_hWnd, NULL);
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
		pData.hWnd = m_hWnd;

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
