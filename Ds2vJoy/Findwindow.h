#pragma once

class Findwindow
{
public:
	Findwindow();
	~Findwindow();

	std::wstring		Get(int idx, int col);
	static				std::wstring GetText(HWND);
	static				std::wstring GetClass(HWND);
	void				Set(int idx, int col, std::wstring);
	void				Set(WCHAR* findClass, WCHAR* findTitle, int findIdx);
	std::wstring		Val();
	BOOL				Val(std::wstring);
	HWND				Find();
	int					Size();
	void				Clear();
	void				Pop();

private:
	bool				m_enable = false;

	std::vector<int>	m_idx = { };
	std::vector<std::wstring> m_class = { };
	std::vector<std::wstring> m_title = { };
};
