#pragma once

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
HRESULT			SaveBitmap(std::wstring filename, HBITMAP bitmap, std::wstring format = L"png")

////////////////////////////////////////////////////////////////////// Diverse
std::wstring	WinPath()
std::wstring	ExePath()
std::wstring	TmpPath()
std::wstring	PrfPath()
BOOL			LaunchProcess(LPCWSTR lpCommandLine, bool wait = false)
std::wstring	LaunchCmd(const wchar_t* cmd)
BOOL			ClientArea(RECT* rect, bool points = false)	//x, y, w, h, true x, y, x', y'
int				MessageBoxPos(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, int x, int y, int wrap = 0)
void			TextInputDialog(HWND parent, PCWSTR title, PCWSTR prompt, PCWSTR description, const std::wstring& defaultInput = L"", bool readOnly = false)
void			CreateToolTip(HWND hWndParent, HWND hControlItem, PTSTR tooltipText)
void			SetWindowTransparent(HWND hwnd, bool bTransparent, int nTransparency)
unsigned int	GetCursorType()
HRESULT			ScreenCapturePart(int x, int y, int z, int t, std::wstring filename, bool scaling = true)
BOOL			SetMagnifyZoom(unsigned char method, float factor, int pointx = 0, int pointy = 0)
BOOL			MagSetColor(char magnifyColor = 0)

////////////////////////////////////////////////////////////////////// Process
BOOL			IsWow64()
DWORD			GetPIDByName(std::wstring ProcessName)
WCHAR*			GetExeNameByPID(DWORD ProcessID)
BOOL			uSleep(__int64 usec)

////////////////////////////////////////////////////////////////////// GUID
GUID			String2GUID(const std::wstring& str)
GUID			ServerString2GUID(const std::wstring& str)
std::wstring	GUID2String(GUID guid)
std::wstring	GUID2ServerString(GUID guid)

////////////////////////////////////////////////////////////////////// Services
BOOL			IsServiceInstalled(LPCWSTR ServiceName)
int				GetServiceState(LPCWSTR ServiceName)
BOOL			ServiceInstall(LPCWSTR ServiceName, LPCWSTR installpath, DWORD servicetype, bool verbose = false)
BOOL			ServiceStart(LPCWSTR ServiceName, bool verbose = false)
BOOL			StopDependentServices(SC_HANDLE scm_handle, SC_HANDLE service_handle)
BOOL			ServiceStop(LPCWSTR ServiceName, bool verbose = false)
BOOL			ServiceDelete(LPCWSTR ServiceName, bool verbose = false)

////////////////////////////////////////////////////////////////////// Devices
std::vector<std::wstring> ListofDriversByFile(bool verbose = false)
BOOL			CheckForDriverByFile(LPCWSTR DriverName, bool verbose = false)
BOOL			CheckForDriverByGUID(std::wstring enumerator, GUID guid, bool verbose = false)
BOOL			CheckForDriverById(std::wstring enumerator, std::wstring MfgName, std::wstring Description, bool verbose = false)
BOOL			CheckForDriverByHwId(std::wstring enumerator, std::wstring hwid, bool verbose = false)
std::wstring	GetDriverHwIdByGUID(std::wstring enumerator, GUID guid, bool verbose = false)
std::wstring	GetDriverHwIdById(std::wstring enumerator, std::wstring MfgName, std::wstring Description, bool verbose = false)
std::vector<int>	GetDeviceError(std::wstring enumerator, std::wstring hwid, bool verbose = false)
char			GetDeviceState(std::wstring enumerator, std::wstring hwid, bool verbose = false)
BOOL			SetDeviceState(std::wstring enumerator, std::wstring hwid, DWORD dwState, bool verbose = false)
BOOL			RemoveDriverById(std::wstring enumerator, std::wstring MfgName, std::wstring Description, bool verbose = false)
BOOL			RemoveDriverByHwId(std::wstring enumerator, std::wstring hwid, bool verbose = false)
BOOL			DeviceRestart(std::wstring enumerator, std::wstring hwid, bool tohide = true, bool verbose = false)
BOOL			DeviceUpdate(std::wstring lpFileName, std::wstring hwid)
BOOL			InstallDriverByHwId(std::wstring lpFileName, std::wstring hwid)
int				UpperClassFilter(std::wstring cf_class, std::wstring cf_driver)
*/

////////////////////////////////////////////////////////////////////// Utilisation
// GetCursorType
#define OCR_HELP 32651
static HANDLE Cur_NORMAL = LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_IBEAM = LoadImage(NULL, MAKEINTRESOURCE(OCR_IBEAM), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_WAIT = LoadImage(NULL, MAKEINTRESOURCE(OCR_WAIT), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_CROSS = LoadImage(NULL, MAKEINTRESOURCE(OCR_CROSS), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_UP = LoadImage(NULL, MAKEINTRESOURCE(OCR_UP), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_SIZENWSE = LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZENWSE), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_SIZENESW = LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZENESW), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_SIZEWE = LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_SIZENS = LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZENS), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_SIZEALL = LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEALL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_NO = LoadImage(NULL, MAKEINTRESOURCE(OCR_NO), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_HAND = LoadImage(NULL, MAKEINTRESOURCE(OCR_HAND), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_APPSTARTING = LoadImage(NULL, MAKEINTRESOURCE(OCR_APPSTARTING), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);
static HANDLE Cur_HELP = LoadImage(NULL, MAKEINTRESOURCE(OCR_HELP), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED);

// MessageBoxPos
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

// SetMagnifyZoom
#define MAG_METHOD_CENTER	0	//Center of the screen
#define MAG_METHOD_MOUSE	1	//Actual Cusor position
#define MAG_METHOD_ACTUAL	2	//Actual Point
#define MAG_METHOD_POINT	3	//Given Point
#define MAG_METHOD_MOVE		4	//Move +(negative if factor = 1 or 2)pointx , +(negative if factor = 2 or 3)pointy
#define MAG_METHOD_ZOOM		5	//Zoom: pointx = 1 Zoom+, pointy = 1 Zoom-, else +magnificationFactor
#define MAG_METHOD_SET		7	//Set magnification factor (when you can send only two unsigned short)
#define MAG_METHOD_RESET	6	//Temporary reset

// CheckForDriverByGUID
// guid = { 0x745a17a0, 0x74d3, 0x11d0, {0xb6, 0xfe, 0x00, 0xa0, 0xc9, 0x0f, 0x57, 0xda} };

// GetDeviceError
#define CM_PROB_DRIVER_NOT_THERE		0
//CM_PROB_NOT_CONFIGURED				1		
//CM_PROB_OUT_OF_MEMORY					3
//CM_PROB_INVALID_DATA					9
//CM_PROB_FAILED_START					10
//CM_PROB_NORMAL_CONFLICT				12
//CM_PROB_NEED_RESTART					14
//CM_PROB_PARTIAL_LOG_CONF				16
//CM_PROB_REINSTALL						18
//CM_PROB_REGISTRY						19
//CM_PROB_WILL_BE_REMOVED				21
//CM_PROB_DISABLED						22
//CM_PROB_DEVICE_NOT_THERE				24
//CM_PROB_FAILED_INSTALL				28
//CM_PROB_HARDWARE_DISABLED				29
//CM_PROB_FAILED_ADD					31
//CM_PROB_DISABLED_SERVICE				32
//CM_PROB_TRANSLATION_FAILED			33
//CM_PROB_NO_SOFTCONFIG					34
//CM_PROB_BIOS_TABLE					35
//CM_PROB_IRQ_TRANSLATION_FAILED		36
//CM_PROB_FAILED_DRIVER_ENTRY			37
//CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD	38
//CM_PROB_DRIVER_FAILED_LOAD			39
//CM_PROB_DRIVER_SERVICE_KEY_INVALID	40
//CM_PROB_LEGACY_SERVICE_NO_DEVICES		41
//CM_PROB_DUPLICATE_DEVICE				42
//CM_PROB_FAILED_POST_START				43
//CM_PROB_HALTED						44
//CM_PROB_PHANTOM						45
//CM_PROB_SYSTEM_SHUTDOWN				46
//CM_PROB_HELD_FOR_EJECT				47
//CM_PROB_DRIVER_BLOCKED				48
//CM_PROB_REGISTRY_TOO_LARGE			49
//CM_PROB_SETPROPERTIES_FAILED			50
//CM_PROB_WAITING_ON_DEPENDENCY			51
//CM_PROB_UNSIGNED_DRIVER				52
//CM_PROB_USED_BY_DEBUGGER				53
//CM_PROB_DEVICE_RESET					54
//CM_PROB_CONSOLE_LOCKED				55
//CM_PROB_NEED_CLASS_CONFIG				56
//CM_PROB_GUEST_ASSIGNMENT_FAILED		57

// GetDeviceState
#define DRIVER_INVALID_STRING   -3
#define DRIVER_INVALID_BUFFER   -2
#define DRIVER_INVALID_HANDLE   -1
#define DRIVER_STATE_NOTPRESENT  0
#define DRIVER_STATE_ACTIVE      1
#define DRIVER_STATE_DISABLED    2

//SetDeviceState
//DICS_DISABLE
//DICS_ENABLE

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
	HRSRC resourceHandle = ::FindResource(tape.Ds2hInst, MAKEINTRESOURCE(resourceID), RT_FONT);

	if (resourceHandle != nullptr)
	{
		HGLOBAL dataHandle = ::LoadResource(tape.Ds2hInst, resourceHandle);
		if (dataHandle != nullptr)
		{
			DWORD nFonts = 0;
			*fonthandle = AddFontMemResourceEx(LockResource(dataHandle), SizeofResource(tape.Ds2hInst, resourceHandle), NULL, &nFonts);

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
	HMODULE hMod = nullptr;
	HRSRC resourceHandle = ::FindResource(hMod, MAKEINTRESOURCE(resourceID), RT_RCDATA);

	if (resourceHandle != nullptr)
	{
		HGLOBAL dataHandle = ::LoadResource(hMod, resourceHandle);
		if (dataHandle != nullptr)
		{
			auto resourceSizetmp = ::SizeofResource(hMod, resourceHandle);
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
	HMODULE hMod = nullptr;
	hMod = ::GetModuleHandle(ModuleName);
	if (hMod == nullptr)
		return;
	/* DISCLAIMER potentially infinite loop
	 * not advisable in production code,
	 * included by request of the OP to
	 * match his original */
	while (::FreeLibrary(hMod));
	if (deletedll && ModuleName)
		::DeleteFile(ModuleName);
}

//-----------------------------------------------------------------------------
inline HRESULT SaveBitmap(std::wstring filename, HBITMAP bitmap, std::wstring format = L"png")
{
	CImage img;
	CImage image;
	image.Attach(bitmap);

	if (format == L"bmp")
		return image.Save((filename + L".bmp").c_str(), Gdiplus::ImageFormatBMP);
	if (format == L"png")
		return image.Save((filename + L".png").c_str(), Gdiplus::ImageFormatPNG);
	if (format == L"jpg")
		return image.Save((filename + L".jpg").c_str(), Gdiplus::ImageFormatJPEG);
	if (format == L"gif")
		return image.Save((filename + L".gif").c_str(), Gdiplus::ImageFormatGIF);
	else
		return E_FAIL;
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

inline LRESULT CALLBACK MsgBox_Proc(int message, WPARAM wParam, LPARAM lParam)
{
	static unsigned int MsgBox_cx = 0;
	switch (message)
	{
	case HCBT_CREATEWND:
	{
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
	}
	return CallNextHookEx(NULL, message, wParam, lParam);
}

inline int MessageBoxPos(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, int x, int y, int wrap = 0)
{
	MsgBox_start = 0;
	MsgBox_uType = uType;
	MsgBox_wrap = wrap;
	MsgBox_x = x;
	MsgBox_y = y;
	HHOOK hHook = SetWindowsHookEx(WH_CBT, &MsgBox_Proc, NULL, GetCurrentThreadId());
	int result = MessageBox(hWnd, lpText, lpCaption, uType);
	if (hHook) UnhookWindowsHookEx(hHook);

	return result;
}

//-----------------------------------------------------------------------------
static PCWSTR TextInput_title;
static PCWSTR TextInput_prompt;
static PCWSTR TextInput_description;
static bool TextInput_readOnly;
static bool TextInput_confirmed;
static std::wstring TextInput_input;
static RECT TextInput_rect;

inline static INT_PTR CALLBACK TextInput_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_BTN);
		SetBkMode(hdcStatic, OPAQUE);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		if (tape.DarkTheme)
			return (LRESULT)tape.hB_BTN_DARK;
		else
			return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_STATIC_DARK);
			return (LRESULT)tape.hB_BackGround_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_STATIC);
			return (LRESULT)tape.hB_BackGround;
		}
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TERMINAL);
			return (LRESULT)tape.hB_EDIT_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_EDIT);
			return (LRESULT)tape.hB_EDIT;
		}
	}
	case WM_PAINT:
	{
		if (!IsIconic(hDlg))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hDlg, &ps);

			RECT rect;
			GetClientRect(hDlg, &rect);
			FillRect(hDC, &rect, tape.hB_white);

			::ReleaseDC(hDlg, hDC);
			EndPaint(hDlg, &ps);
		}
		return FALSE;
	}
	case WM_INITDIALOG:
	{
		SetWindowPos(hDlg, HWND_TOP, TextInput_rect.left, TextInput_rect.top, 0, 0, SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
		SetWindowText(hDlg, TextInput_title);
		SetDlgItemText(hDlg, IDC_EDIT_LABEL, TextInput_prompt);
		SetDlgItemText(hDlg, IDC_EDIT_DESCRIPTION, TextInput_description);
		SetDlgItemText(hDlg, IDC_EDIT_CLEAR, L"Clear");
		SetDlgItemText(hDlg, IDC_EDIT_OK, L"OK");
		SetDlgItemText(hDlg, IDC_EDIT_INPUT, TextInput_input.data());
		if (TextInput_readOnly)
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_INPUT), false);
		SendMessage(hDlg, DM_SETDEFID, NULL, NULL);
		::SetFocus(NULL);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_CLEAR:
		{
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_INPUT), L"");
			break;
		}
		case IDC_EDIT_OK:
		{
			int length = GetWindowTextLength(GetDlgItem(hDlg, IDC_EDIT_INPUT));
			TextInput_input.resize(length);
			PWSTR data = const_cast<PWSTR>(TextInput_input.data());
			GetDlgItemText(hDlg, IDC_EDIT_INPUT, data, length + 1);
			TextInput_confirmed = true;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
		break;
	}
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_CLOSE:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
		break;
	}
	case WM_CLOSE:
	{
		if (GetKeyState(VK_ESCAPE) < 0 || GetKeyState(VK_CANCEL) < 0)
			return 0;
		else
			return DefWindowProc(hDlg, message, wParam, lParam);
	}
	case WM_NCDESTROY:
	{
		return (INT_PTR)TRUE;
	}
	}
	return (INT_PTR)FALSE;
}

inline void TextInputDialog(HWND parent, PCWSTR title, PCWSTR prompt, PCWSTR description, const std::wstring& defaultInput = L"", bool readOnly = false)
{
	TextInput_title = title;
	TextInput_prompt = prompt;
	TextInput_description = description;
	TextInput_readOnly = readOnly;
	TextInput_confirmed = false;
	TextInput_input = defaultInput;
	GetWindowRect(parent, &TextInput_rect);
	DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_INPUT), parent, TextInput_Proc, (LPARAM)NULL);
}

//-----------------------------------------------------------------------------
inline HWND CreateToolTip(
	HWND hWndParent,	/*HWND handle for the parent window, for example dialog box*/
	HWND hControlItem,	/*HWND handle for the control item, for example checkbox*/
	PTSTR tooltipText	/*text for the tool-tip*/)
{
	if (!hControlItem || !hWndParent || !tooltipText)
		return NULL;

	HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOFADE | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, NULL, GetModuleHandle(0), NULL);
	if (!hwndTip)
		return NULL;

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

	return hwndTip;
}

//-----------------------------------------------------------------------------
inline void SetWindowTransparent(HWND hwnd, bool bTransparent, int nTransparency)
{
	int lExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

	if (bTransparent)
	{
		HMODULE hMod = LoadLibrary(_T("User32"));
		if (hMod != nullptr)
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

//-----------------------------------------------------------------------------
inline unsigned int GetCursorType()
{
	HCURSOR cursor = GetCursor();

	if (cursor == Cur_NORMAL)			return OCR_NORMAL;			//Standard arrow
	else if (cursor == Cur_IBEAM)		return OCR_IBEAM;			//I - beam
	else if (cursor == Cur_WAIT)		return OCR_WAIT;			//Hourglass
	else if (cursor == Cur_CROSS)		return OCR_CROSS;			//Crosshair
	else if (cursor == Cur_UP)			return OCR_UP;				//Vertical arrow
	else if (cursor == Cur_SIZENWSE)	return OCR_SIZENWSE;		//Double - pointed arrow pointing northwest and southeast
	else if (cursor == Cur_SIZENESW)	return OCR_SIZENESW;		//Double - pointed arrow pointing northeast and southwest
	else if (cursor == Cur_SIZEWE)		return OCR_SIZEWE;			//Double - pointed arrow pointing west and east
	else if (cursor == Cur_SIZENS)		return OCR_SIZENS;			//Double - pointed arrow pointing north and south
	else if (cursor == Cur_SIZEALL)		return OCR_SIZEALL;			//Four - pointed arrow pointing north, south, east, and west
	else if (cursor == Cur_NO)			return OCR_NO;				//Slashed circle
	else if (cursor == Cur_HAND)		return OCR_HAND;			//Hand
	else if (cursor == Cur_APPSTARTING)	return OCR_APPSTARTING;		//Standard arrow and small hourglass
	else if (cursor == Cur_HELP)		return OCR_HELP;			//Arrow and question mark
	else								return NULL;
}

//-----------------------------------------------------------------------------
inline HRESULT ScreenCapturePart(int x, int y, int z, int t, std::wstring filename, std::wstring format = L"png", bool scaling = true)
{
	z = (z > x) ? z : tape.W;
	t = (t > y) ? t : tape.H;

	x = (x >= z) ? 0 : x;
	y = (y >= t) ? 0 : y;

	int w = z - x;
	int h = t - y;

	double Hscale = (scaling) ? tape.Hscale : 1;
	double Vscale = (scaling) ? tape.Vscale : 1;

	HDC hdcSource = GetDC(NULL);
	HDC hdcMemory = CreateCompatibleDC(hdcSource);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSource, w * Hscale, h * Vscale);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);

	BitBlt(hdcMemory, 0, 0, w * Hscale, h * Vscale, hdcSource, x * Hscale, y * Vscale, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);

	DeleteDC(hdcSource);
	DeleteDC(hdcMemory);

	return SaveBitmap(filename, hBitmap, format);
}

//-----------------------------------------------------------------------------
inline BOOL SetMagnifyZoom(unsigned char method, float factor, int pointx = 0, int pointy = 0)
{
	static float	MagLevel = 1;				//1 to 4096
	static int		MagxOffset = tape.W / 2;
	static int		MagyOffset = tape.H / 2;
	static bool		MagnifyLock = false;

	if (method == MAG_METHOD_RESET)
		MagnifyLock = !MagnifyLock;

	if (MagnifyLock)
	{
		if (method != MAG_METHOD_RESET)
			return FALSE;
		else if (MagLevel == 1)
			return TRUE;
	}

	switch (method)
	{
	case MAG_METHOD_CENTER:
	{
		if (factor >= 1 && factor <= 4096)
			MagLevel = factor;
		MagxOffset = tape.W / 2;
		MagyOffset = tape.H / 2;
		break;
	}
	case MAG_METHOD_MOUSE:
	{
		if (factor >= 1 && factor <= 4096)
			MagLevel = factor;
		GetCursorPos(&tape.mousepoint);
		MagxOffset = max(0, min(tape.W, tape.mousepoint.x));
		MagyOffset = max(0, min(tape.H, tape.mousepoint.y));
		break;
	}
	case MAG_METHOD_ACTUAL:
	{
		if (factor >= 1 && factor <= 4096)
			MagLevel = factor;
		if (MagLevel <= 1)
		{
			MagxOffset = tape.W / 2;
			MagyOffset = tape.H / 2;
		}
		break;
	}
	case MAG_METHOD_POINT:
	{
		if (factor >= 1 && factor <= 4096)
			MagLevel = factor;
		MagxOffset = pointx;
		MagyOffset = pointy;
		break;
	}
	case MAG_METHOD_MOVE:
	{
		if (factor > 0)
		{
			pointx = (factor < 3) ? -pointx : pointx;
			pointy = (factor > 1) ? -pointy : pointy;
		}
		MagxOffset = max(0, min(tape.W, MagxOffset + pointx));
		MagyOffset = max(0, min(tape.H, MagyOffset + pointy));
		break;
	}
	case MAG_METHOD_ZOOM:
	{
		if (pointx == 1)
			MagLevel = min(4096, MagLevel * 1.06);
		else if (pointy == 1)
			MagLevel = max(1, MagLevel * 0.94);
		else
			MagLevel = max(1, min(4096, MagLevel + factor));
		break;
	}
	case MAG_METHOD_SET:
	{
		MagLevel = max(1, min(4096, pointx + ((pointy) ? (float(pointy) / float(pow(10, floor(log10(pointy)) + 1))) : 0)));
		break;
	}
	case MAG_METHOD_RESET:
	{
		if (MagnifyLock)
		{
			if (MagLevel > 1)
				return MagSetFullscreenTransform(1, 0, 0);
			else
				return TRUE;
		}
		break;
	}
	}

	if (MagLevel <= 1 || MagLevel > 4096)
	{
		if (tape.MagInitialized)
		{
			MagLevel = 1;
			MagxOffset = tape.W / 2;
			MagyOffset = tape.H / 2;
			if (tape.MagCanUninitialize)
			{
				MagShowSystemCursor(true);
				if (MagUninitialize())
					tape.MagInitialized = false;
			}
		}
		return FALSE;
	}
	else
	{
		if (!tape.MagInitialized)
		{
			if (MagInitialize())
			{
				tape.MagInitialized = true;
				MagShowSystemCursor(tape.MagCursor);
				//echo(I18N.Magnifier_Magnification_Active);

				switch (method)
				{
				case MAG_METHOD_CENTER:
				case MAG_METHOD_MOUSE:
				{
					tape.MagnificationSmoothing(true);
					break;
				}
				case MAG_METHOD_POINT:
				{
					tape.MagnificationSmoothing(false);
					break;
				}
				}
			}
			else
				return FALSE;
		}
	}
	///////////////MagSetWindowFilterList();

	pointx = int(2 * MagxOffset * (1.0 - 1.0 / MagLevel));
	pointy = int(2 * MagyOffset * (1.0 - 1.0 / MagLevel));
	return MagSetFullscreenTransform(MagLevel, pointx, pointy);
}

//-----------------------------------------------------------------------------
inline BOOL MagSetColor(char magnifyColor = 0)
{
	static char MagnifyColor = 0;
	MagnifyColor = (MagnifyColor == magnifyColor) ? 0 : magnifyColor;

	MAGCOLOREFFECT g_MagEffectIdentity =  { 1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
											0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
											0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
											0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
											0.0f,  0.0f,  0.0f,  0.0f,  1.0f  };

	MAGCOLOREFFECT g_MagEffectGrayscale = { 0.3f,  0.3f,  0.3f,  0.0f,  0.0f,
											0.6f,  0.6f,  0.6f,  0.0f,  0.0f,
											0.1f,  0.1f,  0.1f,  0.0f,  0.0f,
											0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
											0.0f,  0.0f,  0.0f,  0.0f,  1.0f  };

	MAGCOLOREFFECT g_MagEffectInvert =   { -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
											0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
											0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
											0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
											1.0f,  1.0f,  1.0f,  0.0f,  1.0f  };

	switch (MagnifyColor)
	{
	case 0: { return MagSetFullscreenColorEffect(&g_MagEffectIdentity); break; }
	case 1: { return MagSetFullscreenColorEffect(&g_MagEffectGrayscale); break; }
	case 2: { return MagSetFullscreenColorEffect(&g_MagEffectInvert); break; }
	}
	return FALSE;
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
		HMODULE hMod = nullptr;
		DWORD cbNeeded = 0;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			if (hMod != nullptr)
			{
				GetModuleBaseName(hProcess, hMod, ProcessNametmp, sizeof(ProcessNametmp) / sizeof(WCHAR));
				::FreeLibrary(hMod);
			}
		CloseHandle(hProcess);
	}

	size_t tocopy = wcslen(ProcessNametmp) + 1;
	WCHAR* ProcessName = new WCHAR[tocopy];
	wcscpy_s(ProcessName, tocopy, ProcessNametmp);

	return ProcessName;
}


//-----------------------------------------------------------------------------
inline BOOL uSleep(__int64 usec)
{
	if (usec <= 0)
		return FALSE;
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); //Convert to 100 nanosecond interval, negative value indicates relative time

	if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
		return FALSE;
	if (!SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0))
	{
		CloseHandle(timer);
		return FALSE;
	}
	if (timer)
	{
		WaitForSingleObject(timer, INFINITE);
		CloseHandle(timer);
		return TRUE;
	}
	return FALSE;
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
inline BOOL IsServiceInstalled(LPCWSTR ServiceName, bool verbose = false)
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
inline int GetServiceState(LPCWSTR ServiceName, bool verbose = false)
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
inline BOOL ServiceInstall(LPCWSTR ServiceName, LPCWSTR installpath, DWORD servicetype, bool verbose = false)
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
inline BOOL ServiceStart(LPCWSTR ServiceName, bool verbose = false)
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
inline BOOL ServiceStop(LPCWSTR ServiceName, bool verbose = false)
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
inline BOOL ServiceDelete(LPCWSTR ServiceName, bool verbose = false)
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
		if (verbose)
			echo(L"There are %d drivers", cDrivers);

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
inline BOOL CheckForDriverByFile(LPCWSTR DriverName, bool verbose = false)
{
	if (!wcslen(DriverName))
		return FALSE;

	BOOL driverInstalled = FALSE;
	int i;
	std::vector<std::wstring> DriversList = ListofDriversByFile();

	for (i = 0; i < DriversList.size(); i++)
	{
		if (DriverName == DriversList[i])
		{
			if (verbose)
				echo(L"Driver %s found", DriversList[i].c_str());
			return TRUE;
		}
	}

	if (verbose)
		echo(L"Device not found");
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL CheckForDriverByGUID(std::wstring enumerator, GUID guid, bool verbose = false)
{
	//	guid = { 0x745a17a0, 0x74d3, 0x11d0, {0xb6, 0xfe, 0x00, 0xa0, 0xc9, 0x0f, 0x57, 0xda} };
	if (guid == GUID_NULL)
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(&guid, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(&guid, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
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
				SetupDiDestroyDeviceInfoList(hdevinfo);
				return TRUE;
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL CheckForDriverById(std::wstring enumerator, std::wstring MfgName, std::wstring Description, bool verbose = false)
{
	if (!MfgName.length() || !Description.length())
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
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
				if (!wcscmp(drvdata.MfgName, WCHARI(MfgName)))
					if (!wcscmp(drvdata.Description, WCHARI(Description)))
					{
						if (verbose)
						{
							echo(L"Driver %d/%d found:", DeviceIndex, DeviceDataIndex);
							echo(L"   description: %ws", drvdata.Description);
							echo(L"   MfgName: %ws", drvdata.MfgName);
							echo(L"   ProviderName: %ws", drvdata.ProviderName);
						}
						SetupDiDestroyDeviceInfoList(hdevinfo);
						return TRUE;
					}
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL CheckForDriverByHwId(std::wstring enumerator, std::wstring hwid, bool verbose = false)
{
	if (!hwid.length())
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	SP_DRVINFO_DATA_W drvdata;
	drvdata.cbSize = sizeof(SP_DRVINFO_DATA_W);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	DWORD DeviceDataIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;

		DWORD PropertyRegDataType;
		DWORD buffersize = 0;
		while (!SetupDiGetDeviceRegistryProperty(
			hdevinfo,
			&devinfo,
			SPDRP_HARDWAREID,
			&PropertyRegDataType,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
				break;
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
			}
			else
				return FALSE;
		}

		if (PropertyRegDataType != REG_MULTI_SZ)
			continue;

		if (!buffer)
			continue;

		LPTSTR p = NULL;
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
		{
			if (!wcscmp(hwid.c_str(), p))
			{
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
					}
				}
				LocalFree(buffer);
				SetupDiDestroyDeviceInfoList(hdevinfo);
				return TRUE;
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	if (buffer)
		LocalFree(buffer);
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline std::wstring GetDriverHwIdByGUID(std::wstring enumerator, GUID guid, bool verbose = false)
{
	if (guid == GUID_NULL)
		return L"";

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(&guid, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(&guid, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return L"";
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	SP_DRVINFO_DATA_W drvdata;
	drvdata.cbSize = sizeof(SP_DRVINFO_DATA_W);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;
		if (SetupDiBuildDriverInfoList(hdevinfo, &devinfo, SPDIT_COMPATDRIVER))
		{
			if (SetupDiEnumDriverInfoW(hdevinfo, &devinfo, SPDIT_COMPATDRIVER, 0, &drvdata))
			{
				DWORD PropertyRegDataType;
				DWORD buffersize = 0;
				while (!SetupDiGetDeviceRegistryProperty(
					hdevinfo,
					&devinfo,
					SPDRP_HARDWAREID,
					&PropertyRegDataType,
					(PBYTE)buffer,
					buffersize,
					&buffersize))
				{
					if (GetLastError() == ERROR_INVALID_DATA)
						break;
					else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
					{
						if (buffer)
							LocalFree(buffer);
						buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
					}
					else
						return L"";
				}

				if (PropertyRegDataType != REG_MULTI_SZ)
					continue;

				if (!buffer)
					continue;

				LPTSTR p = NULL;
				for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
				{
					if (verbose)
					{
						echo(L"Driver %d found:", DeviceIndex);
						echo(L"   description: %ws", drvdata.Description);
						echo(L"   MfgName: %ws", drvdata.MfgName);
						echo(L"   ProviderName: %ws", drvdata.ProviderName);
					}
					LocalFree(buffer);
					SetupDiDestroyDeviceInfoList(hdevinfo);
					return p;
				}
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return L"";
}

//-----------------------------------------------------------------------------
inline std::wstring GetDriverHwIdById(std::wstring enumerator, std::wstring MfgName, std::wstring Description, bool verbose = false)
{
	if (!MfgName.length() || !Description.length())
		return L"";

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return L"";
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	SP_DRVINFO_DATA_W drvdata;
	drvdata.cbSize = sizeof(SP_DRVINFO_DATA_W);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;
		if (SetupDiBuildDriverInfoList(hdevinfo, &devinfo, SPDIT_COMPATDRIVER))
		{
			if (SetupDiEnumDriverInfoW(hdevinfo, &devinfo, SPDIT_COMPATDRIVER, 0, &drvdata))
			{
				if (!wcscmp(drvdata.MfgName, WCHARI(MfgName)))
					if (!wcscmp(drvdata.Description, WCHARI(Description)))
					{
						DWORD PropertyRegDataType;
						DWORD buffersize = 0;
						while (!SetupDiGetDeviceRegistryProperty(
							hdevinfo,
							&devinfo,
							SPDRP_HARDWAREID,
							&PropertyRegDataType,
							(PBYTE)buffer,
							buffersize,
							&buffersize))
						{
							if (GetLastError() == ERROR_INVALID_DATA)
								break;
							else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
							{
								if (buffer)
									LocalFree(buffer);
								buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
							}
							else
								return L"";
						}

						if (PropertyRegDataType != REG_MULTI_SZ)
							continue;

						if (!buffer)
							continue;

						LPTSTR p = NULL;
						for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
						{
							if (verbose)
							{
								echo(L"Driver %d found:", DeviceIndex);
								echo(L"   description: %ws", drvdata.Description);
								echo(L"   MfgName: %ws", drvdata.MfgName);
								echo(L"   ProviderName: %ws", drvdata.ProviderName);
							}
							LocalFree(buffer);
							SetupDiDestroyDeviceInfoList(hdevinfo);
							return p;
						}
					}
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return L"";
}

//-----------------------------------------------------------------------------
inline std::vector<int> GetDeviceError(std::wstring enumerator, std::wstring hwid, bool verbose = false)
{
	std::vector<int> result = { };

	if (!hwid.length())
		return result;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return result;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;

		DWORD PropertyRegDataType;
		DWORD buffersize = 0;
		while (!SetupDiGetDeviceRegistryProperty(
			hdevinfo,
			&devinfo,
			SPDRP_HARDWAREID,
			&PropertyRegDataType,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
				break;
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
			}
			else
				return result;
		}

		if (PropertyRegDataType != REG_MULTI_SZ)
			continue;

		if (!buffer)
			continue;

		LPTSTR p = NULL;
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
		{
			if (!wcscmp(hwid.c_str(), p))
			{
				DEVPROPTYPE propertyType;
				BYTE propertyBuffer[100] = { 0 };
				DWORD requiredSize = 0;

				if (SetupDiGetDeviceProperty(hdevinfo, &devinfo, &DEVPKEY_Device_ProblemCode, &propertyType, propertyBuffer, 100, &requiredSize, 0))
				{
					unsigned int deviceProblemCode = *((unsigned int*)propertyBuffer);
					for (int i = 0; i < 100; i++)
					{
						result.push_back(propertyBuffer[i]);
						if (verbose)
							switch (propertyBuffer[i])
							{
							case 1: { echo(L"1:  CM_PROB_NOT_CONFIGURED"); break; }
							case 3: { echo(L"3:  CM_PROB_OUT_OF_MEMORY"); break; }
							case 9: { echo(L"9:  CM_PROB_INVALID_DATA"); break; }
							case 10: { echo(L"10: CM_PROB_FAILED_START"); break; }
							case 12: { echo(L"12: CM_PROB_NORMAL_CONFLICT"); break; }
							case 14: { echo(L"14: CM_PROB_NEED_RESTART"); break; }
							case 16: { echo(L"16: CM_PROB_PARTIAL_LOG_CONF"); break; }
							case 18: { echo(L"18: CM_PROB_REINSTALL"); break; }
							case 19: { echo(L"19: CM_PROB_REGISTRY"); break; }
							case 21: { echo(L"21: CM_PROB_WILL_BE_REMOVED"); break; }
							case 22: { echo(L"22: CM_PROB_DISABLED"); break; }
							case 24: { echo(L"24: CM_PROB_DEVICE_NOT_THERE"); break; }
							case 28: { echo(L"28: CM_PROB_FAILED_INSTALL"); break; }
							case 29: { echo(L"29: CM_PROB_HARDWARE_DISABLED"); break; }
							case 31: { echo(L"31: CM_PROB_FAILED_ADD"); break; }
							case 32: { echo(L"32: CM_PROB_DISABLED_SERVICE"); break; }
							case 33: { echo(L"33: CM_PROB_TRANSLATION_FAILED"); break; }
							case 34: { echo(L"34: CM_PROB_NO_SOFTCONFIG"); break; }
							case 35: { echo(L"35: CM_PROB_BIOS_TABLE"); break; }
							case 36: { echo(L"36: CM_PROB_IRQ_TRANSLATION_FAILED"); break; }
							case 37: { echo(L"37: CM_PROB_FAILED_DRIVER_ENTRY"); break; }
							case 38: { echo(L"38: CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD"); break; }
							case 39: { echo(L"39: CM_PROB_DRIVER_FAILED_LOAD"); break; }
							case 40: { echo(L"40: CM_PROB_DRIVER_SERVICE_KEY_INVALID"); break; }
							case 41: { echo(L"41: CM_PROB_LEGACY_SERVICE_NO_DEVICES"); break; }
							case 42: { echo(L"42: CM_PROB_DUPLICATE_DEVICE"); break; }
							case 43: { echo(L"43: CM_PROB_FAILED_POST_START"); break; }
							case 44: { echo(L"44: CM_PROB_HALTED"); break; }
							case 45: { echo(L"45: CM_PROB_PHANTOM"); break; }
							case 46: { echo(L"46: CM_PROB_SYSTEM_SHUTDOWN"); break; }
							case 47: { echo(L"47: CM_PROB_HELD_FOR_EJECT"); break; }
							case 48: { echo(L"48: CM_PROB_DRIVER_BLOCKED"); break; }
							case 49: { echo(L"49: CM_PROB_REGISTRY_TOO_LARGE"); break; }
							case 50: { echo(L"50: CM_PROB_SETPROPERTIES_FAILED"); break; }
							case 51: { echo(L"51: CM_PROB_WAITING_ON_DEPENDENCY"); break; }
							case 52: { echo(L"52: CM_PROB_UNSIGNED_DRIVER"); break; }
							case 53: { echo(L"53: CM_PROB_USED_BY_DEBUGGER"); break; }
							case 54: { echo(L"54: CM_PROB_DEVICE_RESET"); break; }
							case 55: { echo(L"55: CM_PROB_CONSOLE_LOCKED"); break; }
							case 56: { echo(L"56: CM_PROB_NEED_CLASS_CONFIG"); break; }
							case 57: { echo(L"57: CM_PROB_GUEST_ASSIGNMENT_FAILED"); break; }
							}
					}
				}
				LocalFree(buffer);
				SetupDiDestroyDeviceInfoList(hdevinfo);
				return result;
			}
		}
	}

	if (verbose)
		echo(L"0:  CM_PROB_DRIVER_NOT_THERE");
	result.push_back(0);
	if (buffer)
		LocalFree(buffer);
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return result;
}

//-----------------------------------------------------------------------------
inline char GetDeviceState(std::wstring enumerator, std::wstring hwid, bool verbose = false)
{
	if (!hwid.length())
		return DRIVER_INVALID_STRING;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return DRIVER_INVALID_HANDLE;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;

		DWORD PropertyRegDataType;
		DWORD buffersize = 0;
		while (!SetupDiGetDeviceRegistryProperty(
			hdevinfo,
			&devinfo,
			SPDRP_HARDWAREID,
			&PropertyRegDataType,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
				break;
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
			}
			else
				return DRIVER_INVALID_BUFFER;
		}

		if (PropertyRegDataType != REG_MULTI_SZ)
			continue;

		if (!buffer)
			continue;

		LPTSTR p = NULL;
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
		{
			if (!wcscmp(hwid.c_str(), p))
			{
				DEVPROPTYPE propertyType;
				BYTE propertyBuffer[100] = { 0 };
				DWORD requiredSize = 0;

				if (SetupDiGetDeviceProperty(hdevinfo, &devinfo, &DEVPKEY_Device_ProblemCode, &propertyType, propertyBuffer, 100, &requiredSize, 0))
				{
					unsigned int deviceProblemCode = *((unsigned int*)propertyBuffer);
					for (int i = 0; i < 100; i++)
					{
						if (propertyBuffer[i] == CM_PROB_DISABLED)
						{
							LocalFree(buffer);
							SetupDiDestroyDeviceInfoList(hdevinfo);
							return DRIVER_STATE_DISABLED;
						}
					}
				}
				LocalFree(buffer);
				SetupDiDestroyDeviceInfoList(hdevinfo);
				return DRIVER_STATE_ACTIVE;
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	if (buffer)
		LocalFree(buffer);
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return DRIVER_STATE_NOTPRESENT;
}

//-----------------------------------------------------------------------------
inline BOOL SetDeviceState(std::wstring enumerator, std::wstring hwid, DWORD dwState, bool verbose = false)
{
	if (!hwid.length())
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;

		DWORD PropertyRegDataType;
		DWORD buffersize = 0;
		while (!SetupDiGetDeviceRegistryProperty(
			hdevinfo,
			&devinfo,
			SPDRP_HARDWAREID,
			&PropertyRegDataType,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
				break;
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
			}
			else
				return FALSE;
		}

		if (PropertyRegDataType != REG_MULTI_SZ)
			continue;

		if (!buffer)
			continue;

		LPTSTR p = NULL;
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
		{
			if (!wcscmp(hwid.c_str(), p))
			{
				SP_PROPCHANGE_PARAMS params;
				params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
				params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
				params.StateChange = dwState;
				params.Scope = DICS_FLAG_GLOBAL;

				if (SetupDiSetClassInstallParams(hdevinfo, &devinfo, &params.ClassInstallHeader, sizeof(params)))
					if (SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hdevinfo, &devinfo))
					{
						if (verbose)
							echo(L"Device state changed");
						if (buffer)
							LocalFree(buffer);
						SetupDiDestroyDeviceInfoList(hdevinfo);
						return TRUE;
					}

				if (verbose)
					echo(L"Device state not changed: %u", GetLastError());
				if (buffer)
					LocalFree(buffer);
				SetupDiDestroyDeviceInfoList(hdevinfo);
				return FALSE;
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	if (buffer)
		LocalFree(buffer);
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL RemoveDriverById(std::wstring enumerator, std::wstring MfgName, std::wstring Description, bool verbose = false)
{
	if (!MfgName.length() || !Description.length())
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	SP_DRVINFO_DATA_W drvdata;
	drvdata.cbSize = sizeof(SP_DRVINFO_DATA_W);

	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;
		if (SetupDiBuildDriverInfoList(hdevinfo, &devinfo, SPDIT_COMPATDRIVER))
		{
			if (SetupDiEnumDriverInfoW(hdevinfo, &devinfo, SPDIT_COMPATDRIVER, 0, &drvdata))
			{
				if (!wcscmp(drvdata.MfgName, WCHARI(MfgName)))
					if (!wcscmp(drvdata.Description, WCHARI(Description)))
					{
						if (SetupDiRemoveDevice(hdevinfo, &devinfo))
						{
							if (verbose)
							{
								echo(L"Driver %d removed:", DeviceIndex);
								echo(L"   description: %ws", drvdata.Description);
								echo(L"   MfgName: %ws", drvdata.MfgName);
								echo(L"   ProviderName: %ws", drvdata.ProviderName);
							}
							SetupDiDestroyDeviceInfoList(hdevinfo);
							return TRUE;
						}
						else
						{
							SetupDiDestroyDeviceInfoList(hdevinfo);
							if (verbose)
								echo(L"Device not unistalled: %u", GetLastError());
							return FALSE;
						}
					}
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL RemoveDriverByHwId(std::wstring enumerator, std::wstring hwid, bool verbose = false)
{
	if (!hwid.length())
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	SP_DRVINFO_DATA_W drvdata;
	drvdata.cbSize = sizeof(SP_DRVINFO_DATA_W);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;

		DWORD PropertyRegDataType;
		DWORD buffersize = 0;
		while (!SetupDiGetDeviceRegistryProperty(
			hdevinfo,
			&devinfo,
			SPDRP_HARDWAREID,
			&PropertyRegDataType,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
				break;
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
			}
			else
				return FALSE;
		}

		if (PropertyRegDataType != REG_MULTI_SZ)
			continue;

		if (!buffer)
			continue;

		LPTSTR p = NULL;
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
		{
			if (!wcscmp(hwid.c_str(), p))
			{
				if (SetupDiRemoveDevice(hdevinfo, &devinfo))
				{
					if (verbose)
					{
						echo(L"Driver %d removed:", DeviceIndex);
						echo(L"   description: %ws", drvdata.Description);
						echo(L"   MfgName: %ws", drvdata.MfgName);
						echo(L"   ProviderName: %ws", drvdata.ProviderName);
					}
					SetupDiDestroyDeviceInfoList(hdevinfo);
					return TRUE;
				}
				else
				{
					SetupDiDestroyDeviceInfoList(hdevinfo);
					if (verbose)
						echo(L"Device not unistalled: %u", GetLastError());
					return FALSE;
				}
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	if (buffer)
		LocalFree(buffer);
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL DeviceRestart(std::wstring enumerator, std::wstring hwid, bool tohide = true, bool verbose = false)
{
	if (!hwid.length())
		return FALSE;

	HDEVINFO hdevinfo;
	if (enumerator.length())
		hdevinfo = SetupDiGetClassDevsW(NULL, enumerator.c_str(), NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	else
		hdevinfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		if (verbose)
			echo(L"Device information handle failed : INVALID_HANDLE_VALUE");
		return FALSE;
	}

	SP_DEVINFO_DATA devinfo;
	devinfo.cbSize = sizeof(devinfo);

	LPTSTR buffer = NULL;
	DWORD DeviceIndex = 0;
	while (SetupDiEnumDeviceInfo(hdevinfo, DeviceIndex, &devinfo))
	{
		DeviceIndex++;

		DWORD PropertyRegDataType;
		DWORD buffersize = 0;
		while (!SetupDiGetDeviceRegistryProperty(
			hdevinfo,
			&devinfo,
			SPDRP_HARDWAREID,
			&PropertyRegDataType,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
				break;
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (wchar_t*)LocalAlloc(LPTR, buffersize);
			}
			else
				return FALSE;
		}

		if (PropertyRegDataType != REG_MULTI_SZ)
			continue;

		if (!buffer)
			continue;

		LPTSTR p = NULL;
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + 1)
		{
			if (!wcscmp(hwid.c_str(), p))
			{
				if (tohide)
				{
					if (SetupDiRestartDevices(hdevinfo, &devinfo))
					{
						if (verbose)
							echo(L"Device restarted");
						if (buffer)
							LocalFree(buffer);
						SetupDiDestroyDeviceInfoList(hdevinfo);
						return TRUE;
					}
					else
					{
						if (verbose)
							echo(L"Device not restarted: %u", GetLastError());
						if (buffer)
							LocalFree(buffer);
						SetupDiDestroyDeviceInfoList(hdevinfo);
						return FALSE;
					}
				}
				else
				{
					SP_PROPCHANGE_PARAMS params;
					params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
					params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
					params.StateChange = DICS_PROPCHANGE;
					params.Scope = DICS_FLAG_GLOBAL;

					if (SetupDiSetClassInstallParams(hdevinfo, &devinfo, &params.ClassInstallHeader, sizeof(params)))
					{
						if (SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hdevinfo, &devinfo))
						{
							if (verbose)
								echo(L"Device restarted");
							if (buffer)
								LocalFree(buffer);
							SetupDiDestroyDeviceInfoList(hdevinfo);
							return TRUE;
						}
						else
						{
							if (verbose)
								echo(L"Device not restarted: %u", GetLastError());
							if (buffer)
								LocalFree(buffer);
							SetupDiDestroyDeviceInfoList(hdevinfo);
							return FALSE;
						}
					}
				}
			}
		}
	}

	if (verbose)
		echo(L"Device not found: %u", GetLastError());
	if (buffer)
		LocalFree(buffer);
	SetupDiDestroyDeviceInfoList(hdevinfo);
	return FALSE;
}

//-----------------------------------------------------------------------------
inline BOOL DeviceUpdate(std::wstring lpFileName, std::wstring hwid)
{
	BOOL result = FALSE;

	typedef BOOL(WINAPI* UpdateDriverForPlugAndPlayDevicesProto)(
		_In_opt_ HWND hwndParent,
		__in LPCTSTR HardwareId,
		__in LPCTSTR FullInfPath,
		__in DWORD InstallFlags,
		__out_opt PBOOL bRebootRequired);

	UpdateDriverForPlugAndPlayDevicesProto UpdateFn;
	HMODULE newdevMod = NULL;
	DWORD flags = 0;
	DWORD res;
	WCHAR InfPath[MAX_PATH];
	CONFIGRET ret;

	// Inf must be a full pathname
	res = GetFullPathName(lpFileName.c_str(), MAX_PATH, InfPath, NULL);
	if ((res >= MAX_PATH) || (res == 0))
		return FALSE;

	if (GetFileAttributes(InfPath) == (DWORD)(-1))
		return FALSE;

	// make use of UpdateDriverForPlugAndPlayDevices
	newdevMod = LoadLibrary(TEXT("newdev.dll"));
	if (!newdevMod)
		return FALSE;

	//Get UPDATEDRIVERFORPLUGANDPLAYDEVICES
	UpdateFn = (UpdateDriverForPlugAndPlayDevicesProto)GetProcAddress(newdevMod, "UpdateDriverForPlugAndPlayDevicesW");
	if (!UpdateFn)
	{
		FreeLibrary(newdevMod);
		return FALSE;
	}

	// Update Driver
	ret = CMP_WaitNoPendingInstallEvents(30000);
	if (ret != WAIT_OBJECT_0 && ret != WAIT_TIMEOUT)
	{
		FreeLibrary(newdevMod);
		return FALSE;
	}

	//UPDATEDRIVERFORPLUGANDPLAYDEVICES
	if (!UpdateFn(NULL, hwid.c_str(), InfPath, INSTALLFLAG_FORCE, FALSE))
	{
		FreeLibrary(newdevMod);
		return FALSE;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
inline BOOL InstallDriverByHwId(std::wstring lpFileName, std::wstring hwid)
{
	HDEVINFO DeviceInfoSet = INVALID_HANDLE_VALUE;
	SP_DEVINFO_DATA DeviceInfoData;
	GUID ClassGUID;
	WCHAR ClassName[MAX_CLASS_NAME_LEN];
	WCHAR hwIdList[LINE_LEN + 4];
	WCHAR InfPath[MAX_PATH];

	if (!lpFileName.length() || !hwid.length())
		return FALSE;

	if (GetFullPathName(lpFileName.c_str(), MAX_PATH, InfPath, NULL) >= MAX_PATH)
	{
		echo(L"Install: InfPath too long");
		return FALSE;
	}

	// List of hardware ID's must be double zero-terminated
	ZeroMemory(hwIdList, sizeof(hwIdList));
	wcscpy_s(hwIdList, hwid.length() + 1, hwid.c_str());

	// Use the INF File to extract the Class GUID
	if (!SetupDiGetINFClass(InfPath, &ClassGUID, ClassName, sizeof(ClassName) / sizeof(ClassName[0]), 0))
		return FALSE;

	// Create the container for the to-be-created Device Information Element.
	DeviceInfoSet = SetupDiCreateDeviceInfoList(&ClassGUID, 0);
	if (DeviceInfoSet == INVALID_HANDLE_VALUE)
		return FALSE;

	// Use the Class GUID and Name from the INF file.
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	if (!SetupDiCreateDeviceInfo(DeviceInfoSet, ClassName, &ClassGUID, NULL, 0, DICD_GENERATE_ID, &DeviceInfoData))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return FALSE;
	}
	// Add the HardwareID to the Device's HardwareID property
	if (!SetupDiSetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_HARDWAREID, (LPBYTE)hwIdList, (lstrlen(hwIdList) + 1 + 1) * sizeof(WCHAR)))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return FALSE;
	}

	// Transform the registry element into an actual devnode in the PnP HW tree.
	if (!SetupDiCallClassInstaller(DIF_REGISTERDEVICE, DeviceInfoSet, &DeviceInfoData))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return FALSE;
	}

	// update the driver for the device we just created
	DeviceUpdate(lpFileName, hwid);

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
	return TRUE;
}

//-----------------------------------------------------------------------------
inline LPTSTR* GetMultiSzIndexArray(_In_ __drv_aliasesMem LPTSTR MultiSz)
/*
	Get an index array pointing to the MultiSz passed in
*/
{
	LPTSTR scan;
	LPTSTR* array;
	int elements;

	for (scan = MultiSz, elements = 0; scan[0];elements++)
		scan += _tcslen(scan) + 1;

	array = new LPTSTR[elements + 2];
	if (!array)
		return NULL;

	array[0] = MultiSz;
	array++;
	if (elements)
	{
		for (scan = MultiSz, elements = 0; scan[0]; elements++)
		{
			array[elements] = scan;
			scan += _tcslen(scan) + 1;
		}
	}
	array[elements] = NULL;

	return array;
}

inline LPTSTR* GetRegMultiSz(_In_ HKEY hKey, _In_ LPCTSTR Val)
/*
	Get a multi-sz from registry
	and return as an array of strings
*/
{
	LPTSTR buffer;
	DWORD size;
	DWORD reqSize;
	DWORD dataType;
	LPTSTR* array;
	DWORD szChars;
	LONG regErr;

	size = 8192; // initial guess
	buffer = new TCHAR[(size / sizeof(TCHAR)) + 2];
	if (!buffer)
		return NULL;

	reqSize = size;
	regErr = RegQueryValueEx(hKey, Val, NULL, &dataType, (PBYTE)buffer, &reqSize);
	while ((regErr != NO_ERROR)) {
		if (GetLastError() != ERROR_MORE_DATA)
			goto failed;

		if (dataType != REG_MULTI_SZ)
			goto failed;

		size = reqSize;
		delete[] buffer;
		buffer = new TCHAR[(size / sizeof(TCHAR)) + 2];
		if (!buffer)
			goto failed;

		regErr = RegQueryValueEx(hKey, Val, NULL, &dataType, (PBYTE)buffer, &reqSize);
	}
	szChars = reqSize / sizeof(TCHAR);
	buffer[szChars] = TEXT('\0');
	buffer[szChars + 1] = TEXT('\0');

	array = GetMultiSzIndexArray(buffer);
	if (array)
		return array;

failed:
	if (buffer)
		delete[] buffer;

	return NULL;
}

inline LPTSTR* CopyMultiSz(_In_opt_ PZPWSTR Array)
/*
	Creates a new array from old
*/
{
	LPTSTR multiSz = NULL;
	HRESULT hr;
	int cchMultiSz = 0;

	if (Array)
	{
		for (int c = 0;Array[c];c++)
			cchMultiSz += (int)_tcslen(Array[c]) + 1;
	}
	cchMultiSz += 1;
	multiSz = new TCHAR[cchMultiSz];
	if (!multiSz)
		return NULL;

	int len = 0;
	if (Array) {
		for (int c = 0;Array[c];c++)
		{
			//hr = StringCchCopy(multiSz + len, cchMultiSz - len, Array[c]);
			//if (FAILED(hr))
			if (wcscpy_s(multiSz + len, cchMultiSz - len, Array[c]))
			{
				if (multiSz)
					delete[] multiSz;
				return NULL;
			}
			len += (int)_tcslen(multiSz + len) + 1;
		}
	}

	if (len < cchMultiSz)
		multiSz[len] = TEXT('\0');
	else
		multiSz[cchMultiSz - 1] = TEXT('\0'); // This should never happen!

	LPTSTR* pRes = GetMultiSzIndexArray(multiSz);
	if (pRes)
		return pRes;

	delete[] multiSz;

	return NULL;
}

inline void DelMultiSz(_In_opt_ __drv_freesMem(object) PZPWSTR Array)
/*
	Deletes the string array allocated by GetDevMultiSz/GetRegMultiSz/GetMultiSzIndexArray
*/
{
	if (Array) {
		Array--;
		if (Array[0]) {
			delete[] Array[0];
		}
		delete[] Array;
	}
}

#define EXIT_OK      (0)
#define EXIT_REBOOT  (1)
#define EXIT_FAIL    (2)
#define EXIT_USAGE   (3)
inline int UpperClassFilter(std::wstring cf_class, std::wstring cf_driver)
/*
	Class filters Tweaking
	!driver: delete first match of driver
	-driver: insert new driver at start
	+driver: insert new driver at end
*/
{
	size_t tocopy = cf_driver.length();
	WCHAR* driver = new WCHAR[tocopy + 1];
	if (tocopy)
		wcscpy_s(driver, tocopy + 1, cf_driver.c_str());
	else
		driver[0] = 0;

	DWORD nGuids = 0;
	GUID guid;
	WCHAR* regval = new WCHAR[1000];
	HKEY hk = (HKEY)INVALID_HANDLE_VALUE;
	LPTSTR* multiVal = NULL;
	SC_HANDLE SCMHandle = NULL;
	SC_HANDLE ServHandle = NULL;
	bool modified = false;
	int failcode = EXIT_FAIL;

	// take the first guid for the name
	if (!SetupDiClassGuidsFromNameEx(cf_class.c_str(), &guid, 1, &nGuids, NULL, NULL))
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			goto final;
	}
	if (nGuids == 0)
		goto final;

	{
		std::wstring regstr = L"UpperFilters";
		size_t tocopy = regstr.length();
		wcscpy_s(regval, tocopy + 1, regstr.c_str());
	}

	hk = SetupDiOpenClassRegKeyEx(&guid, KEY_READ | KEY_WRITE, DIOCR_INSTALLER, NULL, NULL);
	if (hk == INVALID_HANDLE_VALUE)
		goto final;

	multiVal = GetRegMultiSz(hk, regval);
	if (!multiVal)
	{
		multiVal = CopyMultiSz(NULL);
		if (!multiVal)
			goto final;
	}

	{
		int op = driver[0];
		LPTSTR serv = driver + 1;
		int after = -1;
		int span = 1;
		int mark = 0;
		int cnt;
		int ent;
		LPTSTR* tmpArray;

		if ((driver == NULL) || (!driver) || !serv[0])
		{
			failcode = EXIT_USAGE;
			goto final;
		}

		if (op == TEXT('!')) {
			echo("sddsds");
			// find specified service in list
			for (after += span; multiVal[after]; after++)
			{
				if (_tcsicmp(multiVal[after], serv) == 0)
					break;
			}
			if (!multiVal[after])
				goto final;

			// modifying
			for (int c = after; multiVal[c]; c++)
				multiVal[c] = multiVal[c + 1];

			LPTSTR* newArray = CopyMultiSz(multiVal);
			if (!newArray)
				goto final;

			DelMultiSz(multiVal);
			multiVal = newArray;
			span = 0; // deleted
			modified = true;
		}
		else if (op == '+')
		{
			// insert after
			if (after < 0)
			{
				int c;
				for (c = 0; multiVal[c];c++) {}
				mark = c;
			}
			else
				mark = after + span;
		}
		else if (op == '-')
		{
			// insert before
			if (after < 0)
				mark = 0;
			else
				mark = after;
		}
		else
		{
			// not valid
			failcode = EXIT_USAGE;
			goto final;
		}

		// sanity - see if service exists
		SCMHandle = OpenSCManager(NULL, NULL, GENERIC_READ);
		if (!SCMHandle)
			goto final;
		ServHandle = OpenService(SCMHandle, serv, GENERIC_READ);

		if (ServHandle)
			CloseServiceHandle(ServHandle);

		CloseServiceHandle(SCMHandle);
		if (!ServHandle)
			goto final;

		// need a bigger array
		for (cnt = 0; multiVal[cnt]; cnt++) {}

		tmpArray = new LPTSTR[cnt + 2];
		if (!tmpArray)
			goto final;

		_Analysis_assume_(mark < cnt);
		for (ent = 0; ent < mark; ent++)
			tmpArray[ent] = multiVal[ent];

		tmpArray[ent] = serv;
		for (;ent < cnt; ent++) {
			tmpArray[ent + 1] = multiVal[ent];
		}
		tmpArray[ent + 1] = NULL;

		LPTSTR* newArray = CopyMultiSz(tmpArray);
		delete[] tmpArray;
		if (!newArray)
			goto final;

		DelMultiSz(multiVal);
		multiVal = newArray;
		modified = true;
	}

	if (modified)
	{
		if (multiVal[0])
		{
			size_t len = 0;
			LPTSTR multiSz = multiVal[-1];
			LPTSTR p = multiSz;

			while (*p)
			{
				p += _tcslen(p) + 1;
			}
			p++; // skip past null
			len = (p - multiSz) * sizeof(TCHAR);
			if (len > DWORD_MAX)
				goto final;

			LONG err = RegSetValueEx(hk, regval, 0, REG_MULTI_SZ, (LPBYTE)multiSz, (DWORD)len);
			if (err == NO_ERROR)
				failcode = EXIT_REBOOT;
		}
		else
		{
			LONG err = RegDeleteValue(hk, regval);
			if ((err == NO_ERROR) || (err == ERROR_FILE_NOT_FOUND))
				failcode = EXIT_REBOOT;
		}
	}
	else
		failcode = EXIT_OK;

	final:

	if (multiVal)
		DelMultiSz(multiVal);

	if (hk != (HKEY)INVALID_HANDLE_VALUE)
		RegCloseKey(hk);

	delete[] driver;
	delete[] regval;
	return failcode;
}
