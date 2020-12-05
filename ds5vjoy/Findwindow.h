#pragma once
class Findwindow
{
	std::vector<std::wstring> m_class;
	std::vector<std::wstring> m_title;
	std::vector<int> m_idx;
	bool m_enable;

public:
	Findwindow();
	~Findwindow();
	std::wstring Val();
	BOOL Val(std::wstring);
	static std::wstring GetText(HWND);
	static std::wstring GetClass(HWND);
	HWND Find();

	void Clear();
	void Pop();
	int Size();
	std::wstring Get(int idx, int col);
	void Set(int idx, int col, std::wstring);
};

