#include "stdafx.h"
#include "Ds2vJoy.h"
#include "Source.h"
#include "vJoy.h"
#include "FFB.h"
#include "Stopwatch.h"
#include "SettingDlg.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"
#include "RapidFireDlg.h"
#include "RapidFireDataDlg.h"
#include "KeymapDlg.h"
#include "KeymapDataDlg.h"
#include "ViGEm.h"
#include "ViGEmDlg.h"
#include "Guardian.h"
#include "GuardianDlg.h"
#include "LinksDlg.h"
#include "Tasktray.h"
#include "CPULimiter.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

bool callbackpause;
static const std::wstring ProgramFilesDirName = L"Ds2vJoy";

Settings tape;
Guardian hid;
ViGEm vg;

LogDlg _log;
static SettingDlg sDlg;
static MappingDlg mDlg;
static MappingDlg mDlg2;
static RapidFireDlg rDlg;
static KeymapDlg kDlg;
static ViGEmDlg vDlg;
static GuardianDlg gDlg;
static LinksDlg iDlg;
static Tasktray tasktray;

MappingDataDlg mDDlg;
KeymapDataDlg kDDlg;
RapidFireDataDlg rDDlg;

byte battery;

unsigned char mode = 1;
static double r;
unsigned char mousemode[3];
unsigned char mouseabolute;
short grid[6];
bool defaultmouse;
std::vector<char> gridmove;
static double mousefactor;
static double movefactor;
static double sniperfactor;
static double raidfactor;
static double touchfactor;
static double slowfactor;
static double accuracyfactor;
static POINT gridpoint;

static WCHAR vJoySatusString[80] = L"";
static WCHAR KeymapSatusString[80] = L"";
static WCHAR ViGEmSatusString[80] = L"";

ATOM                RegisterWndClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_DS2VJOY, szWindowClass, MAX_LOADSTRING);
	RegisterWndClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDS_DS2VJOY));

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
}

ATOM RegisterWndClass(HINSTANCE hInstance)
{
	{
		Guardian hid;
		hid.WhitelistDs2vJoy();
		memset(&hid, 0, sizeof(hid));
	}

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

//	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.style          = 0;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DS2VJOY_ICON));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//	wcex.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wcex.hbrBackground	= CreateSolidBrush(RGB(0, 0, 0));
//	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDS_DS2VJOY);
	wcex.lpszMenuName   = 0;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_DS2VJOY_ICON32));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	DWORD dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX); //| WS_MAXIMIZEBOX
//	DWORD dwStyle = WS_OVERLAPPEDWINDOW;		// id + WS_THICKFRAME

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle, CW_USEDEFAULT, 0, 492, 327, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
	  return FALSE;
   }

   RECT rect;
   ClientArea(&rect);
   SetWindowPos(hWnd, HWND_TOPMOST, (rect.right - rect.left) / 2 - 246, rect.top + 200, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
   tape.ActualhWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   if (nCmdShow== SW_SHOWMINNOACTIVE)
	   SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
   else if (nCmdShow == SW_RESTORE)
	   SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
   UpdateWindow(hWnd);

   return TRUE;
}

typedef struct _dsParams
{
	FFB ffb;
	double ffbTime = 0;
	Stopwatch sw;
	vJoyDevice* vj = { 0 };
	unsigned char vJoyID = 0;
	dsDevice* ds = { 0 };
	Mappings mappings;
	Keymaps keymaps;
//	std::vector<RapidFire> rapidfires;
	RapidFires rapidfires;
	bool NextStepFlag = false;
	dsButton *splittouch = { 0 };
	byte splitButton = 0;
	unsigned char splitCol = 0;
	unsigned char splitRow = 0;
} dsParams;

void dsInput(dsDevice* ds, bool updateflag, void* param)
{
	if (callbackpause)
		return;

	double now;
	dsParams *p = (dsParams*)param;
	p->sw.Lap(&now);

	if (tape.PreferredDS)
	{
		if (p->ffbTime + 3 < now)		//4ms
		{
			byte left, right;
			if (p->ffb.Calc(&left, &right))
			{
				ds->SetMoter(left, right);
				ds->Write();
			}
			p->ffbTime = now;
		}
	}

	if (updateflag == false && p->NextStepFlag == false)
		return;

	vJoyDevice* vjoy = p->vj;

	if (vjoy->Active())
		vjoy->ClearState();

	p->mappings[0].RunFirst(vjoy);

	size_t n = p->mappings.size();
	for (int i = 0; i < n; i++)
		if (p->mappings[i].Enable == 1)
			p->mappings[i].Run(p->sw.GetAvg());

	p->mappings[0].RunLast(p->ds, vjoy);
	WCHAR* ret = lstrcpynW(vJoySatusString, p->mappings[0].vJoyButtons(), sizeof(vJoySatusString) / sizeof(vJoySatusString[0]));

	if (vjoy->Active())
		vjoy->UpdateState();
	else
		WCHAR* ret = lstrcpynW(vJoySatusString, L"", sizeof(vJoySatusString) / sizeof(vJoySatusString[0]));

	byte touchbox[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int posymax = 350;

	if (tape.PreferredDS)
	{
		switch (tape.ActualDS)
		{
			/*	case 1:
						int posymax = 350;
						break;*/
		case 2:
			int posymax = 400;
			break;
		}

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
						case 1:
							pos = touchy[idx] / (943 / p->splitRow) * p->splitCol;
							break;
						case 2:
							pos = touchy[idx] / (1080 / p->splitRow) * p->splitCol;
							break;
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
				case 2: //mouse
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
				case 3: //slow
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
				case 4: //accuracy
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
				case 5: //grid
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
				case 2: //mouse
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
				case 3: //move
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
				case 4: //sniper
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
				case 5: //raid
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
				case 2: //mouse
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
				case 3: //move
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
				case 4: //sniper
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
				case 5: //raid
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
			if (gridmove.size())
				gridmove.erase(gridmove.begin());
		}
	}

	{
		bool flag=false;
		size_t max = p->rapidfires.size();
		for (int i = 0; i < max; i++)
		{
			if (p->rapidfires[i].Enable == 1)
				if (p->rapidfires[i].Run(now))
					flag = true;
		}
		p->NextStepFlag = flag;
	}

	if (vjoy->Active())
		vjoy->Update();

	if (tape.ViGEmActive)
	{
		vg.Run();
		WCHAR* ret = lstrcpynW(ViGEmSatusString, vg.ViGEmButtons(), sizeof(ViGEmSatusString) / sizeof(ViGEmSatusString[0]));
	}

	{
		size_t max = p->keymaps.size();
		for (int i = 0; i < max; i++)
			if (p->keymaps[i].Enable == 1)
				p->keymaps[i].Run();
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static dsDevice ds;
	static vJoyDevice vjoy;
	static dsParams cbParams;
	static short iBattery=-1;
	static HWND hTab;
	static HWND hChk;
	static HWND hStatus;
	static HWND hTab2;
	static HMENU hMenu_Tabs;
	static HMENU hMenu_Tabs_2;
	static unsigned char tabrightclick;
	static bool load_dll;
	static bool topmost;
	static bool extended;
	static bool cloned;
	static unsigned long m_flag_drag;
	static short x;
	static short y;

	switch (message)
	{
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor((HDC)wParam, tape.Tx_EDIT_TERMINAL);
		SetBkMode((HDC)wParam, OPAQUE);
		SetBkColor(hdcStatic, tape.Bk_EDIT);
		return (LRESULT)tape.hB_EDIT_TERMINAL;
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_EDIT_TERMINAL);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;
		if (DrawMenuSize->CtlType == ODT_MENU)
		{
			int nEdgeWidth = ::GetSystemMetrics(SM_CYEDGE);
			DrawMenuSize->itemWidth = ::GetSystemMetrics(SM_CXMENUCHECK) + nEdgeWidth + nEdgeWidth;
			DrawMenuSize->itemHeight = 12 + nEdgeWidth + nEdgeWidth;

			WCHAR wszBuffer[MAX_PATH];
			int nCharCount = ::GetMenuString(hMenu_Tabs_2, DrawMenuSize->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				int nAcceleratorDelimiter;
				for (nAcceleratorDelimiter = 0;
					nAcceleratorDelimiter < nCharCount; nAcceleratorDelimiter++)
					if (wszBuffer[nAcceleratorDelimiter] == L'\t' || wszBuffer[nAcceleratorDelimiter] == L'\b')
						break;

				RECT rTextMetric = { 0, 0, 0, 0 };
				HDC hDC = ::GetDC(hWnd);

				if (hDC != NULL)
				{
					NONCLIENTMETRICSW nm;
					nm.cbSize = sizeof(NONCLIENTMETRICS);
					::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0);
					HFONT font = ::CreateFontIndirect(&(nm.lfMenuFont));

					HFONT hOldFont = NULL;
					if (font != NULL)
						hOldFont = (HFONT)::SelectObject(hDC, font);

					::DrawTextW(hDC, wszBuffer, nAcceleratorDelimiter, &rTextMetric, DT_CALCRECT);
					long _CaptionWidth = rTextMetric.right - rTextMetric.left;

					long _AcceleratorWidth = 0;
					if (nAcceleratorDelimiter < nCharCount - 1)
					{
						::DrawTextW(hDC, &(wszBuffer[nAcceleratorDelimiter + 1]), nCharCount - nAcceleratorDelimiter - 1, &rTextMetric, DT_CALCRECT);
						_AcceleratorWidth = rTextMetric.right - rTextMetric.left;
					}
					if (hOldFont == NULL && hOldFont != 0)
						::SelectObject(hDC, hOldFont);

					::ReleaseDC(hWnd, hDC);

					DrawMenuSize->itemWidth = _CaptionWidth + _AcceleratorWidth + (_AcceleratorWidth > 0 ? 1 : 0) + 12;
				}
			}
		}
		break;
	}
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* DrawMenuStructure = (DRAWITEMSTRUCT*)lParam;
		if (DrawMenuStructure->CtlType == ODT_MENU)
		{
			BOOL bSelected = DrawMenuStructure->itemState & ODS_SELECTED;

			// Highlight
			if (DrawMenuStructure->itemState & ODS_SELECTED)
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_HIGHLIGHT);
			// Background
			else
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_CLONE);

			// Caption
			WCHAR wszBuffer[MAX_PATH];
			int   nCharCount = ::GetMenuString((HMENU)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				COLORREF crPrevText = 0;
				COLORREF crCurrText = 0;
				crCurrText = ::GetSysColor((bSelected) ? tape.Tx_MENU_HIGHLIGHT : tape.Tx_MENU_CLONE);
				crPrevText = ::SetTextColor(DrawMenuStructure->hDC, crCurrText);

				int nAcceleratorDelimiter;
				for (nAcceleratorDelimiter = 0;
					nAcceleratorDelimiter < nCharCount; nAcceleratorDelimiter++)
					if (wszBuffer[nAcceleratorDelimiter] == L'\t' ||
						wszBuffer[nAcceleratorDelimiter] == L'\b')
						break;

				NONCLIENTMETRICSW nm;
				nm.cbSize = sizeof(NONCLIENTMETRICS);
				::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0);
				HFONT _hMenuFontNormal = ::CreateFontIndirect(&(nm.lfMenuFont));
				HFONT hOldFont = (HFONT)::SelectObject(DrawMenuStructure->hDC, _hMenuFontNormal);

				int nOldBkMode = ::SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				int nEdgeWidth = ::GetSystemMetrics(SM_CYEDGE);
				int nImageOffsetX = nEdgeWidth + nEdgeWidth + 12;
				DrawMenuStructure->rcItem.left += nImageOffsetX;
				DrawMenuStructure->rcItem.top += 0;
				::DrawTextW(DrawMenuStructure->hDC, wszBuffer, nAcceleratorDelimiter, &(DrawMenuStructure->rcItem), 0);

				if (nAcceleratorDelimiter < nCharCount - 1)
				{
					DrawMenuStructure->rcItem.left += 21;
					if (wszBuffer[nAcceleratorDelimiter] == L'\t')
						::DrawTextW(DrawMenuStructure->hDC, &(wszBuffer[nAcceleratorDelimiter + 1]),
							nCharCount - nAcceleratorDelimiter - 1, &(DrawMenuStructure->rcItem),
							DT_LEFT | DT_SINGLELINE);
					else
						::DrawTextW(DrawMenuStructure->hDC, &(wszBuffer[nAcceleratorDelimiter + 1]),
							nCharCount - nAcceleratorDelimiter - 1, &(DrawMenuStructure->rcItem),
							DT_RIGHT | DT_SINGLELINE);
					DrawMenuStructure->rcItem.left -= +21;
				}
				DrawMenuStructure->rcItem.left -= nImageOffsetX;
				DrawMenuStructure->rcItem.top -= 0;

				::SetBkMode(DrawMenuStructure->hDC, nOldBkMode);
				::SetTextColor(DrawMenuStructure->hDC, crPrevText);

				if (hOldFont == NULL && hOldFont != 0)
					::SelectObject(DrawMenuStructure->hDC, hOldFont);
			}
		}
		break;
	}
	case WM_SHOWWINDOW:
		switch (TabCtrl_GetCurSel(hTab))
		{
		case 5:
			vg.ViGEmStates();
			break;
		case 6:
			hid.HidStates();
			break;
		}
		break;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_CHKBOXW:
				if (SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED)
					{ ::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); topmost = true; }
				else
					{ ::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); topmost = false; }
				break;
			case IDM_EXIT:
				tape.Save(tape.Setting_All);
				PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			case IDM_VJOY:
				tape.vJoyPaused = !tape.vJoyPaused;
				tasktray.SwapMenuitem(0);
				tape.Save(tape.Setting_vJoyPaused);
				break;
			case IDM_RAPIDFIRE:
				tape.RapidFirePaused = !tape.RapidFirePaused;
				tasktray.SwapMenuitem(3);
				tape.Save(tape.Setting_RapidFirePaused);
				break;
			case IDM_KEYMAP:
				tape.KeymapPaused = !tape.KeymapPaused;
				tasktray.SwapMenuitem(2);
				tape.Save(tape.Setting_KeymapPaused);
				break;
			case IDM_VIGEM:
				tape.ViGEmPaused = !tape.ViGEmPaused;
				tasktray.SwapMenuitem(1);
				tape.Save(tape.Setting_ViGEmPaused);
				if (tape.ViGEmPaused)
					vg.ClosePad();
				else
					vg.InitPad();
				break;
			case IDM_GUARDIAN:
				tape.GuardianPaused = !tape.GuardianPaused;
				tasktray.SwapMenuitem(4);
				tape.Save(tape.Setting_GuardianPaused);
				hid.WhitelistInit();
				hid.BlacklistInit(-1);
				break;
			case IDM_PROFILE1:
				SendMessage(hWnd, WM_RELOAD, 1, 0);
				break;
			case IDM_PROFILE2:
				SendMessage(hWnd, WM_RELOAD, 2, 0);
				break;
			case IDM_PROFILE3:
				SendMessage(hWnd, WM_RELOAD, 3, 0);
				break;
			case IDM_APP1:
				if (!LaunchProcess(tape.App1Location))
					echo(I18N.TT_AppNotFound, tape.App1Location);
				break;
			case IDM_APP2:
				if (tape.App2Location)
				{
					if (!LaunchProcess(tape.App2Location))
						echo(I18N.TT_AppNotFound, tape.App2Location);
				}
				break;
			case IDM_APP3:
				if (tape.App3Location)
				{
					if (!LaunchProcess(tape.App3Location))
						echo(I18N.TT_AppNotFound, tape.App3Location);
				}
				break;
			case IDM_APP4:
				if (tape.App4Location)
				{
					if (!LaunchProcess(tape.App4Location))
						echo(I18N.TT_AppNotFound, tape.App4Location);
				}
				break;
			case IDM_APP5:
				if (tape.App5Location)
				{
					if (!LaunchProcess(tape.App5Location))
						echo(I18N.TT_AppNotFound, tape.App5Location);
				}
				break;
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case ID_MENU_TO_MODE_0:tape.Mode[tabrightclick] = 0; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_1:tape.Mode[tabrightclick] = 1; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_2:tape.Mode[tabrightclick] = 2; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_3:tape.Mode[tabrightclick] = 3; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_4:tape.Mode[tabrightclick] = 4; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_5:tape.Mode[tabrightclick] = 5; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_6:tape.Mode[tabrightclick] = 6; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_7:tape.Mode[tabrightclick] = 7; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_TO_MODE_8:tape.Mode[tabrightclick] = 8; tape.Save(tape.Setting_TabToMode); PostMessage(hWnd, WM_REDRAW_TABS, tabrightclick, 0); tape.Save(tape.Setting_TabToMode); break;
			case ID_MENU_SEE_VIEW2:
				mDlg2.setCloned(true);
				mDlg2.SetTab(tabrightclick);
				mDlg2.Show();
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_CREATE:
	{
		load_dll = false;
		/*
				VOID* lockedResssource;
				DWORD resourceSize;
				if (LoadEmbeddedResource(IDC_VJOYINTERFACE_DLL, &lockedResssource, &resourceSize))
					WriteToFile(L"vJoyInterface.dll", lockedResssource, resourceSize, true, true);
		*/
		std::vector<char> data;
		DWORD resourceSize;
		if (LoadEmbeddedResource(IDR_VIGEMCLIENT_DLL, &data, &resourceSize))
			WriteToFile(L"ViGEmClient.dll", data, resourceSize, true, true);
		if (LoadEmbeddedResource(IDR_VJOYINTERFACE_DLL, &data, &resourceSize))
			WriteToFile(L"vJoyInterface.dll", data, resourceSize, true, true);
		if (LoadEmbeddedResource(IDR_DEVCON_EXE, &data, &resourceSize))
			WriteToFile(L"Devcon.exe", data, resourceSize, true, true);
		if (isFileExists("vJoyInterface.dll") && isFileExists("ViGEmClient.dll"))
			load_dll = true;

		if (load_dll)
			_log.Init(hInst, hWnd);
		else
			_log.Init(hInst, hWnd, false);

		LoadLanguage();
		InitCommonControls();
		tape.Init(hInst, hWnd);
		tape.OpenIni(L"Ds2vJoy.ini");
		tape.Load(Settings::Setting_Category_All);
		GetCursorPos(&tape.mousepoint);
		GetCursorPos(&gridpoint);

		if (load_dll)
		{
			sDlg.Init(hInst, hWnd);
			mDlg.Init(hInst, hWnd);
			mDlg2.Init2(hInst, hWnd);
			rDlg.Init(hInst, hWnd);
			kDlg.Init(hInst, hWnd);
			vDlg.Init(hInst, hWnd);
			gDlg.Init(hInst, hWnd);
			iDlg.Init(hInst, hWnd);
			mDDlg.Init(hInst, hWnd);
			rDDlg.Init(hInst, hWnd);
			kDDlg.Init(hInst, hWnd);
			tasktray.Init(hInst, hWnd);
			cbParams.vj = &vjoy;
			cbParams.ds = &ds;
			PostMessage(hWnd, WM_TRANSPARENCY, 0, 0);
		}

		if (tape.Tasktray)
			PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		{
			hTab2 = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_FIXEDWIDTH | TCS_BUTTONS | TCS_FLATBUTTONS, 0, 0, 0, 0, hWnd, (HMENU)ID_TABVJOY, hInst, NULL);
			
			int m_TabsID[10];
			m_TabsID[0] = ID_MENU_SEE_VIEW2;
			m_TabsID[1] = ID_MENU_TO_MODE_0;
			m_TabsID[2] = ID_MENU_TO_MODE_1;
			m_TabsID[3] = ID_MENU_TO_MODE_2;
			m_TabsID[4] = ID_MENU_TO_MODE_3;
			m_TabsID[5] = ID_MENU_TO_MODE_4;
			m_TabsID[6] = ID_MENU_TO_MODE_5;
			m_TabsID[7] = ID_MENU_TO_MODE_6;
			m_TabsID[8] = ID_MENU_TO_MODE_7;
			m_TabsID[9] = ID_MENU_TO_MODE_8;
			hMenu_Tabs = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_TABS));
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_0, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_1, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_2, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_3, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_4, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_5, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_6, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_7, FALSE);
			DeleteMenu(hMenu_Tabs, ID_MENU_TO_MODE_8, FALSE);
			hMenu_Tabs_2 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_TABS));
			MENUITEMINFO info;
			for (int i = 0; i < 10; i++)
			{
				ZeroMemory(&info, sizeof(info));
				info.cbSize = sizeof(info);
				info.fMask = MIIM_FTYPE | MIIM_STATE;
				GetMenuItemInfo(hMenu_Tabs_2, m_TabsID[i], FALSE, &info);
				if (i == 0)
					GetMenuItemInfo(hMenu_Tabs, m_TabsID[i], FALSE, &info);
				info.fType = MFT_OWNERDRAW;
				info.fState = 0;
				SetMenuItemInfo(hMenu_Tabs_2, m_TabsID[i], FALSE, &info);
				if (i == 0)
					SetMenuItemInfo(hMenu_Tabs, m_TabsID[i], FALSE, &info);
			}
			SendMessage(hWnd, WM_REDRAW_TABS, tape.TabMapping, 0);

			HFONT hFont = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendMessage(hTab2, WM_SETFONT, WPARAM(hFont), TRUE);
			SendMessage(hTab2, TCM_SETITEMSIZE, 0, MAKELPARAM(43, 17));	//Remove if TCS_RIGHTJUSTIFY
			SendMessage(hTab2, TCM_SETPADDING, 0, MAKELPARAM(0, 2));

			TabCtrl_SetCurSel(hTab2, 0);
			ShowWindow(hTab2, SW_HIDE);
			mDlg.Hide();
			mDlg2.Hide();
		}

		{
			hTab = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_FIXEDWIDTH, 0, 0, 0, 0, hWnd, (HMENU)ID_TABMENU, hInst, NULL);

			TCITEM tc_item;
			tc_item.mask = TCIF_TEXT;
			tc_item.pszText = I18N.TabLog;
			TabCtrl_InsertItem(hTab, 0, &tc_item);
			if (load_dll)
			{
				tc_item.pszText = I18N.TabSettings;
				TabCtrl_InsertItem(hTab, 1, &tc_item);
				tc_item.pszText = I18N.TabMapping;
				TabCtrl_InsertItem(hTab, 2, &tc_item);
				tc_item.pszText = I18N.TabRapidFire;
				TabCtrl_InsertItem(hTab, 3, &tc_item);
				tc_item.pszText = I18N.TabKeymap;
				TabCtrl_InsertItem(hTab, 4, &tc_item);
				tc_item.pszText = I18N.TabViGEm;
				TabCtrl_InsertItem(hTab, 5, &tc_item);
				tc_item.pszText = I18N.TabGuardian;
				TabCtrl_InsertItem(hTab, 6, &tc_item);
				tc_item.pszText = I18N.TabLinks;
				TabCtrl_InsertItem(hTab, 7, &tc_item);
			}

			HFONT hFont = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
			SendMessage(hTab, WM_SETFONT, WPARAM(hFont), TRUE);
			SendMessage(hTab, TCM_SETITEMSIZE, 0, MAKELPARAM(48, 17));	//Remove if TCS_RIGHTJUSTIFY
			SendMessage(hTab, TCM_SETPADDING, 0, MAKELPARAM(0, 2));

			TabCtrl_SetCurSel(hTab, 0);
		}

		if (!load_dll)
		{
			HFONT hFont = CreateFont(11, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Lucida Console");
			SendMessage(tape.LoghWnd, WM_SETFONT, WPARAM(hFont), TRUE);
			echo(L"!!!! ERROR !!!!");
			echo();
			echo(L"vJoyInterface.dll or ViGEmClient.dll cannot be uncompressed from memory, and not found in program directory");
			return FALSE;
		}

		{
			HFONT hFont = CreateFont(11, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Lucida Console");
			SendMessage(tape.LoghWnd, WM_SETFONT, WPARAM(hFont), TRUE);
		}

		{
			hChk = CreateWindowEx(0, L"button", L"↕", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_CENTER, 451, 3, 20, 15, hWnd, (HMENU)ID_CHKBOXW, hInst, NULL);
			HFONT hFont = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendMessage(hChk, WM_SETFONT, WPARAM(hFont), TRUE);
			CheckDlgButton(hWnd, ID_CHKBOXW, BST_UNCHECKED);
		}

		{
			hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP, NULL, hWnd, ID_STATUS);
			int width[4] = { 70,140,415,-1 };
			SendMessage(hStatus, SB_SETPARTS, 4, (LPARAM)width);
			SendMessage(hStatus, SB_SETTEXT, 0, (WPARAM)I18N.Status_Wait);

			HFONT hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"MS Shell Dlg");
			SendMessage(hStatus, WM_SETFONT, WPARAM(hFont), TRUE);
		}

		echo(L"Modified version of 090: Ds4vJoy and Ds5vJoy");
		echo(L"https://github.com/ytyra/Ds2vJoy 31/07/2021");
		std::wstring datestring = std::to_wstring(tape.VersionDate);
		echo(L"Version %sv%s", datestring.std::wstring::substr(0, 8).c_str(), datestring.std::wstring::substr(8, (datestring.length() - 8)).c_str());
		echo(L"");
		tasktray.Show();

		if (!vjoy.Init(hWnd, true))
			return -1;

		if (!vg.Init(hWnd))
			return -1;

		if (!hid.Init(hWnd))
			return -1;

		SendMessage(hWnd, WM_DISPLAYCHANGE, 0, 0);

		if (!SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 0))
			echo(I18N.Log_Wait_vJoy);
		if (!SendMessage(hWnd, WM_DEVICE_DS_START, 0, 0))
			echo(I18N.Log_Wait_ds);

		SetTimer(hWnd, 1, 10000, NULL);	//Check for vJoy or DS interruptions
		SetTimer(hWnd, 2, 100, NULL);	//Set Ondulating LED
		SetTimer(hWnd, 3, 1000, NULL);	//Battery
		SetTimer(hWnd, 4, 5000, NULL);	//HidGuardian Whitelist Check
		SetTimer(hWnd, 5, 10, NULL);	//When moving windows
		SetTimer(hWnd, 6, 100, NULL);	//Print Profile, mode, mouse and vJoy Buttons when editing

		break;
	}
	case WM_TIMER:
		if (wParam == 1)
		{
			if (!vjoy.Active())
				SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 1);
			if (!ds.Active() && tape.PreferredDS)
				SendMessage(hWnd, WM_DEVICE_DS_START, 0, 1);
		}
		else if (wParam == 2)
		{
			CPULimiter limiter = 1;		//CPU percents
/*			static COLORREF ledcolor;
			ledcolor = tape.LED_Color;
			if (ds.Active())
			{
				ds.SetLED(GetRValue(ledcolor), GetGValue(ledcolor), GetBValue(ledcolor));
				ds.Write();
			}
*/
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
				TCHAR buf[20];
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
				else
				{
					if (LowBatt)
					{
						LowBatt = false;
						ds.SetOrangeLED(0);
					}
				}
				bool charge = ds.BatteryCharge();
				bool full = ds.BatteryFull();
				if (ds.isBT())
				{
					wsprintf(buf, TEXT("BT (%s%d%%)"), full ? L"*" : charge ? L"+" : L"", battery);
					battery += 1;
				}
				else
				{
					wsprintf(buf, TEXT("USB (%s%d%%)"), full ? L"*" : charge ? L"+" : L"", battery);
					battery += 2;
				}
				if (charge)battery += 5;
				if (full) battery += 100;
				if (battery != iBattery)
				{
					iBattery = battery;
					tasktray.Tip(buf);
					echo(L"Battery: %s %s", buf, full ? L"Full" : charge ? L"Connected" : L"Disconnected");
				}
				if (!IsIconic(hWnd))
				{
					SendMessageTimeout(hStatus, SB_SETTEXT, 0, (LPARAM)buf, SMTO_BLOCK, 1000, NULL);
					swprintf_s(buf, TEXT("%0.5f ms"), cbParams.sw.GetAvg());
					SendMessageTimeout(hStatus, SB_SETTEXT, 1, (LPARAM)buf, SMTO_BLOCK, 1000, NULL);
				}
			}
			else
			{
				if (!IsIconic(hWnd))
				{
					SendMessageTimeout(hStatus, SB_SETTEXT, 0, (LPARAM)I18N.Status_Wait, SMTO_BLOCK, 1000, NULL);
					SendMessageTimeout(hStatus, SB_SETTEXT, 1, (LPARAM)L"", SMTO_BLOCK, 1000, NULL);
				}
			}
		}
		else if (wParam == 4)
			hid.WhitelistCheck();
		else if (wParam == 5)
		{
			if (m_flag_drag)
			{
				static POINT q;
				GetCursorPos(&q);
				SetWindowPos(hWnd, HWND_NOTOPMOST, q.x - x, q.y - y, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
				PostMessage(hWnd, WM_SIZE, -1, -3);
			}
		}
		else if (wParam == 6)
		{
			if (!IsIconic(hWnd))
			{
				SendMessageTimeout(hStatus, SB_SETTEXT, 3, (LPARAM)(L"M:" + std::to_wstring(mode) + L" Pr:" + std::to_wstring(tape.Profile)).c_str(), SMTO_BLOCK, 1000, NULL);
				if (TabCtrl_GetCurSel(hTab) == 2)
					SendMessageTimeout(hStatus, SB_SETTEXT, 2, (LPARAM)vJoySatusString, SMTO_BLOCK, 1000, NULL);
				else if (TabCtrl_GetCurSel(hTab) == 4)
				{
					COLORREF color;
					HDC hdcScreen;

					hdcScreen = GetDC(NULL);
					if (hdcScreen != NULL)
					{
						if (GetCursorPos(&tape.mousepoint))
						{
							color = GetPixel(hdcScreen, tape.mousepoint.x, tape.mousepoint.y);
							if (color != CLR_INVALID)
							{
								wsprintf(KeymapSatusString, L"RGB:%03i-%03i-%03i #%02x%02x%02x", GetRValue(color), GetGValue(color), GetBValue(color), GetRValue(color), GetGValue(color), GetBValue(color));
								SendMessageTimeout(hStatus, SB_SETTEXT, 2, (LPARAM)KeymapSatusString, SMTO_BLOCK, 1000, NULL);
							}
						}
						ReleaseDC(GetDesktopWindow(), hdcScreen);
					}
				}
				else if (TabCtrl_GetCurSel(hTab) == 5)
					SendMessageTimeout(hStatus, SB_SETTEXT, 2, (LPARAM)ViGEmSatusString, SMTO_BLOCK, 1000, NULL);
			}
		}
		break;
	case WM_DEVICE_DS_START:
	{
		// lParam == 0 verbose
		// lParam == 1 silent
		if (!load_dll)
			return FALSE;

		callbackpause = true;
		ds.GetButton(dsButtonID::LX)->SetThreshold();
		ds.GetButton(dsButtonID::LY)->SetThreshold();
		ds.GetButton(dsButtonID::RX)->SetThreshold();
		ds.GetButton(dsButtonID::RY)->SetThreshold();
		ds.Close();
		cbParams.sw.Reset(100);

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

		ds.PreOpen();
		if (ds.Active())
		{
			vDlg.Init2();
			ds.SetOrangeLED(0x00);
			ds.SetWhiteLED(0x00);
			ds.AssignOffsets();
			ds.Open(hWnd, !lParam);
			callbackpause = false;
			return TRUE;
		}
		else if (!tape.PreferredDS)
		{
			vDlg.Init2();
			ds.Open(hWnd, !lParam);
			callbackpause = false;
			return TRUE;
		}

		return FALSE;
	}
	case WM_DEVICE_VJOY_START:
	{
		// lParam == 0 verbose
		// lParam == 1 silent
		if (!load_dll)
			return FALSE;

		vjoy.Close();

		if (vjoy.Open(tape.vJoyDeviceID, !lParam))
		{
			cbParams.vJoyID = tape.vJoyDeviceID;
			if (tape.FFB)
			{
				cbParams.ffbTime = 0;
				vjoy.SetFFBCallback(cbParams.ffb.callback, &cbParams.ffb);
			}
			else
				vjoy.SetFFBCallback(NULL, NULL);
			return TRUE;
		}

		return FALSE;
	}
	case WM_RESET:
	{
		Mappings Mappingdatatmp;
		RapidFires RapidFiredatatmp;
		Keymaps Keymapdatatmp;
		tape.Mappingdata = Mappingdatatmp;
		tape.RapidFiredata = RapidFiredatatmp;
		tape.Keymapdata = Keymapdatatmp;

//		MappingDataDlg mDDlgtmp;
//		RapidFireDataDlg rDDlgtmp;
//		KeymapDataDlg kDDlgtmp;
//		mDDlg = mDDlgtmp;
//		rDDlg = rDDlgtmp;
//		kDDlg = kDDlgtmp;
		break;
	}
	case WM_RELOAD:
	{
		// lParam == 0 verbose
		// lParam == 1 silent
		if (!load_dll)
			return FALSE;

		WCHAR* ret1 = lstrcpynW(vJoySatusString, L"", sizeof(vJoySatusString) / sizeof(vJoySatusString[0]));
		WCHAR* ret2 = lstrcpynW(ViGEmSatusString, L"", sizeof(ViGEmSatusString) / sizeof(ViGEmSatusString[0]));
		SendMessage(hWnd, WM_TIMER, 6, 0);

		callbackpause = true;

		{
			TabCtrl_SetCurSel(hTab, 0);
			TabCtrl_SetCurSel(hTab2, 0);
			mDlg2.SetTab(0);
			mDlg2.setCloned(false);
			mDDlg.Hide();
			kDDlg.Hide();
			rDDlg.Hide();
			sDlg.Hide();
			mDlg.Hide();
			mDlg2.Hide();
			rDlg.Hide();
			kDlg.Hide();
			vDlg.Hide();
			gDlg.Hide();
			iDlg.Hide();
			_log.Show();
		}
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

		ds.Close();
		vjoy.Close();
		vg.CloseClient();
		SendMessage(hWnd, WM_RESET, 0, 0);

		tape.Load(Settings::Setting_Category_All);
		SendMessage(hWnd, WM_REDRAW_TABS, tape.TabMapping, 0);
		ShowWindow(hTab2, SW_HIDE);
		mDlg.Hide();
//		mDDlg.Init(hInst, hWnd);
//		rDDlg.Init(hInst, hWnd);
//		kDDlg.Init(hInst, hWnd);
		mDDlg.m_mode = 0;
		if (!vjoy.Init(hWnd))
			return -1;
		if (!vg.Init(hWnd))
			return -1;
		if (!hid.Init(hWnd))
			return -1;
		SendMessage(hWnd, WM_DISPLAYCHANGE, 0, 0);
		SendMessage(hWnd, WM_CREATE_MENU, 0, 0);
		SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, lParam);
		SendMessage(hWnd, WM_DEVICE_DS_START, 0, lParam);
		break;
	}
	case WM_REDRAW_TABS:
		TCITEM tc_item;
		tc_item.mask = TCIF_TEXT;
		WCHAR buff[MAX_PATH];
		TabCtrl_DeleteAllItems(hTab2);
		for (int i = 0; i < 9; i++)
		{
			TabCtrl_SetItem(hTab2, i, L"");
			if (tape.Mode[i])
			{
				_snwprintf_s(buff, sizeof(buff), L"%d: m%d", i, tape.Mode[i]);
				tc_item.pszText = buff;
			}
			else
			{
				if (i)
					_snwprintf_s(buff, sizeof(buff), L"%d", i);
				else
					_snwprintf_s(buff, sizeof(buff), L"%s", L"Always");
				tc_item.pszText = buff;
			}
			TabCtrl_InsertItem(hTab2, i, &tc_item);
		}
		mDlg.SetTab((int)wParam);
		TabCtrl_SetCurSel(hTab2, wParam);
		if (TabCtrl_GetCurSel(hTab) == 2)
			mDlg.Show();
		ShowWindow(hTab2, SW_HIDE);
		ShowWindow(hTab2, SW_SHOW);
		break;
	case WM_LOGNEW:
		_log.Update();
		break;
	case WM_SETORANGELED:
		if (ds.Active() && tape.ActualDS == 2)
			ds.SetOrangeLED((byte)wParam);
		break;
	case WM_SETWHITELED:
		if (ds.Active() && tape.ActualDS == 2)
			ds.SetWhiteLED((byte)wParam);
		break;
	case WM_SETTRIGGERS:
		if (ds.Active() && tape.ActualDS == 2)
		{
			ds.SetTriggers((int)wParam);
			ds.Write();
		}
		break;
	case WM_ADDMAPPING:
	{
		if ((int)lParam <= 0)
		{
			if ((int)lParam == -1)
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
			}
			if ((int)wParam != 1)
				mDDlg.Hide();
			mDlg.SetTab(TabCtrl_GetCurSel(hTab2));
			PostMessage(hWnd, WM_SIZE, 0, 0);
			if (TabCtrl_GetCurSel(hTab) == 2)
				mDlg.Show();
			if (mDlg2.isCloned())
			{
				mDlg2.SetTab(mDlg2.GetTab());
				mDlg2.Show();
			}
		}
		else if ((int)lParam == 1)
		{
			if ((int)wParam == 1)
				mDlg.addMappingDlgBack();
			else if ((int)wParam == 2)
				mDlg.editMappingDlgBack();
			else if ((int)wParam == 3)
				mDlg.editMappingDlgBackMulti();
		}
		else if ((int)lParam == 2)
		{
			if ((int)wParam == 1)
				mDlg2.addMappingDlgBack();
			else if ((int)wParam == 2)
				mDlg2.editMappingDlgBack();
			else if ((int)wParam == 3)
				mDlg2.editMappingDlgBackMulti();
		}
		break;
	}
	case WM_ADDRAPIDFIRE:
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
	case WM_ADDKEYMAP:
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
	case WM_CHANGE_PAD:
		if (wParam == 0)
		{
			tape.ViGEmActive = 0;
			tape.Save(tape.Setting_ViGEmActive);
			vg.CloseClient();
		}
		else if (wParam == 1)
		{
			vg.LoadDevice(&ds, &vjoy);
			vg.InitClient();
			tape.ViGEmActive = true;
			tape.Save(tape.Setting_ViGEmActive);
		}
		else if (wParam == 2)
			if (tape.ViGEmActive)
			{
				vg.CloseClient();
				vg.LoadDevice(&ds, &vjoy);
				vg.InitClient();
				tape.ViGEmActive = true;
			}
		break;
	case WM_CHANGE_HIDS:
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
	case WM_CREATE_MENU:
			tasktray.CreateMenu();
			break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_DPICHANGED:
	case WM_DISPLAYCHANGE:
	{
//		int bppScreen = wParam;
//		int WScreen = LOWORD(lParam);
//		int HScreen = HIWORD(lParam);
		RECT desktop;
		GetClientRect(GetDesktopWindow(), &desktop);
		tape.W = (short)desktop.right;
		tape.H = (short)desktop.bottom;
		tape.w = (short)(tape.W / 2);
		tape.h = (short)(tape.H / 2);
		tape.proportianality = (tape.W > tape.H) ? (tape.W / tape.H) : (tape.H / tape.W);
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
	case WM_MOVE:
		if (m_flag_drag)
			m_flag_drag++;
		break;
	case WM_NCRBUTTONDOWN:
	case WM_TRANSPARENCY:
		if (lParam)
		{
			tape.Transparency = !tape.Transparency;
			tape.Save(tape.Setting_Transparency);
		}
		if (tape.Transparency)
			SetWindowTransparent(hWnd, true, 60);
		else
			SetWindowTransparent(hWnd, false, NULL);
		mDlg.SetTransparency(tape.Transparency);
		mDlg2.SetTransparency(tape.Transparency);
		mDDlg.SetTransparency(tape.Transparency);
		break;
	case WM_NCLBUTTONDOWN:
	{
		int xtmp = (short)LOWORD(lParam);
		int ytmp = (short)HIWORD(lParam);
		RECT win;
		GetWindowRect(hWnd, &win);
		x = (short)(xtmp - win.left);
		y = (short)(ytmp - win.top);
		if (x > 345 && x < 392 && y >= 0 && y <= 30)
			break;
		else if (x > 437 && x < 485 && y >= 0 && y <= 30)
			break;
		mDDlg.movable = false;
		if (TabCtrl_GetCurSel(hTab) != 2)
			mDlg2.Hide();
		if (mDlg2.isCloned() && TabCtrl_GetCurSel(hTab) == 2)
		{
			mDlg2.moving = true;
			mDlg2.SetTab(mDlg2.GetTab());
			mDlg2.Hide();
			mDlg2.Show();
			SetFocus(hWnd);
		}
		SetFocus(hWnd);
		if (!extended)
		{
			RECT rect;
			GetWindowRect(mDDlg.m_hDlg, &rect);
			mDDlg.m_y = rect.top - win.top;
		}
		else
			extended = false;
		mDDlg.docked = mDDlg.docked_last;
		PostMessage(hWnd, WM_SIZE, -1, -3);
		::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		SetWindowPos(hWnd, HWND_TOPMOST, win.left, win.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
		m_flag_drag = true;
		break;
	}
	case WM_NCLBUTTONUP:
	{
		mDDlg.movable = true;
		bool minimize = false;
		bool close = false;
		if (m_flag_drag < 3)
		{
			if (x > 345 && x < 392 && y >= 0 &&y <= 30)
				minimize = true;
			else if (x > 437 && x < 485 && y >= 0 && y <= 30)
				close = true;
		}
		m_flag_drag = false;
		if (minimize || (close && tape.CloseMinimize))
			{ PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); break; }
		else if (close)
			{ PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0); break; }
		RECT rect;
		ClientArea(&rect, true);
		if ((short)HIWORD(lParam) < rect.top + 2)
		{
			if (!extended)
			{
				CheckDlgButton(hWnd, ID_CHKBOXW, BST_CHECKED);
				::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				extended = true;
			}
			if (mDDlg.docked == 2) { mDDlg.docked_last = mDDlg.docked; mDDlg.docked = 1; }
			SendMessage(hWnd, WM_SIZE, 0, -2);
			if (mDlg2.isCloned())
			{
				mDlg2.moving = false;
				mDlg2.SetTab(mDlg2.GetTab());
				mDlg2.Hide();
				mDlg2.Show();
				SetFocus(hWnd);
			}
			break;
		}
		else
		{
			extended = false;
			if (!topmost)
				::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			if (mDlg2.isCloned() && TabCtrl_GetCurSel(hTab) == 2)
			{
				mDlg2.moving = false;
				mDlg2.SetTab(mDlg2.GetTab());
				mDlg2.Hide();
				mDlg2.Show();
				SetFocus(hWnd);
			}
			break;
		}
	}
	case WM_EXITSIZEMOVE:
		PostMessage(hWnd, WM_SIZE, -1, -1);
		break;
	case WM_SIZE:
	{
		RECT win;
		GetWindowRect(hWnd, &win);
		RECT rect;
		ClientArea(&rect);

		if (lParam < 0)
		{
			if (extended)
			{
				mDlg2.MoveWindow(win.right - 7, rect.top + 31, 474, rect.bottom - 39, TRUE);
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0:
				case 2:
				case 3:
				case 4: if (!IsWindowVisible(kDDlg.m_hDlg) && !IsWindowVisible(rDDlg.m_hDlg))
				{
					SetWindowPos(hWnd, HWND_TOPMOST, win.left, rect.top, 492, rect.bottom, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break;
				}
				case 1:
				case 5:
				case 6:
				case 7: SetWindowPos(hWnd, HWND_TOPMOST, win.left, rect.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE); break;
				}
				if (lParam == -2)
				{
					GetWindowRect(hWnd, &win);
					switch (mDDlg.docked)
					{
					case 1:
					case 2: mDDlg.MoveWindow(win.right - 6, win.top + 63, 474, 287, TRUE);	break;				//docked center >, right
					case 3: mDDlg.MoveWindow(win.left + 6 - 474, win.top + 63, 474, 287, TRUE); break;			//docked left
					}
				}
			}
			else
			{
				mDlg2.MoveWindow(win.right - 7, win.top + 31, 474, 288, TRUE);
				if (wParam != -1)
					SetWindowPos(hWnd, HWND_NOTOPMOST, win.left, win.top, 492, 327, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_DEFERERASE);
				if (lParam < -1)
				{
					GetWindowRect(hWnd, &win);
					int heightmp = (lParam == -3) ? mDDlg.m_y : 31;
					switch (mDDlg.docked)
					{
					case 1: mDDlg.MoveWindow(win.right - 7, win.top + heightmp, 474, 287, TRUE); break;		//docked right
					case 2: mDDlg.MoveWindow(win.left + 9, win.top + 31, 474, 287, TRUE); break;			//docked center
					case 3: mDDlg.MoveWindow(win.left + 6 - 474, win.top + heightmp, 474, 287, TRUE); break;//docked left
					}
				}
			}
		}

		if (wParam == -1)
			break;

		GetClientRect(hWnd, &rect);

		MoveWindow(hChk, rect.right - 25, 3, 20, 15, FALSE);
		MoveWindow(hTab, 0, 0, rect.right, rect.bottom, FALSE);
		MoveWindow(hTab2, 3, 19, rect.right + 2, rect.bottom - 19, FALSE);
		MoveWindow(hStatus, 0, rect.bottom -24, rect.right, rect.bottom, FALSE);

		rect.left += 3;
		rect.top += 21;
		rect.right -= 6;
		rect.bottom -= 45;

		_log.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		sDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		mDlg.MoveWindow(rect.left, rect.top + 14, rect.right, rect.bottom - 14, FALSE);
		rDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		kDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		vDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		gDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		iDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		rDDlg.MoveWindow(rect.left, rect.top, rect.right, rect.bottom, FALSE);
		kDDlg.MoveWindow(rect.left - kDDlg.dlgPage * 470, rect.top, rect.right + kDDlg.dlgPage * 470, rect.bottom, FALSE);

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case ID_TABMENU:
			switch (((NMHDR*)lParam)->code)
			{
			case TCN_SELCHANGING:
				SendMessage(hStatus, SB_SETTEXT, 2, (WPARAM)L"");
				mDDlg.m_mode = 0;
				rDDlg.m_mode = 0;
				kDDlg.m_mode = 0;
				mDDlg.Hide();
				rDDlg.Hide();
				kDDlg.Hide();
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0:
					_log.Hide();
					break;
				case 1:
					sDlg.Hide();
					break;
				case 2:
					ShowWindow(hTab2, SW_HIDE);
					mDlg.Hide();
					if (!extended)
						mDlg2.Hide();
					break;
				case 3:
					rDlg.Hide();
					break;
				case 4:
					kDlg.Hide();
					break;
				case 5:
					vDlg.Hide();
					break;
				case 6:
					gDlg.Hide();
					break;
				case 7:
					iDlg.Hide();
					break;
				}
				break;
			case TCN_SELCHANGE:
				SendMessage(hWnd, WM_EXITSIZEMOVE, 0, 0);
				switch (TabCtrl_GetCurSel(hTab))
				{
				case 0:
					_log.Show();
					break;
				case 1:
					sDlg.Show();
					break;
				case 2:
					mDlg.Show();
					ShowWindow(hTab2, SW_SHOW);
					TabCtrl_SetCurSel(hTab2, tape.TabMapping);
					if (mDlg2.isCloned())
					{
						mDlg2.SetTab(mDlg2.GetTab());
						mDlg2.Show();
					}
					break;
				case 3:
					rDlg.Show();
					break;
				case 4:
					kDlg.Show();
					break;
				case 5:
					vDlg.Show();
					break;
				case 6:
					gDlg.Show();
					break;
				case 7:
					iDlg.Show();
					break;
				}
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case ID_TABVJOY:
			switch (((NMHDR*)lParam)->code)
			{
			case NM_RCLICK:
			{
				TCHITTESTINFO tabinfo;
				POINT pt;
				GetCursorPos(&pt);
				POINT ptt = pt;
				ScreenToClient(hTab2, &ptt);
				tabinfo.pt = ptt;
				int tab = TabCtrl_HitTest(hTab2, &tabinfo);
				if (tab == -1)
					break;
				else
					tabrightclick = tab;
				if (tabrightclick)
					TrackPopupMenu((HMENU)GetSubMenu(hMenu_Tabs_2, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
				else
					TrackPopupMenu((HMENU)GetSubMenu(hMenu_Tabs, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
			}
			break;
			case TCN_SELCHANGE:
				tape.TabMapping = TabCtrl_GetCurSel(hTab2);
				tape.Save(tape.Setting_TabMapping);
				mDlg.SetTab(tape.TabMapping);
				mDlg.Show();
				break;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_TASKTRAY:
		tasktray.Message(wParam, lParam);
		break;
	case WM_DESTROY:
	{
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
		PostQuitMessage(0);
		{
			HMODULE hMod = ::GetModuleHandle(L"ViGEmClient.dll");
			if (hMod != 0)
				::FreeLibrary(hMod);
		}
		{
			HMODULE hMod = ::GetModuleHandle(L"vJoyInterface.dll");
			if (hMod != 0)
				::FreeLibrary(hMod);
		}
		::DeleteFile(L"ViGEmClient.dll");
		::DeleteFile(L"vJoyInterface.dll");
		::DeleteFile(L"Devcon.exe");
		break;
	}
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_CLOSE:
			tape.Save(tape.Setting_All);
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case SC_MINIMIZE:
			{ ::SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); topmost = false; }
			mDDlg.Hide();
			mDlg2.Hide();
			ShowWindow(hWnd, SW_HIDE);
			return FALSE;
		case SC_RESTORE:
			PostMessage(hWnd, WM_COMMAND, (WPARAM)ID_CHKBOXW, (LPARAM)GetDlgItem(hWnd, ID_CHKBOXW));
			if (mDDlg.m_mode > 0)
				mDDlg.Show();
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		RECT desktop;
		ClientArea(&desktop);
		RECT dialog;
		GetClientRect(hDlg, &dialog);
		SetWindowPos(hDlg, HWND_TOP,
			desktop.left + ((desktop.right - desktop.left - dialog.right) / 2),
			desktop.top + ((desktop.bottom - desktop.top - dialog.bottom) / 2),
			0, 0, SWP_NOSIZE);
	}
	return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void OutRun()
{
//  #include <future>
//	std::future<void> fut = std::async(std::launch::async, [] { OutRun();});
//	t1.join();
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
