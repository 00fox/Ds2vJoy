﻿#pragma once

class SettingDlg
{
public:
	SettingDlg();
	~SettingDlg();

	void				Init();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hDlg = NULL;

	unsigned char		m_device = 0;
	CHOOSECOLOR			cc = { 0 };
	COLORREF			color = 0;
	COLORREF			CustColors[16] = { 0 };
};

	extern	SettingDlg				sDlg;