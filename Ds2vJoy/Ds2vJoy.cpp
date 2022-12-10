#include "stdafx.h"
#include "Ds2vJoy.h"
#include "Source.h"
#include "Destination.h"
#include "SettingDlg.h"
#include "vJoyDlg.h"
#include "DInputDlg.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"
#include "RapidFireDlg.h"
#include "RapidFireDataDlg.h"
#include "XOutput.h"
#include "XOutputDlg.h"
#include "KeymapDlg.h"
#include "KeymapDataDlg.h"
#include "Guardian.h"
#include "GuardianDlg.h"
#include "ExplorerDlg.h"
#include "LinksDlg.h"
#include "NotepadDlg.h"
#include "Tasktray.h"

#ifdef X64
BOOL x86 = FALSE;
#else
BOOL x86 = TRUE;
#endif

static bool done_WM_CREATE = false;

Settings			tape;
XOutput				xi;
Guardian			hid;

static HWND hProgressBar;

LogDlg				_log;
static SettingDlg	sDlg;
static vJoyDlg		vDlg;
static DInputDlg	dDlg;
static MappingDlg	mDlg;
static MappingDlg	mDlg2;
static RapidFireDlg	rDlg;
static KeymapDlg	kDlg;
static XOutputDlg	xDlg;
static GuardianDlg	gDlg;
static LinksDlg		lDlg;
static NotepadDlg	nDlg;
static Tasktray		tasktray;

MappingDataDlg		mDDlg;
KeymapDataDlg		kDDlg;
RapidFireDataDlg	rDDlg;

unsigned char		mode = 1;
static double		r;
unsigned char		mousemode[3] = { 0 };
unsigned char		mouseabolute = 1;
unsigned short		grid[6] = { 0 };
bool				isGridNeeded = false;
std::vector<char>	gridmove = { };
static double		mousefactor;
static double		movefactor;
static double		sniperfactor;
static double		raidfactor;
static double		touchfactor;
static double		slowfactor;
static double		accuracyfactor;
static POINT		gridpoint;
static double		average = 0;

static WCHAR		LogSatusString[80] = L"";
static WCHAR		SettingsSatusString[80] = L"";
static WCHAR		MappingSatusString[80] = L"";
static WCHAR		RapidFireSatusString[80] = L"";
static WCHAR		XOutputSatusString[80] = L"";
static WCHAR		KeymapSatusString[80] = L"";
static WCHAR		LinksSatusString[80] = L"";

bool isFullScreen = false;
bool MouseIsOverMain = true;
bool MouseIsOverTab = false;
bool WebMenuVisible = false;
bool log_closing = false;
static HDC HDCForInfo = GetDC(NULL);
static HDC hDCStatus = NULL;
static COLORREF COLORREFforInfo = RGB(0, 0, 0);
static std::map<DWORD, HANDLE> s_threads;
std::wstring initialUri = L"";
std::vector<std::unique_ptr<ExplorerDlg>> web_tabs;

	   ATOM             RegisterWndClass(HINSTANCE hInstance);
	   BOOL             InitInstance(HINSTANCE, int);
static int              RunMessagePump();
static DWORD WINAPI     ThreadProc(void* pvParam);
static void             WaitForOtherThreads();
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//	   LRESULT CALLBACK LowLevelKeyboardProc(int, WPARAM, LPARAM);
	   INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
//	   BOOL CALLBACK    EnumChildProc(HWND hwndChild, LPARAM lParam);
	   void				WM_CREATE_END(HWND hWnd);
	   void				GetPixelForInfo();
	   void				OutRun();

DPI_AWARENESS_CONTEXT dpiAwarenessContext = DPI_AWARENESS_CONTEXT_UNAWARE;
//DPI_AWARENESS_CONTEXT dpiAwarenessContext = DPI_AWARENESS_CONTEXT_SYSTEM_AWARE;
//DPI_AWARENESS_CONTEXT dpiAwarenessContext = DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE;
//DPI_AWARENESS_CONTEXT dpiAwarenessContext = DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2;
//DPI_AWARENESS_CONTEXT dpiAwarenessContext = DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED;

#define NEXT_PARAM_CONTAINS(command) \
	_wcsnicmp(nextParam.c_str(), command, ARRAYSIZE(command) - 1) == 0

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_     LPWSTR    lpCmdLine,
					  _In_     int       nCmdShow)
{
	tape.Ds2hInst = hInstance;
	UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

    // Test if this code runs on the correct machine
	SYSTEM_INFO info;
	GetNativeSystemInfo(&info);
	if (info.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64)	//PROCESSOR_ARCHITECTURE_AMD64
	{
		MessageBox(NULL, WCHARI(IDS_FOR_X64), WCHARI(IDS_APP_TITLE), MB_OK | MB_ICONERROR);
		return -1;
	};
	//PROCESSOR_ARCHITECTURE_AMD64		x64 (AMD or Intel)
	//PROCESSOR_ARCHITECTURE_ARM		ARM
	//PROCESSOR_ARCHITECTURE_ARM64		ARM64
	//PROCESSOR_ARCHITECTURE_IA64		Intel Itanium
	//PROCESSOR_ARCHITECTURE_INTEL		x86
	//PROCESSOR_ARCHITECTURE_UNKNOWN	Unknown architecture.

	LoadStringW(hInstance, IDS_DS2VJOY, tape.szWindowClass, 100);
	LoadStringW(hInstance, IDS_APP_TITLE, tape.szTitle, 100);
	SetCurrentProcessExplicitAppUserModelID(tape.szTitle);
	RegisterWndClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;


	if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE | COINIT_SPEED_OVER_MEMORY)))
	//if (FAILED(Windows::Foundation::Initialize(RO_INIT_MULTITHREADED)))
	//if (FAILED(Windows::Foundation::Initialize(RO_INIT_SINGLETHREADED)))
		return FALSE;

	SetProcessDpiAwarenessContext(dpiAwarenessContext);
	InitCommonControls();

	if (lpCmdLine && lpCmdLine[0])
	{
		int paramCount = 0;
		LPWSTR* params = CommandLineToArgvW(GetCommandLineW(), &paramCount);
		for (int i = 0; i < paramCount; ++i)
		{
			std::wstring nextParam;
			if (params[i][0] == L'-')
			{
				if (params[i][1] == L'-')
					nextParam.assign(params[i] + 2);
				else
					nextParam.assign(params[i] + 1);
			}
			if (NEXT_PARAM_CONTAINS(L"url="))
				initialUri = nextParam.substr(nextParam.find(L'=') + 1);
		}
		LocalFree(params);
	}

	//HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
	int retVal = RunMessagePump();
	WaitForOtherThreads();

	//UnhookWindowsHookEx(hhkLowLevelKybd);
	CoUninitialize();

	return retVal;
/*
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
*/
}
/*
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;

	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			if (fEatKeystroke = (p->vkCode == 0x41))     //redirect a to b
			{
				if ((wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN)) // Keydown
				{
					keybd_event('B', 0, 0, 0);
				}
				else if ((wParam == WM_KEYUP) || (wParam == WM_SYSKEYUP)) // Keyup
				{
					keybd_event('B', 0, KEYEVENTF_KEYUP, 0);
				}
				break;
			}
			break;
		}
	}
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}
*/
ATOM RegisterWndClass(HINSTANCE hInstance)
{
	{
		Guardian hid;
		hid.WhitelistDs2vJoy();
		memset(&hid, 0, sizeof(hid));
	}

	WNDCLASSEXW wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DS2VJOY_ICON256));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wcex.hbrBackground	= CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszMenuName	= 0;
//	wcex.lpszMenuName	= MAKEINTRESOURCE(IDR_DS2VJOY);
	wcex.lpszClassName	= tape.szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_DS2VJOY_ICON32));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	RECT desk;
	ClientArea(&desk);
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX/* | WS_THICKFRAME*/;
	tape.Ds2hWnd = CreateWindowExW(WS_EX_CONTROLPARENT, tape.szWindowClass, tape.szTitle, dwStyle, (desk.right - desk.left) / 2 - 246, desk.top + 200, 492, 327, nullptr, nullptr, hInstance, nullptr);

	if (!tape.Ds2hWnd)
		return FALSE;
/*
	{
		HMENU hMenu_Ds2vJoy = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_DS2VJOY));
		ModifyMenu(hMenu_Ds2vJoy, 0, MF_BYPOSITION | MF_STRING, 0, I18N.FILE);
		ModifyMenu(hMenu_Ds2vJoy, 1, MF_BYPOSITION | MF_STRING, 0, I18N.HELP);

		int m_TabsID[4];
		m_TabsID[0] = IDM_EXIT;
		m_TabsID[1] = IDM_ABOUT;
		MENUITEMINFO info;
		for (int i = 0; i < 2; i++)
		{
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING;
			GetMenuItemInfo(hMenu_Ds2vJoy, m_TabsID[i], FALSE, &info);
			info.fType = MFT_OWNERDRAW;
			info.fState = MFS_UNCHECKED;
			switch (i)
			{
			case 0: info.dwTypeData = I18N.EXIT; break;
			case 1: info.dwTypeData = I18N.ABOUT; break;
			}
			SetMenuItemInfo(hMenu_Ds2vJoy, m_TabsID[i], FALSE, &info);
		}
		
		SetMenu(tape.Ds2hWnd, hMenu_Ds2vJoy);
	}
*//*
   ShowWindow(tape.Ds2hWnd, nCmdShow);
   if (nCmdShow== SW_SHOWMINNOACTIVE)
	   SendMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
   else if (nCmdShow == SW_RESTORE)
	   SendMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
   UpdateWindow(tape.Ds2hWnd);
*/
   return TRUE;
}

// Run the message pump for one thread.
static int RunMessagePump()
{
	HACCEL hAccelTable = LoadAccelerators(tape.Ds2hInst, MAKEINTRESOURCE(IDR_DS2VJOY));
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			if (!IsDialogMessage(GetAncestor(msg.hwnd, GA_ROOT), &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	DWORD threadId = GetCurrentThreadId();
	auto it = s_threads.find(threadId);
	if (it != s_threads.end())
	{
		CloseHandle(it->second);
		s_threads.erase(threadId);
	}

	return (int)msg.wParam;
}

// Make a new thread.
void CreateNewThread(ExplorerDlg* dlg)
{
	DWORD threadId;
	HANDLE thread = CreateThread(nullptr, 0, ThreadProc, reinterpret_cast<LPVOID>(dlg), STACK_SIZE_PARAM_IS_A_RESERVATION, &threadId);
	s_threads.insert(std::pair<DWORD, HANDLE>(threadId, thread));
	SetThreadDpiAwarenessContext(dpiAwarenessContext);
}

// This function is the starting point for new threads. It will open a new app window.
static DWORD WINAPI ThreadProc(void* pvParam)
{
	ExplorerDlg* dlg = static_cast<ExplorerDlg*>(pvParam);
	RECT win;
	if (dlg->m_isHome)
		GetWindowRect(tape.Ds2hWnd, &win);
	else
		GetWindowRect(dlg->m_hDlg, &win);
	new ExplorerDlg(L"", false, tape.DefaultZoomValue, win);
	return RunMessagePump();
}

// Called on the main thread. Wait for all other threads to complete before exiting.
static void WaitForOtherThreads()
{
	while (!s_threads.empty())
	{
		std::vector<HANDLE> threadHandles;
		for (auto it = s_threads.begin(); it != s_threads.end(); ++it)
			threadHandles.push_back(it->second);

		HANDLE* handleArray = threadHandles.data();
		DWORD dwIndex = MsgWaitForMultipleObjects(
			static_cast<DWORD>(threadHandles.size()), threadHandles.data(), FALSE,
			INFINITE, QS_ALLEVENTS);

		if (dwIndex == WAIT_OBJECT_0 + threadHandles.size())
		{
			MSG msg;
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}

typedef struct _GeneralParams
{
	Source*			srce = { 0 };
	Destination*	dest = { 0 };
	unsigned char	vJoyID = 0;
	Mappings		mappings;
	Keymaps			keymaps;
	RapidFires		rapidfires;
	bool			NextStepFlag = false;
	SourceButton*	splittouch = { 0 };
	byte			splitButton = 0;
	unsigned char	splitCol = 0;
	unsigned char	splitRow = 0;
} GeneralParams;

void GeneralMotor(bool updateflag, void* param)
{
	if (tape.CallbackPaused)
		return;

	static std::chrono::system_clock::time_point lastesc = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point last = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point lastmouse = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point now;
	now = std::chrono::system_clock::now();
	double averagetmp = double(std::chrono::duration_cast<std::chrono::nanoseconds>(now - last).count()) / double(1000000);

	last = now;
	if (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		lastesc = now;
	if (now - lastesc > std::chrono::seconds(2))
		return;

	GeneralParams* p = (GeneralParams*)param;
	Source* srce = p->srce;
	Destination* dest = p->dest;

	if (updateflag == false && p->NextStepFlag == false)
		return;
	average = averagetmp;

	dest->ClearState();
	p->mappings[0].RunFirst(dest);

	size_t n = p->mappings.size();
	for (int i = 0; i < n; i++)
		if (p->mappings[i].Enable == 1)
			p->mappings[i].Run(average);

	p->mappings[0].RunLast(p->srce, dest);
	wcscpy_s(MappingSatusString, wcslen(p->mappings[0].MappingButtons()) + 1, p->mappings[0].MappingButtons());
	dest->UpdateState();

	if (tape.ActualSource && now - lastmouse > std::chrono::milliseconds(3) && !tape.MouseMovePaused)
	{
		lastmouse = now;
		POINT CursorPos;
		double x = srce->GetButton(SourceButton::LX)->GetVal();
		double y = srce->GetButton(SourceButton::LY)->GetVal();
		double z = srce->GetButton(SourceButton::RX)->GetVal();
		double t = srce->GetButton(SourceButton::RY)->GetVal();
		static bool lastTouchActive;
		static int lasttouchx = 1;
		static int lasttouchy = 1;

		static bool isLastgridNeeded = false;
		bool isOtherMouse = ((mousemode[0] && mousemode[0] != 5) || (mousemode[1] && mousemode[1] != 5) || (mousemode[2] && mousemode[2] != 5)) ? true : false;

		if (isLastgridNeeded && !isOtherMouse)
			SetCursorPos(gridpoint.x, gridpoint.y);
		isLastgridNeeded = isGridNeeded;

		bool GridMoveDone = false;

		if (tape.ActualSource < 3)
		{
			static char lastTouchUsed = -1;
			bool TouchActive = false;
			int touchx = 0;
			int touchy = 0;
			bool TouchActive1 = srce->TouchActive(0);
			bool TouchActive2 = srce->TouchActive(1);
			if (TouchActive1 || TouchActive2)
			{
				lastTouchUsed = (TouchActive1 && TouchActive2) ? ((lastTouchUsed == -1) ? 3 : ((lastTouchUsed < 2) ? ((lastTouchUsed) ? 2 : 3) : lastTouchUsed)) : ((TouchActive2) ? 1 : 0);
				TouchActive = true;
				touchx = srce->TouchX(lastTouchUsed % 2);
				touchy = srce->TouchY(lastTouchUsed % 2);
			}
			else
				lastTouchUsed = -1;

			bool touchbox[7] = { 0, 0, 0, 0, 0, 0, 0 };
			int posymax = (tape.ActualSource == 1) ? 350 : 400;
			if (TouchActive)
			{
				if (touchy > 20)
				{
					if (touchy < posymax)
					{
						if (touchx < 960)
							touchbox[1] = 1;
						else
							touchbox[2] = 1;
					}
					else
					{
						if (touchx < 960)
							touchbox[3] = 1;
						else
							touchbox[4] = 1;
					}
				}
			}

			touchbox[5] = touchbox[1] || touchbox[3];
			touchbox[6] = touchbox[2] || touchbox[4];
			touchbox[0] = touchbox[5] || touchbox[6];
			for (int i = 0; i < 7; i++)
				p->splittouch->SetTouchBox(i, touchbox[i]);

			//	p->srce->String();
			if (p->splittouch != 0 && p->splittouch->isPushed())
			{
				if (TouchActive)
				{
					int pos = 0;
					if (p->splitRow > 0)
					{
						switch (tape.ActualSource)
						{
						case 1: { pos = touchy / (943 / p->splitRow) * p->splitCol; break; }
						case 2: { pos = touchy / (1080 / p->splitRow) * p->splitCol; break; }
						}
					}
					if (p->splitCol > 0)
						pos += touchx / (1920 / p->splitCol);
					if (p->splitButton - 1 + pos < 128)
						dest->GetButton((DestButtonID)(DestinationButton::Button1 + p->splitButton - 1 + pos))->SetVal(1);
				}
			}

			if (mousemode[1])
			{
				static double restx;
				static double resty;
				GetCursorPos(&CursorPos);
				switch (mousemode[1])
				{
				case 1: //absolute
				{
					if (TouchActive && mouseabolute == 1)
					{
						int destx = touchx;
						int desty = 0;
						if (tape.ActualSource)
							desty = touchy * 1080 / 943;
						else
							desty = touchy;
						if (!tape.MouseCanBypass && !tape.MouseCanBypasstmp)
						{
							restx = max(0, min(tape.W - 1, destx));
							resty = max(0, min(tape.H - 1, desty));
						}
						SetCursorPos(destx, desty);
						lasttouchx = touchx;
						lasttouchy = touchy;
						lastTouchActive = TouchActive;
					}
					break;
				}
				case 2: //mouse
				{
					if (TouchActive && lastTouchActive)
					{
						restx = restx + ((double)touchx - lasttouchx) * touchfactor * average;
						if (tape.ActualSource == 1)
							resty = resty + ((double)touchy * 1080 / 943 - lasttouchy) * touchfactor * average;
						else
							resty = resty + ((double)touchy - lasttouchy) * touchfactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
						lasttouchx = touchx;
						lasttouchy = touchy;
						lastTouchActive = TouchActive;
					}
					break;
				}
				case 3: //slow
				{
					if (TouchActive && lastTouchActive)
					{
						restx = restx + ((double)touchx - lasttouchx) * slowfactor * average;
						if (tape.ActualSource == 1)
							resty = resty + ((double)touchy * 1080 / 943 - lasttouchy) * slowfactor * average;
						else
							resty = resty + ((double)touchy - lasttouchy) * slowfactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
						lasttouchx = touchx;
						lasttouchy = touchy;
						lastTouchActive = TouchActive;
					}
					break;
				}
				case 4: //accuracy
				{
					if (TouchActive && lastTouchActive)
					{
						restx = restx + ((double)touchx - lasttouchx) * accuracyfactor * average;
						if (tape.ActualSource == 1)
							resty = resty + ((double)touchy * 1080 / 943 - lasttouchy) * accuracyfactor * average;
						else
							resty = resty + ((double)touchy - lasttouchy) * accuracyfactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
						lasttouchx = touchx;
						lasttouchy = touchy;
						lastTouchActive = TouchActive;
					}
					break;
				}
				case 5: //grid
				{
					if ((TouchActive && touchx && touchy) || gridmove.size())
					{
						double ldesty = (tape.ActualSource == 1) ? 943 : 1080;
						if (gridmove.size())
						{
							switch (gridmove[0])
							{
							case 1:if (grid[4]) lasttouchx = (int)max(1, min(1920, lasttouchx - (1920 / grid[4]))); break;
							case 2:if (grid[5]) lasttouchy = (int)max(1, min(ldesty, lasttouchy - (ldesty / grid[5]))); break;
							case 3:if (grid[4]) lasttouchx = (int)max(1, min(1920, lasttouchx + (1920 / grid[4]))); break;
							case 4:if (grid[5]) lasttouchy = (int)max(1, min(ldesty, lasttouchy + (ldesty / grid[5]))); break;
							}
						}
						else
						{
							lasttouchx = max(((grid[4]) ? 1 : 0), touchx);
							lasttouchy = max(((grid[5]) ? 1 : 0), touchy);
							lastTouchActive = TouchActive;
						}
						int destw = (grid[2]) ? grid[2] : tape.W - grid[0];
						int desth = (grid[3]) ? grid[3] : tape.H - grid[1];
						double destx = 0;
						double desty = 0;
						if (grid[4])
							destx = grid[0] + (double(destw) / grid[4]) * (ceil(double(lasttouchx) / (double(1920) / grid[4])) - 0.5);
						else
							destx = grid[0] + destw * (double(lasttouchx) / 1920);
						if (grid[5])
							desty = grid[1] + (double(desth) / grid[5]) * (ceil(double(lasttouchy) / (ldesty / grid[5])) - 0.5);
						else
							desty = grid[1] + desth * (double(lasttouchy) / ldesty);
						if (!tape.MouseCanBypass && !tape.MouseCanBypasstmp)
						{
							destx = max(0, min(tape.W - 1, destx));
							desty = max(0, min(tape.H - 1, desty));
						}
						SetCursorPos((int)destx, (int)desty);
						gridpoint.x = destx;
						gridpoint.y = desty;
						GridMoveDone = true;
					}
					break;
				}
				}
			}
		}
		{
			if (mousemode[0])
			{
				static double restx;
				static double resty;
				double xtmp = x - 32767.5;
				double ytmp = y - 32767.5;
				GetCursorPos(&CursorPos);
				switch (mousemode[0])
				{
				case 1: //absolute
				{
					if ((srce->GetButton(SourceButton::LX)->isPushed() || srce->GetButton(SourceButton::LY)->isPushed()) && mouseabolute == 0)
					{
						double restx = min((double)2 * tape.w, max(0, r * ((double)2 * x / 65535 - 1) + tape.w));
						double resty = min((double)2 * tape.h, max(0, r * ((double)2 * y / 65535 - 1) + tape.h));
						if (!tape.MouseCanBypass && !tape.MouseCanBypasstmp)
						{
							restx = max(0, min(tape.W - 1, restx));
							resty = max(0, min(tape.H - 1, resty));
						}
						SetCursorPos((int)restx, (int)resty);
					}
					break;
				}
				case 2: //mouse
				{
					if (srce->GetButton(SourceButton::LX)->isPushed() || srce->GetButton(SourceButton::LY)->isPushed())
					{
						restx = restx + xtmp * xtmp * xtmp * mousefactor * average;
						resty = resty + ytmp * ytmp * ytmp * mousefactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 3: //move
				{
					if (srce->GetButton(SourceButton::LX)->isPushed() || srce->GetButton(SourceButton::LY)->isPushed())
					{
						restx = restx + xtmp * xtmp * xtmp * movefactor * average;
						resty = resty + ytmp * ytmp * ytmp * movefactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 4: //sniper
				{
					if (srce->GetButton(SourceButton::LX_SNIPER)->isPushed() || srce->GetButton(SourceButton::LY_SNIPER)->isPushed())
					{
						restx = restx + xtmp * sniperfactor * average;
						resty = resty + ytmp * sniperfactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 5: //raid
				{
					if ((srce->GetButton(SourceButton::LX)->isPushed() || srce->GetButton(SourceButton::LY)->isPushed()) || gridmove.size())
					{
						double destw = (grid[2]) ? grid[2] : tape.W - grid[0];
						double desth = (grid[3]) ? grid[3] : tape.H - grid[1];
						double restxtmp = restx + abs(xtmp) * xtmp * raidfactor * average;
						double restytmp = resty + abs(ytmp) * ytmp * raidfactor * average;
						if (gridmove.size())
						{
							switch (gridmove[0])
							{
							case 1:if (grid[4]) { restx = restx - (destw / grid[4]); resty = restytmp; } break;
							case 2:if (grid[5]) { resty = resty - (desth / grid[5]); restx = restxtmp; } break;
							case 3:if (grid[4]) { restx = restx + (destw / grid[4]); resty = restytmp; } break;
							case 4:if (grid[5]) { resty = resty + (desth / grid[5]); restx = restxtmp; } break;
							}
						}
						else
						{
							restx = restxtmp;
							resty = restytmp;
						}
						restx = max((double)grid[0] + ((grid[4]) ? 1 : 0), min(grid[0] + destw, restx));
						resty = max((double)grid[1] + ((grid[5]) ? 1 : 0), min(grid[1] + desth, resty));
						double destx = 0;
						double desty = 0;
						if (grid[4])
							destx = grid[0] + (destw / grid[4]) * (ceil((double(restx) - grid[0]) / (destw / grid[4])) - 0.5);
						else
							destx = restx;
						if (grid[5])
							desty = grid[1] + (desth / grid[5]) * (ceil((double(resty) - grid[1]) / (desth / grid[5])) - 0.5);
						else
							desty = resty;
						if (!tape.MouseCanBypass && !tape.MouseCanBypasstmp)
						{
							destx = max(0, min(tape.W - 1, destx));
							desty = max(0, min(tape.H - 1, desty));
						}
						SetCursorPos((int)destx, (int)desty);
						gridpoint.x = destx;
						gridpoint.y = desty;
						GridMoveDone = true;
					}
					break;
				}
				}
			}
			if (mousemode[2])
			{
				static double restx;
				static double resty;
				double ztmp = z - 32767.5;
				double ttmp = t - 32767.5;
				GetCursorPos(&CursorPos);
				switch (mousemode[2])
				{
				case 1: //absolute
				{
					if ((srce->GetButton(SourceButton::RX)->isPushed() || srce->GetButton(SourceButton::RY)->isPushed()) && mouseabolute == 2)
					{
						double restx = min((double)2 * tape.w, max(0, r * ((double)2 * z / 65535 - 1) + tape.w));
						double resty = min((double)2 * tape.h, max(0, r * ((double)2 * t / 65535 - 1) + tape.h));
						if (!tape.MouseCanBypass && !tape.MouseCanBypasstmp)
						{
							restx = max(0, min(tape.W - 1, restx));
							resty = max(0, min(tape.H - 1, resty));
						}
						SetCursorPos((int)restx, (int)resty);
					}
					break;
				}
				case 2: //mouse
				{
					if (srce->GetButton(SourceButton::RX)->isPushed() || srce->GetButton(SourceButton::RY)->isPushed())
					{
						restx = restx + ztmp * ztmp * ztmp * mousefactor * average;
						resty = resty + ttmp * ttmp * ttmp * mousefactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 3: //move
				{
					if (srce->GetButton(SourceButton::RX)->isPushed() || srce->GetButton(SourceButton::RY)->isPushed())
					{
						restx = restx + ztmp * ztmp * ztmp * movefactor * average;
						resty = resty + ttmp * ttmp * ttmp * movefactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 4: //sniper
				{
					if (srce->GetButton(SourceButton::RX_SNIPER)->isPushed() || srce->GetButton(SourceButton::RY_SNIPER)->isPushed())
					{
						restx = restx + ztmp * sniperfactor * average;
						resty = resty + ttmp * sniperfactor * average;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass || tape.MouseCanBypasstmp)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W - 1, CursorPos.x + movex));
							movey = max(0, min(tape.H - 1, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 5: //raid
				{
					if ((srce->GetButton(SourceButton::RX)->isPushed() || srce->GetButton(SourceButton::RY)->isPushed()) || gridmove.size())
					{
						double destw = (grid[2]) ? grid[2] : tape.W - grid[0];
						double desth = (grid[3]) ? grid[3] : tape.H - grid[1];
						double restxtmp = restx + abs(ztmp) * ztmp * raidfactor * average;
						double restytmp = resty + abs(ttmp) * ttmp * raidfactor * average;
						if (gridmove.size())
						{
							switch (gridmove[0])
							{
							case 1:if (grid[4]) { restx = restx - (destw / grid[4]); resty = restytmp; } break;
							case 2:if (grid[5]) { resty = resty - (desth / grid[5]); restx = restxtmp; } break;
							case 3:if (grid[4]) { restx = restx + (destw / grid[4]); resty = restytmp; } break;
							case 4:if (grid[5]) { resty = resty + (desth / grid[5]); restx = restxtmp; } break;
							}
						}
						else
						{
							restx = restxtmp;
							resty = restytmp;
						}
						restx = max((double)grid[0] + ((grid[4]) ? 1 : 0), min(grid[0] + destw, restx));
						resty = max((double)grid[1] + ((grid[5]) ? 1 : 0), min(grid[1] + desth, resty));
						double destx = 0;
						double desty = 0;
						if (grid[4])
							destx = grid[0] + (destw / grid[4]) * (ceil((double(restx) - grid[0]) / (destw / grid[4])) - 0.5);
						else
							destx = restx;
						if (grid[5])
							desty = grid[1] + (desth / grid[5]) * (ceil((double(resty) - grid[1]) / (desth / grid[5])) - 0.5);
						else
							desty = resty;
						if (!tape.MouseCanBypass && !tape.MouseCanBypasstmp)
						{
							destx = max(0, min(tape.W - 1, destx));
							desty = max(0, min(tape.H - 1, desty));
						}
						SetCursorPos((int)destx, (int)desty);
						gridpoint.x = destx;
						gridpoint.y = desty;
						GridMoveDone = true;
					}
					break;
				}
				}
			}
		}
		if (gridmove.size() && GridMoveDone)
			gridmove.erase(gridmove.begin());
	}

	{
		p->rapidfires[0].RunFirst();

		bool flag=false;
		size_t max = p->rapidfires.size();
		for (int i = 0; i < max; i++)
		{
			if (p->rapidfires[i].Enable == 1)
				if (p->rapidfires[i].Run(now))
					flag = true;
		}
		p->NextStepFlag = flag;

		wcscpy_s(RapidFireSatusString, wcslen(p->rapidfires[0].RapidFireButtons()) + 1, p->rapidfires[0].RapidFireButtons());
	}

	if (dest->Active() && tape.vJoyActive && !tape.vJoyPaused)
		dest->Update();

	if (tape.XOutputActive)
	{
		xi.Run();
		wcscpy_s(XOutputSatusString, wcslen(xi.XOutputButtons()) + 1, xi.XOutputButtons());
	}

	{
		p->keymaps[0].RunFirst();

		size_t max = p->keymaps.size();
		for (int i = 0; i < max; i++)
			if (p->keymaps[i].Enable == 1)
				p->keymaps[i].Run();

		wcscpy_s(KeymapSatusString, wcslen(p->keymaps[0].KeymapButtons()) + 1, p->keymaps[0].KeymapButtons());
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Source srce;
	static Destination dest;
	static GeneralParams cbParams;
	static HWND hTab;
	static HWND hTopMost;
	static HWND hStatus;
	static HWND hWebMenu;
	static HWND hWebClose;
	static HWND hTab_Explorer;
	static HWND hTab_DeleteDF;
	static bool lastextended = false;
	static bool extended = false;
	static bool cloned = false;
	static bool notepad = false;
	static unsigned char PreviousTab = 15;
	static unsigned char PreviousNotepadTab = 0;
	static unsigned char NotepadTab = 0;
	static unsigned long long m_flag_drag = 0;
	static unsigned long long m_flag_size = 0;
	static RECT FirstMoveRect = { (0, 0, 0, 0) };
	static RECT WebRect = { (0, 0, 0, 0) };
	static bool FirstMove = false;
	static short x = 0;
	static short y = 0;
	static bool first_WM_CREATE = false;
	static bool load_dll = false;
	static bool wm_pause = false;
	static bool wm_reload = false;
	static bool wm_deststart = false;
	static bool wm_srcestart = false;

	switch (message)
	{
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		SetTextColor(hdcStatic, tape.ink_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TERMINAL);
			return (LRESULT)tape.hB_black;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_MSGBOX);
			return (LRESULT)tape.hB_MSGBOX;
		}
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
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
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_COMBO_DARK);
			return (LRESULT)tape.hB_LIST_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_COMBO);
			return (LRESULT)tape.hB_LIST;
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
			if (tape.DarkTheme)
				FillRect(hDC, &rect, tape.hB_black);
			else
				FillRect(hDC, &rect, tape.hB_BackGround);
			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* DrawMenuStructure = (DRAWITEMSTRUCT*)lParam;

		if (DrawMenuStructure->CtlType == ODT_TAB)
		{
			BOOL selected = DrawMenuStructure->itemState & ODS_SELECTED;

			if (tape.DarkTheme)
			{
				unsigned int actual = DrawMenuStructure->itemID;

				if (actual != TabCtrl_GetCurSel(DrawMenuStructure->hwndItem))
					return FALSE;

				HDC hDC = GetDC(DrawMenuStructure->hwndItem);
				RECT rect;
				GetClientRect(DrawMenuStructure->hwndItem, &rect);
				FillRect(hDC, &rect, tape.hB_black);
				::ReleaseDC(DrawMenuStructure->hwndItem, hDC);

				for (int i = 0; i < TabCtrl_GetItemCount(DrawMenuStructure->hwndItem); i++)
				{
					RECT rect = DrawMenuStructure->rcItem;
					rect.top += (DrawMenuStructure->hwndItem == hTab) ? 2 : -3;
					if (DrawMenuStructure->hwndItem == hTab)
					{
						rect.left = (48 * i) + 2;
						rect.right = (48 * (i + 1)) + 2;
					}
					else
					{
						rect.left = (18 * i) + 2;
						rect.right = (18 * (i + 1)) + 2;
					}

					TC_ITEM tc_item;
					tc_item.mask = TCIF_TEXT;
					WCHAR buff[MAX_PATH - 1];
					tc_item.pszText = buff;
					tc_item.cchTextMax = MAX_PATH - 1;
					if (!TabCtrl_GetItem(DrawMenuStructure->hwndItem, i, &tc_item))
						return FALSE;

					SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
					if (actual == i)
						SetTextColor(DrawMenuStructure->hDC, tape.ink_TAB2_DARK);
					else
						SetTextColor(DrawMenuStructure->hDC, tape.ink_TAB_DARK);

					WCHAR wszBuffer[MAX_PATH];
					int nCharCount = _snwprintf_s(wszBuffer, sizeof(wszBuffer), L"%s", buff);
					if (nCharCount > 0)
					{
						int nCharacters;
						for (nCharacters = 0;
							nCharacters < nCharCount; nCharacters++)
							if (wszBuffer[nCharacters] == L'\t' ||
								wszBuffer[nCharacters] == L'\b')
								break;
						DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else
			{
				RECT rect = DrawMenuStructure->rcItem;
				TC_ITEM tc_item;
				tc_item.mask = TCIF_TEXT;
				WCHAR buff[MAX_PATH - 1];
				tc_item.pszText = buff;
				tc_item.cchTextMax = MAX_PATH - 1;
				if (!TabCtrl_GetItem(DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, &tc_item))
					return FALSE;

				rect.top += (DrawMenuStructure->hwndItem == hTab) ? 2 : -1;
				if (selected)
					rect.top -= ::GetSystemMetrics(SM_CYEDGE);

				SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				SetTextColor(DrawMenuStructure->hDC, tape.ink_TAB);

				WCHAR wszBuffer[MAX_PATH];
				int nCharCount = _snwprintf_s(wszBuffer, sizeof(wszBuffer), L"%s", buff);
				if (nCharCount > 0)
				{
					int nCharacters;
					for (nCharacters = 0;
						nCharacters < nCharCount; nCharacters++)
						if (wszBuffer[nCharacters] == L'\t' ||
							wszBuffer[nCharacters] == L'\b')
							break;
					DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
		break;
	}
	case WM_SHOWWINDOW:
	{
		switch (TabCtrl_GetCurSel(hTab))
		{
		case 5: { xi.XOutputStates(); xi.vJoyStates(); break; }
		case 6: { hid.HidStates(); break; }
		}
		break;
	}
	case WM_CREATE:
	{
		if (first_WM_CREATE)
			break;

		first_WM_CREATE = true;
		tape.Ds2hWnd = hWnd;

		tape.Init(WCHARI(L"Ds2vJoy.ini"));
		tape.LoadLanguage();
		_log.Init();

		if (tape.Tasktray)
		{
			::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DEFERERASE | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
			tape.TopMost = false;
			mDDlg.Hide();
			mDlg2.Hide();
		}

		DWORD dwStyle = WS_VISIBLE | WS_POPUP & ~WS_THICKFRAME;
		hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, dwStyle, GetSystemMetrics(SM_CXSCREEN) / 2 - 150, GetSystemMetrics(SM_CYSCREEN) / 2 - 100, 200, 20, hWnd, (HMENU)0, tape.Ds2hInst, NULL);
		SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 45));
		SendMessage(hProgressBar, PBM_SETSTEP, (WPARAM)1, 0);
		SetWindowPos(hProgressBar, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

		std::vector<char> data;
		DWORD resourceSize;
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		//if (LoadEmbeddedResource(IDR_DEVCON_EXE, &data, &resourceSize))
		//	WriteToFile(L"Devcon.exe", data, resourceSize, true, true);
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		//if (isFileExists("Devcon.exe"))
			load_dll = true;
		
		_log.SetShowTime(load_dll);
		tape.Load(Settings::Setting_All);
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		if (tape.BreakAndExit)
		{
			PostMessage(hProgressBar, WM_CLOSE, 0, 0);
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		}
		GetCursorPos(&tape.mousepoint);
		GetCursorPos(&gridpoint);

		if (load_dll)
		{
			tasktray.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			sDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			vDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			dDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			mDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			mDlg2.Init(true);	//Clone
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			rDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			kDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			xDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			gDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			lDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			nDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			mDDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			rDDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			kDDlg.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			cbParams.srce = &srce;
			cbParams.dest = &dest;
		}
		else
		{
			PostMessage(hProgressBar, WM_CLOSE, 0, 0);
			DWORD style = GetWindowLong(hWnd, GWL_STYLE);
			SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU);
			SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

			echo(I18N.Fatal_Error1);
			echo();
			echo(I18N.Fatal_Error2);
			done_WM_CREATE = true;
			return FALSE;
		}

		{
			hTab = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_FIXEDWIDTH | TCS_OWNERDRAWFIXED, 0, 0, 476, 21, hWnd, (HMENU)ID_TABMENU, tape.Ds2hInst, NULL);

			TCITEM tc_item;
			tc_item.mask = TCIF_TEXT;
			tc_item.pszText = I18N.TabLog;
			TabCtrl_InsertItem(hTab, 0, &tc_item);
			tc_item.pszText = I18N.TabSettings;
			TabCtrl_InsertItem(hTab, 1, &tc_item);
			tc_item.pszText = I18N.TabMapping;
			TabCtrl_InsertItem(hTab, 2, &tc_item);
			tc_item.pszText = I18N.TabRapidFire;
			TabCtrl_InsertItem(hTab, 3, &tc_item);
			tc_item.pszText = I18N.TabKeymap;
			TabCtrl_InsertItem(hTab, 4, &tc_item);
			tc_item.pszText = I18N.TabOutput;
			TabCtrl_InsertItem(hTab, 5, &tc_item);
			tc_item.pszText = I18N.TabGuardian;
			TabCtrl_InsertItem(hTab, 6, &tc_item);
			tc_item.pszText = I18N.TabExplorer;
			TabCtrl_InsertItem(hTab, 7, &tc_item);
			tc_item.pszText = I18N.TabLinks;
			TabCtrl_InsertItem(hTab, 8, &tc_item);

			SendMessage(hTab, WM_SETFONT, WPARAM(tape.hTab), TRUE);
			TabCtrl_SetItemSize(hTab, 48, 17);
			TabCtrl_SetPadding(hTab, 0, 4);
			TabCtrl_SetCurSel(hTab, 0);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			hTopMost = CreateWindowEx(0, L"button", L"↕", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_CENTER, 451, 3, 20, 15, hWnd, (HMENU)ID_TOPMOST, tape.Ds2hInst, NULL);
			SendMessage(hTopMost, WM_SETFONT, WPARAM(tape.hTopMost), TRUE);
			if (tape.TopMost)
				CheckDlgButton(hWnd, ID_TOPMOST, BST_CHECKED);
			else
				CheckDlgButton(hWnd, ID_TOPMOST, BST_UNCHECKED);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			hStatus = CreateWindowEx( 0, STATUSCLASSNAME, (PCTSTR)NULL, WS_CHILD | WS_VISIBLE | CCS_BOTTOM /*| SBARS_SIZEGRIP*/, 0, 264, 476, 24, hWnd, (HMENU)ID_STATUS, tape.Ds2hInst, NULL);
			int width[4] = { 70,140,412,-1 };
			SendMessage(hStatus, SB_SETPARTS, 4, LPARAM(width));
			SendMessage(hStatus, SB_SETTEXT, 0, WPARAM(I18N.Status_Wait));
			SendMessage(hStatus, WM_SETFONT, WPARAM(tape.hStatus), TRUE);
			hDCStatus = GetDC(hStatus);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			hWebMenu = CreateWindowEx(0, L"button", L"≡", WS_CHILD | BS_FLAT | BS_CENTER, 0, 0, 22, 17, hWnd, (HMENU)ID_WEBMENU, tape.Ds2hInst, NULL);

			SendMessage(hWebMenu, WM_SETFONT, WPARAM(tape.hWeb), TRUE);
			CreateToolTip(hWnd, hWebMenu, I18N.HELP_WEB_MENU);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			hWebClose = CreateWindowEx(0, L"button", L"✕", WS_CHILD | BS_FLAT | BS_VCENTER | BS_CENTER, 454, 0, 22, 17, hWnd, (HMENU)ID_WEBCLOSE, tape.Ds2hInst, NULL);

			SendMessage(hWebClose, WM_SETFONT, WPARAM(tape.hCancel), TRUE);
			CreateToolTip(hWnd, hWebClose, I18N.HELP_WEB_CLOSE);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			hTab_Explorer = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, WC_TABCONTROL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | TCS_FIXEDWIDTH | TCS_TOOLTIPS | TCS_OWNERDRAWFIXED, 19, 0, 435, 17, hWnd, (HMENU)ID_TABEXPLORER, tape.Ds2hInst, NULL);

			TCITEM tc_item;
			tc_item.mask = TCIF_TEXT;
			wchar_t tabtxt[256];
			tc_item.pszText = WCHARI(L"1");
			TabCtrl_InsertItem(hTab_Explorer, 0, &tc_item);
			tc_item.pszText = WCHARI(L"+");
			TabCtrl_InsertItem(hTab_Explorer, 1, &tc_item);

			SendMessage(hTab_Explorer, WM_SETFONT, WPARAM(tape.hTab), TRUE);
			TabCtrl_SetItemSize(hTab_Explorer, 18, 17);
			TabCtrl_SetPadding(hTab_Explorer, 0, 0);
			TabCtrl_SetCurSel(hTab_Explorer, 0);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			hTab_DeleteDF = CreateWindowEx(0, L"Static", L"", WS_CHILD | SS_BITMAP | SS_CENTERIMAGE, 188, 94, 100, 100, hWnd, nullptr, tape.Ds2hInst, nullptr);

			HDC memoryDC = CreateCompatibleDC(NULL);
			HBITMAP m_DeleteDF = CreateCompatibleBitmap(memoryDC, 100, 100);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(memoryDC, m_DeleteDF);
			SelectObject(memoryDC, tape.hDelete);
			std::wstring text = L"deleting\ndata\nfolder";
			RECT rect = { 0,19,100,100 };
			SetTextColor(memoryDC, tape.ink_STATIC);
			SetBkMode(memoryDC, TRANSPARENT);
			SetBkColor(memoryDC, tape.Bk_STATIC);
			DrawText(memoryDC, text.c_str(), text.size(), &rect, DT_CENTER | DT_WORDBREAK);
			BITMAPINFO Bitmapinfo = { 0 };
			Bitmapinfo.bmiHeader.biSize = sizeof(Bitmapinfo.bmiHeader);
			GetDIBits(memoryDC, m_DeleteDF, 0, 0, NULL, &Bitmapinfo, DIB_RGB_COLORS);
			DeleteDC(memoryDC);
			
			SendMessage(hTab_DeleteDF, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_DeleteDF);
/*
			OpenClipboard(Ds2hWnd);
			EmptyClipboard();
			SetClipboardData(CF_BITMAP, m_DeleteDF);
			CloseClipboard();

			HDC hDC = GetDC(hTab_DeleteDF);
			HDC memoryDC2 = CreateCompatibleDC(hDC);
			BITMAP Bitmap;
			GetObject(m_DeleteDF, sizeof(Bitmap), &Bitmap);
			SelectObject(memoryDC2, m_DeleteDF);

			PAINTSTRUCT ps;
			BeginPaint(hTab_DeleteDF, &ps);
			StretchBlt(hDC, 0, 0, 100, 100, memoryDC2, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
			EndPaint(hTab_DeleteDF, &ps);
			DeleteDC(memoryDC2);
			ReleaseDC(hTab_DeleteDF, hDC);
*/
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			//echo(L"https://github.com/ytyra/Ds2vJoy 31/07/2021");
			std::wstring datestring = std::to_wstring(tape.VersionDate);
			datestring = I18N.LinksSatusString
				+ datestring.std::wstring::substr(0, 4) + L" "
				+ datestring.std::wstring::substr(4, 2) + L" "
				+ datestring.std::wstring::substr(6, 2) + L" - "
				+ datestring.std::wstring::substr(8, (datestring.length() - 8));
			wcscpy_s(LinksSatusString, wcslen(datestring.c_str()) + 1, datestring.c_str());
			tasktray.Show();
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			dest.Init(true);
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			srce.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			if (tape.DsvJoyAddedToGuardian)
				echo(I18N.Guardian_Added_to_Guardian, I18N.APP_TITLE, tape.Ds2vJoyPID);
			hid.Init();
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
			xi.Init();
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			if (tape.PreferredSource != 1 && tape.PreferredSource != 2)
				echo(I18N.ds_notforuse);
			if (tape.PreferredSource != 3)
				echo(I18N.di_notforuse);
			if (tape.PreferredSource != 4)
				echo(I18N.xi_notforuse);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		{
			SendMessage(hWnd, WM_TRANSPARENCY, 0, 0);
			SendMessage(hWnd, WM_DISPLAYCHANGE, 0, 0);
			if (!tape.Tasktray)
				ShowWindow(hWnd, SW_SHOW);
			::SetWindowPos(hWnd, (tape.TopMost && !tape.Tasktray) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DEFERERASE | SWP_NOMOVE | SWP_NOSIZE);
		}
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		std::thread(WM_CREATE_END, hWnd).detach();
		break;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			if (!dest.Active() && tape.vJoyDevice)
				SendMessage(hWnd, WM_DEVICE_DEST_START, 0, 1);
			if (!srce.Active() && tape.PreferredSource)
				SendMessage(hWnd, WM_DEVICE_SRCE_START, 0, 1);
			hid.WhitelistCheck();
		}
		else if (wParam == 2)
		{
/*
			static COLORREF ledcolor;
			ledcolor = tape.LED_Color;
			if (ds.Active())
			{
				ds.SetLED(GetRValue(ledcolor), GetGValue(ledcolor), GetBValue(ledcolor));
				ds.Write();
			}
*/
			CPULimiter limiter = 1;		//CPU percents

			static COLORREF ledcolor;
			static byte R = 0;
			static byte G = 0;
			static byte B = 0;
			static byte Rval = 0;
			static byte Gval = 0;
			static byte Bval = 0;

			const double π = 3.141592653589793;
			const double δ = 0.72;
			const double β = -0.0004314;
			const double γ = 0.0000003076;
			static double chromatic;
			static int frequency;
			static int phase = -1;
			static int phasedelta;
			static double colorphase;

			if (ledcolor != tape.LED_Color)
			{
				ledcolor = tape.LED_Color;
				R = GetRValue(ledcolor); G = GetGValue(ledcolor); B = GetBValue(ledcolor);
				int α = (R + G + B); //* (100 - colorphase) / 100;
				chromatic = δ + β * α + γ * α * α;
				phasedelta = (α - 485) / 24;
			}

			if (phase < 0) { frequency = 16 + tape.WaveSpeed + phasedelta + (rand() % (int)(round((double)tape.WaveSpeed * 0.227451) + 5)); phase = frequency / 2; colorphase = chromatic * ((double)100 - (rand() % 26)) / 100; }
			double LightwaVe = abs(sin(2 * π * phase / frequency));
			Rval = int(R - (R * LightwaVe * colorphase));
			Gval = int(G - (G * LightwaVe * colorphase));
			Bval = int(B - (B * LightwaVe * colorphase));
			if (srce.Active())
			{
				srce.SetLED(Rval, Gval, Bval);
				srce.Write();
			}
			phase--;

			limiter.CalculateAndSleep();
		}
		else if (wParam == 3)
		{
			static char moduloStatus = -1;
			if (moduloStatus++ == 39)
				moduloStatus = -1;

			if (!IsIconic(hWnd) && !isFullScreen)
			{
				//Ensure to actualize all the bar
				SendMessageTimeout(hStatus, SB_SETBKCOLOR, 0, LPARAM(RGB(255, 255, 255)), SMTO_BLOCK, 15, NULL);

				//Battery
				if (!moduloStatus)
					if (srce.Active())
					{
						if (tape.ActualSource < 3)
						{
							static bool LowBatt = false;
							bool isBT = srce.isBT();
							if (tape.BatteryLevel < 11)
							{
								if (!LowBatt)
								{
									LowBatt = true;
									if (tape.ActualSource == 2) srce.SetOrangeLED(2);
								}
							}
							else if (LowBatt)
							{
								LowBatt = false;
								if (tape.ActualSource == 2) srce.SetOrangeLED(0);
							}
							if (tape.ActualSource == 1 && !tape.BatteryCharge)
								isBT = true;
							WCHAR buf[20];
							swprintf_s(buf, sizeof(buf), (isBT) ? L"BT (%s%d%%)" : L"USB (%s%d%%)", tape.BatteryCharge ? L"+" : L"", tape.BatteryLevel);
							SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(buf), SMTO_BLOCK, 15, NULL);
							tasktray.Tip(buf);
						}
						else if (tape.ActualSource == 3)
						{
							SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Active), SMTO_BLOCK, 15, NULL);
							tasktray.Tip(I18N.Status_Active);
						}
						else
						{
							if (tape.BatteryCharge)
							{
								SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Charge), SMTO_BLOCK, 15, NULL);
								tasktray.Tip(I18N.Status_Charge);
							}
							else
							{
								switch (tape.BatteryLevel)
								{
								case 0:
								{
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Active), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(I18N.Status_Active);
									break;
								}
								case 10:
								{
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Empty), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(I18N.Status_Empty);
									break;
								}
								case 40:
								{
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Low), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(I18N.Status_Low);
									break;
								}
								case 70:
								{
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Medium), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(I18N.Status_Medium);
									break;
								}
								case 100:
								{
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Full), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(I18N.Status_Full);
									break;
								}
								}
							}
						}
					}
					else
					{
						if (tape.PreferredSource)
						{
							SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Wait), SMTO_BLOCK, 15, NULL);
							tasktray.Tip(I18N.Status_Wait);
						}
						else
						{
							WCHAR buf[20];
							if (tape.KeyboardActive)
							{
								if (tape.MouseActive)
								{
									swprintf_s(buf, sizeof(buf), L"%s + %s", I18N.SETTINGS_KBD, I18N.SETTINGS_MSE);
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(buf), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(buf);
								}
								else
								{
									SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.SETTINGS_KBD), SMTO_BLOCK, 15, NULL);
									tasktray.Tip(I18N.SETTINGS_KBD);
								}
							}
							else if (tape.MouseActive)
							{
								SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.SETTINGS_MSE), SMTO_BLOCK, 15, NULL);
								tasktray.Tip(I18N.SETTINGS_MSE);
							}
							else
							{
								SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Wait), SMTO_BLOCK, 15, NULL);
								tasktray.Tip(I18N.Status_Wait);
							}
						}
					}

				//Latency & Mag Initialized
				if (!(moduloStatus % 10))
					if (srce.Active())
					{
						WCHAR buf[20];
						if (tape.MagInitialized)
							swprintf_s(buf, TEXT("%0.5f ms*"), average);
						else
							swprintf_s(buf, TEXT("%0.5f ms"), average);
						SendMessageTimeout(hStatus, SB_SETTEXT, 1, LPARAM(buf), SMTO_BLOCK, 15, NULL);
					}
					else
						SendMessageTimeout(hStatus, SB_SETTEXT, 1, LPARAM(L""), SMTO_BLOCK, 15, NULL);

				//Status informations by page
					switch (TabCtrl_GetCurSel(hTab))
					{
					case 0:
					{
						time_t rawtime;
						struct tm timeinfo;
						time(&rawtime);
						localtime_s(&timeinfo, &rawtime);

						//https://www.cplusplus.com/reference/ctime/strftime/
						if (wcsftime(LogSatusString, 100, I18N.LogSatusString, &timeinfo))
							SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(LogSatusString), SMTO_BLOCK, 15, NULL);
						break;
					}
					case 1:
					{
						swprintf_s(SettingsSatusString, sizeof(SettingsSatusString), I18N.SettingsSatusString, GetRValue(COLORREFforInfo), GetGValue(COLORREFforInfo), GetBValue(COLORREFforInfo), GetRValue(COLORREFforInfo), GetGValue(COLORREFforInfo), GetBValue(COLORREFforInfo));
						SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(SettingsSatusString), SMTO_BLOCK, 15, NULL);
						break;
					}
					case 2: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(MappingSatusString), SMTO_BLOCK, 15, NULL); break; }
					case 3: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(RapidFireSatusString), SMTO_BLOCK, 15, NULL); break; }
					case 4: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(KeymapSatusString), SMTO_BLOCK, 15, NULL); break; }
					case 5: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(XOutputSatusString), SMTO_BLOCK, 15, NULL); break; }
					case 6: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(hid.GuardianButtons()), SMTO_BLOCK, 15, NULL); break; }
					case 8: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(LinksSatusString), SMTO_BLOCK, 15, NULL); break; }
					}

				//Mode, Profile & Stance
				if (!(moduloStatus % 2))
				{
					static unsigned short LastTrayIcon = 0;
					static unsigned short ActualTrayIcon = 0;
					ActualTrayIcon = ((tape.Profile - 1) * 40) + ((mode - 1) * 5) + tape.Stance;
					if (ActualTrayIcon != LastTrayIcon)
					{
						tasktray.m_nid.hIcon = tape.hIconTray[ActualTrayIcon];
						Shell_NotifyIcon(NIM_MODIFY, &tasktray.m_nid);
						LastTrayIcon = ActualTrayIcon;
						SendMessageTimeout(hStatus, SB_SETTEXT, 3, LPARAM((L"M:" + std::to_wstring(mode) + L" P:" + std::to_wstring(tape.Profile) + L" S:" + std::to_wstring(tape.Stance + 1)).c_str()), SMTO_BLOCK, 15, NULL);
					}
				}

				//Get pixel color under mouse
				std::thread(GetPixelForInfo).detach();

				//Invert satus bar colors if Dark theme
				if (tape.DarkTheme)
					BitBlt(hDCStatus, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, NULL, DSTINVERT);
			}
		}
		else if (wParam == 4)
		{
			if (!GetCursorPos(&tape.mousepoint))
				break;

			if (m_flag_drag)
			{
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				{
					//Not needed in web tab window flag is WS_CAPTION and can naturally receive WM_NCLBUTTONUP message
					if (TabCtrl_GetCurSel(hTab) != 7 || NotepadTab != 7)
						PostMessage(hWnd, WM_NCLBUTTONUP, 0, 0);
				}
				else
				{
					m_flag_drag++;
					if (m_flag_drag == 4)
					{
						FirstMove = true;
						SendMessage(hWnd, WM_MOVE, 0, 0);
					}
					if (m_flag_drag > 3 && !FirstMove)
					{
						if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
							::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x - x, tape.mousepoint.y - y, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE);
						else
							::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x - x, tape.mousepoint.y - y, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
					}
				}
			}
			else if (m_flag_size)
			{
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				{
					if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
						PostMessage(hWnd, WM_NCLBUTTONUP, 0, 0);
				}
				else
				{
					RECT rect;
					GetWindowRect(hWnd, &rect);
					switch (m_flag_size)	//W-E-N-S-NW-SE-NE-SW
					{
					case 1: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x, rect.top, rect.right - tape.mousepoint.x, rect.bottom - rect.top, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 2: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, rect.top, tape.mousepoint.x - rect.left, rect.bottom - rect.top, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 3: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, tape.mousepoint.y, rect.right - rect.left, rect.bottom - tape.mousepoint.y, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 4: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, rect.top, rect.right - rect.left, tape.mousepoint.y - rect.top, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 5: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x, tape.mousepoint.y, rect.right - tape.mousepoint.x, rect.bottom - tape.mousepoint.y, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 6: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, rect.top, tape.mousepoint.x - rect.left, tape.mousepoint.y - rect.top, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 7: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, tape.mousepoint.y, tape.mousepoint.x - rect.left, rect.bottom - tape.mousepoint.y, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					case 8: { ::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x, rect.top, rect.right - tape.mousepoint.x, tape.mousepoint.y - rect.top, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break; }
					}
				}
			}
			else if (!IsIconic(hWnd) && IsWindowVisible(hWnd) && !isFullScreen)
			{
				if (TabCtrl_GetCurSel(hTab) == 7)
				{
					if (!WebMenuVisible && tape.isExplorerLoaded)
					{
						static size_t tab = -1;
						static bool entered_hTab_Explorer = false;
						static size_t lastview_hTab_Explorer = -1;
						if (!IsIconic(hWnd) && IsWindowVisible(hTab_Explorer) && !isFullScreen)
						{
							TCHITTESTINFO tabinfo;
							POINT pt = tape.mousepoint;
							ScreenToClient(hTab_Explorer, &pt);
							tabinfo.pt = pt;
							tab = TabCtrl_HitTest(hTab_Explorer, &tabinfo);
							if (tab < web_tabs.size() && tab != -1)
							{
								MouseIsOverTab = true;
								if (lastview_hTab_Explorer == -1)
								{
									lastview_hTab_Explorer = 0;
									web_tabs[tape.web_actualtab]->OnMouseOut();
								}
								if (tab != lastview_hTab_Explorer || entered_hTab_Explorer == false)
								{
									entered_hTab_Explorer = true;
									web_tabs[lastview_hTab_Explorer]->Hide();
									lastview_hTab_Explorer = tab;
									web_tabs[tab]->OnMouseOut();
									web_tabs[tab]->Show();
								}
							}
							else if (entered_hTab_Explorer)
							{
								MouseIsOverTab = false;
								entered_hTab_Explorer = false;
								web_tabs[lastview_hTab_Explorer]->Hide();
								lastview_hTab_Explorer = -1;
								web_tabs[tape.web_actualtab]->OnMouseOver();
								web_tabs[tape.web_actualtab]->Show();
							}
						}
						if (tab == -1)
						{
							if (tab)
								ShowWindow(hTab_Explorer, SW_SHOW);
							RECT win;
							GetWindowRect(hWnd, &win);
							if (MouseIsOverMain)
							{
								if (!PtInRect(&win, tape.mousepoint))
								{
									MouseIsOverTab = false;
									MouseIsOverMain = false;
									RECT win;
									GetWindowRect(hWnd, &win);
									win.left += 7;
									win.right -= win.left + 7;
									win.bottom -= win.top + 7;
									DWORD style = GetWindowLong(hWnd, GWL_STYLE);
									SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_BORDER);
									SetWindowPos(hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
									ShowWindow(hWebMenu, SW_HIDE);
									if (tab == -1)
										ShowWindow(hWebClose, SW_HIDE);
									ShowWindow(hTab_Explorer, SW_HIDE);
									web_tabs[tape.web_actualtab]->OnMouseOut();
								}
							}
							else
							{
								if (PtInRect(&win, tape.mousepoint))
								{
									MouseIsOverMain = true;
									RECT win;
									GetWindowRect(hWnd, &win);
									win.left -= 7;
									win.right -= win.left - 7;
									win.bottom -= win.top - 7;
									DWORD style = GetWindowLong(hWnd, GWL_STYLE);
									SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
									SetWindowPos(hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
									ShowWindow(hTab_Explorer, SW_SHOW);
									ShowWindow(hWebMenu, SW_SHOW);
									ShowWindow(hWebClose, SW_SHOW);
									web_tabs[tape.web_actualtab]->OnMouseOver();
								}
							}
						}
					}
				}
				else if (TabCtrl_GetCurSel(hTab) == 9)
				{
					RECT win;
					GetWindowRect(hWnd, &win);
					if (MouseIsOverMain)
					{
						if (!PtInRect(&win, tape.mousepoint))
						{
							MouseIsOverTab = false;
							MouseIsOverMain = false;
							RECT win;
							GetWindowRect(hWnd, &win);
							win.left += 7;
							win.right -= win.left + 7;
							win.bottom -= win.top + 7;
							DWORD style = GetWindowLong(hWnd, GWL_STYLE);
							SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_BORDER);
							SetWindowPos(hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
						}
					}
					else
					{
						if (PtInRect(&win, tape.mousepoint))
						{
							MouseIsOverMain = true;
							RECT win;
							GetWindowRect(hWnd, &win);
							win.left -= 7;
							win.right -= win.left - 7;
							win.bottom -= win.top - 7;
							DWORD style = GetWindowLong(hWnd, GWL_STYLE);
							if (NotepadTab == 7)
								SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
							else
								SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
							SetWindowPos(hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
						}
					}
				}
			}
		}
		else if (wParam == 5)
		{
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
				PostMessage(hWnd, WM_COMMAND, ID_WEBCLOSE, -1);
			break;
		}
		else if (wParam == 6)
		{
			ShowWindow(hTab, SW_HIDE);
			ShowWindow(hTab, SW_SHOW);
			KillTimer(hWnd, 6);
			break;
		}
		else if (wParam == 7)
		{
			ShowWindow(hTab_Explorer, SW_HIDE);
			ShowWindow(hTab_Explorer, SW_SHOW);
			KillTimer(hWnd, 7);
			break;
		}
		break;
	}
	case WM_CHANGE_LANGUAGE:
	{
		wm_pause = true;

		::ShowWindow(hTopMost, SW_HIDE);
		::ShowWindow(hTab, SW_HIDE);
		sDlg.Hide();

		DWORD dwStyle = WS_VISIBLE | WS_POPUP & ~WS_THICKFRAME;
		hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, dwStyle, GetSystemMetrics(SM_CXSCREEN) / 2 - 150, GetSystemMetrics(SM_CYSCREEN) / 2 - 100, 200, 20, hWnd, (HMENU)0, tape.Ds2hInst, NULL);
		SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 14));
		SendMessage(hProgressBar, PBM_SETSTEP, (WPARAM)1, 0);
		SetWindowPos(hProgressBar, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

		tasktray.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		sDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		dDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		mDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		mDlg2.Init(true);	//Clone
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		rDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		kDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		xDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		gDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		lDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		nDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		mDDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		rDDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		kDDlg.Init();
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		PostMessage(hProgressBar, WM_CLOSE, 0, 0);

		::ShowWindow(hTopMost, SW_SHOW);
		::ShowWindow(hTab, SW_SHOW);
		sDlg.Show();
		PostMessage(hWnd, WM_SIZE, 0, -1);

		wm_pause = false;
		break;
	}
	case WM_RESET:
	{
		Mappings Mappingdatatmp;
		RapidFires RapidFiredatatmp;
		Keymaps Keymapdatatmp;
		tape.Mappingdata = Mappingdatatmp;
		tape.RapidFiredata = RapidFiredatatmp;
		tape.Keymapdata = Keymapdatatmp;
		break;
	}
	case WM_PAUSE:
	{
		if (wm_reload)
			return false;

		wm_pause = true;
		tape.CallbackPaused = true;
		srce.GetButton(SrceButtonID::LX)->SetThreshold();
		srce.GetButton(SrceButtonID::LY)->SetThreshold();
		srce.GetButton(SrceButtonID::RX)->SetThreshold();
		srce.GetButton(SrceButtonID::RY)->SetThreshold();
		dest.Close();
		srce.Close();

		return true;
	}
	case WM_RESTART:
	{
		wm_pause = false;

		SendMessage(hWnd, WM_DEVICE_DEST_START, 0, lParam);
		SendMessage(hWnd, WM_DEVICE_SRCE_START, 0, lParam);

		tape.CallbackPaused = false;
		break;
	}
	case WM_RELOAD:
	{
		// wParam == Profile
		// lParam == 1 silent
		if (tape.MagInitialized)
			SetMagnifyZoom(MAG_METHOD_RESET, 0, 0, 0);
		if (wm_reload)
			break;

		wm_pause = false;
		wm_reload = true;
		tape.CallbackPaused = true;
		LogSatusString[0] = '\0';
		SettingsSatusString[0] = '\0';
		MappingSatusString[0] = '\0';
		RapidFireSatusString[0] = '\0';
		KeymapSatusString[0] = '\0';
		XOutputSatusString[0] = '\0';
		SendMessage(hWnd, WM_TIMER, 6, 0);

		PreviousTab = TabCtrl_GetCurSel(hTab);
		PreviousNotepadTab = NotepadTab;
		TabCtrl_SetCurFocus(hTab, 0);

		{
			if ((wParam == 1) || (wParam == 2) || (wParam == 3))
			{
				tape.Save(tape.Setting_All);
				tape.Profile = (unsigned char)wParam;
				tape.Save(tape.Setting_Profile);
				if (!lParam)
					echo(I18N.TaskTray_ProfileChanged, tape.Profile);
			}
			else
				hid.RestartDevices(true);
		}

		if (!lParam)
			echo(I18N.Settings_Change_Settings);

		xi.CloseClient();
		srce.Close();
		dest.Close();
		SendMessage(hWnd, WM_RESET, 0, 0);

		tape.Load(Settings::Setting_All);
		mDlg.Hide();
		mDDlg.m_mode = 0;

		dest.Init();
		xi.Init();
		hid.Init();

		SendMessage(hWnd, WM_DISPLAYCHANGE, 0, 0);
		SendMessage(hWnd, WM_CREATE_MENU, 0, 0);
		wm_reload = false;
		SendMessage(hWnd, WM_DEVICE_DEST_START, 0, lParam);
		SendMessage(hWnd, WM_DEVICE_SRCE_START, 0, lParam);
		break;
	}
	case WM_DEVICE_DEST_START:
	{
		// lParam == 1 silent
		if (wm_reload || wm_pause || wm_deststart)
			break;

		wm_deststart = true;
		tape.CallbackPaused = true; 

		dest.Close();
		if(!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		if (tape.vJoyDevice)
		{
			if (dest.Open(tape.vJoyDevice, !lParam))
				cbParams.vJoyID = tape.vJoyDevice;
			else if (!lParam)
				echo(I18N.vJoy_wait);
		}
		else if (!lParam)
			echo(I18N.vJoy_notforuse);

		tape.CallbackPaused = false;
		wm_deststart = false;

		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		break;
	}
	case WM_DEVICE_SRCE_LIST:
	{
		srce.ListOfJoysticks();

		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		break;
	}
	case WM_DEVICE_SRCE_START:
	{
		// lParam == 1 silent
		if (wm_reload || wm_pause || wm_srcestart)
			break;

		tape.ActualSource = 0;
		wm_srcestart = true;
		tape.CallbackPaused = true;
		tape.MouseMovePaused = true;

		srce.Close();
		dest.Clear();
		srce.GetButton(SrceButtonID::LX)->SetThreshold();
		srce.GetButton(SrceButtonID::LY)->SetThreshold();
		srce.GetButton(SrceButtonID::RX)->SetThreshold();
		srce.GetButton(SrceButtonID::RY)->SetThreshold();

		srce.SetCallback(GeneralMotor, &cbParams);
		srce.SetTriggers(tape.TriggersMode);
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		{
			cbParams.mappings.clear();
			cbParams.mappings[0].PreLoad();
			size_t max = tape.Mappingdata.size();
			for (int i = 0; i < 32; i++)
				tape.destUsed[i] = false;
			for (int i = 0; i < max; i++)
			{
				Mapping* data = &tape.Mappingdata[i];
				if (data->LoadDevice(&srce, &dest))
					cbParams.mappings.push_back(*data);
			}
		}
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		if (tape.SplitTouch)
		{
			cbParams.splittouch = srce.GetButton(SourceButton::TOUCH);
			cbParams.splitCol = tape.TouchCol;
			cbParams.splitRow = tape.TouchRow;
			cbParams.splitButton = tape.TouchPadButton;
		}
		else
			cbParams.splittouch = 0;

		{
			cbParams.rapidfires.clear();
			size_t length = tape.RapidFiredata.size();
			for (int i = 0; i < length; i++)
			{
				if (tape.RapidFiredata[i].LoadDevice(&dest))
					cbParams.rapidfires.push_back(tape.RapidFiredata[i]);
			}
		}
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		{
			cbParams.keymaps.clear();
			size_t max = tape.Keymapdata.size();
			for (int i = 0; i < max; i++)
			{
				Keymap* data = &tape.Keymapdata[i];
				if (data->LoadDevice(&dest))
					cbParams.keymaps.push_back(*data);
			}
		}
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		if (tape.XOutputActive && !xi.xoutput_connected)
		{
			xi.CloseClient();
			xi.LoadDevice(&dest);
			xi.InitClient(true);
			tape.XOutputActive = true;
		}
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		cbParams.NextStepFlag = false;

		srce.SetSerial(tape.Serial);

		{
			mDlg.redrawTabs(mDlg.m_Tab, PreviousTab == 2 || TabCtrl_GetCurSel(hTab) == 2);
			mDlg2.SetTab(mDlg2.m_Tab, false);
			if (PreviousTab == 9)
			{
				TabCtrl_SetCurFocus(hTab, PreviousNotepadTab);
				TCITEM tc_item;
				tc_item.mask = TCIF_TEXT;
				tc_item.pszText = WCHARI(L"");
				TabCtrl_InsertItem(hTab, 9, &tc_item);
				TabCtrl_SetCurFocus(hTab, 9);
			}
			else if (PreviousTab != 15)
				TabCtrl_SetCurFocus(hTab, PreviousTab);
			PreviousTab = 15;
		}
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);

		srce.PreOpen(!lParam);
		if (tape.PreferredSource == 4)
		{
			if (srce.Active())
			{
				tape.MouseMovePaused = false;
				if (!srce.Open(hWnd, !lParam))
					srce.Close();
			}
			else if (!lParam)
				echo(I18N.xi_wait);
		}
		else if (tape.PreferredSource == 3)
		{
			if (srce.Active())
			{
				tape.MouseMovePaused = false;
				if (!srce.Open(hWnd, !lParam))
					srce.Close();
			}
			else if (!lParam)
				echo(I18N.di_wait);
		}
		else if (tape.PreferredSource)
		{
			if (srce.Active())
			{
				tape.MouseMovePaused = false;
				srce.SetOrangeLED(0x00);
				srce.SetWhiteLED(0x00);
				if (!srce.Open(hWnd, !lParam))
					srce.Close();
			}
			else if (!lParam)
				echo(I18N.ds_wait);
		}
		else
			srce.Open(hWnd, !lParam);

		tape.CallbackPaused = false;
		wm_srcestart = false;
		if (!done_WM_CREATE)
			SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		break;
	}
	case WM_SETORANGELED:
	{
		if (srce.Active() && tape.ActualSource == 2)
			srce.SetOrangeLED((byte)wParam);
		break;
	}
	case WM_SETWHITELED:
	{
		if (srce.Active() && tape.ActualSource == 2)
			srce.SetWhiteLED((byte)wParam);
		break;
	}
	case WM_SETTRIGGERS:
	{
		if (srce.Active() && tape.ActualSource == 2)
		{
			srce.SetTriggers((int)wParam);
			srce.Write();
		}
		break;
	}
	case WM_SETVJOY:
	{
		switch (lParam)
		{
		case 0:
		{
			sDlg.Hide();
			vDlg.Show();
			break;
		}
		case 1:
		{
			sDlg.Show();
			vDlg.Hide();
			break;
		}
		}
		break;
	}
	case WM_SETDINPUT:
	{
		switch (lParam)
		{
		case 0:
		{
			sDlg.Hide();
			dDlg.Show();
			break;
		}
		case 1:
		{
			sDlg.Show();
			dDlg.Hide();
			break;
		}
		}
		break;
	}
	case WM_ADDMAPPING:
	{
		switch (LOWORD(lParam))
		{
		case 0:
		{
			srce.GetButton(SrceButtonID::LX)->SetThreshold();
			srce.GetButton(SrceButtonID::LY)->SetThreshold();
			srce.GetButton(SrceButtonID::RX)->SetThreshold();
			srce.GetButton(SrceButtonID::RY)->SetThreshold();
			cbParams.mappings.clear();
			cbParams.mappings[0].PreLoad();
			size_t max = tape.Mappingdata.size();
			for (int i = 0; i < 32; i++)
				tape.destUsed[i] = false;
			for (int i = 0; i < max; i++)
			{
				Mapping* data = &tape.Mappingdata[i];
				if (data->LoadDevice(&srce, &dest))
					cbParams.mappings.push_back(*data);
			}
			break;
		}
		case 1:
		{
			switch ((int)wParam)
			{
			case 0: { mDlg.SetTab(mDlg.m_Tab); break;}
			case 1: { mDlg.SetTab(HIWORD(lParam)); mDlg.addMappingDlgBack(); break; }
			case 2: { mDlg.SetTab(HIWORD(lParam)); mDlg.editMappingDlgBack(); break; }
			case 3: { mDlg.SetTab(HIWORD(lParam)); mDlg.editMappingDlgBackMulti(); break; }
			}
			if ((int)wParam == 4)
				mDlg2.SetTab(HIWORD(lParam));
			else if (HIWORD(lParam) == mDlg2.m_Tab && mDlg2.m_isCloned)
				mDlg2.SetTab(mDlg2.m_Tab);
			break;
		}
		case 2:
		{
			switch ((int)wParam)
			{
			case 0: { mDlg2.SetTab(mDlg2.m_Tab); break; }
			case 1: { mDlg2.SetTab(HIWORD(lParam)); mDlg2.addMappingDlgBack(); break; }
			case 2: { mDlg2.SetTab(HIWORD(lParam)); mDlg2.editMappingDlgBack(); break; }
			case 3: { mDlg2.SetTab(HIWORD(lParam)); mDlg2.editMappingDlgBackMulti(); break; }
			}
			if (HIWORD(lParam) == mDlg.m_Tab)
				mDlg.SetTab(mDlg.m_Tab);
			break;
		}
		}
		break;
	}
	case WM_ADDRAPIDFIRE:
	{
		if ((int)lParam <= 0)
		{
			rDDlg.Hide();
			rDlg.Hide();
			if ((int)lParam == -1)
			{
				cbParams.rapidfires.clear();
				size_t length = tape.RapidFiredata.size();
				for (int i = 0; i < length; i++)
				{
					if (tape.RapidFiredata[i].LoadDevice(&dest))
						cbParams.rapidfires.push_back(tape.RapidFiredata[i]);
				}
			}
			rDlg.Show();
			PostMessage(hWnd, WM_SIZE, 0, -1);
		}
		else if ((int)lParam == 1)
		{
			if ((int)wParam == 1)
				rDlg.addRapidFireDlgBack();
			else if ((int)wParam == 2)
				rDlg.editRapidFireDlgBack();
			else if ((int)wParam == 3)
				rDlg.editRapidFireDlgBackMulti();
		}
		break;
	}
	case WM_CHANGE_PAD:
	{
		if (wParam == 0)
			xi.CloseClient();
		else if (wParam == 1)
		{
			xi.LoadDevice(&dest);
			xi.InitClient();
		}
		else if (wParam == 2)
			if (tape.XOutputActive)
			{
				xi.CloseClient();
				xi.LoadDevice(&dest);
				xi.InitClient();
			}
		break;
	}
	case WM_ADDKEYMAP:
	{
		if ((int)lParam <= 0)
		{
			kDDlg.Hide();
			kDlg.Hide();
			if ((int)lParam == -1)
			{
				cbParams.keymaps.clear();
				size_t max = tape.Keymapdata.size();
				for (int i = 0; i < max; i++)
				{
					Keymap* data = &tape.Keymapdata[i];
					if (data->LoadDevice(&dest))
						cbParams.keymaps.push_back(*data);
				}
			}
			kDlg.Show();
			PostMessage(hWnd, WM_SIZE, 0, -1);
		}
		else if ((int)lParam == 1)
		{
			if ((int)wParam == 1)
				kDlg.addKeymapDlgBack();
			else if ((int)wParam == 2)
				kDlg.editKeymapDlgBack();
			else if ((int)wParam == 3)
				kDlg.editKeymapDlgBackMulti();
		}
		break;
	}
	case WM_CHANGE_HIDS:
	{
		if (wParam == 0)
		{
			hid.WhitelistInit();
			hid.BlacklistInit(-1);
		}
		else if (wParam == 1)
			hid.BlacklistInit((int)lParam);
		else if (wParam == 2)
			hid.WhitelistCheck((int)lParam);
		else
			std::thread(OutRun).detach();
		break;
	}
	case WM_CREATE_NEW_TAB:
	{
		int desttab = web_tabs.size();
		RECT win;
		GetWindowRect(tape.Ds2hWnd, &win);
		std::wstring startpage = (LPCWSTR)wParam;
		web_tabs.push_back(std::make_unique<ExplorerDlg>((startpage == L"") ? initialUri : startpage, true, tape.DefaultZoomValue, win));
		TCITEM tc_item;
		tc_item.mask = TCIF_TEXT;
		wchar_t tabtxt[256];
		swprintf_s(tabtxt, L"%d", desttab + 1);
		tc_item.pszText = tabtxt;
		TabCtrl_InsertItem(hTab_Explorer, desttab, &tc_item);
		if (lParam)
		{
			tape.web_actualtab = desttab;
			TabCtrl_SetCurSel(hTab_Explorer, desttab);
			PostMessage(hWnd, WM_SIZE, 0, 0);
		}
		else
			web_tabs[desttab]->Hide();
		break;
	}
	case WM_CLOSE_ALL_TABS:
	{
		while (web_tabs.size() > 1)
		{
			if (tape.web_actualtab)
			{
				tape.web_actualtab = tape.web_actualtab - 1;
				web_tabs.erase(web_tabs.begin() + tape.web_actualtab);
				TabCtrl_DeleteItem(hTab_Explorer, tape.web_actualtab);
			}
			else
			{
				web_tabs.erase(web_tabs.begin() + tape.web_actualtab + 1);
				TabCtrl_DeleteItem(hTab_Explorer, tape.web_actualtab + 1);
			}
		}
		TCITEM tc_item;
		tc_item.mask = TCIF_TEXT;
		tc_item.pszText = WCHARI(L"1");
		TabCtrl_SetItem(hTab_Explorer, 0, &tc_item);
		TabCtrl_SetCurSel(hTab_Explorer, tape.web_actualtab);
		break;
	}
	case WM_DELETE_DATA_FOLER:
	{
		ShowWindow(hTab_DeleteDF, SW_SHOW);
		web_tabs[tape.web_actualtab]->Hide();
		SetWindowPos(hTab_DeleteDF, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

		SendMessage(hWnd, WM_CLOSE_ALL_TABS, 0, 0);
		web_tabs[tape.web_actualtab]->CleanupUserDataFolder();

		ShowWindow(hTab_DeleteDF, SW_HIDE);
		web_tabs[tape.web_actualtab]->ResizeEverything();
		web_tabs[tape.web_actualtab]->Show();
		break;
	}
	case WM_WEB_SCROLL:
	{
		web_tabs[tape.web_actualtab]->ScrollBy(wParam, lParam);
		break;
	}
	case WM_WEB_CHANGETAB:
	{
		int desttab = TabCtrl_GetCurSel(hTab_Explorer);
		if (lParam)
		{
			if (desttab < web_tabs.size() - 1)
			{
				web_tabs[desttab]->Hide();
				web_tabs[desttab]->OnMouseOut();
				tape.web_actualtab = desttab + 1;
				TabCtrl_SetCurSel(hTab_Explorer, desttab + 1);
			}
		}
		else
		{
			if (desttab)
			{
				web_tabs[desttab]->Hide();
				web_tabs[desttab]->OnMouseOut();
				tape.web_actualtab = desttab - 1;
				TabCtrl_SetCurSel(hTab_Explorer, desttab - 1);
			}
		}
		web_tabs[tape.web_actualtab]->ResizeEverything();
		web_tabs[tape.web_actualtab]->Show();
		break;
	}
	case WM_WEB_FULLSCREEN:
	{
		web_tabs[tape.web_actualtab]->ToggleFullScreen();
		break;
	}
	case WM_WEB_FAVORITE:
	{
		web_tabs[tape.web_actualtab]->NavigateToFavorite(lParam);
		break;
	}
	case WM_WEB_BACK:
	{
		web_tabs[tape.web_actualtab]->Back();
		break;
	}
	case WM_WEB_NEXT:
	{
		web_tabs[tape.web_actualtab]->Forward();
		break;
	}
	case WM_WEB_REFRESH:
	{
		web_tabs[tape.web_actualtab]->Refresh();
		break;
	}
	case WM_WEB_CANCEL:
	{
		web_tabs[tape.web_actualtab]->Cancel();
		break;
	}
	case WM_WEB_AUTOREFRESH:
	{
		web_tabs[tape.web_actualtab]->AutoRefresh();
		break;
	}
	case WM_WEB_ZOOM:
	{
		if (lParam)
			web_tabs[tape.web_actualtab]->ZoomPlus(1);
		else
			web_tabs[tape.web_actualtab]->ZoomMinus(1);
		break;
	}
	case WM_WEB_ZOOMRESET:
	{
		web_tabs[tape.web_actualtab]->ZoomReset();
		break;
	}
	case WM_WEB_ZOOMSET:
	{
		web_tabs[tape.web_actualtab]->ZoomSet();
		break;
	}
	case WM_WEB_VISIBILITY:
	{
		web_tabs[tape.web_actualtab]->ToggleVisibility();
		break;
	}
	case WM_WEB_SCREENSHOT:
	{
		web_tabs[tape.web_actualtab]->SaveScreenshot(true);
		break;
	}
	case WM_WEB_DARKMODE:
	{
		web_tabs[tape.web_actualtab]->DarkMode(lParam);
		break;
	}
	case WM_NOTEPAD_SCROLL:
	{
		nDlg.Scroll(lParam == 1);
		break;
	}
	case WM_SET_MAGNIFY:
	{
		SetMagnifyZoom(LOWORD(wParam), HIWORD(wParam), LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_CREATE_MENU:
	{
		tasktray.CreateMenu();
		break;
	}
	case WM_DPICHANGED:
	case WM_DISPLAYCHANGE:
	{
//		int bppScreen = wParam;
//		int WScreen = LOWORD(lParam);
//		int HScreen = HIWORD(lParam);

		//RECT rect;
		//GetClientRect(GetDesktopWindow(), &rect);
		//tape.W = (short)rect.right;
		//tape.H = (short)rect.bottom;

		auto activeWindow = GetActiveWindow();
		HMONITOR monitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);

		// Get the logical width and height of the monitor
		MONITORINFOEX monitorInfoEx;
		monitorInfoEx.cbSize = sizeof(monitorInfoEx);
		GetMonitorInfo(monitor, &monitorInfoEx);
		tape.W = monitorInfoEx.rcMonitor.right - monitorInfoEx.rcMonitor.left;
		tape.H = monitorInfoEx.rcMonitor.bottom - monitorInfoEx.rcMonitor.top;
		tape.w = (short)(tape.W / 2);
		tape.h = (short)(tape.H / 2);

		// Get the physical width and height of the monitor
		DEVMODE devMode;
		devMode.dmSize = sizeof(devMode);
		devMode.dmDriverExtra = 0;
		EnumDisplaySettings(monitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
		tape.Wp = devMode.dmPelsWidth;
		tape.Hp = devMode.dmPelsHeight;

		// Calculate the scaling factor
		tape.Hscale = double(tape.Wp) / double(tape.W);
		tape.Vscale = double(tape.Hp) / double(tape.H);

		tape.proportianality = (tape.W > tape.H) ? (double(tape.W) / double(tape.H)) : (double(tape.H) / double(tape.W));
		r = sqrt(tape.w * tape.w + tape.h * tape.h);
		double standard_r = sqrt(960 * 960 + 540 * 540);
		mousefactor = 0.000002225 * (r / standard_r) / 16974593;
		movefactor = 0.000001775 / 16974593;
		sniperfactor = 0.002425 / 257;
		raidfactor = 0.000055 * (r / standard_r) / 66049;
		touchfactor = 0.1666667 * (r / standard_r);
		slowfactor = 0.0833333 * (r / standard_r);
		accuracyfactor = 0.2 * (r / standard_r);
		SendMessage(hWnd, WM_SIZE, 0, 0);
		break;
	}
	//case WM_CHAR:
	//case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
/*
		// If bit 30, WM_KEYDOWN message is autorepeated
		if (!(lParam & (1 << 30)))
		{
			if (auto action = GetAcceleratorKeyFunction((UINT)wParam))
				action();
		}
*/
		break;
	}
	case WM_SCREENSHOT:
	{
		std::wstring filename = ExePath() + L"\\" + std::to_wstring(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		ScreenCapturePart(LOWORD(wParam), HIWORD(wParam), LOWORD(lParam), HIWORD(lParam), filename);
		break;
	}
	case WM_NCRBUTTONDOWN:
	case WM_TRANSPARENCY:
	{
		if (lParam)
		{
			tape.Transparency = !tape.Transparency;
			tape.Save(tape.Setting_Transparency);
		}
		if (tape.Transparency)
			SetWindowTransparent(hWnd, true, tape.Opacity);
		else
			SetWindowTransparent(hWnd, false, NULL);
		mDlg2.SetTransparency(tape.Transparency);
		mDDlg.SetTransparency(tape.Transparency);
		break;
	}
	case WM_NCLBUTTONDOWN:
	{
		if (!done_WM_CREATE)
			break;

		GetCursorPos(&tape.mousepoint);
		GetWindowRect(hWnd, &FirstMoveRect);
		x = (short)(tape.mousepoint.x - FirstMoveRect.left);
		y = (short)(tape.mousepoint.y - FirstMoveRect.top);

		switch ((TabCtrl_GetCurSel(hTab) != 7 && NotepadTab != 7) ? OCR_NORMAL : GetCursorType())
		{
		case OCR_SIZEWE:	{ if (x < 15) m_flag_size = 1; else m_flag_size = 2; break; }
		case OCR_SIZENS:	{ if (y < 15) m_flag_size = 3; else m_flag_size = 4; break; }
		case OCR_SIZENWSE:	{ if (x < 15) m_flag_size = 5; else m_flag_size = 6; break; }
		case OCR_SIZENESW:	{ if (x < 15) m_flag_size = 8; else m_flag_size = 7; break; }
		case OCR_NORMAL:	{ m_flag_drag = true; break; }
		}
		break;
	}
	case WM_NCLBUTTONUP:
	{
		if (!done_WM_CREATE)
			break;

		if (m_flag_size)
		{
			m_flag_size = false;
			PostMessage(hWnd, WM_SIZE, -1, -3);
		}
		else
		{
			short m_flag_drag_tmp = m_flag_drag;
			m_flag_drag = false;
			GetCursorPos(&tape.mousepoint);
			RECT win;
			GetWindowRect(hWnd, &win);
			x = (short)(tape.mousepoint.x - win.left);
			y = (short)(tape.mousepoint.y - win.top);
			mDDlg.movable = true;
			bool minimize = false;
			bool maximize = false;
			bool close = false;
			if (m_flag_drag_tmp < 20)
				if (y >= 0 && y <= 30)
				{
					short z = x;
					if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
					{
						RECT rect;
						GetClientRect(hWnd, &rect);
						z = z - rect.right + 476;
					}
					if (z > 345 && z < 392)
						minimize = true;
					else if (z > 392 && z < 438)
						maximize = true;
					else if (z > 438 && z < 485)
						close = true;
				}
			extended = (minimize || maximize || close) && lastextended;
			lastextended = extended;
			if (minimize || (close && tape.CloseMinimize))
			{
				if (m_flag_drag_tmp > 3)
				{
					extended = lastextended;
					::SetWindowPos(hWnd, HWND_TOPMOST, FirstMoveRect.left, FirstMoveRect.top, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE);
				}
				PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); break;
			}
			else if (maximize)
			{
				if (m_flag_drag_tmp > 3)
				{
					extended = lastextended;
					::SetWindowPos(hWnd, HWND_TOPMOST, FirstMoveRect.left, FirstMoveRect.top, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE);
				}
				PostMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); break;
			}
			else if (close)
			{
				if (m_flag_drag_tmp > 3)
				{
					extended = lastextended;
					::SetWindowPos(hWnd, HWND_TOPMOST, FirstMoveRect.left, FirstMoveRect.top, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE);
				}
				PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0); break;
			}
			if (m_flag_drag_tmp > 3 && !FirstMove)
			{
				RECT desk;
				ClientArea(&desk, true);
				if ((short)HIWORD(lParam) < desk.top + 2)
				{
					if (!extended)
					{
						CheckDlgButton(hWnd, ID_TOPMOST, BST_CHECKED);
						::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
						lastextended = true;
						extended = true;
					}
					if (mDDlg.docked == 2) { mDDlg.docked_last = mDDlg.docked; mDDlg.docked = 1; }
					SendMessage(hWnd, WM_SIZE, 0, -2);
					if (mDlg2.m_isCloned)
					{
						mDlg2.moving = false;
						mDlg2.SetTab(mDlg2.m_Tab);
						SetFocus(hWnd);
					}
					break;
				}
				else
				{
					if (extended)
					{
						lastextended = true;
						extended = false;
						if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
						{
							RECT rect;
							GetClientRect(hWnd, &rect);
							::SetWindowPos(hWnd, HWND_TOPMOST, win.left, win.top, rect.right, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
						}
						else
							::SetWindowPos(hWnd, HWND_TOPMOST, win.left, win.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
					}
					else
						lastextended = false;
					if (!tape.TopMost)
					{
						::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
						CheckDlgButton(hWnd, ID_TOPMOST, BST_UNCHECKED);
					}
					if (mDlg2.m_isCloned && TabCtrl_GetCurSel(hTab) == 2)
					{
						mDlg2.moving = false;
						mDlg2.SetTab(mDlg2.m_Tab);
						SetFocus(hWnd);
					}
					break;
				}
				PostMessage(hWnd, WM_SIZE, -1, -3);
			}
		}
		break;
	}
	case WM_MOVE:
	{
		if (!done_WM_CREATE)
			break;

		if (FirstMove)
		{
			RECT win;
			GetWindowRect(hWnd, &win);
			mDDlg.movable = false;
			if (TabCtrl_GetCurSel(hTab) != 2)
				mDlg2.Hide();
			if (mDlg2.m_isCloned && TabCtrl_GetCurSel(hTab) == 2)
			{
				mDlg2.moving = true;
				mDlg2.SetTab(mDlg2.m_Tab);
				SetFocus(hWnd);
			}
			SetFocus(hWnd);
			if (extended)
			{
				lastextended = true;
				extended = false;
				if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
				{
					RECT rect;
					GetClientRect(hWnd, &rect);
					::SetWindowPos(hWnd, HWND_TOPMOST, win.left, win.top, rect.right + 16, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
				}
			}
			else
			{
				lastextended = false;
				RECT win2;
				GetWindowRect(mDDlg.m_hDlg, &win2);
				mDDlg.m_y = win2.top - win.top;
			}
			mDDlg.docked = mDDlg.docked_last;
			PostMessage(hWnd, WM_SIZE, -1, -3);
			::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			if (TabCtrl_GetCurSel(hTab) != 7 || NotepadTab != 7)
				::SetWindowPos(hWnd, HWND_TOPMOST, win.left, win.top, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE);
			else
				::SetWindowPos(hWnd, HWND_TOPMOST, win.left, win.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
		}
		FirstMove = false;
		PostMessage(hWnd, WM_SIZE, -1, -3);
		break;
	}
	case WM_EXITSIZEMOVE:
	{
		PostMessage(hWnd, WM_SIZE, -1, -1);
		break;
	}
	case WM_SIZE:
	{
		RECT win;
		GetWindowRect(hWnd, &win);
		RECT desk;
		ClientArea(&desk);

		if (lParam < 0)
		{
			if (extended)
			{
				mDlg2.MoveWindow(win.right - 7, desk.top + 31, 474, desk.bottom - 39, TRUE);
				switch ((NotepadTab == 7) ? 7 : TabCtrl_GetCurSel(hTab))
				{
				case 0:
				case 2:
				case 3:
				case 4:
				case 9:
				{
					if (!IsWindowVisible(kDDlg.m_hDlg) && !IsWindowVisible(rDDlg.m_hDlg))
						::SetWindowPos(hWnd, HWND_TOPMOST, win.left, desk.top, 492, desk.bottom, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
					break;
				}
				case 7:
				{
					RECT rect;
					GetClientRect(hWnd, &rect);
					::SetWindowPos(hWnd, HWND_NOTOPMOST, win.left, desk.top, rect.right + 16, desk.bottom, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
					break;
				}
				case 1:
				case 5:
				case 6:
				case 8:
				{
					::SetWindowPos(hWnd, HWND_TOPMOST, win.left, desk.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
					break;
				}
				}
				if (lParam == -2)
				{
					GetWindowRect(hWnd, &win);
					switch (mDDlg.docked)
					{
					case 1:
					case 2: { mDDlg.MoveWindow(win.right - 6, win.top + 63, 474, 287, TRUE);	break; }		//docked center >, right
					case 3: { mDDlg.MoveWindow(win.left + 6 - 474, win.top + 63, 474, 287, TRUE); break; }		//docked left
					}
				}
			}
			else
			{
				mDlg2.MoveWindow(win.right - 7, win.top + 31, 474, 288, TRUE);
				if (wParam != -1)
				{
					if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
					{ ::SetWindowPos(hWnd, HWND_NOTOPMOST, win.left, win.top, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE); }
					else
					{ ::SetWindowPos(hWnd, HWND_NOTOPMOST, win.left, win.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); }
				}
				if (lParam < -1)
				{
					GetWindowRect(hWnd, &win);
					int heightmp = (lParam == -3) ? mDDlg.m_y : 31;
					switch (mDDlg.docked)
					{
					case 1: { mDDlg.MoveWindow(win.right - 7, win.top + heightmp, 474, 287, TRUE); break; }		//docked right
					case 2: { mDDlg.MoveWindow(win.left + 9, win.top + 31, 474, 287, TRUE); break; }			//docked center
					case 3: { mDDlg.MoveWindow(win.left + 6 - 474, win.top + heightmp, 474, 287, TRUE); break; }//docked left
					}
				}
			}
		}

		if (wParam == -1)
			break;

		RECT rect;
		GetClientRect(hWnd, &rect);

		MoveWindow(hTopMost, rect.right - 25, 3, 20, 15, FALSE);
		MoveWindow(hTab, 0, 0, rect.right, 21, FALSE);
		MoveWindow(hStatus, 0, rect.bottom -24, rect.right, 24, FALSE);
		MoveWindow(hTab_Explorer, 19, 0, rect.right - 41, (tape.DarkTheme) ? 17 : 19, FALSE);
		MoveWindow(hWebMenu, 0, 0, 22, 17, FALSE);
		MoveWindow(hWebClose, rect.right - 22, 0, 22, 17, FALSE);
		MoveWindow(hTab_DeleteDF, (rect.right / 2) - 50, (rect.bottom / 2) - 50, 100, 100, FALSE);

		if (tape.isExplorerLoaded)
			web_tabs[tape.web_actualtab]->ResizeEverything();

		nDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);

		rect.left += 3;
		rect.top += 21;
		rect.right -= 6;
		rect.bottom -= 45;

		_log.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		sDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		vDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		dDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		mDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		rDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		xDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		kDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		gDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		lDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		rDDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		kDDlg.MoveWindow(rect.left - kDDlg.dlgPage * 470, rect.top, rect.right + kDDlg.dlgPage * 470, rect.bottom, FALSE);

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_NCLBUTTONDBLCLK:
	{
		if (TabCtrl_GetCurSel(hTab) == 7)
		{
			GetCursorPos(&tape.mousepoint);
			RECT win;
			GetWindowRect(hWnd, &win);
			RECT rect;
			GetClientRect(hWnd, &rect);
			short t = (short)(tape.mousepoint.y - win.top);
			if (t >= 0 && t <= 30)
			{
				if (tape.mousepoint.x - win.left - rect.right < -131)
				{
					web_tabs[tape.web_actualtab]->ToggleFullScreen();
				}
			}
		}
		break;
	}
	case WM_ENTER_FULLSCREEN:
	{
		isFullScreen = true;
		ShowWindow(hTab_Explorer, SW_HIDE);
		ShowWindow(hWebMenu, SW_HIDE);
		ShowWindow(hWebClose, SW_HIDE);
		DWORD style = GetWindowLong(hWnd, GWL_STYLE);
		SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
		break;
	}
	case WM_EXIT_FULLSCREEN:
	{
		DWORD style = GetWindowLong(hWnd, GWL_STYLE);
		SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		ShowWindow(hTab_Explorer, SW_SHOW);
		ShowWindow(hWebMenu, SW_SHOW);
		ShowWindow(hWebClose, SW_SHOW);
		isFullScreen = false;
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case ID_TOPMOST:
		case ID_WEBMENU:
		case ID_WEBCLOSE:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case NM_CUSTOMDRAW:
			{
				if (!tape.DarkTheme)
					return CDRF_DODEFAULT;
				LPNMCUSTOMDRAW DrawListCustom = (LPNMCUSTOMDRAW)lParam;
				if (DrawListCustom->uItemState == CDIS_HOT || DrawListCustom->uItemState == CDIS_NEARHOT)
				{
					FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_BTN_DARK);
					SelectObject(DrawListCustom->hdc, GetStockObject(DC_PEN));
					SetDCPenColor(DrawListCustom->hdc, tape.ink_grey);
					RoundRect(DrawListCustom->hdc, DrawListCustom->rc.left + 1, DrawListCustom->rc.top + 1, DrawListCustom->rc.right - 1, DrawListCustom->rc.bottom - 1, 6, 6);
				}
				return CDRF_DODEFAULT;
			}
			case BCN_HOTITEMCHANGE:
			{
				switch (((NMBCHOTITEM*)lParam)->dwFlags)
				{
				case (HICF_ENTERING | HICF_MOUSE):
				{
					if (tape.DarkTheme)
						::SetWindowTheme(((LPNMHDR)lParam)->hwndFrom, L"", L"");
					if (((LPNMHDR)lParam)->idFrom == ID_WEBCLOSE)
					{
						::SetWindowTheme(((LPNMHDR)lParam)->hwndFrom, L"", L"");
						SetTimer(hWnd, 5, 70, NULL);
					}
					break;
				}
				case (HICF_LEAVING | HICF_MOUSE):
				{
					if (tape.DarkTheme)
						::SetWindowTheme(((LPNMHDR)lParam)->hwndFrom, L"Explorer", NULL);
					if (((LPNMHDR)lParam)->idFrom == ID_WEBCLOSE)
					{
						::SetWindowTheme(((LPNMHDR)lParam)->hwndFrom, L"Explorer", NULL);
						KillTimer(hWnd, 5);
					}
					break;
				}
				}
				break;
			}
			}
			break;
		}
		case ID_TABMENU:
		{
			if (!done_WM_CREATE || wm_pause)
				return FALSE;
			static bool NotFromWeb = true;
			NotFromWeb = true;
			switch (((NMHDR*)lParam)->code)
			{
			case NM_CLICK:
			{
				SetTimer(hWnd, 6, 20, NULL);
				break;
			}
			case TCN_SELCHANGING:
				mDDlg.m_mode = 0;
				rDDlg.m_mode = 0;
				kDDlg.m_mode = 0;
				vDlg.Hide();
				dDlg.Hide();
				mDDlg.Hide();
				rDDlg.Hide();
				kDDlg.Hide();
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0: { _log.Hide(); break; }
				case 1: { sDlg.Hide(); break; }
				case 2: { mDlg.Hide(); if (!extended) { mDlg2.Hide(); } break; }
				case 3: { rDlg.Hide(); break; }
				case 4: { kDlg.Hide(); break; }
				case 5: { xDlg.Hide(); break; }
				case 6: { gDlg.Hide(); break; }
				case 7:
				{
					NotFromWeb = false;
					ShowWindow(hTab_Explorer, SW_HIDE);
					ShowWindow(hWebMenu, SW_HIDE);
					ShowWindow(hWebClose, SW_HIDE);
					web_tabs[tape.web_actualtab]->Hide();
					ShowWindow(hTab, SW_SHOW);
					ShowWindow(hTopMost, SW_SHOW);
					ShowWindow(hStatus, SW_SHOW);
					break;
				}
				case 8: { lDlg.Hide(); break; }
				case 9:
				{
					if (NotepadTab == 7)
						NotFromWeb = false;
					notepad = false;
					TabCtrl_DeleteItem(hTab, 9);
					nDlg.Hide();
					ShowWindow(hTab, SW_SHOW);
					ShowWindow(hTopMost, SW_SHOW);
					ShowWindow(hStatus, SW_SHOW);
					break;
				}
				}
				break;
			case TCN_SELCHANGE:
				KillTimer(hWnd, 6);
				SendMessage(hWnd, WM_EXITSIZEMOVE, 0, 0);
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0: { _log.Show(); break; }
				case 1: { sDlg.Show(); break; }
				case 2: { mDlg.SetTab(mDlg.m_Tab, true); if (mDlg2.m_isCloned) { mDlg2.SetTab(mDlg2.m_Tab); } break; }
				case 3: { rDlg.Show(); break; }
				case 4: { kDlg.Show(); break; }
				case 5: { xDlg.Show(); break; }
				case 6: { gDlg.Show(); break; }
				case 7: 
				{
					if (!tape.isExplorerLoaded && !tape.isWebView2Installing)
					{
						RECT win;
						GetWindowRect(tape.Ds2hWnd, &win);
						if (initialUri == L"")
							initialUri = tape.WebURL[0];
						web_tabs.push_back(std::make_unique<ExplorerDlg>(initialUri, true, tape.DefaultZoomValue, win));
					}
					{
						MouseIsOverMain = true;
						RECT win;
						GetWindowRect(hWnd, &win);
							win.right -= win.left;
						win.bottom -= win.top;
						DWORD style = GetWindowLong(hWnd, GWL_STYLE);
						SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
						SetWindowPos(hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
					}
					ShowWindow(hTab, SW_HIDE);
					ShowWindow(hTopMost, SW_HIDE);
					ShowWindow(hStatus, SW_HIDE);
					ShowWindow(hTab_Explorer, SW_SHOW);
					ShowWindow(hWebMenu, SW_SHOW);
					ShowWindow(hWebClose, SW_SHOW);
					web_tabs[tape.web_actualtab]->OnMouseOver();
					web_tabs[tape.web_actualtab]->Show();
					break;
				}
				case 8: { lDlg.Show(); break; }
				case 9:
				{
					ShowWindow(hTopMost, SW_HIDE);
					ShowWindow(hTab, SW_HIDE);
					ShowWindow(hStatus, SW_HIDE);
					nDlg.Show();
					notepad = true;
					break;
				}
				}
				if (NotepadTab != 7)
					PostMessage(hWnd, WM_SIZE, 0, -1);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}
		case ID_TABEXPLORER:
		{
			switch (((NMHDR*)lParam)->code)
			{
			case NM_RCLICK:
			{
				TCHITTESTINFO tabinfo;
				GetCursorPos(&tape.mousepoint);
				POINT pt = tape.mousepoint;
				ScreenToClient(hTab_Explorer, &pt);
				tabinfo.pt = pt;
				int tab = TabCtrl_HitTest(hTab_Explorer, &tabinfo);
				if (tab > -1 && tab < web_tabs.size())
				{
					::SetFocus(NULL);

					if (tab == 0 && web_tabs.size() == 1)
						web_tabs[0]->CloseWebView();
					else
					{
						web_tabs.erase(web_tabs.begin() + tab);
						if (tape.web_actualtab >= max(tab, 1))
							tape.web_actualtab -= 1;

						TabCtrl_DeleteAllItems(hTab_Explorer);
						TCITEM tc_item;
						tc_item.mask = TCIF_TEXT;
						for (int i = 0; i < web_tabs.size(); i++)
						{
							WCHAR buff[MAX_PATH];
							_snwprintf_s(buff, sizeof(buff), L"%d", i + 1);
							tc_item.pszText = buff;
							TabCtrl_InsertItem(hTab_Explorer, i, &tc_item);
						}
						tc_item.pszText = WCHARI(L"+");
						TabCtrl_InsertItem(hTab_Explorer, web_tabs.size(), &tc_item);
						TabCtrl_SetCurSel(hTab_Explorer, tape.web_actualtab);
						web_tabs[tape.web_actualtab]->ResizeEverything();
						web_tabs[tape.web_actualtab]->Show();
					}
				}
				ShowWindow(hTab_Explorer, SW_HIDE);
				ShowWindow(hTab_Explorer, SW_SHOW);
				break;
			}
			case NM_CLICK:
			{
				SetTimer(hWnd, 7, 20, NULL);
				break;
			}
			case TCN_SELCHANGING:
			{
				int desttab = TabCtrl_GetCurSel(hTab_Explorer);
				if (desttab != web_tabs.size())
				{
					web_tabs[desttab]->Hide();
					web_tabs[desttab]->OnMouseOut();
				}
				break;
			}
			case TCN_SELCHANGE:
			{
				KillTimer(hWnd, 7);
				int desttab = TabCtrl_GetCurSel(hTab_Explorer);
				if (desttab == web_tabs.size())
					SendMessage(hWnd, WM_CREATE_NEW_TAB, (WPARAM)initialUri.c_str(), true);
				else
				{
					tape.web_actualtab = desttab;
					web_tabs[tape.web_actualtab]->ResizeEverything();
					web_tabs[tape.web_actualtab]->Show();
				}
				break;
			}
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}
		case ID_STATUS:
		{
			switch (((NMHDR*)lParam)->code)
			{
			case NM_CLICK:
			{
				if (TabCtrl_GetCurSel(hTab) == 0)
					_log.PageDown();
				else if (TabCtrl_GetCurSel(hTab) == 2)
					mDlg.PageDown();
				else if (TabCtrl_GetCurSel(hTab) == 3)
					rDlg.PageDown();
				else if (TabCtrl_GetCurSel(hTab) == 4)
					kDlg.PageDown();
				break;
			}
			case NM_RCLICK:
			{
				if (TabCtrl_GetCurSel(hTab) == 0)
					_log.PageUp();
				else if (TabCtrl_GetCurSel(hTab) == 2)
					mDlg.PageUp();
				else if (TabCtrl_GetCurSel(hTab) == 3)
					rDlg.PageUp();
				else if (TabCtrl_GetCurSel(hTab) == 4)
					kDlg.PageUp();
				break;
			}
			}
		}
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL: //Trap VK_ESCAPE
		{
			break;
		}
		case ID_TOPMOST:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); tape.TopMost = true;
				}
				else
				{
					::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); tape.TopMost = false;
				}
			}
			}
			break;
		}
		case IDM_MENU_EXIT:
		{
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		case IDM_MAPPING:
		{
			tape.MappingPaused = !tape.MappingPaused;
			tasktray.SwapMenuitem(Tasktray::TasktrayItem_MappingPaused);
			tape.Save(tape.Setting_MappingPaused);
			break;
		}
		case IDM_RAPIDFIRE:
		{
			tape.RapidFirePaused = !tape.RapidFirePaused;
			tasktray.SwapMenuitem(Tasktray::TasktrayItem_RapidFirePaused);
			tape.Save(tape.Setting_RapidFirePaused);
			break;
		}
		case IDM_VJOY:
		{
			tape.vJoyPaused = !tape.vJoyPaused;
			tasktray.SwapMenuitem(Tasktray::TasktrayItem_vJoyPaused);
			tape.Save(tape.Setting_vJoyPaused);
			break;
		}
		case IDM_XOUTPUT:
		{
			tape.XOutputPaused = !tape.XOutputPaused;
			tasktray.SwapMenuitem(Tasktray::TasktrayItem_XOutputPaused);
			tape.Save(tape.Setting_XOutputPaused);
			if (tape.XOutputPaused)
				xi.ClosePad();
			else
				xi.InitPad();
			break;
		}
		case IDM_KEYMAP:
		{
			tape.KeymapPaused = !tape.KeymapPaused;
			tasktray.SwapMenuitem(Tasktray::TasktrayItem_KeymapPaused);
			tape.Save(tape.Setting_KeymapPaused);
			break;
		}
		case IDM_GUARDIAN:
		{
			tape.GuardianPaused = !tape.GuardianPaused;
			tasktray.SwapMenuitem(Tasktray::TasktrayItem_GuardianPaused);
			tape.Save(tape.Setting_GuardianPaused);
			hid.WhitelistInit();
			hid.BlacklistInit(-1);
			break;
		}
		case ID_WEBMENU:
		{
			::SetFocus(NULL);
			web_tabs[tape.web_actualtab]->ShowMenu();
			break;
		}
		case ID_WEBCLOSE:
		{
			if (lParam == -1)
			{
				::SetFocus(NULL);
				if (web_tabs.size() > 1 && tape.web_actualtab != web_tabs.size())
				{
					web_tabs.erase(web_tabs.begin() + tape.web_actualtab);
					tape.web_actualtab = (tape.web_actualtab) ? tape.web_actualtab - 1 : 0;

					TabCtrl_DeleteAllItems(hTab_Explorer);
					TCITEM tc_item;
					tc_item.mask = TCIF_TEXT;
					for (int i = 0; i < web_tabs.size(); i++)
					{
						WCHAR buff[MAX_PATH];
						_snwprintf_s(buff, sizeof(buff), L"%d", i + 1);
						tc_item.pszText = buff;
						TabCtrl_InsertItem(hTab_Explorer, i, &tc_item);
					}
					tc_item.pszText = WCHARI(L"+");
					TabCtrl_InsertItem(hTab_Explorer, web_tabs.size(), &tc_item);
					TabCtrl_SetCurSel(hTab_Explorer, tape.web_actualtab);
					web_tabs[tape.web_actualtab]->ResizeEverything();
					web_tabs[tape.web_actualtab]->Show();
				}
				else if (web_tabs.size() == 1)
					web_tabs[tape.web_actualtab]->CloseWebView();
			}
			else
				TabCtrl_SetCurFocus(hTab, 0);
			break;
		}
		case IDM_PROFILE1: { SendMessage(hWnd, WM_RELOAD, 1, 0); break; }
		case IDM_PROFILE2: { SendMessage(hWnd, WM_RELOAD, 2, 0); break; }
		case IDM_PROFILE3: { SendMessage(hWnd, WM_RELOAD, 3, 0); break; }
		case IDM_APP0: { if (tape.App0Location) { if (!LaunchProcess(tape.App0Location)) { echo(I18N.TaskTray_AppNotFound, tape.App0Location); } } break; }
		case IDM_APP1: { if (tape.App1Location) { if (!LaunchProcess(tape.App1Location)) { echo(I18N.TaskTray_AppNotFound, tape.App1Location); } } break; }
		case IDM_APP2: { if (tape.App2Location) { if (!LaunchProcess(tape.App2Location)) { echo(I18N.TaskTray_AppNotFound, tape.App2Location); } } break; }
		case IDM_APP3: { if (tape.App3Location) { if (!LaunchProcess(tape.App3Location)) { echo(I18N.TaskTray_AppNotFound, tape.App3Location); } } break; }
		case IDM_APP4: { if (tape.App4Location) { if (!LaunchProcess(tape.App4Location)) { echo(I18N.TaskTray_AppNotFound, tape.App4Location); } } break; }
		case IDM_MENU_IMPORT: { if (tape.Import()) SendMessage(hWnd, WM_RELOAD, tape.Profile, 1); break; }
		case IDM_MENU_EXPORT: { tape.Export(); break; }
		case IDM_MENU_ABOUT: { DialogBox(tape.Ds2hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); break; }
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_TASKTRAY: { tasktray.Message(wParam, lParam); break; }
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_CLOSE: { PostMessage(hWnd, WM_DESTROY, 0, 0); break; }
		case SC_MINIMIZE:
		{
			if (done_WM_CREATE && !wm_pause)
			{
				::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				tape.TopMost = false;
				mDDlg.Hide();
				mDlg2.Hide();
				ShowWindow(hWnd, SW_HIDE);
			}
			return FALSE;
		}
		case SC_MAXIMIZE:
		{
			if (done_WM_CREATE && !wm_pause)
			{
				if (notepad)
				{
					TabCtrl_SetCurFocus(hTab, NotepadTab);
					NotepadTab = 0;
				}
				else
				{
					NotepadTab = TabCtrl_GetCurSel(hTab);
					TCITEM tc_item;
					tc_item.mask = TCIF_TEXT;
					tc_item.pszText = WCHARI(L"");
					TabCtrl_InsertItem(hTab, 9, &tc_item);
					TabCtrl_SetCurFocus(hTab, 9);
				}
			}
			break;
		}
		case SC_RESTORE:
		{
			PostMessage(hWnd, WM_COMMAND, WPARAM(ID_TOPMOST), LPARAM(GetDlgItem(hWnd, ID_TOPMOST)));
			if (mDDlg.m_mode > 0)
				mDDlg.Show();
			break;
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
	case WM_DESTROY:
	{
		static bool DestructionLaunched = false;
		if (done_WM_CREATE && !DestructionLaunched)
		{
			DestructionLaunched = true;
			wm_pause = true;
			log_closing = true;
			tape.CallbackPaused = true;
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 6);
			if (HDCForInfo != NULL)
				::ReleaseDC(hWnd, HDCForInfo);
			if (hDCStatus != NULL)
				::ReleaseDC(hWnd, hDCStatus);
			if (tape.MagInitialized)
				SetMagnifyZoom(MAG_METHOD_RESET, 0, 0, 0);
			if (tape.NotepadUnsaved)
				nDlg.Save();
			if (!tape.BreakAndExit)
				tape.Save(tape.Setting_All);
			srce.SetTriggers(0);
			if (tape.BlackLedOnExit)
				srce.SetLED(0, 0, 0);
			else
				srce.SetLED(GetRValue(tape.LED_Color), GetGValue(tape.LED_Color), GetBValue(tape.LED_Color));
			srce.SetOrangeLED(0xFF);
			srce.SetWhiteLED(0xFF);
			srce.Write();
			tasktray.Hide();
			if (tape.DisconnectBT)
				srce.DisconnectBT();
			xi.CloseClient();
			srce.Close(true);
			dest.Close();
			if (tape.vJoyShutDown)
				xi.vJoyDisable();
			FreeLanguage();
			DeleteObject((HBRUSH)GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND));
			PostQuitMessage(0);
			//{
			//	HMODULE hMod = ::GetModuleHandle(L"vJoyInstall.dll");
			//	if (hMod != nullptr)
			//		::FreeLibrary(hMod);
			//}
			//::DeleteFile(L"vJoyInstall.dll");
			//::DeleteFile(L"Devcon.exe");
		}
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void WM_CREATE_END(HWND hWnd)
{
	/*
	echo("char:        %d", sizeof(char));			//1		//integers
	echo("byte:        %d", sizeof(byte));			//1
	echo("short:       %d", sizeof(short));			//2
	echo("WCHAR:       %d", sizeof(WCHAR));			//2
	echo("int:         %d", sizeof(int));			//4
	echo("long:        %d", sizeof(long));			//4
	echo("long long:   %d", sizeof(long long));		//8
	echo("float:       %d", sizeof(float));			//4		//1+6 decimals
	echo("double:      %d", sizeof(double));		//8		//1+15 decimals
	echo("long double: %d", sizeof(long double));	//8
	*/
	{
		SendMessage(hWnd, WM_DEVICE_DEST_START, 0, 0);
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
		SendMessage(hWnd, WM_DEVICE_SRCE_START, 0, 0);
		SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
	}

	{
		SetTimer(hWnd, 1, 5000, NULL);	//Check for DS, DirectInput or vJoy interruptions, and Guardian Whitelist Check
		SetTimer(hWnd, 2, 100, NULL);	//Set Ondulating LED
		SetTimer(hWnd, 3, 100, NULL);	//Battery, Latency, tab infos, Mode-Profile-Stance & Invert if Dark theme
		SetTimer(hWnd, 4, 10, NULL);	//When moving windows & Zoom
										//Set and focus explorer tab under cursor & Change window form when mouseover
		//				5				//Webclose button right click
	}
	SendMessage(hProgressBar, PBM_STEPIT, 0, 0);
	PostMessage(hProgressBar, WM_CLOSE, 0, 0);
	done_WM_CREATE = true;
}

void GetPixelForInfo()
{
	static bool GetPixelForInfoOnAir = false;
	if (HDCForInfo != NULL && !GetPixelForInfoOnAir)
	{
		GetPixelForInfoOnAir = true;
		COLORREF COLORREFforInfotmp = GetPixel(HDCForInfo, tape.mousepoint.x * tape.Hscale, tape.mousepoint.y * tape.Vscale);
		if (COLORREFforInfotmp != CLR_INVALID)
			COLORREFforInfo = COLORREFforInfotmp;
		GetPixelForInfoOnAir = false;
	}
}

INT_PTR CALLBACK About(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_ABOUT);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_ABOUT);
		return (LRESULT)tape.hB_ABOUT;
	}
	case WM_INITDIALOG:
	{
		RECT desktop;
		ClientArea(&desktop);
		RECT dialog;
		GetClientRect(hWnd, &dialog);
		SetWindowPos(hWnd, HWND_TOP,
			desktop.left + ((desktop.right - desktop.left - dialog.right) / 2),
			desktop.top - 55 + ((desktop.bottom - desktop.top - dialog.bottom) / 2),
			0, 0, SWP_NOSIZE);
		SendDlgItemMessage(hWnd, IDC_ABOUT_1, WM_SETFONT, WPARAM(tape.hAbout), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hWnd, IDC_ABOUT_2, WM_SETFONT, WPARAM(tape.hAbout), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hWnd, IDC_ABOUT_3, WM_SETFONT, WPARAM(tape.hAbout), MAKELPARAM(TRUE, 0));
		SetWindowText(GetDlgItem(hWnd, IDC_ABOUT_1), I18N.ABOUT_1);
		SetWindowText(GetDlgItem(hWnd, IDC_ABOUT_2), I18N.ABOUT_2);
		SetWindowText(GetDlgItem(hWnd, IDC_ABOUT_3), I18N.ABOUT_3);
		return (INT_PTR)TRUE;
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_ABOUT);

			HWND about_ok = GetDlgItem(hWnd, IDC_ABOUT_OK);
			hDC = BeginPaint(about_ok, &ps);
			GetClientRect(about_ok, &rect);
			FillRect(hDC, &rect, tape.hB_ABOUT);

			rect.left += 3;
			rect.top += 1;
			SelectFont(hDC, tape.hAbout);
			SetTextColor(hDC, tape.ink_ABOUT);
			SetBkColor(hDC, tape.Bk_ABOUT);
			DrawText(hDC, I18N.ABOUT_OK, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_ABOUT_OK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}

/*
BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
{
	static int u = 0;
	u++;
	MessageBox(Ds2hWnd, std::to_wstring(u).c_str(), L"EnumChild", MB_OK);
	return TRUE;
}
*/

void OutRun()
{
	CPULimiter limiter = 1; //CPU percents
	while (true)
	{
		limiter.CalculateAndSleep();
		hid.HidStates();
		int HidCState = hid.GetHidCState();
		if (!isInList({ 2, 3, 5, 6 }, HidCState))
		{
			mDDlg.Hide();
			rDDlg.Hide();
			kDDlg.Hide();
			gDlg.Hide();
			gDlg.Show();
			break;
		}
	}
}

/*
std::function<void()> GetAcceleratorKeyFunction(UINT key)
{
	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			switch (key)
			{
			case 'S':
			{
				if (tape.isExplorerLoaded)
					return [] { web_tabs[tape.web_actualtab]->SaveScreenshot(true); };
				else
					return nullptr;
			}
			}
		}
		else
			switch (key)
			{
			case 'Q':
			{
				return [] { PostMessage(tape.Ds2hWnd, WM_DESTROY, 0, 0); };
			}
			case 'S':
			{
				PostMessage(tape.Ds2hWnd, WM_SCREENSHOT, MAKEWPARAM(0, 0), MAKELPARAM(0, 0));
			}
			}
	}
	return nullptr;
}
*/
