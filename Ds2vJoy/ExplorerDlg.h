#pragma once

#include <wil/com.h>
#include <wrl.h>
#include "WebView2.h"
#include "WebView2EnvironmentOptions.h"
#include <winrt/Windows.UI.Composition.Desktop.h>

//#include "openssl/ssl.h"
//#include "openssl/err.h"
//namespace winrtComp = winrt::Windows::UI::Composition;

static void HideFrameDeffered(HWND tohide, unsigned long long timems);

class ExplorerDlg
{
public:
	enum ToolBar : unsigned char
	{
		ToolBar_Favorites,
		ToolBar_Home,
		ToolBar_Back,
		ToolBar_Forward,
		ToolBar_Refresh,
		ToolBar_AddressBar,
		ToolBar_Go,
		ToolBar_Cancel,
		ToolBar_AutoRefresh,
		ToolBar_ZoomMinus,
		ToolBar_ZoomPlus,
		ToolBar_Count
	};

	ExplorerDlg(const std::wstring& startpage = L"", bool isHome = false, float zoom = tape.DefaultZoomValue, RECT windowRect = { 0 });
	~ExplorerDlg();

	void InstallComplete(int return_code);
	bool CloseWebView();
	HRESULT ClearCache();
	HRESULT ClearCookies();
	void CleanupUserDataFolder(bool init = false);
	void NavigateToAddressBar();
	void NavigateToFavorite(int favorite = 0);
	void Back();
	void Forward();
	void Refresh();
	void Cancel();
	void AutoRefresh();
	// void TakePreview();
	void SaveScreenshot(bool autofilename = false);
	void ToggleVisibility();
	void DarkMode(unsigned char mode = 1);
	void ScrollBy(int x, int y);
	void ZoomMinus(float zoomout = 5);
	void ZoomPlus(float zoomin = 5);
	void ZoomReset();
	void ZoomSet();
	void ShowMenu();
	void OnMouseOver();
	void OnMouseOut();
	void ResizeEverything();
	void ToggleFullScreen();
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);
	void SetTransparency(bool transparencyon);

	HWND m_hDlg = nullptr;
	bool m_isHome = false;
	bool m_onMouseOver = true;
	bool ViewComponentAvailable = false;
	// bool m_Previewdone = false;
	// HBITMAP m_Preview = { 0 };

private:
	static LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void RunAsync(std::function<void(void)> callback);
	void redrawMenu(int ntabs, bool isfavoritesmenu = false);

	void InitializeWebView();
	HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);
	HRESULT OnCreateCoreWebView2ControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);
	void CloseExplorerDlg();
	HRESULT DeleteFileRecursive(std::wstring path);
	void ReinitializeWebView();
	void RestartDlg();
	void EnsureProcessIsClosed(UINT processId, int timeoutMs);

	void RegisterEventHandlers();
	bool ShouldBlockUri(PWSTR uri);
	wil::unique_bstr GetDomainOfUri(PWSTR uri);
	void ScheduleReloadIfSelectedByUser(const std::wstring& message, const std::wstring& caption, bool closeOnNo = false);
	void ScheduleReinitIfSelectedByUser(const std::wstring& message, const std::wstring& caption, bool closeOnNo = false);

	void SetFavorite(int favorite = 1);
	OPENFILENAME CreateOpenFileName(LPWSTR defaultName, LPCWSTR filter);
	void PrintToPdf(bool enableLandscape = false);
	void SetZoomFactor(float zoom = 1.0);
	void SetScrollBarSize();
	void ToggleTopMost();
	void SetBoundsMode();
	void SetBlockImages(COREWEBVIEW2_WEB_RESOURCE_CONTEXT resourceContextToFilter = COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE);
	void InjectScript(std::wstring javaScript);
	void SetInitializeScript();
	void SetDeferred();
	void CompleteDeferred();
	void SendStringWebMessage();
	void SendJsonWebMessage();
	void SubscribeToCdpEvent();
	void CallCdpMethod();
	void AddComObject();
	void SetUserAgent();
	void SetBlackList();
	void OpenTaskManagerWindow();
	void SetBackgroundColor(COLORREF color, bool transparent);

	void ShowMenuFavorites();
	void Suspend();
	void Resume();
	void EnterFullScreen();
	void ExitFullScreen();
	void ShowToolBar();
	void HideToolBar();
	void ScrollBarActive();
	void ScrollBarInactive();
	void ResizeWebView();

	// std::wstring m_htmlContent = L"";
	// HRESULT GetHtmlContent(std::wstring uri, bool httpsmode = false, bool searchmode = false, unsigned char nloops = 0);

	wil::com_ptr<ICoreWebView2Environment> m_webViewEnvironment;
	wil::com_ptr<ICoreWebView2Controller> m_controller;
	wil::com_ptr<ICoreWebView2Controller2> m_controller2;
	wil::com_ptr<ICoreWebView2Controller3> m_controller3;
	wil::com_ptr<ICoreWebView2> m_webView2;
	wil::com_ptr<ICoreWebView2_3> m_webView2_3;
	wil::com_ptr<ICoreWebView2_4> m_webView2_4;
	wil::com_ptr<ICoreWebView2_5> m_webView2_5;
	wil::com_ptr<ICoreWebView2Settings> m_settings;
	wil::com_ptr<ICoreWebView2Settings2> m_settings2;
	wil::com_ptr<ICoreWebView2Settings3> m_settings3;
	wil::com_ptr<ICoreWebView2Settings4> m_settings4;
	wil::com_ptr<ICoreWebView2Settings5> m_settings5;
	wil::com_ptr<ICoreWebView2Settings6> m_settings6;

	EventRegistrationToken m_navigationStartingToken = {};
	EventRegistrationToken m_navigationCompletedToken = {};
	EventRegistrationToken m_frameCreatedToken = {};
	EventRegistrationToken m_frameNavigationCompletedToken = {};
	EventRegistrationToken m_processFailedToken = {};
	EventRegistrationToken m_newWindowRequestedToken = {};
	EventRegistrationToken m_windowCloseRequestedToken = {};
	EventRegistrationToken m_ClientCertificateRequestedToken = {};
	EventRegistrationToken m_permissionRequestedToken = {};
	EventRegistrationToken m_scriptDialogOpeningToken = {};
	EventRegistrationToken m_sourceChangedToken = {};
	EventRegistrationToken m_historyChangedToken = {};
	EventRegistrationToken m_documentTitleChangedToken = {};
	EventRegistrationToken m_containsFullScreenElementChangedToken = {};
	EventRegistrationToken m_browserExitedEventToken = {};
	EventRegistrationToken m_ImageBlockingToken = {};
	std::map<std::wstring, EventRegistrationToken> m_devToolsProtocolToken;
	COREWEBVIEW2_WEB_RESOURCE_CONTEXT m_resourceContext;

	std::wstring m_userDataFolder = L"";
	std::wstring m_initialUri;
	std::wstring m_documentTitle;
	std::wstring m_profileDirName;

	//Background Image members
	// HDC m_memHdc;
	// HBITMAP m_appBackgroundImageHandle;
	// BITMAP m_appBackgroundImage;

	//Menu
	int m_TabsID[36];
	int m_TabsFavID[10];

	//Toolbar
	std::vector<HWND> m_items;
	HFONT m_Toolbarfont = nullptr;
	bool m_autoRefresh = false;

	//Vidibility
	bool m_mouseIsOver = false;
	HWND m_ScrollbarFramehWnd = nullptr;
	RECT m_previousWindowRect = {};
	BOOL m_containsFullscreenElement = false;

	//Window
	bool m_isVisible = true;
	bool m_isCurrentlyTopMost = false;
	RECT m_webView2bounds = {};

	//Control
	bool m_Navigating = true;
	bool m_FrameCreated = false;
	bool m_ToolBar = true;
	bool m_ScrollBar = true;

	//File
	bool m_printToPdfInProgress = false;

	//Process
	UINT m_browserProcessId = 0;
	UINT32 m_newestBrowserPid = 0;
	std::function<void()> m_ToDoOnDeferred;
//	std::function<void()> m_onExplorerDlgClosing;

	//Script
	bool m_isPopupWindow = false;
	std::vector<wil::com_ptr<ICoreWebView2Frame>> m_frames;

	//Settings
	std::function<void()> m_completeDeferredDialog;
	std::map<std::tuple<std::wstring, COREWEBVIEW2_PERMISSION_KIND, BOOL>, bool> m_cached_permissions;
	std::vector<std::wstring> m_vblockedSites;

	//View
	float m_zoomFactor = 1.0;
	COREWEBVIEW2_COLOR m_webViewColor = { 255, 255, 255, 255 };
	COREWEBVIEW2_COLOR transparentColor = { 0, 255, 255, 255 };
	HWND m_downloadsButton;
	const int m_downloadsButtonMargin = 50;
	const int m_downloadsButtonWidth = 120;
	const int m_downloadsButtonHeight = 80;
};

extern bool MouseIsOverMain;
extern bool MouseIsOverTab;
extern bool WebMenuVisible;
extern bool isFullScreen;
extern std::wstring initialUri;
extern std::vector<std::unique_ptr<ExplorerDlg>> web_tabs;
