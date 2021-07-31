#pragma once
#include "Mapping.h"

class MappingDlg
{
public:
	MappingDlg();
	~MappingDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void addMappingDlgBack();
	void editMappingDlgBack(int idx);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void load();
	void save();
	void addMappingDlg();
	void editMappingDlg();
	void duplicateMappingDlg();
	void deleteMapping();
	int insertMapping(int idx, Mapping* m);
	void BeginDrag(int idx);
	void DragMove(int x, int y);
	void EndDrag(int x, int y);
	void setInsertMark(int idx);

	HWND m_hWnd;
	HWND m_hDlg;
	HWND m_hList;
	HMENU m_hMenu;

	bool m_active;
	bool m_flag_drag;
	int m_insrtpos;
};

extern MappingDlg mDlg;
