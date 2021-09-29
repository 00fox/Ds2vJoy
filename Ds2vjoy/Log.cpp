#include "stdafx.h"
#include "Log.h"
#include "Ds2vJoy.h"

LogDlg::LogDlg()
	:m_hWnd(0)
	, m_hDlg(0)
	, queue({ 0 })
	, m_mutex()
	, m_loadvJoy(false)
	, m_count(0)
{
}

LogDlg::~LogDlg()
{
}

void echo() { echo(""); }

void echo(const char* format, ...)
{
	va_list args;
	int len;
	char* buffer;
	va_start(args, format);

	len = _vscprintf_p(format, args) + 1;
	buffer = (char*)malloc(len * sizeof(char));
	if (buffer)
		_vsprintf_p(buffer, len, format, args);

	va_end(args);

	if (buffer)
	{
		const size_t count = strlen(buffer) + 1;
		wchar_t* wcstr = new wchar_t[count];
		size_t* pReturnValue = { 0 };
		mbstowcs_s(pReturnValue, wcstr, (size_t)(count / sizeof(buffer[0])), buffer, count);
		_log.echo(wcstr);
	}
}

void echo(const wchar_t* format, ...)
{
	va_list args;
	int len;
	wchar_t* buffer;
	va_start(args, format);

	len = _vscwprintf_p(format, args) + 1;
	buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
	if (buffer)
	{
		_vswprintf_p(buffer, len, format, args);
		va_end(args);
		_log.echo(buffer);
	}
}

void LogDlg::echo(wchar_t* buffer)
{
	if (m_hWnd)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			queue.push_back(buffer);
		}
		PostMessage(m_hWnd, WM_LOGNEW, 0, 0);
	}
}

void LogDlg::Init(HINSTANCE hInst, HWND hWnd, bool loadvJoy)
{
	m_loadvJoy = loadvJoy;
	if (loadvJoy)
		m_hDlg = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, DS_FIXEDSYS | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL /*| ES_READONLY*/, 0, 0, 0, 0, hWnd, (HMENU)ID_LOGEDITWINDOW, hInst, NULL);
	else
		m_hDlg = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL /*| ES_READONLY*/, 0, 0, 0, 0, hWnd, (HMENU)ID_LOGEDITWINDOW, hInst, NULL);
	m_hWnd = hWnd;
	tape.LoghWnd = m_hDlg;
}

wchar_t* LogDlg::LogGet()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (queue.empty())
		return NULL;

	wchar_t* ret = queue.front();
	queue.pop_front();
	return ret;
}

void LogDlg::Update()
{
	if (m_hDlg == 0)
		return;
	wchar_t* logcnt = LogGet();
	if (logcnt == NULL)
		return;

	if (m_count > 100)
	{
		int target = m_count - 80;
		int targetByte = (int)SendMessage(m_hDlg, EM_LINEINDEX, target, 0);
		SendMessage(m_hDlg, EM_SETSEL, (WPARAM)0, (LPARAM)targetByte);
		SendMessage(m_hDlg, EM_REPLACESEL, 0, 0);
		m_count = 80;
	}
	int ndx = GetWindowTextLength(m_hDlg);
	SendMessage(m_hDlg, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);

	SYSTEMTIME st;
	GetLocalTime(&st);
	WCHAR date[10];

	if (m_loadvJoy)
		wsprintf(date, L"%02d:%02d:%02d ", st.wHour, st.wMinute, st.wSecond);

	while (logcnt != NULL)
	{
		SendMessage(m_hDlg, EM_REPLACESEL, 0, (LPARAM)date);
		SendMessage(m_hDlg, EM_REPLACESEL, 0, (LPARAM)logcnt);
		SendMessage(m_hDlg, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
		free(logcnt);
		m_count++;
		logcnt = LogGet();
	}
}

void LogDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void LogDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL LogDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
