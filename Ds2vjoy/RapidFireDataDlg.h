#pragma once

class RapidFireDataDlg
{
public:
	enum ModifiedRapidFire {
		Mofified_ButtonID,
		Mofified_ButtonID2,
		Mofified_Firsttime,
		Mofified_Releasetime,
		Mofified_Presstime,
		Mofified_count
	};

	RapidFireDataDlg();
	~RapidFireDataDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void Open(HWND parent, int mode);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

	RapidFire rapidFireData;
	bool Modified[Mofified_count];

	HWND m_hDlg;
	int m_mode;

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_parent;

	bool canprint;
};

extern RapidFireDataDlg rDDlg;