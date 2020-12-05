#pragma once
#include "Mapping.h"

class MappingDlg
{
	HWND m_hWnd;
	HWND m_hList;
	HWND m_hDlg;
	HMENU m_hMenu;
	bool m_dragflag;
	int m_insrtpos;

	bool m_active;
	bool m_change;
	void load();
	void save();
	void BeginDrag(int idx);
	void DragMove(int,int);
	void EndDrag(int,int);
	int insertMappingData(int, Mapping*);
	void setInsertMark(int);

	void deleteMappingData();
	void addMappingDataDlg();
	void editMappingDataDlg();
	INT_PTR CALLBACK _proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

public:
	MappingDlg();
	~MappingDlg();

	void Init(HINSTANCE, HWND);
	static INT_PTR CALLBACK Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);
	
};

