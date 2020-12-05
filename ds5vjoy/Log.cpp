#include "stdafx.h"
#include "Log.h"
#include "ds5vjoy.h"

HWND g_hWnd=0;
std::mutex g_mutex;
std::deque<wchar_t*> g_que;


void LogPrintf(const wchar_t *format, ...){

	va_list args;
	int len;
	wchar_t * buffer;
	va_start(args, format);
	len = _vscwprintf_p(format, args)+ 1;
	buffer = (wchar_t *)malloc(len * sizeof(wchar_t));
	_vswprintf_p(buffer, len, format, args);

	if (g_hWnd) {
		{
			std::lock_guard<std::mutex> lock(g_mutex);
			g_que.push_back(buffer);
		}
		PostMessage(g_hWnd, WM_LOGNEW, 0, 0);
	}
	else {
		free(buffer);
	}
}

wchar_t * LogGet() {
	std::lock_guard<std::mutex> lock(g_mutex);
	if (g_que.empty())
		return NULL;

	wchar_t * ret = g_que.front();
	g_que.pop_front();
	return ret;
}
void LogView(HWND hEdit) {
	wchar_t * log = LogGet();

	if(log==NULL)
		return;
	
	int count = (int)SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);

	if (count > 100) {
		int target = count-100;
		int targetByte = (int)SendMessage(hEdit, EM_LINEINDEX, target, 0);
		SendMessage(hEdit, EM_SETSEL, (WPARAM)0, (LPARAM)targetByte);
		SendMessage(hEdit, EM_REPLACESEL, 0, 0);
	}
	int ndx = GetWindowTextLength(hEdit);
	SendMessage(hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);

	SYSTEMTIME st;
	GetLocalTime(&st);
	WCHAR date[10];
	swprintf_s(date,L"%02d:%02d:%02d ",st.wHour, st.wMinute, st.wSecond);

	while (log != NULL) {
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)date);
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)log);
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
		free(log);
		log = LogGet();
	}
}

LogDlg::LogDlg()
	:m_count(0),m_hEdit(0)
{
}

LogDlg::~LogDlg()
{
}

void LogDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,L"EDIT", NULL,WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL |ES_AUTOVSCROLL | ES_READONLY,0, 0, 0, 0, hWnd, NULL,hInst, NULL);//(HMENU)ID_LOGEDITWINDOW
	g_hWnd = hWnd;
}

void LogDlg::Update()
{
	if (m_hEdit == 0)
		return;
	wchar_t * log = LogGet();
	if (log == NULL)
		return;

	if (m_count > 100) {
		int target = m_count - 80;
		int targetByte = (int)SendMessage(m_hEdit, EM_LINEINDEX, target, 0);
		SendMessage(m_hEdit, EM_SETSEL, (WPARAM)0, (LPARAM)targetByte);
		SendMessage(m_hEdit, EM_REPLACESEL, 0, 0);
		m_count = 80;
	}
	int ndx = GetWindowTextLength(m_hEdit);
	SendMessage(m_hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);

	SYSTEMTIME st;
	GetLocalTime(&st);
	WCHAR date[10];
	wsprintf(date, L"%02d:%02d:%02d ", st.wHour, st.wMinute, st.wSecond);

	while (log != NULL) {
		SendMessage(m_hEdit, EM_REPLACESEL, 0, (LPARAM)date);
		SendMessage(m_hEdit, EM_REPLACESEL, 0, (LPARAM)log);
		SendMessage(m_hEdit, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
		free(log);
		m_count++;
		log = LogGet();
	}

}

void LogDlg::Show()
{
	ShowWindow(m_hEdit, SW_SHOW);
}

void LogDlg::Hide()
{
	ShowWindow(m_hEdit, SW_HIDE);
}

BOOL LogDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hEdit, x, y, w, h, r);
}
