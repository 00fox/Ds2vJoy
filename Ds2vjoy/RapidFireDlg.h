#pragma once

class RapidFireDlg
{
public:
	RapidFireDlg();
	~RapidFireDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void addRapidFireDlgBack();
	void editRapidFireDlgBack(int idx);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void redrawMenu(int ntabs);
	void load();
	void save();
	void addRapidFireDlg();
	void editRapidFireDlg();
	void deleteRapidFireDlg();
	void duplicateRapidFireDlg();
	int insertRapidFire(int idx, RapidFire* af);
	void BeginDrag(int idx);
	void DragMove(int x, int y);
	void EndDrag(int x, int y);
	void setInsertMark(int idx);

	HWND m_hWnd;
	HWND m_hDlg;
	HWND m_hList;
	HMENU m_hMenu;

	int m_TabsID[4];
	bool m_active;
	bool m_flag_drag;
	int m_insrtpos;
};

extern RapidFireDlg rDlg;
