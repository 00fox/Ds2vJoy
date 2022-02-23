#include "stdafx.h"
#include "NotepadDlg.h"

NotepadDlg::NotepadDlg()
{
}

NotepadDlg::~NotepadDlg()
{
	if (m_fonthandle != nullptr)
		RemoveFontMemResourceEx(m_fonthandle);
}

void NotepadDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_NOTEPAD), hWnd, (DLGPROC)Proc, LPARAM(this));
	m_hEdit = GetDlgItem(m_hDlg, IDC_NOTEPAD);

	if (LoadEmbeddedFont(IDR_NOTEPAD_TTF, &m_fonthandle))
		tape.hNotepad = CreateFont(16, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"NotepadFont");
	tape.hNotepad = CreateFont(tape.NotepadFontH, tape.NotepadFontW, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, tape.NotepadFont.c_str());
	SendMessage(m_hEdit, WM_SETFONT, WPARAM(tape.hNotepad), TRUE);

	Hide();
}

void NotepadDlg::_InitDialog(HWND hWnd)
{
	SetWindowText(GetDlgItem(hWnd, IDC_NOTEPAD), tape.Notepad.c_str());
}

INT_PTR CALLBACK NotepadDlg::Proc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	NotepadDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<NotepadDlg*>(lparam);
		SetWindowLongPtrW(hWnd, DWLP_USER, lparam);
	}
	else
		dlg = reinterpret_cast<NotepadDlg*>(GetWindowLongPtrW(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wparam, lparam);
		return result;
	}
	return DefWindowProcW(hWnd, message, wparam, lparam);
}

LRESULT CALLBACK NotepadDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		if (m_error)
			SetTextColor(hdcStatic, tape.ink_red);
		else if (tape.DarkTheme)
			SetTextColor(hdcStatic, tape.ink_EDIT_TERMINAL);
		else
			SetTextColor(hdcStatic, tape.ink_EDIT_NOTEPAD);
		SetBkMode(hdcStatic, OPAQUE);
		if (tape.DarkTheme) { SetBkColor((HDC)wParam, tape.ink_black); return (LRESULT)tape.hB_black; }
		else { SetBkColor(hdcStatic, tape.Bk_NOTEPAD); return (LRESULT)tape.hB_white; }
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_white);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_INITDIALOG:
	{
		std::thread(&NotepadDlg::_InitDialog, this, hWnd).detach();
		return TRUE;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			KillTimer(m_hDlg, 1);
			if (tape.NotepadUnsaved)
				std::thread(&NotepadDlg::Save, this).detach();
		}
		break;
	}
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		::MoveWindow(m_hEdit, -1, -1, rect.right + 5, rect.bottom + 2, FALSE);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_NOTEPAD:
		{
			switch (HIWORD(wParam))
			{
			case EN_ERRSPACE:
			case EN_MAXTEXT:
			{
				m_error = true;
				Hide();
				Show();
				break;
			}
			case EN_CHANGE:
			{
				if (!tape.NotepadUnsaved)
				{
					tape.NotepadUnsaved = true;
					SetWindowText(m_hWnd, I18N.NOTEPAD_UNSAVED);
				}
				SetTimer(hWnd, 1, 5000, NULL);
				break;
			}
			break;
			}
		}
		}
		break;
	}
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}

void NotepadDlg::Save()
{
	const int n = 512 * 1024;
	WCHAR* buf = new WCHAR[n];
	GetWindowText(m_hEdit, buf, MAX_PATH);
	tape.Notepad = buf;
	tape.Save(tape.Setting_Notepad);
	SetWindowText(m_hWnd, I18N.APP_TITLE);
}

void NotepadDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void NotepadDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
	if (tape.NotepadUnsaved)
		std::thread(&NotepadDlg::Save, this).detach();
}

BOOL NotepadDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
