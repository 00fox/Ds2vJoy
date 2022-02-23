#pragma once
#include "stdafx.h"
#include "uxtheme.h"
#pragma comment (lib, "UxTheme.lib")

/*
//////////////////////////////////////////////////////////////////////
// INDEX:
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////// Convert
WCHAR*			WCHARI(std::wstring init = L"")
WCHAR*			WCHARI(M maxsize, F format, Args... args)
WCHAR*			WCHARI(const WCHAR* init)
WCHAR*			WCHARI(int ressourceid, const WCHAR* init = L"")

std::wstring	rs2ws(char* s)
std::wstring	rs2ws(std::string s)
std::string		rws2s(wchar_t* ws)
std::string		rws2s(std::wstring ws)
int				urlEncode(const char* toencode, const int strSize, char* encoded, const int resultSize)
std::string		urlDecode(std::string& src)

////////////////////////////////////////////////////////////////////// Replace
BOOL			FindInString(std::wstring stringin, std::wstring findwhat, int begin = 0, int length = 0)
std::wstring	SubString(std::wstring stringin, int begin = 0, int length = 0)
std::wstring	SubString(std::wstring stringin, std::wstring findwhat, int totheend = 0, int stringincluded = 0)
BOOL			isInList(std::set<int> list, int element)
BOOL			LastCharis(std::wstring stringin, std::wstring findwhat)
std::wstring	ReplaceInString(std::wstring stringin, std::wstring replwhat, char replfor)

////////////////////////////////////////////////////////////////////// Ressources
BOOL			isFileExists(const std::string& name)
BOOL			WriteToFile(std::wstring filename, std::vector<char> data, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL			CreateDirectoryRecurse(const std::wstring& directory, bool hidden = false)
int				DeleteDirectory(const std::string& directory, bool recurse = true)
BOOL			LoadEmbeddedFont(WORD resourceID, HANDLE* fonthandle)
BOOL			LoadEmbeddedResource(WORD resourceID, std::vector<char>* output, DWORD* resourceSize)
BOOL			WriteEmbededResource(std::wstring filename, WORD resourceID, bool overwrite = true, bool hidden = false)
BOOL			ExtractEmbededResource(std::wstring location, WORD resourceID, bool overwrite = true, bool forcehidden = false)
void			ForceRemoveModule(LPCTSTR ModuleName, bool deletedll = false)

////////////////////////////////////////////////////////////////////// Diverse
std::wstring	WinPath()
std::wstring	ExePath()
std::wstring	TmpPath()
std::wstring	PrfPath()
BOOL			LaunchProcess(LPWSTR lpCommandLine, bool wait = false)
std::wstring	LaunchCmd(const wchar_t* cmd)
BOOL			ClientArea(RECT* rect, bool points = false)	//x, y, w, h, true x, y, x', y'
int				MessageBoxPos(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, int x, int y)
void			CreateToolTip(HWND hWndParent, HWND hControlItem, PTSTR tooltipText)

////////////////////////////////////////////////////////////////////// Process
BOOL			IsWow64()
DWORD			GetPIDByName(std::wstring ProcessName)
WCHAR*			GetExeNameByPID(DWORD ProcessID)

////////////////////////////////////////////////////////////////////// GUID
GUID			String2GUID(const std::wstring& str)
GUID			ServerString2GUID(const std::wstring& str)
std::wstring	GUID2String(GUID guid)
std::wstring	GUID2ServerString(GUID guid)

////////////////////////////////////////////////////////////////////// Services
BOOL			IsServiceInstalled(LPWSTR ServiceName)
int				GetServiceState(LPWSTR ServiceName)
BOOL			ServiceInstall(LPWSTR ServiceName, LPWSTR installpath, DWORD servicetype, bool verbose = false)
BOOL			ServiceStart(LPWSTR ServiceName, bool verbose = false)
BOOL			StopDependentServices(SC_HANDLE scm_handle, SC_HANDLE service_handle)
BOOL			ServiceStop(LPWSTR ServiceName, bool verbose = false)
BOOL			ServiceDelete(LPWSTR ServiceName, bool verbose = false)

////////////////////////////////////////////////////////////////////// Devices
std::vector<std::wstring> ListofDriversByFile(bool verbose = false)
BOOL			CheckForDriverByFile(LPWSTR DriverName, bool verbose = false)
BOOL			CheckForDriverById(LPWSTR DriverID, bool verbose = false)
BOOL			DeviceRestart(std::wstring DriverID)
*/

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////// Convert
// 

//-----------------------------------------------------------------------------
inline WCHAR* WCHARI(std::wstring init = L"")
{
	size_t tocopy = init.length();
	if (tocopy)
	{
		WCHAR* ret = new WCHAR[tocopy + 1];
		wcscpy_s(ret, tocopy + 1, init.c_str());
		return ret;
	}
	else
	{
		WCHAR* ret = new WCHAR;
		ret[0] = 0;
		return ret;
	}
}
template <typename M, typename F, typename... Args>
inline WCHAR* WCHARI(M maxsize, F format, Args... args)
{
	WCHAR* ret = new WCHAR[maxsize];
	ret[0] = 0;
	swprintf_s(ret, maxsize, format, args...);
	return ret;
}
inline WCHAR* WCHARI(const WCHAR* init)
{
	size_t tocopy = wcslen(init);
	if (tocopy)
	{
		WCHAR* ret = new WCHAR[tocopy + 1];
		wcscpy_s(ret, tocopy + 1, init);
		return ret;
	}
	else
	{
		WCHAR* ret = new WCHAR;
		ret[0] = 0;
		return ret;
	}
	//WCHAR* ret = (WCHAR*)&init[0];
}
inline WCHAR* WCHARI(int ressourceid, const WCHAR* init = L"")
{
	WCHAR buffer[1024];
	if (LoadStringW(GetModuleHandle(NULL), ressourceid, buffer, 1024))
		return WCHARI(buffer);
	else
		return WCHARI(init);
}

//-----------------------------------------------------------------------------
inline std::wstring rs2ws(char* s)
{
	size_t len = strlen(s) + 1;

	if (len > 1)
	{
		wchar_t* ws = new wchar_t[len];

		size_t outlen;
		mbstowcs_s(&outlen, ws, len, s, len - 1);
		return ws;
	}
	else
		return L"";
}

//-----------------------------------------------------------------------------
inline std::wstring rs2ws(std::string s)
{
	return rs2ws((char*)s.c_str());
}

//-----------------------------------------------------------------------------
inline std::string rws2s(wchar_t* ws)
{
	size_t len = wcslen(ws) + 1;

	if (len > 1)
	{
		char* s = new char[len];

		size_t outlen;
		wcstombs_s(&outlen, s, len, ws, len - 1);
		return s;
	}
	else
		return "";
}

//-----------------------------------------------------------------------------
inline std::string rws2s(std::wstring ws)
{
	return rws2s((wchar_t*)ws.c_str());
}

//-----------------------------------------------------------------------------
inline int urlEncode(const char* toencode, const int strSize, char* encoded, const int resultSize)
{
	if ((toencode == NULL) || (encoded == NULL) || (strSize <= 0) || (resultSize <= 0))
		return 0;

	int j = 0;
	for (int i = 0; (i < strSize) && (j < resultSize); i++)
	{
		char ch = toencode[i];
		if ((ch >= 'A') && (ch <= 'Z'))
		{
			encoded[j++] = ch;
		}
		else if ((ch >= 'a') && (ch <= 'z'))
		{
			encoded[j++] = ch;
		}
		else if ((ch >= '0') && (ch <= '9'))
		{
			encoded[j++] = ch;
		}
		else if ( ch == ' ' )
		{
			encoded[ j ++ ] = '+';
		}
		else if (ch == ':')
		{
			encoded[j++] = ch;
		}
		else if (ch == '/')
		{
			encoded[j++] = ch;
		}
		else if (ch == '=')
		{
			encoded[j++] = ch;
		}
		else if (ch == '.')
		{
			encoded[j++] = ch;
		}
		else if (ch == '_')
		{
			encoded[j++] = ch;
		}
		else
		{
			if (j + 3 < resultSize)
			{
				sprintf_s(encoded + j, (size_t)resultSize - j, "%%%02X", (unsigned char)ch);
				j += 3;
			}
			else
			{
				return 0;
			}
		}
	}

	encoded[j] = '\0';

	return j;
}

//-----------------------------------------------------------------------------
std::string urlDecode(std::string& src)
{
	std::string ret;
	char ch;
	int j;
	for (size_t i = 0; i < src.length(); i++)
	{
		if (int(src[i]) == 37)
		{
			sscanf_s(src.substr(i + 1, 2).c_str(), "%x", &j);
			ch = static_cast<char>(j);
			ret += ch;
			i = i + 2;
		}
		else
			ret += src[i];
	}
	return (ret);
}

////////////////////////////////////////////////////////////////////// Replace
// 

//-----------------------------------------------------------------------------
inline BOOL FindInString(std::wstring stringin, std::wstring findwhat, int begin = 0, int length = 0)
// begin < 0 : from string total lenght - begin
// length < 0 : start at begin - length caracters
{
	if (begin || length)
	{
		size_t strlength = stringin.length();
		size_t begintmp = 0;
		size_t endtmp = strlength;

		if (length < 0)
		{
			endtmp = (begin < 0) ? ((int)stringin.length() + begin) : begin;
			if (endtmp < 0)
				return FALSE;
			else if (endtmp > strlength)
			{
				begintmp = min(max((endtmp + length), 0), (int)stringin.length());
				endtmp = strlength;
			}
			else
				begintmp = max((endtmp + length), 0);
		}
		else if (length)
		{
			begintmp = (begin < 0) ? ((int)stringin.length() + begin) : min(begin, (int)stringin.length());
			if (begintmp < 0)
			{
				endtmp = max((begintmp + length), 0);
				begintmp = 0;
			}
			else
				endtmp = min((begintmp + length), (int)stringin.length());

			endtmp = min(endtmp, strlength);
		}
		else
		{
			begintmp = (begin < 0) ? ((int)stringin.length() + begin) : min(begin, (int)stringin.length());
			if (begintmp < 0)
				begintmp = 0;
		}

		std::wstring stringintmp = stringin.substr(begintmp, endtmp - begintmp);
		if (stringintmp.find(findwhat) != std::string::npos)
			return TRUE;
	}
	else if (stringin.find(findwhat) != std::string::npos)
		return TRUE;

	return FALSE;
}

//-----------------------------------------------------------------------------
inline std::wstring SubString(std::wstring stringin, int begin = 0, int length = 0)
// begin < 0 : from string total lenght - begin
// length < 0 : start at begin - length caracters
{
	if (begin || length)
	{
		size_t strlength = stringin.length();
		size_t begintmp = 0;
		size_t endtmp = strlength;

		if (length < 0)
		{
			endtmp = (begin < 0) ? ((int)stringin.length() + begin) : begin;
			if (endtmp < 0)
				return L"";
			else if (endtmp > strlength)
			{
				begintmp = min(max((endtmp + length), 0), (int)stringin.length());
				endtmp = strlength;
			}
			else
				begintmp = max((endtmp + length), 0);
		}
		else if (length)
		{
			begintmp = (begin < 0) ? ((int)stringin.length() + begin) : min(begin, (int)stringin.length());
			if (begintmp < 0)
			{
				endtmp = max((begintmp + length), 0);
				begintmp = 0;
			}
			else
				endtmp = min((begintmp + length), (int)stringin.length());

			endtmp = min(endtmp, strlength);
		}
		else
		{
			begintmp = (begin < 0) ? ((int)stringin.length() + begin) : min(begin, (int)stringin.length());
			if (begintmp < 0)
				begintmp = 0;
		}
		return stringin.substr(begintmp, endtmp - begintmp);
	}
	else
		return stringin;
}

//-----------------------------------------------------------------------------
inline std::wstring SubString(std::wstring stringin, std::wstring findwhat, int totheend = 0, int stringincluded = 0)
{
	std::wstring result = L"";
	size_t pos = stringin.find(findwhat);
	size_t strlength = findwhat.length();

	if (pos < stringin.length())
	{
		if (totheend)
		{
			if (stringincluded)
				result = stringin.substr(pos);
			else
				result = stringin.substr(pos + strlength);
		}
		else
		{
			if (stringincluded)
				result = stringin.substr(0, pos + strlength);
			else
				result = stringin.substr(0, pos);
		}
	}

	return result;
}

//-----------------------------------------------------------------------------
inline BOOL isInList(std::set<int> list, int element)
{
	return list.count(element) != 0;
}

//-----------------------------------------------------------------------------
inline BOOL LastCharis(std::wstring stringin, std::wstring findwhat)
{
	if (stringin.empty())
		return FALSE;

	std::size_t found = stringin.find_last_of(findwhat);
	if (stringin.length() == found + 1)
		return TRUE;

	return FALSE;
}

//-----------------------------------------------------------------------------
inline std::wstring ReplaceInString(std::wstring stringin, std::wstring replwhat, char replfor)
{
	std::size_t found = stringin.find_first_of(replwhat);

	while (found != std::string::npos)
	{
		stringin[found] = replfor;
		found = stringin.find_first_of(replwhat, found + 1);
	}

	return stringin;
}

////////////////////////////////////////////////////////////////////// Resources
//

//-----------------------------------------------------------------------------
inline BOOL isFileExists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(std::wstring filename, std::vector<char> data, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	char* string = reinterpret_cast<char*> (&data[0]);

	DWORD dwCreationDisposition = (overwrite) ? CREATE_ALWAYS : CREATE_NEW;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL | ((hidden) ? FILE_ATTRIBUTE_HIDDEN : 0);

	HANDLE hFile = CreateFile(filename.c_str(), GENERIC_WRITE, 0, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD writ; BOOL bres = WriteFile(hFile, string, BytesToWrite, &writ, NULL);
		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL CreateDirectoryRecurse(const std::wstring& directory, bool hidden = false)
{
	static const std::wstring separators(L"\\/");

	// If the specified directory name doesn't exist, do our thing
	DWORD fileAttributes = ::GetFileAttributesW(directory.c_str());

	if (fileAttributes == INVALID_FILE_ATTRIBUTES)
	{
		// Recursively do it all again for the parent directory, if any
		std::size_t slashIndex = directory.find_last_of(separators);
		if (slashIndex != std::wstring::npos)
			CreateDirectoryRecurse(directory.substr(0, slashIndex), hidden);

		// Create the last directory on the path
		if (!::CreateDirectoryW(directory.c_str(), nullptr))
			return FALSE;
		if (hidden)
			SetFileAttributes(directory.c_str(), FILE_ATTRIBUTE_HIDDEN);
	}
	else if (!(((fileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
			((fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0)))
			return FALSE;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL DeleteDirectory(std::wstring directory, bool recurse = true)
{
	bool			bSubdirectory = false;							// Flag, indicating whether subdirectories have been found
	HANDLE			hFile;											// Handle to directory
	std::wstring	strFilePath;									// Filepath
	std::wstring	strPattern = directory + L"/*.*";				// Pattern
	WIN32_FIND_DATA	FileInformation;								// File information

	hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileInformation.cFileName[0] != '.')
			{
				strFilePath.erase();
				strFilePath = directory + L"/" + FileInformation.cFileName;

				if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (recurse)
					{
						// Delete subdirectory
						int iRC = DeleteDirectory(strFilePath, recurse);
						if (iRC)
							return iRC;
					}
					else
						bSubdirectory = true;
				}
				else
				{
					// Set file attributes
					if (::SetFileAttributes(strFilePath.c_str(),
						FILE_ATTRIBUTE_NORMAL) == FALSE)
						return FALSE;

					// Delete file
					if (::DeleteFile(strFilePath.c_str()) == FALSE)
						return FALSE;
				}
			}
		} while (::FindNextFile(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			return FALSE;
		else
		{
			if (!bSubdirectory)
			{
				// Set directory attributes
				if (::SetFileAttributes(directory.c_str(),
					FILE_ATTRIBUTE_NORMAL) == FALSE)
					return ::GetLastError();

				// Delete directory
				if (::RemoveDirectory(directory.c_str()) == FALSE)
					return ::GetLastError();
			}
		}
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL LoadEmbeddedFont(WORD resourceID, HANDLE* fonthandle)
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	HRSRC resourceHandle = ::FindResource(hInst, MAKEINTRESOURCE(resourceID), RT_FONT);

	if (resourceHandle != nullptr)
	{
		HGLOBAL dataHandle = ::LoadResource(hInst, resourceHandle);
		if (dataHandle != nullptr)
		{
			DWORD nFonts = 0;
			*fonthandle = AddFontMemResourceEx(LockResource(dataHandle), SizeofResource(hInst, resourceHandle), NULL, &nFonts);

			FreeResource(dataHandle);
			if (fonthandle != nullptr)
				return TRUE;
		}
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL LoadEmbeddedResource(WORD resourceID, std::vector<char>* output, DWORD* resourceSize)
{
	std::vector<char> outputtmp;

	// If you need to retrieve resources embedded in a binary that is not the current running program, modify this function to pass in a HMODULE value.
	HMODULE module = nullptr;
	HRSRC resourceHandle = ::FindResource(module, MAKEINTRESOURCE(resourceID), RT_RCDATA);

	if (resourceHandle != nullptr)
	{
		HGLOBAL dataHandle = ::LoadResource(module, resourceHandle);
		if (dataHandle != nullptr)
		{
			auto resourceSizetmp = ::SizeofResource(module, resourceHandle);
			*resourceSize = resourceSizetmp;

			if (resourceSizetmp != 0)
			{
				auto firstByte = reinterpret_cast<const char*>(::LockResource(dataHandle));

				if (firstByte != nullptr)
				{
					outputtmp.resize(resourceSizetmp);
					std::copy(firstByte, firstByte + resourceSizetmp, outputtmp.begin());
					*output = outputtmp;

					FreeResource(dataHandle);
					return TRUE;

					// No need to call ::FreeResource on any 32 or 64 bit version of Windows. See MSDN for details
					// https://msdn.microsoft.com/en-us/library/windows/desktop/ms648044%28v=vs.85%29.aspx
				}
			}
		}
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL WriteEmbededResource(std::wstring filename, WORD resourceID, bool overwrite = true, bool hidden = false)
{
	std::vector<char> data;
	DWORD resourceSize;

	if (LoadEmbeddedResource(resourceID, &data, &resourceSize))
	{
		DWORD ressourceWrinten = 0; WriteToFile(filename, data, resourceSize, overwrite, hidden);
		if (ressourceWrinten)
			return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL ExtractEmbededResource(std::wstring location, WORD resourceID, bool overwrite = true, bool forcehidden = false)
{
	bool result = FALSE;

	std::vector<char> data;
	DWORD resourceSize;

	if (LoadEmbeddedResource(resourceID, &data, &resourceSize))
	{
		HZIP hz = OpenZip(&data[0], resourceSize, 0);

		ZIPENTRY ze; GetZipItem(hz, -1, &ze);
		int nitems = ze.index;

		for (int zi = 0; zi < nitems; zi++)
		{
			ZIPENTRY ze; GetZipItem(hz, zi, &ze);

			std::wstring filename = location;
			filename = ReplaceInString(filename, L"\\", '/');
			if (LastCharis(filename, L"/"))
				filename = filename + ze.name;
			else
				filename = filename + L"/" + ze.name;
			filename = ReplaceInString(filename, L"\\", '/');

			if (LastCharis(filename, L"/"))
				CreateDirectoryRecurse(filename, forcehidden);
			else
			{
				HANDLE h;
				DWORD dwCreationDisposition = (overwrite) ? CREATE_ALWAYS : CREATE_NEW;
				DWORD dwFlagsAndAttributes = ze.attr | ((forcehidden) ? FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_HIDDEN : 0);

				h = CreateFile(filename.c_str(), GENERIC_WRITE, 0, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
				if (h != INVALID_HANDLE_VALUE)
				{
					char* buffer = new char[ze.unc_size];
					UnzipItem(hz, zi, buffer, ze.unc_size);

					DWORD ressourceWrinten; BOOL bres = WriteFile(h, buffer, ze.unc_size, &ressourceWrinten, NULL);
					if (ressourceWrinten)
					{
						SetFileTime(h, &ze.ctime, &ze.atime, &ze.mtime);
						result = TRUE;
					}
					delete[] buffer;
				}
				CloseHandle(h);
			}
		}
		CloseZip(hz);
	}

	return result;
}

//-----------------------------------------------------------------------------
inline void ForceRemoveModule(LPCTSTR ModuleName, bool deletedll = false)
{
	HMODULE hMod;
	hMod = ::GetModuleHandle(ModuleName);
	if (hMod == 0)
		return;
	/* DISCLAIMER potentially infinite loop
	 * not advisable in production code,
	 * included by request of the OP to
	 * match his original */
	while (::FreeLibrary(hMod));
	if (deletedll && ModuleName)
		::DeleteFile(ModuleName);
}

////////////////////////////////////////////////////////////////////// Diverse
// 

//-----------------------------------------------------------------------------
inline std::wstring WinPath()
{
	WCHAR buffer[MAX_PATH] = { 0 };

	int ret = GetWindowsDirectoryW(buffer, MAX_PATH);

	if (ret)
		return buffer;
	else
		return L"";
}

//-----------------------------------------------------------------------------
inline std::wstring ExePath()
{
	WCHAR buffer[MAX_PATH] = { 0 };

	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

	return std::wstring(buffer).substr(0, pos);
}

//-----------------------------------------------------------------------------
inline std::wstring TmpPath()
{
	WCHAR buffer[MAX_PATH] = { 0 };

	GetTempPathW(MAX_PATH, buffer);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

	return std::wstring(buffer).substr(0, pos);
}

//-----------------------------------------------------------------------------
inline std::wstring PrfPath(bool x86test = false)
{
	wchar_t* buffer;
	size_t numberOfElements;

	if (x86test)
	{
		_wdupenv_s(&buffer, &numberOfElements, L"ProgramFiles(x86)");
		if (buffer == NULL)
			return PrfPath(false);
	}
	else
		_wdupenv_s(&buffer, &numberOfElements, L"ProgramFiles");

	return buffer;
}

//-----------------------------------------------------------------------------
inline BOOL LaunchProcess(LPWSTR lpCommandLine, bool wait = false)
{
	if (lpCommandLine == nullptr || *lpCommandLine == '\0')
		return FALSE;

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (CreateProcessW(NULL, lpCommandLine, NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &info, &processInfo))
	{
		if (wait)
			WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline std::wstring LaunchCmd(const wchar_t* cmd)
{
	HWND hCurWnd = ::GetForegroundWindow();

	std::array<wchar_t, 128> buffer;
	std::wstring result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_wpopen(cmd, L"r"), _pclose);

	if (!pipe)
		return L"WindowsTools.h LaunchCmd popen() failed!";
	while (fgetws(buffer.data(), (int)buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();

	::SetForegroundWindow(hCurWnd);
	::SetFocus(hCurWnd);
	return result;
}

//-----------------------------------------------------------------------------
inline BOOL ClientArea(RECT* rect, bool points = false)	//x, y, w, h, true x, y, x', y'
{
	RECT desktop;
	GetClientRect(GetDesktopWindow(), &desktop);

	HWND taskbarhwnd = FindWindow(L"Shell_traywnd", NULL);

	if (taskbarhwnd)
	{
		RECT taskbar;
		GetWindowRect(taskbarhwnd, &taskbar);

		if (taskbar.top)							//Bottom position
		{
			rect->left = 0;
			rect->top = 0;
			rect->right = desktop.right;
			rect->bottom = taskbar.top;
		}
		else if (taskbar.left)						//Right position
		{
			rect->left = 0;
			rect->top = 0;
			rect->right = taskbar.left;
			rect->bottom = desktop.bottom;
		}
		else if (taskbar.right < desktop.right)		//Left position
		{
			rect->left = taskbar.right;
			rect->top = 0;
			if (points)
				rect->right = desktop.right;
			else
				rect->right = desktop.right - taskbar.right;
			rect->bottom = desktop.bottom;
		}
		else										//Top position
		{
			rect->left = 0;
			rect->top = taskbar.bottom;
			rect->right = desktop.right;
			if (points)
				rect->bottom = desktop.bottom;
			else
				rect->bottom = desktop.bottom - taskbar.bottom;
		}

		return TRUE;
	}
	else
		*rect = desktop;

	return FALSE;
}

//-----------------------------------------------------------------------------
static thread_local int MsgBox_x = 0;
static thread_local int MsgBox_y = 0;
static unsigned int MsgBox_start = 0;
static unsigned int MsgBox_uType = 0;
static unsigned int MsgBox_wrap = 0;

inline LRESULT CALLBACK CBTProc(int message, WPARAM wParam, LPARAM lParam)
{

	static unsigned int MsgBox_cx = 0;
	switch (message)
	{
	case HCBT_CREATEWND:
		switch (++MsgBox_start)
		{
		case 1: //window
		{
			CBT_CREATEWND* s = (CBT_CREATEWND*)lParam;
			s->lpcs->x = MsgBox_x;
			s->lpcs->y = MsgBox_y;
			if (MsgBox_wrap)
				s->lpcs->cx = MsgBox_wrap;
			MsgBox_cx = s->lpcs->cx;
		}
		break;
		case 2: //1
		{
			CBT_CREATEWND* s = (CBT_CREATEWND*)lParam;
			switch (MsgBox_uType & 0xFL)
			{
			case MB_OKCANCEL:			s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 102;	break;
			case MB_RETRYCANCEL:		s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 102;	break;
			case MB_ABORTRETRYIGNORE:	s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 272;	break;
			case MB_YESNOCANCEL:		s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 187;	break;
			case MB_CANCELTRYCONTINUE:	s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 187;	break;
			}
		}
		break;
		case 3: //2 || text
		{
			CBT_CREATEWND* s = (CBT_CREATEWND*)lParam;
			switch (MsgBox_uType & 0xFL)
			{
			case MB_OKCANCEL:			s->lpcs->cx = 0;	s->lpcs->x = MsgBox_cx;			break;
			case MB_RETRYCANCEL:		s->lpcs->cx = 0;	s->lpcs->x = MsgBox_cx;			break;
			case MB_ABORTRETRYIGNORE:	s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 187;	break;
			case MB_YESNOCANCEL:		s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 102;	break;
			case MB_CANCELTRYCONTINUE:	s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 102;	break;
			}
		}
		break;
		case 4: //3 || text || icon
		{
			CBT_CREATEWND* s = (CBT_CREATEWND*)lParam;
			switch (MsgBox_uType & 0xFL)
			{
			case MB_ABORTRETRYIGNORE:	s->lpcs->cx = 80;	s->lpcs->x = MsgBox_cx - 102;	break;
			case MB_YESNOCANCEL:		s->lpcs->cx = 0;	s->lpcs->x = MsgBox_cx;			break;
			case MB_CANCELTRYCONTINUE:	s->lpcs->cx = 0;	s->lpcs->x = MsgBox_cx;			break;
			}
		}
		break;
		}
		break;
	}
	return CallNextHookEx(NULL, message, wParam, lParam);
}

// To indicate the buttons displayed in the message box, specify one of the following values.
// MB_OK					OK								This is the default
// MB_OKCANCEL				OK		Cancel
// MB_ABORTRETRYIGNORE		Abort	Retry		Ignore
// MB_RETRYCANCEL			Retry	Cancel
// MB_YESNO					Yes		No
// MB_YESNOCANCEL			Yes		No			Cancel
// MB_CANCELTRYCONTINUE		Cancel	Try Again	Continue
// MB_HELP													Adds Help, When clicks or presses F1, WM_HELP message is sent to the owner
//  
// To display an icon in the message box, specify one of the following values
// MB_ICONEXCLAMATION		Exclamation-point icon appears in the message box
// MB_ICONWARNING			Exclamation-point icon appears in the message box
// MB_ICONINFORMATION		Icon consisting of a lowercase letter i in a circle appears in the message box
// MB_ICONASTERISK			Icon consisting of a lowercase letter i in a circle appears in the message box
// MB_ICONQUESTION			Question-mark icon appears in the message box
// MB_ICONSTOP				Stop-sign icon appears in the message box
// MB_ICONERROR				Stop-sign icon appears in the message box
// MB_ICONHAND				Stop-sign icon appears in the message box
//  
// To indicate the default button, specify one of the following values
// MB_DEFBUTTON1			The first button is the default button.	MB_DEFBUTTON1 is the default unless MB_DEFBUTTON2, MB_DEFBUTTON3, or MB_DEFBUTTON4 is specified.
// MB_DEFBUTTON2			The second button is the default button.
// MB_DEFBUTTON3			The third button is the default button.
// MB_DEFBUTTON4			The fourth button is the default button.
//  
// To indicate the modality of the dialog box, specify one of the following values
// MB_APPLMODAL				The user must respond to the message box before continuing work in the window identified by the hWnd parameter.
// 								However, the user can move to the windows of other threads and work in those windows.
// 								Depending on the hierarchy of windows in the application, the user may be able to move to other windows within the thread.
// 								All child windows of the parent of the message box are automatically disabled, but pop-up windows are not.
// 								is the default if neither MB_SYSTEMMODAL nor MB_TASKMODAL is specified.
// MB_SYSTEMMODAL			Same as MB_APPLMODAL except that the message box has the WS_EX_TOPMOST style.
// 								Use system-modal message boxes to notify the user of serious, potentially damaging errors that require immediate attention (for example, running out of memory).
// 								This flag has no effect on the user's ability to interact with windows other than those associated with hWnd.
// MB_TASKMODAL				Same as MB_APPLMODAL except that all the top-level windows belonging to the current thread are disabled if the hWnd parameter is NULL.
// 								Use this flag when the calling application or library does not have a window handle available but still needs to prevent input to other windows in the calling thread without suspending other threads.
//  
// To specify other options, use one or more of the following values.
// MB_DEFAULT_DESKTOP_ONLY	Same as desktop of the interactive window station. For more information, see Window Stations.
// 								If the current input desktop is not the default desktop, MessageBox does not return until the user switches to the default desktop.
// MB_RIGHT					The text is right-justified.
// MB_RTLREADING			Displays message and caption text using right-to-left reading order on Hebrew and Arabic systems.
// MB_SETFOREGROUND			The message box becomes the foreground window. Internally, the system calls the SetForegroundWindow function for the message box.
// MB_TOPMOST				The message box is created with the WS_EX_TOPMOST window style.
// MB_SERVICE_NOTIFICATION	The caller is a service notifying the user of an event. The function displays a message box on the current active desktop, even if there is no user logged on to the computer.
// 								Terminal Services: If the calling thread has an impersonation token, the function directs the message box to the session specified in the impersonation token.
// 								If this flag is set, the hWnd parameter must be NULL. This is so that the message box can appear on a desktop other than the desktop corresponding to the hWnd.
// 								For information on security considerations in regard to using this flag, see Interactive Services.
// 								DescriptionIn particular, be aware that this flag can produce interactive content on a locked desktop and should therefore be used for only a very limited set of scenarios, such as resource exhaustion.
//
// Return code/Value/Description
// IDOK			1	OK
// IDCANCEL		2	Cancel
// IDABORT		3	Abort
// IDRETRY		4	Retry
// IDIGNORE		5	Ignore
// IDYES		6	Yes
// IDNO			7	No
// IDTRYAGAIN	10	Try Again
// IDCONTINUE	11	Continue

inline int MessageBoxPos(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, int x, int y, int wrap = 0)
{
	MsgBox_start = 0;
	MsgBox_uType = uType;
	MsgBox_wrap = wrap;
	if (x == 0 && y == 0)
	{
		RECT desk;
		ClientArea(&desk);
		MsgBox_x = desk.left + ((desk.right - desk.left - 400) / 2);
		MsgBox_y = desk.top + ((desk.bottom - desk.top - 300) / 2);
	}
	else
	{
		MsgBox_x = x;
		MsgBox_y = y;
	}
	HHOOK hHook = SetWindowsHookEx(WH_CBT, &CBTProc, NULL, GetCurrentThreadId());
	int result = MessageBox(hWnd, lpText, lpCaption, uType);
	if (hHook) UnhookWindowsHookEx(hHook);

	return result;
}

//-----------------------------------------------------------------------------
inline void CreateToolTip(
	HWND hWndParent,	/*HWND handle for the parent window, for example dialog box*/
	HWND hControlItem,	/*HWND handle for the control item, for example checkbox*/
	PTSTR tooltipText	/*text for the tool-tip*/)
{
	if (!hControlItem || !hWndParent || !tooltipText)
		return;

	HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
		WS_POPUP | TTS_ALWAYSTIP /*| TTS_BALLOON*/,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hWndParent, NULL, GetModuleHandle(0), NULL);

	if (!hwndTip)
		return;

	SetWindowPos(hwndTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hWndParent;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hControlItem;
	toolInfo.lpszText = tooltipText;
	GetClientRect(hWndParent, &toolInfo.rect);

	SetWindowTheme(hwndTip, L"", L"");
	SendMessage(hwndTip, TTM_SETMAXTIPWIDTH, 0, 8192);
	SendMessage(hwndTip, TTM_SETDELAYTIME, TTDT_AUTOPOP, MAKELPARAM((32767), (0)));
	SendMessage(hwndTip, TTM_SETTIPBKCOLOR, tape.Bk_TOOLTIP, 0);
	SendMessage(hwndTip, TTM_SETTIPTEXTCOLOR, tape.ink_TOOLTIP, 0);
	RECT TipRect = { 4, 1, 2, 3 };
	SendMessage(hwndTip, TTM_SETMARGIN, 0, LPARAM(&TipRect));
	SendMessage(hwndTip, WM_SETFONT, WPARAM(tape.hTooltip), MAKELPARAM(TRUE, 0));

	if (!SendMessage(hwndTip, TTM_ADDTOOL, 0, LPARAM(&toolInfo)))
		MessageBox(0, TEXT("TTM_ADDTOOL failed\nWrong project manifest!"), 0, 0);
}

//-----------------------------------------------------------------------------
inline void SetWindowTransparent(HWND hwnd, bool bTransparent, int nTransparency)
{
	long lExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

	if (bTransparent)
	{
		HMODULE hMod = LoadLibrary(_T("User32"));
		if (hMod)
		{
			typedef BOOL(WINAPI* pSetLayeredWindowAttributes)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
			pSetLayeredWindowAttributes p = (pSetLayeredWindowAttributes)GetProcAddress(hMod, "SetLayeredWindowAttributes");
			if (p)
			{
				(void)SetWindowLong(hwnd, GWL_EXSTYLE, lExStyle | WS_EX_LAYERED);
				(void)p(hwnd, 0, (BYTE)(nTransparency * 2.55), LWA_ALPHA);
			}
			(void)FreeLibrary(hMod);
		}
	}
	else
	{
		(void)SetWindowLong(hwnd, GWL_EXSTYLE, lExStyle & ~WS_EX_LAYERED);
		(void)RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
}

////////////////////////////////////////////////////////////////////// Process
//

//-----------------------------------------------------------------------------
inline BOOL IsWow64()
{
#if _WIN64

	return TRUE;

#elif _WIN32

	typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	bool isWow64 = FALSE;

	//IsWow64Process is not available on all supported versions of Windows.
	//Use GetModuleHandle to get a handle to the DLL that contains the function
	//and GetProcAddress to get a pointer to the function if available.

	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &isWow64))
			return FALSE;

		return TRUE;
	}
	else
		return FALSE;

#else

	return FALSE;

#endif
}

//-----------------------------------------------------------------------------
inline DWORD GetPIDByName(std::wstring ProcessName)
{
	HWND hWnd = FindWindow(ProcessName.c_str(), NULL);
	DWORD ProcessID = 0;
	DWORD parent;

	parent = GetWindowThreadProcessId(hWnd, &ProcessID);

	return ProcessID;
}

//-----------------------------------------------------------------------------
inline WCHAR* GetExeNameByPID(DWORD ProcessID)
{
	WCHAR ProcessNametmp[MAX_PATH] = L"<unknown>";

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ProcessID);

	if (hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			GetModuleBaseName(hProcess, hMod, ProcessNametmp, sizeof(ProcessNametmp) / sizeof(WCHAR));

		CloseHandle(hProcess);
	}

	size_t tocopy = wcslen(ProcessNametmp) + 1;
	WCHAR* ProcessName = new WCHAR[tocopy];
	wcscpy_s(ProcessName, tocopy, ProcessNametmp);

	return ProcessName;
}

////////////////////////////////////////////////////////////////////// GUID
//

//-----------------------------------------------------------------------------
inline GUID String2GUID(const std::wstring& str)
{
	GUID guid;
	swscanf_s(str.c_str(),
		L"{%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
		&guid.Data1, &guid.Data2, &guid.Data3,
		&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
		&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

	return guid;
}
/*
*/
//-----------------------------------------------------------------------------
inline GUID ServerString2GUID(const std::wstring& str)
{
	GUID guid;
	swscanf_s(str.c_str(),
		L"{%8x%4hx%4hx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
		&guid.Data1, &guid.Data2, &guid.Data3,
		&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
		&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

	return guid;
}

//-----------------------------------------------------------------------------
inline std::wstring GUID2String(GUID guid)
{
	wchar_t guids[39];
	swprintf_s(
		guids, sizeof(guids) / sizeof(guids[0]),
		L"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	guids[sizeof(guids) / sizeof(guids[0]) - 1] = L'\0';

	return (std::wstring)guids;
}

//-----------------------------------------------------------------------------
inline std::wstring GUID2ServerString(GUID guid)
{
	wchar_t guids[33];
	swprintf_s(guids, sizeof(guids) / sizeof(guids[0]),
		L"%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	guids[sizeof(guids) / sizeof(guids[0]) - 1] = L'\0';

	return (std::wstring)guids;
}

////////////////////////////////////////////////////////////////////// Services
//

//-----------------------------------------------------------------------------
inline BOOL IsServiceInstalled(LPWSTR ServiceName, bool verbose = false)
{
	SC_HANDLE scm_handle = OpenSCManager(0, 0, SC_MANAGER_CONNECT);

	if (scm_handle == NULL)
	{
		if (verbose)
			echo(L"Service manager error");
		return FALSE;
	}

	SC_HANDLE service_handle = OpenService(scm_handle, ServiceName, SERVICE_INTERROGATE);
	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
			echo(L"Error opening the service");
		return FALSE;
	}

	CloseServiceHandle(scm_handle);
	CloseServiceHandle(service_handle);
	if (verbose)
		echo(L"Service is installed");

	return TRUE;
}

//-----------------------------------------------------------------------------
inline int GetServiceState(LPWSTR ServiceName, bool verbose = false)
{
	SC_HANDLE scm_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwBytesNeeded;

	if (scm_handle == NULL)
	{
		if (verbose)
			echo(L"Service manager error");
		return FALSE;
	}

	SC_HANDLE service_handle = OpenService(scm_handle, ServiceName, SERVICE_QUERY_STATUS);
	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
			echo(L"Error opening the service");
		return FALSE;
	}

	auto query = QueryServiceStatusEx(service_handle, SC_STATUS_PROCESS_INFO,
		reinterpret_cast<LPBYTE>(&ssStatus), sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded);

	CloseServiceHandle(scm_handle);
	CloseServiceHandle(service_handle);

	int result = (query == 0) ? 0 : ssStatus.dwCurrentState;
	if (verbose)
		echo(L"Service state code %d", result);

	return result;
}

//-----------------------------------------------------------------------------
inline BOOL ServiceInstall(LPWSTR ServiceName, LPWSTR installpath, DWORD servicetype, bool verbose = false)
{
	/*
		ServiceType
		0x00000004	SERVICE_ADAPTER				Reserved.
		0x00000002	SERVICE_FILE_SYSTEM_DRIVER	File system driver service.
		0x00000001	SERVICE_KERNEL_DRIVER		Driver service.
		0x00000008	SERVICE_RECOGNIZER_DRIVER	Reserved.
		0x00000010	SERVICE_WIN32_OWN_PROCESS	Service that runs in its own process.
		0x00000020	SERVICE_WIN32_SHARE_PROCESS	Service that shares a process with one or more other services.For more information, see Service Programs.
		0x00000050	SERVICE_USER_OWN_PROCESS	The service runs in its own process under the logged - on user account.
		0x00000060	SERVICE_USER_SHARE_PROCESS	The service shares a process with one or more other services that run under the logged - on user account.

		if SERVICE_WIN32_OWN_PROCESS or SERVICE_WIN32_SHARE_PROCESS can add:
		0x00000100	SERVICE_INTERACTIVE_PROCESS	The service can interact with the desktop.
		*/

	bool ServiceCreated = FALSE;
	int ServiceState = GetServiceState(ServiceName);

	if (ServiceState != 0)
	{
		if (verbose)
			echo(L"Service already exists");
		return ServiceCreated;
	}

	SC_HANDLE scm_handle = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

	if (scm_handle == NULL)
	{
		if (verbose)
			echo(L"Service manager error");
		return ServiceCreated;
	}

	SC_HANDLE service_handle = CreateService(scm_handle, ServiceName, ServiceName,
		SERVICE_ALL_ACCESS,
		servicetype,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		installpath,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
		{
			echo(L"Error creating the service:");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_CIRCULAR_DEPENDENCY:
				echo(L"ERROR_CIRCULAR_DEPENDENCY");
				break;
			case ERROR_DUPLICATE_SERVICE_NAME:
				echo(L"ERROR_DUPLICATE_SERVICE_NAME");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_INVALID_NAME:
				echo(L"ERROR_INVALID_NAME");
				break;
			case ERROR_INVALID_PARAMETER:
				echo(L"ERROR_INVALID_PARAMETER");
				break;
			case ERROR_INVALID_SERVICE_ACCOUNT:
				echo(L"ERROR_INVALID_SERVICE_ACCOUNT");
				break;
			case ERROR_SERVICE_EXISTS:
				echo(L"ERROR_SERVICE_EXISTS");
				break;
			case ERROR_SERVICE_MARKED_FOR_DELETE:
				echo(L"ERROR_SERVICE_MARKED_FOR_DELETE");
				break;
			}
		}
		return ServiceCreated;
	}

	CloseServiceHandle(service_handle);
	service_handle = OpenService(scm_handle, ServiceName, SERVICE_ALL_ACCESS);

	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
		{
			echo(L"Error opening the service:");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_INVALID_NAME:
				echo(L"ERROR_INVALID_NAME");
				break;
			case ERROR_SERVICE_DOES_NOT_EXIST:
				echo(L"ERROR_SERVICE_DOES_NOT_EXIST");
				break;
			}
		}
		return ServiceCreated;
	}

	CloseServiceHandle(scm_handle);
	CloseServiceHandle(service_handle);
	ServiceCreated = TRUE;
	if (verbose)
		echo(L"Service: %s is created", ServiceName);

	return ServiceCreated;
}

//-----------------------------------------------------------------------------
inline BOOL ServiceStart(LPWSTR ServiceName, bool verbose = false)
{
	SERVICE_STATUS_PROCESS ssp = { };
	int ServiceState = GetServiceState(ServiceName);

	if (ServiceState == 0)
	{
		if (verbose)
			echo(L"Service doesn't exists");
		return FALSE;
	}

	SC_HANDLE scm_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (scm_handle == NULL)
	{
		if (verbose)
		{
			echo(L"Service manager error");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_DATABASE_DOES_NOT_EXIST:
				echo(L"ERROR_DATABASE_DOES_NOT_EXIST");
				break;
			}
		}
		return FALSE;
	}

	SC_HANDLE service_handle = OpenService(scm_handle, ServiceName, SERVICE_START |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
		{
			echo(L"Error opening the service");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_INVALID_NAME:
				echo(L"ERROR_INVALID_NAME");
				break;
			case ERROR_SERVICE_DOES_NOT_EXIST:
				echo(L"ERROR_SERVICE_DOES_NOT_EXIST");
				break;
			}
		}
		return FALSE;
	}

	if (StartService(service_handle, 0, NULL) == NULL)
	{
		CloseServiceHandle(scm_handle);
		CloseServiceHandle(service_handle);
		if (verbose)
		{
			echo(L"Error starting the service:");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_PATH_NOT_FOUND:
				echo(L"ERROR_PATH_NOT_FOUND");
				break;
			case ERROR_SERVICE_ALREADY_RUNNING:
				echo(L"ERROR_SERVICE_ALREADY_RUNNING");
				break;
			case ERROR_SERVICE_DATABASE_LOCKED:
				echo(L"ERROR_SERVICE_DATABASE_LOCKED");
				break;
			case ERROR_SERVICE_DEPENDENCY_DELETED:
				echo(L"ERROR_SERVICE_DEPENDENCY_DELETED");
				break;
			case ERROR_SERVICE_DEPENDENCY_FAIL:
				echo(L"ERROR_SERVICE_DEPENDENCY_FAIL");
				break;
			case ERROR_SERVICE_DISABLED:
				echo(L"ERROR_SERVICE_DISABLED");
				break;
			case ERROR_SERVICE_LOGON_FAILED:
				echo(L"ERROR_SERVICE_LOGON_FAILED");
				break;
			case ERROR_SERVICE_MARKED_FOR_DELETE:
				echo(L"ERROR_SERVICE_MARKED_FOR_DELETE");
				break;
			case ERROR_SERVICE_NO_THREAD:
				echo(L"ERROR_SERVICE_NO_THREAD");
				break;
			case ERROR_SERVICE_REQUEST_TIMEOUT:
				echo(L"ERROR_SERVICE_REQUEST_TIMEOUT");
				break;
			}
		}
		return FALSE;
	}

	CloseServiceHandle(scm_handle);
	CloseServiceHandle(service_handle);
	if (verbose)
		echo(L"Service: %s started", ServiceName);

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL StopDependentServices(SC_HANDLE scm_handle, SC_HANDLE service_handle)
{
	DWORD i;
	DWORD dwBytesNeeded;
	DWORD dwCount;

	LPENUM_SERVICE_STATUS lpDependencies = NULL;
	ENUM_SERVICE_STATUS ess;
	SC_HANDLE hDepService;
	SERVICE_STATUS_PROCESS ssp = { };

	DWORD dwWaitTime = ssp.dwWaitHint / 10;
	unsigned long long dwStartTime = GetTickCount64();
	DWORD dwTimeout = 3000; // 3-second time-out

	//Pass a zero-length buffer to get the required buffer size.
	if (EnumDependentServices(service_handle, SERVICE_ACTIVE, lpDependencies, 0, &dwBytesNeeded, &dwCount))
	{
		//If the Enum call succeeds, then there are no dependent services, so do nothing.
		return TRUE;
	}
	else
	{
		if (GetLastError() != ERROR_MORE_DATA)
			return FALSE; // Unexpected error

		//Allocate a buffer for the dependencies.
		lpDependencies = (LPENUM_SERVICE_STATUS)HeapAlloc(
			GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded);

		if (!lpDependencies)
			return FALSE;

		__try
		{
			//Enumerate the dependencies.
			if (!EnumDependentServices(service_handle, SERVICE_ACTIVE, lpDependencies, dwBytesNeeded, &dwBytesNeeded, &dwCount))
				__leave;

			for (i = 0; i < dwCount; i++)
			{
				ess = *(lpDependencies + i);
				//Open the service.
				hDepService = OpenService(scm_handle,
					ess.lpServiceName,
					SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!hDepService)
					__leave;

				__try {
					//Send a stop code.
					if (!ControlService(hDepService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp))
						__leave;

					//Wait for the service to stop.
					while (ssp.dwCurrentState != SERVICE_STOPPED)
					{
						Sleep(dwWaitTime);
						if (!QueryServiceStatusEx(hDepService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
							__leave;

						if (ssp.dwCurrentState == SERVICE_STOPPED)
							break;

						if (GetTickCount64() - dwStartTime > dwTimeout)
							__leave;
					}
				}
				__finally
				{
					//Always release the service handle.
					CloseServiceHandle(hDepService);
				}
			}
		}
		__finally
		{
			//Always free the enumeration buffer.
			HeapFree(GetProcessHeap(), 0, lpDependencies);
		}
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL ServiceStop(LPWSTR ServiceName, bool verbose = false)
{
	SERVICE_STATUS_PROCESS ssp;
	int ServiceState = GetServiceState(ServiceName);

	if (ServiceState == 0)
	{
		if (verbose)
			echo(L"Service doesn't exists");
		return FALSE;
	}

	SC_HANDLE scm_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (scm_handle == NULL)
	{
		if (verbose)
		{
			echo(L"Service manager error");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_DATABASE_DOES_NOT_EXIST:
				echo(L"ERROR_DATABASE_DOES_NOT_EXIST");
				break;
			}
		}
		return FALSE;
	}

	SC_HANDLE service_handle = OpenService(scm_handle, ServiceName, SERVICE_STOP |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
		{
			echo(L"Error opening the service");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_INVALID_NAME:
				echo(L"ERROR_INVALID_NAME");
				break;
			case ERROR_SERVICE_DOES_NOT_EXIST:
				echo(L"ERROR_SERVICE_DOES_NOT_EXIST");
				break;
			}
		}
		return FALSE;
	}

	StopDependentServices(scm_handle, service_handle);

	if (ControlService(service_handle, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp) == NULL)
	{
		CloseServiceHandle(scm_handle);
		CloseServiceHandle(service_handle);
		if (verbose)
		{
			echo(L"Error stopping the service:");
			DWORD err = GetLastError();
			echo(L"%d", err);
		}
		return FALSE;
	}

	CloseServiceHandle(scm_handle);
	CloseServiceHandle(service_handle);
	if (verbose)
		echo(L"Service: %s stopped", ServiceName);

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL ServiceDelete(LPWSTR ServiceName, bool verbose = false)
{
	int ServiceState = GetServiceState(ServiceName);

	if (ServiceState == 0)
	{
		if (verbose)
			echo(L"Service doesn't exists");
		return FALSE;
	}

	ServiceStop(ServiceName, verbose);
	Sleep(500);

	SC_HANDLE scm_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (scm_handle == NULL)
	{
		if (verbose)
		{
			echo(L"Service manager error");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_DATABASE_DOES_NOT_EXIST:
				echo(L"ERROR_DATABASE_DOES_NOT_EXIST");
				break;
			}
		}
		return FALSE;
	}

	SC_HANDLE service_handle = OpenService(scm_handle, ServiceName, SERVICE_ALL_ACCESS);

	if (service_handle == NULL)
	{
		CloseServiceHandle(scm_handle);
		if (verbose)
		{
			echo(L"Error opening the service");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_INVALID_NAME:
				echo(L"ERROR_INVALID_NAME");
				break;
			case ERROR_SERVICE_DOES_NOT_EXIST:
				echo(L"ERROR_SERVICE_DOES_NOT_EXIST");
				break;
			}
		}
		return FALSE;
	}

	if (DeleteService(service_handle) == NULL)
	{
		CloseServiceHandle(scm_handle);
		CloseServiceHandle(service_handle);
		if (verbose)
		{
			echo(L"Error deleting the service:");
			DWORD err = GetLastError();
			switch (err)
			{
			case ERROR_ACCESS_DENIED:
				echo(L"ERROR_ACCESS_DENIED");
				break;
			case ERROR_INVALID_HANDLE:
				echo(L"ERROR_INVALID_HANDLE");
				break;
			case ERROR_SERVICE_MARKED_FOR_DELETE:
				echo(L"ERROR_SERVICE_MARKED_FOR_DELETE");
				break;
			}
		}
		return FALSE;
	}

	CloseServiceHandle(scm_handle);
	CloseServiceHandle(service_handle);
	if (verbose)
		echo(L"Service: %s deleted", ServiceName);

	return TRUE;
}

////////////////////////////////////////////////////////////////////// Devices
//

//-----------------------------------------------------------------------------
inline std::vector<std::wstring> ListofDriversByFile(bool verbose = false)
{
	LPVOID drivers[1024];
	DWORD cbNeeded;
	int cDrivers, i;
	std::vector<std::wstring> ListofDrivers;

	if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
	{
		WCHAR szDriver[1024];

		cDrivers = cbNeeded / sizeof(drivers[0]);

		_tprintf(TEXT("There are %d drivers:\n"), cDrivers);
		for (i = 0; i < cDrivers; i++)
		{
			if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0])))
			{
				ListofDrivers.push_back(szDriver);

				if (verbose)
					echo(L"%d: %s", i + 1, szDriver);
			}
		}
	}

	return ListofDrivers;
}

//-----------------------------------------------------------------------------
inline BOOL CheckForDriverByFile(LPWSTR DriverName, bool verbose = false)
{
	BOOL driverInstalled = FALSE;
	int i;
	std::vector<std::wstring> DriversList = ListofDriversByFile();

	for (i = 0; i < DriversList.size(); i++)
	{
		if (DriverName == DriversList[i])
		{
			driverInstalled = TRUE;
			if (verbose)
				echo(L"%s is installed", DriversList[i].c_str());
		}
	}

	return driverInstalled;
}

//-----------------------------------------------------------------------------
inline BOOL CheckForDriverById(LPWSTR DriverID, bool verbose = false)
{
	bool driverInstalled = FALSE;

	//	GUID dsGUID = { 0x745a17a0, 0x74d3, 0x11d0, {0xb6, 0xfe, 0x00, 0xa0, 0xc9, 0x0f, 0x57, 0xda} };
	//	PCWSTR DriverID = LR"(USB\VID_05E3&PID_0610)";
	//	PCWSTR DriverID = L"USB\\VID_05E3\&PID_0610";
	HDEVINFO hdevinfo = SetupDiGetClassDevsW(NULL, DriverID, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return driverInstalled;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	SP_DRVINFO_DATA_W drvdata;
	drvdata.cbSize = sizeof(SP_DRVINFO_DATA_W);

	DWORD DeviceIndex = 0;
	DWORD DeviceDataIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;
		if (SetupDiBuildDriverInfoList(hdevinfo, &devinfo, SPDIT_COMPATDRIVER))
		{
			DeviceDataIndex = 0;
			while (SetupDiEnumDriverInfoW(hdevinfo, &devinfo, SPDIT_COMPATDRIVER, DeviceDataIndex, &drvdata))
			{
				DeviceDataIndex++;
				if (verbose)
				{
					echo(L"Driver %d/%d found:", DeviceIndex, DeviceDataIndex);
					echo(L"   description: %ws", drvdata.Description);
					echo(L"   MfgName: %ws", drvdata.MfgName);
					echo(L"   ProviderName: %ws", drvdata.ProviderName);
				}
				driverInstalled = TRUE;
			}
		}
	}

	if (!driverInstalled)
	{
		if (verbose)
			echo(L"Device information not retreived: %u", GetLastError());
	}
	SetupDiDestroyDeviceInfoList(hdevinfo);

	return driverInstalled;
}

//-----------------------------------------------------------------------------
inline BOOL DeviceRestart(std::wstring DriverID)
{
	BOOL deviceRestarted = FALSE;

	HDEVINFO hdevinfo = SetupDiGetClassDevsW(NULL, DriverID.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

	if (hdevinfo == INVALID_HANDLE_VALUE)
		return deviceRestarted;

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		if (SetupDiBuildDriverInfoList(hdevinfo, &devinfo, SPDIT_COMPATDRIVER))
			if (SetupDiRestartDevices(hdevinfo, &devinfo))
				deviceRestarted = TRUE;
		DeviceIndex++;
	}

	SetupDiDestroyDeviceInfoList(hdevinfo);

	return deviceRestarted;
}
