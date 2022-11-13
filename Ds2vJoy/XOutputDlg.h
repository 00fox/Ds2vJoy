#pragma once

class XOutputDlg
{
public:
	XOutputDlg();
	~XOutputDlg();


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

	bool				vjoylock = false;
	bool				vigemlock = false;
	bool				statuslock = false;
};

	extern XOutputDlg	xDlg;
