#include "stdafx.h"
#include "LogDlg.h"

LogDlg::LogDlg()
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
	{
		_vsprintf_p(buffer, len, format, args);
		va_end(args);
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
	queue.push_back(buffer);
	if (m_pause)
		return;

	std::lock_guard<std::mutex> lock(m_mutex);
	Update();
}

void LogDlg::Init(HINSTANCE hInst, HWND hWnd, bool load_dll)
{
	m_hWnd = hWnd;
	m_load_dll = load_dll;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_LOG), hWnd, (DLGPROC)Proc, LPARAM(this));
	m_hEdit = GetDlgItem(m_hDlg, IDC_LOG);
	SendMessage(m_hEdit, WM_SETFONT, WPARAM(tape.hLog), TRUE);
	Show();
}

void LogDlg::_InitDialog(HWND hWnd)
{
}

void LogDlg::ColorDemo(HWND hWnd, HWND hEdit)
{
	CPULimiter limiter = 1; //CPU percents
	_log.m_pause = true;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			if (i > 0 && j > 0)
				continue;

			_log.m_back = i;
			_log.m_ink = (i == 0) ? j : 0;

			std::wstringstream sstream1;
			sstream1 << std::hex << _log.m_back;
			std::wstringstream sstream2;
			sstream2 << std::hex << _log.m_ink;

			std::wstring tosend = L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n                           COLOR " + sstream1.str() + sstream2.str() + L"\r\n";
			Edit_SetSel(hEdit, -1, -1);
			Edit_SetText(hEdit, tosend.c_str());
			Edit_SetSel(hEdit, 0, -1);
			Edit_SetSel(hEdit, -1, -1);
			ShowWindow(hWnd, SW_HIDE);
			ShowWindow(hWnd, SW_SHOW);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	_log.m_back = -1;
	_log.m_ink = -1;
	Edit_SetSel(hEdit, -1, -1);
	Edit_SetText(hEdit, L"OK\r\n");
	Edit_SetSel(hEdit, 0, -1);
	Edit_SetSel(hEdit, -1, -1);
	ShowWindow(hWnd, SW_HIDE);
	ShowWindow(hWnd, SW_SHOW);
	_log.m_pause = false;
	_log.Update();
}

void LogDlg::ColorRand(HWND hWnd, HWND hEdit)
{
	CPULimiter limiter = 1; //CPU percents
	_log.m_pause = true;
	while (_log.m_colorrand)
	{
		_log.m_back = (rand() % 16);
		_log.m_ink = (rand() % 16);

		std::wstringstream sstream1;
		sstream1 << std::hex << _log.m_back;
		std::wstringstream sstream2;
		sstream2 << std::hex << _log.m_ink;

		std::wstring tosend = L"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n                           COLOR " + sstream1.str() + sstream2.str() + L"\r\n";
		Edit_SetSel(hEdit, -1, -1);
		Edit_SetText(hEdit, tosend.c_str());
		Edit_SetSel(hEdit, 0, -1);
		Edit_SetSel(hEdit, -1, -1);
		ShowWindow(hWnd, SW_HIDE);
		ShowWindow(hWnd, SW_SHOW);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	_log.m_back = -1;
	_log.m_ink = -1;
	Edit_SetSel(hEdit, -1, -1);
	Edit_SetText(hEdit, L"OK\r\n");
	Edit_SetSel(hEdit, 0, -1);
	Edit_SetSel(hEdit, -1, -1);
	ShowWindow(hWnd, SW_HIDE);
	ShowWindow(hWnd, SW_SHOW);
	_log.m_pause = false;
	_log.Update();
}

INT_PTR CALLBACK LogDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LogDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<LogDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<LogDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK LogDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLOREDIT:
	{
		SetBkMode((HDC)wParam, OPAQUE);
		switch (m_ink)
		{
		case 0: { SetTextColor((HDC)wParam, tape.ink_black); break; }
		case 1: { SetTextColor((HDC)wParam, tape.ink_red); break; }
		case 2: { SetTextColor((HDC)wParam, tape.ink_orange); break; }
		case 3: { SetTextColor((HDC)wParam, tape.ink_yellow); break; }
		case 4: { SetTextColor((HDC)wParam, tape.ink_emerald); break; }
		case 5: { SetTextColor((HDC)wParam, tape.ink_green); break; }
		case 6: { SetTextColor((HDC)wParam, tape.ink_blue); break; }
		case 7: { SetTextColor((HDC)wParam, tape.ink_purple); break; }
		case 8: { SetTextColor((HDC)wParam, tape.ink_bright_grey); break; }
		case 9: { SetTextColor((HDC)wParam, tape.ink_bright_red); break; }
		case 10: { SetTextColor((HDC)wParam, tape.ink_bright_orange); break; }
		case 11: { SetTextColor((HDC)wParam, tape.ink_bright_yellow); break; }
		case 12: { SetTextColor((HDC)wParam, tape.ink_bright_emerald); break; }
		case 13: { SetTextColor((HDC)wParam, tape.ink_bright_green); break; }
		case 14: { SetTextColor((HDC)wParam, tape.ink_bright_blue); break; }
		case 15: { SetTextColor((HDC)wParam, tape.ink_bright_purple); break; }
		default: { SetTextColor((HDC)wParam, tape.ink_EDIT_TERMINAL); break; }
		}
		switch (m_back)
		{
		case 0: { SetBkColor((HDC)wParam, tape.ink_black); return (LRESULT)tape.hB_black; }
		case 1: { SetBkColor((HDC)wParam, tape.ink_red); return (LRESULT)tape.hB_red; }
		case 2: { SetBkColor((HDC)wParam, tape.ink_orange); return (LRESULT)tape.hB_orange; }
		case 3: { SetBkColor((HDC)wParam, tape.ink_yellow); return (LRESULT)tape.hB_yellow; }
		case 4: { SetBkColor((HDC)wParam, tape.ink_emerald); return (LRESULT)tape.hB_emerald; }
		case 5: { SetBkColor((HDC)wParam, tape.ink_green); return (LRESULT)tape.hB_green; }
		case 6: { SetBkColor((HDC)wParam, tape.ink_blue); return (LRESULT)tape.hB_blue; }
		case 7: { SetBkColor((HDC)wParam, tape.ink_purple); return (LRESULT)tape.hB_purple; }
		case 8: { SetBkColor((HDC)wParam, tape.ink_bright_grey); return (LRESULT)tape.hB_bright_grey; }
		case 9: { SetBkColor((HDC)wParam, tape.ink_bright_red); return (LRESULT)tape.hB_bright_red; }
		case 10: { SetBkColor((HDC)wParam, tape.ink_bright_orange); return (LRESULT)tape.hB_bright_orange; }
		case 11: { SetBkColor((HDC)wParam, tape.ink_bright_yellow); return (LRESULT)tape.hB_bright_yellow; }
		case 12: { SetBkColor((HDC)wParam, tape.ink_bright_emerald); return (LRESULT)tape.hB_bright_emerald; }
		case 13: { SetBkColor((HDC)wParam, tape.ink_bright_green); return (LRESULT)tape.hB_bright_green; }
		case 14: { SetBkColor((HDC)wParam, tape.ink_bright_blue); return (LRESULT)tape.hB_bright_blue; }
		case 15: { SetBkColor((HDC)wParam, tape.ink_bright_purple); return (LRESULT)tape.hB_bright_purple; }
		default: { SetBkColor((HDC)wParam, tape.ink_black); return (LRESULT)tape.hB_black; }
		}
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_black);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_INITDIALOG:
	{
		std::thread(&LogDlg::_InitDialog, this, hWnd).detach();
		return TRUE;
	}
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		::MoveWindow(m_hEdit, 0, 0, rect.right + 3, rect.bottom, FALSE);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LOG:
		{
			switch (HIWORD(wParam))
			{
			case EN_ERRSPACE:
			case EN_MAXTEXT: { Edit_SetText(m_hEdit, L""); break; }
			case EN_CHANGE:
			{
				m_colorrand = false;
				int nlines = Edit_GetLineCount(m_hEdit) - 2;
				if (nlines < 0)
					return FALSE;

				WCHAR buf[256];
				Edit_GetLine(m_hEdit, nlines, buf, 256);

				std::wstring lastLine = buf;
				if (lastLine.substr(0, 3) == L"CLS")
				{
					m_pause = true;
					Edit_SetSel(m_hEdit, 0, -1);
					Edit_ReplaceSel(m_hEdit, L"");
					m_pause = false;
					Update();

				}
				else if (lastLine.substr(0, 5) == L"SALUT")
				{
					if (nlines < 1)
						return FALSE;

					m_pause = true;
					Edit_SetSel(m_hEdit, -1, -1);
					Edit_SetText(m_hEdit, L"SALUT\r\n");
					Edit_SetSel(m_hEdit, 0, -1);
					Edit_SetSel(m_hEdit, -1, -1);
					m_pause = false;
					Update();
				}
				else if (lastLine.substr(0, 14) == L"COMMENT TU VA?")
				{
					m_pause = true;
					Sleep(300);
					Edit_SetSel(m_hEdit, -1, -1);
					Edit_ReplaceSel(m_hEdit, L"BIEN\r\n");
					Edit_SetSel(m_hEdit, -1, -1);
					Sleep(1000);
					Edit_SetSel(m_hEdit, -1, -1);
					Edit_ReplaceSel(m_hEdit, L"ET TOI?\r\n");
					Edit_SetSel(m_hEdit, -1, -1);
					m_pause = false;
					Update();
				}
				else if (lastLine.substr(0, 9) == L"COLORDEMO")
					std::thread(&LogDlg::ColorDemo, this, m_hDlg, m_hEdit).detach();
				else if (lastLine.substr(0, 9) == L"COLORRAND")
				{
					m_colorrand = true;
					std::thread(&LogDlg::ColorRand, this, m_hDlg, m_hEdit).detach();
				}
				else if (lastLine.substr(0, 6) == L"COLOR ")
				{
					if (lastLine.size() > 7)
					{
						m_pause = true;
						std::wstring bytecharset = L"0123456789ABCDEF";
						std::wstring char1 = lastLine.std::wstring::substr(6, 1);
						std::wstring char2 = lastLine.std::wstring::substr(7, 1);

						if (bytecharset.find(char1) != std::wstring::npos)
							m_back = std::stoll(char1, nullptr, 16);
						if (bytecharset.find(char2) != std::wstring::npos)
							m_ink = std::stoll(char2, nullptr, 16);

						Edit_SetSel(m_hEdit, -1, -1);
						Hide();
						Show();
						m_pause = false;
						Update();
					}
				}
				else if (lastLine.substr(0, 5) == L"COLOR")
				{
					m_back = -1;
					m_ink = -1;
					Edit_SetSel(m_hEdit, -1, -1);
					Hide();
					Show();
				}
				break;
			}
			break;
			}
		}
		}
		break;
	}
	case WM_CLOSE:
	{
		if (GetKeyState(VK_ESCAPE) < 0 || GetKeyState(VK_CANCEL) < 0)
			return 0;
		else
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

wchar_t* LogDlg::LogGet()
{
	if (queue.empty())
		return NULL;

	wchar_t* ret = queue.front();
	queue.pop_front();
	return ret;
}

void LogDlg::Update()
{
	if (m_hEdit == NULL)
		return;
	wchar_t* logcnt = LogGet();
	if (logcnt == NULL)
		return;

	if (m_count > MAX_LOG_LINES)
	{
		int target = m_count - MAX_LOG_LINES;
		int targetByte = Edit_LineIndex(m_hEdit, target);
		Edit_SetSel(m_hEdit, 0, targetByte);
		Edit_ReplaceSel(m_hEdit, L"");
		m_count = MAX_LOG_LINES;
	}
	int ndx = GetWindowTextLength(m_hEdit);
	Edit_SetSel(m_hEdit, ndx, ndx);

	SYSTEMTIME st;
	GetLocalTime(&st);
	WCHAR date[10];

	if (m_load_dll)
		swprintf_s(date, 10, L"%02d:%02d:%02d ", st.wHour, st.wMinute, st.wSecond);

	while (logcnt != NULL)
	{
		Edit_ReplaceSel(m_hEdit, date);
		Edit_ReplaceSel(m_hEdit, logcnt);
		Edit_ReplaceSel(m_hEdit, L"\r\n");
		free(logcnt);
		m_count++;
		logcnt = LogGet();
	}
	Edit_Scroll(m_hEdit, MAX_LOG_LINES, 0);
}

void LogDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void LogDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL LogDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
