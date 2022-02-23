#include "stdafx.h"
#include "Language.h"

struct LANGSTRS I18N = { 0 };
/*

WCHAR* SetText(const WCHAR* txt)
{
	size_t tocopy = wcslen(txt) + 1;
	WCHAR* ret = new WCHAR[tocopy];
	wcscpy_s(ret, tocopy, txt);

	return ret;
}*/
void LoadLanguage()
{
	//setlocale(LC_ALL, ".UTF8");
	I18N.DS2VJOY											= WCHARI(IDS_DS2VJOY, L"DS2VJOY");
	I18N.APP_TITLE											= WCHARI(IDS_DS2VJOY, L"IDS_APP_TITLE");
	I18N.FailedParse										= WCHARI(L"Failed to parse %s");
	I18N.FailedRecv											= WCHARI(L"Failed to recv data from %s : %d");
	I18N.FailedSendCmd										= WCHARI(L"Failed to send command to %s : %d");
	I18N.FailedThread										= WCHARI(L"Failed to create thread");
	I18N.MBOX_Delete										= WCHARI(L"Are you sure you want to delete the selected item?");
	I18N.MBOX_ErrorWhileSaving								= WCHARI(L"Errors were detected while saving.\nNo changes were made.");
	I18N.MBOX_ErrTitle										= WCHARI(L"Error");
	I18N.MBOX_NoButtonSelected								= WCHARI(L"No button selected");
	I18N.BT_CRC												= WCHARI(L"BT received data with crc error: %d");
	I18N.BT_Size											= WCHARI(L"The size of the received data was not enough.");
	I18N.Change_Settings									= WCHARI(L"Reconnecting for change settings.");
	I18N.ConnectController									= WCHARI(L"Connect %s Serial %s");
	I18N.ConnectionStarted									= WCHARI(L"Connection started %s");
	I18N.DisconnectController								= WCHARI(L"Disconnect %s");
	I18N.Firmware											= WCHARI(L"Firmware Ver %02X%02X (%s)");
	I18N.FirmwareFail										= WCHARI(L"Cannot get firmware version");
	I18N.Log_Wait_ds										= WCHARI(L"Waiting for a valid DS device.");
	I18N.Log_Wait_vJoy										= WCHARI(L"Waiting for a valid vJoy device.");
	I18N.Registry_Added										= WCHARI(L"Startup value successfully added in Registry");
	I18N.Registry_Removed									= WCHARI(L"Startup value successfully removed from Registry");
	I18N.SkipController										= WCHARI(L"Skip %s Serial %s");
	I18N.Status_Wait										= WCHARI(L"waiting");
	I18N.TT_AppNotFound										= WCHARI(L"%s not found.");
	I18N.TT_ProfileChanged									= WCHARI(L"Profile changed to: %d");
	I18N.vJoy_acquire										= WCHARI(L"Acquired vJoy (ID:%d)");
	I18N.vJoy_busy											= WCHARI(L"vJoy (ID:%d) is busy");
	I18N.vJoy_cantuse										= WCHARI(L"Can not use vJoy (ID:%d) ");
	I18N.vJoy_failed_acquire								= WCHARI(L"Failed to acquire vJoy (ID:%d)");
	I18N.vJoy_failed_update									= WCHARI(L"Failed to update vJoy (ID:%d)");
	I18N.vJoy_version										= WCHARI(L"vJoy version: DLL(%d.%d.%d), Driver(%d.%d.%d)");
	I18N.Clone_of_Tab										= WCHARI(L" Clone of Tab ");
	I18N.TabLog												= WCHARI(L"Log");
	I18N.TabSettings										= WCHARI(L"Settings");
	I18N.TabMapping											= WCHARI(L"Mapping");
	I18N.TabRapidFire										= WCHARI(L"RapidFire");
	I18N.TabKeymap											= WCHARI(L"Keymap");
	I18N.TabViGEm											= WCHARI(L"ViGEm");
	I18N.TabGuardian										= WCHARI(L"Guardian");
	I18N.TabExplorer										= WCHARI(L"Web");
	I18N.TabLinks											= WCHARI(L"Links");
	I18N.dsButton											= WCHARI(L"DS Button");
	I18N.vJoyButton											= WCHARI(L"vJoy Button");
	I18N.Notice												= WCHARI(L"Notice");
	I18N.Setting											= WCHARI(L"Setting");
	I18N.Process											= WCHARI(L"Process");
	I18N.RapidFire_State1									= WCHARI(L"FIRST: %d ms");
	I18N.RapidFire_State2									= WCHARI(L"UP: %d ms");
	I18N.RapidFire_State3									= WCHARI(L"DOWN: %d ms");
	I18N.TagsButton											= WCHARI(L"Tags");
	I18N.Button_LX											= WCHARI(L"AXISL X");
	I18N.Button_LY											= WCHARI(L"AXISL Y");
	I18N.Button_RX											= WCHARI(L"AXISR X");
	I18N.Button_RY											= WCHARI(L"AXISR Y");
	I18N.Button_L3											= WCHARI(L"L3");
	I18N.Button_DPAD_LEFT									= WCHARI(L"←");
	I18N.Button_DPAD_UP										= WCHARI(L"↑");
	I18N.Button_DPAD_RIGHT									= WCHARI(L"→");
	I18N.Button_DPAD_DOWN									= WCHARI(L"↓");
	I18N.Button_SHARE										= WCHARI(L"SHARE");
	I18N.Button_OPTIONS										= WCHARI(L"OPTIONS");
	I18N.Button_SQUARE										= WCHARI(L"□");
	I18N.Button_TRIANGLE									= WCHARI(L"△");
	I18N.Button_CIRCLE										= WCHARI(L"○");
	I18N.Button_CROSS										= WCHARI(L"✕");
	I18N.Button_R3											= WCHARI(L"R3");
	I18N.Button_PS											= WCHARI(L"PS");
	I18N.Button_TOUCH										= WCHARI(L"TOUCH");
	I18N.Button_MUTE										= WCHARI(L"MUTE");
	I18N.Button_L1											= WCHARI(L"L1");
	I18N.Button_R1											= WCHARI(L"R1");
	I18N.Button_L2											= WCHARI(L"L2");
	I18N.Button_R2											= WCHARI(L"R2");
	I18N.Button_L2TRIGGER									= WCHARI(L"L2TRIGGER");
	I18N.Button_R2TRIGGER									= WCHARI(L"R2TRIGGER");
	I18N.Button_EMPTY										= WCHARI(L"NULL");
	I18N.Button_MIDDLE										= WCHARI(L"HALF");
	I18N.Button_FULL										= WCHARI(L"FULL");
	I18N.Button_LX_INV										= WCHARI(L"AXISL XINV");
	I18N.Button_LY_INV										= WCHARI(L"AXISL YINV");
	I18N.Button_RX_INV										= WCHARI(L"AXISR XINV");
	I18N.Button_RY_INV										= WCHARI(L"AXISR YINV");
	I18N.Button_SNIPER_LX									= WCHARI(L"SNIPERL X");
	I18N.Button_SNIPER_LY									= WCHARI(L"SNIPERL Y");
	I18N.Button_SNIPER_RX									= WCHARI(L"SNIPERR X");
	I18N.Button_SNIPER_RY									= WCHARI(L"SNIPERR Y");
	I18N.Button_AXISL_TR_LEFT								= WCHARI(L"AXISL TR ←");
	I18N.Button_AXISL_TR_UP									= WCHARI(L"AXISL TR ↑");
	I18N.Button_AXISL_TR_RIGHT								= WCHARI(L"AXISL TR →");
	I18N.Button_AXISL_TR_DOWN								= WCHARI(L"AXISL TR ↓");
	I18N.Button_AXISR_TR_LEFT								= WCHARI(L"AXISR TR ←");
	I18N.Button_AXISR_TR_UP									= WCHARI(L"AXISR TR ↑");
	I18N.Button_AXISR_TR_RIGHT								= WCHARI(L"AXISR TR →");
	I18N.Button_AXISR_TR_DOWN								= WCHARI(L"AXISR TR ↓");
	I18N.Button_AXISL_LEFT									= WCHARI(L"AXISL ←");
	I18N.Button_AXISL_UP_LEFT								= WCHARI(L"AXISL ←↑");
	I18N.Button_AXISL_UP									= WCHARI(L"AXISL ↑");
	I18N.Button_AXISL_UP_RIGHT								= WCHARI(L"AXISL ↑→");
	I18N.Button_AXISL_RIGHT									= WCHARI(L"AXISL →");
	I18N.Button_AXISL_DOWN_RIGHT							= WCHARI(L"AXISL ↓→");
	I18N.Button_AXISL_DOWN									= WCHARI(L"AXISL ↓");
	I18N.Button_AXISL_DOWN_LEFT								= WCHARI(L"AXISL ←↓");
	I18N.Button_AXISR_LEFT									= WCHARI(L"AXISR ←");
	I18N.Button_AXISR_UP_LEFT								= WCHARI(L"AXISR ←↑");
	I18N.Button_AXISR_UP									= WCHARI(L"AXISR ↑");
	I18N.Button_AXISR_UP_RIGHT								= WCHARI(L"AXISR ↑→");
	I18N.Button_AXISR_RIGHT									= WCHARI(L"AXISR →");
	I18N.Button_AXISR_DOWN_RIGHT							= WCHARI(L"AXISR ↓→");
	I18N.Button_AXISR_DOWN									= WCHARI(L"AXISR ↓");
	I18N.Button_AXISR_DOWN_LEFT								= WCHARI(L"AXISR ←↓");
	I18N.Button_TOUCH_UP									= WCHARI(L"TOUCHUP");
	I18N.Button_TOUCHPAD									= WCHARI(L"TOUCHPAD");
	I18N.Button_TOUCH_1										= WCHARI(L"TOUCH1");
	I18N.Button_TOUCH_2										= WCHARI(L"TOUCH2");
	I18N.Button_TOUCH_3										= WCHARI(L"TOUCH3");
	I18N.Button_TOUCH_4										= WCHARI(L"TOUCH4");
	I18N.Button_TOUCH_L										= WCHARI(L"TOUCHL");
	I18N.Button_TOUCH_R										= WCHARI(L"TOUCHR");
	I18N.Button_L2TRIGGER_33								= WCHARI(L"L2LOW");
	I18N.Button_R2TRIGGER_33								= WCHARI(L"R2LOW");
	I18N.Button_L2TRIGGER_66								= WCHARI(L"L2HIGH");
	I18N.Button_R2TRIGGER_66								= WCHARI(L"R2HIGH");
	I18N.Button_L2TRIGGER_100								= WCHARI(L"L2FULL");
	I18N.Button_R2TRIGGER_100								= WCHARI(L"R2FULL");
	I18N.Button_L1R1										= WCHARI(L"L1R1");
	I18N.Button_L2R2										= WCHARI(L"L2R2");
	I18N.Button_BATTERY										= WCHARI(L"BATTERY");
	I18N.vJoy_X												= WCHARI(L"X");
	I18N.vJoy_Y												= WCHARI(L"Y");
	I18N.vJoy_Z												= WCHARI(L"Z");
	I18N.vJoy_RX											= WCHARI(L"RX");
	I18N.vJoy_RY											= WCHARI(L"RY");
	I18N.vJoy_RZ											= WCHARI(L"RZ");
	I18N.vJoy_SL0											= WCHARI(L"SL0");
	I18N.vJoy_SL1											= WCHARI(L"SL1");
	I18N.vJoy_XTR											= WCHARI(L"XTR");
	I18N.vJoy_YTR											= WCHARI(L"YTR");
	I18N.vJoy_ZTR											= WCHARI(L"ZTR");
	I18N.vJoy_RXTR											= WCHARI(L"RXTR");
	I18N.vJoy_RYTR											= WCHARI(L"RYTR");
	I18N.vJoy_RZTR											= WCHARI(L"RZTR");
	I18N.vJoy_SL0TR											= WCHARI(L"SL0TR");
	I18N.vJoy_SL1TR											= WCHARI(L"SL1TR");
	I18N.vJoy_XINV											= WCHARI(L"XINV");
	I18N.vJoy_YINV											= WCHARI(L"YINV");
	I18N.vJoy_ZINV											= WCHARI(L"ZINV");
	I18N.vJoy_RXINV											= WCHARI(L"RXINV");
	I18N.vJoy_RYINV											= WCHARI(L"RYINV");
	I18N.vJoy_RZINV											= WCHARI(L"RZINV");
	I18N.vJoy_SL0INV										= WCHARI(L"SL0INV");
	I18N.vJoy_SL1INV										= WCHARI(L"SL1INV");
	I18N.vJoy_DPAD1_LEFT									= WCHARI(L"POV1 ←");
	I18N.vJoy_DPAD1_UP_LEFT									= WCHARI(L"POV1 ←↑");
	I18N.vJoy_DPAD1_UP										= WCHARI(L"POV1 ↑");
	I18N.vJoy_DPAD1_UP_RIGHT								= WCHARI(L"POV1 ↑→");
	I18N.vJoy_DPAD1_RIGHT									= WCHARI(L"POV1 →");
	I18N.vJoy_DPAD1_DOWN_RIGHT								= WCHARI(L"POV1 ↓→");
	I18N.vJoy_DPAD1_DOWN									= WCHARI(L"POV1 ↓");
	I18N.vJoy_DPAD1_DOWN_LEFT								= WCHARI(L"POV1 ←↓");
	I18N.vJoy_DPAD2_LEFT									= WCHARI(L"POV2 ←");
	I18N.vJoy_DPAD2_UP_LEFT									= WCHARI(L"POV2 ←↑");
	I18N.vJoy_DPAD2_UP										= WCHARI(L"POV2 ↑");
	I18N.vJoy_DPAD2_UP_RIGHT								= WCHARI(L"POV2 ↑→");
	I18N.vJoy_DPAD2_RIGHT									= WCHARI(L"POV2 →");
	I18N.vJoy_DPAD2_DOWN_RIGHT								= WCHARI(L"POV2 ↓→");
	I18N.vJoy_DPAD2_DOWN									= WCHARI(L"POV2 ↓");
	I18N.vJoy_DPAD2_DOWN_LEFT								= WCHARI(L"POV2 ←↓");
	I18N.vJoy_DPAD3_LEFT									= WCHARI(L"POV3 ←");
	I18N.vJoy_DPAD3_UP_LEFT									= WCHARI(L"POV2 ←↑");
	I18N.vJoy_DPAD3_UP										= WCHARI(L"POV3 ↑");
	I18N.vJoy_DPAD3_UP_RIGHT								= WCHARI(L"POV3 ↑→");
	I18N.vJoy_DPAD3_RIGHT									= WCHARI(L"POV3 →");
	I18N.vJoy_DPAD3_DOWN_RIGHT								= WCHARI(L"POV3 ↓→");
	I18N.vJoy_DPAD3_DOWN									= WCHARI(L"POV3 ↓");
	I18N.vJoy_DPAD3_DOWN_LEFT								= WCHARI(L"POV3 ←↓");
	I18N.vJoy_DPAD4_LEFT									= WCHARI(L"POV4 ←");
	I18N.vJoy_DPAD4_UP_LEFT									= WCHARI(L"POV4 ←↑");
	I18N.vJoy_DPAD4_UP										= WCHARI(L"POV4 ↑");
	I18N.vJoy_DPAD4_UP_RIGHT								= WCHARI(L"POV4 ↑→");
	I18N.vJoy_DPAD4_RIGHT									= WCHARI(L"POV4 →");
	I18N.vJoy_DPAD4_DOWN_RIGHT								= WCHARI(L"POV4 ↓→");
	I18N.vJoy_DPAD4_DOWN									= WCHARI(L"POV4 ↓");
	I18N.vJoy_DPAD4_DOWN_LEFT								= WCHARI(L"POV4 ←↓");
	I18N.LedAction_Led_1									= WCHARI(L"Led 1");
	I18N.LedAction_Led_2									= WCHARI(L"Led 2");
	I18N.LedAction_Led_3									= WCHARI(L"Led 3");
	I18N.LedAction_Led_4									= WCHARI(L"Led 4");
	I18N.LedAction_Led_5									= WCHARI(L"Led 5");
	I18N.LedAction_BATTERY									= WCHARI(L"Battery status");
	I18N.MouseAction_ACTIVE_MOUSE							= WCHARI(L"Active mouse");
	I18N.MouseAction_SAVE_POSITION							= WCHARI(L"Save position");
	I18N.MouseAction_MOVE_BACK								= WCHARI(L"Move back");
	I18N.MouseAction_MOVE_TO_XY								= WCHARI(L"Move to x,y");
	I18N.MouseAction_MOVE_TO_WH								= WCHARI(L"Move to w,h");
	I18N.MouseAction_MOVE_TO_NN								= WCHARI(L"Move to nw,nh");
	I18N.MouseAction_SAVE_AND_MOVE_TO_XY					= WCHARI(L"SnM to x,y");
	I18N.MouseAction_SAVE_AND_MOVE_TO_WH					= WCHARI(L"SnM to w,h");
	I18N.MouseAction_SAVE_AND_MOVE_TO_NN					= WCHARI(L"SnM to nw,nh");
	I18N.MouseAction_GRID_LEFT								= WCHARI(L"Grid Left");
	I18N.MouseAction_GRID_UP								= WCHARI(L"Grid Up");
	I18N.MouseAction_GRID_RIGHT								= WCHARI(L"Grid Right");
	I18N.MouseAction_GRID_DOWN								= WCHARI(L"Grid Down");
	I18N.MouseAction_LEFT_CLICK								= WCHARI(L"Left Click");
	I18N.MouseAction_MIDDLE_CLICK							= WCHARI(L"Middle Click");
	I18N.MouseAction_RIGHT_CLICK							= WCHARI(L"Right Click");
	I18N.MouseAction_X1_CLICK								= WCHARI(L"X1 Click");
	I18N.MouseAction_X2_CLICK								= WCHARI(L"X2 Click");
	I18N.MouseAction_SCROLL_UP								= WCHARI(L"Scroll ↑");
	I18N.MouseAction_SCROLL_DOWN							= WCHARI(L"Scroll ↓");
	I18N.MouseAction_LEFT_DOUBLE_CLICK						= WCHARI(L"Left Double");
	I18N.MouseAction_MIDDLE_DOUBLE_CLICK					= WCHARI(L"Middle Double");
	I18N.MouseAction_RIGHT_DOUBLE_CLICK						= WCHARI(L"Right Double");
	I18N.MouseAction_X1_DOUBLE_CLICK						= WCHARI(L"X1 Double");
	I18N.MouseAction_X2_DOUBLE_CLICK						= WCHARI(L"X2 Double");
	I18N.MouseAction_SCROLL_UP_x5							= WCHARI(L"Scroll ↑ x5");
	I18N.MouseAction_SCROLL_DOWN_x5							= WCHARI(L"Scroll ↓ x5");
	I18N.MouseAction_LEFT_DOWN								= WCHARI(L"Left Down");
	I18N.MouseAction_MIDDLE_DOWN							= WCHARI(L"Middle Down");
	I18N.MouseAction_RIGHT_DOWN								= WCHARI(L"Right Down");
	I18N.MouseAction_X1_DOWN								= WCHARI(L"X1 Down");
	I18N.MouseAction_X2_DOWN								= WCHARI(L"X2 Down");
	I18N.MouseAction_SCROLL_UP_VARIABLE						= WCHARI(L"Scroll ↑ incr");
	I18N.MouseAction_SCROLL_DOWN_VARIABLE					= WCHARI(L"Scroll ↓ incr");
	I18N.MouseAction_MUTE_SOUND								= WCHARI(L"Mute/Unmute");
	I18N.MouseAction_VOLUME_UP								= WCHARI(L"Volume up");
	I18N.MouseAction_VOLUME_DOWN							= WCHARI(L"Volume down");
	I18N.MouseAction_MEMORIZE_MODE							= WCHARI(L"Memorize mode");
	I18N.MouseAction_TO_MEM_MODE							= WCHARI(L"To Last Mode");
	I18N.MouseAction_TO_MODE								= WCHARI(L"To Mode: ");
	I18N.MouseAction_TO_LAST_MODE							= WCHARI(L"To Last Mode");
	I18N.MouseAction_BASE_TO_MODE							= WCHARI(L"Base To: ");
	I18N.MouseAction_TO_BASE_MODE							= WCHARI(L"To Base Mode");
	I18N.MouseAction_FORGOT_RELEASED						= WCHARI(L"Forgot released");
	I18N.MouseAction_IF_RELEASED_GOTO						= WCHARI(L"If released goto");
	I18N.MouseAction_IF_PUSHED_GOTO							= WCHARI(L"If pushed goto");
	I18N.MouseAction_RETURN_TO								= WCHARI(L"Return to");
	I18N.MouseAction_MOUSE_INTERRUPT						= WCHARI(L"Interrupt");
	I18N.MouseAction_MOUSE_NO_SUSTAIN						= WCHARI(L"No sustain");
	I18N.MouseAction_MOUSE_PAUSE							= WCHARI(L"Pause");
	I18N.MouseAction_BEEP1									= WCHARI(L"Beep 1");
	I18N.MouseAction_BEEP2									= WCHARI(L"Beep 2");
	I18N.MouseAction_BEEP3									= WCHARI(L"Beep 3");
	I18N.MouseAction_RESET_STATS							= WCHARI(L"Reset stats");
	I18N.MouseAction_ADDSTAT1								= WCHARI(L"Add stat 1");
	I18N.MouseAction_ADDSTAT2								= WCHARI(L"Add stat 2");
	I18N.MouseAction_ADDSTAT3								= WCHARI(L"Add stat 3");
	I18N.MouseAction_ADDSTAT4								= WCHARI(L"Add stat 4");
	I18N.MouseAction_ADDSTAT5								= WCHARI(L"Add stat 5");
	I18N.MouseAction_ADDSTAT6								= WCHARI(L"Add stat 6");
	I18N.MouseAction_ADDSTAT7								= WCHARI(L"Add stat 7");
	I18N.MouseAction_ADDSTAT8								= WCHARI(L"Add stat 8");
	I18N.MouseAction_MINIMIZE								= WCHARI(L"Minimize");
	I18N.MouseAction_RESTORE								= WCHARI(L"Restore");
	I18N.Axis_XY_CW											= WCHARI(L"XY ⭮");
	I18N.Axis_XY_CN											= WCHARI(L"XY ⭯");
	I18N.Axis_ZRZ_CW										= WCHARI(L"ZRZ ⭮");
	I18N.Axis_ZRZ_CN										= WCHARI(L"ZRZ ⭯");
	I18N.Axis_RXRY_CW										= WCHARI(L"RXRY ⭮");
	I18N.Axis_RXRY_CN										= WCHARI(L"RXRY ⭯");
	I18N.Axis_SL0SL1_CW										= WCHARI(L"SL0SL1 ⭮");
	I18N.Axis_SL0SL1_CN										= WCHARI(L"SL0SL1 ⭯");
	I18N.Axis_XY_CENTER										= WCHARI(L"XY ●");
	I18N.Axis_ZRZ_CENTER									= WCHARI(L"ZRZ ●");
	I18N.Axis_XY_LEFT										= WCHARI(L"XY ●←");
	I18N.Axis_XY_UP_LEFT									= WCHARI(L"XY ●↖");
	I18N.Axis_XY_UP											= WCHARI(L"XY ●↑");
	I18N.Axis_XY_UP_RIGHT									= WCHARI(L"XY ●↗");
	I18N.Axis_XY_RIGHT										= WCHARI(L"XY ●→");
	I18N.Axis_XY_DOWN_RIGHT									= WCHARI(L"XY ●↘");
	I18N.Axis_XY_DOWN										= WCHARI(L"XY ●↓");
	I18N.Axis_XY_DOWN_LEFT									= WCHARI(L"XY ●↙");
	I18N.Axis_XY_Q1_CW										= WCHARI(L"XY Q1 ⭮");
	I18N.Axis_XY_Q1_CN										= WCHARI(L"XY Q1 ⭯");
	I18N.Axis_XY_Q2_CW										= WCHARI(L"XY Q2 ⭮");
	I18N.Axis_XY_Q2_CN										= WCHARI(L"XY Q2 ⭯");
	I18N.Axis_XY_Q3_CW										= WCHARI(L"XY Q3 ⭮");
	I18N.Axis_XY_Q3_CN										= WCHARI(L"XY Q3 ⭯");
	I18N.Axis_XY_Q4_CW										= WCHARI(L"XY Q4 ⭮");
	I18N.Axis_XY_Q4_CN										= WCHARI(L"XY Q4 ⭯");
	I18N.Axis_XY_E1_CW										= WCHARI(L"XY E1 ⭮");
	I18N.Axis_XY_E1_CN										= WCHARI(L"XY E1 ⭯");
	I18N.Axis_XY_E2_CW										= WCHARI(L"XY E2 ⭮");
	I18N.Axis_XY_E2_CN										= WCHARI(L"XY E2 ⭯");
	I18N.Axis_XY_E3_CW										= WCHARI(L"XY E3 ⭮");
	I18N.Axis_XY_E3_CN										= WCHARI(L"XY E3 ⭯");
	I18N.Axis_XY_E4_CW										= WCHARI(L"XY E4 ⭮");
	I18N.Axis_XY_E4_CN										= WCHARI(L"XY E4 ⭯");
	I18N.Axis_XY_E5_CW										= WCHARI(L"XY E5 ⭮");
	I18N.Axis_XY_E5_CN										= WCHARI(L"XY E5 ⭯");
	I18N.Axis_XY_E6_CW										= WCHARI(L"XY E6 ⭮");
	I18N.Axis_XY_E6_CN										= WCHARI(L"XY E6 ⭯");
	I18N.Axis_XY_E7_CW										= WCHARI(L"XY E7 ⭮");
	I18N.Axis_XY_E7_CN										= WCHARI(L"XY E7 ⭯");
	I18N.Axis_XY_E8_CW										= WCHARI(L"XY E8 ⭮");
	I18N.Axis_XY_E8_CN										= WCHARI(L"XY E8 ⭯");
	I18N.Axis_XY_C_L										= WCHARI(L"XY ←");
	I18N.Axis_XY_C_UL										= WCHARI(L"XY ↖");
	I18N.Axis_XY_C_U										= WCHARI(L"XY ↑");
	I18N.Axis_XY_C_UR										= WCHARI(L"XY ↗");
	I18N.Axis_XY_C_R										= WCHARI(L"XY →");
	I18N.Axis_XY_C_DR										= WCHARI(L"XY ↘");
	I18N.Axis_XY_C_D										= WCHARI(L"XY ↓");
	I18N.Axis_XY_C_DL										= WCHARI(L"XY ↙");
	I18N.Axis_XY_2C_L										= WCHARI(L"XY ⭲");
	I18N.Axis_XY_2C_UL										= WCHARI(L"XY ⭸");
	I18N.Axis_XY_2C_U										= WCHARI(L"XY ⭳");
	I18N.Axis_XY_2C_UR										= WCHARI(L"XY ⭹");
	I18N.Axis_XY_2C_R										= WCHARI(L"XY ⭰");
	I18N.Axis_XY_2C_DR										= WCHARI(L"XY ⭶");
	I18N.Axis_XY_2C_D										= WCHARI(L"XY ⭱");
	I18N.Axis_XY_2C_DL										= WCHARI(L"XY ⭷");
	I18N.Axis_XY_D_L										= WCHARI(L"XY ø←");
	I18N.Axis_XY_D_UL										= WCHARI(L"XY ø↖");
	I18N.Axis_XY_D_U										= WCHARI(L"XY ø↑");
	I18N.Axis_XY_D_UR										= WCHARI(L"XY ø↗");
	I18N.Axis_XY_D_R										= WCHARI(L"XY ø→");
	I18N.Axis_XY_D_DR										= WCHARI(L"XY ø↘");
	I18N.Axis_XY_D_D										= WCHARI(L"XY ø↓");
	I18N.Axis_XY_D_DL										= WCHARI(L"XY ø↙");
	I18N.Axis_XY_T_UL_CW									= WCHARI(L"XY ⯅⮣");
	I18N.Axis_XY_T_UL_CN									= WCHARI(L"XY ⯅⮦");
	I18N.Axis_XY_T_UR_CW									= WCHARI(L"XY ⯅⮧");
	I18N.Axis_XY_T_UR_CN									= WCHARI(L"XY ⯅⮢");
	I18N.Axis_XY_T_DR_CW									= WCHARI(L"XY ⯆⮠");
	I18N.Axis_XY_T_DR_CN									= WCHARI(L"XY ⯆⮥");
	I18N.Axis_XY_T_DL_CW									= WCHARI(L"XY ⯆⮤");
	I18N.Axis_XY_T_DL_CN									= WCHARI(L"XY ⯆⮡");
	I18N.Axis_XY_S_L_CW										= WCHARI(L"XY ⯀⮤");
	I18N.Axis_XY_S_L_CN										= WCHARI(L"XY ⯀⮦");
	I18N.Axis_XY_S_U_CW										= WCHARI(L"XY ⯀⮣");
	I18N.Axis_XY_S_U_CN										= WCHARI(L"XY ⯀⮢");
	I18N.Axis_XY_S_R_CW										= WCHARI(L"XY ⯀⮧");
	I18N.Axis_XY_S_R_CN										= WCHARI(L"XY ⯀⮥");
	I18N.Axis_XY_S_D_CW										= WCHARI(L"XY ⯀⮠");
	I18N.Axis_XY_S_D_CN										= WCHARI(L"XY ⯀⮡");
	I18N.Axis_XY_L_UL_CW									= WCHARI(L"XY ⯁⮣");
	I18N.Axis_XY_L_UL_CN									= WCHARI(L"XY ⯁⮦");
	I18N.Axis_XY_L_UR_CW									= WCHARI(L"XY ⯁⮧");
	I18N.Axis_XY_L_UR_CN									= WCHARI(L"XY ⯁⮢");
	I18N.Axis_XY_L_DR_CW									= WCHARI(L"XY ⯁⮠");
	I18N.Axis_XY_L_DR_CN									= WCHARI(L"XY ⯁⮥");
	I18N.Axis_XY_L_DL_CW									= WCHARI(L"XY ⯁⮤");
	I18N.Axis_XY_L_DL_CN									= WCHARI(L"XY ⯁⮡");
	I18N.Axis_ZRZ_LEFT										= WCHARI(L"ZRZ ●←");
	I18N.Axis_ZRZ_UP_LEFT									= WCHARI(L"ZRZ ●↖");
	I18N.Axis_ZRZ_UP										= WCHARI(L"ZRZ ●↑");
	I18N.Axis_ZRZ_UP_RIGHT									= WCHARI(L"ZRZ ●↗");
	I18N.Axis_ZRZ_RIGHT										= WCHARI(L"ZRZ ●→");
	I18N.Axis_ZRZ_DOWN_RIGHT								= WCHARI(L"ZRZ ●↘");
	I18N.Axis_ZRZ_DOWN										= WCHARI(L"ZRZ ●↓");
	I18N.Axis_ZRZ_DOWN_LEFT									= WCHARI(L"ZRZ ●↙");
	I18N.Axis_ZRZ_Q1_CW										= WCHARI(L"ZRZ Q1 ⭮");
	I18N.Axis_ZRZ_Q1_CN										= WCHARI(L"ZRZ Q1 ⭯");
	I18N.Axis_ZRZ_Q2_CW										= WCHARI(L"ZRZ Q2 ⭮");
	I18N.Axis_ZRZ_Q2_CN										= WCHARI(L"ZRZ Q2 ⭯");
	I18N.Axis_ZRZ_Q3_CW										= WCHARI(L"ZRZ Q3 ⭮");
	I18N.Axis_ZRZ_Q3_CN										= WCHARI(L"ZRZ Q3 ⭯");
	I18N.Axis_ZRZ_Q4_CW										= WCHARI(L"ZRZ Q4 ⭮");
	I18N.Axis_ZRZ_Q4_CN										= WCHARI(L"ZRZ Q4 ⭯");
	I18N.Axis_ZRZ_E1_CW										= WCHARI(L"ZRZ E1 ⭮");
	I18N.Axis_ZRZ_E1_CN										= WCHARI(L"ZRZ E1 ⭯");
	I18N.Axis_ZRZ_E2_CW										= WCHARI(L"ZRZ E2 ⭮");
	I18N.Axis_ZRZ_E2_CN										= WCHARI(L"ZRZ E2 ⭯");
	I18N.Axis_ZRZ_E3_CW										= WCHARI(L"ZRZ E3 ⭮");
	I18N.Axis_ZRZ_E3_CN										= WCHARI(L"ZRZ E3 ⭯");
	I18N.Axis_ZRZ_E4_CW										= WCHARI(L"ZRZ E4 ⭮");
	I18N.Axis_ZRZ_E4_CN										= WCHARI(L"ZRZ E4 ⭯");
	I18N.Axis_ZRZ_E5_CW										= WCHARI(L"ZRZ E5 ⭮");
	I18N.Axis_ZRZ_E5_CN										= WCHARI(L"ZRZ E5 ⭯");
	I18N.Axis_ZRZ_E6_CW										= WCHARI(L"ZRZ E6 ⭮");
	I18N.Axis_ZRZ_E6_CN										= WCHARI(L"ZRZ E6 ⭯");
	I18N.Axis_ZRZ_E7_CW										= WCHARI(L"ZRZ E7 ⭮");
	I18N.Axis_ZRZ_E7_CN										= WCHARI(L"ZRZ E7 ⭯");
	I18N.Axis_ZRZ_E8_CW										= WCHARI(L"ZRZ E8 ⭮");
	I18N.Axis_ZRZ_E8_CN										= WCHARI(L"ZRZ E8 ⭯");
	I18N.Axis_ZRZ_C_L										= WCHARI(L"ZRZ ←");
	I18N.Axis_ZRZ_C_UL										= WCHARI(L"ZRZ ↖");
	I18N.Axis_ZRZ_C_U										= WCHARI(L"ZRZ ↑");
	I18N.Axis_ZRZ_C_UR										= WCHARI(L"ZRZ ↗");
	I18N.Axis_ZRZ_C_R										= WCHARI(L"ZRZ →");
	I18N.Axis_ZRZ_C_DR										= WCHARI(L"ZRZ ↘");
	I18N.Axis_ZRZ_C_D										= WCHARI(L"ZRZ ↓");
	I18N.Axis_ZRZ_C_DL										= WCHARI(L"ZRZ ↙");
	I18N.Axis_ZRZ_2C_L										= WCHARI(L"ZRZ ⭲");
	I18N.Axis_ZRZ_2C_UL										= WCHARI(L"ZRZ ⭸");
	I18N.Axis_ZRZ_2C_U										= WCHARI(L"ZRZ ⭳");
	I18N.Axis_ZRZ_2C_UR										= WCHARI(L"ZRZ ⭹");
	I18N.Axis_ZRZ_2C_R										= WCHARI(L"ZRZ ⭰");
	I18N.Axis_ZRZ_2C_DR										= WCHARI(L"ZRZ ⭶");
	I18N.Axis_ZRZ_2C_D										= WCHARI(L"ZRZ ⭱");
	I18N.Axis_ZRZ_2C_DL										= WCHARI(L"ZRZ ⭷");
	I18N.Axis_ZRZ_D_L										= WCHARI(L"ZRZ ø←");
	I18N.Axis_ZRZ_D_UL										= WCHARI(L"ZRZ ø↖");
	I18N.Axis_ZRZ_D_U										= WCHARI(L"ZRZ ø↑");
	I18N.Axis_ZRZ_D_UR										= WCHARI(L"ZRZ ø↗");
	I18N.Axis_ZRZ_D_R										= WCHARI(L"ZRZ ø→");
	I18N.Axis_ZRZ_D_DR										= WCHARI(L"ZRZ ø↘");
	I18N.Axis_ZRZ_D_D										= WCHARI(L"ZRZ ø↓");
	I18N.Axis_ZRZ_D_DL										= WCHARI(L"ZRZ ø↙");
	I18N.Axis_ZRZ_T_UL_CW									= WCHARI(L"ZRZ ⯅⮣");
	I18N.Axis_ZRZ_T_UL_CN									= WCHARI(L"ZRZ ⯅⮦");
	I18N.Axis_ZRZ_T_UR_CW									= WCHARI(L"ZRZ ⯅⮧");
	I18N.Axis_ZRZ_T_UR_CN									= WCHARI(L"ZRZ ⯅⮢");
	I18N.Axis_ZRZ_T_DR_CW									= WCHARI(L"ZRZ ⯆⮠");
	I18N.Axis_ZRZ_T_DR_CN									= WCHARI(L"ZRZ ⯆⮥");
	I18N.Axis_ZRZ_T_DL_CW									= WCHARI(L"ZRZ ⯆⮤");
	I18N.Axis_ZRZ_T_DL_CN									= WCHARI(L"ZRZ ⯆⮡");
	I18N.Axis_ZRZ_S_L_CW									= WCHARI(L"ZRZ ⯀⮤");
	I18N.Axis_ZRZ_S_L_CN									= WCHARI(L"ZRZ ⯀⮦");
	I18N.Axis_ZRZ_S_U_CW									= WCHARI(L"ZRZ ⯀⮣");
	I18N.Axis_ZRZ_S_U_CN									= WCHARI(L"ZRZ ⯀⮢");
	I18N.Axis_ZRZ_S_R_CW									= WCHARI(L"ZRZ ⯀⮧");
	I18N.Axis_ZRZ_S_R_CN									= WCHARI(L"ZRZ ⯀⮥");
	I18N.Axis_ZRZ_S_D_CW									= WCHARI(L"ZRZ ⯀⮠");
	I18N.Axis_ZRZ_S_D_CN									= WCHARI(L"ZRZ ⯀⮡");
	I18N.Axis_ZRZ_L_UL_CW									= WCHARI(L"ZRZ ⯁⮣");
	I18N.Axis_ZRZ_L_UL_CN									= WCHARI(L"ZRZ ⯁⮦");
	I18N.Axis_ZRZ_L_UR_CW									= WCHARI(L"ZRZ ⯁⮧");
	I18N.Axis_ZRZ_L_UR_CN									= WCHARI(L"ZRZ ⯁⮢");
	I18N.Axis_ZRZ_L_DR_CW									= WCHARI(L"ZRZ ⯁⮠");
	I18N.Axis_ZRZ_L_DR_CN									= WCHARI(L"ZRZ ⯁⮥");
	I18N.Axis_ZRZ_L_DL_CW									= WCHARI(L"ZRZ ⯁⮤");
	I18N.Axis_ZRZ_L_DL_CN									= WCHARI(L"ZRZ ⯁⮡");
	I18N.Gamepad_LEFT_STICK									= WCHARI(L"Lstick");
	I18N.Gamepad_BACK										= WCHARI(L"Back");
	I18N.Gamepad_START										= WCHARI(L"Start");
	I18N.Gamepad_X											= WCHARI(L"X");
	I18N.Gamepad_Y											= WCHARI(L"Y");
	I18N.Gamepad_B											= WCHARI(L"B");
	I18N.Gamepad_A											= WCHARI(L"A");
	I18N.Gamepad_RIGHT_STICK								= WCHARI(L"Rstick");
	I18N.Gamepad_GUIDE										= WCHARI(L"Guide");
	I18N.Gamepad_LEFT_BUMPER								= WCHARI(L"Lbumper");
	I18N.Gamepad_RIGHT_BUMPER								= WCHARI(L"Rbumper");
	I18N.Gamepad_LEFT_TRIGGER								= WCHARI(L"Ltrigger");
	I18N.Gamepad_RIGHT_TRIGGER								= WCHARI(L"Rtrigger");

	I18N.ABOUT_1											= WCHARI(L"Ds2vJoy ,");
	I18N.ABOUT_2											= WCHARI(L"Modified version");
	I18N.ABOUT_3											= WCHARI(L"of Ds4vJoy");
	I18N.ABOUT_OK											= WCHARI(L"OK");
	I18N.SETTINGS_PREFERRED_DS								= WCHARI(L"Preferred DS:");
	I18N.SETTINGS_DS4										= WCHARI(L"DS4");
	I18N.SETTINGS_DS5										= WCHARI(L"DS5");
	I18N.SETTINGS_KBD										= WCHARI(L"KBD");
	I18N.SETTINGS_MSE										= WCHARI(L"MSE");
	I18N.SETTINGS_TEXT_VJOY_DEVICE							= WCHARI(L"vJoy device");
	I18N.SETTINGS_STARTUP									= WCHARI(L"Start on system startup");
	I18N.SETTINGS_START_MINIMIZED							= WCHARI(L"Start Minimized");
	I18N.SETTINGS_CLOSE_MINIMIZE							= WCHARI(L"Close Minimize");
	I18N.SETTINGS_DISCONNECT_BT								= WCHARI(L"Disconnect Bluetooth on exit");
	I18N.SETTINGS_MOUSE_CAN_BYPASS							= WCHARI(L"Mouse bypass screen dimensions");
	I18N.SETTINGS_ALERT_ON_LOWBATTS							= WCHARI(L"Low Batt Alert");
	I18N.SETTINGS_TRIGGERS_MODE								= WCHARI(L"Triggers mode:");
	I18N.SETTINGS_TRIGGERS_NONE								= WCHARI(L"None");
	I18N.SETTINGS_TRIGGERS_SHOOT							= WCHARI(L"Shoot");
	I18N.SETTINGS_TRIGGERS_RESIST							= WCHARI(L"Resist");
	I18N.SETTINGS_TRIGGERS_PROACTIVE						= WCHARI(L"Proactive");
	I18N.SETTINGS_USE_THE_DS_SERIAL							= WCHARI(L"Use the DS serial:");
	I18N.SETTINGS_DARK_THEME								= WCHARI(L"Dark theme (Notepad)");
	I18N.SETTINGS_TEXT_THRESHOLD							= WCHARI(L"Threshold");
	I18N.SETTINGS_TEXT_SIMULTANEOUS							= WCHARI(L"Simultaneous");
	I18N.SETTINGS_TEXT_LONG									= WCHARI(L"Long");
	I18N.SETTINGS_TEXT_VERY_LONG							= WCHARI(L"Very long");
	I18N.SETTINGS_TEXT_WEBREFRESH							= WCHARI(L"Web refresh");
	I18N.SETTINGS_UNIT_THRESHOLD							= WCHARI(L"128");
	I18N.SETTINGS_UNIT_SIMULTANEOUS							= WCHARI(L"ms");
	I18N.SETTINGS_UNIT_LONG									= WCHARI(L"ms");
	I18N.SETTINGS_UNIT_VERY_LONG							= WCHARI(L"ms");
	I18N.SETTINGS_UNIT_WEB_REFRESH							= WCHARI(L"s");
	I18N.SETTINGS_MULTIPLE_TOUCHPAD							= WCHARI(L"Multiple Touchpad:");
	I18N.SETTINGS_TEXT_FIRST_BUTTON							= WCHARI(L"First button");
	I18N.SETTINGS_TEXT_COLUMN								= WCHARI(L"Column");
	I18N.SETTINGS_TEXT_ROW									= WCHARI(L"Row");
	I18N.SETTINGS_LED										= WCHARI(L"Black Led");
	I18N.SETTINGS_WHEN_EXITING								= WCHARI(L"when Exiting");
	I18N.SETTINGS_LED_BUTTON								= WCHARI(L"LED");
	I18N.SETTINGS_COLOR										= WCHARI(L"LED color");
	I18N.CLONE_MENU											= WCHARI(L"Clone of Tab 1");
	I18N.CLONE_STATS										= WCHARI(L"Stats:");
	I18N.CLONE_STAT1										= WCHARI(L"00000");
	I18N.CLONE_STAT2										= WCHARI(L"00000");
	I18N.CLONE_STAT3										= WCHARI(L"00000");
	I18N.CLONE_STAT4										= WCHARI(L"00000");
	I18N.CLONE_STAT5										= WCHARI(L"00000");
	I18N.CLONE_STAT6										= WCHARI(L"00000");
	I18N.CLONE_STAT7										= WCHARI(L"00000");
	I18N.CLONE_STAT8										= WCHARI(L"00000");
	I18N.CLONE_CANCEL										= WCHARI(L"X");
	I18N.CLONE_CLEAR										= WCHARI(L"Clear");
	I18N.CLONE_POSTIT										= WCHARI(L"Yet another Post-its");
	I18N.MAPPING_HELP										= WCHARI(L"Help");
	I18N.MAPPING_OK											= WCHARI(L"OK");
	I18N.MAPPING_CLEAR										= WCHARI(L"Clear");
	I18N.MAPPING_CANCEL										= WCHARI(L"x");
	I18N.MAPPING_X											= WCHARI(L"88888");
	I18N.MAPPING_Y											= WCHARI(L"88888");
	I18N.MIND_OK											= WCHARI(L"✓");
	I18N.MIND_CANCEL										= WCHARI(L"✗");
	I18N.RAPIDFIRE_RAPIDFIRE								= WCHARI(L"RapidFire");
	I18N.RAPIDFIRE_MULTIPLE_PRESS							= WCHARI(L"Multiple press");
	I18N.RAPIDFIRE_TEXT_FIRST								= WCHARI(L"First press time");
	I18N.RAPIDFIRE_TEXT_RELEASE								= WCHARI(L"Release time");
	I18N.RAPIDFIRE_TEXT_DOWN								= WCHARI(L"Press time");
	I18N.RAPIDFIRE_UNIT_FIRST								= WCHARI(L"ms");
	I18N.RAPIDFIRE_UNIT_RELEASE								= WCHARI(L"ms");
	I18N.RAPIDFIRE_UNIT_DOWN								= WCHARI(L"ms");
	I18N.RAPIDFIRE_NOTICE									= WCHARI(L"An odd number for Release or Press times add 0-19 ms, differents each turn / push");
	I18N.RAPIDFIRE_OK										= WCHARI(L"OK");
	I18N.RAPIDFIRE_CANCEL									= WCHARI(L"Cancel");
	I18N.KEYMAP_SOURCE										= WCHARI(L"Source");
	I18N.KEYMAP_RESTORE										= WCHARI(L"Restore /Hide");
	I18N.KEYMAP_MAXIMIZE									= WCHARI(L"Maximize /Minimize");
	I18N.KEYMAP_SHOW										= WCHARI(L"Show /Normal");
	I18N.KEYMAP_ACTIVATING									= WCHARI(L"Activate window");
	I18N.KEYMAP_SEND										= WCHARI(L"Send Keycode");
	I18N.KEYMAP_ENTER										= WCHARI(L"Enter Keycode");
	I18N.KEYMAP_CLEAR										= WCHARI(L"Clear");
	I18N.KEYMAP_NATURAL										= WCHARI(L"Natural typing");
	I18N.KEYMAP_POSTMESSAGE									= WCHARI(L"Send to :");
	I18N.KEYMAP_FINDWINDOW									= WCHARI(L"Find");
	I18N.KEYMAP_METHOD										= WCHARI(L"Method: PostMessage");
	I18N.KEYMAP_EXTENDEDKEY									= WCHARI(L"KEYEVENTF_EXTENDEDKEY");
	I18N.KEYMAP_SCANCODE									= WCHARI(L"KEYEVENTF_SCANCODE");
	I18N.KEYMAP_OK											= WCHARI(L"OK");
	I18N.KEYMAP_CANCEL										= WCHARI(L"Cancel");
	I18N.KEYMAP_WINDOW										= WCHARI(L"Window");
	I18N.KEYMAP_IS_W_VISIBLE								= WCHARI(L"IsWindowVisible");
	I18N.KEYMAP_CLEAR2										= WCHARI(L"Clear");
	I18N.KEYMAP_DELETE										= WCHARI(L"Delete");
	I18N.KEYMAP_OK2											= WCHARI(L"OK");
	I18N.KEYMAP_CANCEL2										= WCHARI(L"Cancel");
	I18N.VIGEM_ACTIVE										= WCHARI(L"ViGEm Module Active");
	I18N.VIGEM_PAD											= WCHARI(L"Desired Virtual Pad:");
	I18N.VIGEM_X360											= WCHARI(L"X360");
	I18N.VIGEM_DS4											= WCHARI(L"DS4");
	I18N.VIGEM_INSTALL										= WCHARI(L"ViGEm status");
	I18N.VIGEM_STATUS										= WCHARI(L"ViGEm status");
	I18N.HID_ACTIVE											= WCHARI(L"HidGuardian Module Active");
	I18N.HID_BLACKLIST										= WCHARI(L"Blacklist");
	I18N.HID_REMOVE											= WCHARI(L" Add/Remove Blacklist on Enter/Exit");
	I18N.HID_WHITELIST										= WCHARI(L"Whitelist");
	I18N.HID_PURGE											= WCHARI(L" Purge Whitelist on Enter/Exit");
	I18N.HID_CERBERUS_LINK									= WCHARI(L"<a>HidCerberus Service configuration page</a>");
	I18N.HID_CERBERUS_URL									= WCHARI(L"http://localhost:26762/");
	I18N.HID_INSTALL										= WCHARI(L"Installation");
	I18N.HID_GUARDIAN_INSTALL								= WCHARI(L"HidCerberus status");
	I18N.HID_GUARDIAN_STATUS								= WCHARI(L"HidCerberus status");
	I18N.HID_CERBERUS_INSTALL								= WCHARI(L"HidGuardian status");
	I18N.HID_CERBERUS_STATUS								= WCHARI(L"HidGuardian status");
	I18N.HID_LEGEND											= WCHARI(L"Legend:");
	I18N.HID_LEGEND2										= WCHARI(L"installed ");
	I18N.HID_LEGEND1										= WCHARI(L"Not");
	I18N.HID_LEGEND3										= WCHARI(L"Running ");
	I18N.HID_LEGEND4										= WCHARI(L"Stopped ");
	I18N.HID_LEGEND5										= WCHARI(L"Paused ");
	I18N.LINKS_TEXT1										= WCHARI(L"Add webbrowser links 1-5");
	I18N.LINKS_TEXT2										= WCHARI(L"Add webbrowser links 6-10");
	I18N.LINKS_TEXT3										= WCHARI(L"Add the name …");
	I18N.LINKS_TEXT4										= WCHARI(L"… and location of 1-5 executables to place in tray menu");
	I18N.LINKS_DS4VJOY										= WCHARI(L"<a>Ds4vJoy</a>");
	I18N.LINKS_VJOY											= WCHARI(L"<a>vJoy</a>");
	I18N.LINKS_WEBVIEW2										= WCHARI(L"<a>WebView2</a>");
	I18N.LINKS_VIGEMBUS										= WCHARI(L"<a>ViGEmBus</a>");
	I18N.LINKS_VIGEMCLIENT									= WCHARI(L"<a>ViGEmClient</a>");
	I18N.LINKS_HIDGUARDIAN									= WCHARI(L"<a>HidGuardian</a>");
	I18N.LINKS_HIDCERBERUS									= WCHARI(L"<a>HidCerberus</a>");
	I18N.LINKS_URL_DS4VJOY									= WCHARI(L"https://github.com/090/Ds4vJoy");
	I18N.LINKS_URL_VJOY										= WCHARI(L"https://sourceforge.net/projects/vjoystick");
	I18N.LINKS_URL_WEBVIEW2									= WCHARI(L"https://developer.microsoft.com/en-us/microsoft-edge/webview2");
	I18N.LINKS_URL_VIGEMBUS									= WCHARI(L"https://github.com/ViGEm/ViGEmBus");
	I18N.LINKS_URL_VIGEMCLIENT								= WCHARI(L"https://github.com/ViGEm/ViGEmClient");
	I18N.LINKS_URL_HIDGUARDIAN								= WCHARI(L"https://github.com/ViGEm/HidGuardian");
	I18N.LINKS_URL_HIDCERBERUS								= WCHARI(L"https://github.com/ViGEm/HidCerberus");
	I18N.NOTEPAD_UNSAVED									= WCHARI(L"*Unsaved");

	I18N.STATE_INSTALL										= WCHARI(L"Install");
	I18N.STATE_UNINSTALL									= WCHARI(L"Uninstall");
	I18N.STATE_START										= WCHARI(L"Start");
	I18N.STATE_STOP											= WCHARI(L"Stop");
	I18N.STATE_RESTART										= WCHARI(L"Restart");
	I18N.STATE_ENABLE										= WCHARI(L"Enable");
	I18N.STATE_DISABLE										= WCHARI(L"Disable");
	I18N.STATE_WAITING										= WCHARI(L"Waiting...");

	I18N.HELP_IFMOUSE										= WCHARI(L"If mouse requirement:\n\
If a mouse is already in use\n\
double, if none mouse is actually in use");
	I18N.HELP_FORCE											= WCHARI(L"Force overpass:\n\
Ignore if a button has been disabled by a precedent mapping\n\
double, this will work only if this mapping is already working");
	I18N.HELP_ORXOR											= WCHARI(L"OrXor condition:\n\
'or' instead of simple combination\n\
double, 'xor' conditions instead of simple combination\n\
If only first 'or' is used and first source is killed\n\
	to launch the mapping\n\
	(for example, pushed more than a short press),\n\
	and still pushed, second source is still available.\n\
	But both will have to be released\n\
	to be available to trigger the mapping again");
	I18N.HELP_NOT											= WCHARI(L"Not condition:\n\
The mapping won't be launched if this button is pressed\n\
double, except if this mapping is already running\n\
See 'Pause' for more informations about not condition");
	I18N.HELP_SOURCE										= WCHARI(L"Source selection:\n\
swap between DS or vJoy (V)");
	I18N.HELP_DESTINATION									= WCHARI(L"Destination selection:\n\
Swap between vJoy\n\
Simple, Mouse actions (M)\n\
Double, Sound, modes, window, stats and time actions (S)\n\
Triple, Axis movements (A)");
	I18N.HELP_DISABLING_S									= WCHARI(L"Disabling post action:\n\
This button will be disabled for next mappings\n\
	if this mapping is running (except with Force)\n\
double (only source),\n\
	if Short (or Double), even when release time,\n\
	before time to activate spent (or second press)");
	I18N.HELP_DISABLING_D									= WCHARI(L"Disabling post action:\n\
This button will be disabled for next mappings\n\
	if this mapping is running\n\
double (only destination),\n\
	if time stamp is in use, disabling will be effective\n\
	until whole mapping is finished instead this destination only");
	I18N.HELP_MACRO											= WCHARI(L"Macro modificator:\n\
simple, Interrupt:\n\
	Interrupt macros on release(even if timestamp not finished)\n\
double, No sustain :\n\
	we use release value of first source instead of 0xFF\n\
	if timestamp is still in use and we have released sources\n\
	second source too if first is not pushed and OrXor1\n\
	third source too if first is not pushed, second isn't in used and OrXor1 + OrXor2");
	I18N.HELP_PAUSE											= WCHARI(L"Pause modificator:\n\
simple, Pause:\n\
	Pause this mapping while a 'not' condition\n\
otherwise :\n\
	if 'not' is a simple, and 'not' button is pressed, the mapping is interrupted\n\
	if 'not' is a double, and 'not' button is pressed, the mapping still continue\n\
double : One time, used in Transitivity as a modificator or action (see Transitivity)");
	I18N.HELP_TRANSITIVITY									= WCHARI(L"Transitivity modificator:\n\
simple, Transitivity:\n\
	bring different transitions while mode changed\n\
double, Come back:\n\
	another way of transitivity which brings its owns\n\
One time : Conduct\n\
	If the source is already pushed when entering the new mode,\n\
	the mapping is triggered\n\
Transitivity : Complete\n\
	You can release and trigger again in new mode\n\
	if it was already active before changing mode\n\
Transitivity + One time : Limited\n\
	Action continue while changing mode,\n\
	but you can't trigger again if release\n\
Come back : Retroactive\n\
	Instead of continuation, button is released,\n\
	but triggered again if still pushed when initial mode is back\n\
Come back + One time : One time back\n\
	The same as Retroactive, but while pushed,\n\
	you can change modeand get it triggered again only one time.\n\
	After, you have to releaseand trigger it again in its own mode\n\
in any case, except conduct,\n\
	you cannot launch the mapping of a mode when another mode is active,\n\
	if it was not activated before this change of mode");
	I18N.HELP_TOGGLE										= WCHARI(L"Toggle modificator:\n\
Satisfy mapping condition once to start, once again one to stop\n\
double, destinations states begin activated at program launch\n\
Can be used to time based mouse actions too\n\
	and for mouse if ACTIVE_MOUSE special action is used");
	I18N.HELP_SWITCH										= WCHARI(L"Switch overpass:\n\
simple, On\n\
	double, Off\n\
Switch can be use in conjunction or independently from Toggle\n\
	In conjuction it forces the toggle state\n\
	Otherwize it acts as a linear commutator");
	I18N.HELP_OVERCONTROL									= WCHARI(L"Overcontrol modificator:\n\
Like for normal axis, the value of axis movement takes place over last axis values\n\
	of the same type (for example X, XTR, XINV, XY_C_UR: XY center to UpRight)\n\
	but you can use Overcontrol checkbox to fuse values\n\
double, Protect : further axis action which should overpass this one won't be permit\n\
	(may be used on other vJoy buttons)\n\
	if there are merged vJoy axes of type X, Y, Z, RZ in the mapping,\n\
	the threshold is removed on, respectively, the LX, LY, RX, RY axes of ds");
	I18N.HELP_START											= WCHARI(L"Start Time stamp:\n\
Enter start (if not as soon as)\n\
If you enter an odd number,\n\
	0 - 9 milliseconds will be added,\n\
	different each time");
	I18N.HELP_END											= WCHARI(L"End Time stamp:\n\
Enter end (if not when release)\n\
If you enter an odd number,\n\
	0 - 9 milliseconds will be added,\n\
	different each time");
	I18N.HELP_ONRELEASE										= WCHARI(L"OnRelease condition:\n\
To begin the action on release\n\
double, only the up press,\n\
	even if some other timestamps are finished");
	I18N.HELP_NORELEASE										= WCHARI(L"NoRelease modificator:\n\
To decide to not do release action\n\
	while transitivity mode active and mode changed\n\
double, one turn of this release action\n\
	will still be performed then stopped");
	I18N.HELP_NLRELEASE										= WCHARI(L"NlRelease (normal release) overpass:\n\
To decide not perform NoRelease condition\n\
	if back to initial mode\n\
double, not perform NoRelease condition\n\
	while the new mode");
	I18N.HELP_SHORT											= WCHARI(L"Short condition:\n\
Short\n\
	Simple:\n\
	You have to press and release quickly\n\
	you'll have to use timestamp or On release\n\
	Time: Immediate\n\
Short & Double\n\
	Double short:\n\
	Second press acting like short\n\
	you'll have to use timestamp or On release\n\
	Time: ~first press and second press < long\n\
		+ second press duration > long\n\
Short & Long\n\
	Medium long:\n\
	Like long but after double long\n\
	Time: ~press > twice the time as long\n\
All\n\
	Very long\n\
	Time: found in settings");
	I18N.HELP_DOUBLE										= WCHARI(L"Double condition:\n\
Double\n\
	You'll have to double press in a limited time\n\
	Time: ~first press and second press < long\n\
Short & Double\n\
	Double short:\n\
	Second press acting like short\n\
	you'll have to use timestamp or On release\n\
	Time: ~first press and second press < long\n\
		+ second press duration > long\n\
Double & Long\n\
	Double long:\n\
	Second press acting like long\n\
	Time: ~press > twice the time as long\n\
All\n\
	Very long\n\
	Time: found in settings");
	I18N.HELP_LONG											= WCHARI(L"Long condition:\n\
Long\n\
	You have to stay pressed from a certain time\n\
	Time: found in settings\n\
Short & Long\n\
	Medium long:\n\
	Like long but after double long\n\
	Time: ~press > twice the time as long\n\
Double & Long\n\
	Double long:\n\
	Second press acting like long\n\
	Time: ~press > twice the time as long\n\
All\n\
	Very long\n\
	Time: found in settings");
	I18N.HELP_MOUSE_L1										= WCHARI(L"Left stick:\n\
Absolute\n\
	you move at a point which correspond\n\
	to the coordinates of the stick or touchpad");
	I18N.HELP_MOUSE_L2										= WCHARI(L"Left stick:\n\
Mouse\n\
	as a normal mouse with acceleration");
	I18N.HELP_MOUSE_L3										= WCHARI(L"Left stick:\n\
Move\n\
	adapted for game movements");
	I18N.HELP_MOUSE_L4										= WCHARI(L"Left stick:\n\
Sniper\n\
	extreme precision");
	I18N.HELP_MOUSE_L5										= WCHARI(L"Left stick:\n\
Raid\n\
move inside a zone whom coordinates\n\
are entered in numbers group at the right");
	I18N.HELP_MOUSE_T1										= WCHARI(L"Touchpad:\n\
Absolute\n\
	you move at a point which correspond\n\
	to the coordinates of the stick or touchpad");
	I18N.HELP_MOUSE_T2										= WCHARI(L"Touchpad:\n\
Mouse\n\
	as a normal mouse with acceleration");
	I18N.HELP_MOUSE_T3										= WCHARI(L"Touchpad:\n\
Slow\n\
	precise mouse");
	I18N.HELP_MOUSE_T4										= WCHARI(L"Touchpad:\n\
Accuracy\n\
	extreme precision");
	I18N.HELP_MOUSE_T5										= WCHARI(L"Touchpad:\n\
Grid\n\
	move inside a zone whom coordinates\n\
	are entered in numbers group at the right");
	I18N.HELP_MOUSE_R1										= WCHARI(L"Right stick:\n\
Absolute\n\
	you move at a point which correspond\n\
	to the coordinates of the stick or touchpad");
	I18N.HELP_MOUSE_R2										= WCHARI(L"Right stick:\n\
Mouse\n\
	as a normal mouse with acceleration");
	I18N.HELP_MOUSE_R3										= WCHARI(L"Right stick:\n\
Move\n\
	adapted for game movements");
	I18N.HELP_MOUSE_R4										= WCHARI(L"Right stick:\n\
Sniper\n\
	extreme precision");
	I18N.HELP_MOUSE_R5										= WCHARI(L"Right stick:\n\
Raid\n\
move inside a zone whom coordinates\n\
are entered in numbers group at the right");
	I18N.HELP_MOUSE_GRID									= WCHARI(L"Priority:\n\
when you have together raid / grid\n\
	and another mouse mode active,\n\
	determine which one is the default one\n\
unchecked: Raid / Grid is not the default one\n\
simple: Raid/Grid is the default one\n\
double: Remove previous (not the default again)");
	I18N.HELP_GRID_X										= WCHARI(L"x:\n\
Abscissa of first point (Move to x,y etc) or\n\
Abscissa of upper-left point of the Raid/Grid");
	I18N.HELP_GRID_Y										= WCHARI(L"y:\n\
Ordinate of first point (Move to x,y etc) or\n\
Ordinate of upper - left point of the Raid / Grid");
	I18N.HELP_GRID_W										= WCHARI(L"w:\n\
Abscissa of second point (Move to w,h etc) or\n\
Width of the Raid / Grid");
	I18N.HELP_GRID_H										= WCHARI(L"h:\n\
Ordinate of second point (Move to w,h etc) or\n\
Height of the Raid / Grid");
	I18N.HELP_GRID_NW										= WCHARI(L"nw:\n\
Abscissa of third point (Move to nw,nh etc) or\n\
Number of horizontal subdivisions");
	I18N.HELP_GRID_NH										= WCHARI(L"nh:\n\
Ordinate of third point (Move to nw,nh etc) or\n\
Number of horizontal subdivisions");
	I18N.HELP_DIGITS										= WCHARI(L"Digits:\n\
mouse coordinates,\n\
	to make it easier to enter special mouse actions\n\
click on the left number to start capture,\n\
	the color changes for 3s,\n\
	and after 3s it come back to its normal state\n\
	with the mouse point you were at captured\n\
while you already selected an element of the grid\n\
	(x, y or w, h or nw, nh)\n\
	click on the right number,\n\
	it will insert the coordinates into this column");
}

void FreeLanguage()
{
	if (I18N.SkipController== 0)
		return;
	delete[] I18N.EMPTY;
	delete[] I18N.DS2VJOY;
	delete[] I18N.APP_TITLE;
	delete[] I18N.FailedParse;
	delete[] I18N.FailedRecv;
	delete[] I18N.FailedSendCmd;
	delete[] I18N.FailedThread;
	delete[] I18N.MBOX_Delete;
	delete[] I18N.MBOX_ErrorWhileSaving;
	delete[] I18N.MBOX_ErrTitle;
	delete[] I18N.MBOX_NoButtonSelected;
	delete[] I18N.BT_CRC;
	delete[] I18N.BT_Size;
	delete[] I18N.Change_Settings;
	delete[] I18N.ConnectController;
	delete[] I18N.ConnectionStarted;
	delete[] I18N.DisconnectController;
	delete[] I18N.Firmware;
	delete[] I18N.FirmwareFail;
	delete[] I18N.Log_Wait_ds;
	delete[] I18N.Log_Wait_vJoy;
	delete[] I18N.Registry_Added;
	delete[] I18N.Registry_Removed;
	delete[] I18N.SkipController;
	delete[] I18N.Status_Wait;
	delete[] I18N.TT_AppNotFound;
	delete[] I18N.TT_ProfileChanged;
	delete[] I18N.vJoy_acquire;
	delete[] I18N.vJoy_busy;
	delete[] I18N.vJoy_cantuse;
	delete[] I18N.vJoy_failed_acquire;
	delete[] I18N.vJoy_failed_update;
	delete[] I18N.vJoy_version;
	delete[] I18N.Clone_of_Tab;
	delete[] I18N.TabLog;
	delete[] I18N.TabSettings;
	delete[] I18N.TabMapping;
	delete[] I18N.TabRapidFire;
	delete[] I18N.TabKeymap;
	delete[] I18N.TabViGEm;
	delete[] I18N.TabGuardian;
	delete[] I18N.TabExplorer;
	delete[] I18N.TabLinks;
	delete[] I18N.dsButton;
	delete[] I18N.vJoyButton;
	delete[] I18N.Notice;
	delete[] I18N.Setting;
	delete[] I18N.Process;
	delete[] I18N.RapidFire_State1;
	delete[] I18N.RapidFire_State2;
	delete[] I18N.RapidFire_State3;
	delete[] I18N.TagsButton;
	delete[] I18N.Button_LX;
	delete[] I18N.Button_LY;
	delete[] I18N.Button_RX;
	delete[] I18N.Button_RY;
	delete[] I18N.Button_L3;
	delete[] I18N.Button_DPAD_LEFT;
	delete[] I18N.Button_DPAD_UP;
	delete[] I18N.Button_DPAD_RIGHT;
	delete[] I18N.Button_DPAD_DOWN;
	delete[] I18N.Button_SHARE;
	delete[] I18N.Button_OPTIONS;
	delete[] I18N.Button_SQUARE;
	delete[] I18N.Button_TRIANGLE;
	delete[] I18N.Button_CIRCLE;
	delete[] I18N.Button_CROSS;
	delete[] I18N.Button_R3;
	delete[] I18N.Button_PS;
	delete[] I18N.Button_TOUCH;
	delete[] I18N.Button_MUTE;
	delete[] I18N.Button_L1;
	delete[] I18N.Button_R1;
	delete[] I18N.Button_L2;
	delete[] I18N.Button_R2;
	delete[] I18N.Button_L2TRIGGER;
	delete[] I18N.Button_R2TRIGGER;
	delete[] I18N.Button_EMPTY;
	delete[] I18N.Button_MIDDLE;
	delete[] I18N.Button_FULL;
	delete[] I18N.Button_LX_INV;
	delete[] I18N.Button_LY_INV;
	delete[] I18N.Button_RX_INV;
	delete[] I18N.Button_RY_INV;
	delete[] I18N.Button_SNIPER_LX;
	delete[] I18N.Button_SNIPER_LY;
	delete[] I18N.Button_SNIPER_RX;
	delete[] I18N.Button_SNIPER_RY;
	delete[] I18N.Button_AXISL_TR_LEFT;
	delete[] I18N.Button_AXISL_TR_UP;
	delete[] I18N.Button_AXISL_TR_RIGHT;
	delete[] I18N.Button_AXISL_TR_DOWN;
	delete[] I18N.Button_AXISR_TR_LEFT;
	delete[] I18N.Button_AXISR_TR_UP;
	delete[] I18N.Button_AXISR_TR_RIGHT;
	delete[] I18N.Button_AXISR_TR_DOWN;
	delete[] I18N.Button_AXISL_LEFT;
	delete[] I18N.Button_AXISL_UP_LEFT;
	delete[] I18N.Button_AXISL_UP;
	delete[] I18N.Button_AXISL_UP_RIGHT;
	delete[] I18N.Button_AXISL_RIGHT;
	delete[] I18N.Button_AXISL_DOWN_RIGHT;
	delete[] I18N.Button_AXISL_DOWN;
	delete[] I18N.Button_AXISL_DOWN_LEFT;
	delete[] I18N.Button_AXISR_LEFT;
	delete[] I18N.Button_AXISR_UP_LEFT;
	delete[] I18N.Button_AXISR_UP;
	delete[] I18N.Button_AXISR_UP_RIGHT;
	delete[] I18N.Button_AXISR_RIGHT;
	delete[] I18N.Button_AXISR_DOWN_RIGHT;
	delete[] I18N.Button_AXISR_DOWN;
	delete[] I18N.Button_AXISR_DOWN_LEFT;
	delete[] I18N.Button_TOUCH_UP;
	delete[] I18N.Button_TOUCHPAD;
	delete[] I18N.Button_TOUCH_1;
	delete[] I18N.Button_TOUCH_2;
	delete[] I18N.Button_TOUCH_3;
	delete[] I18N.Button_TOUCH_4;
	delete[] I18N.Button_TOUCH_L;
	delete[] I18N.Button_TOUCH_R;
	delete[] I18N.Button_L2TRIGGER_33;
	delete[] I18N.Button_R2TRIGGER_33;
	delete[] I18N.Button_L2TRIGGER_66;
	delete[] I18N.Button_R2TRIGGER_66;
	delete[] I18N.Button_L2TRIGGER_100;
	delete[] I18N.Button_R2TRIGGER_100;
	delete[] I18N.Button_L1R1;
	delete[] I18N.Button_L2R2;
	delete[] I18N.Button_BATTERY;
	delete[] I18N.vJoy_X;
	delete[] I18N.vJoy_Y;
	delete[] I18N.vJoy_Z;
	delete[] I18N.vJoy_RX;
	delete[] I18N.vJoy_RY;
	delete[] I18N.vJoy_RZ;
	delete[] I18N.vJoy_SL0;
	delete[] I18N.vJoy_SL1;
	delete[] I18N.vJoy_XTR;
	delete[] I18N.vJoy_YTR;
	delete[] I18N.vJoy_ZTR;
	delete[] I18N.vJoy_RXTR;
	delete[] I18N.vJoy_RYTR;
	delete[] I18N.vJoy_RZTR;
	delete[] I18N.vJoy_SL0TR;
	delete[] I18N.vJoy_SL1TR;
	delete[] I18N.vJoy_XINV;
	delete[] I18N.vJoy_YINV;
	delete[] I18N.vJoy_ZINV;
	delete[] I18N.vJoy_RXINV;
	delete[] I18N.vJoy_RYINV;
	delete[] I18N.vJoy_RZINV;
	delete[] I18N.vJoy_SL0INV;
	delete[] I18N.vJoy_SL1INV;
	delete[] I18N.vJoy_DPAD1_LEFT;
	delete[] I18N.vJoy_DPAD1_UP_LEFT;
	delete[] I18N.vJoy_DPAD1_UP;
	delete[] I18N.vJoy_DPAD1_UP_RIGHT;
	delete[] I18N.vJoy_DPAD1_RIGHT;
	delete[] I18N.vJoy_DPAD1_DOWN_RIGHT;
	delete[] I18N.vJoy_DPAD1_DOWN;
	delete[] I18N.vJoy_DPAD1_DOWN_LEFT;
	delete[] I18N.vJoy_DPAD2_LEFT;
	delete[] I18N.vJoy_DPAD2_UP_LEFT;
	delete[] I18N.vJoy_DPAD2_UP;
	delete[] I18N.vJoy_DPAD2_UP_RIGHT;
	delete[] I18N.vJoy_DPAD2_RIGHT;
	delete[] I18N.vJoy_DPAD2_DOWN_RIGHT;
	delete[] I18N.vJoy_DPAD2_DOWN;
	delete[] I18N.vJoy_DPAD2_DOWN_LEFT;
	delete[] I18N.vJoy_DPAD3_LEFT;
	delete[] I18N.vJoy_DPAD3_UP_LEFT;
	delete[] I18N.vJoy_DPAD3_UP;
	delete[] I18N.vJoy_DPAD3_UP_RIGHT;
	delete[] I18N.vJoy_DPAD3_RIGHT;
	delete[] I18N.vJoy_DPAD3_DOWN_RIGHT;
	delete[] I18N.vJoy_DPAD3_DOWN;
	delete[] I18N.vJoy_DPAD3_DOWN_LEFT;
	delete[] I18N.vJoy_DPAD4_LEFT;
	delete[] I18N.vJoy_DPAD4_UP_LEFT;
	delete[] I18N.vJoy_DPAD4_UP;
	delete[] I18N.vJoy_DPAD4_UP_RIGHT;
	delete[] I18N.vJoy_DPAD4_RIGHT;
	delete[] I18N.vJoy_DPAD4_DOWN_RIGHT;
	delete[] I18N.vJoy_DPAD4_DOWN;
	delete[] I18N.vJoy_DPAD4_DOWN_LEFT;
	delete[] I18N.LedAction_Led_1;
	delete[] I18N.LedAction_Led_2;
	delete[] I18N.LedAction_Led_3;
	delete[] I18N.LedAction_Led_4;
	delete[] I18N.LedAction_Led_5;
	delete[] I18N.LedAction_BATTERY;
	delete[] I18N.MouseAction_ACTIVE_MOUSE;
	delete[] I18N.MouseAction_SAVE_POSITION;
	delete[] I18N.MouseAction_MOVE_BACK;
	delete[] I18N.MouseAction_MOVE_TO_XY;
	delete[] I18N.MouseAction_MOVE_TO_WH;
	delete[] I18N.MouseAction_MOVE_TO_NN;
	delete[] I18N.MouseAction_SAVE_AND_MOVE_TO_XY;
	delete[] I18N.MouseAction_SAVE_AND_MOVE_TO_WH;
	delete[] I18N.MouseAction_SAVE_AND_MOVE_TO_NN;
	delete[] I18N.MouseAction_GRID_LEFT;
	delete[] I18N.MouseAction_GRID_UP;
	delete[] I18N.MouseAction_GRID_RIGHT;
	delete[] I18N.MouseAction_GRID_DOWN;
	delete[] I18N.MouseAction_LEFT_CLICK;
	delete[] I18N.MouseAction_MIDDLE_CLICK;
	delete[] I18N.MouseAction_RIGHT_CLICK;
	delete[] I18N.MouseAction_X1_CLICK;
	delete[] I18N.MouseAction_X2_CLICK;
	delete[] I18N.MouseAction_SCROLL_UP;
	delete[] I18N.MouseAction_SCROLL_DOWN;
	delete[] I18N.MouseAction_LEFT_DOUBLE_CLICK;
	delete[] I18N.MouseAction_MIDDLE_DOUBLE_CLICK;
	delete[] I18N.MouseAction_RIGHT_DOUBLE_CLICK;
	delete[] I18N.MouseAction_X1_DOUBLE_CLICK;
	delete[] I18N.MouseAction_X2_DOUBLE_CLICK;
	delete[] I18N.MouseAction_SCROLL_UP_x5;
	delete[] I18N.MouseAction_SCROLL_DOWN_x5;
	delete[] I18N.MouseAction_LEFT_DOWN;
	delete[] I18N.MouseAction_MIDDLE_DOWN;
	delete[] I18N.MouseAction_RIGHT_DOWN;
	delete[] I18N.MouseAction_X1_DOWN;
	delete[] I18N.MouseAction_X2_DOWN;
	delete[] I18N.MouseAction_SCROLL_UP_VARIABLE;
	delete[] I18N.MouseAction_SCROLL_DOWN_VARIABLE;
	delete[] I18N.MouseAction_MUTE_SOUND;
	delete[] I18N.MouseAction_VOLUME_UP;
	delete[] I18N.MouseAction_VOLUME_DOWN;
	delete[] I18N.MouseAction_MEMORIZE_MODE;
	delete[] I18N.MouseAction_TO_MEM_MODE;
	delete[] I18N.MouseAction_TO_MODE;
	delete[] I18N.MouseAction_TO_LAST_MODE;
	delete[] I18N.MouseAction_BASE_TO_MODE;
	delete[] I18N.MouseAction_TO_BASE_MODE;
	delete[] I18N.MouseAction_IF_RELEASED_GOTO;
	delete[] I18N.MouseAction_IF_PUSHED_GOTO;
	delete[] I18N.MouseAction_RETURN_TO;
	delete[] I18N.MouseAction_FORGOT_RELEASED;
	delete[] I18N.MouseAction_MOUSE_INTERRUPT;
	delete[] I18N.MouseAction_MOUSE_NO_SUSTAIN;
	delete[] I18N.MouseAction_MOUSE_PAUSE;
	delete[] I18N.MouseAction_BEEP1;
	delete[] I18N.MouseAction_BEEP2;
	delete[] I18N.MouseAction_BEEP3;
	delete[] I18N.MouseAction_RESET_STATS;
	delete[] I18N.MouseAction_ADDSTAT1;
	delete[] I18N.MouseAction_ADDSTAT2;
	delete[] I18N.MouseAction_ADDSTAT3;
	delete[] I18N.MouseAction_ADDSTAT4;
	delete[] I18N.MouseAction_ADDSTAT5;
	delete[] I18N.MouseAction_ADDSTAT6;
	delete[] I18N.MouseAction_ADDSTAT7;
	delete[] I18N.MouseAction_ADDSTAT8;
	delete[] I18N.MouseAction_MINIMIZE;
	delete[] I18N.MouseAction_RESTORE;
	delete[] I18N.Axis_XY_CW;
	delete[] I18N.Axis_XY_CN;
	delete[] I18N.Axis_ZRZ_CW;
	delete[] I18N.Axis_ZRZ_CN;
	delete[] I18N.Axis_RXRY_CW;
	delete[] I18N.Axis_RXRY_CN;
	delete[] I18N.Axis_SL0SL1_CW;
	delete[] I18N.Axis_SL0SL1_CN;
	delete[] I18N.Axis_XY_CENTER;
	delete[] I18N.Axis_ZRZ_CENTER;
	delete[] I18N.Axis_XY_LEFT;
	delete[] I18N.Axis_XY_UP_LEFT;
	delete[] I18N.Axis_XY_UP;
	delete[] I18N.Axis_XY_UP_RIGHT;
	delete[] I18N.Axis_XY_RIGHT;
	delete[] I18N.Axis_XY_DOWN_RIGHT;
	delete[] I18N.Axis_XY_DOWN;
	delete[] I18N.Axis_XY_DOWN_LEFT;
	delete[] I18N.Axis_XY_Q1_CW;
	delete[] I18N.Axis_XY_Q1_CN;
	delete[] I18N.Axis_XY_Q2_CW;
	delete[] I18N.Axis_XY_Q2_CN;
	delete[] I18N.Axis_XY_Q3_CW;
	delete[] I18N.Axis_XY_Q3_CN;
	delete[] I18N.Axis_XY_Q4_CW;
	delete[] I18N.Axis_XY_Q4_CN;
	delete[] I18N.Axis_XY_E1_CW;
	delete[] I18N.Axis_XY_E1_CN;
	delete[] I18N.Axis_XY_E2_CW;
	delete[] I18N.Axis_XY_E2_CN;
	delete[] I18N.Axis_XY_E3_CW;
	delete[] I18N.Axis_XY_E3_CN;
	delete[] I18N.Axis_XY_E4_CW;
	delete[] I18N.Axis_XY_E4_CN;
	delete[] I18N.Axis_XY_E5_CW;
	delete[] I18N.Axis_XY_E5_CN;
	delete[] I18N.Axis_XY_E6_CW;
	delete[] I18N.Axis_XY_E6_CN;
	delete[] I18N.Axis_XY_E7_CW;
	delete[] I18N.Axis_XY_E7_CN;
	delete[] I18N.Axis_XY_E8_CW;
	delete[] I18N.Axis_XY_E8_CN;
	delete[] I18N.Axis_XY_C_L;
	delete[] I18N.Axis_XY_C_UL;
	delete[] I18N.Axis_XY_C_U;
	delete[] I18N.Axis_XY_C_UR;
	delete[] I18N.Axis_XY_C_R;
	delete[] I18N.Axis_XY_C_DR;
	delete[] I18N.Axis_XY_C_D;
	delete[] I18N.Axis_XY_C_DL;
	delete[] I18N.Axis_XY_2C_L;
	delete[] I18N.Axis_XY_2C_UL;
	delete[] I18N.Axis_XY_2C_U;
	delete[] I18N.Axis_XY_2C_UR;
	delete[] I18N.Axis_XY_2C_R;
	delete[] I18N.Axis_XY_2C_DR;
	delete[] I18N.Axis_XY_2C_D;
	delete[] I18N.Axis_XY_2C_DL;
	delete[] I18N.Axis_XY_D_L;
	delete[] I18N.Axis_XY_D_UL;
	delete[] I18N.Axis_XY_D_U;
	delete[] I18N.Axis_XY_D_UR;
	delete[] I18N.Axis_XY_D_R;
	delete[] I18N.Axis_XY_D_DR;
	delete[] I18N.Axis_XY_D_D;
	delete[] I18N.Axis_XY_D_DL;
	delete[] I18N.Axis_XY_T_UL_CW;
	delete[] I18N.Axis_XY_T_UL_CN;
	delete[] I18N.Axis_XY_T_UR_CW;
	delete[] I18N.Axis_XY_T_UR_CN;
	delete[] I18N.Axis_XY_T_DR_CW;
	delete[] I18N.Axis_XY_T_DR_CN;
	delete[] I18N.Axis_XY_T_DL_CW;
	delete[] I18N.Axis_XY_T_DL_CN;
	delete[] I18N.Axis_XY_S_L_CW;
	delete[] I18N.Axis_XY_S_L_CN;
	delete[] I18N.Axis_XY_S_U_CW;
	delete[] I18N.Axis_XY_S_U_CN;
	delete[] I18N.Axis_XY_S_R_CW;
	delete[] I18N.Axis_XY_S_R_CN;
	delete[] I18N.Axis_XY_S_D_CW;
	delete[] I18N.Axis_XY_S_D_CN;
	delete[] I18N.Axis_XY_L_UL_CW;
	delete[] I18N.Axis_XY_L_UL_CN;
	delete[] I18N.Axis_XY_L_UR_CW;
	delete[] I18N.Axis_XY_L_UR_CN;
	delete[] I18N.Axis_XY_L_DR_CW;
	delete[] I18N.Axis_XY_L_DR_CN;
	delete[] I18N.Axis_XY_L_DL_CW;
	delete[] I18N.Axis_XY_L_DL_CN;
	delete[] I18N.Axis_ZRZ_LEFT;
	delete[] I18N.Axis_ZRZ_UP_LEFT;
	delete[] I18N.Axis_ZRZ_UP;
	delete[] I18N.Axis_ZRZ_UP_RIGHT;
	delete[] I18N.Axis_ZRZ_RIGHT;
	delete[] I18N.Axis_ZRZ_DOWN_RIGHT;
	delete[] I18N.Axis_ZRZ_DOWN;
	delete[] I18N.Axis_ZRZ_DOWN_LEFT;
	delete[] I18N.Axis_ZRZ_Q1_CW;
	delete[] I18N.Axis_ZRZ_Q1_CN;
	delete[] I18N.Axis_ZRZ_Q2_CW;
	delete[] I18N.Axis_ZRZ_Q2_CN;
	delete[] I18N.Axis_ZRZ_Q3_CW;
	delete[] I18N.Axis_ZRZ_Q3_CN;
	delete[] I18N.Axis_ZRZ_Q4_CW;
	delete[] I18N.Axis_ZRZ_Q4_CN;
	delete[] I18N.Axis_ZRZ_E1_CW;
	delete[] I18N.Axis_ZRZ_E1_CN;
	delete[] I18N.Axis_ZRZ_E2_CW;
	delete[] I18N.Axis_ZRZ_E2_CN;
	delete[] I18N.Axis_ZRZ_E3_CW;
	delete[] I18N.Axis_ZRZ_E3_CN;
	delete[] I18N.Axis_ZRZ_E4_CW;
	delete[] I18N.Axis_ZRZ_E4_CN;
	delete[] I18N.Axis_ZRZ_E5_CW;
	delete[] I18N.Axis_ZRZ_E5_CN;
	delete[] I18N.Axis_ZRZ_E6_CW;
	delete[] I18N.Axis_ZRZ_E6_CN;
	delete[] I18N.Axis_ZRZ_E7_CW;
	delete[] I18N.Axis_ZRZ_E7_CN;
	delete[] I18N.Axis_ZRZ_E8_CW;
	delete[] I18N.Axis_ZRZ_E8_CN;
	delete[] I18N.Axis_ZRZ_C_L;
	delete[] I18N.Axis_ZRZ_C_UL;
	delete[] I18N.Axis_ZRZ_C_U;
	delete[] I18N.Axis_ZRZ_C_UR;
	delete[] I18N.Axis_ZRZ_C_R;
	delete[] I18N.Axis_ZRZ_C_DR;
	delete[] I18N.Axis_ZRZ_C_D;
	delete[] I18N.Axis_ZRZ_C_DL;
	delete[] I18N.Axis_ZRZ_2C_L;
	delete[] I18N.Axis_ZRZ_2C_UL;
	delete[] I18N.Axis_ZRZ_2C_U;
	delete[] I18N.Axis_ZRZ_2C_UR;
	delete[] I18N.Axis_ZRZ_2C_R;
	delete[] I18N.Axis_ZRZ_2C_DR;
	delete[] I18N.Axis_ZRZ_2C_D;
	delete[] I18N.Axis_ZRZ_2C_DL;
	delete[] I18N.Axis_ZRZ_D_L;
	delete[] I18N.Axis_ZRZ_D_UL;
	delete[] I18N.Axis_ZRZ_D_U;
	delete[] I18N.Axis_ZRZ_D_UR;
	delete[] I18N.Axis_ZRZ_D_R;
	delete[] I18N.Axis_ZRZ_D_DR;
	delete[] I18N.Axis_ZRZ_D_D;
	delete[] I18N.Axis_ZRZ_D_DL;
	delete[] I18N.Axis_ZRZ_T_UL_CW;
	delete[] I18N.Axis_ZRZ_T_UL_CN;
	delete[] I18N.Axis_ZRZ_T_UR_CW;
	delete[] I18N.Axis_ZRZ_T_UR_CN;
	delete[] I18N.Axis_ZRZ_T_DR_CW;
	delete[] I18N.Axis_ZRZ_T_DR_CN;
	delete[] I18N.Axis_ZRZ_T_DL_CW;
	delete[] I18N.Axis_ZRZ_T_DL_CN;
	delete[] I18N.Axis_ZRZ_S_L_CW;
	delete[] I18N.Axis_ZRZ_S_L_CN;
	delete[] I18N.Axis_ZRZ_S_U_CW;
	delete[] I18N.Axis_ZRZ_S_U_CN;
	delete[] I18N.Axis_ZRZ_S_R_CW;
	delete[] I18N.Axis_ZRZ_S_R_CN;
	delete[] I18N.Axis_ZRZ_S_D_CW;
	delete[] I18N.Axis_ZRZ_S_D_CN;
	delete[] I18N.Axis_ZRZ_L_UL_CW;
	delete[] I18N.Axis_ZRZ_L_UL_CN;
	delete[] I18N.Axis_ZRZ_L_UR_CW;
	delete[] I18N.Axis_ZRZ_L_UR_CN;
	delete[] I18N.Axis_ZRZ_L_DR_CW;
	delete[] I18N.Axis_ZRZ_L_DR_CN;
	delete[] I18N.Axis_ZRZ_L_DL_CW;
	delete[] I18N.Axis_ZRZ_L_DL_CN;
	delete[] I18N.Gamepad_LEFT_STICK;
	delete[] I18N.Gamepad_BACK;
	delete[] I18N.Gamepad_START;
	delete[] I18N.Gamepad_X;
	delete[] I18N.Gamepad_Y;
	delete[] I18N.Gamepad_B;
	delete[] I18N.Gamepad_A;
	delete[] I18N.Gamepad_RIGHT_STICK;
	delete[] I18N.Gamepad_GUIDE;
	delete[] I18N.Gamepad_LEFT_BUMPER;
	delete[] I18N.Gamepad_RIGHT_BUMPER;
	delete[] I18N.Gamepad_LEFT_TRIGGER;
	delete[] I18N.Gamepad_RIGHT_TRIGGER;

	delete[] I18N.ABOUT_1;
	delete[] I18N.ABOUT_2;
	delete[] I18N.ABOUT_3;
	delete[] I18N.ABOUT_OK;
	delete[] I18N.SETTINGS_PREFERRED_DS;
	delete[] I18N.SETTINGS_DS4;
	delete[] I18N.SETTINGS_DS5;
	delete[] I18N.SETTINGS_KBD;
	delete[] I18N.SETTINGS_MSE;
	delete[] I18N.SETTINGS_TEXT_VJOY_DEVICE;
	delete[] I18N.SETTINGS_STARTUP;
	delete[] I18N.SETTINGS_START_MINIMIZED;
	delete[] I18N.SETTINGS_CLOSE_MINIMIZE;
	delete[] I18N.SETTINGS_DISCONNECT_BT;
	delete[] I18N.SETTINGS_MOUSE_CAN_BYPASS;
	delete[] I18N.SETTINGS_ALERT_ON_LOWBATTS;
	delete[] I18N.SETTINGS_TRIGGERS_MODE;
	delete[] I18N.SETTINGS_TRIGGERS_NONE;
	delete[] I18N.SETTINGS_TRIGGERS_SHOOT;
	delete[] I18N.SETTINGS_TRIGGERS_RESIST;
	delete[] I18N.SETTINGS_TRIGGERS_PROACTIVE;
	delete[] I18N.SETTINGS_USE_THE_DS_SERIAL;
	delete[] I18N.SETTINGS_DARK_THEME;
	delete[] I18N.SETTINGS_TEXT_THRESHOLD;
	delete[] I18N.SETTINGS_TEXT_SIMULTANEOUS;
	delete[] I18N.SETTINGS_TEXT_LONG;
	delete[] I18N.SETTINGS_TEXT_VERY_LONG;
	delete[] I18N.SETTINGS_TEXT_WEBREFRESH;
	delete[] I18N.SETTINGS_UNIT_THRESHOLD;
	delete[] I18N.SETTINGS_UNIT_SIMULTANEOUS;
	delete[] I18N.SETTINGS_UNIT_LONG;
	delete[] I18N.SETTINGS_UNIT_VERY_LONG;
	delete[] I18N.SETTINGS_UNIT_WEB_REFRESH;
	delete[] I18N.SETTINGS_MULTIPLE_TOUCHPAD;
	delete[] I18N.SETTINGS_TEXT_FIRST_BUTTON;
	delete[] I18N.SETTINGS_TEXT_COLUMN;
	delete[] I18N.SETTINGS_TEXT_ROW;
	delete[] I18N.SETTINGS_LED;
	delete[] I18N.SETTINGS_WHEN_EXITING;
	delete[] I18N.SETTINGS_LED_BUTTON;
	delete[] I18N.SETTINGS_COLOR;
	delete[] I18N.CLONE_MENU;
	delete[] I18N.CLONE_STATS;
	delete[] I18N.CLONE_STAT1;
	delete[] I18N.CLONE_STAT2;
	delete[] I18N.CLONE_STAT3;
	delete[] I18N.CLONE_STAT4;
	delete[] I18N.CLONE_STAT5;
	delete[] I18N.CLONE_STAT6;
	delete[] I18N.CLONE_STAT7;
	delete[] I18N.CLONE_STAT8;
	delete[] I18N.CLONE_CANCEL;
	delete[] I18N.CLONE_CLEAR;
	delete[] I18N.CLONE_POSTIT;
	delete[] I18N.MAPPING_HELP;
	delete[] I18N.MAPPING_OK;
	delete[] I18N.MAPPING_CLEAR;
	delete[] I18N.MAPPING_CANCEL;
	delete[] I18N.MAPPING_X;
	delete[] I18N.MAPPING_Y;
	delete[] I18N.MIND_OK;
	delete[] I18N.MIND_CANCEL;
	delete[] I18N.RAPIDFIRE_RAPIDFIRE;
	delete[] I18N.RAPIDFIRE_MULTIPLE_PRESS;
	delete[] I18N.RAPIDFIRE_TEXT_FIRST;
	delete[] I18N.RAPIDFIRE_TEXT_RELEASE;
	delete[] I18N.RAPIDFIRE_TEXT_DOWN;
	delete[] I18N.RAPIDFIRE_UNIT_FIRST;
	delete[] I18N.RAPIDFIRE_UNIT_RELEASE;
	delete[] I18N.RAPIDFIRE_UNIT_DOWN;
	delete[] I18N.RAPIDFIRE_NOTICE;
	delete[] I18N.RAPIDFIRE_OK;
	delete[] I18N.RAPIDFIRE_CANCEL;
	delete[] I18N.KEYMAP_SOURCE;
	delete[] I18N.KEYMAP_RESTORE;
	delete[] I18N.KEYMAP_MAXIMIZE;
	delete[] I18N.KEYMAP_SHOW;
	delete[] I18N.KEYMAP_ACTIVATING;
	delete[] I18N.KEYMAP_SEND;
	delete[] I18N.KEYMAP_ENTER;
	delete[] I18N.KEYMAP_CLEAR;
	delete[] I18N.KEYMAP_NATURAL;
	delete[] I18N.KEYMAP_POSTMESSAGE;
	delete[] I18N.KEYMAP_FINDWINDOW;
	delete[] I18N.KEYMAP_METHOD;
	delete[] I18N.KEYMAP_EXTENDEDKEY;
	delete[] I18N.KEYMAP_SCANCODE;
	delete[] I18N.KEYMAP_OK;
	delete[] I18N.KEYMAP_CANCEL;
	delete[] I18N.KEYMAP_WINDOW;
	delete[] I18N.KEYMAP_IS_W_VISIBLE;
	delete[] I18N.KEYMAP_CLEAR2;
	delete[] I18N.KEYMAP_DELETE;
	delete[] I18N.KEYMAP_OK2;
	delete[] I18N.KEYMAP_CANCEL2;
	delete[] I18N.VIGEM_ACTIVE;
	delete[] I18N.VIGEM_PAD;
	delete[] I18N.VIGEM_X360;
	delete[] I18N.VIGEM_DS4;
	delete[] I18N.VIGEM_INSTALL;
	delete[] I18N.VIGEM_STATUS;
	delete[] I18N.HID_ACTIVE;
	delete[] I18N.HID_BLACKLIST;
	delete[] I18N.HID_REMOVE;
	delete[] I18N.HID_WHITELIST;
	delete[] I18N.HID_PURGE;
	delete[] I18N.HID_CERBERUS_LINK;
	delete[] I18N.HID_CERBERUS_URL;
	delete[] I18N.HID_INSTALL;
	delete[] I18N.HID_GUARDIAN_INSTALL;
	delete[] I18N.HID_GUARDIAN_STATUS;
	delete[] I18N.HID_CERBERUS_INSTALL;
	delete[] I18N.HID_CERBERUS_STATUS;
	delete[] I18N.HID_LEGEND;
	delete[] I18N.HID_LEGEND2;
	delete[] I18N.HID_LEGEND1;
	delete[] I18N.HID_LEGEND3;
	delete[] I18N.HID_LEGEND4;
	delete[] I18N.HID_LEGEND5;
	delete[] I18N.LINKS_TEXT1;
	delete[] I18N.LINKS_TEXT2;
	delete[] I18N.LINKS_TEXT3;
	delete[] I18N.LINKS_TEXT4;
	delete[] I18N.LINKS_DS4VJOY;
	delete[] I18N.LINKS_VJOY;
	delete[] I18N.LINKS_WEBVIEW2;
	delete[] I18N.LINKS_VIGEMBUS;
	delete[] I18N.LINKS_VIGEMCLIENT;
	delete[] I18N.LINKS_HIDGUARDIAN;
	delete[] I18N.LINKS_HIDCERBERUS;
	delete[] I18N.LINKS_URL_DS4VJOY;
	delete[] I18N.LINKS_URL_VJOY;
	delete[] I18N.LINKS_URL_WEBVIEW2;
	delete[] I18N.LINKS_URL_VIGEMBUS;
	delete[] I18N.LINKS_URL_VIGEMCLIENT;
	delete[] I18N.LINKS_URL_HIDGUARDIAN;
	delete[] I18N.LINKS_URL_HIDCERBERUS;
	delete[] I18N.NOTEPAD_UNSAVED;

	delete[] I18N.STATE_INSTALL;
	delete[] I18N.STATE_UNINSTALL;
	delete[] I18N.STATE_START;
	delete[] I18N.STATE_STOP;
	delete[] I18N.STATE_RESTART;
	delete[] I18N.STATE_ENABLE;
	delete[] I18N.STATE_DISABLE;
	delete[] I18N.STATE_WAITING;
	
	delete[] I18N.HELP_IFMOUSE;
	delete[] I18N.HELP_FORCE;
	delete[] I18N.HELP_SHORT;
	delete[] I18N.HELP_DOUBLE;
	delete[] I18N.HELP_LONG;
	delete[] I18N.HELP_ORXOR;
	delete[] I18N.HELP_NOT;
	delete[] I18N.HELP_SOURCE;
	delete[] I18N.HELP_DESTINATION;
	delete[] I18N.HELP_DISABLING_S;
	delete[] I18N.HELP_DISABLING_D;
	delete[] I18N.HELP_MACRO;
	delete[] I18N.HELP_PAUSE;
	delete[] I18N.HELP_TRANSITIVITY;
	delete[] I18N.HELP_TOGGLE;
	delete[] I18N.HELP_SWITCH;
	delete[] I18N.HELP_OVERCONTROL;
	delete[] I18N.HELP_START;
	delete[] I18N.HELP_END;
	delete[] I18N.HELP_ONRELEASE;
	delete[] I18N.HELP_NORELEASE;
	delete[] I18N.HELP_NLRELEASE;
	delete[] I18N.HELP_MOUSE_L1;
	delete[] I18N.HELP_MOUSE_L2;
	delete[] I18N.HELP_MOUSE_L3;
	delete[] I18N.HELP_MOUSE_L4;
	delete[] I18N.HELP_MOUSE_L5;
	delete[] I18N.HELP_MOUSE_T1;
	delete[] I18N.HELP_MOUSE_T2;
	delete[] I18N.HELP_MOUSE_T3;
	delete[] I18N.HELP_MOUSE_T4;
	delete[] I18N.HELP_MOUSE_T5;
	delete[] I18N.HELP_MOUSE_R1;
	delete[] I18N.HELP_MOUSE_R2;
	delete[] I18N.HELP_MOUSE_R3;
	delete[] I18N.HELP_MOUSE_R4;
	delete[] I18N.HELP_MOUSE_R5;
	delete[] I18N.HELP_MOUSE_GRID;
	delete[] I18N.HELP_GRID_X;
	delete[] I18N.HELP_GRID_Y;
	delete[] I18N.HELP_GRID_W;
	delete[] I18N.HELP_GRID_H;
	delete[] I18N.HELP_GRID_NW;
	delete[] I18N.HELP_GRID_NH;
	delete[] I18N.HELP_DIGITS;
}
