#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used parts from the header
#pragma warning(disable : 4244)

#define OEMRESOURCE
//////////////////////////////////////////////////////////////////////
//#include <windows.h>
#include "windowsx.h"
//#include <commctrl.h>
//#pragma comment(lib, "comctl32.lib")
#include "Resource.h"
#include <atlbase.h>			//A2T T2A W2T T2W A2W W2A
#include <sstream>				//std+Settings stringstream
#include <variant>
#include "Language.h"
//////////////////////////////////////////////////////////////////////
#include <set>
#include <future>				// std::async, std::future
#include <filesystem>			//filesystem
#include <condition_variable>	//mutex
//#include <fstream>			//<<
//#include <codecvt>			//convert string wstring
//#include <iostream>			//std::cout & std::err
//#include <psapi.h>			//EnumDeviceDrivers & GetDeviceDriverBaseName
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <stdio.h>
//#include <iomanip>
//#include <string>
//#include <locale>
//#include <process.h>
//#include <Dbt.h>
//#include <comdef.h >
//#include <comutil.h>
////////////////////////////////////////////////////////////////////// Screenshot
#include <atlimage.h>
//#include <gdiplus.h>
////////////////////////////////////////////////////////////////////// Sound control
#include <mmeapi.h>
#pragma comment (lib, "winmm.lib")
////////////////////////////////////////////////////////////////////// Magnification
#include "magnification.h"
#pragma comment(lib, "Magnification.lib")
////////////////////////////////////////////////////////////////////// Zip Utils
#include "Zip Utils/unzip.h"
////////////////////////////////////////////////////////////////////// CPULimiter
#include "CPULimiter/CPULimiter.h"
////////////////////////////////////////////////////////////////////// HTTPRequest
#include "HTTPRequest/HTTPRequest.hpp"
#pragma comment(lib, "Ws2_32.lib")
////////////////////////////////////////////////////////////////////// DS
#include <Hidsdi.h>
#pragma comment(lib, "hid.lib")
#include <BluetoothAPIs.h>
#pragma comment(lib, "Bthprops")
#include <SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")
////////////////////////////////////////////////////////////////////// Source
#include "Crc32/Crc32.h"
////////////////////////////////////////////////////////////////////// DirectInput
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <dinputd.h>			// Preffered control panel joystick
#include <wrl/client.h>			//           "
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
////////////////////////////////////////////////////////////////////// XInput
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
////////////////////////////////////////////////////////////////////// vJoyInterface
//#include <winioctl.h>
////////////////////////////////////////////////////////////////////// vJoy
#include <Dbt.h>
#include <INITGUID.H>	// Definitions for controlling GUID initialization
#include <winioctl.h>
#include "vJoyInterface.h"
#include "vJoyDevice.h"
//#include "vJoy/public.h"
//#include "vJoy/vJoyInterface.h"
//#pragma comment(lib, "vJoy/vJoyInterface.lib")
////////////////////////////////////////////////////////////////////// vJoyConf
//#include "vJoy/hidtoken.h"
//#include "vJoy/hidusage.h"
//#include "vJoy/declarations.h"
////////////////////////////////////////////////////////////////////// Log
#include "LogDlg.h"
////////////////////////////////////////////////////////////////////// Settings
#include "Settings.h"
////////////////////////////////////////////////////////////////////// SettingDlg
#include <Commdlg.h>
////////////////////////////////////////////////////////////////////// Mapping & dsButton
#include "time.h"
////////////////////////////////////////////////////////////////////// MappingDlg
#include <bitset>
////////////////////////////////////////////////////////////////////// RapidFire
//#include <map>
////////////////////////////////////////////////////////////////////// ViGem
//#include "winres.h"
//#include <Windows.h>
//#include <SetupAPI.h>
//#include <initguid.h>
//#include <Dbghelp.h>
//#include <winioctl.h>
//#include <cstdlib>
//#include <climits>
//#include <vector>
//#include <algorithm>
//#include <thread>
//#include <functional>
//#include <limits.h>
#include "ViGEmClient.h"
//#pragma comment(lib, "ViGEm/ViGEmClient.lib")
////////////////////////////////////////////////////////////////////// Keymap
//#include <vector>
////////////////////////////////////////////////////////////////////// Guardian
#include <psapi.h>				// (EnumProcesses, EnumProcessModules & GetModuleBaseName)
////////////////////////////////////////////////////////////////////// ExplorerDlg
//#include "WebView2.h"
//#include "WebView2EnvironmentOptions.h"
//#pragma comment(lib, "WebView2Loader.dll.lib")
//#pragma comment(lib, "WebView2LoaderStatic.lib")
#include <DispatcherQueue.h>
#include <regex>
#include <ShObjIdl_core.h>
#include <pathcch.h>
////////////////////////////////////////////////////////////////////// Thumbnail
//#include "dwmapi.h"
//#pragma comment(lib, "Dwmapi.lib")
////////////////////////////////////////////////////////////////////// Tasktray
#include <Shellapi.h>
////////////////////////////////////////////////////////////////////// WindowsTools
#include "uxtheme.h"
#pragma comment (lib, "UxTheme.lib")
#include "cfgmgr32.h"
#include "devpkey.h"
#include "newdev.h"
#include "WindowsTools.h"

#pragma warning(default : 4244)