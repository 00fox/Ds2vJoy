#pragma once


class ViGEmDlg
{
public:
	ViGEmDlg();
	~ViGEmDlg();

	void				Init(HINSTANCE, HWND);
	void				Init2();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:

	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_ChangeComboBox(HWND hWnd);
	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HINSTANCE			m_hInst = NULL;
	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;

	bool				m_initdiffered = false;
};

	extern ViGEmDlg		vDlg;
