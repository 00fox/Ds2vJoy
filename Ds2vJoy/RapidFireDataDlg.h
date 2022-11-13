#pragma once

class RapidFireDataDlg
{
public:
	enum ModifiedRapidFire : char
	{
		ModifiedRapidFire_ButtonID,
		ModifiedRapidFire_ButtonID2,
		ModifiedRapidFire_Firsttime,
		ModifiedRapidFire_Releasetime,
		ModifiedRapidFire_Presstime,
		ModifiedRapidFire_Count
	};

	RapidFireDataDlg();
	~RapidFireDataDlg();

	void				Init();
	void				Open(HWND parent, int mode);
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

	HWND				m_hDlg = NULL;
	int					m_mode = 0;

	RapidFire			rapidFireData;
	bool				Modified[ModifiedRapidFire_Count] = { false };

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_parent = NULL;

	bool				canprint = false;
};

	extern RapidFireDataDlg rDDlg;