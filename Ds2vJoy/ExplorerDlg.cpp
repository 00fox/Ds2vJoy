#include "stdafx.h"
#include "ExplorerDlg.h"
#include "Ds2vJoy.h"

using namespace Microsoft::WRL;
namespace numerics = winrt::Windows::Foundation::Numerics;
static HMENU hMenuWeb;
static HMENU hMenuFav;
static thread_local size_t s_appInstances = 0;
static bool m_blockImages = false;
static bool m_deferredScripts = false;
static bool m_rightClickFav = false;
static RECT m_explorer_win;
static std::wstring DarkModeStyle = LR"(
const addStyle = (() => {
  const style = document.createElement('style');
  document.head.append(style);
  return (styleString) => style.textContent = styleString; })();
addStyle(`
.header-description {color: #99cc99;}
*			{background-image: none;}
element.style {background-color: #101213}
body		{background-image: none !important; background-color: #101213 !important; color: #dddddd !important;}
header		{}
footer		{}
div			{background-image: none; background-color: transparent !important; color: #dddddd !important;}
hr			{}
p			{background-image: none !important; background-color: transparent !important; color: #dddddd !important;}
h1			{color: #bbaa66 !important;}
h2			{color: #8866bb !important;}
h3			{color: #99cc99 !important;}
h4			{color: #88bb99 !important;}
h5			{color: #aaaaaa !important;}
table		{background-image: none !important; background-color: transparent !important; color: transparent !important;}
tbody		{background-image: none !important; background-color: transparent !important; color: transparent !important;}
tr			{background-image: none !important;}
td			{background-image: none !important; background-color: #442233 !important; color: #dd9999 !important; border: 1px solid #bbaa66 !important; border-radius: 1px;}
a[href] 	{background-image: none !important; background-color: transparent !important; color: #cc99cc !important;}
a[href]:hover 	{background-image: none !important; background-color: transparent !important; color: #aaaaee !important;}
.btn		{background-color: #aaaa77 !important; border-color: #666688 !important; color: #101213 !important; border: 1px solid !important; border-radius: 3px; !important}
.btn:hover	{background-color: #bbbb88 !important; border-color: #8888aa !important; color: #101213 !important; border: 1px solid !important; border-radius: 3px; !important}
.container	{background-image: none !important;}
img			{background-color: #transparent !important; color: #2299aa !important;}
ul			{background-color: #313235 !important; color: #eecc88 !important;}
ol			{background-color: #313235 !important; color: #eebbee !important;}
li			{background-image: none !important; background-color: transparent !important;}
label		{background-image: none !important; background-color: transparent !important; color: #99cc99 !important;}
input		{background-color: #bdd3de !important; border-color: #aabb99 !important; color: #332211 !important; border: 1px solid !important; border-radius: 1px; !important}
textarea	{background-color: #555566 !important; border-color: #bbaa66 !important; color: #bbbbcc !important; border: 1px solid !important; border-radius: 1px; !important}
pre			{background-color: transparent !important; color: #eeee88 !important;}
code		{background-color: transparent !important; color: #eeee88 !important;}
nav			{background-image: none !important; background-color: transparent !important;}
span		{background-image: none !important; background-color: transparent !important;}
::-webkit-scrollbar {width: 14px; height: 14px}
::-webkit-scrollbar-button {background-color: #101213 !important;}
::-webkit-scrollbar-thumb {background-color: #101213 !important; border: 0px !important; border-left : 1px solid #aaaadd !important; min-height: 66px !important; border-radius: 1px; !important}
::-webkit-scrollbar-track {background-color: #101213 !important;}
::-webkit-scrollbar-track-piece {background-color: #101213 !important;}
::-webkit-resizer {background-color: #bbaa66 !important;}
::selection {background: #338ccc; color: #fff;}
`);
)";
static std::wstring DarkMode2Style = LR"(
const addStyle = (() => {
  const style = document.createElement('style');
  document.head.append(style);
  return (styleString) => style.textContent = styleString; })();
addStyle(`
.header-description {color: #99cc99;}
*			{background-image: none;}
element.style {background-color: #101213}
body		{background-image: none !important; background-color: #101213 !important; color: #dddddd !important;}
header		{}
footer		{}
div			{background-image: none !important; background-color: transparent !important; color: #dddddd !important;}
hr			{}
p			{background-image: none !important; background-color: transparent !important; color: #dddddd !important;}
h1			{color: #bbaa66 !important;}
h2			{color: #8866bb !important;}
h3			{color: #99cc99 !important;}
h4			{color: #88bb99 !important;}
h5			{color: #aaaaaa !important;}
table		{background-image: none !important; background-color: transparent !important; color: transparent !important;}
tbody		{background-image: none !important; background-color: transparent !important; color: transparent !important;}
tr			{background-image: none !important;}
td			{background-image: none !important; background-color: #442233 !important; color: #dd9999 !important; border: 1px solid #bbaa66 !important; border-radius: 1px;}
a[href] 	background-image: none !important; {background-color: transparent !important; color: #cc99cc !important;}
a[href]:hover 	{background-image: none !important; background-color: transparent !important; color: #aaaaee !important;}
.btn		{background-color: #aaaa77 !important; border-color: #666688 !important; color: #101213 !important; border: 1px solid !important; border-radius: 3px; !important}
.btn:hover	{background-color: #bbbb88 !important; border-color: #8888aa !important; color: #101213 !important; border: 1px solid !important; border-radius: 3px; !important}
.container	{background-image: none !important;}
img			{background-color: #transparent !important; color: #2299aa !important; filter: brightness(75%) contrast(1.1);}
ul			{background-color: #313235 !important; color: #eecc88 !important;}
ol			{background-color: #313235 !important; color: #eebbee !important;}
li			{background-image: none !important; background-color: transparent !important;}
label		{background-image: none !important; background-color: transparent !important; color: #99cc99 !important;}
input		{background-color: #bdd3de !important; border-color: #aabb99 !important; color: #332211 !important; border: 1px solid !important; border-radius: 1px; !important}
textarea	{background-color: #555566 !important; border-color: #bbaa66 !important; color: #bbbbcc !important; border: 1px solid !important; border-radius: 1px; !important}
pre			{background-color: transparent !important; color: #eeee88 !important;}
code		{background-color: transparent !important; color: #eeee88 !important;}
nav			{background-image: none !important; background-color: transparent !important;}
span		{background-image: none !important; background-color: transparent !important;}
::-webkit-scrollbar {width: 14px; height: 14px}
::-webkit-scrollbar-button {background-color: #101213 !important;}
::-webkit-scrollbar-thumb {background-color: #101213 !important; border: 0px !important; border-left : 1px solid #aaaadd !important; min-height: 66px !important; border-radius: 1px; !important}
::-webkit-scrollbar-track {background-color: #101213 !important;}
::-webkit-scrollbar-track-piece {background-color: #101213 !important;}
::-webkit-resizer {background-color: #bbaa66 !important;}
::selection {background: #338ccc; color: #fff;}
`);
)";

void ExplorerDlg::RunAsync(std::function<void()> callback)
{
	auto* task = new std::function<void()>(std::move(callback));
	PostMessage(m_hWnd, WM_APP, reinterpret_cast<WPARAM>(task), 0);
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI DownloadAndInstallWV2RT(_In_ LPVOID lpParameter)
{
	ExplorerDlg* dlg = (ExplorerDlg*)lpParameter;

	int returnCode = 2; // Download failed
	// https://developer.microsoft.com/microsoft-edge/webview2/
	HRESULT hr = URLDownloadToFile(NULL, L"https://go.microsoft.com/fwlink/p/?LinkId=2124703", L".\\MicrosoftEdgeWebview2Setup.exe", 0, 0);
	if (hr == S_OK)
	{
		// Run Download and Install in another thread so we don't block the UI thread
		SHELLEXECUTEINFO shExInfo = { 0 };
		shExInfo.cbSize = sizeof(shExInfo);
		shExInfo.fMask = SEE_MASK_NOASYNC;
		shExInfo.hwnd = 0;
		shExInfo.lpVerb = L"runas";
		shExInfo.lpFile = L"MicrosoftEdgeWebview2Setup.exe";
		shExInfo.lpParameters = L" /silent /install";
		shExInfo.lpDirectory = 0;
		shExInfo.nShow = 0;
		shExInfo.hInstApp = 0;

		if (ShellExecuteEx(&shExInfo))
			returnCode = 0; // Install successfull
		else
			returnCode = 1; // Install failed
	}

	dlg->InstallComplete(returnCode);
	return returnCode;
}

void ExplorerDlg::InstallComplete(int return_code)
{
	tape.isWebView2Installing = false;
	if (return_code == 0) { RunAsync([this] {InitializeWebView();}); }
	else if (return_code == 1) { echo(I18N.WebView2_Installation_failed); }
	else if (return_code == 2) { echo(I18N.WebView2_downloading_failed); }
}

//////////////////////////////////////////////////////////////////////

ExplorerDlg::ExplorerDlg(const std::wstring& startpage, bool isHome, double zoom, RECT windowRect) :
	m_initialUri(startpage), m_isHome(isHome), m_zoomFactor(zoom), m_items{ ToolBar_Count }
{
	m_ToDoOnDeferred = nullptr;
	HRESULT hr = OleInitialize(NULL);
	if (FAILED(hr))
		return;

	++s_appInstances;

	if (m_isHome)
	{
		m_hWnd = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_EXPLORER), tape.Ds2hWnd, (DLGPROC)Proc, (LPARAM)this);
	}
	else
	{
		m_hWnd = CreateWindowExW(
			WS_EX_CONTROLPARENT, tape.szWindowClass, tape.szTitle, WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
			windowRect.left, windowRect.top + 17, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - 17, nullptr, nullptr, tape.Ds2hInst, nullptr);
		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)&Proc);
		SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
		m_isCurrentlyTopMost = true;
	}
	{
		m_ScrollbarFramehWnd = CreateWindowEx(0, L"Static", L"", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_CENTER, 0, 0, 17, 17, m_hWnd, nullptr, tape.Ds2hInst, nullptr);
		ShowWindow(m_ScrollbarFramehWnd, SW_HIDE);
	}
/*
	{
		m_appBackgroundImageHandle = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDI_WEBVIEW2_BACKGROUND), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
		GetObject(m_appBackgroundImageHandle, sizeof(m_appBackgroundImage), &m_appBackgroundImage);
		m_memHdc = CreateCompatibleDC(GetDC(m_hWnd));
		SelectObject(m_memHdc, m_appBackgroundImageHandle);
	}
*//*
	{
		HDC memoryDC = CreateCompatibleDC(NULL);
		m_Preview = CreateCompatibleBitmap(memoryDC, 192, 108);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memoryDC, m_Preview);
		HFONT hFont = CreateFont(22, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
		SelectObject(memoryDC, hFont);
		std::wstring text = L"preview\nnot\nrefreshed";
		RECT rect = { 0,19,192,88 };
		SetTextColor(memoryDC, tape.Tx_STATIC);
		SetBkMode(memoryDC, TRANSPARENT);
		SetBkColor(memoryDC, tape.Bk_STATIC);
		DrawText(memoryDC, text.c_str(), text.size(), &rect, DT_CENTER | DT_WORDBREAK);
		BITMAPINFO Bitmapinfo = { 0 };
		Bitmapinfo.bmiHeader.biSize = sizeof(Bitmapinfo.bmiHeader);
		GetDIBits(memoryDC, m_Preview, 0, 0, NULL, &Bitmapinfo, DIB_RGB_COLORS);
		DeleteObject(hFont);
		DeleteDC(memoryDC);
	}
*/
	{
		hMenuWeb = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_WEB));
		MENUINFO mnuInfo = { 0 };
		mnuInfo.cbSize = sizeof(mnuInfo);
		mnuInfo.fMask = MIM_BACKGROUND; //| MIM_APPLYTOSUBMENUS
		mnuInfo.hbrBack = CreateSolidBrush(RGB(0, 0, 0));
		SetMenuInfo(hMenuWeb, &mnuInfo);

		m_TabsID[0]  = IDM_MENU_WEB_PDF_PORTRAIT;
		m_TabsID[1]  = IDM_MENU_WEB_PDF_LANDSCAPE;
		m_TabsID[2]  = IDM_MENU_WEB_SCREENSHOT;
		m_TabsID[3]  = IDM_MENU_SEPARATOR1;
		m_TabsID[4]  = IDM_MENU_WEB_TOPMOST;
		m_TabsID[5]  = IDM_MENU_WEB_VISIBILITY;
		m_TabsID[6]  = IDM_MENU_WEB_DARK_MODE;
		m_TabsID[7]  = IDM_MENU_WEB_DARK_MODE_2;
		m_TabsID[8]  = IDM_MENU_WEB_BOUNDS_MODE;
		m_TabsID[9]  = IDM_MENU_WEB_BLOCK_IMAGES;
		m_TabsID[10] = IDM_MENU_SEPARATOR2;
		m_TabsID[11] = IDM_MENU_WEB_CLOSE_WEBVIEW;
		m_TabsID[12] = IDM_MENU_WEB_REINIT;
		m_TabsID[13] = IDM_MENU_WEB_NEW_WINDOW;
		m_TabsID[14] = IDM_MENU_WEB_NEW_THREAD;
		m_TabsID[15] = IDM_MENU_WEB_CLEAR_CACHE;
		m_TabsID[16] = IDM_MENU_WEB_CLEAR_COOKIES;
		m_TabsID[17] = IDM_MENU_WEB_DELETE_DATAFOLDER;
		m_TabsID[18] = IDM_MENU_SEPARATOR3;
		m_TabsID[19] = IDM_MENU_WEB_INJECT_SCRIPT;
		m_TabsID[20] = IDM_MENU_WEB_INITIALIZE_SCRIPT;
		m_TabsID[21] = IDM_MENU_WEB_USE_DEFERRED_SCRIPT;
		m_TabsID[22] = IDM_MENU_WEB_COMPLETE_DEFERRED;
		m_TabsID[23] = IDM_MENU_WEB_POST_MESSAGE_STRING;
		m_TabsID[24] = IDM_MENU_WEB_POST_MESSAGE_JSON;
		m_TabsID[25] = IDM_MENU_WEB_SUBSCRIBE_CDP_EVENT;
		m_TabsID[26] = IDM_MENU_WEB_CALL_CDP_METHOD;
		m_TabsID[27] = IDM_MENU_WEB_COM_OBJECT;
		m_TabsID[28] = IDM_MENU_SEPARATOR4;
		m_TabsID[29] = IDM_MENU_WEB_FLAGS;
		m_TabsID[30] = IDM_MENU_WEB_LANGUAGE;
		m_TabsID[31] = IDM_MENU_WEB_USERAGENT;
		m_TabsID[32] = IDM_MENU_WEB_BLACKLIST;
		m_TabsID[33] = IDM_MENU_WEB_TASK_MANAGER;
//		m_TabsID[34] = IDM_MENU_SEPARATOR5;
//		m_TabsID[35] = IDM_MENU_WEB_EXIT;
		redrawMenu(34);

//		if (!m_isHome)
//			SetMenu(m_hWnd, hMenuWeb);
	}

	{
		hMenuFav = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_FAVORITES));
		MENUINFO mnuInfo = { 0 };
		mnuInfo.cbSize = sizeof(mnuInfo);
		mnuInfo.fMask = MIM_BACKGROUND; //| MIM_APPLYTOSUBMENUS
		mnuInfo.hbrBack = CreateSolidBrush(RGB(0, 0, 0));
		SetMenuInfo(hMenuFav, &mnuInfo);

		m_TabsID[0] = IDM_MENU_WEB_FAV_0;
		m_TabsID[1] = IDM_MENU_WEB_FAV_1;
		m_TabsID[2] = IDM_MENU_WEB_FAV_2;
		m_TabsID[3] = IDM_MENU_WEB_FAV_3;
		m_TabsID[4] = IDM_MENU_WEB_FAV_4;
		m_TabsID[5] = IDM_MENU_WEB_FAV_5;
		m_TabsID[6] = IDM_MENU_WEB_FAV_6;
		m_TabsID[7] = IDM_MENU_WEB_FAV_7;
		m_TabsID[8] = IDM_MENU_WEB_FAV_8;
		m_TabsID[9] = IDM_MENU_WEB_FAV_9;
		redrawMenu(10, true);
	}

	{
		m_items[ToolBar_Favorites] = CreateWindow(L"button", L"☆", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_FAVORITES, nullptr, 0);
		m_items[ToolBar_Home] = CreateWindow(L"button", L"⌂", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_HOME, nullptr, 0);
		m_items[ToolBar_Back] = CreateWindow(L"button", L"‹", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_BACK, nullptr, 0);
		m_items[ToolBar_Forward] = CreateWindow(L"button", L"›", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_FORWARD, nullptr, 0);
		m_items[ToolBar_Refresh] = CreateWindow(L"button", L"⭯", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_REFRESH, nullptr, 0);
		m_items[ToolBar_AddressBar] = CreateWindow(L"edit", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_WANTRETURN | ES_MULTILINE | ES_AUTOHSCROLL, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_EDIT_URL, nullptr, 0);
		m_items[ToolBar_Go] = CreateWindow(L"button", L"⮞", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_GO, nullptr, 0);
		m_items[ToolBar_Cancel] = CreateWindow(L"button", L"⧗", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_CANCEL, nullptr, 0);
		m_items[ToolBar_AutoRefresh] = CreateWindow(L"button", L"◻", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER | BS_AUTOCHECKBOX | BS_PUSHLIKE, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_AUTOREFRESH, nullptr, 0);
		m_items[ToolBar_ZoomMinus] = CreateWindow(L"button", L"⁻", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_TOP | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_ZOOM_MINUS, nullptr, 0);
		m_items[ToolBar_ZoomPlus] = CreateWindow(L"button", L"+", WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER | BS_CENTER, 0, 0, 0, 0, m_hWnd, (HMENU)IDC_WEB_ZOOM_PLUS, nullptr, 0);

		{
			CreateToolTip(m_hWnd, m_items[ToolBar_Favorites], I18N.HELP_WEB_FAVORITES);
			CreateToolTip(m_hWnd, m_items[ToolBar_Home], I18N.HELP_WEB_HOME);
			CreateToolTip(m_hWnd, m_items[ToolBar_Back], I18N.HELP_WEB_BACK);
			CreateToolTip(m_hWnd, m_items[ToolBar_Forward], I18N.HELP_WEB_FORWARD);
			CreateToolTip(m_hWnd, m_items[ToolBar_Refresh], I18N.HELP_WEB_REFRESH);
			CreateToolTip(m_hWnd, m_items[ToolBar_Go], I18N.HELP_WEB_GO);
			CreateToolTip(m_hWnd, m_items[ToolBar_Cancel], I18N.HELP_WEB_STOP);
			CreateToolTip(m_hWnd, m_items[ToolBar_AutoRefresh], I18N.HELP_WEB_AUTOREFRESH);
			CreateToolTip(m_hWnd, m_items[ToolBar_ZoomMinus], I18N.HELP_WEB_ZOOM_MINUS);
			CreateToolTip(m_hWnd, m_items[ToolBar_ZoomPlus], I18N.HELP_WEB_ZOOM_PLUS);
		}

		{
			HFONT hFont = CreateFont(19, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			for (ToolBar item = ToolBar_Favorites; item < ToolBar_Count; item = ToolBar(item + 1))
				SendMessage(m_items[item], WM_SETFONT, WPARAM(hFont), TRUE);
		}

		{
			HFONT hFont = CreateFont(18, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendMessage(m_items[ToolBar_Home], WM_SETFONT, WPARAM(hFont), TRUE);
		}

		{
			LOGFONT logFont;
			ZeroMemory(&logFont, sizeof(LOGFONT));
			HFONT hFont = (HFONT)SendMessage(m_items[ToolBar_AddressBar], WM_GETFONT, NULL, NULL);
			GetObject(hFont, sizeof(LOGFONT), &logFont);
			logFont.lfHeight = 14;
			logFont.lfWidth = 4;
			m_Toolbarfont = CreateFontIndirect(&logFont);
			SendMessage(m_items[ToolBar_AddressBar], WM_SETFONT, (WPARAM)m_Toolbarfont, FALSE);
		}

		for (HWND hwnd : m_items)
			EnableWindow(hwnd, FALSE);
		::SetFocus(NULL);

		HideToolBar();
	}

	if (!m_isHome)
		SetTimer(m_hWnd, 2, 300, nullptr);	//Change window form when mouseover

	if (!m_isHome || (m_isHome && web_tabs.size()))
		ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// If WebView2 Runtime installed initialize webview otherwise create new thread to download & install
	wil::unique_cotaskmem_string version_info;
	hr = GetAvailableCoreWebView2BrowserVersionString(nullptr, &version_info);
	if (hr == S_OK && version_info != nullptr)
		RunAsync([this] {InitializeWebView();});
	else if (m_isHome && !tape.isWebView2Installing)
	{
		RECT win;
		GetWindowRect(tape.Ds2hWnd, &win);
		if (MessageBoxPos(tape.Ds2hWnd, I18N.WebView2_Not_Installed_text, I18N.WebView2_Not_Installed_tittle, MB_YESNO, win.left + 160, win.top + 60) == IDYES)
		{
			tape.isWebView2Installing = true;
			CreateThread(0, 0, DownloadAndInstallWV2RT, (void*)this, 0, 0);
		}
		else
		{
			PostMessage(tape.Ds2hWnd, WM_COMMAND, ID_WEBCLOSE, 0);
			PostMessage(tape.Ds2hWnd, WM_CLOSE_ALL_TABS, 0, 0);
		}
	}
}

ExplorerDlg::~ExplorerDlg()
{
	KillTimer(m_hWnd, 1);
	KillTimer(m_hWnd, 2);

	CloseWebView();

	if (m_downloadsButton)
		DestroyWindow(m_downloadsButton);

	SetWindowText(m_items[ToolBar_AddressBar], L"");
	for (HWND hwnd : m_items)
		EnableWindow(hwnd, FALSE);
	::SetFocus(NULL);
	if (m_Toolbarfont)
		DeleteObject(m_Toolbarfont);

	//DeleteObject(m_appBackgroundImageHandle);
	//DeleteDC(m_memHdc);

	if (m_isHome)
		DestroyWindow(m_hWnd);
}

void ExplorerDlg::redrawMenu(int ntabs, bool isfavoritesmenu)
{
	MENUITEMINFO info;
	if (isfavoritesmenu)
		for (int i = 0; i < ntabs; i++)
		{
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING;
			GetMenuItemInfo(hMenuFav, m_TabsID[i], FALSE, &info);
			info.fType = MFT_OWNERDRAW;
			info.fState = MFS_UNCHECKED;
			switch (i)
			{
			case 0: info.dwTypeData = I18N.MENU_WEB_FAV_0; break;
			case 1: info.dwTypeData = I18N.MENU_WEB_FAV_1; break;
			case 2: info.dwTypeData = I18N.MENU_WEB_FAV_2; break;
			case 3: info.dwTypeData = I18N.MENU_WEB_FAV_3; break;
			case 4: info.dwTypeData = I18N.MENU_WEB_FAV_4; break;
			case 5: info.dwTypeData = I18N.MENU_WEB_FAV_5; break;
			case 6: info.dwTypeData = I18N.MENU_WEB_FAV_6; break;
			case 7: info.dwTypeData = I18N.MENU_WEB_FAV_7; break;
			case 8: info.dwTypeData = I18N.MENU_WEB_FAV_8; break;
			case 9: info.dwTypeData = I18N.MENU_WEB_FAV_9; break;
			}
			SetMenuItemInfo(hMenuFav, m_TabsID[i], FALSE, &info);
		}
	else
		for (int i = 0; i < ntabs; i++)
		{
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING;
			GetMenuItemInfo(hMenuWeb, m_TabsID[i], FALSE, &info);
			if (m_TabsID[i] == IDM_MENU_SEPARATOR1 ||
				m_TabsID[i] == IDM_MENU_SEPARATOR2 ||
				m_TabsID[i] == IDM_MENU_SEPARATOR3 ||
				m_TabsID[i] == IDM_MENU_SEPARATOR4 ||
				m_TabsID[i] == IDM_MENU_SEPARATOR5)
				info.fType = MFT_OWNERDRAW | MF_SEPARATOR;
			else
				info.fType = MFT_RADIOCHECK | MFT_OWNERDRAW;
			info.fState = MFS_UNCHECKED;
			switch (i)
			{
			case 0: info.dwTypeData = I18N.MENU_WEB_PDF_PORTRAIT; break;
			case 1: info.dwTypeData = I18N.MENU_WEB_PDF_LANDSCAPE; break;
			case 2: info.dwTypeData = I18N.MENU_WEB_SCREENSHOT; break;
			case 3: info.dwTypeData = I18N.MENU_SEPARATORN; break;
			case 4: info.dwTypeData = I18N.MENU_WEB_TOPMOST; break;
			case 5: info.dwTypeData = I18N.MENU_WEB_VISIBILITY; break;
			case 6: info.dwTypeData = I18N.MENU_WEB_DARK_MODE; break;
			case 7: info.dwTypeData = I18N.MENU_WEB_DARK_MODE_2; break;
			case 8: info.dwTypeData = I18N.MENU_WEB_BOUNDS_MODE; break;
			case 9: info.dwTypeData = I18N.MENU_WEB_BLOCK_IMAGES; break;
			case 10: info.dwTypeData = I18N.MENU_SEPARATORN; break;
			case 11: info.dwTypeData = I18N.MENU_WEB_CLOSE_WEBVIEW; break;
			case 12: info.dwTypeData = I18N.MENU_WEB_REINIT; break;
			case 13: info.dwTypeData = I18N.MENU_WEB_NEW_WINDOW; break;
			case 14: info.dwTypeData = I18N.MENU_WEB_NEW_THREAD; break;
			case 15: info.dwTypeData = I18N.MENU_WEB_CLEAR_CACHE; break;
			case 16: info.dwTypeData = I18N.MENU_WEB_CLEAR_COOKIES; break;
			case 17: info.dwTypeData = I18N.MENU_WEB_DELETE_DATAFOLDER; break;
			case 18: info.dwTypeData = I18N.MENU_SEPARATORN; break;
			case 19: info.dwTypeData = I18N.MENU_WEB_INJECT_SCRIPT; break;
			case 20: info.dwTypeData = I18N.MENU_WEB_INITIALIZE_SCRIPT; break;
			case 21: info.dwTypeData = I18N.MENU_WEB_USE_DEFERRED_SCRIPT; break;
			case 22: info.dwTypeData = I18N.MENU_WEB_COMPLETE_DEFERRED; break;
			case 23: info.dwTypeData = I18N.MENU_WEB_POST_MESSAGE_STRING; break;
			case 24: info.dwTypeData = I18N.MENU_WEB_POST_MESSAGE_JSON; break;
			case 25: info.dwTypeData = I18N.MENU_WEB_SUBSCRIBE_CDP_EVENT; break;
			case 26: info.dwTypeData = I18N.MENU_WEB_CALL_CDP_METHOD; break;
			case 27: info.dwTypeData = I18N.MENU_WEB_COM_OBJECT; break;
			case 28: info.dwTypeData = I18N.MENU_SEPARATORN; break;
			case 29: info.dwTypeData = I18N.MENU_WEB_FLAGS; break;
			case 30: info.dwTypeData = I18N.MENU_WEB_LANGUAGE; break;
			case 31: info.dwTypeData = I18N.MENU_WEB_USERAGENT; break;
			case 32: info.dwTypeData = I18N.MENU_WEB_BLACKLIST; break;
			case 33: info.dwTypeData = I18N.MENU_WEB_TASK_MANAGER; break;
			//case 34: info.dwTypeData = I18N.MENU_SEPARATORN; break;
			//case 35: info.dwTypeData = I18N.EXIT; break;
			}
			SetMenuItemInfo(hMenuWeb, m_TabsID[i], FALSE, &info);
		}
}

//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ExplorerDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ExplorerDlg* dlg;
	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<ExplorerDlg*>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
	}
	else
		dlg = (ExplorerDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, message, wParam, lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ExplorerDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TIMER:
	{
		if (IsIconic(hWnd) || !IsWindowVisible(m_hWnd))
			break;

		switch (wParam)
		{
		case 1:
		{
			m_webView2->Reload();
			break;
		}
		case 2:
		{
			if (IsWindowVisible(m_hWnd) && !isFullScreen)
			{
				if (GetCursorPos(&tape.mousepoint))
				{
					RECT win;
					GetWindowRect(hWnd, &win);
					if (m_mouseIsOver)
					{
						if (!PtInRect(&win, tape.mousepoint))
						{
							m_mouseIsOver = false;
							OnMouseOut();
						}
					}
					else
					{
						if (PtInRect(&win, tape.mousepoint))
						{
							m_mouseIsOver = true;
							OnMouseOver();
						}
					}
				}
			}
			break;
		}
		case 3:
		{
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				m_rightClickFav = true;
				ShowMenuFavorites();
			}
			break;
		}
		case 4:
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				ZoomMinus(3);
			else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
				ZoomReset();
			break;
		}
		case 5:
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				ZoomPlus(3);
			else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
				ZoomSet();
			break;
		}
		case 6:
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
				ExitFullScreen();
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				GetCursorPos(&tape.mousepoint);
				if (tape.mousepoint.y == 0)
					SetZoomFactor(0.25 + (4.75 * (tape.mousepoint.x * tape.mousepoint.x) / (tape.W * tape.W)));
				else if (tape.mousepoint.x == 0 && tape.mousepoint.y == tape.H)
					ExitFullScreen();
			}
			break;
		}
		}
	}
	break;
	case WM_SIZE:
	{
		if (ViewComponentAvailable)
		{
			if (wParam == SIZE_MINIMIZED)
			{
				m_controller->put_IsVisible(FALSE);
				Suspend();
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (m_isVisible)
				{
					Resume();
					m_controller->put_IsVisible(TRUE);
				}
			}
		}
		if (lParam != 0)
			ResizeEverything();
		break;
	}
	case WM_DPICHANGED:
	{
		if (!m_isHome || IsWindowVisible(m_hWnd))
		{
			RECT* const newWindowSize = reinterpret_cast<RECT*>(lParam);
			SetWindowPos(hWnd, nullptr, newWindowSize->left, newWindowSize->top, newWindowSize->right - newWindowSize->left, newWindowSize->bottom - newWindowSize->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}
	break;
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;
		if (DrawMenuSize->CtlType == ODT_MENU)
		{
			DrawMenuSize->itemHeight = 14;
			switch (DrawMenuSize->itemID)
			{
			case IDM_MENU_WEB_FAV_0:
			case IDM_MENU_WEB_FAV_1:
			case IDM_MENU_WEB_FAV_2:
			case IDM_MENU_WEB_FAV_3:
			case IDM_MENU_WEB_FAV_4:
			case IDM_MENU_WEB_FAV_5:
			case IDM_MENU_WEB_FAV_6:
			case IDM_MENU_WEB_FAV_7:
			case IDM_MENU_WEB_FAV_8:
			case IDM_MENU_WEB_FAV_9:
			{
				DrawMenuSize->itemWidth = 75;
				break;
			}
			default:
			{
				DrawMenuSize->itemWidth = 106;
				break;
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
			BOOL selected = DrawMenuStructure->itemState & ODS_SELECTED;

			int itemnumber = -1;
			switch (DrawMenuStructure->itemID)
			{
			case IDM_MENU_SEPARATOR1: { itemnumber = 0; break; }
			case IDM_MENU_SEPARATOR2: { itemnumber = 0; break; }
			case IDM_MENU_SEPARATOR3: { itemnumber = 0; break; }
			case IDM_MENU_SEPARATOR4: { itemnumber = 0; break; }
			case IDM_MENU_SEPARATOR5: { itemnumber = 0; break; }
			case IDM_MENU_WEB_PDF_PORTRAIT: { if (m_printToPdfInProgress) { itemnumber = 3; } break; }
			case IDM_MENU_WEB_PDF_LANDSCAPE: { if (m_printToPdfInProgress) { itemnumber = 3; } break; }
			case IDM_MENU_WEB_VISIBILITY: { if (!m_isVisible) { itemnumber = 1; } break; }
			case IDM_MENU_WEB_BOUNDS_MODE: { if (tape.RawBounds) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_DARK_MODE: { if (tape.DarkMode == 1) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_DARK_MODE_2: { if (tape.DarkMode == 2) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_BLOCK_IMAGES: { if (m_blockImages) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_TOPMOST:
			{
				if (m_isHome)
				{
					if ((GetWindowLong(tape.Ds2hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0) { itemnumber = 2; }
				}
				else
				{
					if ((GetWindowLong(m_hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0) { itemnumber = 2; }
				}
				break;
			}
			case IDM_MENU_WEB_INITIALIZE_SCRIPT: { if (tape.WebScript.size()) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_USE_DEFERRED_SCRIPT: { if (m_deferredScripts) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_LANGUAGE: { if (tape.WebLanguage.size()) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_USERAGENT: { if (tape.UserAgent.size()) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_BLACKLIST: { if (tape.BlockedSites.size()) { itemnumber = 2; } break; }
			case IDM_MENU_WEB_EXIT: { itemnumber = 3; break; }
			case IDM_MENU_WEB_FAV_0: { itemnumber = 4; break; }
			}

			if (selected)
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_HIGHLIGHT);
			else if (itemnumber == 1)
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_Running);
			else if (itemnumber == 2)
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_Paused);
			else if (itemnumber == 3)
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_Stopped);
			else if (itemnumber == 4)
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_green);
			else
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_CLONE);

			SelectObject(DrawMenuStructure->hDC, tape.hMenus);
			WCHAR wszBuffer[MAX_PATH];
			int nCharCount = ::GetMenuString((HMENU)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				COLORREF crCurrText = 0;
				crCurrText = (selected) ? ((DrawMenuStructure->itemID == IDM_MENU_DEL) ? tape.ink_MENU_Delete : tape.ink_MENU_HIGHLIGHT) : tape.ink_MENU;
				SetTextColor(DrawMenuStructure->hDC, crCurrText);

				int nCharacters;
				for (nCharacters = 0;
					nCharacters < nCharCount; nCharacters++)
					if (wszBuffer[nCharacters] == L'\t' || wszBuffer[nCharacters] == L'\b')
						break;

				SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				DrawMenuStructure->rcItem.left += 5;
				DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &(DrawMenuStructure->rcItem), DT_VCENTER | DT_SINGLELINE);
			}
		}
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		return (LRESULT)tape.hB_WEB_BackGround;	//Hide scrollbar when recharging page or new page
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_black);

			// hDC = GetDC(hWnd);
			// StretchBlt(hDC, m_webView2bounds.left, m_webView2bounds.top, m_webView2bounds.right, m_webView2bounds.bottom,
			// m_memHdc, 0, 0, m_appBackgroundImage.bmWidth, m_appBackgroundImage.bmHeight, SRCCOPY);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		break;
	}
	case WM_APP:
	{
		auto* task = reinterpret_cast<std::function<void()>*>(wParam);
		(*task)();
		delete task;
		break;
	}
	case WM_CLOSE:
	{
		CloseExplorerDlg();
		break;
	}
	case WM_NCDESTROY:
	{
		if (--s_appInstances == 0)
			PostQuitMessage(0);
		break;
	}
	case WM_QUERYENDSESSION:
	{
		RegisterApplicationRestart(L"--restore", RESTART_NO_CRASH | RESTART_NO_HANG);
		break;
	}
	case WM_ENDSESSION:
	{
		if (wParam == TRUE)
			PostQuitMessage(0);
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
			{
				switch (((LPNMHDR)lParam)->idFrom)
				{
				case IDC_WEB_FAVORITES: { SetTimer(m_hWnd, 3, 70, NULL); break; }
				case IDC_WEB_ZOOM_MINUS: { SetTimer(m_hWnd, 4, 70, NULL); break; }
				case IDC_WEB_ZOOM_PLUS: { SetTimer(m_hWnd, 5, 70, NULL); break; }
				default: { return FALSE; }
				}
				break;
			}
			case (HICF_LEAVING | HICF_MOUSE):
			{
				::SetFocus(NULL);
				switch (((LPNMHDR)lParam)->idFrom)
				{
				case IDC_WEB_FAVORITES: { KillTimer(m_hWnd, 3); break; }
				case IDC_WEB_ZOOM_MINUS: { KillTimer(m_hWnd, 4); break; }
				case IDC_WEB_ZOOM_PLUS: { KillTimer(m_hWnd, 5); break; }
				default: { return FALSE; }
				}
				break;
			}
			default: { return FALSE; }
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
		case IDC_WEB_FAVORITES:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				m_rightClickFav = false;
				ShowMenuFavorites();
			}
			break;
		}
		case IDC_WEB_HOME:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				if (!ViewComponentAvailable)
				{
					m_initialUri = initialUri;
					InitializeWebView();
				}
				else
					m_webView2->Navigate(initialUri.c_str());
			}
			break;
		}
		case IDC_WEB_EDIT_URL:
		{
			if (HIWORD(wParam) == EN_MAXTEXT)
			{
				if (!ViewComponentAvailable)
				{
					m_initialUri = L"about:bar";
					InitializeWebView();
				}
				else
					NavigateToAddressBar();
			}
			break;
		}
		case IDC_WEB_GO:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				if (!ViewComponentAvailable)
				{
					m_initialUri = L"about:bar";
					InitializeWebView();
				}
				else
					NavigateToAddressBar();
			}
			break;
		}
		case IDM_MENU_WEB_TOPMOST:
		{
			ToggleTopMost();
			break;
		}
		case IDM_MENU_WEB_DARK_MODE:
		{
			if (tape.DarkMode == 1)
			{
				tape.DarkMode = 0;
				SetBackgroundColor(RGB(255, 255, 255), false);
			}
			else
			{
				tape.DarkMode = 1;
				SetBackgroundColor(RGB(16, 18, 19), false);
			}
			if (ViewComponentAvailable)
				NavigateToAddressBar();
			else
				m_controller2->put_DefaultBackgroundColor(transparentColor);
			break;
		}
		case IDM_MENU_WEB_DARK_MODE_2:
		{
			if (tape.DarkMode == 2)
			{
				tape.DarkMode = 0;
				SetBackgroundColor(RGB(255, 255, 255), false);
			}
			else
			{
				tape.DarkMode = 2;
				SetBackgroundColor(RGB(16, 18, 19), false);
			}
			if (ViewComponentAvailable)
				NavigateToAddressBar();
			else
				m_controller2->put_DefaultBackgroundColor(transparentColor);
			break;
		}
		case IDM_MENU_WEB_REINIT:
		{
			ViewComponentAvailable = false;
			InitializeWebView();
			break;
		}
		case IDM_MENU_WEB_NEW_WINDOW:
		{
			RECT win;
			if (m_isHome)
				GetWindowRect(tape.Ds2hWnd, &win);
			else
				GetWindowRect(m_hWnd, &win);
			new ExplorerDlg(L"", false, m_zoomFactor, win);
			break;
		}
		case IDM_MENU_WEB_NEW_THREAD:
			CreateNewThread(this);
			break;
		case IDM_MENU_WEB_LANGUAGE:
		{
			TextInputDialog(
				m_hWnd,
				I18N.WEB_LANGUAGE_1,
				I18N.WEB_LANGUAGE_2,
				I18N.WEB_LANGUAGE_3,
				tape.WebLanguage.empty() ? L"zh-cn" : tape.WebLanguage.c_str());
			if (TextInput_confirmed)
			{
				tape.WebLanguage = TextInput_input;
				ViewComponentAvailable = false;
				InitializeWebView();
			}
			break;
		}
		case IDM_MENU_WEB_FAV_0:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(0);
			else
				NavigateToFavorite(0);
			break;
		}
		case IDM_MENU_WEB_FAV_1:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(1);
			else
				NavigateToFavorite(1);
			break;
		}
		case IDM_MENU_WEB_FAV_2:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(2);
			else
				NavigateToFavorite(2);
			break;
		}
		case IDM_MENU_WEB_FAV_3:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(3);
			else
				NavigateToFavorite(3);
			break;
		}
		case IDM_MENU_WEB_FAV_4:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(4);
			else
				NavigateToFavorite(4);
			break;
		}
		case IDM_MENU_WEB_FAV_5:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(5);
			else
				NavigateToFavorite(5);
			break;
		}
		case IDM_MENU_WEB_FAV_6:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(6);
			else
				NavigateToFavorite(6);
			break;
		}
		case IDM_MENU_WEB_FAV_7:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(7);
			else
				NavigateToFavorite(7);
			break;
		}
		case IDM_MENU_WEB_FAV_8:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(8);
			else
				NavigateToFavorite(8);
			break;
		}
		case IDM_MENU_WEB_FAV_9:
		{
			::SetFocus(NULL);
			if (m_rightClickFav)
				SetFavorite(9);
			else
				NavigateToFavorite(9);
			break;
		}
		case IDC_WEB_BACK:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				Back();
			}
			break;
		}
		case IDC_WEB_FORWARD:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				Forward();
			}
			break;
		}
		case IDC_WEB_REFRESH:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				Refresh();
			}
			break;
		}
		case IDC_WEB_CANCEL:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				Cancel();
			}
			break;
		}
		case IDC_WEB_AUTOREFRESH:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				AutoRefresh();
			}
			break;
		}
		case IDC_WEB_ZOOM_MINUS:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
			}
			break;
		}
		case IDC_WEB_ZOOM_PLUS:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
			}
			break;
		}
		case IDC_WEB_ZOOM_RESET:
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				::SetFocus(NULL);
				ZoomReset();
			}
			break;
		}
		case IDM_MENU_WEB_VISIBILITY:
		{
			ToggleVisibility();
			break;
		}
		case IDM_MENU_WEB_EXIT:
		{
			CloseExplorerDlg();
			break;
		}
		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_MAXIMIZE:
			{
				if (!m_isHome)
					EnterFullScreen();
				break;
			}
			}
			break;
		}
		}

		if (!m_webView2)
			return 0;

		switch (LOWORD(wParam))
		{
		case IDM_MENU_WEB_PDF_LANDSCAPE:
		{
			if (m_printToPdfInProgress)
			{
				GetWindowRect(m_hWnd, &m_explorer_win);
				MessageBoxPos(m_hWnd, I18N.WebView2_PDF_Progress, I18N.WebView2_PDF_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
			}
			else
				PrintToPdf(true);
			break;
		}
		case IDM_MENU_WEB_PDF_PORTRAIT:
		{
			if (m_printToPdfInProgress)
			{
				GetWindowRect(m_hWnd, &m_explorer_win);
				MessageBoxPos(m_hWnd, I18N.WebView2_PDF_Progress, I18N.WebView2_PDF_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
			}
			else
				PrintToPdf();
			break;
		}
		case IDM_MENU_WEB_SCREENSHOT:
		{
			SaveScreenshot();
			break;
		}
		case IDM_MENU_WEB_BOUNDS_MODE:
		{
			tape.RawBounds = !tape.RawBounds;
			SetBoundsMode();
			break;
		}
		case IDM_MENU_WEB_BLOCK_IMAGES:
		{
			m_blockImages = !m_blockImages;
			SetBlockImages();
			break;
		}
		case IDM_MENU_WEB_CLOSE_WEBVIEW:
		{
			for (HWND hwnd : m_items)
				EnableWindow(hwnd, FALSE);
			EnableWindow(m_items[ToolBar_Favorites], true);
			EnableWindow(m_items[ToolBar_Home], true);
			EnableWindow(m_items[ToolBar_AddressBar], true);
			EnableWindow(m_items[ToolBar_Go], true);
			::SetFocus(NULL);
			CloseWebView();
			break;
		}
		case IDM_MENU_WEB_CLEAR_CACHE:
		{
			::SetFocus(NULL);
			ClearCache();
			break;
		}
		case IDM_MENU_WEB_CLEAR_COOKIES:
		{
			::SetFocus(NULL);
			ClearCookies();
			break;
		}
		case IDM_MENU_WEB_DELETE_DATAFOLDER:
		{
			::SetFocus(NULL);
			CleanupUserDataFolder(true);
			break;
		}
		case IDM_MENU_WEB_INJECT_SCRIPT:
		{
			TextInputDialog(
				m_hWnd,
				I18N.WEB_INJECT_SCRIPT_1,
				I18N.WEB_INJECT_SCRIPT_2,
				I18N.WEB_INJECT_SCRIPT_3,
				L"window.getComputedStyle(document.body).backgroundColor");
			if (TextInput_confirmed)
			{
				GetWindowRect(m_hWnd, &m_explorer_win);
				m_webView2->ExecuteScript(TextInput_input.c_str(),
					Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
						[](HRESULT error, PCWSTR result) -> HRESULT
						{
							if (error != S_OK)
								MessageBoxPos(nullptr, I18N.WebView2_Inject_Script_Failed, I18N.WebView2_Inject_Script_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
							else
								MessageBoxPos(nullptr, result, I18N.WebView2_Inject_Script_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
							return S_OK;}).Get());
			}
			break;
		}
		case IDM_MENU_WEB_INITIALIZE_SCRIPT:
		{
			TextInputDialog(
				m_hWnd,
				I18N.WEB_INITIALIZE_SCRIPT_1,
				I18N.WEB_INITIALIZE_SCRIPT_2,
				I18N.WEB_INITIALIZE_SCRIPT_3,
				// This example script stops child frames from opening new windows.  Because
				// the initialization script runs before any script in the HTML document, we
				// can trust the results of our checks on window.parent and window.top.
				(tape.WebScript.empty()) ? (
					L"if (window.parent !== window.top) {\r\n"
					L"    delete window.open;\r\n}") : (tape.WebScript));
			if (TextInput_confirmed)
			{
				if (tape.WebScript.size())
					m_webView2->RemoveScriptToExecuteOnDocumentCreated(tape.WebScript.c_str());
				tape.WebScript = TextInput_input;
				SetInitializeScript();
			}
			break;
		}
		case IDM_MENU_WEB_USE_DEFERRED_SCRIPT:
		{
			m_deferredScripts = !m_deferredScripts;
			SetDeferred();
			break;
		}
		case IDM_MENU_WEB_COMPLETE_DEFERRED:
		{
			CompleteDeferred();
			break;
		}
		case IDM_MENU_WEB_POST_MESSAGE_STRING:
		{
			SendStringWebMessage();
			break;
		}
		case IDM_MENU_WEB_POST_MESSAGE_JSON:
		{
			SendJsonWebMessage();
			break;
		}
		case IDM_MENU_WEB_SUBSCRIBE_CDP_EVENT:
		{
			SubscribeToCdpEvent();
			break;
		}
		case IDM_MENU_WEB_CALL_CDP_METHOD:
		{
			CallCdpMethod();
			break;
		}
		case IDM_MENU_WEB_COM_OBJECT:
		{
			AddComObject();
			break;
		}
		case IDM_MENU_WEB_FLAGS:
		{
			m_webView2->Navigate(L"edge://flags/");
			break;
		}
		case IDM_MENU_WEB_USERAGENT:
		{
			if (m_settings2)
			{
				LPWSTR user_agent;
				m_settings2->get_UserAgent(&user_agent);
				TextInputDialog(
					m_hWnd,
					I18N.WEB_USERAGENT_1,
					I18N.WEB_USERAGENT_2,
					I18N.WEB_USERAGENT_3,
					(tape.UserAgent.empty()) ? user_agent : tape.UserAgent.c_str());
				if (TextInput_confirmed)
				{
					tape.UserAgent = TextInput_input;
					SetUserAgent();
				}
			}
			break;
		}
		case IDM_MENU_WEB_BLACKLIST:
		{
			LPWSTR emptyBlockedSites = WCHARI(L"foo.com;ftp.bar.org");
			TextInputDialog(
				m_hWnd,
				I18N.WEB_BLACKLIST_1,
				I18N.WEB_BLACKLIST_2,
				I18N.WEB_BLACKLIST_3,
				(tape.BlockedSites.empty()) ? emptyBlockedSites : tape.BlockedSites.c_str());
			if (TextInput_confirmed)
			{
				tape.BlockedSites = TextInput_input;
				SetBlackList();
			}
			break;
		}
		case IDM_MENU_WEB_TASK_MANAGER:
		{
			OpenTaskManagerWindow();
			break;
		}
		case IDM_MENU_WEB_OPEN_DEVTOOLS:
		{
			m_webView2->OpenDevToolsWindow();
			break;
		}
		}
	}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////

void ExplorerDlg::InitializeWebView()
{
	CloseWebView();
	LPCWSTR subFolder = nullptr;

	auto options = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();
	options->put_AllowSingleSignOnUsingOSPrimaryAccount(TRUE);

	if (!tape.WebLanguage.empty())
		options->put_Language(tape.WebLanguage.c_str());

	HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
		subFolder, m_userDataFolder.c_str(), options.Get(),
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			this, &ExplorerDlg::OnCreateEnvironmentCompleted).Get());
	if (!SUCCEEDED(hr))
	{
		PostMessage(tape.Ds2hWnd, WM_COMMAND, ID_WEBCLOSE, -1);
		GetWindowRect(m_hWnd, &m_explorer_win);
		switch (hr)
		{
		case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND): { MessageBoxPos(m_hWnd, I18N.WebView2_Runtime_Failed_Found, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21); break; }
		case HRESULT_FROM_WIN32(ERROR_FILE_EXISTS): { MessageBoxPos(m_hWnd, I18N.WebView2_Data_Folder_Failed_Overwrite, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21); break; }
		case E_ACCESSDENIED: { MessageBoxPos(m_hWnd, I18N.WebView2_Data_Folder_Failed_Access, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21); break; }
		case E_FAIL: { MessageBoxPos(m_hWnd, I18N.WebView2_Runtime_Failed_Start, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21); break; }
		default: { MessageBoxPos(m_hWnd, I18N.WebView2_Create_Environment_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21); break; }
		}
	}
}

HRESULT ExplorerDlg::OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment)
{
	if (FAILED(result))
	{
		GetWindowRect(m_hWnd, &m_explorer_win);
		MessageBoxPos(m_hWnd, I18N.WebView2_Create_Environment_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
		FAIL_FAST();
	}

	m_webViewEnvironment = environment;

	auto webViewEnvironment3 = m_webViewEnvironment.try_query<ICoreWebView2Environment3>();
	{
		m_webViewEnvironment->CreateCoreWebView2Controller(
			m_hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
				this, &ExplorerDlg::OnCreateCoreWebView2ControllerCompleted)
			.Get());
	}

	return S_OK;
}

HRESULT ExplorerDlg::OnCreateCoreWebView2ControllerCompleted(HRESULT result, ICoreWebView2Controller* controller)
{
	if (result == S_OK)
	{
		m_controller = controller;
		wil::com_ptr<ICoreWebView2> coreWebView2;
		m_controller->get_CoreWebView2(&coreWebView2);
		m_controller2 = m_controller.query<ICoreWebView2Controller2>();
		m_controller3 = m_controller.try_query<ICoreWebView2Controller3>();

		coreWebView2.query_to(&m_webView2);
		m_webView2->get_Settings(&m_settings);
		m_webView2_4 = m_webView2.try_query<ICoreWebView2_4>();
		m_webView2_5 = m_webView2.try_query<ICoreWebView2_5>();

		m_settings2 = m_settings.try_query<ICoreWebView2Settings2>();
		m_settings3 = m_settings.try_query<ICoreWebView2Settings3>();
		m_settings4 = m_settings.try_query<ICoreWebView2Settings4>();
		m_settings5 = m_settings.try_query<ICoreWebView2Settings5>();
		m_settings6 = m_settings.try_query<ICoreWebView2Settings6>();

		m_settings->put_IsScriptEnabled(TRUE);
		m_settings->put_IsWebMessageEnabled(TRUE);
		m_settings->put_IsStatusBarEnabled(FALSE);
		m_settings->put_AreDevToolsEnabled(TRUE);
		m_settings->put_IsBuiltInErrorPageEnabled(TRUE);
		m_settings->put_AreDefaultContextMenusEnabled(TRUE);
		m_settings->put_AreHostObjectsAllowed(TRUE);
		m_settings->put_IsZoomControlEnabled(TRUE);

		if (m_settings3)
			m_settings3->put_AreBrowserAcceleratorKeysEnabled(FALSE);
		if (m_settings4)
		{
			m_settings4->put_IsPasswordAutosaveEnabled(TRUE);
			m_settings4->put_IsGeneralAutofillEnabled(TRUE);
		}
		if (m_settings5)
			m_settings5->put_IsPinchZoomEnabled(TRUE);
		if (m_settings6)
			m_settings6->put_IsSwipeNavigationEnabled(TRUE);

		SetUserAgent();
		SetBlackList();
		SetBoundsMode();
		if (m_blockImages)
			SetBlockImages();
		SetInitializeScript();
		SetDeferred();
		SetZoomFactor(m_zoomFactor);

		// Setup host resource mapping for local files
		m_webView2_3 = coreWebView2.try_query<ICoreWebView2_3>();
		if (m_webView2_3)
			m_webView2_3->SetVirtualHostNameToFolderMapping(L"appassets.example", L"assets", COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND_DENY_CORS);

		// Register event handlers by component's type ordering, destruct them in reverse order in ~ExplorerDlg()
		RegisterEventHandlers();

		ViewComponentAvailable = true;
		if (m_isHome)
			tape.isExplorerLoaded = true;
		ResizeEverything();

		if (m_ToDoOnDeferred)
		{
			m_ToDoOnDeferred();
			m_ToDoOnDeferred = nullptr;
		}

		EnableWindow(m_items[ToolBar_Favorites], true);
		EnableWindow(m_items[ToolBar_Home], true);
		EnableWindow(m_items[ToolBar_AddressBar], true);
		EnableWindow(m_items[ToolBar_Go], true);
		EnableWindow(m_items[ToolBar_AutoRefresh], true);
		::SetFocus(NULL);
		ResizeWebView();

		if (m_initialUri == L"about:bar")
			NavigateToAddressBar();
		else
		{
			m_initialUri = m_initialUri.empty() ? initialUri : m_initialUri;
			m_webView2->Navigate(m_initialUri.c_str());
		}
	}
	else
	{
		GetWindowRect(m_hWnd, &m_explorer_win);
		MessageBoxPos(m_hWnd, I18N.WebView2_Create_Webview_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
	}
	return S_OK;
}

void ExplorerDlg::CloseExplorerDlg()
{
	if (!CloseWebView())
		return;
	DestroyWindow(m_hWnd);
}

bool ExplorerDlg::CloseWebView()
{
	ViewComponentAvailable = false;
	if (m_printToPdfInProgress)
	{
		GetWindowRect(m_hWnd, &m_explorer_win);
		int selection = MessageBoxPos(m_hWnd, I18N.WebView2_PDF_Closing, I18N.WebView2_PDF_Tittle, MB_YESNO, m_explorer_win.left + 1, m_explorer_win.top + 21);
		if (selection == IDNO)
			return false;
	}

	wil::com_ptr<ICoreWebView2Environment5> environment5;
	if (m_webViewEnvironment)
		environment5 = m_webViewEnvironment.try_query<ICoreWebView2Environment5>();

	for (auto& pair : m_devToolsProtocolToken)
	{
		wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> receiver;
		m_webView2->GetDevToolsProtocolEventReceiver(pair.first.c_str(), &receiver);
		receiver->remove_DevToolsProtocolEventReceived(pair.second);
	}

	//	if (m_webView2_5)
	//	m_webView2_5->remove_ClientCertificateRequested(m_ClientCertificateRequestedToken);

	if (m_webView2_4)
		m_webView2_4->remove_FrameCreated(m_frameCreatedToken);

	if (m_webView2)
	{
		m_webView2->remove_NavigationStarting(m_navigationStartingToken);
		m_webView2->remove_NavigationCompleted(m_navigationCompletedToken);
		m_webView2->remove_FrameNavigationCompleted(m_frameNavigationCompletedToken);
		m_webView2->remove_ProcessFailed(m_processFailedToken);
		m_webView2->remove_NewWindowRequested(m_newWindowRequestedToken);
		m_webView2->remove_WindowCloseRequested(m_windowCloseRequestedToken);
		m_webView2->remove_PermissionRequested(m_permissionRequestedToken);
		m_webView2->remove_ScriptDialogOpening(m_scriptDialogOpeningToken);
		m_webView2->remove_SourceChanged(m_sourceChangedToken);
		m_webView2->remove_HistoryChanged(m_historyChangedToken);
		m_webView2->remove_DocumentTitleChanged(m_documentTitleChangedToken);
		m_webView2->remove_ContainsFullScreenElementChanged(m_containsFullScreenElementChangedToken);
		m_webView2->remove_WebResourceRequested(m_ImageBlockingToken);
	}

	if (m_controller)
	{
		m_controller->Close();
		m_controller = nullptr;
		m_webView2 = nullptr;
		m_webView2_3 = nullptr;
	}

	m_webViewEnvironment = nullptr;
	m_profileDirName = L"";
	m_documentTitle = L"";
	return true;
}

HRESULT ExplorerDlg::ClearCache()
{
	if (m_webView2)
		return m_webView2->CallDevToolsProtocolMethod(L"Network.clearBrowserCache", L"{}", nullptr);
	else
		return E_ABORT;
}

HRESULT ExplorerDlg::ClearCookies()
{
	if (m_webView2)
		return m_webView2->CallDevToolsProtocolMethod(L"Network.clearBrowserCookies", L"{}", nullptr);
	else
		return E_ABORT;
}

void ExplorerDlg::CleanupUserDataFolder(bool init)
{
	WCHAR userDataFolder[MAX_PATH] = L"";

	// Obtain the absolute path for relative paths that include "./" or "../"
	std::wstring relativePath = L".WebView2";
	WCHAR rawPath[MAX_PATH];
	GetModuleFileNameW(tape.Ds2hInst, rawPath, MAX_PATH);
	std::wstring path(rawPath);
	path.append(relativePath);
	WCHAR* ret = _wfullpath(userDataFolder, path.c_str(), MAX_PATH);
	std::wstring userDataFolderPath(userDataFolder);

	if (init)
	{
		std::wstring message = L"Are you sure to clean up user data folder at:\n\n";
		path = rawPath;
		path.replace(path.size() - 12, 12, L"");
		message += path;
		message += L" ?\n\nWarning: This action is not reversible.";
		std::replace(message.begin(), message.end(), '\\', '\n');
		GetWindowRect(m_hWnd, &m_explorer_win);
		switch (MessageBoxPos(m_hWnd, message.c_str(), I18N.WebView2_Cleanup_Data_Folder, MB_YESNOCANCEL, m_explorer_win.left + 1, m_explorer_win.top + 21))
		{
		case IDYES:
			for (HWND hwnd : m_items)
				EnableWindow(hwnd, FALSE);
			::SetFocus(NULL);
			SendMessage(tape.Ds2hWnd, WM_DELETE_DATA_FOLER, NULL, NULL);
			break;
		}
	}
	else
	{
		UINT webviewProcessId = 0;
		m_webView2->get_BrowserProcessId(&webviewProcessId);
		CloseWebView();
		EnsureProcessIsClosed(webviewProcessId, 2000);
		Sleep(100);
		DeleteFileRecursive(userDataFolderPath);
		EnableWindow(m_items[ToolBar_Favorites], true);
		EnableWindow(m_items[ToolBar_Home], true);
		EnableWindow(m_items[ToolBar_AddressBar], true);
		EnableWindow(m_items[ToolBar_Go], true);
		::SetFocus(NULL);
	}
}

HRESULT ExplorerDlg::DeleteFileRecursive(std::wstring path)
{
	wil::com_ptr<IFileOperation> fileOperation;
	HRESULT result = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&fileOperation));
	if (FAILED(result))
		return E_FAIL;

	// Turn off all UI from being shown to the user during the operation.
	fileOperation->SetOperationFlags(FOF_NO_UI);

	wil::com_ptr<IShellItem> userDataFolder;
	SHCreateItemFromParsingName(path.c_str(), NULL, IID_PPV_ARGS(&userDataFolder));

	// Add the operation
	fileOperation->DeleteItem(userDataFolder.get(), NULL);
	userDataFolder.reset();

	// Perform the operation to delete the directory
	fileOperation->PerformOperations();

	fileOperation->Release();
	OleUninitialize();
	return S_OK;
}

void ExplorerDlg::ReinitializeWebView()
{
	if (m_webView2)
	{
		UINT webviewProcessId = 0;
		m_webView2->get_BrowserProcessId(&webviewProcessId);
		CloseWebView();
		EnsureProcessIsClosed(webviewProcessId, 2000);
	}

	InitializeWebView();
}

void ExplorerDlg::RestartDlg()
{
	// Use the reference to the web view before we close the app window
	UINT webviewProcessId = 0;
	m_webView2->get_BrowserProcessId(&webviewProcessId);
	// To restart the app completely, first we close the current Window
	CloseExplorerDlg();
	// Make sure the browser process inside webview is closed
	EnsureProcessIsClosed(webviewProcessId, 2000);
	// Get the command line arguments used to start this app
	LPWSTR args = GetCommandLineW();

	STARTUPINFOW startup_info = { 0 };
	startup_info.cb = sizeof(startup_info);
	PROCESS_INFORMATION temp_process_info = {};
	// Start a new process
	if (!::CreateProcess(
		nullptr, args,
		nullptr, // default process attributes
		nullptr, // default thread attributes
		FALSE,   // do not inherit handles
		0,
		nullptr, // no environment
		nullptr, // default current directory
		&startup_info,
		&temp_process_info))
	{
		// Log some error information if desired
	}

	::exit(0);
}

void ExplorerDlg::EnsureProcessIsClosed(UINT processId, int timeoutMs)
{
	UINT exitCode = 1;
	if (processId != 0)
	{
		HANDLE hBrowserProcess = ::OpenProcess(PROCESS_TERMINATE, false, processId);
		// Wait for the process to exit by itself
		DWORD waitResult = ::WaitForSingleObject(hBrowserProcess, timeoutMs);
		if (waitResult != WAIT_OBJECT_0)
		{
			// Force kill the process if it doesn't exit by itself
			BOOL result = ::TerminateProcess(hBrowserProcess, exitCode);
			::CloseHandle(hBrowserProcess);
		}
	}
}

//////////////////////////////////////////////////////////////////////

void ExplorerDlg::RegisterEventHandlers()
{
	m_webView2->add_NavigationStarting(
		Callback<ICoreWebView2NavigationStartingEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args)
			-> HRESULT {
				m_Navigating = true;
				m_FrameCreated = false;
				EnableWindow(m_items[ToolBar_Cancel], true);
				EnableWindow(m_items[ToolBar_ZoomPlus], false);
				EnableWindow(m_items[ToolBar_ZoomMinus], false);
				::SetFocus(NULL);

				wil::unique_cotaskmem_string newUri;
				args->get_Uri(&newUri);

				wil::unique_cotaskmem_string oldUri;
				m_webView2->get_Source(&oldUri);

				std::wstring appStartPage = L"about:blank";

				if (wcscmp(appStartPage.c_str(), newUri.get()) == 0)
				{
					// When navigating to the app start page, make the background color transparent
					m_controller2->get_DefaultBackgroundColor(&m_webViewColor);
					m_controller2->put_DefaultBackgroundColor(transparentColor);
				}
				else if (wcscmp(appStartPage.c_str(), oldUri.get()) == 0)
					// When navigating away from the app start page, set the background color back to the previous value
					m_controller2->put_DefaultBackgroundColor(m_webViewColor);

				if (ShouldBlockUri(newUri.get()))
				{
					// If the user clicked a blacklisted link to navigate, replace by a warning page
					args->put_Cancel(true);
					BOOL userInitiated;
					args->get_IsUserInitiated(&userInitiated);
					static WCHAR htmlBlacklistedDomain[500] = L"";
					std::wstring domain = GetDomainOfUri(newUri.get()).get();
					wsprintf(htmlBlacklistedDomain, L"<body style=""background-color:black;color:yellow;""><center><h1>Domain Blacklisted</h1><p style=""color:white;"">%s</center></body>", domain.c_str());
					/////////Bug////////////sender->NavigateToString(htmlBlacklistedDomain);
				}
				if (tape.DarkMode)
					ShowWindow(m_ScrollbarFramehWnd, SW_SHOW);
				return S_OK;}).Get(), &m_navigationStartingToken);

	m_webView2->add_NavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args)
			-> HRESULT {
				BOOL success;
				args->get_IsSuccess(&success);
				if (!success)
				{
					COREWEBVIEW2_WEB_ERROR_STATUS webErrorStatus;
					args->get_WebErrorStatus(&webErrorStatus);
					if (webErrorStatus == COREWEBVIEW2_WEB_ERROR_STATUS_DISCONNECTED)
					{
						// Do something here if you want to handle a specific error case.
						// In most cases this isn't necessary, because the WebView will
						// display its own error page automatically.
					}
				}
				EnableWindow(m_items[ToolBar_Refresh], true);
				EnableWindow(m_items[ToolBar_Cancel], false);
				EnableWindow(m_items[ToolBar_ZoomPlus], true);
				EnableWindow(m_items[ToolBar_ZoomMinus], true);
				::SetFocus(NULL);

				if (tape.DarkMode == 1)
					m_webView2->ExecuteScript(DarkModeStyle.c_str(), nullptr);
				else if (tape.DarkMode == 2)
					m_webView2->ExecuteScript(DarkMode2Style.c_str(), nullptr);

				SetScrollBarSize();
				if (((m_isHome && !MouseIsOverMain) || (!m_isHome && !m_mouseIsOver) && !isFullScreen) || MouseIsOverTab)
				{
					ScrollBarInactive();
					ResizeEverything();
				}
				m_Navigating = false;
				std::thread(HideFrameDeffered, m_ScrollbarFramehWnd, 100).detach();
				// TakePreview();
				return S_OK;}).Get(), &m_navigationCompletedToken);

	if (m_webView2_4)
	{
		m_webView2_4->add_FrameCreated(
			Callback<ICoreWebView2FrameCreatedEventHandler>(
				[this](ICoreWebView2* sender, ICoreWebView2FrameCreatedEventArgs* args)
				-> HRESULT {
					m_FrameCreated = true;
					::SetFocus(NULL);
					wil::com_ptr<ICoreWebView2Frame> webviewFrame;
					args->get_Frame(&webviewFrame);
					m_frames.emplace_back(webviewFrame);
					webviewFrame->add_Destroyed(
						Callback<ICoreWebView2FrameDestroyedEventHandler>(
							[this](ICoreWebView2Frame* sender, IUnknown* args) -> HRESULT {
								auto frame =
									std::find(m_frames.begin(), m_frames.end(), sender);
								if (frame != m_frames.end())
								{
									m_frames.erase(frame);
								}
								return S_OK;}).Get(), NULL);
					return S_OK;}).Get(), &m_frameCreatedToken);
	}

	m_webView2->add_FrameNavigationCompleted(
		Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args)
			-> HRESULT {
				BOOL success;
				args->get_IsSuccess(&success);
				if (!success)
				{
					COREWEBVIEW2_WEB_ERROR_STATUS webErrorStatus;
					args->get_WebErrorStatus(&webErrorStatus);
					// The web page can cancel its own iframe loads, so we'll ignore that.
					//if (webErrorStatus != COREWEBVIEW2_WEB_ERROR_STATUS_OPERATION_CANCELED)...
				}
				return S_OK;}).Get(), &m_frameNavigationCompletedToken);

	m_webView2->add_ProcessFailed(
		Callback<ICoreWebView2ProcessFailedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2ProcessFailedEventArgs* argsRaw)
			-> HRESULT {
				wil::com_ptr<ICoreWebView2ProcessFailedEventArgs> args = argsRaw;
				COREWEBVIEW2_PROCESS_FAILED_KIND kind;
				args->get_ProcessFailedKind(&kind);

				switch (kind)
				{
				case COREWEBVIEW2_PROCESS_FAILED_KIND_BROWSER_PROCESS_EXITED:
				{
					// Indicates that the browser process ended unexpectedly
					ScheduleReinitIfSelectedByUser(
						L"Browser process exited unexpectedly. Recreate webview?",
						L"Browser process exited", true);
					break;
				}
				case COREWEBVIEW2_PROCESS_FAILED_KIND_RENDER_PROCESS_EXITED:
				{
					// Indicates that the main frame's render process ended unexpectedly
					ScheduleReloadIfSelectedByUser(
						L"Browser render process ended unexpectedly. Reload page?",
						L"Web page unresponsive");
					break;
				}
				case COREWEBVIEW2_PROCESS_FAILED_KIND_RENDER_PROCESS_UNRESPONSIVE:
				{
					// Indicates that the main frame's render process is unresponsive
					ScheduleReinitIfSelectedByUser(
						L"Browser render process is unresponsive. Recreate webview?",
						L"Web page unresponsive");
					break;
				}
				case COREWEBVIEW2_PROCESS_FAILED_KIND_FRAME_RENDER_PROCESS_EXITED:
				{
					// Indicates that a frame-only render process ended unexpectedly
					// Check the runtime event args implements the newer interface
					auto args2 = args.try_query<ICoreWebView2ProcessFailedEventArgs2>();
					if (!args2)
						return S_OK;
					// The process exit does not affect the top, check if reload is needed
					wil::com_ptr<ICoreWebView2FrameInfoCollection> frameInfos;
					wil::com_ptr<ICoreWebView2FrameInfoCollectionIterator> iterator;
					args2->get_FrameInfosForFailedProcess(&frameInfos);
					frameInfos->GetIterator(&iterator);

					BOOL hasCurrent = FALSE;
					while (SUCCEEDED(iterator->get_HasCurrent(&hasCurrent)) && hasCurrent)
					{
						wil::com_ptr<ICoreWebView2FrameInfo> frameInfo;
						iterator->GetCurrent(&frameInfo);

						wil::unique_cotaskmem_string nameRaw;
						wil::unique_cotaskmem_string sourceRaw;
						frameInfo->get_Name(&nameRaw);
						frameInfo->get_Source(&sourceRaw);

						const std::wstring& source = sourceRaw.get();
						wil::com_ptr<IUri> uri;
						CreateUri(source.c_str(), Uri_CREATE_CANONICALIZE, 0, &uri);
						wil::unique_bstr domain;
						uri->GetDomain(&domain);

						// Content from our dlg uses a mapped host name.
						const std::wstring mappedAppHostName = L"appassets.example";
						if (domain.get() == mappedAppHostName)
						{
							ScheduleReloadIfSelectedByUser(
								L"Browser render process for window frame exited unexpectedly. "
								L"Reload page?",
								L"Frame content  unresponsive");
							break;
						}

						BOOL hasNext = FALSE;
						iterator->MoveNext(&hasNext);
					}
					break;
				}
				case COREWEBVIEW2_PROCESS_FAILED_KIND_PPAPI_PLUGIN_PROCESS_EXITED:
				{
					//Indicates that a PPAPI plugin process ended unexpectedly
					ScheduleReloadIfSelectedByUser(
						L"A PPAPI plugin process ended unexpectedly. Reload page?",
						L"PPAPI plugin failed");
					break;
				}
				case COREWEBVIEW2_PROCESS_FAILED_KIND_PPAPI_BROKER_PROCESS_EXITED:
				{
					//Indicates that a PPAPI plugin broker process ended unexpectedly
					ScheduleReloadIfSelectedByUser(
						L"A PPAPI plugin broker process ended unexpectedly. Reload page?",
						L"PPAPI plugin unresponsive");
					break;
				}
				case COREWEBVIEW2_PROCESS_FAILED_KIND_UTILITY_PROCESS_EXITED:
					//Indicates that a utility process ended unexpectedly
				case COREWEBVIEW2_PROCESS_FAILED_KIND_SANDBOX_HELPER_PROCESS_EXITED:
					//Indicates that a sandbox helper process ended unexpectedly
				case COREWEBVIEW2_PROCESS_FAILED_KIND_GPU_PROCESS_EXITED:
					//Indicates that the GPU process ended unexpectedly
				case COREWEBVIEW2_PROCESS_FAILED_KIND_UNKNOWN_PROCESS_EXITED:
					//Indicates that a process of unspecified kind ended unexpectedly
				{
					break;
				}
				}

				return S_OK;}).Get(), &m_processFailedToken);

	m_webView2->add_NewWindowRequested(
		Callback<ICoreWebView2NewWindowRequestedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2NewWindowRequestedEventArgs* args) {
				wil::unique_cotaskmem_string uri;
				// uri = wil::make_cotaskmem_string(L"");
				args->get_Uri(&uri);
				args->put_Handled(TRUE);

				if (ShouldBlockUri(uri.get()))
					return E_FAIL;

				std::wstring address = uri.get();
				if (m_isHome)
				{
					// new tab
					SendMessage(tape.Ds2hWnd, WM_CREATE_NEW_TAB, (WPARAM)address.c_str(), false);
				}
				else
				{
					// new window
					RECT win;
					if (m_isHome)
						GetWindowRect(tape.Ds2hWnd, &win);
					else
						GetWindowRect(m_hWnd, &win);
					new ExplorerDlg(address, false, m_zoomFactor, win);
					/*
					wil::com_ptr<ICoreWebView2Deferral> deferral;
					args->GetDeferral(&deferral);
					ExplorerDlg* newExplorerDlg;

					wil::com_ptr<ICoreWebView2WindowFeatures> windowFeatures;
					args->get_WindowFeatures(&windowFeatures);

					BOOL hasPosition = FALSE;
					windowFeatures->get_HasPosition(&hasPosition);

					BOOL hasSize = FALSE;
					windowFeatures->get_HasSize(&hasSize);

					RECT win;
					GetWindowRect(m_hWnd, &win);
					bool useActualSize = true;
					if (!!hasPosition && !!hasSize)
					{
						useActualSize = false;

						UINT32 left = 0;
						UINT32 top = 0;
						UINT32 height = 0;
						UINT32 width = 0;
						windowFeatures->get_Left(&left);
						windowFeatures->get_Top(&top);
						windowFeatures->get_Height(&height);
						windowFeatures->get_Width(&width);
						win.left = left;
						win.right = left + (width < 100 ? 100 : width);
						win.top = top;
						win.bottom = top + (height < 100 ? 100 : height);
					}

					wil::unique_cotaskmem_string uri;
					args->get_Uri(&uri);
					std::wstring address = uri.get();

					newExplorerDlg = new ExplorerDlg(address, false, m_zoomFactor, win);
					newExplorerDlg->m_isPopupWindow = true;
					newExplorerDlg->m_ToDoOnDeferred = [args, deferral, newExplorerDlg]() {
						// args->put_NewWindow(newExplorerDlg->m_webView2.get());
						args->put_Handled(TRUE);
						deferral->Complete();
					};
					newExplorerDlg->CloseExplorerDlg();
					*/
				}return S_OK;}).Get(), &m_newWindowRequestedToken);

	m_webView2->add_WindowCloseRequested(
		Callback<ICoreWebView2WindowCloseRequestedEventHandler>([this](ICoreWebView2* sender, IUnknown* args) {
			if (m_isPopupWindow)
				CloseExplorerDlg();
			return S_OK;}).Get(), &m_windowCloseRequestedToken);

	if (m_webView2_5)
	{
		//Enable Autoselect Client Certificate Selection
		m_webView2_5->add_ClientCertificateRequested(
			Callback<ICoreWebView2ClientCertificateRequestedEventHandler>(
				[this](
					ICoreWebView2* sender,
					ICoreWebView2ClientCertificateRequestedEventArgs* args) {
						wil::com_ptr<ICoreWebView2ClientCertificateCollection> certificateCollection;
						args->get_MutuallyTrustedCertificates(&certificateCollection);

						UINT certificateCollectionCount = 0;
						certificateCollection->get_Count(&certificateCollectionCount);
						wil::com_ptr<ICoreWebView2ClientCertificate> certificate = nullptr;

						if (certificateCollectionCount > 0)
						{
							// There is no significance to the order, picking a certificate arbitrarily.
							certificateCollection->GetValueAtIndex(certificateCollectionCount - 1, &certificate);
							// Continue with the selected certificate to respond to the server.
							args->put_SelectedCertificate(certificate.get());
							args->put_Handled(TRUE);
						}
						else
						{
							// Continue without a certificate if certificate collection is empty
							args->put_Handled(TRUE);
						}
						return S_OK;}).Get(),&m_ClientCertificateRequestedToken);
	}

	m_webView2->add_PermissionRequested(
		Callback<ICoreWebView2PermissionRequestedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2PermissionRequestedEventArgs* args)
			-> HRESULT {
				wil::unique_cotaskmem_string uri;
				COREWEBVIEW2_PERMISSION_KIND kind = COREWEBVIEW2_PERMISSION_KIND_UNKNOWN_PERMISSION;
				BOOL userInitiated = FALSE;

				args->get_Uri(&uri);
				args->get_PermissionKind(&kind);
				args->get_IsUserInitiated(&userInitiated);
				auto cached_key = std::tuple<std::wstring, COREWEBVIEW2_PERMISSION_KIND, BOOL>(
					std::wstring(uri.get()), kind, userInitiated);
				auto cached_permission = m_cached_permissions.find(cached_key);
				if (cached_permission != m_cached_permissions.end())
				{
					bool allow = cached_permission->second;
					if (allow)
						args->put_State(COREWEBVIEW2_PERMISSION_STATE_ALLOW);
					else
						args->put_State(COREWEBVIEW2_PERMISSION_STATE_DENY);
					return S_OK;
				}

				std::wstring message = I18N.WebView2_Permission;
				switch (kind)
				{
				case COREWEBVIEW2_PERMISSION_KIND_MICROPHONE:			{ message += I18N.WebView2_MICROPHONE; break; }
				case COREWEBVIEW2_PERMISSION_KIND_CAMERA:				{ message += I18N.WebView2_CAMERA; break; }
				case COREWEBVIEW2_PERMISSION_KIND_GEOLOCATION:			{ message += I18N.WebView2_GEOLOCATION; break; }
				case COREWEBVIEW2_PERMISSION_KIND_NOTIFICATIONS:		{ message += I18N.WebView2_NOTIFICATIONS; break; }
				case COREWEBVIEW2_PERMISSION_KIND_OTHER_SENSORS:		{ message += I18N.WebView2_OTHER_SENSORS; break; }
				case COREWEBVIEW2_PERMISSION_KIND_CLIPBOARD_READ:		{ message += I18N.WebView2_CLIPBOARD_READ; break; }
				case COREWEBVIEW2_PERMISSION_KIND_UNKNOWN_PERMISSION:
				default:												{ message += I18N.WebView2_UNKNOWN_PERMISSION; break; }
				}

				GetWindowRect(m_hWnd, &m_explorer_win);
				switch (MessageBoxPos(m_hWnd, message.c_str(), GetDomainOfUri(uri.get()).get(), MB_YESNOCANCEL | ((userInitiated) ? MB_ICONQUESTION : MB_ICONWARNING), m_explorer_win.right - 240, m_explorer_win.top + 21, 240))
				{
				case IDYES:
				{
					m_cached_permissions[cached_key] = true;
					args->put_State(COREWEBVIEW2_PERMISSION_STATE_ALLOW);
					break;
				}
				case IDNO:
				{
					m_cached_permissions[cached_key] = false;
					args->put_State(COREWEBVIEW2_PERMISSION_STATE_DENY);
					break;
				}
				default:
				{
					args->put_State(COREWEBVIEW2_PERMISSION_STATE_DEFAULT);
					break;
				}
				}
				return S_OK;}).Get(), &m_permissionRequestedToken);

	m_webView2->add_ScriptDialogOpening(
		Callback<ICoreWebView2ScriptDialogOpeningEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2ScriptDialogOpeningEventArgs* args)
			-> HRESULT {
				wil::com_ptr<ICoreWebView2ScriptDialogOpeningEventArgs> eventArgs = args;
				auto showDialog = [this, eventArgs] {
					wil::unique_cotaskmem_string uri;
					COREWEBVIEW2_SCRIPT_DIALOG_KIND type;
					wil::unique_cotaskmem_string message;
					wil::unique_cotaskmem_string defaultText;

					eventArgs->get_Uri(&uri);
					eventArgs->get_Kind(&type);
					eventArgs->get_Message(&message);
					eventArgs->get_DefaultText(&defaultText);

					std::wstring promptString = I18N.WEB_SCRIPT_DIALOG_2 + uri.get() + I18N.WEB_SCRIPT_DIALOG_3;
					TextInputDialog(
						m_hWnd, I18N.WEB_SCRIPT_DIALOG_1, promptString.c_str(),
						message.get(), defaultText.get(),
						/* readonly */ type != COREWEBVIEW2_SCRIPT_DIALOG_KIND_PROMPT);
					if (TextInput_confirmed)
					{
						eventArgs->put_ResultText(TextInput_input.c_str());
						eventArgs->Accept();
					}
				};

				if (m_deferredScripts)
				{
					wil::com_ptr<ICoreWebView2Deferral> deferral;
					args->GetDeferral(&deferral);
					m_completeDeferredDialog = [showDialog, deferral] {
						showDialog();
						deferral->Complete();
					};
				}
				else
					showDialog();
				return S_OK;}).Get(), &m_scriptDialogOpeningToken);

	m_webView2->add_SourceChanged(
		Callback<ICoreWebView2SourceChangedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2SourceChangedEventArgs* args)
			-> HRESULT {
				wil::unique_cotaskmem_string uri;
				sender->get_Source(&uri);
				if (wcscmp(uri.get(), L"about:blank") == 0)
					uri = wil::make_cotaskmem_string(L"");
				SetWindowText(m_items[ToolBar_AddressBar], uri.get());
				return S_OK;}).Get(), &m_sourceChangedToken);

	m_webView2->add_HistoryChanged(
		Callback<ICoreWebView2HistoryChangedEventHandler>(
			[this](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				BOOL canGoBack;
				BOOL canGoForward;
				sender->get_CanGoBack(&canGoBack);
				sender->get_CanGoForward(&canGoForward);
				EnableWindow(m_items[ToolBar_Back], canGoBack);
				EnableWindow(m_items[ToolBar_Forward], canGoForward);
				::SetFocus(NULL);
				return S_OK;}).Get(), &m_historyChangedToken);

	m_webView2->add_DocumentTitleChanged(
		Callback<ICoreWebView2DocumentTitleChangedEventHandler>(
			[this](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				wil::unique_cotaskmem_string title;
				sender->get_DocumentTitle(&title);
				m_documentTitle = title.get();
				std::wstring str(tape.szTitle);
				if (!m_profileDirName.empty())
					str += L" - " + m_profileDirName;
				if (!m_documentTitle.empty())
					str += L" - " + m_documentTitle;
				SetWindowText(m_hWnd, str.c_str());
				return S_OK;}).Get(), &m_documentTitleChangedToken);

	m_webView2->add_ContainsFullScreenElementChanged(
		Callback<ICoreWebView2ContainsFullScreenElementChangedEventHandler>(
			[this](ICoreWebView2* sender, IUnknown* args) -> HRESULT {
				sender->get_ContainsFullScreenElement(&m_containsFullscreenElement);
				if (m_containsFullscreenElement)
					EnterFullScreen();
				else
					ExitFullScreen();
				return S_OK;}).Get(), &m_containsFullScreenElementChangedToken);
/*
	m_webViewEnvironment->add_NewBrowserVersionAvailable(
		Callback<ICoreWebView2NewBrowserVersionAvailableEventHandler>(
			[this](ICoreWebView2Environment* sender, IUnknown* args) -> HRESULT {
				std::wstring message = L"We detected there is a new version for the browser.";
				if (m_webView2)
				{
					message += L"Do you want to restart the app? \n\n";
					message += L"Click No if you only want to re-create the webviews. \n";
					message += L"Click Cancel for no action. \n";
				}
				GetWindowRect(m_hWnd, &m_explorer_win);
				int response = MessageBoxPos(m_hWnd, message.c_str(), L"New available version", m_webView2 ? MB_YESNOCANCEL : MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);

				if (response == IDYES)
					RestartDlg();
				else if (response == IDNO)
					ReinitializeWebView();
				return S_OK;}).Get(),nullptr);
*/
}

bool ExplorerDlg::ShouldBlockUri(PWSTR uri)
{
	wil::unique_bstr host = GetDomainOfUri(uri);
	std::wstring domain = host.get();
	std::size_t found = domain.find_first_of(L"www.");
	if (domain.substr(0, 4) == L"www.")
		domain = domain.substr(4, domain.size());

	for (auto site = m_vblockedSites.begin(); site != m_vblockedSites.end(); site++)
	{
		if (lstrcmpi(site->c_str(), domain.c_str()) == 0)
			return true;
	}
	return false;
}

wil::unique_bstr ExplorerDlg::GetDomainOfUri(PWSTR uri)
{
	wil::com_ptr<IUri> uriObject;
	CreateUri(uri, Uri_CREATE_CANONICALIZE | Uri_CREATE_NO_DECODE_EXTRA_INFO, 0, &uriObject);
	wil::unique_bstr domain;
	uriObject->GetHost(&domain);
	return domain;
}

void ExplorerDlg::ScheduleReloadIfSelectedByUser(const std::wstring& message, const std::wstring& caption, bool closeOnNo)
{
	RunAsync([this, message, caption, closeOnNo]() {
		GetWindowRect(m_hWnd, &m_explorer_win);
		int selection = MessageBoxPos(m_hWnd, message.c_str(), caption.c_str(), MB_YESNO, m_explorer_win.left + 1, m_explorer_win.top + 21);
		if (selection == IDYES)
			m_webView2->Reload();
		else if (closeOnNo)
			CloseWebView();
		});
}

void ExplorerDlg::ScheduleReinitIfSelectedByUser(const std::wstring& message, const std::wstring& caption, bool closeOnNo)
{
	for (HWND hwnd : m_items)
		EnableWindow(hwnd, FALSE);
	::SetFocus(NULL);
	RunAsync([this, message, caption, closeOnNo]() {
		GetWindowRect(m_hWnd, &m_explorer_win);
		int selection = MessageBoxPos(m_hWnd, message.c_str(), caption.c_str(), MB_YESNO, m_explorer_win.left + 1, m_explorer_win.top + 21);
		if (selection == IDYES)
			ReinitializeWebView();
		else if (closeOnNo)
			CloseWebView();
		});
}

//////////////////////////////////////////////////////////////////////

void ExplorerDlg::NavigateToAddressBar()
{
	int length = GetWindowTextLength(m_items[ToolBar_AddressBar]);
	std::wstring uri(length, 0);
	PWSTR buffer = const_cast<PWSTR>(uri.data());
	GetWindowText(m_items[ToolBar_AddressBar], buffer, length + 1);

	HRESULT hr = m_webView2->Navigate(uri.c_str());
	if (hr == E_INVALIDARG)
	{
		if (uri.find(L' ') == std::wstring::npos && uri.find(L'.') != std::wstring::npos)
		{
			hr = m_webView2->Navigate((L"https://" + uri).c_str());
			if (hr == E_INVALIDARG)
				hr = m_webView2->Navigate((L"http://" + uri).c_str());
		}
		else
		{
			std::wstring urlEscaped(2048, ' ');
			DWORD dwEscaped = (DWORD)urlEscaped.length();
			UrlEscapeW(uri.c_str(), &urlEscaped[0], &dwEscaped, URL_ESCAPE_ASCII_URI_COMPONENT);
//			hr = m_webView2->Navigate((L"https://bing.com/search?q=" + std::regex_replace(urlEscaped, std::wregex(L"(?:%20)+"), L"+")).c_str());
			hr = m_webView2->Navigate((L"https://google.com/search?q=" + std::regex_replace(urlEscaped, std::wregex(L"(?:%20)+"), L"+")).c_str());
		}
	}
}

void ExplorerDlg::NavigateToFavorite(int favorite)
{
	if (favorite < 0 || favorite > 9)
		return;

	if (!ViewComponentAvailable)
	{
		m_initialUri = tape.WebURL[favorite];
		InitializeWebView();
	}
	else
		m_webView2->Navigate(tape.WebURL[favorite]);
}

void ExplorerDlg::Back()
{
	if (m_webView2)
		m_webView2->GoBack();
}

void ExplorerDlg::Forward()
{
	if (m_webView2)
		m_webView2->GoForward();
}

void ExplorerDlg::Refresh()
{
	if (m_webView2)
		m_webView2->Reload();
}

void ExplorerDlg::Cancel()
{
	if (m_webView2)
		m_webView2->Stop();
}

void ExplorerDlg::AutoRefresh()
{
	m_autoRefresh = !m_autoRefresh;
	if (m_autoRefresh)
	{
		SetWindowText(m_items[ToolBar_AutoRefresh], L"◼");
		if (m_webView2)
		{
			m_webView2->Reload();
			SetTimer(m_hWnd, 1, 1000 * tape.WebRefreshTime, NULL);
		}
	}
	else
	{
		SetWindowText(m_items[ToolBar_AutoRefresh], L"◻");
		KillTimer(m_hWnd, 1);
	}
}

/*
void ExplorerDlg::TakePreview()
{
	if (IsWindowVisible(m_hWnd) && ViewComponentAvailable)
	{
		hTab_Tip_canShow = false;
		ShowWindow(hTab_Tip, SW_HIDE);
		DeleteObject(m_Preview);
		HDC screenDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
		HDC memoryDC = CreateCompatibleDC(screenDC);
		RECT win;
		GetWindowRect(m_hWnd, &win);
		int width = win.right - win.left;
		int height = win.bottom - win.top;
		int medianh = min((width * 9) / 16, height);
		int medianw = (medianh * 16) / 9;
		// int medianw = GetDeviceCaps(hScreenDC, HORZRES);
		// int medianh = GetDeviceCaps(hScreenDC, VERTRES);
		m_Preview = CreateCompatibleBitmap(screenDC, medianw, medianh);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memoryDC, m_Preview);
		win.left += (width > height) ? (width - medianw) / 2 : 0;

		// PAINTSTRUCT ps;
		// BeginPaint(hDlg, &ps);
		// HDC hDC = GetDC(hDlg);
		// StretchBlt(hDC, 0, 0, 192, 108, screenDC, rect.left, rect.top, median, median, SRCCOPY);
		StretchBlt(memoryDC, 0, 0, medianw, medianh, screenDC, rect.left, rect.top, medianw, medianh, SRCCOPY);
		m_Preview = (HBITMAP)SelectObject(memoryDC, hOldBitmap);
		// EndPaint(hDlg, &ps);
		// DeleteDC(hDC);
		DeleteDC(memoryDC);
		DeleteDC(screenDC);
		m_Previewdone = true;
		hTab_Tip_canShow = true;
	}
}
*/

void ExplorerDlg::SetFavorite(int favorite)
{
	int length = GetWindowTextLength(m_items[ToolBar_AddressBar]);
	std::wstring uri(length, 0);
	PWSTR buffer = const_cast<PWSTR>(uri.data());
	GetWindowText(m_items[ToolBar_AddressBar], buffer, length + 1);
	tape.setWebURL(uri.c_str(), favorite);
	switch (favorite)
	{
	case 0: { tape.Save(tape.Setting_WebURL0); break; }
	case 1: { tape.Save(tape.Setting_WebURL1); break; }
	case 2: { tape.Save(tape.Setting_WebURL2); break; }
	case 3: { tape.Save(tape.Setting_WebURL3); break; }
	case 4: { tape.Save(tape.Setting_WebURL4); break; }
	case 5: { tape.Save(tape.Setting_WebURL5); break; }
	case 6: { tape.Save(tape.Setting_WebURL6); break; }
	case 7: { tape.Save(tape.Setting_WebURL7); break; }
	case 8: { tape.Save(tape.Setting_WebURL8); break; }
	case 9: { tape.Save(tape.Setting_WebURL9); break; }
	}
}

OPENFILENAME ExplorerDlg::CreateOpenFileName(LPWSTR defaultName, LPCWSTR filter)
{
	OPENFILENAME openFileName = {};
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = nullptr;
	openFileName.hInstance = nullptr;
	openFileName.lpstrFile = defaultName;
	openFileName.lpstrFilter = filter;
	openFileName.nMaxFile = MAX_PATH;
	openFileName.Flags = OFN_OVERWRITEPROMPT;
	return openFileName;
}

void ExplorerDlg::PrintToPdf(bool enableLandscape)
{
	WCHAR defaultName[MAX_PATH] = L"WebView2_PrintedPdf.pdf";
	OPENFILENAME openFileName = CreateOpenFileName(defaultName, L"PDF File\0*.pdf\0");
	if (GetSaveFileName(&openFileName))
	{
		wil::com_ptr<ICoreWebView2PrintSettings> printSettings = nullptr;
		wil::com_ptr<ICoreWebView2Environment6> webviewEnvironment6;
		m_webViewEnvironment->QueryInterface(IID_PPV_ARGS(&webviewEnvironment6));
		if (webviewEnvironment6)
		{
			webviewEnvironment6->CreatePrintSettings(&printSettings);
			if (enableLandscape)
				printSettings->put_Orientation(COREWEBVIEW2_PRINT_ORIENTATION_LANDSCAPE);
			printSettings->put_ScaleFactor(max(0.1, min(2, m_zoomFactor)));
			printSettings->put_ShouldPrintBackgrounds(true);
			printSettings->put_ShouldPrintHeaderAndFooter(false);
		}

		wil::com_ptr<ICoreWebView2_7> webview2_7;
		m_webView2->QueryInterface(IID_PPV_ARGS(&webview2_7));
		if (webview2_7)
		{
			GetWindowRect(m_hWnd, &m_explorer_win);
			m_printToPdfInProgress = true;
			webview2_7->PrintToPdf(
				openFileName.lpstrFile, printSettings.get(),
				Callback<ICoreWebView2PrintToPdfCompletedHandler>(
					[this](HRESULT error, BOOL isSuccessful) -> HRESULT {
						if (FAILED(error))
						{
							MessageBoxPos(m_hWnd, I18N.WebView2_PDF_Failed, I18N.WebView2_PDF_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
							FAIL_FAST();
						}
						m_printToPdfInProgress = false;
						auto showDialog = [isSuccessful] {
							MessageBoxPos(nullptr, (isSuccessful) ? I18N.WebView2_PDF_Succeeded : I18N.WebView2_PDF_Failed, I18N.WebView2_PDF_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
						};
						RunAsync([showDialog]() { showDialog(); });
						return S_OK;}).Get());
		}
	}
}

uint64_t timeSinceEpochMillisec()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void ExplorerDlg::SaveScreenshot(bool autofilename)
{
	if (autofilename)
	{
		std::wstring filename = ExePath() + L"\\" + std::to_wstring(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + L".png";
		wil::com_ptr<IStream> stream;
		SHCreateStreamOnFileEx(filename.c_str(), STGM_READWRITE | STGM_CREATE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &stream);
		m_webView2->CapturePreview(COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT_PNG, stream.get(), nullptr);
	}
	else
	{
		WCHAR defaultName[MAX_PATH] = L"WebView2_Screenshot.png";
		OPENFILENAME openFileName = CreateOpenFileName(defaultName, L"PNG File\0*.png\0");
		if (GetSaveFileName(&openFileName))
		{
			wil::com_ptr<IStream> stream;
				SHCreateStreamOnFileEx(defaultName, STGM_READWRITE | STGM_CREATE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &stream);

				GetWindowRect(m_hWnd, &m_explorer_win);
				HWND mainWindow = m_hWnd;
				m_webView2->CapturePreview(
					COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT_PNG, stream.get(),
					Callback<ICoreWebView2CapturePreviewCompletedHandler>(
						[mainWindow](HRESULT error) -> HRESULT {
							if (FAILED(error))
								MessageBoxPos(mainWindow, I18N.WebView2_Capture_Failed, I18N.WebView2_Screenshot_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
							else
								MessageBoxPos(mainWindow, I18N.WebView2_Preview_Captured, I18N.WebView2_Screenshot_Tittle, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
							return S_OK;}).Get());
		}
	}
}

void ExplorerDlg::ToggleVisibility()
{
	m_isVisible = !m_isVisible;
	if (m_controller)
		m_controller->put_IsVisible(m_isVisible);
}

void ExplorerDlg::DarkMode(unsigned char mode)
{
	if (mode != 1 && mode != 2)
		return;

	if (tape.DarkMode == mode)
	{
		tape.DarkMode = 0;
		SetBackgroundColor(RGB(255, 255, 255), false);
	}
	else
	{
		tape.DarkMode = mode;
		SetBackgroundColor(RGB(16, 18, 19), false);
	}
	if (ViewComponentAvailable)
		NavigateToAddressBar();
	else
		m_controller2->put_DefaultBackgroundColor(transparentColor);
}

void ExplorerDlg::ScrollBy(int x, int y)
{
	if (m_webView2)
	{
		std::wstring javaScript = L"window.scrollBy(" + std::to_wstring(x) + L", " + std::to_wstring(y) + L");";
		InjectScript(javaScript);
	}
}

void ExplorerDlg::SetZoomFactor(double zoom)
{
	if (m_webView2)
	{
		m_zoomFactor = max(0.25, min(5, zoom));
		m_controller->put_ZoomFactor(m_zoomFactor);
		SetScrollBarSize();
	}
}

void ExplorerDlg::SetScrollBarSize()
{
	if (m_webView2)
	{
		m_webView2->ExecuteScript(L"document.getElementsByTagName('body')[0].removeChild(ScrollBarSize)", nullptr);
		std::wstring ScrollBarpx = std::to_wstring((m_zoomFactor < 1) ? ((double)14 / m_zoomFactor) : ((double)14 / (m_zoomFactor * (1 - ((m_zoomFactor - 1) / 13)))));
		std::wstring ScrollBarSize = L"document.querySelector('body').style.overflow='scroll';var ScrollBarSize=document.createElement('style');ScrollBarSize.type='text/css';ScrollBarSize.innerHTML='::-webkit-scrollbar{width: " + ScrollBarpx + L"px !important; height: " + ScrollBarpx + L"px !important; }';document.getElementsByTagName('body')[0].appendChild(ScrollBarSize)";
		m_webView2->ExecuteScript(ScrollBarSize.c_str(), nullptr);
	}
}

void ExplorerDlg::ZoomMinus(double zoomout)
{
	m_zoomFactor = m_zoomFactor - max(0.01, zoomout * (m_zoomFactor / 100));
	SetZoomFactor(m_zoomFactor);
}

void ExplorerDlg::ZoomPlus(double zoomin)
{
	m_zoomFactor = m_zoomFactor + max(0.01, zoomin * (m_zoomFactor / 100));
	SetZoomFactor(m_zoomFactor);
}

void ExplorerDlg::ZoomReset()
{
	m_zoomFactor = tape.DefaultZoomValue;
	if (m_webView2)
		m_controller->put_ZoomFactor(m_zoomFactor);
}

void ExplorerDlg::ZoomSet()
{
	tape.DefaultZoomValue = m_zoomFactor;
	tape.Save(tape.Setting_DefaultZoomValue);
}

void ExplorerDlg::ToggleTopMost()
{
	if (m_isHome)
	{
		m_isCurrentlyTopMost = (GetWindowLong(tape.Ds2hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;
		m_isCurrentlyTopMost = !m_isCurrentlyTopMost;
		SetWindowPos(tape.Ds2hWnd, m_isCurrentlyTopMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
	}
	else
	{
		m_isCurrentlyTopMost = (GetWindowLong(m_hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;
		m_isCurrentlyTopMost = !m_isCurrentlyTopMost;
		SetWindowPos(m_hWnd, m_isCurrentlyTopMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
	}
}

void ExplorerDlg::SetBoundsMode()
{
	if (m_controller3)
	{
		if (tape.RawBounds)
			m_controller3->put_BoundsMode(COREWEBVIEW2_BOUNDS_MODE_USE_RAW_PIXELS);
		else
			m_controller3->put_BoundsMode(COREWEBVIEW2_BOUNDS_MODE_USE_RASTERIZATION_SCALE);
		ResizeWebView();
	}
}

void ExplorerDlg::SetBlockImages(COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContextToFilter)
{
	if (m_blockImages)
	{
		m_resourceContext = resourceContextToFilter;
		m_webView2->AddWebResourceRequestedFilter(L"*", m_resourceContext);
		m_webView2->add_WebResourceRequested(
			Callback<ICoreWebView2WebResourceRequestedEventHandler>(
				[this](
					ICoreWebView2* sender,
					ICoreWebView2WebResourceRequestedEventArgs* args) {
						COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContext;
						args->get_ResourceContext(&resourceContext);
						// Ensure that the type is image
						if (resourceContext != m_resourceContext)
							return E_INVALIDARG;
						// Override the response with an empty one to block the image.
						// If put_Response is not called, the request will continue as normal.
						wil::com_ptr<ICoreWebView2WebResourceResponse> response;
						wil::com_ptr<ICoreWebView2Environment> environment;
						wil::com_ptr<ICoreWebView2_2> webview2;
						m_webView2->QueryInterface(IID_PPV_ARGS(&webview2));
						webview2->get_Environment(&environment);
						switch (m_resourceContext)
						{
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_DOCUMENT:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: application/msword", &response);
							break;
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_STYLESHEET:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: text/css", &response);
							break;
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: image/jpeg", &response);
							break;
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_MEDIA:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: video/x-msvideo", &response);
								break;
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_FONT:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: font/ttf", &response);
								break;
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_SCRIPT:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: application/javascript", &response);
								break;
						case COREWEBVIEW2_WEB_RESOURCE_CONTEXT_XML_HTTP_REQUEST:
							environment->CreateWebResourceResponse(nullptr, 403 /*NoContent*/, L"Blocked", L"Content-Type: application/xml", &response);
							break;
						}
						args->put_Response(response.get());
						return S_OK;}).Get(),&m_ImageBlockingToken);
	}
	else
		m_webView2->remove_WebResourceRequested(m_ImageBlockingToken);
	m_webView2->Reload();
}

void ExplorerDlg::InjectScript(std::wstring javaScript)
{
	if (!m_Navigating)
		m_webView2->ExecuteScript(javaScript.c_str(), nullptr);
}

void ExplorerDlg::SetInitializeScript()
{
	if (tape.WebScript.size())
		m_webView2->AddScriptToExecuteOnDocumentCreated(tape.WebScript.c_str(), nullptr);
}

void ExplorerDlg::SetDeferred()
{
	m_settings->put_AreDefaultScriptDialogsEnabled(m_deferredScripts);
}

void ExplorerDlg::CompleteDeferred()
{
	if (m_completeDeferredDialog)
	{
		m_completeDeferredDialog();
		m_completeDeferredDialog = nullptr;
	}
}

void ExplorerDlg::SendStringWebMessage()
{
	TextInputDialog(
		m_hWnd,
		I18N.WEB_POST_MESSAGE_STRING_1,
		I18N.WEB_POST_MESSAGE_STRING_2,
		I18N.WEB_POST_MESSAGE_STRING_3);
	if (TextInput_confirmed)
		m_webView2->PostWebMessageAsString(TextInput_input.c_str());
}

void ExplorerDlg::SendJsonWebMessage()
{
	TextInputDialog(
		m_hWnd,
		I18N.WEB_POST_MESSAGE_JSON_1,
		I18N.WEB_POST_MESSAGE_JSON_2,
		I18N.WEB_POST_MESSAGE_JSON_3,
		L"{\"SetColor\":\"blue\"}");
	if (TextInput_confirmed)
		m_webView2->PostWebMessageAsJson(TextInput_input.c_str());
}

void ExplorerDlg::SubscribeToCdpEvent()
{
	TextInputDialog(
		m_hWnd,
		I18N.WEB_SUBSCRIBE_CDP_EVENT_1,
		I18N.WEB_SUBSCRIBE_CDP_EVENT_2,
		I18N.WEB_SUBSCRIBE_CDP_EVENT_3,
		L"Log.entryAdded");
	if (TextInput_confirmed)
	{
		std::wstring eventName = TextInput_input;
		wil::com_ptr<ICoreWebView2DevToolsProtocolEventReceiver> receiver;
		m_webView2->GetDevToolsProtocolEventReceiver(eventName.c_str(), &receiver);

		// If we are already subscribed to this event, unsubscribe first.
		auto preexistingToken = m_devToolsProtocolToken.find(eventName);
		if (preexistingToken != m_devToolsProtocolToken.end())
			receiver->remove_DevToolsProtocolEventReceived(preexistingToken->second);

		GetWindowRect(m_hWnd, &m_explorer_win);
		HWND mainWindow = m_hWnd;
		receiver->add_DevToolsProtocolEventReceived(
			Callback<ICoreWebView2DevToolsProtocolEventReceivedEventHandler>(
				[mainWindow, eventName](
					ICoreWebView2* sender,
					ICoreWebView2DevToolsProtocolEventReceivedEventArgs* args) -> HRESULT {
						wil::unique_cotaskmem_string parameterObjectAsJson;
						args->get_ParameterObjectAsJson(&parameterObjectAsJson);
						MessageBoxPos(mainWindow, parameterObjectAsJson.get(), (I18N.WebView2_CDP_Event + eventName).c_str(), MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
						return S_OK;}).Get(),&m_devToolsProtocolToken[eventName]);
	}
}

void ExplorerDlg::CallCdpMethod()
{
	TextInputDialog(
		m_hWnd,
		I18N.WEB_CALL_CDP_METHOD_1,
		I18N.WEB_CALL_CDP_METHOD_2,
		I18N.WEB_CALL_CDP_METHOD_3,
		L"Runtime.evaluate {\"expression\":\"alert(\\\"test\\\")\"}");
	if (TextInput_confirmed)
	{
		size_t delimiterPos = TextInput_input.find(L' ');
		std::wstring methodName = TextInput_input.substr(0, delimiterPos);
		std::wstring methodParams =
			(delimiterPos < TextInput_input.size()
				? TextInput_input.substr(delimiterPos + 1)
				: L"{}");

		GetWindowRect(m_hWnd, &m_explorer_win);
		m_webView2->CallDevToolsProtocolMethod(
			methodName.c_str(),
			methodParams.c_str(),
			Callback<ICoreWebView2CallDevToolsProtocolMethodCompletedHandler>(
				[](HRESULT error, PCWSTR resultJson) -> HRESULT
				{
					MessageBoxPos(nullptr, resultJson, I18N.WebView2_CDP_Result, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
					return S_OK;}).Get());
	}
}

void ExplorerDlg::AddComObject()
{
	TextInputDialog(
		m_hWnd,
		I18N.WEB_COM_OBJECT_1,
		I18N.WEB_COM_OBJECT_2,
		I18N.WEB_COM_OBJECT_3,
		L"InternetExplorer.Application");
	if (TextInput_confirmed)
	{
		CLSID classId = {};
		HRESULT hr = CLSIDFromProgID(TextInput_input.c_str(), &classId);
		if (FAILED(hr))
			hr = CLSIDFromString(TextInput_input.c_str(), &classId);

		GetWindowRect(m_hWnd, &m_explorer_win);
		if (SUCCEEDED(hr))
		{
			wil::com_ptr_nothrow<IDispatch> objectAsDispatch;
			hr = CoCreateInstance(
				classId,
				nullptr,
				CLSCTX_LOCAL_SERVER | CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER,
				IID_PPV_ARGS(&objectAsDispatch));
			if (SUCCEEDED(hr))
			{
				wil::unique_variant objectAsVariant;
				objectAsVariant.vt = VT_DISPATCH;
				hr = objectAsDispatch.query_to(IID_PPV_ARGS(&objectAsVariant.pdispVal));
				if (SUCCEEDED(hr))
				{
					hr = m_webView2->AddHostObjectToScript(L"example", &objectAsVariant);
					if (FAILED(hr))
						MessageBoxPos(m_hWnd, I18N.WebView2_AddHostObjectToScript_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
				}
				else
					MessageBoxPos(m_hWnd, I18N.WebView2_IDispatch_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
			}
			else
				MessageBoxPos(m_hWnd, I18N.WebView2_CoCreateInstance_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
		}
		else
			MessageBoxPos(m_hWnd, I18N.WebView2_Convert_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
	}
}

void ExplorerDlg::SetUserAgent()
{
	if (m_settings2)
		if (!tape.UserAgent.empty())
			m_settings2->put_UserAgent(tape.UserAgent.c_str());
}

void ExplorerDlg::SetBlackList()
{
	if (tape.BlockedSites.size())
	{
		m_vblockedSites.clear();
		size_t begin = 0;
		size_t end = 0;
		while (end != std::wstring::npos)
		{
			end = tape.BlockedSites.find(L';', begin);
			if (end != begin)
			{
				m_vblockedSites.push_back(tape.BlockedSites.substr(begin, end - begin));
			}
			begin = end + 1;
		}
	}
}

void ExplorerDlg::OpenTaskManagerWindow()
{
	auto webView6 = m_webView2.try_query<ICoreWebView2_6>();

	if (webView6)
		webView6->OpenTaskManagerWindow();
}

void ExplorerDlg::SetBackgroundColor(COLORREF color, bool transparent)
{
	m_webViewColor.R = GetRValue(color);
	m_webViewColor.G = GetGValue(color);
	m_webViewColor.B = GetBValue(color);
	m_webViewColor.A = transparent ? 0 : 255;
	m_controller2->put_DefaultBackgroundColor(m_webViewColor);
}

//////////////////////////////////////////////////////////////////////

void ExplorerDlg::ShowMenu()
{
	WebMenuVisible = true;
	RECT win;
	GetWindowRect(m_hWnd, &win);
	int item = TrackPopupMenu((HMENU)GetSubMenu(hMenuWeb, 0), TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, win.left + 1, win.top, NULL, m_hWnd, NULL);
	if (item)
		PostMessage(m_hWnd, WM_COMMAND, item, 0);
	WebMenuVisible = false;
}

void ExplorerDlg::ShowMenuFavorites()
{
	WebMenuVisible = true;
	redrawMenu(10, true);
	RECT win;
	GetWindowRect(m_hWnd, &win);
	int item = TrackPopupMenu((HMENU)GetSubMenu(hMenuFav, 0), TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, win.left + 1, win.top + 17, NULL, m_hWnd, NULL);
	if (item)
		PostMessage(m_hWnd, WM_COMMAND, item, 0);
	WebMenuVisible = false;
}

void ExplorerDlg::Suspend()
{
	wil::com_ptr<ICoreWebView2_3> webView;
	webView = m_webView2.try_query<ICoreWebView2_3>();
	if (webView)
	{
		GetWindowRect(m_hWnd, &m_explorer_win);
		HRESULT hr = webView->TrySuspend(
			Callback<ICoreWebView2TrySuspendCompletedHandler>(
				[](HRESULT error, BOOL isSuccessful) -> HRESULT {
					if ((error != S_OK) || !isSuccessful)
						MessageBoxPos(nullptr, I18N.Suspend_Failed, nullptr, MB_OK, m_explorer_win.left + 1, m_explorer_win.top + 21);
					return S_OK;}).Get());
	}
}

void ExplorerDlg::Resume()
{
	wil::com_ptr<ICoreWebView2_3> webView;
	webView = m_webView2.try_query<ICoreWebView2_3>();
	if (webView)
		webView->Resume();
}

void ExplorerDlg::EnterFullScreen()
{
	isFullScreen = true;
	HWND tofull_hWnd = (m_isHome) ? tape.Ds2hWnd : m_hWnd;

	MONITORINFO monitorinfo = { sizeof(monitorinfo) };
	if (GetMonitorInfo(MonitorFromWindow(tofull_hWnd, MONITOR_DEFAULTTOPRIMARY), &monitorinfo))
		if (GetWindowRect(tofull_hWnd, &m_previousWindowRect))
		{
			if (m_isHome)
				SendMessage(tape.Ds2hWnd, WM_ENTER_FULLSCREEN, 0, 0);
			else
			{
				DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
				SetWindowLong(m_hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
			}
			SetWindowPos(
				tofull_hWnd, HWND_TOPMOST,
				monitorinfo.rcMonitor.left, monitorinfo.rcMonitor.top,
				monitorinfo.rcMonitor.right - monitorinfo.rcMonitor.left,
				monitorinfo.rcMonitor.bottom - monitorinfo.rcMonitor.top,
				SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
		}
	HideToolBar();
	ResizeEverything();
	if (!m_isHome)
		m_mouseIsOver = false;
	SetTimer(m_hWnd, 6, 70, NULL);
}

void ExplorerDlg::ExitFullScreen()
{
	KillTimer(m_hWnd, 6);
	HWND hWnd = m_hWnd;
	HWND tofull_hWnd = (m_isHome) ? tape.Ds2hWnd : m_hWnd;

	if (m_isHome)
		SendMessage(tape.Ds2hWnd, WM_EXIT_FULLSCREEN, 0, 0);
	else
	{
		DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
		SetWindowLong(m_hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}
	SetWindowPos(
		tofull_hWnd, (m_isHome) ? HWND_TOPMOST : HWND_NOTOPMOST,
		m_previousWindowRect.left, m_previousWindowRect.top,
		m_previousWindowRect.right - m_previousWindowRect.left,
		m_previousWindowRect.bottom - m_previousWindowRect.top,
		SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

	if (!m_isHome || (m_isHome && !MouseIsOverMain))
		OnMouseOut();
	else if (m_isHome)
		ShowToolBar();
	isFullScreen = false;
}

void ExplorerDlg::ToggleFullScreen()
{
	(isFullScreen) ? ExitFullScreen() : EnterFullScreen();
}

void ExplorerDlg::OnMouseOver()
{
	if ((m_isHome && MouseIsOverMain) || (!m_isHome && m_mouseIsOver))
	{
		if (!m_isHome)
		{
			RECT win;
			GetWindowRect(m_hWnd, &win);
			win.left -= 7;
			win.right -= win.left - 7;
			win.bottom -= win.top - 7;
			DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
			SetWindowLong(m_hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
			SetWindowPos(m_hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
		ShowToolBar();
		ScrollBarActive();
	}
	ResizeEverything();
}

void ExplorerDlg::OnMouseOut()
{
	if ((m_isHome && (!MouseIsOverMain || MouseIsOverTab)) || (!m_isHome && !m_mouseIsOver))
	{
		if (!m_isHome)
		{
			RECT win;
			GetWindowRect(m_hWnd, &win);
			win.left += 7;
			win.right -= win.left + 7;
			win.bottom -= win.top + 7;
			DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
			SetWindowLong(m_hWnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW | WS_BORDER);
			SetWindowPos(m_hWnd, NULL, win.left, win.top, win.right, win.bottom, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
		HideToolBar();
		ScrollBarInactive();
	}
	ResizeEverything();
}

void ExplorerDlg::ShowToolBar()
{
	if (!m_ToolBar)
		if (((m_isHome && MouseIsOverMain && !MouseIsOverTab) || (!m_isHome && m_mouseIsOver)) && !isFullScreen)
		{
			for (ToolBar item = ToolBar_Favorites; item < ToolBar_Count; item = ToolBar(item + 1))
				ShowWindow(m_items[item], SW_SHOW);
			m_ToolBar = true;
		}
}

void ExplorerDlg::HideToolBar()
{
	if (m_ToolBar)
		if ((m_isHome && (!MouseIsOverMain || MouseIsOverTab)) || (!m_isHome && !m_mouseIsOver) || isFullScreen)
		{
			for (ToolBar item = ToolBar_Favorites; item < ToolBar_Count; item = ToolBar(item + 1))
				ShowWindow(m_items[item], SW_HIDE);
			m_ToolBar = false;
		}
}

void ExplorerDlg::ScrollBarActive()
{
	if (!m_ScrollBar)
		if (!m_Navigating && ViewComponentAvailable && !MouseIsOverTab)
		{
			m_webView2->ExecuteScript(L"document.getElementsByTagName('body')[0].removeChild(NoScrollBar)", nullptr);
			m_ScrollBar = true;
		}
}

void ExplorerDlg::ScrollBarInactive()
{
	if (m_ScrollBar)
		if (!m_Navigating && ViewComponentAvailable)
		{
			// m_webView2->ExecuteScript(L"document.querySelector('body').style.overflow='hidden'", nullptr);
			m_webView2->ExecuteScript(L"document.querySelector('body').style.overflow='scroll';var NoScrollBar=document.createElement('style');NoScrollBar.type='text/css';NoScrollBar.innerHTML='::-webkit-scrollbar{display:none}';document.getElementsByTagName('body')[0].appendChild(NoScrollBar)", nullptr);
			m_ScrollBar = false;
		}
}

void ExplorerDlg::ResizeEverything()
{
	int tabsHeight = (isFullScreen || (m_isHome && !MouseIsOverMain) || (!m_isHome && !m_mouseIsOver)) ? 0 : 17;
	//int toolbarHeight = (!m_Navigating && (isFullScreen || !m_ToolBar || (m_isHome && !MouseIsOverMain) || (!m_isHome && !m_mouseIsOver))) ? 0 : 17;
	int toolbarHeight = (m_ToolBar) ? 17 : 0;
	if (m_isHome)
	{
		RECT rect;
		GetClientRect(tape.Ds2hWnd, &rect);
		MoveWindow(rect.left, rect.top + tabsHeight, rect.right, rect.bottom, FALSE);
	}

	RECT availableBounds = { 0 };
	GetClientRect(m_hWnd, &availableBounds);
	availableBounds.top = toolbarHeight;
	m_webView2bounds = availableBounds;

	SetWindowPos(m_ScrollbarFramehWnd, nullptr, availableBounds.right - 17, toolbarHeight, 17, availableBounds.bottom - toolbarHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	if (!m_containsFullscreenElement && m_ToolBar)
	{
		int width = availableBounds.right - availableBounds.left;

		int nextOffsetX = 0;
		for (ToolBar item = ToolBar_Favorites; item < ToolBar_Count; item = ToolBar(item + 1))
		{
			static const int s_itemButtonLogicalWidth = 21;
			int itemWidth = 0;
			switch (item)
			{
			case ToolBar_Favorites:
			case ToolBar_Home:
			case ToolBar_Back:
			case ToolBar_Forward:
			case ToolBar_Refresh:
			case ToolBar_Go:
			case ToolBar_Cancel:
			case ToolBar_AutoRefresh:
			case ToolBar_ZoomPlus:
			case ToolBar_ZoomMinus:
				itemWidth = s_itemButtonLogicalWidth;
				break;
			case ToolBar_AddressBar:
				itemWidth = width - s_itemButtonLogicalWidth * (ToolBar_Count - 1);
				break;
			default:
				FAIL_FAST();
			}
			SetWindowPos(m_items[item], nullptr, nextOffsetX, 0, itemWidth, toolbarHeight, SWP_NOZORDER | SWP_NOACTIVATE);
			nextOffsetX += itemWidth;
		}
	}

	if (ViewComponentAvailable)
		ResizeWebView();
}

void ExplorerDlg::ResizeWebView()
{
	SIZE webViewSize = {
			LONG((m_webView2bounds.right - m_webView2bounds.left)),
			LONG((m_webView2bounds.bottom - m_webView2bounds.top)) };

	RECT desiredBounds = m_webView2bounds;
	desiredBounds.bottom = LONG(webViewSize.cy + m_webView2bounds.top);
	desiredBounds.right = LONG(webViewSize.cx + m_webView2bounds.left);

	m_controller->put_Bounds(desiredBounds);
}

void ExplorerDlg::Show()
{
	ShowWindow(m_hWnd, SW_SHOW);
}

void ExplorerDlg::Hide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}

static void HideFrameDeffered(HWND tohide, unsigned long timems)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timems));
	ShowWindow(tohide, SW_HIDE);
}

BOOL ExplorerDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hWnd, x, y, w, h, r);
} 

void ExplorerDlg::SetTransparency(bool transparencyon)
{
	if (transparencyon)
		SetWindowTransparent(m_hWnd, true, tape.Opacity);
	else
		SetWindowTransparent(m_hWnd, false, NULL);
}

/*
HRESULT ExplorerDlg::GetHtmlContent(std::wstring uri, bool httpsmode, bool searchmode, unsigned char nloops) //need SSL
{
	//if (nloops == 0 && !searchmode)
	//	uri = L"http://jaapl.org/";

	std::string url = converterX.to_bytes(uri);
	std::string domain, filepath;
	if (searchmode)
	{
		url = std::regex_replace(url, std::regex("(?:%20)+"), "+");
		domain = "www.google.com";
		filepath = "/search?q=" + url;
		httpsmode = true;
	}
	else
	{
		std::string::size_type n;
		if (url.substr(0, 7) == "http://")
		{
			httpsmode = false;
			url.erase(0, 7);
		}
		if (url.substr(0, 8) == "https://")
		{
			httpsmode = true;
			url.erase(0, 8);
		}
		n = url.find("//");
		if (n != std::string::npos)
			url.erase(0, n + 2);
		n = url.find("/");
		if (n != std::string::npos)
		{
			domain = url.substr(0, n);
			filepath = url.substr(n);
			n = filepath.rfind("/");
		}
		else
		{
			domain = url;
			filepath = "/";
		}
	}

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return E_FAIL;

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;			// IPv4
	hints.ai_protocol = IPPROTO_TCP;	// TCP
	hints.ai_socktype = SOCK_STREAM;	// SOCK

	struct addrinfo* result = NULL;
	DWORD getAddrRes = getaddrinfo(domain.c_str(), NULL, &hints, &result);
	if (getAddrRes != 0 || result == NULL)
	{
		freeaddrinfo(result);
		return E_FAIL;
	}

	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr;	// IPv4 Address
	sockAddr.sin_family = AF_INET;											// IPv4
	if (httpsmode)
		sockAddr.sin_port = htons(443);										// HTTP Port: 443
	else
		sockAddr.sin_port = htons(80);										// HTTP Port: 80
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	freeaddrinfo(result);
	if (sock == INVALID_SOCKET)
	{
		closesocket(sock);
		return E_FAIL;
	}

	if (connect(sock, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		closesocket(sock);
		return E_FAIL;
	}

	m_htmlContent = L"";
	if (httpsmode)
	{
		SSL_library_init();
		SSLeay_add_ssl_algorithms();
		SSL_load_error_strings();
		//const SSL_METHOD* method = TLSv1_2_client_method();
		const SSL_METHOD* method = SSLv23_client_method();
		SSL_CTX* ctx = SSL_CTX_new(method);
		if (ctx == NULL)
			return E_FAIL;
		SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION);
		SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

		SSL* ssl = SSL_new(ctx);
		if (!ssl)
			return E_FAIL;
		int sockssl = SSL_get_fd(ssl);
		SSL_set_fd(ssl, sock);
		int err = SSL_connect(ssl);
		if (err <= 0)
			return E_FAIL;

		std::string request = "GET https://" + domain + filepath + " HTTP/1.1\r\nConnection: close\r\n\r\n";
		int len = SSL_write(ssl, request.c_str(), strlen(request.c_str()));
		if (len < 0)
		{
			int err = SSL_get_error(ssl, len);
			switch (err)
			{
			case SSL_ERROR_SSL:
				return E_FAIL;
			case SSL_ERROR_WANT_WRITE:
			case SSL_ERROR_WANT_READ:
				return E_UNEXPECTED;
			case SSL_ERROR_ZERO_RETURN:
			case SSL_ERROR_SYSCALL:
			default:
				return E_ABORT;
			}
		}

		char buf[8000];
		while (true)
		{
			len = SSL_read(ssl, buf, 100);
			if (len < 0)
			{
				int err = SSL_get_error(ssl, len);
				switch (err)
				{
				case SSL_ERROR_SSL:
					return E_FAIL;
				case SSL_ERROR_WANT_WRITE:
				case SSL_ERROR_WANT_READ:
					return E_UNEXPECTED;
				case SSL_ERROR_ZERO_RETURN:
				case SSL_ERROR_SYSCALL:
				default:
					return E_ABORT;
				}
			}
			for (int i = 0; i < len; i++)
				if (buf[i] >= 32 || buf[i] == '\n' || buf[i] == '\r')
					m_htmlContent += buf[i];
			if (len < 100)
				break;
		}
		SSL_shutdown(ssl);
		SSL_free(ssl);
		SSL_CTX_free(ctx);
	}
	else
	{
		std::string request = "GET " + filepath + " HTTP/1.1\r\nHost: " + domain + "\r\nConnection: close\r\n\r\n";
		int sentBytes = send(sock, request.c_str(), strlen(request.c_str()), 0);

		if (sentBytes < strlen(request.c_str()) || sentBytes == SOCKET_ERROR)
			return E_FAIL;

		char buf[8000];
		ZeroMemory(buf, sizeof(buf));
		int dataLen;
		while ((dataLen = recv(sock, buf, sizeof(buf), 0) > 0))
		{
			int i = 0;
			while (buf[i] >= 32 || buf[i] == '\n' || buf[i] == '\r') {
				m_htmlContent += buf[i];
				i += 1;
			}
		}
	}
	closesocket(sock);
	WSACleanup();
	std::wstring header = m_htmlContent.substr(0, 40);
	if (!searchmode && (header.find(L"301") != std::wstring::npos || header.find(L"302") != std::wstring::npos))
	{
		++nloops;
		std::wstring::size_type n = m_htmlContent.find(L"Location: https");
		if (n != std::wstring::npos)
		{
			m_htmlContent.erase(0, n + 18);
			n = m_htmlContent.find(L"\r");
			if (n != std::wstring::npos)
				m_htmlContent.erase(n, m_htmlContent.size());
			return GetHtmlContent(m_htmlContent, true, (nloops >= 5) ? true : false, nloops);;
		}
		else
		{
			std::string::size_type n = m_htmlContent.find(L"Location: http");
			if (n != std::wstring::npos)
			{
				m_htmlContent.erase(0, n + 17);
				n = m_htmlContent.find(L"\r");
				if (n != std::wstring::npos)
					m_htmlContent.erase(n, m_htmlContent.size());
				return GetHtmlContent(m_htmlContent, (nloops >= 5) ? true : false, (nloops >= 5) ? true : false, nloops);
			}
		}
	}
	else if(header.find(L"200") != std::wstring::npos)
	{
		std::wstring::size_type n = m_htmlContent.find(L"<!DOCTYPE");
		if (n != std::wstring::npos)
		{
				m_htmlContent.erase(0, n);
				return S_OK;
		}
		return E_UNEXPECTED;
	}

	if (!searchmode)
		return GetHtmlContent(uri, true, true, nloops);

	return E_INVALIDARG;
}
*/
