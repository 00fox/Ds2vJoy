#pragma once
#include "stdafx.h"
#include "unzip.h"
#include <set>

/*
INDEX:
////////////////////////////////////////////////////////////////////// Convert
s	s2s		ws2s	rs2s	rws2s
c	s2c		ws2c	rs2c	rws2c
ws	s2ws	ws2w	rs2ws	rws2wss
wc	s2wc	ws2w	rs2wc	rws2wcc

int urlEncode(const char* toencode, const int strSize, char* encoded, const int resultSize)
std::string urlDecode(std::string& src)

////////////////////////////////////////////////////////////////////// Replace
BOOL FindInStdString(std::string stringin, std::string findwhat, int begin = 0, int length = 0)
BOOL FindInStdString(wchar_t* stringin, std::string findwhat, int begin = 0, int length = 0)
std::string SubString(std::string stringin, int begin = 0, int length = 0)
std::string SubString(wchar_t* stringin, int begin = 0, int length = 0)
std::string SubString(std::string stringin, std::string findwhat, int totheend = 0, int stringincluded = 0)
std::string SubString(wchar_t* stringin, std::string findwhat, int totheend = 0, int stringincluded = 0)
BOOL isInList(std::set<int> list, int element)
BOOL LastCharis(std::string stringin, std::string findwhat)
std::string ReplaceInStdString(std::string stringin, std::string replwhat, char replfor)
std::wstring ReplaceInStdwString(std::wstring stringin, std::string replwhat, char replfor)

////////////////////////////////////////////////////////////////////// Ressources
BOOL isFileExists(const std::string& name)
BOOL WriteToFile(	char* filename,			std::string string,		bool binary = false, bool overwrite = false)
BOOL WriteToFile(	wchar_t* filename,		char* string,			DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL WriteToFile(	wchar_t* filename,		std::vector<char> data,	DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL WriteToFile(	std::wstring filename,	char* string,			DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL WriteToFile(	std::wstring filename,	std::vector<char> data, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL WriteToFile(	wchar_t* filename,		VOID* lockedResssource, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL WriteToFile(	std::wstring filename,	VOID* lockedResssource, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
BOOL CreateDirectoryRecurse(const std::wstring& directory, bool hidden = false)
int DeleteDirectory(const std::string& directory, bool recurse = true)
std::vector<char> LoadEmbeddedResource(LPCTSTR name)
BOOL WriteEmbededResource(std::wstring filename, WORD resourceID, bool overwrite = true, bool hidden = false)
BOOL ExtractEmbededResource(std::wstring location, WORD resourceID, bool overwrite = true, bool forcehidden = false)
void ForceRemoveModule(LPCTSTR ModuleName, bool deletedll = false)

////////////////////////////////////////////////////////////////////// Diverse
std::string WinPath()
std::wstring WinPathW()
std::string ExePath()
std::wstring ExePathW()
std::string TmpPath()
std::wstring TmpPathW()
std::string PrfPath()
std::wstring PrfPathW()
BOOL LaunchProcess(LPWSTR lpCommandLine, bool wait = false)
std::string LaunchCmd(const char* cmd)
BOOL ClientArea(RECT* rect, bool points = false)	//x, y, w, h, true x, y, x', y'
int MessageBoxPos(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, int x, int y)
void CreateToolTip(HWND hWndParent, HWND hControlItem, PTSTR tooltipText)

////////////////////////////////////////////////////////////////////// Process
BOOL IsWow64()
DWORD GetPIDByName(std::wstring ProcessName)
TCHAR* GetExeNameByPID(DWORD ProcessID)

////////////////////////////////////////////////////////////////////// GUID
GUID StringToGUID(const std::string& str)
GUID WStringToGUID(const std::wstring& str)
GUID ServerStringToGUID(const std::string& str)
GUID ServerWStringToGUID(const std::wstring& str)
std::string GUIDToString(GUID guid)
std::string GUIDToServerString(GUID guid)
std::wstring GUIDToWString(GUID* guid)
std::wstring GUIDToSymbolServerWString(GUID* guid)

////////////////////////////////////////////////////////////////////// Services
BOOL IsServiceInstalled(LPWSTR ServiceName)
int GetServiceState(LPWSTR ServiceName)
BOOL ServiceInstall(LPWSTR ServiceName, LPWSTR installpath, DWORD servicetype, bool verbose = false)
BOOL ServiceStart(LPWSTR ServiceName, bool verbose = false)
BOOL StopDependentServices(SC_HANDLE scm_handle, SC_HANDLE service_handle)
BOOL ServiceStop(LPWSTR ServiceName, bool verbose = false)
BOOL ServiceDelete(LPWSTR ServiceName, bool verbose = false)

////////////////////////////////////////////////////////////////////// Devices
std::vector<std::wstring> ListofDriversByFile(bool verbose = false)
BOOL CheckForDriverByFile(LPWSTR DriverName, bool verbose = false)
BOOL CheckForDriverById(LPWSTR DriverID, bool verbose = false)
BOOL DeviceRestart(LPWSTR BaseName, bool verbose = false)
BOOL DeviceRestart2(LPWSTR BaseName, bool verbose = false)
*/

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////// Convert
// 
//-----------------------------------------------------------------------------
inline BOOL s2s(char* s, std::string* o)
{
	const int len = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	if (len <= 1)
		return FALSE;

	std::string out = std::string(s);
	*o = out;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL s2s(std::string s, std::string* o)
{
	return s2s((char*)s.c_str(), o);
}

//-----------------------------------------------------------------------------
inline BOOL s2c(char* s, char** o)
{
	const int len = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	if (len <= 1)
		return FALSE;

	char* tmp = new char[MAX_PATH];
	strcpy_s(tmp, MAX_PATH, s);
	*o = tmp;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL s2c(std::string s, char** o)
{
	return s2c((char*)s.c_str(), o);
}

//-----------------------------------------------------------------------------
inline BOOL s2ws(char* s, std::wstring* ws)
{
	const int len = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	if (len <= 1)
		return FALSE;

	std::string tmp = std::string(s);
	std::wstring out(tmp.begin(), tmp.end());
	*ws = out;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL s2ws(std::string s, std::wstring* ws)
{
	return s2ws((char*)s.c_str(), ws);
}

//-----------------------------------------------------------------------------
inline BOOL s2wc(char* s, wchar_t** wo)
{
	const int len = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	if (len <= 1)
		return FALSE;

	const size_t cSize = strlen(s) + 1;
	wchar_t* tmp = new wchar_t[cSize];
	size_t* pReturnValue = 0;
	mbstowcs_s(pReturnValue, tmp, MAX_PATH, s, cSize);

	*wo = tmp;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL s2wc(std::string s, wchar_t** wo)
{
	return s2wc((char*)s.c_str(), wo);
}

//-----------------------------------------------------------------------------
inline BOOL ws2s(wchar_t* ws, std::string* s)
{
	if (0 == ws || 0 == ws[0])
		return FALSE;

	std::wstring tmp = std::wstring(ws);
	std::string out(tmp.begin(), tmp.end());
	*s = out;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL ws2s(std::wstring ws, std::string* s)
{
	return ws2s((wchar_t*)ws.c_str(), s);
}

//-----------------------------------------------------------------------------
inline BOOL ws2c(wchar_t* ws, char** s)
{
	if (0 == ws || 0 == ws[0])
		return FALSE;

	const size_t cSize = wcslen(ws) + 1;
	char* out = new char[MAX_PATH];
	size_t* pReturnValue = 0;
	wcstombs_s(pReturnValue, out, MAX_PATH, ws, cSize);

	*s = out;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL ws2c(std::wstring ws, char** s)
{
	return ws2c((wchar_t*)ws.c_str(), s);
}

//-----------------------------------------------------------------------------
inline BOOL ws2ws(wchar_t* ws, std::wstring* wo)
{
	if (0 == ws || 0 == ws[0])
		return FALSE;

	std::wstring out = std::wstring(ws);
	*wo = out;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL ws2ws(std::wstring ws, std::wstring* wo)
{
	return ws2ws((wchar_t*)ws.c_str(), wo);
}

//-----------------------------------------------------------------------------
inline BOOL ws2wc(wchar_t* ws, wchar_t** wo)
{
	if (0 == ws || 0 == ws[0])
		return FALSE;

	wchar_t* tmp = new wchar_t[MAX_PATH];
	wcscpy_s(tmp, MAX_PATH, ws);
	*wo = tmp;

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL ws2wc(std::wstring ws, wchar_t** wo)
{
	return ws2wc((wchar_t*)ws.c_str(), wo);
}


//-----------------------------------------------------------------------------
inline std::string rs2s(char* s)
{
	std::string o = "";
	s2s(s, &o);
	return o;
}

//-----------------------------------------------------------------------------
inline std::string rs2s(std::string s)
{
	return rs2s((char*)s.c_str());
}

//-----------------------------------------------------------------------------
inline char* rs2c(char* s)
{
	char* o = "";
	s2c(s, &o);
	return o;
}

//-----------------------------------------------------------------------------
inline char* rs2c(std::string s)
{
	return rs2c((char*)s.c_str());
}

//-----------------------------------------------------------------------------
inline std::wstring rs2ws(char* s)
{
	std::wstring ws = L"";
	s2ws(s, &ws);
	return ws;
}

//-----------------------------------------------------------------------------
inline std::wstring rs2ws(std::string s)
{
	return rs2ws((char*)s.c_str());
}

//-----------------------------------------------------------------------------
inline wchar_t* rs2wc(char* s)
{
	wchar_t* wo = L"";
	s2wc(s, &wo);
	return wo;
}

//-----------------------------------------------------------------------------
inline wchar_t* rs2wc(std::string s)
{
	return rs2wc((char*)s.c_str());
}

//-----------------------------------------------------------------------------
inline std::string rws2s(wchar_t* ws)
{
	std::string s = "";
	ws2s(ws, &s);
	return s;
}

//-----------------------------------------------------------------------------
inline std::string rws2s(std::wstring ws)
{
	return rws2s((wchar_t*)ws.c_str());
}

//-----------------------------------------------------------------------------
inline char* rws2c(wchar_t* ws)
{
	char* s = "";
	ws2c(ws, &s);
	return s;
}

//-----------------------------------------------------------------------------
inline char* rws2c(std::wstring ws)
{
	return rws2c((wchar_t*)ws.c_str());
}

//-----------------------------------------------------------------------------
inline std::wstring rws2ws(wchar_t* ws)
{
	std::wstring wo = L"";
	ws2ws(ws, &wo);
	return wo;
}

//-----------------------------------------------------------------------------
inline std::wstring rws2ws(std::wstring ws)
{
	return rws2ws((wchar_t*)ws.c_str());
}

//-----------------------------------------------------------------------------
inline wchar_t* rws2wc(wchar_t* ws)
{
	wchar_t* wo = L"";
	ws2wc(ws, &wo);
	return wo;
}

//-----------------------------------------------------------------------------
inline wchar_t* rws2wc(std::wstring ws)
{
	return rws2wc((wchar_t*)ws.c_str());
}

//-----------------------------------------------------------------------------
inline void checkconv()
{
	std::string test = "ok";

	echo(L"");
	std::string rtest;
	if (s2s((char*)test.c_str(), &rtest))
		echo("c2s %s", rtest.c_str());
	if (s2s(test, &rtest))
		echo("s2s %s", rtest.c_str());
	echo("rs2s %s", rs2s((char*)test.c_str()).c_str());
	echo("rs2s %s", rs2s(test).c_str());

	echo(L"");
	char* rctest = "";
	if (s2c((char*)test.c_str(), &rctest))
		echo("c2c %s", rctest);
	if (s2c(test, &rctest))
		echo("s2c %s", rctest);
	echo("rc2c %s", rs2c((char*)test.c_str()));
	echo("rs2c %s", rs2c(test));

	echo(L"");
	std::wstring rwtest;
	if (s2ws((char*)test.c_str(), &rwtest))
		echo(L"c2ws %s", rwtest.c_str());
	if (s2ws(test, &rwtest))
		echo(L"s2ws %s", rwtest.c_str());
	echo(L"rs2ws %s", rs2ws((char*)test.c_str()));
	echo(L"rs2ws %s", rs2ws(test).c_str());

	echo(L"");
	wchar_t* rwctest = L"";
	if (s2wc((char*)test.c_str(), &rwctest))
		echo(L"c2wc %s", rwctest);
	if (s2wc(test, &rwctest))
		echo(L"s2wc %s", rwctest);
	echo(L"rc2wc %s", rs2wc((char*)test.c_str()));
	echo(L"rs2wc %s", rs2wc(test));

	echo(L"");
	rtest = "";
	if (ws2s((wchar_t*)rwtest.c_str(), &rtest))
		echo("wc2s %s", rtest.c_str());
	if (ws2s(rwtest, &rtest))
		echo("ws2s %s", rtest.c_str());
	echo("rwc2s %s", rws2s((wchar_t*)rwtest.c_str()).c_str());
	echo("rws2s %s", rws2s(rwtest).c_str());

	echo(L"");
	rctest = "";
	if (ws2c((wchar_t*)rwtest.c_str(), &rctest))
		echo("wc2c %s", rctest);
	if (ws2c(rwtest, &rctest))
		echo("ws2c %s", rctest);
	echo("rwc2c %s", rws2c((wchar_t*)rwtest.c_str()));
	echo("rws2c %s", rws2c(rwtest));

	echo(L"");
	std::wstring rrwtest = L"";
	if (ws2ws((wchar_t*)rwtest.c_str(), &rrwtest))
		echo(L"wc2ws %s", rrwtest);
	if (ws2ws(rwtest, &rrwtest))
		echo(L"ws2ws %s", rrwtest);
	echo(L"rwc2ws %s", rws2ws((wchar_t*)rwtest.c_str()));
	echo(L"rws2ws %s", rws2ws(rwtest));

	echo(L"");
	rwctest = L"";
	if (ws2wc((wchar_t*)rwtest.c_str(), &rwctest))
		echo(L"wc2wc %s", rwctest);
	if (ws2wc(rwtest, &rwctest))
		echo(L"ws2wc %s", rwctest);
	echo(L"rwc2wc %s", rws2wc((wchar_t*)rwtest.c_str()));
	echo(L"rws2wc %s", rws2wc(rwtest));

	echo(L"");
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
		//else if ( ch == ' ' )
		//{
		//	encoded[ j ++ ] = '+';
		//}
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
				sprintf_s(encoded + j, resultSize - j, "%%%02X", (unsigned char)ch);
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
	int i, ii;
	for (i = 0; i < src.length(); i++)
	{
		if (int(src[i]) == 37)
		{
			sscanf_s(src.substr(i + 1, 2).c_str(), "%x", &ii);
			ch = static_cast<char>(ii);
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
inline BOOL FindInStdString(std::string stringin, std::string findwhat, int begin = 0, int length = 0)
// begin < 0 : from string total lenght - begin
// length < 0 : start at begin - length caracters
{
	if (begin || length)
	{
		int strlength = (int)stringin.length();
		int begintmp = 0;
		int endtmp = strlength;

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

		std::string stringintmp = stringin.substr(begintmp, endtmp - begintmp);
		if (stringintmp.find(findwhat) != std::string::npos)
			return TRUE;
	}
	else if (stringin.find(findwhat) != std::string::npos)
		return TRUE;

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL FindInStdString(wchar_t* stringin, std::string findwhat, int begin = 0, int length = 0)
// begin < 0 : from string total lenght - begin
// length < 0 : start at begin - length caracters
{
	return FindInStdString(rws2s(stringin), findwhat, begin , length);
}

//-----------------------------------------------------------------------------
inline std::string SubString(std::string stringin, int begin = 0, int length = 0)
// begin < 0 : from string total lenght - begin
// length < 0 : start at begin - length caracters
{
	if (begin || length)
	{
		int strlength = (int)stringin.length();
		int begintmp = 0;
		int endtmp = strlength;

		if (length < 0)
		{
			endtmp = (begin < 0) ? ((int)stringin.length() + begin) : begin;
			if (endtmp < 0)
				return "";
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
inline std::string SubString(wchar_t* stringin, int begin = 0, int length = 0)
// begin < 0 : from string total lenght - begin
// length < 0 : start at begin - length caracters
{
	return SubString(rws2s(stringin), begin, length);
}

//-----------------------------------------------------------------------------
inline std::string SubString(std::string stringin, std::string findwhat, int totheend = 0, int stringincluded = 0)
{
	std::string result = "";
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
inline std::string SubString(wchar_t* stringin, std::string findwhat, int totheend = 0, int stringincluded = 0)
{
	return SubString(rws2s(stringin), findwhat, totheend, stringincluded);
}

//-----------------------------------------------------------------------------
inline BOOL isInList(std::set<int> list, int element)
{
//	return (std::find(list.begin(), list.end(), element) != list.end());
	return list.count(element) != 0;
}

//-----------------------------------------------------------------------------
inline BOOL LastCharis(std::string stringin, std::string findwhat)
{
	if (stringin.empty())
		return FALSE;

	std::size_t found = stringin.find_last_of(findwhat);
	if (stringin.length() == found + 1)
		return TRUE;

	return FALSE;
}

//-----------------------------------------------------------------------------
inline std::string ReplaceInStdString(std::string stringin, std::string replwhat, char replfor)
{
	std::size_t found = stringin.find_first_of(replwhat);

	while (found != std::string::npos)
	{
		stringin[found] = replfor;
		found = stringin.find_first_of(replwhat, found + 1);
	}

	return stringin;
}

//-----------------------------------------------------------------------------
inline std::wstring ReplaceInStdwString(std::wstring stringin, std::string replwhat, char replfor)
{
	std::string stringin8 = rws2s(stringin);
	std::size_t found = stringin8.find_first_of(replwhat);

	while (found != std::string::npos)
	{
		stringin8[found] = replfor;
		found = stringin8.find_first_of(replwhat, found + 1);
	}
	stringin = rs2ws(stringin8);

	return stringin;
}

////////////////////////////////////////////////////////////////////// Resources

//-----------------------------------------------------------------------------
inline BOOL isFileExists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(char* filename, std::string string, bool binary = false, bool overwrite = true)
{
	if (isFileExists(filename))
		if (!overwrite)
			return FALSE;
	std::ofstream out;
	if (binary)
		out.open(filename, std::ios_base::out | std::ios_base::binary);
	else
		out.open(filename, std::ios_base::out);
	out << string;
	out.close();

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(wchar_t* filename, char* string, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	DWORD dwCreationDisposition = (overwrite) ? CREATE_ALWAYS : CREATE_NEW;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL | ((hidden) ? FILE_ATTRIBUTE_HIDDEN : 0);

	HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD writ; BOOL bres = WriteFile(hFile, string, BytesToWrite, &writ, NULL);
		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(wchar_t* filename, std::vector<char> data, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	char* buffer = reinterpret_cast<char*> (&data[0]);

	return WriteToFile(filename, buffer, BytesToWrite, overwrite, hidden);
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(std::wstring filename, char* string, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	return WriteToFile((TCHAR*)filename.c_str(), string, BytesToWrite, overwrite, hidden);
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(std::wstring filename, std::vector<char> data, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	return WriteToFile((TCHAR*)filename.c_str(), data, BytesToWrite, overwrite, hidden);
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(wchar_t* filename, VOID* lockedResssource, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	DWORD dwCreationDisposition = (overwrite) ? CREATE_ALWAYS : CREATE_NEW;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL | ((hidden) ? FILE_ATTRIBUTE_HIDDEN : 0);

	HANDLE hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, BytesToWrite, NULL);	//PAGE_EXECUTE_READWRITE
		LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		CopyMemory(lpAddress, lockedResssource, BytesToWrite);
		UnmapViewOfFile(lpAddress);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		FreeResource(lockedResssource);
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL WriteToFile(std::wstring filename, VOID* lockedResssource, DWORD BytesToWrite, bool overwrite = true, bool hidden = false)
{
	return WriteToFile((TCHAR*)filename.c_str(), lockedResssource, BytesToWrite, overwrite, hidden);
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
inline BOOL LoadEmbeddedResource(WORD resourceID, std::vector<char>* output, DWORD* resourceSize)
{
	std::vector<char> outputtmp;

	// If you need to retrieve resources embedded in a binary that is not the current running program, modify this
	// function to pass in a HMODULE value.
	HMODULE module = nullptr;

	auto resourceHandle = ::FindResource(module, MAKEINTRESOURCE(resourceID), RT_RCDATA);

	if (resourceHandle != nullptr)
	{
		auto dataHandle = ::LoadResource(module, resourceHandle);

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
					// on why the call is not needed:
					// https://msdn.microsoft.com/en-us/library/windows/desktop/ms648044%28v=vs.85%29.aspx
				}
			}
		}
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL LoadEmbeddedResource(WORD resourceID, VOID** output, DWORD* resourceSize)
{
	std::vector<char> outputtmp;

	// If you need to retrieve resources embedded in a binary that is not the current running program, modify this
	// function to pass in a HMODULE value.
	HMODULE module = nullptr;

	auto resourceHandle = ::FindResource(module, MAKEINTRESOURCE(resourceID), RT_RCDATA);

	if (resourceHandle != nullptr)
	{
		auto dataHandle = ::LoadResource(module, resourceHandle);

		if (dataHandle != nullptr)
		{
			auto resourceSizetmp = ::SizeofResource(module, resourceHandle);
			*resourceSize = resourceSizetmp;

			if (resourceSizetmp != 0)
			{
				auto firstByte = reinterpret_cast<const char*>(::LockResource(dataHandle));

				if (firstByte != nullptr)
				{
					*output = LockResource(dataHandle);

					FreeResource(dataHandle);
					return TRUE;

					// No need to call ::FreeResource on any 32 or 64 bit version of Windows. See MSDN for details
					// on why the call is not needed:
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
		DWORD ressourceWrinten; WriteToFile(filename, data, resourceSize, overwrite, hidden);
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
			filename = ReplaceInStdwString(filename, "\\", '/');
			if (LastCharis(rws2s(filename), "/"))
				filename = filename + ze.name;
			else
				filename = filename + L"/" + ze.name;
			filename = ReplaceInStdwString(filename, "\\", '/');

			if (LastCharis(rws2s(filename), "/"))
				CreateDirectoryRecurse(filename, forcehidden);
			else
			{
				//	UnzipItem(hz, zi, (TCHAR*)filename.c_str());
				HANDLE h;
				DWORD dwCreationDisposition = (overwrite) ? CREATE_ALWAYS : CREATE_NEW;
				DWORD dwFlagsAndAttributes = ze.attr | ((forcehidden) ? FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_HIDDEN : 0);

				h = CreateFile((TCHAR*)filename.c_str(), GENERIC_WRITE, 0, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
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
	if (deletedll)
		::DeleteFile(ModuleName);
}

////////////////////////////////////////////////////////////////////// Diverse
// 
//-----------------------------------------------------------------------------
inline std::string WinPath()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	GetWindowsDirectory(buffer, MAX_PATH);

	return rws2s(buffer);
}

//-----------------------------------------------------------------------------
inline std::wstring WinPathW()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	GetWindowsDirectory(buffer, MAX_PATH);

	return buffer;
}

//-----------------------------------------------------------------------------
inline std::string ExePath()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	
	std::wstring tmp = std::wstring(buffer).substr(0, pos);

	return rws2s(tmp);
}

//-----------------------------------------------------------------------------
inline std::wstring ExePathW()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

	return std::wstring(buffer).substr(0, pos);
}

//-----------------------------------------------------------------------------
inline std::string TmpPath()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	GetTempPathW(MAX_PATH, buffer);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

	std::wstring tmp = std::wstring(buffer).substr(0, pos);

	return rws2s(tmp);
}

//-----------------------------------------------------------------------------
inline std::wstring TmpPathW()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	GetTempPathW(MAX_PATH, buffer);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

	return std::wstring(buffer).substr(0, pos);
}

//-----------------------------------------------------------------------------
inline std::string PrfPath(bool x86test = false)
{
	wchar_t* buffer;
	size_t numberOfElements = 1024;

	if (x86test)
	{
		_wdupenv_s(&buffer, &numberOfElements, L"ProgramFiles(x86)");
		if (buffer == NULL)
			return PrfPath(false);
	}
	else
		_wdupenv_s(&buffer, &numberOfElements, L"ProgramFiles");

	return rws2s(buffer);
}

//-----------------------------------------------------------------------------
inline std::wstring PrfPathW(bool x86test = false)
{
	wchar_t* buffer;
	size_t numberOfElements;

	if (x86test)
	{
		_wdupenv_s(&buffer, &numberOfElements, L"ProgramFiles(x86)");
		if (buffer == NULL)
			return PrfPathW(false);
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
inline std::string LaunchCmd(const char* cmd)
{
	HWND hCurWnd = ::GetForegroundWindow();

	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);

	if (!pipe)
		return "WindowsTools.h LaunchCmd popen() failed!";
	while (fgets(buffer.data(), (int)buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();

	::SetForegroundWindow(hCurWnd);
	::SetFocus(hCurWnd);
	return result;
}

//-----------------------------------------------------------------------------
static thread_local int MsgBox_x = 0;
static thread_local int MsgBox_y = 0;
static bool MsgBox_start = false;

inline LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_CREATEWND && MsgBox_start == true)
	{
		MsgBox_start = false;
		CBT_CREATEWND* s = (CBT_CREATEWND*)lParam;
		s->lpcs->x = MsgBox_x;
		s->lpcs->y = MsgBox_y;
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

inline int MessageBoxPos(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, int x, int y)
{
	MsgBox_start = true;
	HHOOK hHook = SetWindowsHookEx(WH_CBT, &CBTProc, NULL, GetCurrentThreadId());
	MsgBox_x = x;
	MsgBox_y = y;
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

	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hWndParent;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hControlItem;
	toolInfo.lpszText = tooltipText;

	if (!SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo))
		MessageBox(0, TEXT("TTM_ADDTOOL failed\nWrong project manifest!"), 0, 0);
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
inline TCHAR* GetExeNameByPID(DWORD ProcessID)
{
	TCHAR* ProcessName = TEXT("<unknown>");
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ProcessID);

	if (hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, ProcessName, sizeof(ProcessName) / sizeof(TCHAR));
		}
		CloseHandle(hProcess);
	}

	return ProcessName;
}

////////////////////////////////////////////////////////////////////// GUID
// 
//-----------------------------------------------------------------------------
inline GUID StringToGUID(const std::string& str)
{
	GUID guid;
	sscanf_s(str.c_str(),
		"{%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
		&guid.Data1, &guid.Data2, &guid.Data3,
		&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
		&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

	return guid;
}

//-----------------------------------------------------------------------------
inline GUID WStringToGUID(const std::wstring& str)
{
	GUID guid;
	swscanf_s(str.c_str(),
		L"{%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
		&guid.Data1, &guid.Data2, &guid.Data3,
		&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
		&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

	return guid;
}

//-----------------------------------------------------------------------------
inline GUID ServerStringToGUID(const std::string& str)
{
	GUID guid;
	sscanf_s(str.c_str(),
		"{%8x%4hx%4hx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
		&guid.Data1, &guid.Data2, &guid.Data3,
		&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
		&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

	return guid;
}

//-----------------------------------------------------------------------------
inline GUID ServerWStringToGUID(const std::wstring& str)
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
inline std::string GUIDToString(GUID guid)
{
	char guid_cstr[39];
	snprintf(guid_cstr, sizeof(guid_cstr),
		"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return (std::string)guid_cstr;
}

//-----------------------------------------------------------------------------
inline std::string GUIDToServerString(GUID guid)
{
	char guid_cstr[33];
	snprintf(guid_cstr, sizeof(guid_cstr),
		"%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return (std::string)guid_cstr;
}

//-----------------------------------------------------------------------------
inline std::wstring GUIDToWString(GUID* guid)
{
	wchar_t guid_string[39];
	swprintf(
		guid_string, sizeof(guid_string) / sizeof(guid_string[0]),
		L"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2],
		guid->Data4[3], guid->Data4[4], guid->Data4[5],
		guid->Data4[6], guid->Data4[7]);

	// remove when VC++7.1 is no longer supported
	guid_string[sizeof(guid_string) / sizeof(guid_string[0]) - 1] = L'\0';

	return (std::wstring)guid_string;
}

//-----------------------------------------------------------------------------
inline std::wstring GUIDToSymbolServerWString(GUID* guid)
{
	wchar_t guid_string[33];
	swprintf(
		guid_string, sizeof(guid_string) / sizeof(guid_string[0]),
		L"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2],
		guid->Data4[3], guid->Data4[4], guid->Data4[5],
		guid->Data4[6], guid->Data4[7]);

	// remove when VC++7.1 is no longer supported
	guid_string[sizeof(guid_string) / sizeof(guid_string[0]) - 1] = L'\0';

	return (std::wstring)guid_string;
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
	ULONGLONG dwStartTime = GetTickCount64();
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
				return FALSE;

			for (i = 0; i < dwCount; i++)
			{
				ess = *(lpDependencies + i);
				//Open the service.
				hDepService = OpenService(scm_handle,
					ess.lpServiceName,
					SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!hDepService)
					return FALSE;

				__try {
					//Send a stop code.
					if (!ControlService(hDepService,
						SERVICE_CONTROL_STOP,
						(LPSERVICE_STATUS)&ssp))
						return FALSE;

					//Wait for the service to stop.
					while (ssp.dwCurrentState != SERVICE_STOPPED)
					{
						Sleep(dwWaitTime);
						if (!QueryServiceStatusEx(
							hDepService,
							SC_STATUS_PROCESS_INFO,
							(LPBYTE)&ssp,
							sizeof(SERVICE_STATUS_PROCESS),
							&dwBytesNeeded))
							return FALSE;

						if (ssp.dwCurrentState == SERVICE_STOPPED)
							break;

						if (GetTickCount() - dwStartTime > dwTimeout)
							return FALSE;
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
		TCHAR szDriver[1024];

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
inline BOOL DeviceRestartW(LPWSTR DriverID, bool verbose = false)
{
	BOOL deviceRestarted = FALSE;

	HDEVINFO hdevinfo = SetupDiGetClassDevsW(NULL, DriverID, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return deviceRestarted;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;
		if (SetupDiBuildDriverInfoList(hdevinfo, &devinfo, SPDIT_COMPATDRIVER))
		{
			if (SetupDiRestartDevices(hdevinfo, &devinfo))
			{
				deviceRestarted = TRUE;
			}
		}
	}

	if (verbose)
		if (deviceRestarted)
		{
			echo(L"Device %s restarted", DriverID);
		}
		else
		{
			echo(L"Device %s not restarted: %u", DriverID, GetLastError());
		}
	SetupDiDestroyDeviceInfoList(hdevinfo);

	return deviceRestarted;
}

//-----------------------------------------------------------------------------
inline BOOL DeviceRestart(std::string DriverID, bool verbose = false)
{
	std::wstring tmp1 = rs2ws(DriverID);
	LPWSTR tmp2 = (LPWSTR)tmp1.c_str();

	return DeviceRestartW(tmp2, verbose);
}