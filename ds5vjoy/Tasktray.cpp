#include "stdafx.h"
#include "ds5vjoy.h"
#include "Tasktray.h"
Tasktray::Tasktray()
	:m_flag(0)
{
}

void Tasktray::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = hWnd;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_TASKTRAY;
	m_nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DS5VJOY));
	wsprintf(m_nid.szTip,L"DS5vJoy");
}


void Tasktray::Show()
{
	if(!m_flag)
		Shell_NotifyIcon(NIM_ADD, &m_nid);
	m_flag = true;
}

void Tasktray::Hide()
{
	if(m_flag)
		Shell_NotifyIcon(NIM_DELETE, &m_nid);
	m_flag = false;

}

void Tasktray::Tip(WCHAR * buf)
{
	if (!m_flag)
		return;
	lstrcpyW(m_nid.szTip, buf);
	Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

void Tasktray::Message(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1 && lParam == WM_LBUTTONDBLCLK) {
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		SetForegroundWindow(m_hWnd);
	}
}

Tasktray::~Tasktray()
{
}
