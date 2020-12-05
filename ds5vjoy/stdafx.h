// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")


//DS5.cpp
#include <process.h>
#include <Dbt.h>
#include <Hidsdi.h>
#pragma comment(lib, "hid.lib")
#include <BluetoothAPIs.h>
#pragma comment(lib, "Bthprops")
#include <SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")
#include <mutex>
#include <condition_variable>

//log.cpp
#include <deque>
#include <mutex>
//keymap mapping
#include <vector>
//RapidFire
#include <map>
//tasktray
#include <Shellapi.h>

//vjoy
#include "public.h"
#include "vjoyinterface.h"
#pragma comment(lib, "vJoyInterface.lib")

//LogPrintf
//#include "Log.h"
//g_settings
//#include "Settings.h"

//SettingDlg
#include <Commdlg.h>
