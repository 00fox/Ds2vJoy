#pragma once

class ViGEmDlg
{
public:
	ViGEmDlg();
	~ViGEmDlg();

	void Init(HINSTANCE, HWND);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	#define WM_CHANGE_COMBO_BOX WM_USER + 1

	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_hDlg;
};

extern ViGEmDlg vDlg;
