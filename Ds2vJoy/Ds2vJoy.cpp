#include "stdafx.h"
#include "Source.h"
#include "Ds2vJoy.h"
#include "vJoy.h"
#include "SettingDlg.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"
#include "RapidFireDlg.h"
#include "RapidFireDataDlg.h"
#include "ViGEm.h"
#include "ViGEmDlg.h"
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

Settings			tape;
Guardian			hid;
ViGEm				vg;

LogDlg				_log;
static SettingDlg	sDlg;
static MappingDlg	mDlg;
static MappingDlg	mDlg2;
static RapidFireDlg	rDlg;
static ViGEmDlg		vDlg;
static KeymapDlg	kDlg;
static GuardianDlg	gDlg;
static LinksDlg		iDlg;
static NotepadDlg	nDlg;
static Tasktray		tasktray;

MappingDataDlg		mDDlg;
KeymapDataDlg		kDDlg;
RapidFireDataDlg	rDDlg;

byte				battery;

unsigned char		mode = 1;
static double		r;
unsigned char		mousemode[3] = { 0 };
unsigned char		mouseabolute = 1;
unsigned short		grid[6] = { 0 };
bool				defaultmouse = false;
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
static WCHAR		ViGEmSatusString[80] = L"";
static WCHAR		KeymapSatusString[80] = L"";
static WCHAR		LinksSatusString[80] = L"";

bool isFullScreen = false;
bool MouseIsOverMain = true;
bool MouseIsOverTab = false;
bool WebMenuVisible = false;
static std::map<DWORD, HANDLE> s_threads;
std::wstring initialUri = L"";
std::vector<std::unique_ptr<ExplorerDlg>> web_tabs;

	   ATOM             RegisterWndClass(HINSTANCE hInstance);
	   BOOL             InitInstance(HINSTANCE, int);
static int              RunMessagePump();
static DWORD WINAPI     ThreadProc(void* pvParam);
static void             WaitForOtherThreads();
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	   INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
//	   BOOL CALLBACK    EnumChildProc(HWND hwndChild, LPARAM lParam);
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

	SetProcessDpiAwarenessContext(dpiAwarenessContext);

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

	int retVal = RunMessagePump();
	WaitForOtherThreads();
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DS2VJOY_ICON));
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
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX/* | WS_THICKFRAME*/;
	tape.Ds2hWnd = CreateWindowExW(WS_EX_CONTROLPARENT, tape.szWindowClass, tape.szTitle, dwStyle, CW_USEDEFAULT, 0, 492, 327, nullptr, nullptr, hInstance, nullptr);

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
*/
   RECT desk;
   ClientArea(&desk);
   SetWindowPos(tape.Ds2hWnd, HWND_TOPMOST, (desk.right - desk.left) / 2 - 246, desk.top + 200, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);

   ShowWindow(tape.Ds2hWnd, nCmdShow);
   if (nCmdShow== SW_SHOWMINNOACTIVE)
	   SendMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
   else if (nCmdShow == SW_RESTORE)
	   SendMessage(tape.Ds2hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
   UpdateWindow(tape.Ds2hWnd);

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
		GetWindowRect(dlg->m_hWnd, &win);
	new ExplorerDlg(L"", false, tape.DefaultZoomValue, win);
	return RunMessagePump();
}

// Called on the main thread.  Wait for all other threads to complete before exiting.
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

typedef struct _dsParams
{
	vJoyDevice* vj = { 0 };
	/////vJoyDevice* vjdi = { 0 };	//////////////////////////////////
	unsigned char vJoyID = 0;
	dsDevice* ds = { 0 };
	Mappings mappings;
	Keymaps keymaps;
	RapidFires rapidfires;
	bool NextStepFlag = false;
	dsButton *splittouch = { 0 };
	byte splitButton = 0;
	unsigned char splitCol = 0;
	unsigned char splitRow = 0;
} dsParams;

void dsInput(dsDevice* ds, bool updateflag, void* param)
{
	if (tape.CallbackPaused)
		return;

	static std::chrono::system_clock::time_point last = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point now;
	now = std::chrono::system_clock::now();
	average = double(std::chrono::duration_cast<std::chrono::nanoseconds>(now - last).count()) / double(1000000);
	last = now;

	dsParams *p = (dsParams*)param;

	if (updateflag == false && p->NextStepFlag == false)
		return;

	vJoyDevice* vjoy = p->vj;

	vjoy->ClearState();
	p->mappings[0].RunFirst(vjoy);

	size_t n = p->mappings.size();
	for (int i = 0; i < n; i++)
		if (p->mappings[i].Enable == 1)
			p->mappings[i].Run(average);

	p->mappings[0].RunLast(p->ds, vjoy);
	wcscpy_s(MappingSatusString, wcslen(p->mappings[0].MappingButtons()) + 1, p->mappings[0].MappingButtons());
	vjoy->UpdateState();

	if (tape.PreferredDS)
	{
		byte touchbox[7] = { 0, 0, 0, 0, 0, 0, 0 };
		int posymax = (tape.ActualDS == 1) ? 350 : 400;
		bool TouchActive[2];
		int touchx[2];
		int touchy[2];
		TouchActive[0] = ds->TouchActive(0);
		TouchActive[1] = ds->TouchActive(1);
		touchx[0] = ds->TouchX(0);
		touchx[1] = ds->TouchX(1);
		touchy[0] = ds->TouchY(0);
		touchy[1] = ds->TouchY(1);

		if (TouchActive[0])
		{
			if (touchy[0] > 20)
			{
				if (touchy[0] < posymax)
				{
					if (touchx[0] < 960)
						touchbox[1] = 1;
					else
						touchbox[2] = 1;
				}
				else
				{
					if (touchx[0] < 960)
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
			p->splittouch->SetTouch(i, touchbox[i]);

		//	p->ds->String();
		if (p->splittouch != 0 && p->splittouch->isPushed())
		{
			for (int idx = 0; idx < 2; idx++)
			{
				if (TouchActive[idx])
				{
					int pos = 0;
					if (p->splitRow > 0)
					{
						switch (tape.ActualDS)
						{
						case 1: { pos = touchy[idx] / (943 / p->splitRow) * p->splitCol; break; }
						case 2: { pos = touchy[idx] / (1080 / p->splitRow) * p->splitCol; break; }
						}
					}
					if (p->splitCol > 0)
						pos += touchx[idx] / (1920 / p->splitCol);
					if (p->splitButton - 1 + pos < 128)
						vjoy->GetButton((vJoyButtonID)(vJoyButton::Button1 + p->splitButton - 1 + pos))->SetValByte(1);
				}
			}
		}

		{
			POINT CursorPos;
			double x = ds->GetButton(dsButton::LX)->GetVal();
			double y = ds->GetButton(dsButton::LY)->GetVal();
			double z = ds->GetButton(dsButton::RX)->GetVal();
			double t = ds->GetButton(dsButton::RY)->GetVal();
			static bool lastTouchActive;
			static int lasttouchx = 1;
			static int lasttouchy = 1;
			static bool lastmouseactivated2 = false;
			static bool lastmouseactivated34 = false;
			static bool mouseactivated2 = mousemode[0] == 2 || mousemode[1] == 2 || mousemode[2] == 2;
			static bool mouseactivated34 = mousemode[0] == 3 || mousemode[1] == 3 || mousemode[2] == 3 ||
				mousemode[0] == 4 || mousemode[1] == 4 || mousemode[2] == 4;

			if (lastmouseactivated2 && !mouseactivated2)
			{
				GetCursorPos(&tape.mousepoint);
				if (!mouseactivated34 && defaultmouse)
					SetCursorPos(gridpoint.x, gridpoint.y);
			}
			if (lastmouseactivated34 && !mouseactivated34)
			{
				GetCursorPos(&gridpoint);
				if (!mouseactivated2 && !defaultmouse)
					SetCursorPos(tape.mousepoint.x, tape.mousepoint.y);
			}
			if (!lastmouseactivated2 && mouseactivated2)
				SetCursorPos(tape.mousepoint.x, tape.mousepoint.y);
			if (!lastmouseactivated34 && mouseactivated34)
				SetCursorPos(gridpoint.x, gridpoint.y);

			lastmouseactivated2 = mouseactivated2;
			lastmouseactivated34 = mouseactivated34;

			if (mousemode[1])
			{
				static double restx;
				static double resty;
				GetCursorPos(&CursorPos);
				switch (mousemode[1])
				{
				case 1: //absolute
				{
					if (TouchActive[0] && mouseabolute == 1)
					{
						int destx = touchx[0];
						int desty = 0;
						if (tape.ActualDS)
							desty = touchy[0] * 1080 / 943;
						else
							desty = touchy[0];
						if (!tape.MouseCanBypass)
						{
							restx = max(0, min(tape.W, destx));
							resty = max(0, min(tape.H, desty));
						}
						SetCursorPos(destx, desty);
						lasttouchx = touchx[0];
						lasttouchy = touchy[0];
						lastTouchActive = TouchActive[0];
					}
					break;
				}
				case 2: //mouse
				{
					if (TouchActive[0] && lastTouchActive)
					{
						restx = restx + ((double)touchx[0] - lasttouchx) * touchfactor;
						if (tape.ActualDS == 1)
							resty = resty + ((double)touchy[0] * 1080 / 943 - lasttouchy) * touchfactor;
						else
							resty = resty + ((double)touchy[0] - lasttouchy) * touchfactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
						lasttouchx = touchx[0];
						lasttouchy = touchy[0];
						lastTouchActive = TouchActive[0];
					}
					break;
				}
				case 3: //slow
				{
					if (TouchActive[0] && lastTouchActive)
					{
						restx = restx + ((double)touchx[0] - lasttouchx) * slowfactor;
						if (tape.ActualDS == 1)
							resty = resty + ((double)touchy[0] * 1080 / 943 - lasttouchy) * slowfactor;
						else
							resty = resty + ((double)touchy[0] - lasttouchy) * slowfactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
						lasttouchx = touchx[0];
						lasttouchy = touchy[0];
						lastTouchActive = TouchActive[0];
					}
					break;
				}
				case 4: //accuracy
				{
					if (TouchActive[0] && lastTouchActive)
					{
						restx = restx + ((double)touchx[0] - lasttouchx) * accuracyfactor;
						if (tape.ActualDS == 1)
							resty = resty + ((double)touchy[0] * 1080 / 943 - lasttouchy) * accuracyfactor;
						else
							resty = resty + ((double)touchy[0] - lasttouchy) * accuracyfactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
						lasttouchx = touchx[0];
						lasttouchy = touchy[0];
						lastTouchActive = TouchActive[0];
					}
					break;
				}
				case 5: //grid
				{
					if ((TouchActive[0] && touchx[0] && touchy[0]) || gridmove.size())
					{
						double ldesty = (tape.ActualDS == 1) ? 943 : 1080;
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
							lasttouchx = max(((grid[4]) ? 1 : 0), touchx[0]);
							lasttouchy = max(((grid[5]) ? 1 : 0), touchy[0]);
							lastTouchActive = TouchActive[0];
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
						if (!tape.MouseCanBypass)
						{
							destx = max(0, min(tape.W, destx));
							desty = max(0, min(tape.H, desty));
						}
						SetCursorPos((int)destx, (int)desty);
					}
					break;
				}
				}
			}
			if (mousemode[0])
			{
				static double restx;
				static double resty;
				double xtmp = x - 127.5;
				double ytmp = y - 127.5;
				GetCursorPos(&CursorPos);
				switch (mousemode[0])
				{
				case 1: //absolute
				{
					if ((ds->GetButton(dsButton::LX)->isPushed() || ds->GetButton(dsButton::LY)->isPushed()) && mouseabolute == 0)
					{
						double restx = min((double)2 * tape.w, max(0, r * ((double)2 * x / 255 - 1) + tape.w));
						double resty = min((double)2 * tape.h, max(0, r * ((double)2 * y / 255 - 1) + tape.h));
						if (!tape.MouseCanBypass)
						{
							restx = max(0, min(tape.W, restx));
							resty = max(0, min(tape.H, resty));
						}
						SetCursorPos((int)restx, (int)resty);
					}
					break;
				}
				case 2: //mouse
				{
					if (ds->GetButton(dsButton::LX)->isPushed() || ds->GetButton(dsButton::LY)->isPushed())
					{
						restx = restx + xtmp * xtmp * xtmp * mousefactor;
						resty = resty + ytmp * ytmp * ytmp * mousefactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 3: //move
				{
					if (ds->GetButton(dsButton::LX)->isPushed() || ds->GetButton(dsButton::LY)->isPushed())
					{
						restx = restx + xtmp * xtmp * xtmp * movefactor;
						resty = resty + ytmp * ytmp * ytmp * movefactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 4: //sniper
				{
					if (ds->GetButton(dsButton::SNIPER_LX)->isPushed() || ds->GetButton(dsButton::SNIPER_LY)->isPushed())
					{
						restx = restx + xtmp * sniperfactor;
						resty = resty + ytmp * sniperfactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 5: //raid
				{
					if ((ds->GetButton(dsButton::LX)->isPushed() || ds->GetButton(dsButton::LY)->isPushed()) || gridmove.size())
					{
						double destw = (grid[2]) ? grid[2] : tape.W - grid[0];
						double desth = (grid[3]) ? grid[3] : tape.H - grid[1];
						double restxtmp = restx + abs(xtmp) * xtmp * raidfactor;
						double restytmp = resty + abs(ytmp) * ytmp * raidfactor;
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
						if (!tape.MouseCanBypass)
						{
							destx = max(0, min(tape.W, destx));
							desty = max(0, min(tape.H, desty));
						}
						SetCursorPos((int)destx, (int)desty);
					}
					break;
				}
				}
			}
			if (mousemode[2])
			{
				static double restx;
				static double resty;
				double ztmp = z - 127.5;
				double ttmp = t - 127.5;
				GetCursorPos(&CursorPos);
				switch (mousemode[2])
				{
				case 1: //absolute
				{
					if ((ds->GetButton(dsButton::RX)->isPushed() || ds->GetButton(dsButton::RY)->isPushed()) && mouseabolute == 2)
					{
						double restx = min((double)2 * tape.w, max(0, r * ((double)2 * z / 255 - 1) + tape.w));
						double resty = min((double)2 * tape.h, max(0, r * ((double)2 * t / 255 - 1) + tape.h));
						if (!tape.MouseCanBypass)
						{
							restx = max(0, min(tape.W, restx));
							resty = max(0, min(tape.H, resty));
						}
						SetCursorPos((int)restx, (int)resty);
					}
					break;
				}
				case 2: //mouse
				{
					if (ds->GetButton(dsButton::RX)->isPushed() || ds->GetButton(dsButton::RY)->isPushed())
					{
						restx = restx + ztmp * ztmp * ztmp * mousefactor;
						resty = resty + ttmp * ttmp * ttmp * mousefactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 3: //move
				{
					if (ds->GetButton(dsButton::RX)->isPushed() || ds->GetButton(dsButton::RY)->isPushed())
					{
						restx = restx + ztmp * ztmp * ztmp * movefactor;
						resty = resty + ttmp * ttmp * ttmp * movefactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 4: //sniper
				{
					if (ds->GetButton(dsButton::SNIPER_RX)->isPushed() || ds->GetButton(dsButton::SNIPER_RY)->isPushed())
					{
						restx = restx + ztmp * sniperfactor;
						resty = resty + ttmp * sniperfactor;
						double movex = (restx > 0) ? floor(restx) : ceil(restx);
						double movey = (resty > 0) ? floor(resty) : ceil(resty);
						restx -= movex;
						resty -= movey;
						if (tape.MouseCanBypass)
						{
							movex = CursorPos.x + movex;
							movey = CursorPos.y + movey;
						}
						else
						{
							movex = max(0, min(tape.W, CursorPos.x + movex));
							movey = max(0, min(tape.H, CursorPos.y + movey));
						}
						SetCursorPos((int)movex, (int)movey);
					}
					break;
				}
				case 5: //raid
				{
					if ((ds->GetButton(dsButton::RX)->isPushed() || ds->GetButton(dsButton::RY)->isPushed()) || gridmove.size())
					{
						double destw = (grid[2]) ? grid[2] : tape.W - grid[0];
						double desth = (grid[3]) ? grid[3] : tape.H - grid[1];
						double restxtmp = restx + abs(ztmp) * ztmp * raidfactor;
						double restytmp = resty + abs(ttmp) * ttmp * raidfactor;
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
						if (!tape.MouseCanBypass)
						{
							destx = max(0, min(tape.W, destx));
							desty = max(0, min(tape.H, desty));
						}
						SetCursorPos((int)destx, (int)desty);
					}
					break;
				}
				}
			}
			if (gridmove.size())
				gridmove.erase(gridmove.begin());
		}
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

	if (vjoy->Active() && tape.vJoyActive && !tape.vJoyPaused)
		vjoy->Update();

	if (tape.ViGEmActive)
	{
		vg.Run();
		wcscpy_s(ViGEmSatusString, wcslen(vg.ViGEmButtons()) + 1, vg.ViGEmButtons());
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
	static dsDevice ds;
	static vJoyDevice vjoy;
	//////static vJoyDevice vjoydi;	//////////////////////////////////////
	static dsParams cbParams;
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
	static unsigned long m_flag_drag = 0;
	static unsigned long m_flag_size = 0;
	static RECT FirstMoveRect = { (0, 0, 0, 0) };
	static RECT WebRect = { (0, 0, 0, 0) };
	static bool FirstMove = false;
	static short x = 0;
	static short y = 0;
	static bool first_WM_CREATE = false;
	static bool load_dll = false;
	static bool done_WM_CREATE = false;

	switch (message)
	{
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
	case WM_SHOWWINDOW:
	{
		switch (TabCtrl_GetCurSel(hTab))
		{
		case 4: { vg.ViGEmStates(); vg.vJoyStates(); break; }
		case 6: { hid.HidStates(); break; }
		}
		break;
	}
	case WM_CREATE:
	{
		if (first_WM_CREATE)
			break;

		first_WM_CREATE = true;
		std::vector<char> data;
		DWORD resourceSize;
		if (LoadEmbeddedResource(IDR_VIGEMCLIENT_DLL, &data, &resourceSize))
			WriteToFile(L"ViGEmClient.dll", data, resourceSize, true, true);
		if (LoadEmbeddedResource(IDR_VJOYINTERFACE_DLL, &data, &resourceSize))
			WriteToFile(L"vJoyInterface.dll", data, resourceSize, true, true);
		if (LoadEmbeddedResource(IDR_VJOYINSTALL_DLL, &data, &resourceSize))
			WriteToFile(L"vJoyInstall.dll", data, resourceSize, true, true);
		if (LoadEmbeddedResource(IDR_WEBVIEW2LOADER_DLL, &data, &resourceSize))
			WriteToFile(L"WebView2Loader.dll", data, resourceSize, true, true);
		if (LoadEmbeddedResource(IDR_DEVCON_EXE, &data, &resourceSize))
			WriteToFile(L"Devcon.exe", data, resourceSize, true, true);
		if (isFileExists("vJoyInterface.dll") && isFileExists("ViGEmClient.dll") && isFileExists("vJoyInstall.dll") && isFileExists("WebView2Loader.dll"))
			load_dll = true;

		_log.Init(tape.Ds2hInst, hWnd, load_dll);

		LoadLanguage();
		InitCommonControls();
		tape.Init(tape.Ds2hInst, hWnd);
		tape.OpenIni(WCHARI(L"Ds2vJoy.ini"));
		tape.Load(Settings::Setting_Category_All);
		if (tape.BreakAndExit)
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		GetCursorPos(&tape.mousepoint);
		GetCursorPos(&gridpoint);

		if (load_dll)
		{
			tasktray.Init(tape.Ds2hInst, hWnd);
			sDlg.Init(tape.Ds2hInst, hWnd);
			mDlg.Init(tape.Ds2hInst, hWnd);
			rDlg.Init(tape.Ds2hInst, hWnd);
			vDlg.Init(tape.Ds2hInst, hWnd);
			kDlg.Init(tape.Ds2hInst, hWnd);
			gDlg.Init(tape.Ds2hInst, hWnd);
			iDlg.Init(tape.Ds2hInst, hWnd);
			nDlg.Init(tape.Ds2hInst, hWnd);
			mDlg2.Init(tape.Ds2hInst, hWnd, true);	//Clone
			mDDlg.Init(tape.Ds2hInst, hWnd);
			rDDlg.Init(tape.Ds2hInst, hWnd);
			kDDlg.Init(tape.Ds2hInst, hWnd);
			cbParams.vj = &vjoy;
			/////cbParams.vjdi = &vjoydi;	///////////////////////////////////////////////
			cbParams.ds = &ds;
			PostMessage(hWnd, WM_TRANSPARENCY, 0, 0);
		}
		else
		{
			DWORD style = GetWindowLong(hWnd, GWL_STYLE);
			SetWindowLong(hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU);
			SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);

			echo(I18N.Fatal_Error1);
			echo();
			echo(I18N.Fatal_Error2);
			return FALSE;
		}

		if (tape.Tasktray)
			PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		{
			hTab = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_FIXEDWIDTH, 0, 0, 0, 0, hWnd, (HMENU)ID_TABMENU, tape.Ds2hInst, NULL);

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
			tc_item.pszText = I18N.TabViGEm;
			TabCtrl_InsertItem(hTab, 4, &tc_item);
			tc_item.pszText = I18N.TabKeymap;
			TabCtrl_InsertItem(hTab, 5, &tc_item);
			tc_item.pszText = I18N.TabGuardian;
			TabCtrl_InsertItem(hTab, 6, &tc_item);
			tc_item.pszText = I18N.TabExplorer;
			TabCtrl_InsertItem(hTab, 7, &tc_item);
			tc_item.pszText = I18N.TabLinks;
			TabCtrl_InsertItem(hTab, 8, &tc_item);

			SendMessage(hTab, WM_SETFONT, WPARAM(tape.hTab1), TRUE);
			TabCtrl_SetItemSize(hTab, 48, 17);
			TabCtrl_SetPadding(hTab, 0, 2);

			TabCtrl_SetCurSel(hTab, 0);
		}

		{
			hTopMost = CreateWindowEx(0, L"button", L"↕", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_CENTER, 451, 3, 20, 15, hWnd, (HMENU)ID_TOPMOST, tape.Ds2hInst, NULL);
			SendMessage(hTopMost, WM_SETFONT, WPARAM(tape.hTopMost), TRUE);
			if (tape.TopMost)
			{
				CheckDlgButton(hWnd, ID_TOPMOST, BST_CHECKED);
				::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			}
			else
				CheckDlgButton(hWnd, ID_TOPMOST, BST_UNCHECKED);
		}

		{
			hStatus = CreateWindowEx( 0, STATUSCLASSNAME, (PCTSTR)NULL, WS_CHILD | WS_VISIBLE | CCS_BOTTOM /*| SBARS_SIZEGRIP*/, 0, 0, 0, 0, hWnd, (HMENU)ID_STATUS, tape.Ds2hInst, NULL);
			int width[4] = { 70,140,415,-1 };
			SendMessage(hStatus, SB_SETPARTS, 4, LPARAM(width));
			SendMessage(hStatus, SB_SETTEXT, 0, WPARAM(I18N.Status_Wait));
			SendMessage(hStatus, WM_SETFONT, WPARAM(tape.hStatus), TRUE);
		}

		{
			hWebMenu = CreateWindowEx(0, L"button", L"≡", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_CENTER, 0, 0, 22, 17, hWnd, (HMENU)ID_WEBMENU, tape.Ds2hInst, NULL);
			SendMessage(hWebMenu, WM_SETFONT, WPARAM(tape.hWeb), TRUE);
			ShowWindow(hWebMenu, SW_HIDE);
			CreateToolTip(hWnd, hWebMenu, I18N.HELP_WEB_MENU);
		}

		{
			hWebClose = CreateWindowEx(0, L"button", L"✕", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 454, 0, 22, 17, hWnd, (HMENU)ID_WEBCLOSE, tape.Ds2hInst, NULL);
			SendMessage(hWebClose, WM_SETFONT, WPARAM(tape.hWebX), TRUE);
			ShowWindow(hWebClose, SW_HIDE);
			CreateToolTip(hWnd, hWebClose, I18N.HELP_WEB_CLOSE);
		}

		{
			hTab_Explorer = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_FIXEDWIDTH | TCS_TOOLTIPS, 0, 0, 0, 0, hWnd, (HMENU)ID_TABEXPLORER, tape.Ds2hInst, NULL);
			TCITEM tc_item;
			tc_item.mask = TCIF_TEXT;
			wchar_t tabtxt[256];
			tc_item.pszText = WCHARI(L"1");
			TabCtrl_InsertItem(hTab_Explorer, 0, &tc_item);
			tc_item.pszText = WCHARI(L"+");
			TabCtrl_InsertItem(hTab_Explorer, 1, &tc_item);

			SendMessage(hTab_Explorer, WM_SETFONT, WPARAM(tape.hExplorer), TRUE);
			TabCtrl_SetItemSize(hTab_Explorer, 18, 17);
			TabCtrl_SetPadding(hTab_Explorer, 0, 1);

			TabCtrl_SetCurSel(hTab_Explorer, 0);
			ShowWindow(hTab_Explorer, SW_HIDE);
		}

		{
			hTab_DeleteDF = CreateWindowEx(0, L"Static", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, 0, 0, 100, 100, hWnd, nullptr, tape.Ds2hInst, nullptr);
			ShowWindow(hTab_DeleteDF, SW_HIDE);

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

		//echo(L"https://github.com/ytyra/Ds2vJoy 31/07/2021");
		std::wstring datestring = std::to_wstring(tape.VersionDate);
		datestring = L"Version: "
			+ datestring.std::wstring::substr(0, 4) + L" "
			+ datestring.std::wstring::substr(4, 2) + L" "
			+ datestring.std::wstring::substr(6, 2) + L" - "
			+ datestring.std::wstring::substr(8, (datestring.length() - 8));
		wcscpy_s(LinksSatusString, wcslen(datestring.c_str()) + 1, datestring.c_str());
		tasktray.Show();

		vjoy.Init(hWnd, true);
		vg.Init(hWnd);
		if (tape.DsvJoyAddedToGuardian)
			echo(I18N.Guardian_Added_to_Guardian, I18N.APP_TITLE, tape.Ds2vJoyPID);
		hid.Init(hWnd);

		SendMessage(hWnd, WM_DISPLAYCHANGE, 0, 0);

		if (!SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 0))
			echo(I18N.Log_Wait_vJoy);
		if (!SendMessage(hWnd, WM_DEVICE_DS_START, 0, 0))
			echo(I18N.Log_Wait_ds);

		SetTimer(hWnd, 1, 10000, NULL);	//Check for vJoy or DS interruptions
		SetTimer(hWnd, 2, 100, NULL);	//Set Ondulating LED
		SetTimer(hWnd, 3, 1000, NULL);	//Battery & Latency
		SetTimer(hWnd, 4, 5000, NULL);	//Guardian Whitelist Check
		SetTimer(hWnd, 5, 10, NULL);	//When moving windows & Zoom
		SetTimer(hWnd, 6, 100, NULL);	//Print Profile, mode, mouse and vJoy Buttons when editing
		SetTimer(hWnd, 7, 65, NULL);	//Set and focus explorer tab under cursor & Change window form when mouseover
										//8 Webclose button right click

		done_WM_CREATE = true;
		break;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			if (!vjoy.Active())
				SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 1);
			if (!ds.Active() && tape.PreferredDS)
				SendMessage(hWnd, WM_DEVICE_DS_START, 0, 1);
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

			const double π = 3.141592653589793238462643;
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
			if (ds.Active())
			{
				ds.SetLED(Rval, Gval, Bval);
				ds.Write();
			}
			phase--;

			limiter.CalculateAndSleep();
		}
		else if (wParam == 3)
		{
			if (ds.Active())
			{
				static bool LowBatt = false;
				battery = ds.Battery();
				if (battery < 5)
				{
					if (!LowBatt)
					{
						LowBatt = true;
						ds.SetOrangeLED(2);
					}
				}
				else if (LowBatt)
				{
					LowBatt = false;
					ds.SetOrangeLED(0);
				}
				bool charge = ds.BatteryCharge();
				bool full = ds.BatteryFull();
				if (charge)battery -= 5;
				if (full) battery = 100;
				WCHAR buf[20];
				if (ds.isBT())
				{
					swprintf_s(buf, sizeof(buf), L"BT (%s%d%%)", charge ? L"+" : L"", battery);
					battery += 1;
				}
				else
				{
					swprintf_s(buf, sizeof(buf), L"USB (%s%d%%)", charge ? L"+" : L"", battery);
					battery += 2;
				}
				tasktray.Tip(buf);
				if (!IsIconic(hWnd))
				{
					SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(buf), SMTO_BLOCK, 1000, NULL);
					if (tape.MagInitialized)
						swprintf_s(buf, TEXT("%0.5f ms*"), average);
					else
						swprintf_s(buf, TEXT("%0.5f ms"), average);
					SendMessageTimeout(hStatus, SB_SETTEXT, 1, LPARAM(buf), SMTO_BLOCK, 1000, NULL);
				}
			}
			else
			{
				if (!IsIconic(hWnd))
				{
					SendMessageTimeout(hStatus, SB_SETTEXT, 0, LPARAM(I18N.Status_Wait), SMTO_BLOCK, 1000, NULL);
					SendMessageTimeout(hStatus, SB_SETTEXT, 1, LPARAM(L""), SMTO_BLOCK, 1000, NULL);
				}
			}
		}
		else if (wParam == 4)
		{
			hid.WhitelistCheck();
		}
		else if (wParam == 5)
		{
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
						GetCursorPos(&tape.mousepoint);
						if (TabCtrl_GetCurSel(hTab) == 7 || NotepadTab == 7)
						{
							::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x - x, tape.mousepoint.y - y, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER | SWP_DEFERERASE);
						}
						else
						{
							::SetWindowPos(hWnd, HWND_NOTOPMOST, tape.mousepoint.x - x, tape.mousepoint.y - y, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
						}
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
					GetCursorPos(&tape.mousepoint);
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
		}
		else if (wParam == 6)
		{
			if (!IsIconic(hWnd) && !isFullScreen)
			{
				SendMessageTimeout(hStatus, SB_SETTEXT, 3, LPARAM((L"M:" + std::to_wstring(mode) + L" Pr:" + std::to_wstring(tape.Profile)).c_str()), SMTO_BLOCK, 1000, NULL);
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0:
				{
					time_t rawtime;
					struct tm timeinfo;
					time(&rawtime);
					localtime_s(&timeinfo, &rawtime);

					//https://www.cplusplus.com/reference/ctime/strftime/
					if (wcsftime(LogSatusString, 100, L"%a  %d /%m /%y     %T     UTC %z     %u …%W", &timeinfo))
						SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(LogSatusString), SMTO_BLOCK, 1000, NULL);
					break;
				}
				case 1:
				{
					COLORREF color;
					HDC hdcScreen;

					hdcScreen = GetDC(NULL);
					if (hdcScreen != NULL)
					{
						if (GetCursorPos(&tape.mousepoint))
						{
							color = GetPixel(hdcScreen, tape.mousepoint.x * tape.Hscale, tape.mousepoint.y * tape.Vscale);
							if (color != CLR_INVALID)
							{
								swprintf_s(SettingsSatusString, sizeof(SettingsSatusString), L"Color: # %02X  %02X  %02X    R %03i  G %03i  B %03i", GetRValue(color), GetGValue(color), GetBValue(color), GetRValue(color), GetGValue(color), GetBValue(color));
								SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(SettingsSatusString), SMTO_BLOCK, 1000, NULL);
							}
						}
						ReleaseDC(GetDesktopWindow(), hdcScreen);
					}
					break;
				}
				case 2: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(MappingSatusString), SMTO_BLOCK, 1000, NULL); break; }
				case 3: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(RapidFireSatusString), SMTO_BLOCK, 1000, NULL); break; }
				case 4: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(ViGEmSatusString), SMTO_BLOCK, 1000, NULL); break; }
				case 5: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(KeymapSatusString), SMTO_BLOCK, 1000, NULL); break; }
				case 6: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(hid.GuardianButtons()), SMTO_BLOCK, 1000, NULL); break; }
				case 8: { SendMessageTimeout(hStatus, SB_SETTEXT, 2, LPARAM(LinksSatusString), SMTO_BLOCK, 1000, NULL); break; }
				}
			}
		}
		else if (wParam == 7)
		{
			if (!IsIconic(hWnd) && IsWindowVisible(hWnd) && !isFullScreen)
			{
				if (!WebMenuVisible && tape.isExplorerLoaded && TabCtrl_GetCurSel(hTab) == 7)
				{
					static size_t tab = -1;
					static bool entered_hTab_Explorer = false;
					static size_t lastview_hTab_Explorer = -1;
					if (!IsIconic(hWnd) && IsWindowVisible(hTab_Explorer) && !isFullScreen)
					{
						TCHITTESTINFO tabinfo;
						GetCursorPos(&tape.mousepoint);
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
					if (GetCursorPos(&tape.mousepoint) && tab == -1)
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
				else if (TabCtrl_GetCurSel(hTab) == 9)
				{
					if (GetCursorPos(&tape.mousepoint))
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
		}
		else if (wParam == 8)
		{
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
				PostMessage(hWnd, WM_COMMAND, ID_WEBCLOSE, -1);
			break;
		}
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
		tape.CallbackPaused = true;
		ds.GetButton(dsButtonID::LX)->SetThreshold();
		ds.GetButton(dsButtonID::LY)->SetThreshold();
		ds.GetButton(dsButtonID::RX)->SetThreshold();
		ds.GetButton(dsButtonID::RY)->SetThreshold();
		vjoy.Close();
		ds.Close();
		break;
	}
	case WM_RESTART:
	{
		ds.SetCallback(dsInput, &cbParams);
		ds.PreOpen();
		if (vjoy.Open(tape.vJoyDeviceID, !lParam))
			cbParams.vJoyID = tape.vJoyDeviceID;
		if (ds.Active())
		{
			vDlg.Init2();
			ds.SetOrangeLED(0x00);
			ds.SetWhiteLED(0x00);
			ds.AssignOffsets();
			ds.Open(hWnd, !lParam);
			tape.CallbackPaused = false;
			return TRUE;
		}
		else if (!tape.PreferredDS)
		{
			vDlg.Init2();
			ds.Open(hWnd, !lParam);
			tape.CallbackPaused = false;
			return TRUE;
		}
		break;
	}
	case WM_RELOAD:
	{
		// lParam == 0 verbose
		// lParam == 1 silent
		LogSatusString[0] = '\0';
		SettingsSatusString[0] = '\0';
		MappingSatusString[0] = '\0';
		RapidFireSatusString[0] = '\0';
		KeymapSatusString[0] = '\0';
		ViGEmSatusString[0] = '\0';
		SendMessage(hWnd, WM_TIMER, 6, 0);

		tape.CallbackPaused = true;

		PreviousTab = TabCtrl_GetCurSel(hTab);
		PreviousNotepadTab = NotepadTab;
		TabCtrl_SetCurFocus(hTab, 0);

		if (!lParam)
			echo(I18N.Change_Settings);

		{
			if ((wParam == 1) || (wParam == 2) || (wParam == 3))
			{
				tape.Save(tape.Setting_All);
				tape.Profile = (unsigned char)wParam;
				tape.Save(tape.Setting_Profile);
				echo(I18N.TT_ProfileChanged, tape.Profile);
			}
			else
				hid.RestartDevices(true);
		}

		vg.CloseClient();
		vjoy.Close();
		ds.Close();
		SendMessage(hWnd, WM_RESET, 0, 0);

		tape.Load(Settings::Setting_Category_All);
		mDlg.Hide();
		mDDlg.m_mode = 0;

		vjoy.Init(hWnd);
		vg.Init(hWnd);
		hid.Init(hWnd);

		SendMessage(hWnd, WM_DISPLAYCHANGE, 0, 0);
		SendMessage(hWnd, WM_CREATE_MENU, 0, 0);
		SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, lParam);
		SendMessage(hWnd, WM_DEVICE_DS_START, 0, lParam);
		break;
	}
	case WM_DEVICE_DS_START:
	{
		// lParam == 0 verbose
		// lParam == 1 silent
		static bool dsstartrunning = false;

		if (dsstartrunning)
			return FALSE;
		dsstartrunning = true;

		tape.CallbackPaused = true;
		ds.GetButton(dsButtonID::LX)->SetThreshold();
		ds.GetButton(dsButtonID::LY)->SetThreshold();
		ds.GetButton(dsButtonID::RX)->SetThreshold();
		ds.GetButton(dsButtonID::RY)->SetThreshold();
		ds.Close();

		ds.SetCallback(dsInput, &cbParams);

		ds.SetTriggers(tape.TriggersMode);

		{
			cbParams.mappings.clear();
			cbParams.mappings[0].PreLoad();
			size_t max = tape.Mappingdata.size();
			for (int i = 0; i < 32; i++)
				tape.vJoyUsed[i] = false;
			for (int i = 0; i < max; i++)
			{
				Mapping *data = &tape.Mappingdata[i];
				if (data->LoadDevice(hWnd, &ds, &vjoy))
					cbParams.mappings.push_back(*data);
			}
		}

		if (tape.SplitTouch)
		{
			cbParams.splittouch = ds.GetButton(dsButton::TOUCH);
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
				if (tape.RapidFiredata[i].LoadDevice(&vjoy))
					cbParams.rapidfires.push_back(tape.RapidFiredata[i]);
			}
		}

		{
			cbParams.keymaps.clear();
			size_t max = tape.Keymapdata.size();
			for (int i = 0; i < max; i++)
			{
				Keymap *data = &tape.Keymapdata[i];
				if (data->LoadDevice(&vjoy))
					cbParams.keymaps.push_back(*data);
			}
		}

		if (tape.ViGEmActive && !vg.vigem_connected)
		{
			vg.CloseClient();
			vg.LoadDevice(&ds, &vjoy);
			vg.InitClient(true);
			tape.ViGEmActive = true;
		}

		cbParams.NextStepFlag = false;

		ds.SetTargetSerial(tape.getSerial());

		{
			mDlg.redrawTabs(mDlg.m_Tab);
			mDlg.SetTab(mDlg.m_Tab, PreviousTab == 2);
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

		ds.PreOpen();
		if (ds.Active())
		{
			vDlg.Init2();
			ds.SetOrangeLED(0x00);
			ds.SetWhiteLED(0x00);
			ds.AssignOffsets();
			ds.Open(hWnd, !lParam);
			tape.CallbackPaused = false;
			dsstartrunning = false;
			return TRUE;
		}
		else if (!tape.PreferredDS)
		{
			vDlg.Init2();
			ds.Open(hWnd, !lParam);
			tape.CallbackPaused = false;
			dsstartrunning = false;
			return TRUE;
		}
		dsstartrunning = false;

		return FALSE;
	}
	case WM_DEVICE_VJOY_START:
	{
		// lParam == 0 verbose
		// lParam == 1 silent
		vjoy.Close();

		if (vjoy.Open(tape.vJoyDeviceID, !lParam))
			cbParams.vJoyID = tape.vJoyDeviceID;

		return FALSE;
	}
	case WM_SETORANGELED:
	{
		if (ds.Active() && tape.ActualDS == 2)
			ds.SetOrangeLED((byte)wParam);
		break;
	}
	case WM_SETWHITELED:
	{
		if (ds.Active() && tape.ActualDS == 2)
			ds.SetWhiteLED((byte)wParam);
		break;
	}
	case WM_SETTRIGGERS:
	{
		if (ds.Active() && tape.ActualDS == 2)
		{
			ds.SetTriggers((int)wParam);
			ds.Write();
		}
		break;
	}
	case WM_ADDMAPPING:
	{
		switch (LOWORD(lParam))
		{
		case 0:
		{
			ds.GetButton(dsButtonID::LX)->SetThreshold();
			ds.GetButton(dsButtonID::LY)->SetThreshold();
			ds.GetButton(dsButtonID::RX)->SetThreshold();
			ds.GetButton(dsButtonID::RY)->SetThreshold();
			cbParams.mappings.clear();
			cbParams.mappings[0].PreLoad();
			size_t max = tape.Mappingdata.size();
			for (int i = 0; i < 32; i++)
				tape.vJoyUsed[i] = false;
			for (int i = 0; i < max; i++)
			{
				Mapping* data = &tape.Mappingdata[i];
				if (data->LoadDevice(hWnd, &ds, &vjoy))
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
					if (tape.RapidFiredata[i].LoadDevice(&vjoy))
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
			vg.CloseClient();
		else if (wParam == 1)
		{
			vg.LoadDevice(&ds, &vjoy);
			vg.InitClient();
		}
		else if (wParam == 2)
			if (tape.ViGEmActive)
			{
				vg.CloseClient();
				vg.LoadDevice(&ds, &vjoy);
				vg.InitClient();
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
					if (data->LoadDevice(&vjoy))
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

		tape.proportianality = (long(tape.W) > long(tape.H)) ? (long(tape.W) / long(tape.H)) : (long(tape.H) / long(tape.W));
		r = sqrt(tape.w * tape.w + tape.h * tape.h);
		double standard_r = sqrt(960 * 960 + 540 * 540);
		mousefactor = 0.0000089 * (r / standard_r);
		movefactor = 0.0000071;
		sniperfactor = 0.0097;
		raidfactor = 0.00022 * (r / standard_r);
		touchfactor = 0.6666667 * (r / standard_r);
		slowfactor = 0.3333333 * (r / standard_r);
		accuracyfactor = 0.2 * (r / standard_r);
		SendMessage(hWnd, WM_SIZE, 0, 0);
		break;
	}
	case WM_CHAR:
	case WM_SYSKEYDOWN:
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
		{
			GetCursorPos(&tape.mousepoint);
			RECT win;
			GetWindowRect(hWnd, &win);
			x = (short)(tape.mousepoint.x - win.left);
			y = (short)(tape.mousepoint.y - win.top);
			if (y >= 0 && y <= 30)
			{
				if (x > 438 && x < 485)
					PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0); break;
			}
			break;
		}

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
						::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
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
						::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
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
			::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
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
				case 5:
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
				case 4:
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
		MoveWindow(hTab, 0, 0, rect.right, rect.bottom, FALSE);
		MoveWindow(hStatus, 0, rect.bottom -24, rect.right, rect.bottom, FALSE);
		MoveWindow(hTab_Explorer, 19, 0, rect.right - 41, 17, FALSE);
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
		mDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		rDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		vDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		kDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		gDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		iDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		rDDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		kDDlg.MoveWindow(rect.left - kDDlg.dlgPage * 470, rect.top, rect.right + kDDlg.dlgPage * 470, rect.bottom, FALSE);

		InvalidateRect(hWnd, NULL, FALSE);
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
		switch (((LPNMLISTVIEW)lParam)->hdr.code)
		{
		case BCN_HOTITEMCHANGE:
		{
			switch (((NMBCHOTITEM*)lParam)->dwFlags)
			{
			case (HICF_ENTERING | HICF_MOUSE):
				switch (((LPNMHDR)lParam)->idFrom)
				{
				case ID_WEBCLOSE:SetTimer(hWnd, 8, 70, NULL); break;
				default:
					return FALSE;
				}
				break;
			case (HICF_LEAVING | HICF_MOUSE):
				switch (((LPNMHDR)lParam)->idFrom)
				{
				case ID_WEBCLOSE:KillTimer(hWnd, 8); break;
				default:
					return FALSE;
				}
				break;
			default:
				return FALSE;
			}
			break;
		}
		}
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case ID_TABMENU:
		{
			static bool NotFromWeb = true;
			NotFromWeb = true;
			switch (((NMHDR*)lParam)->code)
			{
			case TCN_SELCHANGING:
				SendMessage(hStatus, SB_SETTEXT, 2, WPARAM(L""));
				mDDlg.m_mode = 0;
				rDDlg.m_mode = 0;
				kDDlg.m_mode = 0;
				mDDlg.Hide();
				rDDlg.Hide();
				kDDlg.Hide();
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0: { _log.Hide(); break; }
				case 1: { sDlg.Hide(); break; }
				case 2: { mDlg.Hide(); if (!extended) { mDlg2.Hide(); } break; }
				case 3: { rDlg.Hide(); break; }
				case 4: { vDlg.Hide(); break; }
				case 5: { kDlg.Hide(); break; }
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
				case 8: { iDlg.Hide(); break; }
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
				SendMessage(hWnd, WM_EXITSIZEMOVE, 0, 0);
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0: { _log.Show(); break; }
				case 1: { sDlg.Show(); break; }
				case 2: { mDlg.Show(); if (mDlg2.m_isCloned) { mDlg2.SetTab(mDlg2.m_Tab); } break; }
				case 3: { rDlg.Show(); break; }
				case 4: { vDlg.Show(); break; }
				case 5: { kDlg.Show(); break; }
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
				case 8: { iDlg.Show(); break; }
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
			if (SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{ ::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); tape.TopMost = true; }
			else
				{ ::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); tape.TopMost = false; }
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
			tasktray.SwapMenuitem(Tasktray::Tasktray_Item_MappingPaused);
			tape.Save(tape.Setting_MappingPaused);
			break;
		}
		case IDM_RAPIDFIRE:
		{
			tape.RapidFirePaused = !tape.RapidFirePaused;
			tasktray.SwapMenuitem(Tasktray::Tasktray_Item_RapidFirePaused);
			tape.Save(tape.Setting_RapidFirePaused);
			break;
		}
		case IDM_VJOY:
		{
			tape.vJoyPaused = !tape.vJoyPaused;
			tasktray.SwapMenuitem(Tasktray::Tasktray_Item_vJoyPaused);
			tape.Save(tape.Setting_vJoyPaused);
			break;
		}
		case IDM_VIGEM:
		{
			tape.ViGEmPaused = !tape.ViGEmPaused;
			tasktray.SwapMenuitem(Tasktray::Tasktray_Item_ViGEmPaused);
			tape.Save(tape.Setting_ViGEmPaused);
			if (tape.ViGEmPaused)
				vg.ClosePad();
			else
				vg.InitPad();
			break;
		}
		case IDM_KEYMAP:
		{
			tape.KeymapPaused = !tape.KeymapPaused;
			tasktray.SwapMenuitem(Tasktray::Tasktray_Item_KeymapPaused);
			tape.Save(tape.Setting_KeymapPaused);
			break;
		}
		case IDM_GUARDIAN:
		{
			tape.GuardianPaused = !tape.GuardianPaused;
			tasktray.SwapMenuitem(Tasktray::Tasktray_Item_GuardianPaused);
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
		case IDM_APP1: { if (!LaunchProcess(tape.App1Location)) { echo(I18N.TT_AppNotFound, tape.App1Location); } break; }
		case IDM_APP2: { if (tape.App2Location) { if (!LaunchProcess(tape.App2Location)) { echo(I18N.TT_AppNotFound, tape.App2Location); } } break; }
		case IDM_APP3: { if (tape.App3Location) { if (!LaunchProcess(tape.App3Location)) { echo(I18N.TT_AppNotFound, tape.App3Location); } } break; }
		case IDM_APP4: { if (tape.App4Location) { if (!LaunchProcess(tape.App4Location)) { echo(I18N.TT_AppNotFound, tape.App4Location); } } break; }
		case IDM_APP5: { if (tape.App5Location) { if (!LaunchProcess(tape.App5Location)) { echo(I18N.TT_AppNotFound, tape.App5Location); } } break; }
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
			if (done_WM_CREATE)
			{
				::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				tape.TopMost = false;
				mDDlg.Hide();
				mDlg2.Hide();
				ShowWindow(hWnd, SW_HIDE);
			}
			return FALSE;
		}
		case SC_MAXIMIZE:
		{
			if (done_WM_CREATE)
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
		if (tape.MagInitialized)
		{
			SetMagnifyZoom(1, 0);
			MagUninitialize();
		}
		if (tape.NotepadUnsaved)
			nDlg.Save();
		if (!tape.BreakAndExit)
			tape.Save(tape.Setting_All);
		DeleteObject((HBRUSH)GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND));
		ds.SetTriggers(0);
		if (tape.BlackLedOnExit)
			ds.SetLED(0, 0, 0);
		else
			ds.SetLED(GetRValue(tape.LED_Color), GetGValue(tape.LED_Color), GetBValue(tape.LED_Color));
		ds.SetOrangeLED(0xFF);
		ds.SetWhiteLED(0xFF);
		ds.Write();
		tasktray.Hide();
		if (tape.DisconnectBT)
			ds.DisconnectBT();
		vg.CloseClient();
		vjoy.Close();
		ds.Close();
		FreeLanguage();
		if (tape.vJoyShutDown)
			disable(GetvJoyVersion());
		PostQuitMessage(0);
		{
			HMODULE hMod = ::GetModuleHandle(L"ViGEmClient.dll");
			if (hMod != nullptr)
				::FreeLibrary(hMod);
		}
		{
			HMODULE hMod = ::GetModuleHandle(L"vJoyInterface.dll");
			if (hMod != nullptr)
				::FreeLibrary(hMod);
		}
		{
			HMODULE hMod = ::GetModuleHandle(L"vJoyInstall.dll");
			if (hMod != nullptr)
				::FreeLibrary(hMod);
		}
		{
			HMODULE hMod = ::GetModuleHandle(L"WebView2Loader.dll");
			if (hMod != nullptr)
				::FreeLibrary(hMod);
		}
		::DeleteFile(L"ViGEmClient.dll");
		::DeleteFile(L"vJoyInterface.dll");
		::DeleteFile(L"vJoyInstall.dll");
		::DeleteFile(L"WebView2Loader.dll");
		::DeleteFile(L"Devcon.exe");
		::DeleteFile(L"ViGEmClient.dmp");
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_black);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.ink_bright_yellow);
		return (LRESULT)tape.hB_bright_yellow;
	}
	case WM_INITDIALOG:
	{
		RECT desk;
		ClientArea(&desk);
		RECT rect;
		GetClientRect(hWnd, &rect);
		SetWindowPos(hWnd, HWND_TOP, desk.left + ((desk.right - desk.left - rect.right) / 2), desk.top + ((desk.bottom - desk.top - rect.bottom) / 2), 0, 0, SWP_NOSIZE);
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
			FillRect(hDC, &rect, tape.hB_bright_yellow);

			HWND about_ok = GetDlgItem(hWnd, IDC_ABOUT_OK);
			hDC = BeginPaint(about_ok, &ps);
			GetClientRect(about_ok, &rect);
			FillRect(hDC, &rect, tape.hB_bright_yellow);

			rect.left += 3;
			rect.top += 1;
			SelectFont(hDC, tape.hAbout);
			SetTextColor(hDC, tape.ink_black);
			SetBkColor(hDC, tape.ink_bright_yellow);
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
