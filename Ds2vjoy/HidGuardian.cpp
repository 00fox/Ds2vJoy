#include "stdafx.h"
#include "HidGuardian.h"
#include "unzip.h"
#include "Ds2vJoy.h"

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

BOOL Guardian::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	if (tape.GuardianActive && !tape.GuardianPaused)
	{
		WhitelistInit();
		BlacklistInit(-1);
	}

	return TRUE;
}

void Guardian::AllDevicesRestart()
{
	for (int i = 1; i < 4; i++)
		if (tape.getHID(i) != "")
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
					if (tape.getHID(1) != "")
						DeviceRestart(tape.getHID(1));
				}
				else if (!tape.GuardianActive && pid1_affected)
				{
					RemoveBlacklistDevice(tape.getHID(1));
					Sleep(100);
					if (tape.getHID(1) != "")
						DeviceRestart(tape.getHID(1));
				}
			}
			else if (pid1_affected)
			{
				RemoveBlacklistDevice(tape.getHID(1));
				Sleep(100);
				if (tape.getHID(1) != "")
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
					if (tape.getHID(2) != "")
						DeviceRestart(tape.getHID(2));
				}
				else if (!tape.GuardianActive && pid2_affected)
				{
					RemoveBlacklistDevice(tape.getHID(2));
					Sleep(100);
					if (tape.getHID(2) != "")
						DeviceRestart(tape.getHID(2));
				}
			}
			else if (pid2_affected)
			{
				RemoveBlacklistDevice(tape.getHID(2));
				Sleep(100);
				if (tape.getHID(2) != "")
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
					if (tape.getHID(3) != "")
						DeviceRestart(tape.getHID(3));
				}
				else if (!tape.GuardianActive && pid3_affected)
				{
					RemoveBlacklistDevice(tape.getHID(3));
					Sleep(100);
					if (tape.getHID(3) != "")
						DeviceRestart(tape.getHID(3));
				}
			}
			else if (pid3_affected)
			{
				RemoveBlacklistDevice(tape.getHID(3));
				Sleep(100);
				if (tape.getHID(3) != "")
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
	int GuardianState = -1;

	std::string devconpath = "Devcon.exe status Root\\HidGuardian";
	std::string devconcmd = LaunchCmd(devconpath.c_str());

	if (FindInStdString(devconcmd, "No matching devices found"))
		GuardianState = 0;
	if (FindInStdString(devconcmd, "Driver is running"))
		GuardianState = 1;
	if (FindInStdString(devconcmd, "Device is disabled"))
		GuardianState = 2;

	if (verbose)
		switch (GuardianState)
		{
		case 0:
			echo(L"HidGuardian driver is uninstalled");
			break;
		case 1:
			echo(L"HidGuardian driver is runing");
			break;
		case 2:
			echo(L"HidGuardian driver is disabled");
			break;
		default:
			echo(L"HidGuardian state unknown");
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

	std::wstring installpath = PrfPathW() + L"\\" + ProgramFilesDirName;

	if (ExtractEmbededResource(installpath, IDR_HIDGUARDIAN_ZIP, true))
	{
		std::string devconpath = "Devcon.exe install \"" + PrfPath() + "\\" + rws2s(ProgramFilesDirName) + "\\HidGuardian\\HidGuardian.inf\" Root\\HidGuardian";
		LaunchCmd(devconpath.c_str());

		devconpath = "Devcon.exe classfilter HIDClass upper -HidGuardian";
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
			std::string devconpath = "Devcon.exe remove Root\\HidGuardian";
			LaunchCmd(devconpath.c_str());

			devconpath = "Devcon.exe classfilter HIDClass upper !HidGuardian";
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

	std::wstring installpath = PrfPathW() + L"\\" + ProgramFilesDirName + L"\\HidGuardian\0\0";
	remove_all(installpath);

	std::wstring prfdirpath = PrfPathW() + L"/" + ProgramFilesDirName;
	prfdirpath = ReplaceInStdwString(prfdirpath, "\\", '/');
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

	std::string devconpath = "Devcon.exe enable Root\\HidGuardian";
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

	std::string devconpath = "Devcon.exe disable Root\\HidGuardian";
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
	int HidCerberusState = -1;

	HidCerberusState = GetServiceState(L"HidCerberus.Srv");

	if (verbose)
		switch (HidCerberusState)
		{
		case 0:
			echo(L"HidCerberus service is uninstalled");
			break;
		case 1:					//SERVICE_STOPPED
			echo(L"HidCerberus service is stopped");
			break;
		case 2:					//SERVICE_START_PENDING
			echo(L"HidCerberus service is starting");
			break;
		case 3:					//SERVICE_STOP_PENDING
			echo(L"HidCerberus service is stopping");
			break;
		case 4:					//SERVICE_RUNNING
			echo(L"HidCerberus service is running");
			break;
		case 5:					//SERVICE_CONTINUE_PENDING
			echo(L"HidCerberus service is about to continue");
			break;
		case 6:					//SERVICE_PAUSE_PENDING
			echo(L"HidCerberus service is pausing");
			break;
		case 7:					//SERVICE_PAUSED
			echo(L"HidCerberus service is paused");
			break;
		default:
			echo(L"HidCerberus service state unknown");
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

	std::wstring installpath = PrfPathW() + L"\\" + ProgramFilesDirName;

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

	std::wstring installpath = PrfPathW() + L"\\" + ProgramFilesDirName + L"\\HidCerberus\0\0";
	remove_all(installpath);

	std::wstring prfdirpath = PrfPathW() + L"/" + ProgramFilesDirName;
	prfdirpath = ReplaceInStdwString(prfdirpath, "\\", '/');
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
		TCHAR* AAProcessName;
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
		TCHAR* AAProcessName;
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
					if (std::find(ProcessPIDs.begin(), ProcessPIDs.end(), AllProcessesPIDs[i]) != ProcessPIDs.end())
						auto removed = remove(ProcessPIDs.begin(), ProcessPIDs.end(), (int)AllProcessesPIDs[i]);
					if (RemoveWhitelistByPID((int)AllProcessesPIDs[i]))
						echo(L"Removed from Guardian: %s (%u)", ProcessExeName.c_str(), AllProcessesPIDs[i]);
				}
			}
		}
	}
}

BOOL Guardian::BlacklistDevice(std::string device)
{
	if (device != "" && HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "affected/add/");
		std::map<std::string, std::string> parameters = { {"hwids", device} };
		const http::Response response = request.send("POST", parameters, {"Content-Type: application/x-www-form-urlencoded"}, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

BOOL Guardian::RemoveBlacklistDevice(std::string device)
{
	if (device != "" && HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "affected/remove/");
		std::map<std::string, std::string> parameters = { {"hwids", device} };
		const http::Response response = request.send("POST", parameters, {"Content-Type: application/x-www-form-urlencoded"}, ms);

		if (std::string(response.body.begin(), response.body.end()) == "[\"OK\"]")
			return TRUE;
	}

	return FALSE;
}

std::string Guardian::GetBlacklist()
{
	if (HidCerberusState() == 4)
	{
		std::chrono::milliseconds ms{ 100 };
		http::Request request(GuardianUrl + "/affected/get");
		const http::Response response = request.send("GET", "", { "Content-Type: application/x-www-form-urlencoded" }, ms);

		return { response.body.begin(), response.body.end() };
	}

	return "";
}

void Guardian::AffectedList()
{
	std::string affected = GetBlacklist();

	std::string::size_type pos = std::string(tape.getHID(1)).find_last_of("\\/");
	pid1_affected = FindInStdString(affected, std::string(tape.getHID(1)).substr(pos + 1));

	pos = std::string(tape.getHID(2)).find_last_of("\\/");
	pid2_affected = FindInStdString(affected, std::string(tape.getHID(2)).substr(pos + 1));

	pos = std::string(tape.getHID(3)).find_last_of("\\/");
	pid3_affected = FindInStdString(affected, std::string(tape.getHID(3)).substr(pos + 1));
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
		std::string devconpath = "Devcon.exe restart \"" + device + "\"";
		std::string devconcmd = LaunchCmd(devconpath.c_str());

		if (FindInStdString(devconcmd, "Restarted"))
		{
			if (verbose)
				echo(L"Device restarted");

			return TRUE;
		}
		else if (FindInStdString(devconcmd, "Requires reboot"))
		{
			if (verbose)
				echo(L"Requires reboot, unplug & plug device instead");

			return TRUE;
		}
		else if (FindInStdString(devconcmd, "No matching devices found"))
			return FALSE;
	}

	if (verbose)
		echo(L"Device restart failed");

	return FALSE;
}

/*

Example of GET request
#include "HTTPRequest.hpp"

try
{
	// you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
	http::Request request("http://test.com/test");

	// send a get request
	const http::Response response = request.send("GET");
	std::cout << std::string(response.body.begin(), response.body.end()) << '\n'; // print the result
}
catch (const std::exception& e)
{
	std::cerr << "Request failed, error: " << e.what() << '\n';
}


Example of POST request
#include "HTTPRequest.hpp"

try
{
	http::Request request("http://test.com/test");
	// send a post request
	const http::Response response = request.send("POST", "foo=1&bar=baz", {
		"Content-Type: application/x-www-form-urlencoded"
	});
	std::cout << std::string(response.body.begin(), response.body.end()) << '\n'; // print the result
}
catch (const std::exception& e)
{
	std::cerr << "Request failed, error: " << e.what() << '\n';
}


Example of POST request by passing a map of parameters
#include "HTTPRequest.hpp"

try
{
	http::Request request("http://test.com/test");
	// pass parameters as a map
	std::map<std::string, std::string> parameters = {{"foo", "1"}, {"bar", "baz"}};
	const http::Response response = request.send("POST", parameters, {
		"Content-Type: application/x-www-form-urlencoded"
	});
	std::cout << std::string(response.body.begin(), response.body.end()) << '\n'; // print the result
}
catch (const std::exception& e)
{
	std::cerr << "Request failed, error: " << e.what() << '\n';
}

To set a timeout for HTTP requests, pass std::chrono::duration as a last parameter to send().
A negative duration (default) passed to send() disables timeout.


//Example 1 - Create a Zip File from Existing Files
HZIP hz = CreateZip("simple1.zip", 0);
ZipAdd(hz, "znsimple.bmp", "simple.bmp");
ZipAdd(hz, "znsimple.txt", "simple.txt");
CloseZip(hz);

//Example 2 - Unzip a Zip File Using the Names It Has Inside It
HZIP hz = OpenZip("\\simple1.zip",0);
ZIPENTRY ze; GetZipItem(hz,-1,&ze); int numitems=ze.index;
// -1 gives overall information about the zipfile
for (int zi=0; zi<numitems; zi++)
{ ZIPENTRY ze; GetZipItem(hz,zi,&ze); // fetch individual details
  UnzipItem(hz, zi, ze.name);		 // e.g. the item's name.
}
CloseZip(hz);

//Example 3- Unzip from Resource Directly into Memory
//This technique is useful for small games, where you want to keep all resources bundled up inside the executable, but restricting the size.
//Suppose we used a .rc with 1 RCDATA "file.zip" to embed the zip file as a resource.
HRSRC hrsrc = FindResource(hInstance,MAKEINTRESOURCE(1),RT_RCDATA);
HANDLE hglob = LoadResource(hInstance,hrsrc);
void *zipbuf = LockResource(hglob);
unsigned int ziplen = SizeofResource(hInstance,hrsrc);
hz = OpenZip(zipbuf, ziplen, 0);
ZIPENTRY ze; int i; FindZipItem(hz,"sample.jpg",true,&i,&ze);
// that lets us search for an item by filename.
// Now we unzip it to a membuffer.
char *ibuf = new char[ze.unc_size];
UnzipItem(hz,i, ibuf, ze.unc_size);
//...
delete[] ibuf;
CloseZip(hz);
// note: no need to free resources obtained through Find/Load/LockResource

//Example 4 - Unzip Chunk by Chunk to a membuffer
//Normally when you call UnzipItem(...), it gives the return-code ZR_OK. But if you gave it too small a buffer so that it couldn't fit it all in, then it returns ZR_MORE.
char buf[1024]; ZRESULT zr=ZR_MORE; unsigned long totsize=0;
while (zr==ZR_MORE)
{ zr = UnzipItem(hz,i, buf,1024);
  unsigned long bufsize=1024; if (zr==ZR_OK) bufsize=ze.unc_size-totsize;
  ... maybe write the buffer to a disk file here
  totsize+=bufsize;
}

ZRESULT RemoveFileFromZip(const TCHAR *zip, const TCHAR *name);
ZRESULT AddFileToZip(const TCHAR *zip, const TCHAR *name, const TCHAR *fn);
// eg. AddFileToZip("c:\\archive.zip","znsimple.txt","c:\\docs\\file.txt");
// If the zipfile already contained that thing (case-insensitive), it is removed.
// These two functions are defined in "modify.cpp"
*/