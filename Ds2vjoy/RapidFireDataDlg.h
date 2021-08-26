#pragma once

class RapidFireDataDlg
{
public:
	RapidFireDataDlg();
	~RapidFireDataDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void Open(HWND parent, int idx = 0);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

	RapidFire rapidFireData;

	HWND m_hDlg;
	int m_idx;

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_parent;
};

extern RapidFireDataDlg rDDlg;