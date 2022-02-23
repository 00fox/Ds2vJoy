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

	void				Init(HINSTANCE hInst, HWND hWnd);
	void				Open(HWND parent, int mode);
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

	HWND				m_hDlg = NULL;
	int					m_mode = 0;

	RapidFire			rapidFireData;
	bool				Modified[Mofified_count] = { false };

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hWnd = NULL;
	HWND				m_parent = NULL;

	bool				canprint = false;
};

	extern RapidFireDataDlg rDDlg;