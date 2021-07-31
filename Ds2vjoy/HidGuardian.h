#pragma once

class Guardian
{
public:
	Guardian();
	~Guardian();

	BOOL Init(HWND);
	void AllDevicesRestart();
	void BlacklistInit(int hid = 0);
	void WhitelistInit();
	void WhitelistCheck(int pid = 0);
	BOOL WhitelistDs2vJoy();
	void HidStates();
	int GetHidGState();
	int GetHidCState();
	BOOL GuardianInstall(bool verbose = false);
	BOOL GuardianUninstall(bool verbose = false);
	BOOL GuardianEnable(bool verbose = false);
	BOOL GuardianDisable(bool verbose = false);
	BOOL HidCerberusInstall(bool verbose = false);
	BOOL HidCerberusUninstall(bool verbose = false);
	BOOL HidCerberusStart(bool verbose = false);
	BOOL HidCerberusStop(bool verbose = false);
	BOOL RestartDevices(bool verbose = false);

private:
	int GuardianState(bool verbose = false);
	int HidCerberusState(bool verbose = false);
	BOOL WhitelistByPID(int pid = 0);
	BOOL RemoveWhitelistByPID(int pid = 0);
	BOOL PurgeWhitelist();
	void WhitelistByExeName(std::wstring ProcessExeName);
	void RemoveWhitelistByExeName(std::wstring ProcessExeName);
	BOOL BlacklistDevice(std::string device);
	BOOL RemoveBlacklistDevice(std::string device);
	std::string GetBlacklist();
	void AffectedList();
	BOOL PurgeBlacklist();
	BOOL RestartDevice(std::string device = "", bool verbose = false);

	HWND m_hWnd;
	HWND m_hDlg;

	const std::string GuardianUrl = "http://localhost:26762/api/v1/hidguardian/";
	std::vector<int> ProcessPIDs;
	bool pid1_affected;
	bool pid2_affected;
	bool pid3_affected;

	int HidGState;
	int HidCState;
};

extern Guardian hid;
