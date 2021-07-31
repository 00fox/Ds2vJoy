#pragma once

class SettingDlg
{
public:
	SettingDlg();
	~SettingDlg();

	void Init(HINSTANCE, HWND);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_hDlg;

	CHOOSECOLOR cc = { 0 };
	COLORREF color = 0, CustColors[16];
};

extern SettingDlg sDlg;
