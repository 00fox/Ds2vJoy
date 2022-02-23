#include "stdafx.h"
#include "Findwindow.h"

Findwindow::Findwindow()
{
}

Findwindow::~Findwindow()
{
}

std::wstring replace(const std::wstring& str, const std::wstring& from, const std::wstring& to)
{
	std::wstring buf = str;
	std::wstring::size_type pos = 0;
	while ((pos = buf.find(from, pos)) != std::wstring::npos)
	{
		buf.replace(pos, from.length(), to);
		pos += to.length();
	}
	return std::move(buf);
}

std::wstring Findwindow::Val()
{
	std::wstring buf;
	WCHAR findIdx[20];
	for (int i = 0; i < m_class.size(); i++)
	{
		swprintf_s(findIdx, 20, L"%d", m_idx[i]);
		buf += L"\"";
		buf += replace(m_class[i], L"\"", L"\"\"");
		buf += L"\",\"";
		buf += replace(m_title[i], L"\"", L"\"\"");
		buf += L"\",\"";
		buf += findIdx;
		buf += L"\";";
	}

	return std::move(buf);
}

BOOL Findwindow::Val(std::wstring val)
{
	std::wstring findClass;
	std::wstring findTitle;
	std::wstring findIdx;
	int begin = 0;
	bool flag = false;
	std::wstring* buf = nullptr;
	for (int pos = 0; pos < val.length(); pos++)
	{
		if (val[pos] == L'"')
		{
			if (begin % 2 == 0)
			{
				switch (++begin)
				{
				case 1: { buf = &findClass; break; }
				case 3: { buf = &findTitle; break; }
				case 5: { buf = &findIdx; break; }
				default: return FALSE;
				}
				continue;
			}
			if (!flag)
			{
				flag = true;
				continue;
			}
			flag = false;
		}
		else if (flag)
		{
			flag = false;
			buf = nullptr;
			switch (++begin)
			{
			case 2: break;
			case 4: break;
			case 6: break;
			default: return FALSE;
			}
			if (val[pos] == L';')
			{
				begin = 0;
				m_class.push_back(findClass);
				m_title.push_back(findTitle);
				m_idx.push_back(_wtoi(findIdx.c_str()));
				findClass.clear();
				findTitle.clear();
				findIdx.clear();
			}
		}
		if (buf != nullptr)
			buf->push_back(val[pos]);
	}
	return TRUE;
}

std::wstring Findwindow::GetText(HWND hwnd)
{
	std::wstring text;
	int length = GetWindowTextLength(hwnd);
	if (length > 0)
	{
		WCHAR* buf = new WCHAR[(size_t)length + 1];
		int ret = GetWindowText(hwnd, buf, length + 1);

		if (ret == length)
			text = buf;
		delete[] buf;
	}
	return std::move(text);
}

std::wstring Findwindow::GetClass(HWND hwnd)
{
	WCHAR buf[MAX_PATH];
	std::wstring str;
	if (GetClassName(hwnd, buf, MAX_PATH) > 0)
		str = buf;
	return std::move(str);


}

HWND Findwindow::Find()
{
	HWND hwnd = NULL;
	const WCHAR* fclass, * ftitle;
	for (int i = 0; i < m_class.size(); i++)
	{
		fclass = (m_class[i].empty()) ? NULL : m_class[i].c_str();
		ftitle = (m_title[i].empty()) ? NULL : m_title[i].c_str();
		if (fclass != NULL || ftitle != NULL)
		{
			int idx = m_idx[i];
			HWND child = NULL;
			do {
				child = FindWindowEx(hwnd, child, fclass, ftitle);
				if (child == NULL)
					break;
			} while (--idx >= 0);
			hwnd = child;
		}
		else
			hwnd = NULL;
		if (hwnd == NULL)
			break;
	}
	return hwnd;
}

void Findwindow::Clear()
{
	m_class.clear();
	m_title.clear();
	m_idx.clear();
}

void Findwindow::Pop()
{
	if (!m_class.empty())
	{
		m_class.pop_back();
		m_title.pop_back();
		m_idx.pop_back();
	}
}

int Findwindow::Size()
{
	return (int)m_class.size();
}

std::wstring Findwindow::Get(int idx, int col)
{
	std::wstring buf;
	if (m_class.size() > idx)
	{
		switch (col)
		{
		case 0: { buf = m_class[idx]; break; }
		case 1: { buf = m_title[idx]; break; }
		case 2:
		{
			WCHAR str[10];
			swprintf_s(str, 10, L"%d", m_idx[idx]);
			buf = str;
			break;
		}
		}
	}
	return std::move(buf);
}

void Findwindow::Set(int idx, int col, std::wstring buf)
{
	if (m_class.size() > idx)
	{
		switch (col)
		{
		case 0: { m_class[idx] = buf; break; }
		case 1: { m_title[idx] = buf; break; }
		case 2: { m_idx[idx] = _wtoi(buf.c_str()); break; }
		}
	}
	else if (idx == -1)
	{
		switch (col)
		{
		case 0: { m_class.push_back(buf); break; }
		case 1: { m_title.push_back(buf); break; }
		case 2: { m_idx.push_back(_wtoi(buf.c_str())); break; }
		}
	}
}

void Findwindow::Set(WCHAR* findClass, WCHAR* findTitle, int findIdx)
{
	m_class.push_back(findClass);
	m_title.push_back(findTitle);
	m_idx.push_back(findIdx);
}
