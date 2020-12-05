// ds5vjoy.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include "ds5vjoy.h"
#include "DS5.h"
#include "vjoy.h"
#include "FFB.h"
#include "Stopwatch.h"

#include "Settings.h"
#include "Tasktray.h"

#include "Log.h"
#include "SettingDlg.h"
#include "MappingDlg.h"
#include "KeymapDlg.h"
#include "RapidFireDlg.h"
#include "Language.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名
Settings g_settings;

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
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

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化しています。
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DS5VJOY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーションの初期化を実行します:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DS5VJOY));

    MSG msg;

    // メイン メッセージ ループ:
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



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;// CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DS5VJOY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = 0;// MAKEINTRESOURCEW(IDC_DS5VJOY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_DS5VJOY_S));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 486, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   if (nCmdShow== SW_SHOWMINNOACTIVE) {
	   SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
   }
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウの描画
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//

typedef struct _ds5cbParams
{
	vJoyDevice *vj;
	int vJoyDevID;
	DS5Device *ds5;
	Mappings mapping;
	Keymaps keymapdata;
	std::vector<RapidFire> rapidFires;
	bool rapidFireflag;
	DS5Button *splitTouchPad;
	int splitCol;
	int splitRow;
	int splitButton;
	Stopwatch sw;
	FFB ffb;
	double ffb_time;
} DS5cbParams;

void ds5inputcb(DS5Device * ds5, BOOL updateflag,void*param) {
	double now;
	DS5cbParams *p = (DS5cbParams*)param;
	p->sw.Lap(&now);
	if (p->ffb_time + 3 < now) {//3ms
		BYTE left, right;
		if (p->ffb.Calc(&left, &right)) {
			ds5->SetMoter(left, right);
			ds5->Write();
		}
		p->ffb_time = now;
	}


	if (updateflag == false && p->rapidFireflag == false)
		return;

	vJoyDevice* vjoy = p->vj;
	vjoy->ClearState();

	//ボタンマッピング
	size_t n = p->mapping.size();
	for (size_t i = 0; i < n; i++) {
		p->mapping[i].Run();
	}

	//タッチパッドの分割
	if (p->splitTouchPad != 0 && p->splitTouchPad->isPushed() ) {
		for (int idx = 0; idx < 2; idx++) {
			if (ds5->TouchActive(idx)) {
				int pos = 0;
				if (p->splitRow > 0) {
					pos = ds5->TouchY(idx) / (943 / p->splitRow) * p->splitCol;
				}
				if (p->splitCol > 0) {
					pos += ds5->TouchX(idx) / (1920 / p->splitCol);
				}
				if (p->splitButton - 1 + pos < 128) {
					vjoy->GetButton((vJoyButtonID)(vJoyButton::Button1 + p->splitButton - 1 + pos))->SetVal(1);
				}
			}
		}
	}
	
	//連射
	{
		bool flag=false;
		size_t max = p->rapidFires.size();
		for (size_t i = 0; i < max; i++) {
			if (p->rapidFires[i].Run(now)) {
				flag = true;
			}
		}
		p->rapidFireflag = flag;
	}

	//ボタンが押されたらキーを送信
	size_t max = p->keymapdata.size();
	for (size_t i = 0; i < max; i++) {
		p->keymapdata[i].Run();
	}

	vjoy->Update();

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DS5Device ds5;
	static vJoyDevice vjoy;
	static HWND hTab;
	static HWND hStatus;
	static COLORREF ledcolor;
	static Tasktray tasktray;
	static LogDlg lDlg;
	static SettingDlg sDlg;
	static MappingDlg mDlg;
	static RapidFireDlg rDlg;
	static KeymapDlg kDlg;
	static DS5cbParams cbParams;
	static int iBattery=-1;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		LoadLanguage();
		InitCommonControls();
		g_settings.OpenIni(L"ds5vjoy.ini");
		g_settings.Load();
		lDlg.Init(hInst, hWnd);
		sDlg.Init(hInst, hWnd);
		kDlg.Init(hInst, hWnd);
		mDlg.Init(hInst, hWnd);
		rDlg.Init(hInst, hWnd);
		tasktray.Init(hInst, hWnd);
		cbParams.vj = &vjoy;
		cbParams.ds5 = &ds5;

		{//タブ
			hTab = CreateWindowEx(0, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | TCS_RIGHTJUSTIFY, 0, 0, 10, 10, hWnd, (HMENU)ID_TABMENU, hInst, NULL);
			TCITEM tc_item;
			tc_item.mask = TCIF_TEXT;
			tc_item.pszText = I18N.tabLog;
			TabCtrl_InsertItem(hTab, 0, &tc_item);
			tc_item.pszText = I18N.tabSettings;
			TabCtrl_InsertItem(hTab, 1, &tc_item);
			tc_item.pszText = I18N.tabMapping;
			TabCtrl_InsertItem(hTab, 2, &tc_item);
			tc_item.pszText = I18N.tabRapidfire;
			TabCtrl_InsertItem(hTab, 3, &tc_item);
			tc_item.pszText = I18N.tabKeymap;
			TabCtrl_InsertItem(hTab, 4, &tc_item);
		}

		//ステータスバー
		{
			hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP, NULL, hWnd, ID_STATUS);
			int width[3] = { 100,200,-1 };
			SendMessage(hStatus, SB_SETPARTS, 3, (LPARAM)width);
			SendMessage(hStatus, SB_SETTEXT, 0 | 0, (WPARAM)I18N.status_wait);
		}

		LogPrintf(L"https://github.com/090/DS5vJoy Ver1.3");

		//vjoy初期化
		if (!vjoy.Init(hWnd)) {
			return -1;
		}

		//デバイスオープン
		if (!SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 0)) {
			LogPrintf(I18N.log_wait_vjoy);
		}else if (!SendMessage(hWnd, WM_DEVICE_DS5_START, 0, 0)) {
			LogPrintf(I18N.log_wait_ds5);
		}

		//デバイスのチェック間隔
		SetTimer(hWnd, 1, 10000, NULL);
		//ステータス更新間隔
		SetTimer(hWnd, 2, 1000, NULL);

		break;
	case WM_TIMER:
		if (wParam == 1) {
			if (!vjoy.Active() ) {
				SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 0);
			}
			if (!ds5.Active() ) {
				SendMessage(hWnd, WM_DEVICE_DS5_START, 0, 0);
			}
		}
		else if (wParam == 2) {

			if (ds5.Active()) {
				TCHAR buf[20];
				int battery = ds5.Battery();
				bool charge = ds5.BatteryCharge();
				bool full = ds5.BatteryFull();
				if (ds5.isBT()) {
					wsprintf(buf, TEXT("BT(%s%d%%)"), full ? L"*": charge ? L"+" : L"", battery);
					battery += 1;
				}
				else {
					wsprintf(buf, TEXT("USB(%s%d%%)"), full ? L"*": charge ? L"+" : L"", battery);
					battery += 2;
				}
				if (charge)battery += 5;
				if (full) battery += 100;
				if (battery != iBattery) {
					iBattery = battery;
					tasktray.Tip(buf);
					LogPrintf(L"Battery: %s %s", buf,full?L"connected":charge?L"charge":L"");
				}
				SendMessage(hStatus, SB_SETTEXT, 0, (WPARAM)buf);
				swprintf_s(buf, TEXT("%0.2fms"), cbParams.sw.GetAvg());
				SendMessage(hStatus, SB_SETTEXT, 1, (WPARAM)buf);
			}
			else {
				SendMessage(hStatus, SB_SETTEXT, 0 | 0, (WPARAM)I18N.status_wait);
				SendMessage(hStatus, SB_SETTEXT, 1 | 0, (WPARAM)L"");
			}
			if (ledcolor != g_settings.LED_Color) {
				ledcolor = g_settings.LED_Color;
				ds5.SetLED(GetRValue(ledcolor), GetGValue(ledcolor), GetBValue(ledcolor));
				if(ds5.Active())
					ds5.Write();
			}
		}
		break;
	case WM_DEVICE_VJOY_START:
		if (g_settings.Tasktray) {
			tasktray.Show();
		}
		else {
			tasktray.Hide();
		}
		vjoy.Close();
		if (vjoy.Open(g_settings.vJoyDeviceID)) {
			cbParams.vJoyDevID = g_settings.vJoyDeviceID;
			if (g_settings.FFB) {
				cbParams.ffb_time = 0;
				vjoy.SetFFBCallback(cbParams.ffb.callback, &cbParams.ffb);
			}
			else {
				vjoy.SetFFBCallback(NULL, NULL);
			}
			return TRUE;
		}
		return FALSE;
	case WM_DEVICE_DS5_START:{
		ds5.Close();
		if (vjoy.Active()) {
			//Stopwatch初期化
			cbParams.sw.Reset(100);

			//ds5コールバック登録
			ds5.SetCallback(ds5inputcb, &cbParams);

			//派手に電飾
			ledcolor = g_settings.LED_Color;
			ds5.SetLED(GetRValue(ledcolor), GetGValue(ledcolor), GetBValue(ledcolor));

			//ボタンマッピング
			{
				cbParams.mapping.clear();
				size_t max = g_settings.Mappingdata.size();
				for (size_t i = 0; i < max;++i){
					Mapping *data = &g_settings.Mappingdata[i];
					if ( data->LoadDevice(&ds5, &vjoy))
						cbParams.mapping.push_back(*data);
				}
			}

			//TouchPadの分割
			if (g_settings.SplitTouchPad) {
				cbParams.splitTouchPad = ds5.GetButton(DS5Button::TOUCH);
				cbParams.splitCol = g_settings.TouchCol;
				cbParams.splitRow = g_settings.TouchRow;
				cbParams.splitButton = g_settings.TouchPadButton;
			}
			else {
				cbParams.splitTouchPad = 0;
			}

			//キーマッピング
			{
				cbParams.keymapdata.clear();
				size_t max = g_settings.Keymapdata.size();
				for (size_t i = 0; i < max; ++i) {
					Keymap *data = &g_settings.Keymapdata[i];
					if ( data->LoadDevice(&vjoy) )
						cbParams.keymapdata.push_back(*data);
				}
			}

			//連射
			cbParams.rapidFires.clear();
			for (auto itr = g_settings.RapidFiredata.begin(); itr != g_settings.RapidFiredata.end(); ++itr) {
				if (itr->second.LoadDevice(&vjoy))
					cbParams.rapidFires.push_back(itr->second);
			}
			cbParams.rapidFireflag = false;

			//接続DS5指定
			ds5.SetTargetSerial(g_settings.getSerial());

			return ds5.Open();
		}
		return FALSE;
	}
	case WM_DEVICECHANGE:
		if (!vjoy.Active()) {
			SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 0);
		}
		if (!ds5.Active()) {
			SendMessage(hWnd, WM_DEVICE_DS5_START, 0, 0);
		}
		break;
	case WM_CHANGE_SETTING:
		if (ds5.Active()) {
			LogPrintf(I18N.log_change_settings);
		}
		SendMessage(hWnd, WM_DEVICE_VJOY_START, 0, 0);
		SendMessage(hWnd, WM_DEVICE_DS5_START, 0, 0);
		
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_SIZE:{
		SendMessage(hStatus, WM_SIZE, wParam, lParam);
		RECT rc = { 0 }, statusBar;
		rc.right = LOWORD(lParam);
		rc.bottom = HIWORD(lParam);
		GetClientRect(hStatus, &statusBar);
		rc.bottom -= statusBar.bottom;
		MoveWindow(hTab, 0, 0, rc.right, rc.bottom, FALSE);
		TabCtrl_AdjustRect(hTab, FALSE, &rc);
		rc.bottom -= rc.top;
		rc.right -= rc.left;
			
		lDlg.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);
		sDlg.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);
		kDlg.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);
		mDlg.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);
		rDlg.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_NOTIFY:
		switch (((NMHDR *)lParam)->code) {
		case TCN_SELCHANGING:
			switch (TabCtrl_GetCurSel(hTab)) {
			case 0:
				lDlg.Hide();
				break;
			case 1:
				sDlg.Hide();
				break;
			case 2:
				mDlg.Hide();
				break;
			case 3:
				rDlg.Hide();
				break;
			case 4:
				kDlg.Hide();
				break;
			}
			break;
		case TCN_SELCHANGE:
			switch (TabCtrl_GetCurSel(hTab)) {
			case 0:
				lDlg.Show();
				break;
			case 1:
				sDlg.Show();
				break;
			case 2:
				mDlg.Show();
				break;
			case 3:
				rDlg.Show();
				break;
			case 4:
				kDlg.Show();
				break;
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TASKTRAY:
		tasktray.Message(wParam, lParam);
		break;
    case WM_DESTROY:
		tasktray.Hide();
		if(g_settings.DisconnectBT)
			ds5.DisconnectBT();
		ds5.Close();
		vjoy.Close();
		FreeLanguage();
        PostQuitMessage(0);
        break;
	case WM_LOGNEW:
		lDlg.Update();
		break;
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			if (g_settings.Tasktray) {
				tasktray.Show();
				ShowWindow(hWnd, SW_HIDE);
				return 0;
			}
			break;
		}
//		return DefWindowProc(hWnd, message, wParam, lParam);
//		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
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
