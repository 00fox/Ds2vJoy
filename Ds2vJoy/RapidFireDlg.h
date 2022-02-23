#pragma once

class RapidFireDlg
{
public:
	RapidFireDlg();
	~RapidFireDlg();

	void				Init(HINSTANCE hInst, HWND hWnd);
	void				addRapidFireDlgBack();
	void				editRapidFireDlgBack();
	void				editRapidFireDlgBackMulti();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);
	void				redrawMenu(int ntabs);
	void				load();
	void				save();
	void				addRapidFireDlg();
	void				addSeparator();
	void				editRapidFireDlg();
	void				deleteRapidFireDlg();
	void				duplicateRapidFireDlg();
	int					insertRapidFire(int idx, RapidFire* rf);
	void				BeginDrag(int idx);
	void				DragMove(int x, int y);
	void				EndDrag(int x, int y);
	void				setInsertMark(int idx);

	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;
	HWND				m_hList = NULL;
	HMENU				m_hMenu = NULL;

	int					m_TabsID[5];
	bool				m_active = false;
	bool				m_flag_drag = false;
	int					m_insrtpos = 0;
	int					lastidx = 0;
	std::vector<int>	lastidxs = { };
	unsigned char		lasttab = 15;
	bool				tabSortingMethod = false;
};

	extern RapidFireDlg rDlg;
