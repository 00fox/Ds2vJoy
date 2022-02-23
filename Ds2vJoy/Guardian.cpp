#include "stdafx.h"
#include "Guardian.h"

Guardian::Guardian()
{
}

Guardian::~Guardian()
{
	if (tape.PurgeWhitelist)
		PurgeWhitelist();
	else
	{
		for (int i = 0; i < ProcessPIDs.size(); i++)
			RemoveWhitelistByPID(ProcessPIDs[i]);
	}
	if (tape.RemoveBlacklist)
	{
		AffectedList();

		if (tape.dsHID1Enable && tape.dsHID1 && pid1_affected)
			RemoveBlacklistDevice(tape.getHID(1));
		if (tape.dsHID2Enable && tape.dsHID2 && pid2_affected)
			RemoveBlacklistDevice(tape.getHID(2));
		if (tape.dsHID3Enable && tape.dsHID3 && pid3_affected)
			RemoveBlacklistDevice(tape.getHID(3));
	}
}

void Guardian::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	if (tape.GuardianActive && !tape.GuardianPaused)
	{
		WhitelistInit();
		BlacklistInit(-1);
	}
}

void Guardian::AllDevicesRestart()
{
	for (int i = 1; i < 4; i++)
		if (tape.getHID(i) != L"")
			DeviceRestart(tape.getHID(i));

	return;
}

void Guardian::BlacklistInit(int hid)
{
	if ((tape.GuardianActive && !tape.GuardianPaused && tape.RemoveBlacklist) || hid)
	{
		AffectedList();

		if (tape.dsHID1 && (hid == -1 || hid == 0 || hid == 1))
		{
			if (tape.dsHID1Enable && !tape.GuardianPaused)
			{
				if (tape.GuardianActive && !pid1_affected)
				{
					RemoveBlacklistDevice(tape.getHID(1));
					BlacklistDevice(tape.getHID(1));
					Sleep(100);
					if (tape.getHID(1) != L"")
						DeviceRestart(tape.getHID(1));
				}
				else if (!tape.GuardianActive && pid1_affected)
				{
					RemoveBlacklistDevice(tape.getHID(1));
					Sleep(100);
					if (tape.getHID(1) != L"")
						DeviceRestart(tape.getHID(1));
				}
			}
			else if (pid1_affected)
			{
				RemoveBlacklistDevice(tape.getHID(1));
				Sleep(100);
				if (tape.getHID(1) != L"")
					DeviceRestart(tape.getHID(1));
			}
		
		}
		if (tape.dsHID2 && (hid == -1 || hid == 0 || hid == 2))
		{
			if (tape.dsHID2Enable && !tape.GuardianPaused)
			{
				if (tape.GuardianActive && !pid2_affected)
				{
					RemoveBlacklistDevice(tape.getHID(2));
					BlacklistDevice(tape.getHID(2));
					Sleep(100);
					if (tape.getHID(2) != L"")
						DeviceRestart(tape.getHID(2));
				}
				else if (!tape.GuardianActive && pid2_affected)
				{
					RemoveBlacklistDevice(tape.getHID(2));
					Sleep(100);
					if (tape.getHID(2) != L"")
						DeviceRestart(tape.getHID(2));
				}
			}
			else if (pid2_affected)
			{
				RemoveBlacklistDevice(tape.getHID(2));
				Sleep(100);
				if (tape.getHID(2) != L"")
					DeviceRestart(tape.getHID(2));
			}

		}
		if (tape.dsHID3 && (hid == -1 || hid == 0 || hid == 3))
		{
			if (tape.dsHID3Enable && !tape.GuardianPaused)
			{
				if (tape.GuardianActive && !pid3_affected)
				{
					RemoveBlacklistDevice(tape.getHID(3));
					BlacklistDevice(tape.getHID(3));
					Sleep(100);
					if (tape.getHID(3) != L"")
						DeviceRestart(tape.getHID(3));
				}
				else if (!tape.GuardianActive && pid3_affected)
				{
					RemoveBlacklistDevice(tape.getHID(3));
					Sleep(100);
					if (tape.getHID(3) != L"")
						DeviceRestart(tape.getHID(3));
				}
			}
			else if (pid3_affected)
			{
				RemoveBlacklistDevice(tape.getHID(3));
				Sleep(100);
				if (tape.getHID(3) != L"")
					DeviceRestart(tape.getHID(3));
			}

		}
	}
}

void Guardian::WhitelistInit()
{
	if (tape.PurgeWhitelist)
		PurgeWhitelist();
	else
	{
		for (int i = 0;i < ProcessPIDs.size(); i++)
		{
			RemoveWhitelistByPID(ProcessPIDs[i]);
		}
	}
	ProcessPIDs = { 0 };
	if (tape.GuardianActive && !tape.GuardianPaused)
		WhitelistDs2vJoy();
	WhitelistCheck();
}

void Guardian::WhitelistCheck(int pid)
{
	if ((tape.GuardianActive && !tape.GuardianPaused) || pid)
	{
		if (tape.Exe1Name && (pid == 0 || pid == 1))
		{
			if (tape.Exe1NameEnable)
				WhitelistByExeName(tape.Exe1Name);
			else if (pid)
				RemoveWhitelistByExeName(tape.Exe1Name);
		}
		if (tape.Exe2Name && (pid == 0 || pid == 2))
		{
			if (tape.Exe2NameEnable)
				WhitelistByExeName(tape.Exe2Name);
			else if (pid)
				RemoveWhitelistByExeName(tape.Exe2Name);
		}
		if (tape.Exe3Name && (pid == 0 || pid == 3))
		{
			if (tape.Exe3NameEnable)
				WhitelistByExeName(tape.Exe3Name);
			else if (pid)
				RemoveWhitelistByExeName(tape.Exe3Name);
		}
		if (tape.Exe4Name && (pid == 0 || pid == 4))
		{
			if (tape.Exe4NameEnable)
				WhitelistByExeName(tape.Exe4Name);
			else if (pid)
				RemoveWhitelistByExeName(tape.Exe4Name);
		}
		if (tape.Exe5Name && (pid == 0 || pid == 5))
		{
			if (tape.Exe5NameEnable)
				WhitelistByExeName(tape.Exe5Name);
			else if (pid)
				RemoveWhitelistByExeName(tape.Exe5Name);
		}
	}
}

void Guardian::HidStates()
{
	HidGState = GuardianState();
	HidCState = HidCerberusState();
}

int Guardian::GetHidGState()
{
	return HidGState;
}

int Guardian::GetHidCState()
{
	return HidCState;
}

int Guardian::GuardianState(bool verbose)
{
	char GuardianState = -1;

	std::wstring devconpath = L"Devcon.exe status Root\\HidGuardian";
	std::wstring devconcmd = LaunchCmd(devconpath.c_str());

	if (FindInString(devconcmd, L"No matching devices found"))
		GuardianState = 0;
	if (FindInString(devconcmd, L"Driver is running"))
		GuardianState = 1;
	if (FindInString(devconcmd, L"Device is disabled"))
		GuardianState = 2;

	if (verbose)
		switch (GuardianState)
		{
		case 0: { echo(L"HidGuardian driver is uninstalled"); break; }
		case 1: { echo(L"HidGuardian driver is runing"); break; }
		case 2: { echo(L"HidGuardian driver is disabled"); break; }
		default: { echo(L"HidGuardian state unknown"); break; }
		}

	return GuardianState;
}

BOOL Guardian::GuardianInstall(bool verbose)
{
	if (GuardianState() > 0)
	{
		if (verbose)
			echo(L"HidGuardian driver is already installed");
		return TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName;

	if (ExtractEmbededResource(installpath, IDR_HIDGUARDIAN_ZIP, true))
	{
		std::wstring devconpath = L"Devcon.exe install \"" + PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\HidGuardian\\HidGuardian.inf\" Root\\HidGuardian";
		LaunchCmd(devconpath.c_str());

		devconpath = L"Devcon.exe classfilter HIDClass upper -HidGuardian";
		LaunchCmd(devconpath.c_str());

		if (GuardianState() == 1)
		{
			echo(L"HidGuardian driver is installed");
			return TRUE;
		}
	}

	if (verbose)
		echo(L"ERROR: HidGuardian driver instalation failed");

	return FALSE;
}

BOOL Guardian::GuardianUninstall(bool verbose)
{
	BOOL GuardianUninstall = FALSE;

	if (GuardianState() > 0)
	{
		{
			std::wstring devconpath = L"Devcon.exe remove Root\\HidGuardian";
			LaunchCmd(devconpath.c_str());

			devconpath = L"Devcon.exe classfilter HIDClass upper !HidGuardian";
			LaunchCmd(devconpath.c_str());
		}

		if (GuardianState() < 1)
		{
			echo(L"HidGuardian driver is uninstalled");
			GuardianUninstall = TRUE;
		}
		else
			echo(L"ERROR: HidGuardian driver uninstalation failed");
	}
	else
	{
		if (verbose)
			echo(L"HidGuardian driver is already uninstalled");
		GuardianUninstall = TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\HidGuardian\0\0";
	std::filesystem::remove_all(installpath);

	std::wstring prfdirpath = PrfPath() + L"/" + tape.ProgramFilesDirName;
	prfdirpath = ReplaceInString(prfdirpath, L"\\", '/');
	RemoveDirectoryW(prfdirpath.c_str());

	return GuardianUninstall;
}

BOOL Guardian::GuardianEnable(bool verbose)
{
	int hdState = GuardianState();

	if (hdState == 0)
	{
		if (verbose)
			echo(L"HidGuardian driver is not installed");
		return FALSE;
	}
	else if (hdState == 1)
	{
		if (verbose)
			echo(L"HidGuardian driver is already running");
		return TRUE;
	}

	std::wstring devconpath = L"Devcon.exe enable Root\\HidGuardian";
	LaunchCmd(devconpath.c_str());

	if (GuardianState() == 1)
	{
		if (verbose)
			echo(L"HidGuardian driver enabled");
		return TRUE;
	}

	if (verbose)
		echo(L"HidGuardian driver enabling failed");

	return FALSE;
}

BOOL Guardian::GuardianDisable(bool verbose)
{
	int hdState = GuardianState();

	if (hdState == 0)
	{
		if (verbose)
			echo(L"HidGuardian driver is not installed");
		return FALSE;
	}
	else if (hdState == 2)
	{
		if (verbose)
			echo(L"HidGuardian driver is already disabled");
		return TRUE;
	}

	std::wstring devconpath = L"Devcon.exe disable Root\\HidGuardian";
	LaunchCmd((ExePath() + devconpath).c_str());

	if (GuardianState() == 2)
	{
		if (verbose)
			echo(L"HidGuardian driver disabled");
		return TRUE;
	}

	if (verbose)
		echo(L"HidGuardian driver disabling failed");

	return FALSE;
}

int Guardian::HidCerberusState(bool verbose)
{
	char HidCerberusState = -1;

	HidCerberusState = GetServiceState(L"HidCerberus.Srv");

	if (verbose)
		switch (HidCerberusState)
		{
		case 0: { echo(L"HidCerberus service is uninstalled"); break; }
		case 1: { echo(L"HidCerberus service is stopped"); break; }				//SERVICE_STOPPED
		case 2: { echo(L"HidCerberus service is starting"); break; }			//SERVICE_START_PENDING
		case 3: { echo(L"HidCerberus service is stopping"); break; }			//SERVICE_STOP_PENDING
		case 4: { echo(L"HidCerberus service is running"); break; }				//SERVICE_RUNNING
		case 5: { echo(L"HidCerberus service is about to continue"); break; }	//SERVICE_CONTINUE_PENDING
		case 6: { echo(L"HidCerberus service is pausing"); break; }				//SERVICE_PAUSE_PENDING
		case 7: { echo(L"HidCerberus service is paused"); break; }				//SERVICE_PAUSED
		default: { echo(L"HidCerberus service state unknown"); }
		}

	return HidCerberusState;
}

BOOL Guardian::HidCerberusInstall(bool verbose)
{
	if (HidCerberusState() > 0)
	{
		if (verbose)
			echo(L"HidCerberus service is already installed");
		return TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName;

	if (ExtractEmbededResource(installpath, IDR_HIDCERBERUS_ZIP, true))
	{
		std::wstring exepath = installpath + L"/HidCerberus/HidCerberus.exe";

		if (verbose)
		{
			echo(L"Install HidCerberus service at extracted:");
			echo(exepath.c_str());
		}
		LPWSTR exepathtmp = (LPWSTR)(LPCWSTR)exepath.c_str();
		if (ServiceInstall(L"HidCerberus.Srv", exepathtmp, SERVICE_WIN32_OWN_PROCESS, verbose))
		{
			if (!verbose)
				echo(L"HidCerberus service installed");
			return TRUE;
		}
	}
	if (verbose)
		echo(L"ERROR: HidCerberus service not installed");

	return FALSE;
}

BOOL Guardian::HidCerberusUninstall(bool verbose)
{
	BOOL HidCerberusUninstall = FALSE;

	if (HidCerberusState() > 0)
	{
		if (ServiceDelete(L"HidCerberus.Srv", verbose))
		{
			if (verbose)
				echo(L"HidCerberus service is uninstalled");
			HidCerberusUninstall = TRUE;
		}
		else
			echo(L"ERROR: HidCerberus service uninstalation failed");
	}
	else
	{
		if (verbose)
			echo(L"HidCerberus service is already uninstalled");
		HidCerberusUninstall = TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\HidCerberus\0\0";
	std::filesystem::remove_all(installpath);

	std::wstring prfdirpath = PrfPath() + L"/" + tape.ProgramFilesDirName;
	prfdirpath = ReplaceInString(prfdirpath, L"\\", '/');
	RemoveDirectoryW(prfdirpath.c_str());

	return HidCerberusUninstall;
}

BOOL Guardian::HidCerberusStart(bool verbose)
{
	return ServiceStart(L"HidCerberus.Srv", verbose);
}

BOOL Guardian::HidCerberusStop(bool verbose)
{
	return ServiceStop(L"HidCerberus.Srv", verbose);
}

BOOL Guardian::WhitelistDs2vJoy()
{
	int pid = _getpid();

	if (pid != 0 && HidCerberusState() == 4)
	{
		if (WhitelistByPID(pid))
		{
			ProcessPIDs.push_back(pid);
			echo(L"Added to Guardian: Ds2vJoy (%u)", pid);

			return TRUE;
		}
	}

	return FALSE;
}

BOOL Guardian::WhitelistByPID(int pid)
{
	if (pid != 0 && HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "whitelist/add/" + std::to_string(pid));
		const http::Response response = request.send("GET", "", { "Content-Type: application/x-www-form-urlencoded" }, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Guardian::RemoveWhitelistByPID(int pid)
{
	if (pid != 0 && HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "whitelist/remove/" + std::to_string(pid));
		const http::Response response = request.send("GET", "", { "Content-Type: application/x-www-form-urlencoded" }, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

BOOL Guardian::PurgeWhitelist()
{
	if (HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "whitelist/purge");
		const http::Response response = request.send("GET", "", { "Content-Type: application/x-www-form-urlencoded" }, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

void Guardian::WhitelistByExeName(std::wstring ProcessExeName)
{
	if (HidCerberusState() == 4)
	{
		WCHAR* AAProcessName;
		DWORD AllProcessesPIDs[1024], MemoryNeeded;

		EnumProcesses(AllProcessesPIDs, sizeof(AllProcessesPIDs), &MemoryNeeded);
		int NumberOfProcesses = MemoryNeeded / sizeof(DWORD);

		for (int i = 0; i < NumberOfProcesses; i++)
		{
			if (AllProcessesPIDs[i] != 0)
			{
				AAProcessName = GetExeNameByPID(AllProcessesPIDs[i]);
				if (AAProcessName == ProcessExeName)
				{
					if (!(std::find(ProcessPIDs.begin(), ProcessPIDs.end(), AllProcessesPIDs[i]) != ProcessPIDs.end()))
					{
						if (WhitelistByPID((int)AllProcessesPIDs[i]))
						{
							ProcessPIDs.push_back((int)AllProcessesPIDs[i]);
							echo(L"Added to Guardian: %s (%u)", ProcessExeName.c_str(), AllProcessesPIDs[i]);
						}
					}
				}
			}
		}
	}
}

void Guardian::RemoveWhitelistByExeName(std::wstring ProcessExeName)
{
	if (HidCerberusState() == 4)
	{
		WCHAR* AAProcessName;
		DWORD AllProcessesPIDs[1024], MemoryNeeded;

		EnumProcesses(AllProcessesPIDs, sizeof(AllProcessesPIDs), &MemoryNeeded);
		int NumberOfProcesses = MemoryNeeded / sizeof(DWORD);

		for (int i = 0; i < NumberOfProcesses; i++)
		{
			if (AllProcessesPIDs[i] != 0)
			{
				AAProcessName = GetExeNameByPID(AllProcessesPIDs[i]);
				if (AAProcessName == ProcessExeName)
				{
					while (std::find(ProcessPIDs.begin(), ProcessPIDs.end(), AllProcessesPIDs[i]) != ProcessPIDs.end())
					{
						std::vector<int>::iterator pos = std::find(ProcessPIDs.begin(), ProcessPIDs.end(), AllProcessesPIDs[i]);
						ProcessPIDs.erase(pos);
					}
					if (RemoveWhitelistByPID((int)AllProcessesPIDs[i]))
						echo(L"Removed from Guardian: %s (%u)", ProcessExeName.c_str(), AllProcessesPIDs[i]);
				}
			}
		}
	}
}

BOOL Guardian::BlacklistDevice(std::wstring device)
{
	if (device != L"" && HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "affected/add/");
		std::map<std::string, std::string> parameters = { {"hwids", rws2s(device)} };
		const http::Response response = request.send("POST", parameters, {"Content-Type: application/x-www-form-urlencoded"}, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

BOOL Guardian::RemoveBlacklistDevice(std::wstring device)
{
	if (device != L"" && HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "affected/remove/");
		std::map<std::string, std::string> parameters = { {"hwids", rws2s(device)} };
		const http::Response response = request.send("POST", parameters, {"Content-Type: application/x-www-form-urlencoded"}, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

std::wstring Guardian::GetBlacklist()
{
	if (HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "/affected/get");
		const http::Response response = request.send("GET", "", { "Content-Type: application/x-www-form-urlencoded" }, ms);

		std::string tmp = { response.body.begin(), response.body.end() };
		return rs2ws(tmp);
	}

	return L"";
}

void Guardian::AffectedList()
{
	std::wstring affected = GetBlacklist();

	std::wstring::size_type pos = std::wstring(tape.getHID(1)).find_last_of(L"\\/");
	pid1_affected = FindInString(affected, std::wstring(tape.getHID(1)).substr(pos + 1));

	pos = std::wstring(tape.getHID(2)).find_last_of(L"\\/");
	pid2_affected = FindInString(affected, std::wstring(tape.getHID(2)).substr(pos + 1));

	pos = std::wstring(tape.getHID(3)).find_last_of(L"\\/");
	pid3_affected = FindInString(affected, std::wstring(tape.getHID(3)).substr(pos + 1));
}

BOOL Guardian::PurgeBlacklist()
{
	if (HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "affected/purge");
		const http::Response response = request.send("GET", "", { "Content-Type: application/x-www-form-urlencoded" }, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

BOOL Guardian::RestartDevices(bool verbose)
{
	bool result = FALSE;
	if (tape.dsHID1Enable)
		result = result || RestartDevice(rws2s(tape.dsHID1), true);
	if (tape.dsHID2Enable)
		result = result || RestartDevice(rws2s(tape.dsHID2), true);
	if (tape.dsHID3Enable)
		result = result || RestartDevice(rws2s(tape.dsHID3), true);

	return result;
}

BOOL Guardian::RestartDevice(std::string device, bool verbose)
{
	if (device != "")
	{
		std::wstring devconpath = L"Devcon.exe restart \"" + rs2ws(device) + L"\"";
		std::wstring devconcmd = LaunchCmd(devconpath.c_str());

		if (FindInString(devconcmd, L"Restarted"))
		{
			if (verbose)
				echo(L"Device restarted");

			return TRUE;
		}
		else if (FindInString(devconcmd, L"Requires reboot"))
		{
			if (verbose)
				echo(L"Requires reboot, unplug & plug device instead");

			return TRUE;
		}
		else if (FindInString(devconcmd, L"No matching devices found"))
			return FALSE;
	}

	if (verbose)
		echo(L"Device restart failed");

	return FALSE;
}
