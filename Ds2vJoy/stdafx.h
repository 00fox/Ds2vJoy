#pragma once
#include "targetver.h"
// Windows, Exclude unused parts from the header.
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
//#include <windows.h>
#pragma warning(disable : 4244)

// C runtime header file
#include <atlbase.h>					//A2T T2A W2T T2W A2W W2A
//#include <fstream>					//<<
#include "windowsx.h"
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
#include <sstream>						//Settings stringstream
#include <future>						// std::async, std::future
#include <set>

#include <filesystem>					//filesystem
#include <condition_variable>			//mutex
#include <mmeapi.h>						//Sound control
#pragma comment (lib, "winmm.lib")

// any additional headers needed for your program
//#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
//#pragma comment(lib, "comsuppw.lib")	//_bstr_t wchar to char
//#include <process.h>
//#include <Dbt.h>
//#include <comdef.h >
//#include <comutil.h>

#include "Resource.h"
#include "Language.h"

#include <Hidsdi.h>						//DS
#pragma comment(lib, "hid.lib")
#include <BluetoothAPIs.h>
#pragma comment(lib, "Bthprops")
#include <SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")

#include "Crc32/Crc32.h"				//Source
#include "LogDlg.h"						//Log
#include <Commdlg.h>					//SettingDlg
#include "time.h"						//Mapping & dsButton
#include <bitset>						//MappingDlg
//#include <vector>						//Keymap
//#include <map>						//RapidFire
#include <psapi.h>						//Guardian (EnumProcesses, EnumProcessModules & GetModuleBaseName)
#include <Shellapi.h>					//Tasktray

#include "Zip Utils/unzip.h"
#include "CPULimiter/CPULimiter.h"

#include "HTTPRequest/HTTPRequest.hpp"//HTTPRequest (https://github.com/elnormous/HTTPRequest)
#pragma comment(lib, "Ws2_32.lib")

//#include <winioctl.h>					//vJoyInterface
#include "vJoy/vJoyInterface.h"			//vJoy
#pragma comment(lib, "vJoy/vJoyInterface.lib")

//#include <Xinput.h>					//Xinput
//#pragma comment(lib, "Xinput.lib")

//#include "magnification.h"
//#pragma comment(lib, "Magnification.lib")

#include "ViGEm/Client.h"				//ViGem
#pragma comment(lib, "ViGEm/ViGEmClient.lib")

#include "Settings.h"					//Settings
#include "WindowsTools.h"				//WindowsTools

#pragma warning(default : 4244)