#pragma once

class DInputDlg
{
public:
	DInputDlg();
	~DInputDlg();

	void				Init();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hDlg	= NULL;
	HWND				m_h1	= NULL;
	HWND				m_hP1	= NULL;
	HWND				m_hP2	= NULL;
	HWND				m_hP3	= NULL;
	HWND				m_hP4	= NULL;
	HWND				m_h6	= NULL;
	HWND				m_h7	= NULL;
	HWND				m_h8	= NULL;
	HWND				m_h9	= NULL;
	HWND				m_h10	= NULL;
	HWND				m_h11	= NULL;
	HWND				m_h12	= NULL;
	HWND				m_h13	= NULL;
	HWND				m_h14	= NULL;
	HWND				m_h15	= NULL;
	HWND				m_h16	= NULL;
	HWND				m_h17	= NULL;
	HWND				m_h18	= NULL;
	HWND				m_h19	= NULL;
	HWND				m_h20	= NULL;
	HWND				m_h21	= NULL;
	HWND				m_h22	= NULL;
	HWND				m_h23	= NULL;
	HWND				m_h24	= NULL;
	HWND				m_h25	= NULL;
	HWND				m_h26	= NULL;
	HWND				m_h27	= NULL;
	HWND				m_h28	= NULL;
	HWND				m_h29	= NULL;
	HWND				m_h30	= NULL;
	HWND				m_h31	= NULL;
	HWND				m_h32	= NULL;
	HWND				m_hL1	= NULL;
	HWND				m_hR1	= NULL;
	HWND				m_hL2	= NULL;
	HWND				m_hR2	= NULL;
	HWND				m_hLT	= NULL;
	HWND				m_hRT	= NULL;
	HWND				m_hLX	= NULL;
	HWND				m_hLY	= NULL;
	HWND				m_hRX	= NULL;
	HWND				m_hRY	= NULL;
	HWND				m_hS0	= NULL;
	HWND				m_hS1	= NULL;
};

	extern DInputDlg	dDlg;
