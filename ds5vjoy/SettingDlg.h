#pragma once
class SettingDlg
{
	HWND m_hWnd;
	HWND m_hDlg;
	bool m_changeflag;
	INT_PTR CALLBACK _proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
public:
	SettingDlg();
	void Init(HINSTANCE ,HWND );
	static INT_PTR CALLBACK Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);
	~SettingDlg();
};

