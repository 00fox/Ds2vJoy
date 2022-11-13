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

		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
		{
			if (tape.dsHID1Enable && tape.dsHID[0] && pid1_affected)
			{
				RemoveBlacklistDevice(tape.dsHID[0]);
				DeviceRestart(L"HID", tape.dsHID[0]);
			}
			if (tape.dsHID2Enable && tape.dsHID[1] && pid2_affected)
			{
				RemoveBlacklistDevice(tape.dsHID[1]);
				DeviceRestart(L"HID", tape.dsHID[1]);
			}
			if (tape.dsHID3Enable && tape.dsHID[2] && pid3_affected)
			{
				RemoveBlacklistDevice(tape.dsHID[2]);
				DeviceRestart(L"HID", tape.dsHID[2]);
			}
		}
	}
}

void Guardian::Init()
{
	if (tape.GuardianActive && !tape.GuardianPaused)
	{
		WhitelistInit();
		BlacklistInit(-2);
	}
}

const WCHAR* Guardian::GuardianButtons()
{
	return GuardianButtonsString.c_str();
}

void Guardian::GuardianButtonsComputString()
{
	GuardianButtonsString = I18N.GuardianButtonsString;
	for (int i = 0; i < ProcessPIDs.size(); i++)
		GuardianButtonsString = GuardianButtonsString + L" " + std::to_wstring(ProcessPIDs[i]);
}

void Guardian::AllDevicesRestart()
{
	for (int i = 0; i < 3; i++)
		DeviceRestart(L"HID", tape.dsHID[i]);

	return;
}

void Guardian::BlacklistInit(int hid)
{
	if ((tape.GuardianActive && !tape.GuardianPaused && tape.RemoveBlacklist) || hid)
	{
		AffectedList();

		bool torestart = false;
		if (!tape.CallbackPaused && hid > -2)
		{
			if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
				torestart = true;
		}
		else
			hid = -1;

		if (tape.dsHID[0] && (hid == -1 || hid == 0 || hid == 1))
		{
			if (tape.dsHID1Enable && !tape.GuardianPaused)
			{
				if (tape.GuardianActive && !pid1_affected)
				{
					RemoveBlacklistDevice(tape.dsHID[0]);
					BlacklistDevice(tape.dsHID[0]);
				}
				else if (!tape.GuardianActive && pid1_affected)
					RemoveBlacklistDevice(tape.dsHID[0]);
			}
			else if (pid1_affected)
				RemoveBlacklistDevice(tape.dsHID[0]);
			DeviceRestart(L"HID", tape.dsHID[0]);
		}
		if (tape.dsHID[1] && (hid == -1 || hid == 0 || hid == 2))
		{
			if (tape.dsHID2Enable && !tape.GuardianPaused)
			{
				if (tape.GuardianActive && !pid2_affected)
				{
					RemoveBlacklistDevice(tape.dsHID[1]);
					BlacklistDevice(tape.dsHID[1]);
				}
				else if (!tape.GuardianActive && pid2_affected)
					RemoveBlacklistDevice(tape.dsHID[1]);
			}
			else if (pid2_affected)
				RemoveBlacklistDevice(tape.dsHID[1]);
			DeviceRestart(L"HID", tape.dsHID[1]);
		}
		if (tape.dsHID[2] && (hid == -1 || hid == 0 || hid == 3))
		{
			if (tape.dsHID3Enable && !tape.GuardianPaused)
			{
				if (tape.GuardianActive && !pid3_affected)
				{
					RemoveBlacklistDevice(tape.dsHID[2]);
					BlacklistDevice(tape.dsHID[2]);
				}
				else if (!tape.GuardianActive && pid3_affected)
					RemoveBlacklistDevice(tape.dsHID[2]);
			}
			else if (pid3_affected)
				RemoveBlacklistDevice(tape.dsHID[2]);
			DeviceRestart(L"HID", tape.dsHID[2]);
		}

		if (torestart) 
			PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);
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
	ProcessPIDs = { };
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

char Guardian::GetHidGState()
{
	return HidGState;
}

char Guardian::GetHidCState()
{
	return HidCState;
}

char Guardian::GuardianState(bool verbose)
{
	return GetDeviceState(L"ROOT\\SYSTEM", L"Root\\HidGuardian", verbose);
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
		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
		{
			std::wstring infpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\HidGuardian\\HidGuardian.inf";
			InstallDriverByHwId(infpath, L"Root\\HidGuardian");
		}

		UpperClassFilter(L"HIDClass", L"-HidGuardian");
		PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);

		switch (GuardianState())
		{
		case DRIVER_STATE_ACTIVE:
		{
			echo(I18N.Guardian_driver_installed);
			return TRUE;
		}
		case DRIVER_STATE_DISABLED:
		{
			echo(I18N.Guardian_driver_installed);
			return TRUE;
		}
		}
	}
	echo(I18N.Guardian_driver_instalation_failed);

	return FALSE;
}

BOOL Guardian::GuardianUninstall(bool verbose)
{
	PurgeBlacklist();
	switch (GuardianState())
	{
	case DRIVER_STATE_NOTPRESENT:
	{
		if (verbose)
			echo(L"HidGuardian driver is already uninstalled");
		return TRUE;
	}
	case DRIVER_STATE_ACTIVE:
	case DRIVER_STATE_DISABLED:
	{
		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
			RemoveDriverByHwId(L"ROOT\\SYSTEM", L"Root\\HidGuardian", verbose);

		UpperClassFilter(L"HIDClass", L"!HidGuardian");
		PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);

		if (GuardianState() == DRIVER_STATE_NOTPRESENT)
		{
			std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\HidGuardian\0\0";
			std::filesystem::remove_all(installpath);

			std::wstring prfdirpath = PrfPath() + L"/" + tape.ProgramFilesDirName;
			prfdirpath = ReplaceInString(prfdirpath, L"\\", '/');
			RemoveDirectoryW(prfdirpath.c_str());

			echo(I18N.Guardian_driver_uninstalled);
			return TRUE;
		}
		else
		{
			if (verbose)
				echo(I18N.Guardian_driver_uninstalation_failed);
			return FALSE;
		}
	}
	default:
	{
		if (verbose)
		{
			echo(L"HidGuardian driver has a problem");
			GetDeviceError(L"ROOT\\SYSTEM", L"Root\\HidGuardian", true);
		}
		return FALSE;
	}
	}
}

BOOL Guardian::GuardianEnable(bool verbose)
{
	BOOL result = SetDeviceState(L"ROOT\\SYSTEM", L"Root\\HidGuardian", DICS_ENABLE, verbose);

	UpperClassFilter(L"HIDClass", L"-HidGuardian");

	return result;
}

BOOL Guardian::GuardianDisable(bool verbose)
{
	BOOL result = SetDeviceState(L"ROOT\\SYSTEM", L"Root\\HidGuardian", DICS_DISABLE, verbose);
	
	UpperClassFilter(L"HIDClass", L"!HidGuardian");

	return result;
}

char Guardian::HidCerberusState(bool verbose)
{
	char HidCerberusState = -1;

	HidCerberusState = GetServiceState(WCHARI(L"HidCerberus.Srv"));

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
		if (ServiceInstall(WCHARI(L"HidCerberus.Srv"), exepathtmp, SERVICE_WIN32_OWN_PROCESS, verbose))
		{
			echo(I18N.Cerberus_service_installed);
			return TRUE;
		}
	}
	echo(I18N.Cerberus_service_instalation_failed);

	return FALSE;
}

BOOL Guardian::HidCerberusUninstall(bool verbose)
{
	PurgeBlacklist();
	BOOL HidCerberusUninstall = FALSE;

	if (HidCerberusState() > 0)
	{
		if (ServiceDelete(WCHARI(L"HidCerberus.Srv"), verbose))
		{
			echo(I18N.Cerberus_service_uninstalled);
			HidCerberusUninstall = TRUE;
		}
		else
			echo(I18N.Cerberus_service_uninstalation_failed);
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
	return ServiceStart(WCHARI(L"HidCerberus.Srv"), verbose);
}

BOOL Guardian::HidCerberusStop(bool verbose)
{
	return ServiceStop(WCHARI(L"HidCerberus.Srv"), verbose);
}

BOOL Guardian::WhitelistDs2vJoy()
{
	tape.Ds2vJoyPID = _getpid();

	if (tape.Ds2vJoyPID != 0 && HidCerberusState() == 4)
	{
		if (WhitelistByPID(tape.Ds2vJoyPID))
		{
			ProcessPIDs.push_back(tape.Ds2vJoyPID);
			tape.DsvJoyAddedToGuardian = true;
			GuardianButtonsComputString();

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
							echo(I18N.Guardian_Added_to_Guardian, ProcessExeName.c_str(), AllProcessesPIDs[i]);
							GuardianButtonsComputString();
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
					{
						echo(I18N.Guardian_Removed_from_Guardian, ProcessExeName.c_str(), AllProcessesPIDs[i]);
						GuardianButtonsComputString();
					}
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

	std::wstring::size_type pos = std::wstring(tape.dsHID[0]).find_last_of(L"\\/");
	pid1_affected = FindInString(affected, std::wstring(tape.dsHID[0]).substr(pos + 1));

	pos = std::wstring(tape.dsHID[1]).find_last_of(L"\\/");
	pid2_affected = FindInString(affected, std::wstring(tape.dsHID[1]).substr(pos + 1));

	pos = std::wstring(tape.dsHID[2]).find_last_of(L"\\/");
	pid3_affected = FindInString(affected, std::wstring(tape.dsHID[2]).substr(pos + 1));
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
		result = result || DeviceRestart(L"HID", tape.dsHID[0]);
	if (tape.dsHID2Enable)
		result = result || DeviceRestart(L"HID", tape.dsHID[1]);
	if (tape.dsHID3Enable)
		result = result || DeviceRestart(L"HID", tape.dsHID[2]);

	return result;
}
