#pragma once

class GuardianDlg
{
public:
	GuardianDlg();
	~GuardianDlg();

	void				Init(HINSTANCE, HWND);
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;

	bool				guardianlock = false;
	bool				cerberuslock = false;
	bool				statuslock = false;
	bool				status2lock = false;
};

	extern GuardianDlg	gDlg;
