#pragma once
#include "targetver.h"

// Windows, Exclude unused parts from the header.
#define WIN32_LEAN_AND_MEAN
//#include <windows.h>

// C runtime header file
#include <atlbase.h>					//A2T T2A W2T T2W A2W W2A
#include <fstream>						//<<
//#include <codecvt>					//convert string wstring
//#include <iostream>					//std::cout & std::err
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <stdio.h>
//#include <iomanip>
//#include <string>
//#include <locale>
//#include <chrono>						//HTTPRequest timeout
//#include <psapi.h>					//EnumDeviceDrivers & GetDeviceDriverBaseName

#include <filesystem>					//filesystem
using namespace std::filesystem;
#include <condition_variable>			//mutex

// any additional headers needed for your program
//#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
//#pragma comment(lib, "comsuppw.lib")	//_bstr_t wchar to char
//#include <process.h>
//#include <Dbt.h>
//#include <comdef.h >
//#include <comutil.h>

#include "Language.h"
#include "resource.h"

#include <Hidsdi.h>						//DS
#pragma comment(lib, "hid.lib")
#include <BluetoothAPIs.h>
#pragma comment(lib, "Bthprops")
#include <SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")

#include "Log.h"						//Log
#include <Commdlg.h>					//SettingDlg
#include "time.h"						//Mapping & dsButton
//#include <vector>						//Keymap
//#include <map>						//RapidFire
#include <psapi.h>						//Guardian (EnumProcesses, EnumProcessModules & GetModuleBaseName)
#include <Shellapi.h>					//Tasktray

#include "HTTPRequest.hpp"				//HTTPRequest (https://github.com/elnormous/HTTPRequest)
#pragma comment(lib, "Ws2_32.lib")

//#include <winioctl.h>					//vJoyInterface
#include "vJoyInterface.h"				//vJoy
#pragma comment(lib, "vJoyInterface.lib")

//#include <Xinput.h>					//Xinput
//#pragma comment(lib, "Xinput.lib")

#include "ViGEm/Client.h"				//ViGem
#pragma comment(lib, "ViGEmClient.lib")

#include "WindowsTools.h"				//WindowsTools
#include "Settings.h"					//Settings
