#pragma once

class Guardian
{
public:
	Guardian();
	~Guardian();

	void				Init(HWND);
	const				WCHAR* GuardianButtons();
	void				GuardianButtonsComputString();
	void				AllDevicesRestart();
	void				BlacklistInit(int hid = 0);
	void				WhitelistInit();
	void				WhitelistCheck(int pid = 0);
	BOOL				WhitelistDs2vJoy();
	void				HidStates();
	char				GetHidGState();
	char				GetHidCState();
	BOOL				GuardianInstall(bool verbose = false);
	BOOL				GuardianUninstall(bool verbose = false);
	BOOL				GuardianEnable(bool verbose = false);
	BOOL				GuardianDisable(bool verbose = false);
	BOOL				HidCerberusInstall(bool verbose = false);
	BOOL				HidCerberusUninstall(bool verbose = false);
	BOOL				HidCerberusStart(bool verbose = false);
	BOOL				HidCerberusStop(bool verbose = false);
	BOOL				RestartDevices(bool verbose = false);

private:
	char				GuardianState(bool verbose = false);
	char				HidCerberusState(bool verbose = false);
	BOOL				WhitelistByPID(int pid = 0);
	BOOL				RemoveWhitelistByPID(int pid = 0);
	BOOL				PurgeWhitelist();
	void				WhitelistByExeName(std::wstring ProcessExeName);
	void				RemoveWhitelistByExeName(std::wstring ProcessExeName);
	BOOL				BlacklistDevice(std::wstring device);
	BOOL				RemoveBlacklistDevice(std::wstring device);
	std::wstring		GetBlacklist();
	void				AffectedList();
	BOOL				PurgeBlacklist();
	BOOL				RestartDevice(std::string device = "", bool verbose = false);

	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;

	const std::string	GuardianUrl = "http://localhost:26762/api/v1/hidguardian/";
	std::vector<int>	ProcessPIDs{ };
	bool				pid1_affected = false;
	bool				pid2_affected = false;
	bool				pid3_affected = false;

	int					HidGState = 0;
	int					HidCState = 0;
};

	//String of Keymap buttons in use, to show in status bar
	static std::wstring	GuardianButtonsString = L"";
	extern Guardian		hid;
