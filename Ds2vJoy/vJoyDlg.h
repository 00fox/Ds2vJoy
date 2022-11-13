#pragma once

// HID Descriptor definitions
#define HID_USAGE_X		0x30
#define HID_USAGE_Y		0x31
#define HID_USAGE_Z		0x32
#define HID_USAGE_RX	0x33
#define HID_USAGE_RY	0x34
#define HID_USAGE_RZ	0x35
#define HID_USAGE_SL0	0x36
#define HID_USAGE_SL1	0x37
#define HID_USAGE_WHL	0x38
#define HID_USAGE_POV	0x39

/* These macros are used to build the report by adding a byte/word at a time*/
#ifndef	 NEXT_BYTE
#define NEXT_BYTE(vReport,Data)   vReport.push_back(Data);
#endif

#ifndef	 NEXT_SHORT
#define NEXT_SHORT(vReport,Data)  vReport.push_back(Data&0xFF); vReport.push_back((Data&0xFF00)>>8);
#endif

// Internal messages
#define WM_VJOYCHANGED	WM_USER+1

// Timer ID
#define TIMER_ID 24553

class vJoyDlg
{
public:
	vJoyDlg();
	~vJoyDlg();

	void				Init();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				EnableTab(bool Enable);
	void				GetCtrlState(HWND hDlg, bool* AxisArr, int* nPovCont, int* nPovDisc, int* nButtons, bool* Ffb);
	void				OnSelChanged();
	int					GetFfbState(void);
	void				EnableFfbEffectCB(bool Enable);
	void				ClearFfbEffectCB(void);
	void				UpdateFfbEffectCB(int rID);

	unsigned char       m_device = 0;
	std::vector<CvJoyDevice*> vJoyDevice;
	std::vector<int>	vControls;
	bool				Changed = false;
	bool				AddBtn = false;
	int					FfbState = -1; // 0: Prohibited; 1: Inactive; 2: Active

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hDlg	= NULL;
};

	extern vJoyDlg		vDlg;
