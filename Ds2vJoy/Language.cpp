#include "stdafx.h"
#include "Language.h"

struct LANGSTRS I18N = { 0 };

void LoadLanguage()
{
	switch (tape.Country)
	{
	case CountryID::Country_UNITED_STATES:
	case CountryID::Country_ALBANIA:
	case CountryID::Country_ARMENIA:
	case CountryID::Country_AZERBAIJAN:
	case CountryID::Country_BOSNIA:
	case CountryID::Country_BULGARIA:
	case CountryID::Country_BRAZIL:
	case CountryID::Country_BELARUSIAN:
	case CountryID::Country_CANADA:
	case CountryID::Country_CHEROKEE:
	case CountryID::Country_CHINA_SIMPLIFIED:
	case CountryID::Country_SERBIA_LATIN:
	case CountryID::Country_CZECH_REPUBLIC:
	case CountryID::Country_GERMANY:
	case CountryID::Country_DENMARK:
	case CountryID::Country_ESTONIA:
	case CountryID::Country_SPAIN:
	case CountryID::Country_ETHIOPIA:
	case CountryID::Country_FINLAND:
	case CountryID::Country_FRANCE:
	case CountryID::Country_GREAT_BRITAIN:
	case CountryID::Country_GEORGIA:
	case CountryID::Country_GREECE:
	case CountryID::Country_HONG_KONG:
	case CountryID::Country_CROATIA:
	case CountryID::Country_HUNGARY:
	case CountryID::Country_INDONESIA:
	case CountryID::Country_IRELAND:
	case CountryID::Country_ISRAEL:
	case CountryID::Country_INDIA:
	case CountryID::Country_PERSIAN:
	case CountryID::Country_ICELAND:
	case CountryID::Country_ITALY:
	case CountryID::Country_JAPAN:
	case CountryID::Country_CAMBODIA:
	case CountryID::Country_KOREA:
	case CountryID::Country_KAZAKHSTAN:
	case CountryID::Country_LAOS:
	case CountryID::Country_LITHUANIA:
	case CountryID::Country_LUXEMBOURG:
	case CountryID::Country_LATVIA:
	case CountryID::Country_MACEDONIA:
	case CountryID::Country_MALTA:
	case CountryID::Country_MEXICO:
	case CountryID::Country_MALAYSIA_BRUNEI_SINGAPORE:
	case CountryID::Country_NETHERLANDS:
	case CountryID::Country_NORWAY:
	case CountryID::Country_NEPAL:
	case CountryID::Country_NEW_ZEALAND:
	case CountryID::Country_PERU:
	case CountryID::Country_FILIPINO:
	case CountryID::Country_URDU:
	case CountryID::Country_POLAND:
	case CountryID::Country_PORTUGAL:
	case CountryID::Country_ROMANIA:
	case CountryID::Country_SERBIAN_CYRILLIC:
	case CountryID::Country_RUSSIA:
	case CountryID::Country_SAUDI_ARABIA:
	case CountryID::Country_SWEDEN:
	case CountryID::Country_SLOVENIA:
	case CountryID::Country_SLOVAKIA:
	case CountryID::Country_THAILAND:
	case CountryID::Country_TURKEY:
	case CountryID::Country_TAIWAN:
	case CountryID::Country_UKRAINE:
	case CountryID::Country_UZBEKISTAN:
	case CountryID::Country_VIETNAMESE:
	case CountryID::Country_SOUTH_AFRICA:
	{
	//setlocale(LC_ALL, ".UTF8");
	I18N.EMPTY												= WCHARI(L"");
	I18N.WHICH												= WCHARI(L"???");
	I18N.NONE												= WCHARI(L"None");
	I18N.DS2VJOY											= WCHARI(IDS_DS2VJOY, L"DS2VJOY");
	I18N.APP_TITLE											= WCHARI(IDS_APP_TITLE, L"Ds2vJoy");
	I18N.Fatal_Error1										= WCHARI(L"!!!! ERROR !!!!");
	I18N.Fatal_Error2										= WCHARI(L"     vJoyInterface.dll\r\n\
         or   vJoyInstall.dll\r\n\
              cannot be uncompressed from memory,\r\n\
         and  not found in program directory");
	I18N.Status_Wait										= WCHARI(L"Waiting");
	I18N.Status_Active										= WCHARI(L"Active");
	I18N.Status_Charge										= WCHARI(L"Charge");
	I18N.Status_Empty										= WCHARI(L"Empty");
	I18N.Status_Low											= WCHARI(L"Low");
	I18N.Status_Medium										= WCHARI(L"Medium");
	I18N.Status_Full										= WCHARI(L"Full");
	I18N.MBOX_Delete										= WCHARI(L"Are you sure you want to delete the selected item?");
	I18N.MBOX_ErrorWhileSaving								= WCHARI(L"Errors were detected while saving.\nNo changes were made.");
	I18N.MBOX_ErrTitle										= WCHARI(L"Error");
	I18N.MBOX_NoButtonSelected								= WCHARI(L"No button selected");
	
	I18N.Magnifier_Magnification_Active						= WCHARI(L"  MAGNIFIER: Magnification activated");
	I18N.Settings_Registry_Added							= WCHARI(L"   SETTINGS: Startup value added in Registry");
	I18N.Settings_Registry_Removed							= WCHARI(L"   SETTINGS: Startup value removed from Registry");
	I18N.Settings_Change_Settings							= WCHARI(L"   SETTINGS: Reconnecting for change settings");
	I18N.TaskTray_AppNotFound								= WCHARI(L"   TASKTRAY: %s not found");
	I18N.TaskTray_ProfileChanged							= WCHARI(L"   TASKTRAY: Profile changed to: %d");

	I18N.ds_notforuse										= WCHARI(L"         DS: set to not intended for use");
	I18N.ds_wait											= WCHARI(L"         DS: waiting for a valid device");
	I18N.ds_skip_controller									= WCHARI(L"         DS: Skip %s Serial %s");
	I18N.ds_connect_controller								= WCHARI(L"         DS: connect %s serial %s");
	I18N.ds_connection_started								= WCHARI(L"         DS: connection started %s");
	I18N.ds_disconnect_controller							= WCHARI(L"         DS: disconnect %s");
	I18N.ds_failed_parse									= WCHARI(L"         DS: failed to parse %s");
	I18N.ds_failed_recv										= WCHARI(L"         DS: failed to recv data from %s : %d");
	I18N.ds_failed_send_cmd									= WCHARI(L"         DS: failed to send command to %s : %d");
	I18N.ds_failed_thread									= WCHARI(L"         DS: failed to create thread");
	I18N.ds_bt_crc											= WCHARI(L"         DS: BT received data with crc error: %d");
	I18N.ds_bt_size											= WCHARI(L"         DS: BT received data size was not enough");
	I18N.ds_version											= WCHARI(L"         DS: firmware version: %02X%02X");
	I18N.ds_firmware_fail									= WCHARI(L"         DS: cannot get firmware version");

	I18N.di_notforuse										= WCHARI(L"DirectInput: set to not intended for use");
	I18N.di_wait											= WCHARI(L"DirectInput: waiting for a valid device");
	I18N.di_failed_acquire									= WCHARI(L"DirectInput: failed to initialize");
	I18N.di_failed_thread									= WCHARI(L"DirectInput: failed to create thread");
	I18N.di_client_connected								= WCHARI(L"DirectInput: client connected");
	I18N.di_client_removed									= WCHARI(L"DirectInput: client removed");
	I18N.di_target_plugin_failed							= WCHARI(L"DirectInput: failed to acquire pad");
	I18N.di_pad_acquired									= WCHARI(L"DirectInput: %s acquired");
	I18N.di_pad_unacquired									= WCHARI(L"DirectInput: %s disconnected");
	I18N.di_busy											= WCHARI(L"DirectInput: pad signal is lost");

	I18N.xi_notforuse										= WCHARI(L"     XInput: set to not intended for use");
	I18N.xi_wait											= WCHARI(L"     XInput: waiting for a valid device");
	I18N.xi_failed_thread									= WCHARI(L"		XInput: failed to create thread");
	I18N.xi_pad_acquired									= WCHARI(L"     XInput: device %d acquired");
	I18N.xi_busy											= WCHARI(L"     XInput: pad signal is lost");

	I18N.vJoy_notforuse										= WCHARI(L"       vJoy: set to not intended for use");
	I18N.vJoy_wait											= WCHARI(L"       vJoy: waiting for a valid device");
	I18N.vJoy_initialization_failed							= WCHARI(L"       vJoy: can not use device ID: %d");
	I18N.vJoy_failed_acquire								= WCHARI(L"       vJoy: failed to acquire device ID: %d");
	I18N.vJoy_acquired										= WCHARI(L"       vJoy: acquired device ID:%d");
	I18N.vJoy_busy											= WCHARI(L"       vJoy: device ID:%d is busy");
	I18N.vJoy_failed_update									= WCHARI(L"       vJoy: failed to update device ID: %d");
	I18N.vJoy_version										= WCHARI(L"       vJoy: version: dll(%d.%d.%d) driver(%d.%d.%d)");

	I18N.XOutput_memory_allocating_error					= WCHARI(L"    XOutput: ERROR allocating memory to XOutput");
	I18N.XOutput_bus_connection_failed						= WCHARI(L"    XOutput: bus connection failed with error: %s");
	I18N.XOutput_target_plugin_failed						= WCHARI(L"    XOutput: plugin failed with error: %s");
	I18N.XOutput_client_connected							= WCHARI(L"    XOutput: client connected");
	I18N.XOutput_client_removed								= WCHARI(L"    XOutput: client removed");
	I18N.XOutput_pad_added									= WCHARI(L"    XOutput: pad added");
	I18N.XOutput_pad_removed								= WCHARI(L"    XOutput: pad removed");
	
	I18N.LogSatusString										= WCHARI(L"%a  %d /%m /%y     %T     UTC %z     %u …%W");
	I18N.SettingsSatusString								= WCHARI(L"Color: # %02X  %02X  %02X    R %03i  G %03i  B %03i");
	I18N.MappingButtonsString								= WCHARI(L"Dest:");
	I18N.RapidFireButtonsString								= WCHARI(L"RapidFire source:");
	I18N.XOutputButtonsString								= WCHARI(L"XOutput:");
	I18N.KeymapButtonsString								= L"Keymap source:";
	I18N.GuardianButtonsString								= L"PIDs: ";
	I18N.LinksSatusString									= L"Version: ";

	I18N.Profile_1											= WCHARI(L"Profile 1");
	I18N.Profile_2											= WCHARI(L"Profile 2");
	I18N.Profile_3											= WCHARI(L"Profile 3");
	I18N.MappingPaused_On									= WCHARI(L"Pause Mapping");
	I18N.MappingPaused_Off									= WCHARI(L"Start Mapping");
	I18N.RapidFirePaused_On									= WCHARI(L"Pause RapidFire");
	I18N.RapidFirePaused_Off								= WCHARI(L"Start RapidFire");
	I18N.vJoyPaused_On										= WCHARI(L"Pause vJoy");
	I18N.vJoyPaused_Off										= WCHARI(L"Start vJoy");
	I18N.XOutputPaused_On									= WCHARI(L"Pause XOutput");
	I18N.XOutputPaused_Off									= WCHARI(L"Start XOutput");
	I18N.KeymapPaused_On									= WCHARI(L"Pause Keymap");
	I18N.KeymapPaused_Off									= WCHARI(L"Start Keymap");
	I18N.GuardianPaused_On									= WCHARI(L"Pause Guardian");
	I18N.GuardianPaused_Off									= WCHARI(L"Start Guardian");

	I18N.XOutput_vJoy_Install_tittle						= WCHARI(L"vJoy Installation");
	I18N.XOutput_vJoy_Install_text							= WCHARI(L"I can't tell you what will happen\n\
  If you have vJoy device driver\n\
  Already installed by another software.\n\n\
	Continue anyway?");
	I18N.XOutput_vJoy_Uninstall_tittle = WCHARI(L"vJoy Uninstallation");
	I18N.XOutput_vJoy_Uninstall_text = WCHARI(L"It is recommended\n\
  To not uninstall vJoy device driver\n\
  If it has been installed by another software.\n\n\
	Are you sure to continue?");
	I18N.XOutput_driver_installed							= WCHARI(L"    XOutput: XOutput driver is installed");
	I18N.XOutput_driver_instalation_failed					= WCHARI(L"  ! XOutput: XOutput driver instalation failed");
	I18N.XOutput_driver_uninstalled							= WCHARI(L"    XOutput: XOutput driver is uninstalled");
	I18N.XOutput_driver_uninstalation_failed				= WCHARI(L"  ! XOutput: XOutput driver uninstalation failed");
	I18N.vJoy_driver_installed								= WCHARI(L"       vJoy: vJoy driver is installed");
	I18N.vJoy_driver_instalation_failed						= WCHARI(L"     ! vJoy: vJoy driver instalation failed");
	I18N.vJoy_driver_uninstalled							= WCHARI(L"       vJoy: vJoy driver is uninstalled");
	I18N.vJoy_driver_uninstalation_failed					= WCHARI(L"     ! vJoy: vJoy driver uninstalation failed");

	I18N.Guardian_driver_installed							= WCHARI(L"   Guardian: HidGuardian driver is installed");
	I18N.Guardian_driver_instalation_failed					= WCHARI(L" ! Guardian: HidGuardian driver instalation failed");
	I18N.Guardian_driver_uninstalled						= WCHARI(L"   Guardian: HidGuardian driver is uninstalled");
	I18N.Guardian_driver_uninstalation_failed				= WCHARI(L" ! Guardian: HidGuardian driver uninstalation failed");
	I18N.Cerberus_service_installed							= WCHARI(L"   Guardian: HidCerberus service installed");
	I18N.Cerberus_service_instalation_failed				= WCHARI(L" ! Guardian: HidCerberus service instalation failed");
	I18N.Cerberus_service_uninstalled						= WCHARI(L"   Guardian: HidCerberus service is uninstalled");
	I18N.Cerberus_service_uninstalation_failed				= WCHARI(L" ! Guardian: HidCerberus service uninstalation failed");
	I18N.Guardian_Added_to_Guardian							= WCHARI(L"   Guardian: Added %s (%u)");
	I18N.Guardian_Removed_from_Guardian						= WCHARI(L"   Guardian: Removed %s (%u)");

	I18N.WebView2_Not_Installed_tittle						= WCHARI(L"WebView2 Runtime is not installed");
	I18N.WebView2_Not_Installed_text						= WCHARI(L"Do you want to silently download and install it?\n\n\
	You can manually install it,\n\
	  by following 'WebView2' link below the 'Links' tab");
	I18N.WebView2_Installation_failed						= WCHARI(L"WebView2 installation failed");
	I18N.WebView2_downloading_failed						= WCHARI(L"WebView2 dowloading failed");
	I18N.WebView2_Permission								= L"Permission Request for:\n\n";
	I18N.WebView2_MICROPHONE								= L"Microphone";
	I18N.WebView2_CAMERA									= L"Camera";
	I18N.WebView2_GEOLOCATION								= L"Geolocation";
	I18N.WebView2_NOTIFICATIONS								= L"Notifications";
	I18N.WebView2_OTHER_SENSORS								= L"Generic Sensors";
	I18N.WebView2_CLIPBOARD_READ							= L"Clipboard Read";
	I18N.WebView2_UNKNOWN_PERMISSION						= L"Unknown resource";
	I18N.WebView2_Runtime_Failed_Found						= WCHARI(L"Couldn't find Edge WebView2 Runtime.\n\nDo you have a version installed?");
	I18N.WebView2_Data_Folder_Failed_Overwrite				= WCHARI(L"User data folder cannot be created\nbecause a file with the same name already exists.");
	I18N.WebView2_Data_Folder_Failed_Access					= WCHARI(L"Unable to create user data folder,\nAccess Denied.");
	I18N.WebView2_Runtime_Failed_Start						= WCHARI(L"Edge runtime unable to start");
	I18N.WebView2_Create_Environment_Failed					= WCHARI(L"Failed to create WebView2 environment");
	I18N.WebView2_Create_Webview_Failed						= WCHARI(L"Failed to create WebView2");
	I18N.WebView2_Cleanup_Data_Folder						= WCHARI(L"Cleanup User Data Folder");
	I18N.WebView2_New_version								= WCHARI(L"New available version");
	I18N.WebView2_PDF_Tittle								= WCHARI(L"Print to PDF");
	I18N.WebView2_PDF_Progress								= WCHARI(L"Print to PDF already in progress.");
	I18N.WebView2_PDF_Closing								= WCHARI(L"Print to PDF is in progress.\n\nContinue closing?");
	I18N.WebView2_PDF_Succeeded								= WCHARI(L"Print to PDF succeeded");
	I18N.WebView2_PDF_Failed								= WCHARI(L"Failed to create PDF");
	I18N.WebView2_Screenshot_Tittle							= WCHARI(L"Screenshot");
	I18N.WebView2_Preview_Captured							= WCHARI(L"Preview Captured");
	I18N.WebView2_Capture_Failed							= WCHARI(L"Failed to create capture");
	I18N.WebView2_Inject_Script_Tittle						= WCHARI(L"Inject Script Result");
	I18N.WebView2_Inject_Script_Failed						= WCHARI(L"Inject Script failed");
	I18N.WebView2_CDP_Event									= L"CDP Event Fired: ";
	I18N.WebView2_CDP_Result								= WCHARI(L"CDP Method Result");
	I18N.WebView2_AddHostObjectToScript_Failed				= WCHARI(L"AddHostObjectToScript failed");
	I18N.WebView2_IDispatch_Failed							= WCHARI(L"COM object doesn't support IDispatch");
	I18N.WebView2_CoCreateInstance_Failed					= WCHARI(L"CoCreateInstance failed");
	I18N.WebView2_Convert_Failed							= WCHARI(L"Failed to convert string to CLSID or ProgID");
	I18N.Suspend_Failed										= WCHARI(L"Failed to suspend WebView2");

	I18N.Clone_of_Tab										= WCHARI(L" Clone of Tab ");
	I18N.TabLog												= WCHARI(L"Log");
	I18N.TabSettings										= WCHARI(L"Settings");
	I18N.TabMapping											= WCHARI(L"Mapping");
	I18N.TabRapidFire										= WCHARI(L"RapidFire");
	I18N.TabXOutput											= WCHARI(L"XOutput");
	I18N.TabKeymap											= WCHARI(L"Keymap");
	I18N.TabGuardian										= WCHARI(L"Guardian");
	I18N.TabExplorer										= WCHARI(L"Web");
	I18N.TabLinks											= WCHARI(L"Links");

	I18N.srceButton											= WCHARI(L"Source Button");
	I18N.destButton											= WCHARI(L"Destination Button");
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
	I18N.Button_L2_TRIGGER									= WCHARI(L"L2 TRIGGER");
	I18N.Button_R2_TRIGGER									= WCHARI(L"R2 TRIGGER");
	I18N.Button_LX_INV										= WCHARI(L"AXISL XINV");
	I18N.Button_LY_INV										= WCHARI(L"AXISL YINV");
	I18N.Button_RX_INV										= WCHARI(L"AXISR XINV");
	I18N.Button_RY_INV										= WCHARI(L"AXISR YINV");
	I18N.Button_LX_SNIPER									= WCHARI(L"SNIPERL X");
	I18N.Button_LY_SNIPER									= WCHARI(L"SNIPERL Y");
	I18N.Button_RX_SNIPER									= WCHARI(L"SNIPERR X");
	I18N.Button_RY_SNIPER									= WCHARI(L"SNIPERR Y");
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
	I18N.Button_TOUCH_1										= WCHARI(L"TOUCH 1");
	I18N.Button_TOUCH_2										= WCHARI(L"TOUCH 2");
	I18N.Button_TOUCH_3										= WCHARI(L"TOUCH 3");
	I18N.Button_TOUCH_4										= WCHARI(L"TOUCH 4");
	I18N.Button_TOUCH_L										= WCHARI(L"TOUCH L");
	I18N.Button_TOUCH_R										= WCHARI(L"TOUCH R");
	I18N.Button_L2_TRIGGER_33								= WCHARI(L"L2 LOW");
	I18N.Button_R2_TRIGGER_33								= WCHARI(L"R2 LOW");
	I18N.Button_L2_TRIGGER_66								= WCHARI(L"L2 HIGH");
	I18N.Button_R2_TRIGGER_66								= WCHARI(L"R2 HIGH");
	I18N.Button_L2_TRIGGER_100								= WCHARI(L"L2 FULL");
	I18N.Button_R2_TRIGGER_100								= WCHARI(L"R2 FULL");
	I18N.Button_L1R1										= WCHARI(L"L1R1");
	I18N.Button_L2R2										= WCHARI(L"L2R2");
	I18N.Button_EMPTY										= WCHARI(L"NULL");
	I18N.Button_MIDDLE										= WCHARI(L"HALF");
	I18N.Button_FULL										= WCHARI(L"FULL");
	I18N.Button_QUARTER1									= WCHARI(L"QUARTER 1");
	I18N.Button_QUARTER2									= WCHARI(L"QUARTER 2");
	I18N.Button_THIRD1										= WCHARI(L"THIRD 1");
	I18N.Button_THIRD2										= WCHARI(L"THIRD 2");
	I18N.Button_TEN											= WCHARI(L"TEN");
	I18N.Button_TWENTY										= WCHARI(L"TWENTY");
	I18N.Button_THIRTY										= WCHARI(L"THIRTY");
	I18N.Button_FORTY										= WCHARI(L"FORTY");
	I18N.Button_SIXTY										= WCHARI(L"SIXTY");
	I18N.Button_SEVENTY										= WCHARI(L"SEVENTY");
	I18N.Button_EIGHTY										= WCHARI(L"EIGHTY");
	I18N.Button_NINETY										= WCHARI(L"NINETY");
	I18N.Button_BATTERY										= WCHARI(L"BATTERY");
	I18N.Button_BATTERY0									= WCHARI(L"BATTERY 0");
	I18N.Button_BATTERY1									= WCHARI(L"BATTERY 1");
	I18N.Button_BATTERY2									= WCHARI(L"BATTERY 2");
	I18N.Button_BATTERY3									= WCHARI(L"BATTERY 3");
	I18N.Button_BATTERY4									= WCHARI(L"BATTERY 4");
	I18N.Button_BATTERY5									= WCHARI(L"BATTERY 5");
	I18N.Button_BATTERY6									= WCHARI(L"BATTERY 6");
	I18N.Button_BATTERY7									= WCHARI(L"BATTERY 7");
	I18N.Button_BATTERY8									= WCHARI(L"BATTERY 8");
	I18N.Button_BATTERY9									= WCHARI(L"BATTERY 9");
	I18N.Button_USB											= WCHARI(L"USB");
	I18N.Button_EARS										= WCHARI(L"EARS");
	I18N.Button_MIC											= WCHARI(L"MIC");
	I18N.Button_BT											= WCHARI(L"BT");
	I18N.Button_FINGER										= WCHARI(L"FINGER");
	I18N.Button_FINGERS										= WCHARI(L"FINGERS");
	I18N.Button_DS_SELECTED									= WCHARI(L"DS SELECTED");
	I18N.Button_DS4_SELECTED								= WCHARI(L"DS4 SELECTED");
	I18N.Button_DS5_SELECTED								= WCHARI(L"DS5 SELECTED");
	I18N.Button_DI_SELECTED									= WCHARI(L"DI SELECTED");
	I18N.Button_XI_SELECTED									= WCHARI(L"XI SELECTED");
	I18N.Button_DS_ACTIVE									= WCHARI(L"DS ACTIVE");
	I18N.Button_DS4_ACTIVE									= WCHARI(L"DS4 ACTIVE");
	I18N.Button_DS5_ACTIVE									= WCHARI(L"DS5 ACTIVE");
	I18N.Button_DI_ACTIVE									= WCHARI(L"DI ACTIVE");
	I18N.Button_KBD_ACTIVE									= WCHARI(L"KBD ACTIVE");
	I18N.Button_MSE_ACTIVE									= WCHARI(L"MSE ACTIVE");
	I18N.Button_MSE_DI_ACTIVE								= WCHARI(L"MSE DI ACTIVE");
	I18N.Button_INACTIVITY_5MN								= WCHARI(L"INACTY 5MN");
	I18N.Button_INACTIVITY_10MN								= WCHARI(L"INACTY 10MN");
	I18N.Button_INACTIVITY_15MN								= WCHARI(L"INACTY 15MN");
	I18N.Button_INACTIVITY_30MN								= WCHARI(L"INACTY 30MN");
	I18N.Button_NO_MOVEMENT_5MN								= WCHARI(L"NO MVT 5MN");
	I18N.Button_NO_MOVEMENT_10MN							= WCHARI(L"NO MVT 10MN");
	I18N.Button_NO_MOVEMENT_15MN							= WCHARI(L"NO MVT 15MN");
	I18N.Button_NO_MOVEMENT_30MN							= WCHARI(L"NO MVT 30MN");
	I18N.Button_SLO											= WCHARI(L"SLO");
	I18N.Button_SLO_INV										= WCHARI(L"SLO INV");
	I18N.Button_SLO_SNIPER									= WCHARI(L"SNIPER SLO");
	I18N.Button_SL1											= WCHARI(L"SL1");
	I18N.Button_SL1_INV										= WCHARI(L"SL1INV");
	I18N.Button_SL1_SNIPER									= WCHARI(L"SNIPER SL1");
	I18N.Button_DI_X										= WCHARI(L"DI X");
	I18N.Button_DI_X_INV									= WCHARI(L"DI X INV");
	I18N.Button_DI_X_TRIGGER								= WCHARI(L"DI X TR");
	I18N.Button_DI_Y										= WCHARI(L"DI Y");
	I18N.Button_DI_Y_INV									= WCHARI(L"DI Y INV");
	I18N.Button_DI_Y_TRIGGER								= WCHARI(L"DI Y TR");
	I18N.Button_DI_Z										= WCHARI(L"DI Z");
	I18N.Button_DI_Z_INV									= WCHARI(L"DI Z INV");
	I18N.Button_DI_Z_TRIGGER								= WCHARI(L"DI Z TR");
	I18N.Button_DI_RX										= WCHARI(L"DI RX");
	I18N.Button_DI_RX_INV									= WCHARI(L"DI RX INV");
	I18N.Button_DI_RX_TRIGGER								= WCHARI(L"DI RX TR");
	I18N.Button_DI_RY										= WCHARI(L"DI RY");
	I18N.Button_DI_RY_INV									= WCHARI(L"DI RY INV");
	I18N.Button_DI_RY_TRIGGER								= WCHARI(L"DI RY TR");
	I18N.Button_DI_RZ										= WCHARI(L"DI RZ");
	I18N.Button_DI_RZ_INV									= WCHARI(L"DI RZ INV");
	I18N.Button_DI_RZ_TRIGGER								= WCHARI(L"DI RZ TR");
	I18N.Button_DI_SL0										= WCHARI(L"DI SL0");
	I18N.Button_DI_SL0_INV									= WCHARI(L"DI SL0 INV");
	I18N.Button_DI_SL0_TRIGGER								= WCHARI(L"DI SL0 TR");
	I18N.Button_DI_SL1										= WCHARI(L"DI SL1");
	I18N.Button_DI_SL1_INV									= WCHARI(L"DI SL1 INV");
	I18N.Button_DI_SL1_TRIGGER								= WCHARI(L"DI SL1 TR");
	I18N.Button_DPAD2_LEFT									= WCHARI(L"DPAD2 ←");
	I18N.Button_DPAD2_UP									= WCHARI(L"DPAD2 ↑");
	I18N.Button_DPAD2_RIGHT									= WCHARI(L"DPAD2 →");
	I18N.Button_DPAD2_DOWN									= WCHARI(L"DPAD2 ↓");
	I18N.Button_DPAD3_LEFT									= WCHARI(L"DPAD3 ←");
	I18N.Button_DPAD3_UP									= WCHARI(L"DPAD3 ↑");
	I18N.Button_DPAD3_RIGHT									= WCHARI(L"DPAD3 →");
	I18N.Button_DPAD3_DOWN									= WCHARI(L"DPAD3 ↓");
	I18N.Button_DPAD4_LEFT									= WCHARI(L"DPAD4 ←");
	I18N.Button_DPAD4_UP									= WCHARI(L"DPAD4 ↑");
	I18N.Button_DPAD4_RIGHT									= WCHARI(L"DPAD4 →");
	I18N.Button_DPAD4_DOWN									= WCHARI(L"DPAD4 ↓");
	
	I18N.Button_STANCE										= WCHARI(L"STANCE");
	I18N.Button_ZONE										= WCHARI(L"ZONE");
	I18N.Button_STANCE1										= WCHARI(L"STANCE 1");
	I18N.Button_STANCE2										= WCHARI(L"STANCE 2");
	I18N.Button_STANCE3										= WCHARI(L"STANCE 3");
	I18N.Button_STANCE4										= WCHARI(L"STANCE 4");
	I18N.Button_STANCE5										= WCHARI(L"STANCE 5");
	I18N.Button_ZONE1										= WCHARI(L"ZONE 1");
	I18N.Button_ZONE2										= WCHARI(L"ZONE 2");
	I18N.Button_ZONE3										= WCHARI(L"ZONE 3");
	I18N.Button_ZONE4										= WCHARI(L"ZONE 4");
	I18N.Button_ZONE5										= WCHARI(L"ZONE 5");
	I18N.Button_ROLL										= WCHARI(L"ROLL");
	I18N.Button_ROLL_INV									= WCHARI(L"ROLL INV");
	I18N.Button_ROLL_TRIGGER								= WCHARI(L"ROLL TR");
	I18N.Button_ROLL_CENTER									= WCHARI(L"RLL CENTER");
	I18N.Button_LEFT1										= WCHARI(L"LEFT 1");
	I18N.Button_LEFT2										= WCHARI(L"LEFT 2");
	I18N.Button_LEFT3										= WCHARI(L"LEFT 3");
	I18N.Button_LEFT4										= WCHARI(L"LEFT 4");
	I18N.Button_LEFT5										= WCHARI(L"LEFT 5");
	I18N.Button_LEFT6										= WCHARI(L"LEFT 6");
	I18N.Button_LEFT7										= WCHARI(L"LEFT TILT");
	I18N.Button_RIGHT										= WCHARI(L"RIGHT");
	I18N.Button_RIGHT1										= WCHARI(L"RIGHT 1");
	I18N.Button_RIGHT2										= WCHARI(L"RIGHT 2");
	I18N.Button_RIGHT3										= WCHARI(L"RIGHT 3");
	I18N.Button_RIGHT4										= WCHARI(L"RIGHT 4");
	I18N.Button_RIGHT5										= WCHARI(L"RIGHT 5");
	I18N.Button_RIGHT6										= WCHARI(L"RIGHT 6");
	I18N.Button_RIGHT7										= WCHARI(L"RIGHT TILT");
	I18N.Button_YAW											= WCHARI(L"YAW");
	I18N.Button_YAW_INV										= WCHARI(L"YAW INV");
	I18N.Button_YAW_TRIGGER									= WCHARI(L"YAW TR");
	I18N.Button_YAW_CENTER									= WCHARI(L"YAW CENTER");
	I18N.Button_ANTI1										= WCHARI(L"ANTI 1");
	I18N.Button_ANTI2										= WCHARI(L"ANTI 2");
	I18N.Button_ANTI3										= WCHARI(L"ANTI 3");
	I18N.Button_ANTI4										= WCHARI(L"ANTI 4");
	I18N.Button_ANTI5										= WCHARI(L"ANTI 5");
	I18N.Button_ANTI6										= WCHARI(L"ANTI 6");
	I18N.Button_ANTI7										= WCHARI(L"ANTI TILT");
	I18N.Button_CLOCK										= WCHARI(L"CLOCK");
	I18N.Button_CLOCK1										= WCHARI(L"CLOCK 1");
	I18N.Button_CLOCK2										= WCHARI(L"CLOCK 2");
	I18N.Button_CLOCK3										= WCHARI(L"CLOCK 3");
	I18N.Button_CLOCK4										= WCHARI(L"CLOCK 4");
	I18N.Button_CLOCK5										= WCHARI(L"CLOCK 5");
	I18N.Button_CLOCK6										= WCHARI(L"CLOCK 6");
	I18N.Button_CLOCK7										= WCHARI(L"CLOCK TILT");
	I18N.Button_PITCH										= WCHARI(L"PITCH");
	I18N.Button_PITCH_INV									= WCHARI(L"PITCH INV");
	I18N.Button_PITCH_TRIGGER								= WCHARI(L"PITCH TR");
	I18N.Button_PITCH_CENTER								= WCHARI(L"PTC CENTER");
	I18N.Button_REAR1										= WCHARI(L"REAR 1");
	I18N.Button_REAR2										= WCHARI(L"REAR 2");
	I18N.Button_REAR3										= WCHARI(L"REAR 3");
	I18N.Button_REAR4										= WCHARI(L"REAR 4");
	I18N.Button_REAR5										= WCHARI(L"REAR 5");
	I18N.Button_REAR6										= WCHARI(L"REAR 6");
	I18N.Button_REAR7										= WCHARI(L"REAR TILT");
	I18N.Button_FORE										= WCHARI(L"FORE");
	I18N.Button_FORE1										= WCHARI(L"FORE 1");
	I18N.Button_FORE2										= WCHARI(L"FORE 2");
	I18N.Button_FORE3										= WCHARI(L"FORE 3");
	I18N.Button_FORE4										= WCHARI(L"FORE 4");
	I18N.Button_FORE5										= WCHARI(L"FORE 5");
	I18N.Button_FORE6										= WCHARI(L"FORE 6");
	I18N.Button_FORE7										= WCHARI(L"FORE TILT");
	I18N.Button_SIDEWARD									= WCHARI(L"SIDEWARD");
	I18N.Button_SIDEWARD_INV								= WCHARI(L"SIDEWARD INV");
	I18N.Button_SIDEWARD_TRIGGER							= WCHARI(L"SIDEWARD TR");
	I18N.Button_SIDEWARD_CENTER								= WCHARI(L"SWD CENTER");
	I18N.Button_WEST1										= WCHARI(L"WEST 1");
	I18N.Button_WEST2										= WCHARI(L"WEST 2");
	I18N.Button_WEST3										= WCHARI(L"WEST 3");
	I18N.Button_WEST4										= WCHARI(L"WEST 4");
	I18N.Button_WEST5										= WCHARI(L"WEST 5");
	I18N.Button_WEST6										= WCHARI(L"WEST 6");
	I18N.Button_EAST										= WCHARI(L"EAST");
	I18N.Button_EAST1										= WCHARI(L"EAST 1");
	I18N.Button_EAST2										= WCHARI(L"EAST 2");
	I18N.Button_EAST3										= WCHARI(L"EAST 3");
	I18N.Button_EAST4										= WCHARI(L"EAST 4");
	I18N.Button_EAST5										= WCHARI(L"EAST 5");
	I18N.Button_EAST6										= WCHARI(L"EAST 6");
	I18N.Button_TOWARD										= WCHARI(L"TOWARD");
	I18N.Button_TOWARD_INV									= WCHARI(L"TOWARD INV");
	I18N.Button_TOWARD_TRIGGER								= WCHARI(L"TOWARD TR");
	I18N.Button_TOWARD_CENTER								= WCHARI(L"TWD CENTER");
	I18N.Button_BACKWARD1									= WCHARI(L"BACKWARD 1");
	I18N.Button_BACKWARD2									= WCHARI(L"BACKWARD 2");
	I18N.Button_BACKWARD3									= WCHARI(L"BACKWARD 3");
	I18N.Button_BACKWARD4									= WCHARI(L"BACKWARD 4");
	I18N.Button_BACKWARD5									= WCHARI(L"BACKWARD 5");
	I18N.Button_BACKWARD6									= WCHARI(L"BACKWARD 6");
	I18N.Button_FORWARD										= WCHARI(L"FORWARD");
	I18N.Button_FORWARD1									= WCHARI(L"FORWARD 1");
	I18N.Button_FORWARD2									= WCHARI(L"FORWARD 2");
	I18N.Button_FORWARD3									= WCHARI(L"FORWARD 3");
	I18N.Button_FORWARD4									= WCHARI(L"FORWARD 4");
	I18N.Button_FORWARD5									= WCHARI(L"FORWARD 5");
	I18N.Button_FORWARD6									= WCHARI(L"FORWARD 6");
	I18N.Button_LEVEL										= WCHARI(L"LEVEL");
	I18N.Button_LEVEL_INV									= WCHARI(L"LEVEL INV");
	I18N.Button_LEVEL_TRIGGER								= WCHARI(L"LEVEL TR");
	I18N.Button_LEVEL_CENTER								= WCHARI(L"LVL CENTER");
	I18N.Button_SOUTH1										= WCHARI(L"SOUTH 1");
	I18N.Button_SOUTH2										= WCHARI(L"SOUTH 2");
	I18N.Button_SOUTH3										= WCHARI(L"SOUTH 3");
	I18N.Button_SOUTH4										= WCHARI(L"SOUTH 4");
	I18N.Button_SOUTH5										= WCHARI(L"SOUTH 5");
	I18N.Button_SOUTH6										= WCHARI(L"SOUTH 6");
	I18N.Button_NORTH										= WCHARI(L"NORTH");
	I18N.Button_NORTH1										= WCHARI(L"NORTH 1");
	I18N.Button_NORTH2										= WCHARI(L"NORTH 2");
	I18N.Button_NORTH3										= WCHARI(L"NORTH 3");
	I18N.Button_NORTH4										= WCHARI(L"NORTH 4");
	I18N.Button_NORTH5										= WCHARI(L"NORTH 5");
	I18N.Button_NORTH6										= WCHARI(L"NORTH 6");
	I18N.Button_WHEEL										= WCHARI(L"WHEEL");
	I18N.Button_QUARTER										= WCHARI(L"QUARTER");
	I18N.Button_REAR										= WCHARI(L"REAR	");
	I18N.Button_GEAR_1										= WCHARI(L"GEAR 1");
	I18N.Button_GEAR_2										= WCHARI(L"GEAR 2");
	I18N.Button_GEAR_3										= WCHARI(L"GEAR 3");
	I18N.Button_GEAR_4										= WCHARI(L"GEAR 4");
	I18N.Button_GEAR_5										= WCHARI(L"GEAR 5");

	I18N.Button_MOUSE_AXEX									= WCHARI(L"MOUSE AXE X");
	I18N.Button_MOUSE_AXEY									= WCHARI(L"MOUSE AXE Y");
	I18N.Button_MOUSE_SCROLL_UP								= WCHARI(L"SCROLL ↑");
	I18N.Button_MOUSE_SCROLL_DOWN							= WCHARI(L"SCROLL ↓");
	I18N.Button_MOUSE_SCROLL_UP_HIGH						= WCHARI(L"SCROLL ↑ HIGH");
	I18N.Button_MOUSE_SCROLL_DOWN_HIGH						= WCHARI(L"SCROLL ↓ HIGH");
	I18N.Button_MOUSE_LEFT									= WCHARI(L"MOUSE LEFT");
	I18N.Button_MOUSE_RIGHT									= WCHARI(L"MOUSE RIGHT");
	I18N.Button_MOUSE_UP									= WCHARI(L"MOUSE UP");
	I18N.Button_MOUSE_DOWN									= WCHARI(L"MOUSE DOWN");
	I18N.Button_MOUSE_LBUTTON								= WCHARI(L"LBUTTON");
	I18N.Button_MOUSE_MBUTTON								= WCHARI(L"MBUTTON");
	I18N.Button_MOUSE_RBUTTON								= WCHARI(L"RBUTTON");
	I18N.Button_MOUSE_XBUTTON1								= WCHARI(L"XBUTTON1");
	I18N.Button_MOUSE_XBUTTON2								= WCHARI(L"XBUTTON2");
	I18N.Button_MOUSE_BUTTON6								= WCHARI(L"MOUSE B6");
	I18N.Button_MOUSE_BUTTON7								= WCHARI(L"MOUSE B7");
	I18N.Button_MOUSE_BUTTON8								= WCHARI(L"MOUSE B8");
	I18N.Button_KID_F1										= WCHARI(L"F1");
	I18N.Button_KID_F2										= WCHARI(L"F2");
	I18N.Button_KID_F3										= WCHARI(L"F3");
	I18N.Button_KID_F4										= WCHARI(L"F4");
	I18N.Button_KID_F5										= WCHARI(L"F5");
	I18N.Button_KID_F6										= WCHARI(L"F6");
	I18N.Button_KID_F7										= WCHARI(L"F7");
	I18N.Button_KID_F8										= WCHARI(L"F8");
	I18N.Button_KID_F9										= WCHARI(L"F9");
	I18N.Button_KID_F10										= WCHARI(L"F10");
	I18N.Button_KID_F11										= WCHARI(L"F11");
	I18N.Button_KID_F12										= WCHARI(L"F12");
	I18N.Button_KID_0										= WCHARI(L"0");
	I18N.Button_KID_1										= WCHARI(L"1");
	I18N.Button_KID_2										= WCHARI(L"2");
	I18N.Button_KID_3										= WCHARI(L"3");
	I18N.Button_KID_4										= WCHARI(L"4");
	I18N.Button_KID_5										= WCHARI(L"5");
	I18N.Button_KID_6										= WCHARI(L"6");
	I18N.Button_KID_7										= WCHARI(L"7");
	I18N.Button_KID_8										= WCHARI(L"8");
	I18N.Button_KID_9										= WCHARI(L"9");
	I18N.Button_KID_OEM_MINUS								= WCHARI(L"OEM_MINUS");
	I18N.Button_KID_OEM_PLUS								= WCHARI(L"OEM_PLUS");
	I18N.Button_KID_OEM_1									= WCHARI(L"OEM_1");
	I18N.Button_KID_OEM_2									= WCHARI(L"OEM_2");
	I18N.Button_KID_OEM_3									= WCHARI(L"OEM_3");
	I18N.Button_KID_OEM_4									= WCHARI(L"OEM_4");
	I18N.Button_KID_OEM_5									= WCHARI(L"OEM_5");
	I18N.Button_KID_OEM_6									= WCHARI(L"OEM_6");
	I18N.Button_KID_OEM_7									= WCHARI(L"OEM_7");
	I18N.Button_KID_OEM_8									= WCHARI(L"OEM_8");
	I18N.Button_KID_OEM_102									= WCHARI(L"OEM_102");
	I18N.Button_KID_OEM_COMMA								= WCHARI(L"OEM_COMMA");
	I18N.Button_KID_OEM_PERIOD								= WCHARI(L"OEM_PERIOD");
	I18N.Button_KID_A										= WCHARI(L"A");
	I18N.Button_KID_B										= WCHARI(L"B");
	I18N.Button_KID_C										= WCHARI(L"C");
	I18N.Button_KID_D										= WCHARI(L"D");
	I18N.Button_KID_E										= WCHARI(L"E");
	I18N.Button_KID_F										= WCHARI(L"F");
	I18N.Button_KID_G										= WCHARI(L"G");
	I18N.Button_KID_H										= WCHARI(L"H");
	I18N.Button_KID_I										= WCHARI(L"I");
	I18N.Button_KID_J										= WCHARI(L"J");
	I18N.Button_KID_K										= WCHARI(L"K");
	I18N.Button_KID_L										= WCHARI(L"L");
	I18N.Button_KID_M										= WCHARI(L"M");
	I18N.Button_KID_N										= WCHARI(L"N");
	I18N.Button_KID_O										= WCHARI(L"O");
	I18N.Button_KID_P										= WCHARI(L"P");
	I18N.Button_KID_Q										= WCHARI(L"Q");
	I18N.Button_KID_R										= WCHARI(L"R");
	I18N.Button_KID_S										= WCHARI(L"S");
	I18N.Button_KID_T										= WCHARI(L"T");
	I18N.Button_KID_U										= WCHARI(L"U");
	I18N.Button_KID_V										= WCHARI(L"V");
	I18N.Button_KID_W										= WCHARI(L"W");
	I18N.Button_KID_X										= WCHARI(L"X");
	I18N.Button_KID_Y										= WCHARI(L"Y");
	I18N.Button_KID_Z										= WCHARI(L"Z");
	I18N.Button_KID_ESCAPE									= WCHARI(L"ESCAPE");
	I18N.Button_KID_TAB										= WCHARI(L"TAB");
	I18N.Button_KID_RETURN									= WCHARI(L"RETURN");
	I18N.Button_KID_SPACE									= WCHARI(L"SPACE");
	I18N.Button_KID_BACK									= WCHARI(L"BACK");
	I18N.Button_KID_DELETE									= WCHARI(L"DELETE");
	I18N.Button_KID_INSERT									= WCHARI(L"INSERT");
	I18N.Button_KID_NUMLOCK									= WCHARI(L"NUMLOCK");
	I18N.Button_KID_LSHIFT									= WCHARI(L"LSHIFT");
	I18N.Button_KID_RSHIFT									= WCHARI(L"RSHIFT");
	I18N.Button_KID_LCONTROL								= WCHARI(L"LCONTROL");
	I18N.Button_KID_RCONTROL								= WCHARI(L"RCONTROL");
	I18N.Button_KID_LWIN									= WCHARI(L"LWIN");
	I18N.Button_KID_RWIN									= WCHARI(L"RWIN");
	I18N.Button_KID_LMENU									= WCHARI(L"LMENU");
	I18N.Button_KID_RMENU									= WCHARI(L"RMENU");
	I18N.Button_KID_LEFT									= WCHARI(L"LEFT");
	I18N.Button_KID_UP										= WCHARI(L"UP");
	I18N.Button_KID_RIGHT									= WCHARI(L"RIGHT");
	I18N.Button_KID_DOWN									= WCHARI(L"DOWN");
	I18N.Button_KID_PRIOR									= WCHARI(L"PRIOR");
	I18N.Button_KID_NEXT									= WCHARI(L"NEXT");
	I18N.Button_KID_END										= WCHARI(L"END");
	I18N.Button_KID_HOME									= WCHARI(L"HOME");
	I18N.Button_KID_NUMPAD0									= WCHARI(L"NUMPAD0");
	I18N.Button_KID_NUMPAD1									= WCHARI(L"NUMPAD1");
	I18N.Button_KID_NUMPAD2									= WCHARI(L"NUMPAD2");
	I18N.Button_KID_NUMPAD3									= WCHARI(L"NUMPAD3");
	I18N.Button_KID_NUMPAD4									= WCHARI(L"NUMPAD4");
	I18N.Button_KID_NUMPAD5									= WCHARI(L"NUMPAD5");
	I18N.Button_KID_NUMPAD6									= WCHARI(L"NUMPAD6");
	I18N.Button_KID_NUMPAD7									= WCHARI(L"NUMPAD7");
	I18N.Button_KID_NUMPAD8									= WCHARI(L"NUMPAD8");
	I18N.Button_KID_NUMPAD9									= WCHARI(L"NUMPAD9");
	I18N.Button_KID_DIVIDE									= WCHARI(L"DIVIDE");
	I18N.Button_KID_MULTIPLY								= WCHARI(L"MULTIPLY");
	I18N.Button_KID_SUBTRACT								= WCHARI(L"SUBTRACT");
	I18N.Button_KID_ADD										= WCHARI(L"ADD");
	I18N.Button_KID_SEPARATOR								= WCHARI(L"SEPARATOR");
	I18N.Button_KID_DECIMAL									= WCHARI(L"DECIMAL");

	I18N.Dest_X												= WCHARI(L"X");
	I18N.Dest_Y												= WCHARI(L"Y");
	I18N.Dest_Z												= WCHARI(L"Z");
	I18N.Dest_RX											= WCHARI(L"RX");
	I18N.Dest_RY											= WCHARI(L"RY");
	I18N.Dest_RZ											= WCHARI(L"RZ");
	I18N.Dest_SL0											= WCHARI(L"SL0");
	I18N.Dest_SL1											= WCHARI(L"SL1");
	I18N.Dest_XTR											= WCHARI(L"XTR");
	I18N.Dest_YTR											= WCHARI(L"YTR");
	I18N.Dest_ZTR											= WCHARI(L"ZTR");
	I18N.Dest_RXTR											= WCHARI(L"RXTR");
	I18N.Dest_RYTR											= WCHARI(L"RYTR");
	I18N.Dest_RZTR											= WCHARI(L"RZTR");
	I18N.Dest_SL0TR											= WCHARI(L"SL0TR");
	I18N.Dest_SL1TR											= WCHARI(L"SL1TR");
	I18N.Dest_XAXTOTR										= WCHARI(L"XA2T");
	I18N.Dest_YAXTOTR										= WCHARI(L"YA2T");
	I18N.Dest_ZAXTOTR										= WCHARI(L"ZA2T");
	I18N.Dest_RXAXTOTR										= WCHARI(L"RXA2T");
	I18N.Dest_RYAXTOTR										= WCHARI(L"RYA2T");
	I18N.Dest_RZAXTOTR										= WCHARI(L"RZA2T");
	I18N.Dest_SL0AXTOTR										= WCHARI(L"SL0A2T");
	I18N.Dest_SL1AXTOTR										= WCHARI(L"SL1A2T");
	I18N.Dest_XINV											= WCHARI(L"XINV");
	I18N.Dest_YINV											= WCHARI(L"YINV");
	I18N.Dest_ZINV											= WCHARI(L"ZINV");
	I18N.Dest_RXINV											= WCHARI(L"RXINV");
	I18N.Dest_RYINV											= WCHARI(L"RYINV");
	I18N.Dest_RZINV											= WCHARI(L"RZINV");
	I18N.Dest_SL0INV										= WCHARI(L"SL0INV");
	I18N.Dest_SL1INV										= WCHARI(L"SL1INV");
	I18N.Dest_XTRINV										= WCHARI(L"XTRINV");
	I18N.Dest_YTRINV										= WCHARI(L"YTRINV");
	I18N.Dest_ZTRINV										= WCHARI(L"ZTRINV");
	I18N.Dest_RXTRINV										= WCHARI(L"RXTRINV");
	I18N.Dest_RYTRINV										= WCHARI(L"RYTRINV");
	I18N.Dest_RZTRINV										= WCHARI(L"RZTRINV");
	I18N.Dest_SL0TRINV										= WCHARI(L"SL0TRINV");
	I18N.Dest_SL1TRINV										= WCHARI(L"SL1TRINV");
	I18N.Dest_XAXTOTRINV									= WCHARI(L"XA2TINV");
	I18N.Dest_YAXTOTRINV									= WCHARI(L"YA2TINV");
	I18N.Dest_ZAXTOTRINV									= WCHARI(L"ZA2TINV");
	I18N.Dest_RXAXTOTRINV									= WCHARI(L"RXA2TINV");
	I18N.Dest_RYAXTOTRINV									= WCHARI(L"RYA2TINV");
	I18N.Dest_RZAXTOTRINV									= WCHARI(L"RZA2TINV");
	I18N.Dest_SL0AXTOTRINV									= WCHARI(L"S0A2TINV");
	I18N.Dest_SL1AXTOTRINV									= WCHARI(L"S1A2TINV");
	I18N.Dest_DPAD1_LEFT									= WCHARI(L"POV1 ←");
	I18N.Dest_DPAD1_UP_LEFT									= WCHARI(L"POV1 ←↑");
	I18N.Dest_DPAD1_UP										= WCHARI(L"POV1 ↑");
	I18N.Dest_DPAD1_UP_RIGHT								= WCHARI(L"POV1 ↑→");
	I18N.Dest_DPAD1_RIGHT									= WCHARI(L"POV1 →");
	I18N.Dest_DPAD1_DOWN_RIGHT								= WCHARI(L"POV1 ↓→");
	I18N.Dest_DPAD1_DOWN									= WCHARI(L"POV1 ↓");
	I18N.Dest_DPAD1_DOWN_LEFT								= WCHARI(L"POV1 ←↓");
	I18N.Dest_DPAD2_LEFT									= WCHARI(L"POV2 ←");
	I18N.Dest_DPAD2_UP_LEFT									= WCHARI(L"POV2 ←↑");
	I18N.Dest_DPAD2_UP										= WCHARI(L"POV2 ↑");
	I18N.Dest_DPAD2_UP_RIGHT								= WCHARI(L"POV2 ↑→");
	I18N.Dest_DPAD2_RIGHT									= WCHARI(L"POV2 →");
	I18N.Dest_DPAD2_DOWN_RIGHT								= WCHARI(L"POV2 ↓→");
	I18N.Dest_DPAD2_DOWN									= WCHARI(L"POV2 ↓");
	I18N.Dest_DPAD2_DOWN_LEFT								= WCHARI(L"POV2 ←↓");
	I18N.Dest_DPAD3_LEFT									= WCHARI(L"POV3 ←");
	I18N.Dest_DPAD3_UP_LEFT									= WCHARI(L"POV2 ←↑");
	I18N.Dest_DPAD3_UP										= WCHARI(L"POV3 ↑");
	I18N.Dest_DPAD3_UP_RIGHT								= WCHARI(L"POV3 ↑→");
	I18N.Dest_DPAD3_RIGHT									= WCHARI(L"POV3 →");
	I18N.Dest_DPAD3_DOWN_RIGHT								= WCHARI(L"POV3 ↓→");
	I18N.Dest_DPAD3_DOWN									= WCHARI(L"POV3 ↓");
	I18N.Dest_DPAD3_DOWN_LEFT								= WCHARI(L"POV3 ←↓");
	I18N.Dest_DPAD4_LEFT									= WCHARI(L"POV4 ←");
	I18N.Dest_DPAD4_UP_LEFT									= WCHARI(L"POV4 ←↑");
	I18N.Dest_DPAD4_UP										= WCHARI(L"POV4 ↑");
	I18N.Dest_DPAD4_UP_RIGHT								= WCHARI(L"POV4 ↑→");
	I18N.Dest_DPAD4_RIGHT									= WCHARI(L"POV4 →");
	I18N.Dest_DPAD4_DOWN_RIGHT								= WCHARI(L"POV4 ↓→");
	I18N.Dest_DPAD4_DOWN									= WCHARI(L"POV4 ↓");
	I18N.Dest_DPAD4_DOWN_LEFT								= WCHARI(L"POV4 ←↓");
	I18N.Dest_WORK1AX										= WCHARI(L"WORK1AX");
	I18N.Dest_WORK2AX										= WCHARI(L"WORK2AX");
	I18N.Dest_WORK3AX										= WCHARI(L"WORK3AX");
	I18N.Dest_WORK4AX										= WCHARI(L"WORK4AX");
	I18N.Dest_WORK5AX										= WCHARI(L"WORK5AX");
	I18N.Dest_WORK6AX										= WCHARI(L"WORK6AX");
	I18N.Dest_WORK7AX										= WCHARI(L"WORK7AX");
	I18N.Dest_WORK8AX										= WCHARI(L"WORK8AX");
	I18N.Dest_WORK1TR										= WCHARI(L"WORK1TR");
	I18N.Dest_WORK2TR										= WCHARI(L"WORK2TR");
	I18N.Dest_WORK3TR										= WCHARI(L"WORK3TR");
	I18N.Dest_WORK4TR										= WCHARI(L"WORK4TR");
	I18N.Dest_WORK5TR										= WCHARI(L"WORK5TR");
	I18N.Dest_WORK6TR										= WCHARI(L"WORK6TR");
	I18N.Dest_WORK7TR										= WCHARI(L"WORK7TR");
	I18N.Dest_WORK8TR										= WCHARI(L"WORK8TR");
	I18N.Dest_BUTTON										= WCHARI(L"%d");
	I18N.Dest_BUTTON_WORK									= WCHARI(L"WORK%d");

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
	I18N.MouseAction_MAGNIFY								= WCHARI(L"Magnify");
	I18N.MouseAction_MAGNIFY_PLUS							= WCHARI(L"Magnify+");
	I18N.MouseAction_MAGNIFY_MINUS							= WCHARI(L"Magnify-");
	I18N.MouseAction_MAGNIFY_RESET							= WCHARI(L"Magnify Reset");
	I18N.MouseAction_MAGNIFY_UP								= WCHARI(L"Magnify ↑");
	I18N.MouseAction_MAGNIFY_DOWN							= WCHARI(L"Magnify ↓");
	I18N.MouseAction_MAGNIFY_LEFT							= WCHARI(L"Magnify ←");
	I18N.MouseAction_MAGNIFY_RIGHT							= WCHARI(L"Magnify →");
	I18N.MouseAction_MAGNIFY_LOCK							= WCHARI(L"Magnify Lock");
	I18N.MouseAction_MAGNIFY_CURSOR_ON						= WCHARI(L"Mag Cur On");
	I18N.MouseAction_MAGNIFY_CURSOR_OFF						= WCHARI(L"Mag Cur Off");
	I18N.MouseAction_MAGNIFY_CURSOR_SWITCH					= WCHARI(L"Mag Cur Switch");
	I18N.MouseAction_MSE_CAN_BYPASS_ON						= WCHARI(L"Mse bypass On");
	I18N.MouseAction_MSE_CAN_BYPASS_OFF						= WCHARI(L"Mse bypass Off");

	I18N.SpecialAction_MUTE_SOUND							= WCHARI(L"Mute/Unmute");
	I18N.SpecialAction_VOLUME_UP							= WCHARI(L"Volume up");
	I18N.SpecialAction_VOLUME_DOWN							= WCHARI(L"Volume down");
	I18N.SpecialAction_MEMORIZE_MODE						= WCHARI(L"Memorize mode");
	I18N.SpecialAction_TO_MEM_MODE							= WCHARI(L"To Mem Mode");
	I18N.SpecialAction_TO_MODE1								= WCHARI(L"To Mode: 1");
	I18N.SpecialAction_TO_MODE2								= WCHARI(L"To Mode: 2");
	I18N.SpecialAction_TO_MODE3								= WCHARI(L"To Mode: 3");
	I18N.SpecialAction_TO_MODE4								= WCHARI(L"To Mode: 4");
	I18N.SpecialAction_TO_MODE5								= WCHARI(L"To Mode: 5");
	I18N.SpecialAction_TO_MODE6								= WCHARI(L"To Mode: 6");
	I18N.SpecialAction_TO_MODE7								= WCHARI(L"To Mode: 7");
	I18N.SpecialAction_TO_MODE8								= WCHARI(L"To Mode: 8");
	I18N.SpecialAction_TO_LAST_MODE							= WCHARI(L"To Last Mode");
	I18N.SpecialAction_BASE_TO_MODE1						= WCHARI(L"Base To: 1");
	I18N.SpecialAction_BASE_TO_MODE2						= WCHARI(L"Base To: 2");
	I18N.SpecialAction_BASE_TO_MODE3						= WCHARI(L"Base To: 3");
	I18N.SpecialAction_BASE_TO_MODE4						= WCHARI(L"Base To: 4");
	I18N.SpecialAction_BASE_TO_MODE5						= WCHARI(L"Base To: 5");
	I18N.SpecialAction_BASE_TO_MODE6						= WCHARI(L"Base To: 6");
	I18N.SpecialAction_BASE_TO_MODE7						= WCHARI(L"Base To: 7");
	I18N.SpecialAction_BASE_TO_MODE8						= WCHARI(L"Base To: 8");
	I18N.SpecialAction_TO_BASE_MODE							= WCHARI(L"To Base Mode");
	I18N.SpecialAction_FORGOT_RELEASED						= WCHARI(L"Forgot released");
	I18N.SpecialAction_IF_RELEASED_GOTO						= WCHARI(L"If released goto");
	I18N.SpecialAction_IF_PUSHED_GOTO						= WCHARI(L"If pushed goto");
	I18N.SpecialAction_RETURN_TO							= WCHARI(L"Return to");
	I18N.SpecialAction_INTERRUPT							= WCHARI(L"Interrupt");
	I18N.SpecialAction_NO_SUSTAIN							= WCHARI(L"No sustain");
	I18N.SpecialAction_PAUSE								= WCHARI(L"Pause");
	I18N.SpecialAction_CHANGE_POSITION						= WCHARI(L"Change position");
	I18N.SpecialAction_STANCE1								= WCHARI(L"Stance 1 Back");
	I18N.SpecialAction_STANCE2								= WCHARI(L"Stance 2 Leaned");
	I18N.SpecialAction_STANCE3								= WCHARI(L"Stance 3 Both");
	I18N.SpecialAction_STANCE4								= WCHARI(L"Stance 4 Sat");
	I18N.SpecialAction_STANCE5								= WCHARI(L"Stance 5 Leaning");
	I18N.SpecialAction_BEEP1								= WCHARI(L"Beep 1");
	I18N.SpecialAction_BEEP2								= WCHARI(L"Beep 2");
	I18N.SpecialAction_BEEP3								= WCHARI(L"Beep 3");
	I18N.SpecialAction_RESET_STATS							= WCHARI(L"Reset stats");
	I18N.SpecialAction_ADDSTAT1								= WCHARI(L"Add stat 1");
	I18N.SpecialAction_ADDSTAT2								= WCHARI(L"Add stat 2");
	I18N.SpecialAction_ADDSTAT3								= WCHARI(L"Add stat 3");
	I18N.SpecialAction_ADDSTAT4								= WCHARI(L"Add stat 4");
	I18N.SpecialAction_ADDSTAT5								= WCHARI(L"Add stat 5");
	I18N.SpecialAction_ADDSTAT6								= WCHARI(L"Add stat 6");
	I18N.SpecialAction_ADDSTAT7								= WCHARI(L"Add stat 7");
	I18N.SpecialAction_ADDSTAT8								= WCHARI(L"Add stat 8");
	I18N.SpecialAction_KBD_INPUT_ON							= WCHARI(L"KBD Input On");
	I18N.SpecialAction_KBD_INPUT_OFF						= WCHARI(L"KBD Input Off");
	I18N.SpecialAction_MSE_INPUT_ON							= WCHARI(L"MSE Input On");
	I18N.SpecialAction_MSE_INPUT_OFF						= WCHARI(L"MSE Input Off");
	I18N.SpecialAction_SCREENSHOT							= WCHARI(L"Screenshot");
	I18N.SpecialAction_MINIMIZE								= WCHARI(L"Minimize");
	I18N.SpecialAction_RESTORE								= WCHARI(L"Restore");
	I18N.SpecialAction_TRANSPARENCY							= WCHARI(L"Transparency");
	I18N.SpecialAction_INPUT_OFF							= WCHARI(L"Input Off");
	I18N.SpecialAction_DS4_INPUT_ON							= WCHARI(L"DS4 Input On");
	I18N.SpecialAction_DS5_INPUT_ON							= WCHARI(L"DS5 Input On");
	I18N.SpecialAction_DI_INPUT_ON							= WCHARI(L"DI Input On");
	I18N.SpecialAction_XI_INPUT_ON							= WCHARI(L"XI Input On");
	I18N.SpecialAction_EXIT									= WCHARI(L"Exit");

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
	I18N.Effect_X_INV										= WCHARI(L"X INV");
	I18N.Effect_Y_INV										= WCHARI(L"Y INV");
	I18N.Effect_Z_INV										= WCHARI(L"Z INV");
	I18N.Effect_RZ_INV										= WCHARI(L"RZ INV");
	I18N.Effect_RX_INV										= WCHARI(L"RX INV");
	I18N.Effect_RY_INV										= WCHARI(L"RY INV");
	I18N.Effect_X_PLUS										= WCHARI(L"X +");
	I18N.Effect_Y_PLUS										= WCHARI(L"Y +");
	I18N.Effect_Z_PLUS										= WCHARI(L"Z +");
	I18N.Effect_RZ_PLUS										= WCHARI(L"RZ +");
	I18N.Effect_RX_PLUS										= WCHARI(L"RX +");
	I18N.Effect_RY_PLUS										= WCHARI(L"RY +");
	I18N.Effect_X_MINUS										= WCHARI(L"X -");
	I18N.Effect_Y_MINUS										= WCHARI(L"Y -");
	I18N.Effect_Z_MINUS										= WCHARI(L"Z -");
	I18N.Effect_RZ_MINUS									= WCHARI(L"RZ -");
	I18N.Effect_RX_MINUS									= WCHARI(L"RX -");
	I18N.Effect_RY_MINUS									= WCHARI(L"RY -");
	I18N.Effect_X_DIM										= WCHARI(L"X DIM");
	I18N.Effect_X_DIM_P1									= WCHARI(L"X DIM P1");
	I18N.Effect_X_DIM_P2									= WCHARI(L"X DIM P2");
	I18N.Effect_Y_DIM										= WCHARI(L"Y DIM");
	I18N.Effect_Y_DIM_P1									= WCHARI(L"Y DIM P1");
	I18N.Effect_Y_DIM_P2									= WCHARI(L"Y DIM P2");
	I18N.Effect_Z_DIM										= WCHARI(L"Z DIM");
	I18N.Effect_Z_DIM_P1									= WCHARI(L"Z DIM P1");
	I18N.Effect_Z_DIM_P2									= WCHARI(L"Z DIM P2");
	I18N.Effect_RZ_DIM										= WCHARI(L"RZ DIM");
	I18N.Effect_RZ_DIM_P1									= WCHARI(L"RZ DIM P1");
	I18N.Effect_RZ_DIM_P2									= WCHARI(L"RZ DIM P2");
	I18N.Effect_RX_DIM_P1									= WCHARI(L"RX DIM P1");
	I18N.Effect_RX_DIM_P2									= WCHARI(L"RX DIM P2");
	I18N.Effect_RY_DIM_P1									= WCHARI(L"RY DIM P1");
	I18N.Effect_RY_DIM_P2									= WCHARI(L"RY DIM P2");
	I18N.Effect_XY_DEL_12_1									= WCHARI(L"XY DEL-12 1");
	I18N.Effect_XY_DEL_12_2									= WCHARI(L"XY DEL-12 2");
	I18N.Effect_XY_DEL_12_3									= WCHARI(L"XY DEL-12 3");
	I18N.Effect_XY_DEL_12_4									= WCHARI(L"XY DEL-12 4");
	I18N.Effect_XY_DEL_12_5									= WCHARI(L"XY DEL-12 5");
	I18N.Effect_XY_DEL_12_6									= WCHARI(L"XY DEL-12 6");
	I18N.Effect_XY_DEL_12_7									= WCHARI(L"XY DEL-12 7");
	I18N.Effect_XY_DEL_12_8									= WCHARI(L"XY DEL-12 8");
	I18N.Effect_XY_DEL_12_9									= WCHARI(L"XY DEL-12 9");
	I18N.Effect_XY_DEL_12_10								= WCHARI(L"XY DEL-12 10");
	I18N.Effect_XY_DEL_12_11								= WCHARI(L"XY DEL-12 11");
	I18N.Effect_XY_DEL_12_12								= WCHARI(L"XY DEL-12 12");
	I18N.Effect_ZRZ_DEL_12_1								= WCHARI(L"ZRZ DEL-12 1");
	I18N.Effect_ZRZ_DEL_12_2								= WCHARI(L"ZRZ DEL-12 2");
	I18N.Effect_ZRZ_DEL_12_3								= WCHARI(L"ZRZ DEL-12 3");
	I18N.Effect_ZRZ_DEL_12_4								= WCHARI(L"ZRZ DEL-12 4");
	I18N.Effect_ZRZ_DEL_12_5								= WCHARI(L"ZRZ DEL-12 5");
	I18N.Effect_ZRZ_DEL_12_6								= WCHARI(L"ZRZ DEL-12 6");
	I18N.Effect_ZRZ_DEL_12_7								= WCHARI(L"ZRZ DEL-12 7");
	I18N.Effect_ZRZ_DEL_12_8								= WCHARI(L"ZRZ DEL-12 8");
	I18N.Effect_ZRZ_DEL_12_9								= WCHARI(L"ZRZ DEL-12 9");
	I18N.Effect_ZRZ_DEL_12_10								= WCHARI(L"ZRZ DEL-12 10");
	I18N.Effect_ZRZ_DEL_12_11								= WCHARI(L"ZRZ DEL-12 11");
	I18N.Effect_ZRZ_DEL_12_12								= WCHARI(L"ZRZ DEL-12 12");
	I18N.Effect_XY_DEL_16_1									= WCHARI(L"XY DEL-16 1");
	I18N.Effect_XY_DEL_16_2									= WCHARI(L"XY DEL-16 2");
	I18N.Effect_XY_DEL_16_3									= WCHARI(L"XY DEL-16 3");
	I18N.Effect_XY_DEL_16_4									= WCHARI(L"XY DEL-16 4");
	I18N.Effect_XY_DEL_16_5									= WCHARI(L"XY DEL-16 5");
	I18N.Effect_XY_DEL_16_6									= WCHARI(L"XY DEL-16 6");
	I18N.Effect_XY_DEL_16_7									= WCHARI(L"XY DEL-16 7");
	I18N.Effect_XY_DEL_16_8									= WCHARI(L"XY DEL-16 8");
	I18N.Effect_XY_DEL_16_9									= WCHARI(L"XY DEL-16 9");
	I18N.Effect_XY_DEL_16_10								= WCHARI(L"XY DEL-16 10");
	I18N.Effect_XY_DEL_16_11								= WCHARI(L"XY DEL-16 11");
	I18N.Effect_XY_DEL_16_12								= WCHARI(L"XY DEL-16 12");
	I18N.Effect_XY_DEL_16_13								= WCHARI(L"XY DEL-16 13");
	I18N.Effect_XY_DEL_16_14								= WCHARI(L"XY DEL-16 14");
	I18N.Effect_XY_DEL_16_15								= WCHARI(L"XY DEL-16 15");
	I18N.Effect_XY_DEL_16_16								= WCHARI(L"XY DEL-16 16");
	I18N.Effect_ZRZ_DEL_16_1								= WCHARI(L"ZRZ DEL-16 1");
	I18N.Effect_ZRZ_DEL_16_2								= WCHARI(L"ZRZ DEL-16 2");
	I18N.Effect_ZRZ_DEL_16_3								= WCHARI(L"ZRZ DEL-16 3");
	I18N.Effect_ZRZ_DEL_16_4								= WCHARI(L"ZRZ DEL-16 4");
	I18N.Effect_ZRZ_DEL_16_5								= WCHARI(L"ZRZ DEL-16 5");
	I18N.Effect_ZRZ_DEL_16_6								= WCHARI(L"ZRZ DEL-16 6");
	I18N.Effect_ZRZ_DEL_16_7								= WCHARI(L"ZRZ DEL-16 7");
	I18N.Effect_ZRZ_DEL_16_8								= WCHARI(L"ZRZ DEL-16 8");
	I18N.Effect_ZRZ_DEL_16_9								= WCHARI(L"ZRZ DEL-16 9");
	I18N.Effect_ZRZ_DEL_16_10								= WCHARI(L"ZRZ DEL-16 10");
	I18N.Effect_ZRZ_DEL_16_11								= WCHARI(L"ZRZ DEL-16 11");
	I18N.Effect_ZRZ_DEL_16_12								= WCHARI(L"ZRZ DEL-16 12");
	I18N.Effect_ZRZ_DEL_16_13								= WCHARI(L"ZRZ DEL-16 13");
	I18N.Effect_ZRZ_DEL_16_14								= WCHARI(L"ZRZ DEL-16 14");
	I18N.Effect_ZRZ_DEL_16_15								= WCHARI(L"ZRZ DEL-16 15");
	I18N.Effect_ZRZ_DEL_16_16								= WCHARI(L"ZRZ DEL-16 16");
	I18N.Effect_RX_DEL_3_1									= WCHARI(L"RX DEL 3 1");
	I18N.Effect_RX_DEL_3_2									= WCHARI(L"RX DEL 3 2");
	I18N.Effect_RX_DEL_3_3									= WCHARI(L"RX DEL 3 3");
	I18N.Effect_RX_DEL_4_1									= WCHARI(L"RX DEL 4 1");
	I18N.Effect_RX_DEL_4_2									= WCHARI(L"RX DEL 4 2");
	I18N.Effect_RX_DEL_4_3									= WCHARI(L"RX DEL 4 3");
	I18N.Effect_RX_DEL_4_4									= WCHARI(L"RX DEL 4 4");
	I18N.Effect_RY_DEL_3_1									= WCHARI(L"RY DEL 3 1");
	I18N.Effect_RY_DEL_3_2									= WCHARI(L"RY DEL 3 2");
	I18N.Effect_RY_DEL_3_3									= WCHARI(L"RY DEL 3 3");
	I18N.Effect_RY_DEL_4_1									= WCHARI(L"RY DEL 4 1");
	I18N.Effect_RY_DEL_4_2									= WCHARI(L"RY DEL 4 2");
	I18N.Effect_RY_DEL_4_3									= WCHARI(L"RY DEL 4 3");
	I18N.Effect_RY_DEL_4_4									= WCHARI(L"RY DEL 4 4");
	I18N.Effect_XY_DISTORT_U___								= WCHARI(L"XY DIST. U___");
	I18N.Effect_XY_DISTORT__U__								= WCHARI(L"XY DIST. _U__");
	I18N.Effect_XY_DISTORT___U_								= WCHARI(L"XY DIST. __U_");
	I18N.Effect_XY_DISTORT____U								= WCHARI(L"XY DIST. ___U");
	I18N.Effect_XY_DISTORT_UU__								= WCHARI(L"XY DIST. UU__");
	I18N.Effect_XY_DISTORT__UU_								= WCHARI(L"XY DIST. _UU_");
	I18N.Effect_XY_DISTORT___UU								= WCHARI(L"XY DIST. __UU");
	I18N.Effect_XY_DISTORT_UUU_								= WCHARI(L"XY DIST. UUU_");
	I18N.Effect_XY_DISTORT__UUU								= WCHARI(L"XY DIST. _UUU");
	I18N.Effect_XY_DISTORT_UUUU								= WCHARI(L"XY DIST. UUUU");
	I18N.Effect_XY_DISTORT_D___								= WCHARI(L"XY DIST. D___");
	I18N.Effect_XY_DISTORT__D__								= WCHARI(L"XY DIST. _D__");
	I18N.Effect_XY_DISTORT___D_								= WCHARI(L"XY DIST. __D_");
	I18N.Effect_XY_DISTORT____D								= WCHARI(L"XY DIST. ___D");
	I18N.Effect_XY_DISTORT_DD__								= WCHARI(L"XY DIST. DD__");
	I18N.Effect_XY_DISTORT__DD_								= WCHARI(L"XY DIST. _DD_");
	I18N.Effect_XY_DISTORT___DD								= WCHARI(L"XY DIST. __DD");
	I18N.Effect_XY_DISTORT_DDD_								= WCHARI(L"XY DIST. DDD_");
	I18N.Effect_XY_DISTORT__DDD								= WCHARI(L"XY DIST. _DDD");
	I18N.Effect_XY_DISTORT_DDDD								= WCHARI(L"XY DIST. DDDD");
	I18N.Effect_XY_DISTORT_U_____							= WCHARI(L"XY_DIST. U_____");
	I18N.Effect_XY_DISTORT__U____							= WCHARI(L"XY_DIST. _U____");
	I18N.Effect_XY_DISTORT___U___							= WCHARI(L"XY_DIST. __U___");
	I18N.Effect_XY_DISTORT____U__							= WCHARI(L"XY_DIST. ___U__");
	I18N.Effect_XY_DISTORT_____U_							= WCHARI(L"XY_DIST. ____U_");
	I18N.Effect_XY_DISTORT______U							= WCHARI(L"XY_DIST. _____U");
	I18N.Effect_XY_DISTORT_UU____							= WCHARI(L"XY_DIST. UU____");
	I18N.Effect_XY_DISTORT__UU___							= WCHARI(L"XY_DIST. _UU___");
	I18N.Effect_XY_DISTORT___UU__							= WCHARI(L"XY_DIST. __UU__");
	I18N.Effect_XY_DISTORT____UU_							= WCHARI(L"XY_DIST. ___UU_");
	I18N.Effect_XY_DISTORT_____UU							= WCHARI(L"XY_DIST. ____UU");
	I18N.Effect_XY_DISTORT__UUU__							= WCHARI(L"XY_DIST. _UUU__");
	I18N.Effect_XY_DISTORT___UUU_							= WCHARI(L"XY_DIST. __UUU_");
	I18N.Effect_XY_DISTORT_UUUU__							= WCHARI(L"XY_DIST. UUUU__");
	I18N.Effect_XY_DISTORT__UUUU_							= WCHARI(L"XY_DIST. _UUUU_");
	I18N.Effect_XY_DISTORT___UUUU							= WCHARI(L"XY_DIST. __UUUU");
	I18N.Effect_XY_DISTORT_UUUUU_							= WCHARI(L"XY_DIST. UUUUU_");
	I18N.Effect_XY_DISTORT__UUUUU							= WCHARI(L"XY_DIST. _UUUUU");
	I18N.Effect_XY_DISTORT_D_____							= WCHARI(L"XY_DIST. D_____");
	I18N.Effect_XY_DISTORT__D____							= WCHARI(L"XY_DIST. _D____");
	I18N.Effect_XY_DISTORT___D___							= WCHARI(L"XY_DIST. __D___");
	I18N.Effect_XY_DISTORT____D__							= WCHARI(L"XY_DIST. ___D__");
	I18N.Effect_XY_DISTORT_____D_							= WCHARI(L"XY_DIST. ____D_");
	I18N.Effect_XY_DISTORT______D							= WCHARI(L"XY_DIST. _____D");
	I18N.Effect_XY_DISTORT_DD____							= WCHARI(L"XY_DIST. DD____");
	I18N.Effect_XY_DISTORT__DD___							= WCHARI(L"XY_DIST. _DD___");
	I18N.Effect_XY_DISTORT___DD__							= WCHARI(L"XY_DIST. __DD__");
	I18N.Effect_XY_DISTORT____DD_							= WCHARI(L"XY_DIST. ___DD_");
	I18N.Effect_XY_DISTORT_____DD							= WCHARI(L"XY_DIST. ____DD");
	I18N.Effect_XY_DISTORT__DDD__							= WCHARI(L"XY_DIST. _DDD__");
	I18N.Effect_XY_DISTORT___DDD_							= WCHARI(L"XY_DIST. __DDD_");
	I18N.Effect_XY_DISTORT_DDDD__							= WCHARI(L"XY_DIST. DDDD__");
	I18N.Effect_XY_DISTORT__DDDD_							= WCHARI(L"XY_DIST. _DDDD_");
	I18N.Effect_XY_DISTORT___DDDD							= WCHARI(L"XY_DIST. __DDDD");
	I18N.Effect_XY_DISTORT_DDDDD_							= WCHARI(L"XY_DIST. DDDDD_");
	I18N.Effect_XY_DISTORT__DDDDD							= WCHARI(L"XY_DIST. _DDDDD");
	I18N.Effect_ZRZ_DISTORT_U___							= WCHARI(L"ZRZ DIST. U___");
	I18N.Effect_ZRZ_DISTORT__U__							= WCHARI(L"ZRZ DIST. _U__");
	I18N.Effect_ZRZ_DISTORT___U_							= WCHARI(L"ZRZ DIST. __U_");
	I18N.Effect_ZRZ_DISTORT____U							= WCHARI(L"ZRZ DIST. ___U");
	I18N.Effect_ZRZ_DISTORT_UU__							= WCHARI(L"ZRZ DIST. UU__");
	I18N.Effect_ZRZ_DISTORT__UU_							= WCHARI(L"ZRZ DIST. _UU_");
	I18N.Effect_ZRZ_DISTORT___UU							= WCHARI(L"ZRZ DIST. __UU");
	I18N.Effect_ZRZ_DISTORT_UUU_							= WCHARI(L"ZRZ DIST. UUU_");
	I18N.Effect_ZRZ_DISTORT__UUU							= WCHARI(L"ZRZ DIST. _UUU");
	I18N.Effect_ZRZ_DISTORT_UUUU							= WCHARI(L"ZRZ DIST. UUUU");
	I18N.Effect_ZRZ_DISTORT_D___							= WCHARI(L"ZRZ DIST. D___");
	I18N.Effect_ZRZ_DISTORT__D__							= WCHARI(L"ZRZ DIST. _D__");
	I18N.Effect_ZRZ_DISTORT___D_							= WCHARI(L"ZRZ DIST. __D_");
	I18N.Effect_ZRZ_DISTORT____D							= WCHARI(L"ZRZ DIST. ___D");
	I18N.Effect_ZRZ_DISTORT_DD__							= WCHARI(L"ZRZ DIST. DD__");
	I18N.Effect_ZRZ_DISTORT__DD_							= WCHARI(L"ZRZ DIST. _DD_");
	I18N.Effect_ZRZ_DISTORT___DD							= WCHARI(L"ZRZ DIST. __DD");
	I18N.Effect_ZRZ_DISTORT_DDD_							= WCHARI(L"ZRZ DIST. DDD_");
	I18N.Effect_ZRZ_DISTORT__DDD							= WCHARI(L"ZRZ DIST. _DDD");
	I18N.Effect_ZRZ_DISTORT_DDDD							= WCHARI(L"ZRZ DIST. DDDD");
	I18N.Effect_ZRZ_DISTORT_U_____							= WCHARI(L"ZRZ_DIST. U_____");
	I18N.Effect_ZRZ_DISTORT__U____							= WCHARI(L"ZRZ_DIST. _U____");
	I18N.Effect_ZRZ_DISTORT___U___							= WCHARI(L"ZRZ_DIST. __U___");
	I18N.Effect_ZRZ_DISTORT____U__							= WCHARI(L"ZRZ_DIST. ___U__");
	I18N.Effect_ZRZ_DISTORT_____U_							= WCHARI(L"ZRZ_DIST. ____U_");
	I18N.Effect_ZRZ_DISTORT______U							= WCHARI(L"ZRZ_DIST. _____U");
	I18N.Effect_ZRZ_DISTORT_UU____							= WCHARI(L"ZRZ_DIST. UU____");
	I18N.Effect_ZRZ_DISTORT__UU___							= WCHARI(L"ZRZ_DIST. _UU___");
	I18N.Effect_ZRZ_DISTORT___UU__							= WCHARI(L"ZRZ_DIST. __UU__");
	I18N.Effect_ZRZ_DISTORT____UU_							= WCHARI(L"ZRZ_DIST. ___UU_");
	I18N.Effect_ZRZ_DISTORT_____UU							= WCHARI(L"ZRZ_DIST. ____UU");
	I18N.Effect_ZRZ_DISTORT__UUU__							= WCHARI(L"ZRZ_DIST. _UUU__");
	I18N.Effect_ZRZ_DISTORT___UUU_							= WCHARI(L"ZRZ_DIST. __UUU_");
	I18N.Effect_ZRZ_DISTORT_UUUU__							= WCHARI(L"ZRZ_DIST. UUUU__");
	I18N.Effect_ZRZ_DISTORT__UUUU_							= WCHARI(L"ZRZ_DIST. _UUUU_");
	I18N.Effect_ZRZ_DISTORT___UUUU							= WCHARI(L"ZRZ_DIST. __UUUU");
	I18N.Effect_ZRZ_DISTORT_UUUUU_							= WCHARI(L"ZRZ_DIST. UUUUU_");
	I18N.Effect_ZRZ_DISTORT__UUUUU							= WCHARI(L"ZRZ_DIST. _UUUUU");
	I18N.Effect_ZRZ_DISTORT_D_____							= WCHARI(L"ZRZ_DIST. D_____");
	I18N.Effect_ZRZ_DISTORT__D____							= WCHARI(L"ZRZ_DIST. _D____");
	I18N.Effect_ZRZ_DISTORT___D___							= WCHARI(L"ZRZ_DIST. __D___");
	I18N.Effect_ZRZ_DISTORT____D__							= WCHARI(L"ZRZ_DIST. ___D__");
	I18N.Effect_ZRZ_DISTORT_____D_							= WCHARI(L"ZRZ_DIST. ____D_");
	I18N.Effect_ZRZ_DISTORT______D							= WCHARI(L"ZRZ_DIST. _____D");
	I18N.Effect_ZRZ_DISTORT_DD____							= WCHARI(L"ZRZ_DIST. DD____");
	I18N.Effect_ZRZ_DISTORT__DD___							= WCHARI(L"ZRZ_DIST. _DD___");
	I18N.Effect_ZRZ_DISTORT___DD__							= WCHARI(L"ZRZ_DIST. __DD__");
	I18N.Effect_ZRZ_DISTORT____DD_							= WCHARI(L"ZRZ_DIST. ___DD_");
	I18N.Effect_ZRZ_DISTORT_____DD							= WCHARI(L"ZRZ_DIST. ____DD");
	I18N.Effect_ZRZ_DISTORT__DDD__							= WCHARI(L"ZRZ_DIST. _DDD__");
	I18N.Effect_ZRZ_DISTORT___DDD_							= WCHARI(L"ZRZ_DIST. __DDD_");
	I18N.Effect_ZRZ_DISTORT_DDDD__							= WCHARI(L"ZRZ_DIST. DDDD__");
	I18N.Effect_ZRZ_DISTORT__DDDD_							= WCHARI(L"ZRZ_DIST. _DDDD_");
	I18N.Effect_ZRZ_DISTORT___DDDD							= WCHARI(L"ZRZ_DIST. __DDDD");
	I18N.Effect_ZRZ_DISTORT_DDDDD_							= WCHARI(L"ZRZ_DIST. DDDDD_");
	I18N.Effect_ZRZ_DISTORT__DDDDD							= WCHARI(L"ZRZ_DIST. _DDDDD");
	I18N.ModulesAction_NOTEPAD								= WCHARI(L"Notepad");
	I18N.ModulesAction_NOTEPAD_DOWN							= WCHARI(L"Notepad ↓");
	I18N.ModulesAction_NOTEPAD_UP							= WCHARI(L"Notepad ↑");
	I18N.ModulesAction_WEB_DOWN								= WCHARI(L"Web ↓");
	I18N.ModulesAction_WEB_UP								= WCHARI(L"Web ↑");
	I18N.ModulesAction_WEB_LEFT								= WCHARI(L"Web ←");
	I18N.ModulesAction_WEB_RIGHT							= WCHARI(L"Web →");
	I18N.ModulesAction_WEB_PREVIOUSTAB						= WCHARI(L"Tab «");
	I18N.ModulesAction_WEB_NEXTTAB							= WCHARI(L"Tab »");
	I18N.ModulesAction_WEB_CLOSETAB							= WCHARI(L"Close Tab");
	I18N.ModulesAction_WEB_FULLSCREEN						= WCHARI(L"FullScreen");
	I18N.ModulesAction_WEB_HOME								= WCHARI(L"Home");
	I18N.ModulesAction_WEB_FAVORITE1						= WCHARI(L"Favorite1");
	I18N.ModulesAction_WEB_FAVORITE2						= WCHARI(L"Favorite2");
	I18N.ModulesAction_WEB_FAVORITE3						= WCHARI(L"Favorite3");
	I18N.ModulesAction_WEB_FAVORITE4						= WCHARI(L"Favorite4");
	I18N.ModulesAction_WEB_FAVORITE5						= WCHARI(L"Favorite5");
	I18N.ModulesAction_WEB_FAVORITE6						= WCHARI(L"Favorite6");
	I18N.ModulesAction_WEB_FAVORITE7						= WCHARI(L"Favorite7");
	I18N.ModulesAction_WEB_FAVORITE8						= WCHARI(L"Favorite8");
	I18N.ModulesAction_WEB_FAVORITE9						= WCHARI(L"Favorite9");
	I18N.ModulesAction_WEB_BACK								= WCHARI(L"Back");
	I18N.ModulesAction_WEB_NEXT								= WCHARI(L"Next");
	I18N.ModulesAction_WEB_REFRESH							= WCHARI(L"Refresh");
	I18N.ModulesAction_WEB_CANCEL							= WCHARI(L"Cancel");
	I18N.ModulesAction_WEB_AUTOREFRESH						= WCHARI(L"Autorefresh");
	I18N.ModulesAction_WEB_ZOOMMINUS						= WCHARI(L"Zoom-");
	I18N.ModulesAction_WEB_ZOOMPLUS							= WCHARI(L"Zoom+");
	I18N.ModulesAction_WEB_ZOOMRESET						= WCHARI(L"Zoom Reset");
	I18N.ModulesAction_WEB_ZOOMSET							= WCHARI(L"Zoom Set");
	I18N.ModulesAction_WEB_VISIBILITY						= WCHARI(L"Visibility");
	I18N.ModulesAction_WEB_SCREENSHOT						= WCHARI(L"Screenshot");
	I18N.ModulesAction_WEB_DARKMODE							= WCHARI(L"Darkmode");
	I18N.ModulesAction_WEB_DARKMODE2						= WCHARI(L"Darkmode2");
	I18N.ModulesAction_LINKS_APPLICATION0					= WCHARI(L"Appli 0");
	I18N.ModulesAction_LINKS_APPLICATION1					= WCHARI(L"Appli 1");
	I18N.ModulesAction_LINKS_APPLICATION2					= WCHARI(L"Appli 2");
	I18N.ModulesAction_LINKS_APPLICATION3					= WCHARI(L"Appli 3");
	I18N.ModulesAction_LINKS_APPLICATION4					= WCHARI(L"Appli 4");

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
	
	I18N.Dispatch_1_X										= WCHARI(L"1 X");
	I18N.Dispatch_1_Y										= WCHARI(L"1 Y");
	I18N.Dispatch_1_Z										= WCHARI(L"1 Z");
	I18N.Dispatch_1_RX										= WCHARI(L"1 RX");
	I18N.Dispatch_1_RY										= WCHARI(L"1 RY");
	I18N.Dispatch_1_RZ										= WCHARI(L"1 RZ");
	I18N.Dispatch_1_SL0										= WCHARI(L"1 SL0");
	I18N.Dispatch_1_SL1										= WCHARI(L"1 SL1");
	I18N.Dispatch_2_X										= WCHARI(L"2 X");
	I18N.Dispatch_2_Y										= WCHARI(L"2 Y");
	I18N.Dispatch_2_Z										= WCHARI(L"2 Z");
	I18N.Dispatch_2_RX										= WCHARI(L"2 RX");
	I18N.Dispatch_2_RY										= WCHARI(L"2 RY");
	I18N.Dispatch_2_RZ										= WCHARI(L"2 RZ");
	I18N.Dispatch_2_SL0										= WCHARI(L"2 SL0");
	I18N.Dispatch_2_SL1										= WCHARI(L"2 SL1");
	I18N.Dispatch_1_POV1									= WCHARI(L"1 POV1");
	I18N.Dispatch_1_POV2									= WCHARI(L"1 POV2");
	I18N.Dispatch_1_POV3									= WCHARI(L"1 POV3");
	I18N.Dispatch_1_POV4									= WCHARI(L"1 POV4");
	I18N.Dispatch_2_POV1									= WCHARI(L"2 POV1");
	I18N.Dispatch_2_POV2									= WCHARI(L"2 POV2");
	I18N.Dispatch_2_POV3									= WCHARI(L"2 POV3");
	I18N.Dispatch_2_POV4									= WCHARI(L"2 POV4");
	I18N.Dispatch_BUTTON									= WCHARI(L"%d %d");

	I18N.ABOUT_1											= WCHARI(L"Ds2vJoy ,");
	I18N.ABOUT_2											= WCHARI(L"From an idea");
	I18N.ABOUT_3											= WCHARI(L"of 090/ Ds4vJoy");
	I18N.ABOUT_OK											= WCHARI(L"OK");
	I18N.SETTINGS_SOURCES									= WCHARI(L"Sources:");
	I18N.SETTINGS_DS4										= WCHARI(L"DS4");
	I18N.SETTINGS_DS5										= WCHARI(L"DS5");
	I18N.SETTINGS_DI										= WCHARI(L"DI");
	I18N.SETTINGS_XI										= WCHARI(L"XI");
	I18N.SETTINGS_KBD										= WCHARI(L"KBD");
	I18N.SETTINGS_MSE										= WCHARI(L"MSE");
	I18N.SETTINGS_COUNTRY									= WCHARI(L"⚑");
	I18N.SETTINGS_VJOY_SHUTDOWN								= WCHARI(L"ShutDown");
	I18N.SETTINGS_ON_EXIT									= WCHARI(L"vJoy on exit");
	I18N.SETTINGS_TEXT_VJ_DEVICE							= WCHARI(L"vJoy device");
	I18N.SETTINGS_TEXT_XI_DEVICE							= WCHARI(L"XIntput device");
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
	I18N.SETTINGS_TEXT_DS_SERIAL							= WCHARI(L"Use the DS serial:");
	I18N.SETTINGS_DI_DEVICE_1								= WCHARI(L"1");
	I18N.SETTINGS_DI_DEVICE_2								= WCHARI(L"2");
	I18N.SETTINGS_DI_DEVICE_RELOAD							= WCHARI(L"↩");
	I18N.SETTINGS_TEXT_DI_DEVICE							= WCHARI(L"DI device:");
	I18N.SETTINGS_DI_DEVICE_CLEAR							= WCHARI(L"X");
	I18N.SETTINGS_DARK_THEME								= WCHARI(L"Dark theme");
	I18N.SETTINGS_TEXT_THRESHOLD							= WCHARI(L"Threshold");
	I18N.SETTINGS_TEXT_SIMULTANEOUS							= WCHARI(L"Simultaneous");
	I18N.SETTINGS_TEXT_LONG									= WCHARI(L"Long");
	I18N.SETTINGS_TEXT_VERY_LONG							= WCHARI(L"Very long");
	I18N.SETTINGS_TEXT_WEBREFRESH							= WCHARI(L"Web refresh");
	I18N.SETTINGS_TEXT_OPACITY								= WCHARI(L"Opacity");
	I18N.SETTINGS_UNIT_THRESHOLD							= WCHARI(L"128");
	I18N.SETTINGS_UNIT_SIMULTANEOUS							= WCHARI(L"ms");
	I18N.SETTINGS_UNIT_LONG									= WCHARI(L"ms");
	I18N.SETTINGS_UNIT_VERY_LONG							= WCHARI(L"ms");
	I18N.SETTINGS_UNIT_WEB_REFRESH							= WCHARI(L"s");
	I18N.SETTINGS_UNIT_OPACITY								= WCHARI(L"%");
	I18N.SETTINGS_MULTIPLE_TOUCHPAD							= WCHARI(L"Multiple Touchpad:");
	I18N.SETTINGS_TEXT_FIRST_BUTTON							= WCHARI(L"First button");
	I18N.SETTINGS_TEXT_COLUMNS								= WCHARI(L"Columns");
	I18N.SETTINGS_TEXT_ROWS									= WCHARI(L"Rows");
	I18N.SETTINGS_LED										= WCHARI(L"Black Led");
	I18N.SETTINGS_WHEN_EXITING								= WCHARI(L"when Exiting");
	I18N.SETTINGS_LED_BUTTON								= WCHARI(L"LED");
	I18N.SETTINGS_COLOR										= WCHARI(L"LED color");

	I18N.VJOY_NOT_INSTALLED									= WCHARI(L"Vjoy not running,\r\n\r\nNeed to be activated under XOutput tab.");
	I18N.VJOY_FAILED										= WCHARI(L"Failed to create HID Report Descriptor");
	I18N.VJOY_RESET_CONFIRM									= WCHARI(L"Are you sure?\r\n\r\nThis will remove all devices\r\nreplacing them with a default device.");
	I18N.VJOY_ADDDEV										= WCHARI(L"Add Device");
	I18N.VJOY_DELDEV										= WCHARI(L"Delete Device");
	I18N.VJOY_AXIS											= WCHARI(L"Axis");
	I18N.VJOY_CHK_X											= WCHARI(L"X");
	I18N.VJOY_CHK_Y											= WCHARI(L"Y");
	I18N.VJOY_CHK_Z											= WCHARI(L"Z");
	I18N.VJOY_CHK_RX										= WCHARI(L"Rx");
	I18N.VJOY_CHK_RY										= WCHARI(L"Ry");
	I18N.VJOY_CHK_RZ										= WCHARI(L"Rz");
	I18N.VJOY_CHK_SL0										= WCHARI(L"Slider");
	I18N.VJOY_CHK_SL1										= WCHARI(L"Slider2");
	I18N.VJOY_BTN											= WCHARI(L"Buttons (0-128)");
	I18N.VJOY_POV											= WCHARI(L"POV");
	I18N.VJOY_POV_DESC										= WCHARI(L"4 Directions");
	I18N.VJOY_POV_CONT										= WCHARI(L"Continuous");
	I18N.VJOY_FFB											= WCHARI(L"Force Feedback");
	I18N.VJOY_CHK_FFB_CONST									= WCHARI(L"Constant");
	I18N.VJOY_CHK_FFB_RAMP									= WCHARI(L"Ramp");
	I18N.VJOY_CHK_FFB_SQUARE								= WCHARI(L"Square");
	I18N.VJOY_CHK_FFB_SINE									= WCHARI(L"Sine");
	I18N.VJOY_CHK_FFB_TRI									= WCHARI(L"Triangle");
	I18N.VJOY_CHK_FFB_STUP									= WCHARI(L"Sawtooth Up");
	I18N.VJOY_CHK_FFB_STDN									= WCHARI(L"Sawtooth Down");
	I18N.VJOY_CHK_FFB_SPRING								= WCHARI(L"Spring");
	I18N.VJOY_CHK_FFB_DAMPER								= WCHARI(L"Damper");
	I18N.VJOY_CHK_FFB_INERTIA								= WCHARI(L"Inertia");
	I18N.VJOY_CHK_FFB_FRICTION								= WCHARI(L"Friction");
	I18N.VJOY_DEVICE_1										= WCHARI(L"1");
	I18N.VJOY_DEVICE_2										= WCHARI(L"2");
	I18N.VJOY_DEVICE_3										= WCHARI(L"3");
	I18N.VJOY_DEVICE_4										= WCHARI(L"4");
	I18N.VJOY_DEVICE_5										= WCHARI(L"5");
	I18N.VJOY_DEVICE_6										= WCHARI(L"6");
	I18N.VJOY_DEVICE_7										= WCHARI(L"7");
	I18N.VJOY_DEVICE_8										= WCHARI(L"8");
	I18N.VJOY_DEVICE_9										= WCHARI(L"9");
	I18N.VJOY_DEVICE_10										= WCHARI(L"10");
	I18N.VJOY_DEVICE_11										= WCHARI(L"11");
	I18N.VJOY_DEVICE_12										= WCHARI(L"12");
	I18N.VJOY_DEVICE_13										= WCHARI(L"13");
	I18N.VJOY_DEVICE_14										= WCHARI(L"14");
	I18N.VJOY_DEVICE_15										= WCHARI(L"15");
	I18N.VJOY_DEVICE_16										= WCHARI(L"16");
	I18N.VJOY_CANCEL										= WCHARI(L"X");
	I18N.VJOY_DEVNUMBER										= WCHARI(L"Device n° ");
	I18N.VJOY_CTRLPANEL										= WCHARI(L"Ctrl Panel");
	I18N.VJOY_APPLY											= WCHARI(L"Apply");
	I18N.VJOY_ADDDEL										= WCHARI(L"A/R");
	I18N.VJOY_RESET											= WCHARI(L"Reset All");
	I18N.DINPUT_CANCEL										= WCHARI(L"X");
	I18N.DINPUT_LOAD1										= WCHARI(L"LOAD 1");
	I18N.DINPUT_LOAD2										= WCHARI(L"LOAD 2");
	I18N.DINPUT_LOAD3										= WCHARI(L"LOAD 3");
	I18N.DINPUT_SAVE1										= WCHARI(L"SAVE 1");
	I18N.DINPUT_SAVE2										= WCHARI(L"SAVE 2");
	I18N.DINPUT_SAVE3										= WCHARI(L"SAVE 3");
	I18N.DINPUT_CLEAR										= WCHARI(L"CLEAR");
	I18N.DINPUT_CTRLPANEL									= WCHARI(L"CTRLPNL");
	I18N.MAPPING_ALWAYS										= WCHARI(L"Always");
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
	I18N.CLONE_POSTIT										= WCHARI(L" Yet another Post-its ");
	I18N.MAPPING_HELP										= WCHARI(L"Help");
	I18N.MAPPING_OK											= WCHARI(L"OK");
	I18N.MAPPING_CLEAR										= WCHARI(L"Clear");
	I18N.MAPPING_CANCEL										= WCHARI(L"x");
	I18N.MAPPING_X											= WCHARI(L"88888");
	I18N.MAPPING_Y											= WCHARI(L"88888");
	I18N.MIND_OK											= WCHARI(L"✓");
	I18N.MIND_CANCEL										= WCHARI(L"✗");
	I18N.RAPIDFIRE_RAPIDFIRE								= WCHARI(L"Source");
	I18N.RAPIDFIRE_MULTIPLE_PRESS							= WCHARI(L"Multiple press");
	I18N.RAPIDFIRE_TEXT_FIRST								= WCHARI(L"First press time");
	I18N.RAPIDFIRE_TEXT_RELEASE								= WCHARI(L"Release time");
	I18N.RAPIDFIRE_TEXT_DOWN								= WCHARI(L"Press time");
	I18N.RAPIDFIRE_UNIT_FIRST								= WCHARI(L"ms");
	I18N.RAPIDFIRE_UNIT_RELEASE								= WCHARI(L"ms");
	I18N.RAPIDFIRE_UNIT_DOWN								= WCHARI(L"ms");
	I18N.RAPIDFIRE_NOTICE									= WCHARI(L"An odd number for Release or Press times add 0-19 ms, differents each turn / push");
	I18N.RAPIDFIRE_OK										= WCHARI(L"OK");
	I18N.RAPIDFIRE_CANCEL									= WCHARI(L"X");
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
	I18N.KEYMAP_CANCEL										= WCHARI(L"X");
	I18N.KEYMAP_WINDOW										= WCHARI(L"Window");
	I18N.KEYMAP_CLASS										= WCHARI(L"Class");
	I18N.KEYMAP_TITLE										= WCHARI(L"Title");
	I18N.KEYMAP_IDX											= WCHARI(L"Idx");
	I18N.KEYMAP_IS_W_VISIBLE								= WCHARI(L"IsWindowVisible");
	I18N.KEYMAP_CLEAR2										= WCHARI(L"Clear");
	I18N.KEYMAP_DELETE										= WCHARI(L"Delete");
	I18N.KEYMAP_OK2											= WCHARI(L"OK");
	I18N.KEYMAP_CANCEL2										= WCHARI(L"Cancel");
	I18N.XOUTPUT_ACTIVE										= WCHARI(L"XOutput Module Active");
	I18N.XOUTPUT_VJOY_ACTIVE								= WCHARI(L"vJoy Driver Active");
	I18N.XOUTPUT_PAD										= WCHARI(L"Desired Virtual Pad:");
	I18N.XOUTPUT_X360										= WCHARI(L"X360");
	I18N.XOUTPUT_DS4										= WCHARI(L"DS4");
	I18N.XOUTPUT_INSTALL									= WCHARI(L"XOutput status");
	I18N.XOUTPUT_INSTALL_VJOY								= WCHARI(L"vJoy status");
	I18N.XOUTPUT_STATUS										= WCHARI(L"XOutput status");
	I18N.HID_ACTIVE											= WCHARI(L"Guardian Module Active");
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
	I18N.WEB_INJECT_SCRIPT_1								= WCHARI(L"Inject Script");
	I18N.WEB_INJECT_SCRIPT_2								= WCHARI(L"Enter script code:");
	I18N.WEB_INJECT_SCRIPT_3								= WCHARI(L"Enter the JavaScript code to run in the webview");
	I18N.WEB_INITIALIZE_SCRIPT_1							= WCHARI(L"Add Initialize Script");
	I18N.WEB_INITIALIZE_SCRIPT_2							= WCHARI(L"nitialization Script:");
	I18N.WEB_INITIALIZE_SCRIPT_3							= WCHARI(L"Enter the JavaScript code to run as the initialization script\r\n\
  that runs before any script in the HTML document.");
	I18N.WEB_POST_MESSAGE_STRING_1							= WCHARI(L"Post Web Message String");
	I18N.WEB_POST_MESSAGE_STRING_2							= WCHARI(L"Web message string:");
	I18N.WEB_POST_MESSAGE_STRING_3							= WCHARI(L"Enter the web message as a string");
	I18N.WEB_POST_MESSAGE_JSON_1							= WCHARI(L"Post Web Message JSON");
	I18N.WEB_POST_MESSAGE_JSON_2							= WCHARI(L"Web message JSON:");
	I18N.WEB_POST_MESSAGE_JSON_3							= WCHARI(L"Enter the web message as JSON");
	I18N.WEB_SUBSCRIBE_CDP_EVENT_1							= WCHARI(L"Subscribe to CDP Event");
	I18N.WEB_SUBSCRIBE_CDP_EVENT_2							= WCHARI(L"CDP event name:");
	I18N.WEB_SUBSCRIBE_CDP_EVENT_3							= WCHARI(L"Enter the name of the CDP event to subscribe to\r\n\
  You may also have to call the \"enable\" method of the\r\n\
  event's domain to receive events (for example \"Log.enable\")");
	I18N.WEB_CALL_CDP_METHOD_1								= WCHARI(L"Call CDP Method");
	I18N.WEB_CALL_CDP_METHOD_2								= WCHARI(L"CDP method name:");
	I18N.WEB_CALL_CDP_METHOD_3								= WCHARI(L"Enter the CDP method name to call, followed by a space,\r\n\
  followed by the parameters in JSON format");
	I18N.WEB_COM_OBJECT_1									= WCHARI(L"Add COM object");
	I18N.WEB_COM_OBJECT_2									= WCHARI(L"CLSID or ProgID of COM object:");
	I18N.WEB_COM_OBJECT_3									= WCHARI(L"Enter the CLSID (eg '{0002DF01-0000-0000-C000-000000000046}')\r\n\
  or ProgID (eg 'InternetExplorer.Application') of the COM object to create and\r\n\
  provide to the WebView as `window.chrome.remoteObjects.example`");
	I18N.WEB_LANGUAGE_1										= WCHARI(L"Language");
	I18N.WEB_LANGUAGE_2										= WCHARI(L"Language:");
	I18N.WEB_LANGUAGE_3										= WCHARI(L"Enter a language to use for WebView, or leave blank to restore default");
	I18N.WEB_USERAGENT_1									= WCHARI(L"User Agent");
	I18N.WEB_USERAGENT_2									= WCHARI(L"User agent:");
	I18N.WEB_USERAGENT_3									= WCHARI(L"Enter user agent, or leave blank to restore default");
	I18N.WEB_BLACKLIST_1									= WCHARI(L"locked Sites");
	I18N.WEB_BLACKLIST_2									= WCHARI(L"Sites:");
	I18N.WEB_BLACKLIST_3									= WCHARI(L"Enter hostnames to block, separated by semicolons");
	I18N.WEB_SCRIPT_DIALOG_1								= WCHARI(L"Script Dialog");
	I18N.WEB_SCRIPT_DIALOG_2								= L"The page at '";
	I18N.WEB_SCRIPT_DIALOG_3								= L"' says:";
	I18N.LINKS_TEXT1										= WCHARI(L"Add webbrowser Home and Favorites 1-4");
	I18N.LINKS_TEXT2										= WCHARI(L"Add webbrowser Favorites 5-9");
	I18N.LINKS_TEXT3										= WCHARI(L"Add the name … and location of 0-4 cmd to place in tray");
	I18N.LINKS_TEXT4										= WCHARI(L"… 0-9 for mapping actions");
	I18N.LINKS_DS2VJOY										= WCHARI(L"<a>Ds2vJoy</a>");
	I18N.LINKS_VJOY											= WCHARI(L"<a>vJoy</a>");
	I18N.LINKS_WEBVIEW2										= WCHARI(L"<a>WebView2</a>");
	I18N.LINKS_VIGEMBUS										= WCHARI(L"<a>ViGEmBus</a>");
	I18N.LINKS_VIGEMCLIENT									= WCHARI(L"<a>ViGEmClient</a>");
	I18N.LINKS_HIDGUARDIAN									= WCHARI(L"<a>HidGuardian</a>");
	I18N.LINKS_HIDCERBERUS									= WCHARI(L"<a>HidCerberus</a>");
	I18N.LINKS_URL_DS2VJOY									= WCHARI(L"https://github.com/ytyra/Ds2vJoy");
	I18N.LINKS_URL_VJOY										= WCHARI(L"https://github.com/jshafer817/vJoy");
	I18N.LINKS_URL_WEBVIEW2									= WCHARI(L"https://developer.microsoft.com/en-us/microsoft-edge/webview2");
	I18N.LINKS_URL_VIGEMBUS									= WCHARI(L"https://github.com/ViGEm/ViGEmBus");
	I18N.LINKS_URL_VIGEMCLIENT								= WCHARI(L"https://github.com/ViGEm/ViGEmClient");
	I18N.LINKS_URL_HIDGUARDIAN								= WCHARI(L"https://github.com/ViGEm/HidGuardian");
	I18N.LINKS_URL_HIDCERBERUS								= WCHARI(L"https://github.com/ViGEm/HidCerberus");
	I18N.NOTEPAD_UNSAVED									= WCHARI(L"*Unsaved");

	I18N.STATE_INSTALL										= WCHARI(L"Install");
	I18N.STATE_UNINSTALL									= WCHARI(L"Uninstall");
	I18N.STATE_VJOY_INSTALL									= WCHARI(L"vJoy Inst");
	I18N.STATE_VJOY_UNINSTALL								= WCHARI(L"vJoy Unin");
	I18N.STATE_START										= WCHARI(L"Start");
	I18N.STATE_STOP											= WCHARI(L"Stop");
	I18N.STATE_RESTART										= WCHARI(L"Restart");
	I18N.STATE_ENABLE										= WCHARI(L"Enable");
	I18N.STATE_VJOY_ENABLE									= WCHARI(L"vJoy En.");
	I18N.STATE_DISABLE										= WCHARI(L"Disable");
	I18N.STATE_WAITING										= WCHARI(L"Waiting...");

	I18N.FILE												= WCHARI(L"File(&F)");
	I18N.EXIT												= WCHARI(L"Exit");
	I18N.HELP												= WCHARI(L"Help(&H)");
	I18N.ABOUT												= WCHARI(L"About");

	I18N.MENU_SEE_VIEW2										= WCHARI(L"Clone to view2");
	I18N.MENU_TO_MODE_0										= WCHARI(L"Set to Always");
	I18N.MENU_TO_MODE_1										= WCHARI(L"Set to mode 1");
	I18N.MENU_TO_MODE_2										= WCHARI(L"Set to mode 2");
	I18N.MENU_TO_MODE_3										= WCHARI(L"Set to mode 3");
	I18N.MENU_TO_MODE_4										= WCHARI(L"Set to mode 4");
	I18N.MENU_TO_MODE_5										= WCHARI(L"Set to mode 5");
	I18N.MENU_TO_MODE_6										= WCHARI(L"Set to mode 6");
	I18N.MENU_TO_MODE_7										= WCHARI(L"Set to mode 7");
	I18N.MENU_TO_MODE_8										= WCHARI(L"Set to mode 8");

	I18N.CLONE_TO_MODE_0                                    = WCHARI(L"Clone 1st tab");
	I18N.CLONE_TO_MODE_1                                    = WCHARI(L"Clone tab 1");
	I18N.CLONE_TO_MODE_2                                    = WCHARI(L"Clone tab 2");
	I18N.CLONE_TO_MODE_3                                    = WCHARI(L"Clone tab 3");
	I18N.CLONE_TO_MODE_4                                    = WCHARI(L"Clone tab 4");
	I18N.CLONE_TO_MODE_5                                    = WCHARI(L"Clone tab 5");
	I18N.CLONE_TO_MODE_6                                    = WCHARI(L"Clone tab 6");
	I18N.CLONE_TO_MODE_7                                    = WCHARI(L"Clone tab 7");
	I18N.CLONE_TO_MODE_8                                    = WCHARI(L"Clone tab 8");

	I18N.MENU_ADD											= WCHARI(L"Add");
	I18N.MENU_EDIT											= WCHARI(L"Edit");
	I18N.MENU_DEL											= WCHARI(L"Delete");
	I18N.MENU_COPY											= WCHARI(L"Copy");
	I18N.MENU_SEPARATOR										= WCHARI(L"Separator");
	I18N.MENU_MOVE_TO_0										= WCHARI(L"Move to 0");
	I18N.MENU_MOVE_TO_1										= WCHARI(L"Move to 1");
	I18N.MENU_MOVE_TO_2										= WCHARI(L"Move to 2");
	I18N.MENU_MOVE_TO_3										= WCHARI(L"Move to 3");
	I18N.MENU_MOVE_TO_4										= WCHARI(L"Move to 4");
	I18N.MENU_MOVE_TO_5										= WCHARI(L"Move to 5");
	I18N.MENU_MOVE_TO_6										= WCHARI(L"Move to 6");
	I18N.MENU_MOVE_TO_7										= WCHARI(L"Move to 7");
	I18N.MENU_MOVE_TO_8										= WCHARI(L"Move to 8");
	I18N.MENU_SWAP_VIEW										= WCHARI(L"Swap view");
	I18N.MENU_ADD_NOTICE									= WCHARI(L"Add notice");

	I18N.MENU_SEPARATORN									= WCHARI(L"    —————————");
	I18N.MENU_WEB_PDF_PORTRAIT								= WCHARI(L"Print to PDF Portrait");
	I18N.MENU_WEB_PDF_LANDSCAPE								= WCHARI(L"Print to PDF Landscape");
	I18N.MENU_WEB_SCREENSHOT								= WCHARI(L"Save Screenshot");

	I18N.MENU_WEB_TOPMOST									= WCHARI(L"Toggle TopMost");
	I18N.MENU_WEB_VISIBILITY								= WCHARI(L"Toggle Visibility");
	I18N.MENU_WEB_DARK_MODE									= WCHARI(L"Dark mode");
	I18N.MENU_WEB_DARK_MODE_2								= WCHARI(L"Dark mode 2");
	I18N.MENU_WEB_BOUNDS_MODE								= WCHARI(L"Raw/Scale Pixels");
	I18N.MENU_WEB_BLOCK_IMAGES								= WCHARI(L"Toggle Block Images");

	I18N.MENU_WEB_CLOSE_WEBVIEW								= WCHARI(L"Close WebView");
	I18N.MENU_WEB_REINIT									= WCHARI(L"Create WebView");
	I18N.MENU_WEB_NEW_WINDOW								= WCHARI(L"Create New Window");
	I18N.MENU_WEB_NEW_THREAD								= WCHARI(L"Create New Thread");
	I18N.MENU_WEB_CLEAR_CACHE								= WCHARI(L"Clear cache");
	I18N.MENU_WEB_CLEAR_COOKIES								= WCHARI(L"Clear cookies");
	I18N.MENU_WEB_DELETE_DATAFOLDER							= WCHARI(L"Delete UserData Folder");

	I18N.MENU_WEB_INJECT_SCRIPT								= WCHARI(L"Inject Script");
	I18N.MENU_WEB_INITIALIZE_SCRIPT							= WCHARI(L"Add Initialize Script");
	I18N.MENU_WEB_USE_DEFERRED_SCRIPT						= WCHARI(L"JavaScript Deferred");
	I18N.MENU_WEB_COMPLETE_DEFERRED							= WCHARI(L"JavaScript Complete");
	I18N.MENU_WEB_POST_MESSAGE_STRING						= WCHARI(L"Post Message String");
	I18N.MENU_WEB_POST_MESSAGE_JSON							= WCHARI(L"Post Message JSON");
	I18N.MENU_WEB_SUBSCRIBE_CDP_EVENT						= WCHARI(L"Subscribe CDP event");
	I18N.MENU_WEB_CALL_CDP_METHOD							= WCHARI(L"Call CDP method");
	I18N.MENU_WEB_COM_OBJECT								= WCHARI(L"Add COM object");

	I18N.MENU_WEB_FLAGS										= WCHARI(L"Flags");
	I18N.MENU_WEB_LANGUAGE									= WCHARI(L"Language");
	I18N.MENU_WEB_USERAGENT									= WCHARI(L"User Agent");
	I18N.MENU_WEB_BLACKLIST									= WCHARI(L"Blacklist");
	I18N.MENU_WEB_TASK_MANAGER								= WCHARI(L"Task Manager");

	I18N.MENU_WEB_FAV_0										= WCHARI(L"Home");
	I18N.MENU_WEB_FAV_1										= WCHARI(L"Favorite 1");
	I18N.MENU_WEB_FAV_2										= WCHARI(L"Favorite 2");
	I18N.MENU_WEB_FAV_3										= WCHARI(L"Favorite 3");
	I18N.MENU_WEB_FAV_4										= WCHARI(L"Favorite 4");
	I18N.MENU_WEB_FAV_5										= WCHARI(L"Favorite 5");
	I18N.MENU_WEB_FAV_6										= WCHARI(L"Favorite 6");
	I18N.MENU_WEB_FAV_7										= WCHARI(L"Favorite 7");
	I18N.MENU_WEB_FAV_8										= WCHARI(L"Favorite 8");
	I18N.MENU_WEB_FAV_9										= WCHARI(L"Favorite 9");
	
	I18N.HELP_DINPUT_1										= I18N.Button_L3;
	I18N.HELP_DINPUT_P1										= WCHARI(L"DPAD1> ←↑→↓");
	I18N.HELP_DINPUT_P2										= WCHARI(L"DPAD2");
	I18N.HELP_DINPUT_P3										= WCHARI(L"DPAD3");
	I18N.HELP_DINPUT_P4										= WCHARI(L"DPAD4");
	I18N.HELP_DINPUT_6										= I18N.Button_SHARE;
	I18N.HELP_DINPUT_7										= I18N.Button_OPTIONS;
	I18N.HELP_DINPUT_8										= I18N.Button_SQUARE;
	I18N.HELP_DINPUT_9										= I18N.Button_TRIANGLE;
	I18N.HELP_DINPUT_10										= I18N.Button_CIRCLE;
	I18N.HELP_DINPUT_11										= I18N.Button_CROSS;
	I18N.HELP_DINPUT_12										= I18N.Button_R3;
	I18N.HELP_DINPUT_13										= I18N.Button_PS;
	I18N.HELP_DINPUT_14										= I18N.Button_TOUCH;
	I18N.HELP_DINPUT_15										= I18N.Button_MUTE;
	I18N.HELP_DINPUT_16										= WCHARI(L"16");
	I18N.HELP_DINPUT_17										= WCHARI(L"17");
	I18N.HELP_DINPUT_18										= WCHARI(L"18");
	I18N.HELP_DINPUT_19										= WCHARI(L"19");
	I18N.HELP_DINPUT_20										= WCHARI(L"20");
	I18N.HELP_DINPUT_21										= WCHARI(L"21");
	I18N.HELP_DINPUT_22										= WCHARI(L"22");
	I18N.HELP_DINPUT_23										= WCHARI(L"23");
	I18N.HELP_DINPUT_24										= WCHARI(L"24");
	I18N.HELP_DINPUT_25										= WCHARI(L"25");
	I18N.HELP_DINPUT_26										= WCHARI(L"26");
	I18N.HELP_DINPUT_27										= WCHARI(L"27");
	I18N.HELP_DINPUT_28										= WCHARI(L"28");
	I18N.HELP_DINPUT_29										= WCHARI(L"29");
	I18N.HELP_DINPUT_30										= WCHARI(L"30");
	I18N.HELP_DINPUT_31										= WCHARI(L"31");
	I18N.HELP_DINPUT_32										= WCHARI(L"32");
	I18N.HELP_DINPUT_L1										= I18N.Button_L1;
	I18N.HELP_DINPUT_R1										= I18N.Button_R1;
	I18N.HELP_DINPUT_L2										= I18N.Button_L2;
	I18N.HELP_DINPUT_R2										= I18N.Button_R2;
	I18N.HELP_DINPUT_LT										= I18N.Button_L2_TRIGGER;
	I18N.HELP_DINPUT_RT										= I18N.Button_R2_TRIGGER;
	I18N.HELP_DINPUT_LX										= I18N.Button_LX;
	I18N.HELP_DINPUT_LY										= I18N.Button_LY;
	I18N.HELP_DINPUT_RX										= I18N.Button_RX;
	I18N.HELP_DINPUT_RY										= I18N.Button_RY;
	I18N.HELP_DINPUT_S0										= I18N.Button_SLO;
	I18N.HELP_DINPUT_S1										= I18N.Button_SL1;

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
None, Source, DS or DirectInput\n\
Simple, Sisaxis(S)\n\
Double, Mouse and Keyboard (K)\n\
Triple, Destination (D), even if vJoy not used");
	I18N.HELP_DESTINATION									= WCHARI(L"Destination selection:\n\
None, vJoy\n\
Simple, Mouse actions, Magnifier (M)\n\
Double, Sound, modes, window, stats and time actions (S)\n\
Triple, Axis movements (A)\n\
quadruple, Modules actions, Web, Notepad, etc. (W)");
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
	we use release value of first source instead of 0xFFFF\n\
	if timestamp is still in use and we have released sources\n\
	second source too if first is not pushed and OrXor1\n\
	third source too if first is not pushed, second isn't in used and OrXor1 + OrXor2");
	I18N.HELP_PAUSE											= WCHARI(L"Pause modificator:\n\
simple, Pause1:\n\
	Pause this mapping while a 'not1' condition\n\
double, Pause2:\n\
	Pause this mapping while a 'not2' condition\n\
triple, Pause:\n\
	Pause this mapping while a 'not' condition\n\
otherwise :\n\
	if 'not' is a simple, and 'not' button is pressed, the mapping is interrupted\n\
	if 'not' is a double, and 'not' button is pressed, the mapping still continue");
	I18N.HELP_TRANSITIVITY									= WCHARI(L"Transitivity modificator:\n\
Brings different behaviors and transition possibilities while mode changed\n\
simple : Conduct\n\
	If the source is already pushed when entering the new mode,\n\
	the mapping is triggered\n\
double : Complete\n\
	You can release and trigger again in new mode\n\
	if it was already active before changing mode\n\
triple : Limited\n\
	Action continue while changing mode,\n\
	but you can't trigger again if release\n\
quadruple : Retroactive\n\
	Instead of continuation, button is released,\n\
	but triggered again if still pushed when initial mode is back\n\
quintuple : One time back\n\
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
	the threshold is removed on, respectively, the LX, LY, RX, RY axes of source");
	I18N.HELP_START											= WCHARI(L"Start Time stamp:\n\
Enter start (if not as soon as)\n\
If you enter an odd number,\n\
	0 - 9 milliseconds will be added,\n\
	different each time");
	I18N.HELP_END											= WCHARI(L"End Time stamp:\n\
Enter end (if not when release)\n\
If you enter an odd number,\n\
	0 - 9 milliseconds will be added,\n\
	different each time\n\
Or enter ‘return to’ time");
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
Mouse action\n\
	Abscissa of first point\n\
Raid/Grid\n\
	Abscissa of upper-left point\n\
Magnifier\n\
	x=y=0	at center\n\
	x=1 y=0	at cursor position\n\
	x=0 y=1	at actual point\n\
	x=y=1	at given point (w,h)");
	I18N.HELP_GRID_Y										= WCHARI(L"y:\n\
Mouse action\n\
	Ordinate of first point\n\
Raid/Grid\n\
	Ordinate of upper-left point\n\
Magnifier\n\
	x=y=0	at center\n\
	x=1 y=0	at cursor position\n\
	x=0 y=1	at actual point\n\
	x=y=1	at given point (w,h)");
	I18N.HELP_GRID_W										= WCHARI(L"w:\n\
Mouse action\n\
	Abscissa of second point\n\
Raid/Grid\n\
	Width of the grid\n\
Magnifier\n\
	if x=y=1, Abscissa to zoom at");
	I18N.HELP_GRID_H										= WCHARI(L"h:\n\
Mouse action\n\
	Ordinate of second point\n\
Raid/Grid\n\
	Height of the grid\n\
Magnifier\n\
	if x=y=1, Ordinate to zoom at");
	I18N.HELP_GRID_NW										= WCHARI(L"nw:\n\
Mouse action\n\
	Abscissa of third point\n\
Raid/Grid\n\
	Number of horizontal subdivisions\n\
Magnifier\n\
	Zoom factor (1-4096)");
	I18N.HELP_GRID_NH										= WCHARI(L"nh:\n\
Mouse action\n\
	Ordinate of third point\n\
Raid/Grid\n\
	Number of horizontal subdivisions\n\
Magnifier\n\
	frational part of zoom level");
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

	I18N.HELP_SETTINGS_MOUSE								= WCHARI(L"Mouse acquisition:\n\
via usual Virual keys\n\
double, by activating mouse DirectInput\n\
	to have buttons 6,7 and 8 too");

	I18N.HELP_WEB_MENU										= WCHARI(L"Web menu");
	I18N.HELP_WEB_CLOSE										= WCHARI(L"Left click: quit web module\nRight click: close actual tab");
	I18N.HELP_WEB_FAVORITES									= WCHARI(L"Left click: go to favorite\nRight click: set favorite");
	I18N.HELP_WEB_HOME										= WCHARI(L"Home");
	I18N.HELP_WEB_BACK										= WCHARI(L"Back");
	I18N.HELP_WEB_FORWARD									= WCHARI(L"Forward");
	I18N.HELP_WEB_REFRESH									= WCHARI(L"Refresh");
	I18N.HELP_WEB_GO										= WCHARI(L"Go");
	I18N.HELP_WEB_STOP										= WCHARI(L"Stop");
	I18N.HELP_WEB_AUTOREFRESH								= WCHARI(L"Autorefresh");
	I18N.HELP_WEB_ZOOM_MINUS								= WCHARI(L"Left click: Zoom minus\nRight click: Return to default");
	I18N.HELP_WEB_ZOOM_PLUS									= WCHARI(L"Left click: Zoom plus\nRight click: Set default");
	break;
	}
	}
}

void FreeLanguage()
{
	if (I18N.ds_skip_controller == 0)
		return;
	delete[] I18N.EMPTY;
	delete[] I18N.WHICH;
	delete[] I18N.NONE;
	delete[] I18N.DS2VJOY;
	delete[] I18N.APP_TITLE;
	delete[] I18N.Fatal_Error1;
	delete[] I18N.Fatal_Error2;
	delete[] I18N.Status_Wait;
	delete[] I18N.Status_Active;
	delete[] I18N.Status_Charge;
	delete[] I18N.Status_Empty;
	delete[] I18N.Status_Low;
	delete[] I18N.Status_Medium;
	delete[] I18N.Status_Full;
	delete[] I18N.MBOX_Delete;
	delete[] I18N.MBOX_ErrorWhileSaving;
	delete[] I18N.MBOX_ErrTitle;
	delete[] I18N.MBOX_NoButtonSelected;

	delete[] I18N.Magnifier_Magnification_Active;
	delete[] I18N.Settings_Registry_Added;
	delete[] I18N.Settings_Registry_Removed;
	delete[] I18N.Settings_Change_Settings;
	delete[] I18N.TaskTray_AppNotFound;
	delete[] I18N.TaskTray_ProfileChanged;

	delete[] I18N.ds_notforuse;
	delete[] I18N.ds_wait;
	delete[] I18N.ds_skip_controller;
	delete[] I18N.ds_connect_controller;
	delete[] I18N.ds_connection_started;
	delete[] I18N.ds_disconnect_controller;
	delete[] I18N.ds_failed_parse;
	delete[] I18N.ds_failed_recv;
	delete[] I18N.ds_failed_send_cmd;
	delete[] I18N.ds_failed_thread;
	delete[] I18N.ds_bt_crc;
	delete[] I18N.ds_bt_size;
	delete[] I18N.ds_version;
	delete[] I18N.ds_firmware_fail;

	delete[] I18N.di_notforuse;
	delete[] I18N.di_wait;
	delete[] I18N.di_failed_acquire;
	delete[] I18N.di_failed_thread;
	delete[] I18N.di_client_connected;
	delete[] I18N.di_client_removed;
	delete[] I18N.di_target_plugin_failed;
	delete[] I18N.di_pad_acquired;
	delete[] I18N.di_pad_unacquired;
	delete[] I18N.di_busy;

	delete[] I18N.xi_notforuse;
	delete[] I18N.xi_wait;
	delete[] I18N.xi_failed_thread;
	delete[] I18N.xi_pad_acquired;
	delete[] I18N.xi_busy;

	delete[] I18N.vJoy_notforuse;
	delete[] I18N.vJoy_wait;
	delete[] I18N.vJoy_initialization_failed;
	delete[] I18N.vJoy_failed_acquire;
	delete[] I18N.vJoy_acquired;
	delete[] I18N.vJoy_busy;
	delete[] I18N.vJoy_failed_update;
	delete[] I18N.vJoy_version;

	delete[] I18N.XOutput_memory_allocating_error;
	delete[] I18N.XOutput_bus_connection_failed;
	delete[] I18N.XOutput_target_plugin_failed;
	delete[] I18N.XOutput_client_connected;
	delete[] I18N.XOutput_client_removed;
	delete[] I18N.XOutput_pad_added;
	delete[] I18N.XOutput_pad_removed;
	
	delete[] I18N.LogSatusString;
	delete[] I18N.SettingsSatusString;
	delete[] I18N.MappingButtonsString;
	delete[] I18N.XOutputButtonsString;

	delete[] I18N.Profile_1;
	delete[] I18N.Profile_2;
	delete[] I18N.Profile_3;
	delete[] I18N.MappingPaused_On;
	delete[] I18N.MappingPaused_Off;
	delete[] I18N.RapidFirePaused_On;
	delete[] I18N.RapidFirePaused_Off;
	delete[] I18N.KeymapPaused_On;
	delete[] I18N.KeymapPaused_Off;
	delete[] I18N.vJoyPaused_On;
	delete[] I18N.vJoyPaused_Off;
	delete[] I18N.XOutputPaused_On;
	delete[] I18N.XOutputPaused_Off;
	delete[] I18N.GuardianPaused_On;
	delete[] I18N.GuardianPaused_Off;

	delete[] I18N.XOutput_vJoy_Install_tittle;
	delete[] I18N.XOutput_vJoy_Install_text;
	delete[] I18N.XOutput_vJoy_Uninstall_tittle;
	delete[] I18N.XOutput_vJoy_Uninstall_text;
	delete[] I18N.XOutput_driver_instalation_failed;
	delete[] I18N.XOutput_driver_uninstalled;
	delete[] I18N.XOutput_driver_uninstalation_failed;
	delete[] I18N.vJoy_driver_installed;
	delete[] I18N.vJoy_driver_instalation_failed;
	delete[] I18N.vJoy_driver_uninstalled;
	delete[] I18N.vJoy_driver_uninstalation_failed;

	delete[] I18N.Guardian_driver_installed;
	delete[] I18N.Guardian_driver_instalation_failed;
	delete[] I18N.Guardian_driver_uninstalled;
	delete[] I18N.Guardian_driver_uninstalation_failed;
	delete[] I18N.Cerberus_service_installed;
	delete[] I18N.Cerberus_service_instalation_failed;
	delete[] I18N.Cerberus_service_uninstalled;
	delete[] I18N.Cerberus_service_uninstalation_failed;
	delete[] I18N.Guardian_Added_to_Guardian;
	delete[] I18N.Guardian_Removed_from_Guardian;
	
	delete[] I18N.WebView2_Not_Installed_tittle;
	delete[] I18N.WebView2_Not_Installed_text;
	delete[] I18N.WebView2_Installation_failed;
	delete[] I18N.WebView2_downloading_failed;
	delete[] I18N.WebView2_Runtime_Failed_Found;
	delete[] I18N.WebView2_Data_Folder_Failed_Overwrite;
	delete[] I18N.WebView2_Data_Folder_Failed_Access;
	delete[] I18N.WebView2_Runtime_Failed_Start;
	delete[] I18N.WebView2_Create_Environment_Failed;
	delete[] I18N.WebView2_Create_Webview_Failed;
	delete[] I18N.WebView2_Cleanup_Data_Folder;
	delete[] I18N.WebView2_New_version;
	delete[] I18N.WebView2_PDF_Tittle;
	delete[] I18N.WebView2_PDF_Progress;
	delete[] I18N.WebView2_PDF_Closing;
	delete[] I18N.WebView2_PDF_Succeeded;
	delete[] I18N.WebView2_PDF_Failed;
	delete[] I18N.WebView2_Screenshot_Tittle;
	delete[] I18N.WebView2_Preview_Captured;
	delete[] I18N.WebView2_Capture_Failed;
	delete[] I18N.WebView2_Inject_Script_Tittle;
	delete[] I18N.WebView2_Inject_Script_Failed;
	delete[] I18N.WebView2_CDP_Result;
	delete[] I18N.WebView2_AddHostObjectToScript_Failed;
	delete[] I18N.WebView2_IDispatch_Failed;
	delete[] I18N.WebView2_CoCreateInstance_Failed;
	delete[] I18N.WebView2_Convert_Failed;
	delete[] I18N.Suspend_Failed;

	delete[] I18N.Clone_of_Tab;
	delete[] I18N.TabLog;
	delete[] I18N.TabSettings;
	delete[] I18N.TabMapping;
	delete[] I18N.TabRapidFire;
	delete[] I18N.TabKeymap;
	delete[] I18N.TabXOutput;
	delete[] I18N.TabGuardian;
	delete[] I18N.TabExplorer;
	delete[] I18N.TabLinks;

	delete[] I18N.srceButton;
	delete[] I18N.destButton;
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
	delete[] I18N.Button_L2_TRIGGER;
	delete[] I18N.Button_R2_TRIGGER;
	delete[] I18N.Button_LX_INV;
	delete[] I18N.Button_LY_INV;
	delete[] I18N.Button_RX_INV;
	delete[] I18N.Button_RY_INV;
	delete[] I18N.Button_LX_SNIPER;
	delete[] I18N.Button_LY_SNIPER;
	delete[] I18N.Button_RX_SNIPER;
	delete[] I18N.Button_RY_SNIPER;
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
	delete[] I18N.Button_L2_TRIGGER_33;
	delete[] I18N.Button_R2_TRIGGER_33;
	delete[] I18N.Button_L2_TRIGGER_66;
	delete[] I18N.Button_R2_TRIGGER_66;
	delete[] I18N.Button_L2_TRIGGER_100;
	delete[] I18N.Button_R2_TRIGGER_100;
	delete[] I18N.Button_L1R1;
	delete[] I18N.Button_L2R2;
	delete[] I18N.Button_EMPTY;
	delete[] I18N.Button_MIDDLE;
	delete[] I18N.Button_FULL;
	delete[] I18N.Button_QUARTER1;
	delete[] I18N.Button_QUARTER2;
	delete[] I18N.Button_THIRD1;
	delete[] I18N.Button_THIRD2;
	delete[] I18N.Button_TEN;
	delete[] I18N.Button_TWENTY;
	delete[] I18N.Button_THIRTY;
	delete[] I18N.Button_FORTY;
	delete[] I18N.Button_SIXTY;
	delete[] I18N.Button_SEVENTY;
	delete[] I18N.Button_EIGHTY;
	delete[] I18N.Button_NINETY;
	delete[] I18N.Button_BATTERY;
	delete[] I18N.Button_BATTERY0;
	delete[] I18N.Button_BATTERY1;
	delete[] I18N.Button_BATTERY2;
	delete[] I18N.Button_BATTERY3;
	delete[] I18N.Button_BATTERY4;
	delete[] I18N.Button_BATTERY5;
	delete[] I18N.Button_BATTERY6;
	delete[] I18N.Button_BATTERY7;
	delete[] I18N.Button_BATTERY8;
	delete[] I18N.Button_BATTERY9;
	delete[] I18N.Button_USB;
	delete[] I18N.Button_EARS;
	delete[] I18N.Button_MIC;
	delete[] I18N.Button_BT;
	delete[] I18N.Button_FINGER;
	delete[] I18N.Button_FINGERS;
	delete[] I18N.Button_DS_SELECTED;
	delete[] I18N.Button_DS4_SELECTED;
	delete[] I18N.Button_DS5_SELECTED;
	delete[] I18N.Button_DI_SELECTED;
	delete[] I18N.Button_XI_SELECTED;
	delete[] I18N.Button_DS_ACTIVE;
	delete[] I18N.Button_DS4_ACTIVE;
	delete[] I18N.Button_DS5_ACTIVE;
	delete[] I18N.Button_DI_ACTIVE;
	delete[] I18N.Button_KBD_ACTIVE;
	delete[] I18N.Button_MSE_ACTIVE;
	delete[] I18N.Button_MSE_DI_ACTIVE;
	delete[] I18N.Button_INACTIVITY_5MN;
	delete[] I18N.Button_INACTIVITY_10MN;
	delete[] I18N.Button_INACTIVITY_15MN;
	delete[] I18N.Button_INACTIVITY_30MN;
	delete[] I18N.Button_NO_MOVEMENT_5MN;
	delete[] I18N.Button_NO_MOVEMENT_10MN;
	delete[] I18N.Button_NO_MOVEMENT_15MN;
	delete[] I18N.Button_NO_MOVEMENT_30MN;
	delete[] I18N.Button_SLO;
	delete[] I18N.Button_SLO_INV;
	delete[] I18N.Button_SLO_SNIPER;
	delete[] I18N.Button_SL1;
	delete[] I18N.Button_SL1_INV;
	delete[] I18N.Button_SL1_SNIPER;
	delete[] I18N.Button_DI_X;
	delete[] I18N.Button_DI_X_INV;
	delete[] I18N.Button_DI_X_TRIGGER;
	delete[] I18N.Button_DI_Y;
	delete[] I18N.Button_DI_Y_INV;
	delete[] I18N.Button_DI_Y_TRIGGER;
	delete[] I18N.Button_DI_Z;
	delete[] I18N.Button_DI_Z_INV;
	delete[] I18N.Button_DI_Z_TRIGGER;
	delete[] I18N.Button_DI_RX;
	delete[] I18N.Button_DI_RX_INV;
	delete[] I18N.Button_DI_RX_TRIGGER;
	delete[] I18N.Button_DI_RY;
	delete[] I18N.Button_DI_RY_INV;
	delete[] I18N.Button_DI_RY_TRIGGER;
	delete[] I18N.Button_DI_RZ;
	delete[] I18N.Button_DI_RZ_INV;
	delete[] I18N.Button_DI_RZ_TRIGGER;
	delete[] I18N.Button_DI_SL0;
	delete[] I18N.Button_DI_SL0_INV;
	delete[] I18N.Button_DI_SL0_TRIGGER;
	delete[] I18N.Button_DI_SL1;
	delete[] I18N.Button_DI_SL1_INV;
	delete[] I18N.Button_DI_SL1_TRIGGER;
	delete[] I18N.Button_DPAD2_LEFT;
	delete[] I18N.Button_DPAD2_UP;
	delete[] I18N.Button_DPAD2_RIGHT;
	delete[] I18N.Button_DPAD2_DOWN;
	delete[] I18N.Button_DPAD3_LEFT;
	delete[] I18N.Button_DPAD3_UP;
	delete[] I18N.Button_DPAD3_RIGHT;
	delete[] I18N.Button_DPAD3_DOWN;
	delete[] I18N.Button_DPAD4_LEFT;
	delete[] I18N.Button_DPAD4_UP;
	delete[] I18N.Button_DPAD4_RIGHT;
	delete[] I18N.Button_DPAD4_DOWN;

	delete[] I18N.Button_STANCE;
	delete[] I18N.Button_ZONE;
	delete[] I18N.Button_STANCE1;
	delete[] I18N.Button_STANCE2;
	delete[] I18N.Button_STANCE3;
	delete[] I18N.Button_STANCE4;
	delete[] I18N.Button_STANCE5;
	delete[] I18N.Button_ZONE1;
	delete[] I18N.Button_ZONE2;
	delete[] I18N.Button_ZONE3;
	delete[] I18N.Button_ZONE4;
	delete[] I18N.Button_ZONE5;
	delete[] I18N.Button_ROLL;
	delete[] I18N.Button_ROLL_INV;
	delete[] I18N.Button_ROLL_TRIGGER;
	delete[] I18N.Button_ROLL_CENTER;
	delete[] I18N.Button_LEFT1;
	delete[] I18N.Button_LEFT2;
	delete[] I18N.Button_LEFT3;
	delete[] I18N.Button_LEFT4;
	delete[] I18N.Button_LEFT5;
	delete[] I18N.Button_LEFT6;
	delete[] I18N.Button_LEFT7;
	delete[] I18N.Button_RIGHT;
	delete[] I18N.Button_RIGHT1;
	delete[] I18N.Button_RIGHT2;
	delete[] I18N.Button_RIGHT3;
	delete[] I18N.Button_RIGHT4;
	delete[] I18N.Button_RIGHT5;
	delete[] I18N.Button_RIGHT6;
	delete[] I18N.Button_RIGHT7;
	delete[] I18N.Button_YAW;
	delete[] I18N.Button_YAW_INV;
	delete[] I18N.Button_YAW_TRIGGER;
	delete[] I18N.Button_YAW_CENTER;
	delete[] I18N.Button_ANTI1;
	delete[] I18N.Button_ANTI2;
	delete[] I18N.Button_ANTI3;
	delete[] I18N.Button_ANTI4;
	delete[] I18N.Button_ANTI5;
	delete[] I18N.Button_ANTI6;
	delete[] I18N.Button_ANTI7;
	delete[] I18N.Button_CLOCK;
	delete[] I18N.Button_CLOCK1;
	delete[] I18N.Button_CLOCK2;
	delete[] I18N.Button_CLOCK3;
	delete[] I18N.Button_CLOCK4;
	delete[] I18N.Button_CLOCK5;
	delete[] I18N.Button_CLOCK6;
	delete[] I18N.Button_CLOCK7;
	delete[] I18N.Button_PITCH;
	delete[] I18N.Button_PITCH_INV;
	delete[] I18N.Button_PITCH_TRIGGER;
	delete[] I18N.Button_PITCH_CENTER;
	delete[] I18N.Button_REAR1;
	delete[] I18N.Button_REAR2;
	delete[] I18N.Button_REAR3;
	delete[] I18N.Button_REAR4;
	delete[] I18N.Button_REAR5;
	delete[] I18N.Button_REAR6;
	delete[] I18N.Button_REAR7;
	delete[] I18N.Button_FORE;
	delete[] I18N.Button_FORE1;
	delete[] I18N.Button_FORE2;
	delete[] I18N.Button_FORE3;
	delete[] I18N.Button_FORE4;
	delete[] I18N.Button_FORE5;
	delete[] I18N.Button_FORE6;
	delete[] I18N.Button_FORE7;
	delete[] I18N.Button_SIDEWARD;
	delete[] I18N.Button_SIDEWARD_INV;
	delete[] I18N.Button_SIDEWARD_TRIGGER;
	delete[] I18N.Button_SIDEWARD_CENTER;
	delete[] I18N.Button_WEST1;
	delete[] I18N.Button_WEST2;
	delete[] I18N.Button_WEST3;
	delete[] I18N.Button_WEST4;
	delete[] I18N.Button_WEST5;
	delete[] I18N.Button_WEST6;
	delete[] I18N.Button_EAST;
	delete[] I18N.Button_EAST1;
	delete[] I18N.Button_EAST2;
	delete[] I18N.Button_EAST3;
	delete[] I18N.Button_EAST4;
	delete[] I18N.Button_EAST5;
	delete[] I18N.Button_EAST6;
	delete[] I18N.Button_TOWARD;
	delete[] I18N.Button_TOWARD_INV;
	delete[] I18N.Button_TOWARD_TRIGGER;
	delete[] I18N.Button_TOWARD_CENTER;
	delete[] I18N.Button_BACKWARD1;
	delete[] I18N.Button_BACKWARD2;
	delete[] I18N.Button_BACKWARD3;
	delete[] I18N.Button_BACKWARD4;
	delete[] I18N.Button_BACKWARD5;
	delete[] I18N.Button_BACKWARD6;
	delete[] I18N.Button_FORWARD;
	delete[] I18N.Button_FORWARD1;
	delete[] I18N.Button_FORWARD2;
	delete[] I18N.Button_FORWARD3;
	delete[] I18N.Button_FORWARD4;
	delete[] I18N.Button_FORWARD5;
	delete[] I18N.Button_FORWARD6;
	delete[] I18N.Button_LEVEL;
	delete[] I18N.Button_LEVEL_INV;
	delete[] I18N.Button_LEVEL_TRIGGER;
	delete[] I18N.Button_LEVEL_CENTER;
	delete[] I18N.Button_SOUTH1;
	delete[] I18N.Button_SOUTH2;
	delete[] I18N.Button_SOUTH3;
	delete[] I18N.Button_SOUTH4;
	delete[] I18N.Button_SOUTH5;
	delete[] I18N.Button_SOUTH6;
	delete[] I18N.Button_NORTH;
	delete[] I18N.Button_NORTH1;
	delete[] I18N.Button_NORTH2;
	delete[] I18N.Button_NORTH3;
	delete[] I18N.Button_NORTH4;
	delete[] I18N.Button_NORTH5;
	delete[] I18N.Button_NORTH6;
	delete[] I18N.Button_WHEEL;
	delete[] I18N.Button_QUARTER;
	delete[] I18N.Button_REAR;
	delete[] I18N.Button_GEAR_1;
	delete[] I18N.Button_GEAR_2;
	delete[] I18N.Button_GEAR_3;
	delete[] I18N.Button_GEAR_4;
	delete[] I18N.Button_GEAR_5;

	delete[] I18N.Button_MOUSE_AXEX;
	delete[] I18N.Button_MOUSE_AXEY;
	delete[] I18N.Button_MOUSE_SCROLL_UP;
	delete[] I18N.Button_MOUSE_SCROLL_DOWN;
	delete[] I18N.Button_MOUSE_SCROLL_UP_HIGH;
	delete[] I18N.Button_MOUSE_SCROLL_DOWN_HIGH;
	delete[] I18N.Button_MOUSE_LEFT;
	delete[] I18N.Button_MOUSE_RIGHT;
	delete[] I18N.Button_MOUSE_UP;
	delete[] I18N.Button_MOUSE_DOWN;
	delete[] I18N.Button_MOUSE_LBUTTON;
	delete[] I18N.Button_MOUSE_MBUTTON;
	delete[] I18N.Button_MOUSE_RBUTTON;
	delete[] I18N.Button_MOUSE_XBUTTON1;
	delete[] I18N.Button_MOUSE_XBUTTON2;
	delete[] I18N.Button_MOUSE_BUTTON6;
	delete[] I18N.Button_MOUSE_BUTTON7;
	delete[] I18N.Button_MOUSE_BUTTON8;
	delete[] I18N.Button_KID_F1;
	delete[] I18N.Button_KID_F2;
	delete[] I18N.Button_KID_F3;
	delete[] I18N.Button_KID_F4;
	delete[] I18N.Button_KID_F5;
	delete[] I18N.Button_KID_F6;
	delete[] I18N.Button_KID_F7;
	delete[] I18N.Button_KID_F8;
	delete[] I18N.Button_KID_F9;
	delete[] I18N.Button_KID_F10;
	delete[] I18N.Button_KID_F11;
	delete[] I18N.Button_KID_F12;
	delete[] I18N.Button_KID_0;
	delete[] I18N.Button_KID_1;
	delete[] I18N.Button_KID_2;
	delete[] I18N.Button_KID_3;
	delete[] I18N.Button_KID_4;
	delete[] I18N.Button_KID_5;
	delete[] I18N.Button_KID_6;
	delete[] I18N.Button_KID_7;
	delete[] I18N.Button_KID_8;
	delete[] I18N.Button_KID_9;
	delete[] I18N.Button_KID_OEM_MINUS;
	delete[] I18N.Button_KID_OEM_PLUS;
	delete[] I18N.Button_KID_OEM_1;
	delete[] I18N.Button_KID_OEM_2;
	delete[] I18N.Button_KID_OEM_3;
	delete[] I18N.Button_KID_OEM_4;
	delete[] I18N.Button_KID_OEM_5;
	delete[] I18N.Button_KID_OEM_6;
	delete[] I18N.Button_KID_OEM_7;
	delete[] I18N.Button_KID_OEM_8;
	delete[] I18N.Button_KID_OEM_102;
	delete[] I18N.Button_KID_OEM_COMMA;
	delete[] I18N.Button_KID_OEM_PERIOD;
	delete[] I18N.Button_KID_A;
	delete[] I18N.Button_KID_B;
	delete[] I18N.Button_KID_C;
	delete[] I18N.Button_KID_D;
	delete[] I18N.Button_KID_E;
	delete[] I18N.Button_KID_F;
	delete[] I18N.Button_KID_G;
	delete[] I18N.Button_KID_H;
	delete[] I18N.Button_KID_I;
	delete[] I18N.Button_KID_J;
	delete[] I18N.Button_KID_K;
	delete[] I18N.Button_KID_L;
	delete[] I18N.Button_KID_M;
	delete[] I18N.Button_KID_N;
	delete[] I18N.Button_KID_O;
	delete[] I18N.Button_KID_P;
	delete[] I18N.Button_KID_Q;
	delete[] I18N.Button_KID_R;
	delete[] I18N.Button_KID_S;
	delete[] I18N.Button_KID_T;
	delete[] I18N.Button_KID_U;
	delete[] I18N.Button_KID_V;
	delete[] I18N.Button_KID_W;
	delete[] I18N.Button_KID_X;
	delete[] I18N.Button_KID_Y;
	delete[] I18N.Button_KID_Z;
	delete[] I18N.Button_KID_ESCAPE;
	delete[] I18N.Button_KID_TAB;
	delete[] I18N.Button_KID_RETURN;
	delete[] I18N.Button_KID_SPACE;
	delete[] I18N.Button_KID_BACK;
	delete[] I18N.Button_KID_DELETE;
	delete[] I18N.Button_KID_INSERT;
	delete[] I18N.Button_KID_NUMLOCK;
	delete[] I18N.Button_KID_LSHIFT;
	delete[] I18N.Button_KID_RSHIFT;
	delete[] I18N.Button_KID_LCONTROL;
	delete[] I18N.Button_KID_RCONTROL;
	delete[] I18N.Button_KID_LWIN;
	delete[] I18N.Button_KID_RWIN;
	delete[] I18N.Button_KID_LMENU;
	delete[] I18N.Button_KID_RMENU;
	delete[] I18N.Button_KID_LEFT;
	delete[] I18N.Button_KID_UP;
	delete[] I18N.Button_KID_RIGHT;
	delete[] I18N.Button_KID_DOWN;
	delete[] I18N.Button_KID_PRIOR;
	delete[] I18N.Button_KID_NEXT;
	delete[] I18N.Button_KID_END;
	delete[] I18N.Button_KID_HOME;
	delete[] I18N.Button_KID_NUMPAD0;
	delete[] I18N.Button_KID_NUMPAD1;
	delete[] I18N.Button_KID_NUMPAD2;
	delete[] I18N.Button_KID_NUMPAD3;
	delete[] I18N.Button_KID_NUMPAD4;
	delete[] I18N.Button_KID_NUMPAD5;
	delete[] I18N.Button_KID_NUMPAD6;
	delete[] I18N.Button_KID_NUMPAD7;
	delete[] I18N.Button_KID_NUMPAD8;
	delete[] I18N.Button_KID_NUMPAD9;
	delete[] I18N.Button_KID_DIVIDE;
	delete[] I18N.Button_KID_MULTIPLY;
	delete[] I18N.Button_KID_SUBTRACT;
	delete[] I18N.Button_KID_ADD;
	delete[] I18N.Button_KID_SEPARATOR;
	delete[] I18N.Button_KID_DECIMAL;

	delete[] I18N.Dest_X;
	delete[] I18N.Dest_Y;
	delete[] I18N.Dest_Z;
	delete[] I18N.Dest_RX;
	delete[] I18N.Dest_RY;
	delete[] I18N.Dest_RZ;
	delete[] I18N.Dest_SL0;
	delete[] I18N.Dest_SL1;
	delete[] I18N.Dest_XTR;
	delete[] I18N.Dest_YTR;
	delete[] I18N.Dest_ZTR;
	delete[] I18N.Dest_RXTR;
	delete[] I18N.Dest_RYTR;
	delete[] I18N.Dest_RZTR;
	delete[] I18N.Dest_SL0TR;
	delete[] I18N.Dest_SL1TR;
	delete[] I18N.Dest_XAXTOTR;
	delete[] I18N.Dest_YAXTOTR;
	delete[] I18N.Dest_ZAXTOTR;
	delete[] I18N.Dest_RXAXTOTR;
	delete[] I18N.Dest_RYAXTOTR;
	delete[] I18N.Dest_RZAXTOTR;
	delete[] I18N.Dest_SL0AXTOTR;
	delete[] I18N.Dest_SL1AXTOTR;
	delete[] I18N.Dest_XINV;
	delete[] I18N.Dest_YINV;
	delete[] I18N.Dest_ZINV;
	delete[] I18N.Dest_RXINV;
	delete[] I18N.Dest_RYINV;
	delete[] I18N.Dest_RZINV;
	delete[] I18N.Dest_SL0INV;
	delete[] I18N.Dest_SL1INV;
	delete[] I18N.Dest_XTRINV;
	delete[] I18N.Dest_YTRINV;
	delete[] I18N.Dest_ZTRINV;
	delete[] I18N.Dest_RXTRINV;
	delete[] I18N.Dest_RYTRINV;
	delete[] I18N.Dest_RZTRINV;
	delete[] I18N.Dest_SL0TRINV;
	delete[] I18N.Dest_SL1TRINV;
	delete[] I18N.Dest_XAXTOTRINV;
	delete[] I18N.Dest_YAXTOTRINV;
	delete[] I18N.Dest_ZAXTOTRINV;
	delete[] I18N.Dest_RXAXTOTRINV;
	delete[] I18N.Dest_RYAXTOTRINV;
	delete[] I18N.Dest_RZAXTOTRINV;
	delete[] I18N.Dest_SL0AXTOTRINV;
	delete[] I18N.Dest_SL1AXTOTRINV;
	delete[] I18N.Dest_DPAD1_LEFT;
	delete[] I18N.Dest_DPAD1_UP_LEFT;
	delete[] I18N.Dest_DPAD1_UP;
	delete[] I18N.Dest_DPAD1_UP_RIGHT;
	delete[] I18N.Dest_DPAD1_RIGHT;
	delete[] I18N.Dest_DPAD1_DOWN_RIGHT;
	delete[] I18N.Dest_DPAD1_DOWN;
	delete[] I18N.Dest_DPAD1_DOWN_LEFT;
	delete[] I18N.Dest_DPAD2_LEFT;
	delete[] I18N.Dest_DPAD2_UP_LEFT;
	delete[] I18N.Dest_DPAD2_UP;
	delete[] I18N.Dest_DPAD2_UP_RIGHT;
	delete[] I18N.Dest_DPAD2_RIGHT;
	delete[] I18N.Dest_DPAD2_DOWN_RIGHT;
	delete[] I18N.Dest_DPAD2_DOWN;
	delete[] I18N.Dest_DPAD2_DOWN_LEFT;
	delete[] I18N.Dest_DPAD3_LEFT;
	delete[] I18N.Dest_DPAD3_UP_LEFT;
	delete[] I18N.Dest_DPAD3_UP;
	delete[] I18N.Dest_DPAD3_UP_RIGHT;
	delete[] I18N.Dest_DPAD3_RIGHT;
	delete[] I18N.Dest_DPAD3_DOWN_RIGHT;
	delete[] I18N.Dest_DPAD3_DOWN;
	delete[] I18N.Dest_DPAD3_DOWN_LEFT;
	delete[] I18N.Dest_DPAD4_LEFT;
	delete[] I18N.Dest_DPAD4_UP_LEFT;
	delete[] I18N.Dest_DPAD4_UP;
	delete[] I18N.Dest_DPAD4_UP_RIGHT;
	delete[] I18N.Dest_DPAD4_RIGHT;
	delete[] I18N.Dest_DPAD4_DOWN_RIGHT;
	delete[] I18N.Dest_DPAD4_DOWN;
	delete[] I18N.Dest_DPAD4_DOWN_LEFT;
	delete[] I18N.Dest_WORK1AX;
	delete[] I18N.Dest_WORK2AX;
	delete[] I18N.Dest_WORK3AX;
	delete[] I18N.Dest_WORK4AX;
	delete[] I18N.Dest_WORK5AX;
	delete[] I18N.Dest_WORK6AX;
	delete[] I18N.Dest_WORK7AX;
	delete[] I18N.Dest_WORK8AX;
	delete[] I18N.Dest_WORK1TR;
	delete[] I18N.Dest_WORK2TR;
	delete[] I18N.Dest_WORK3TR;
	delete[] I18N.Dest_WORK4TR;
	delete[] I18N.Dest_WORK5TR;
	delete[] I18N.Dest_WORK6TR;
	delete[] I18N.Dest_WORK7TR;
	delete[] I18N.Dest_WORK8TR;
	delete[] I18N.Dest_BUTTON;
	delete[] I18N.Dest_BUTTON_WORK;

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
	delete[] I18N.MouseAction_MAGNIFY;
	delete[] I18N.MouseAction_MAGNIFY_PLUS;
	delete[] I18N.MouseAction_MAGNIFY_MINUS;
	delete[] I18N.MouseAction_MAGNIFY_RESET;
	delete[] I18N.MouseAction_MAGNIFY_UP;
	delete[] I18N.MouseAction_MAGNIFY_DOWN;
	delete[] I18N.MouseAction_MAGNIFY_LEFT;
	delete[] I18N.MouseAction_MAGNIFY_RIGHT;
	delete[] I18N.MouseAction_MAGNIFY_LOCK;
	delete[] I18N.MouseAction_MAGNIFY_CURSOR_ON;
	delete[] I18N.MouseAction_MAGNIFY_CURSOR_OFF;
	delete[] I18N.MouseAction_MAGNIFY_CURSOR_SWITCH;
	delete[] I18N.MouseAction_MSE_CAN_BYPASS_ON;
	delete[] I18N.MouseAction_MSE_CAN_BYPASS_OFF;

	delete[] I18N.SpecialAction_MUTE_SOUND;
	delete[] I18N.SpecialAction_VOLUME_UP;
	delete[] I18N.SpecialAction_VOLUME_DOWN;
	delete[] I18N.SpecialAction_MEMORIZE_MODE;
	delete[] I18N.SpecialAction_TO_MEM_MODE;
	delete[] I18N.SpecialAction_TO_MODE1;
	delete[] I18N.SpecialAction_TO_MODE2;
	delete[] I18N.SpecialAction_TO_MODE3;
	delete[] I18N.SpecialAction_TO_MODE4;
	delete[] I18N.SpecialAction_TO_MODE5;
	delete[] I18N.SpecialAction_TO_MODE6;
	delete[] I18N.SpecialAction_TO_MODE7;
	delete[] I18N.SpecialAction_TO_MODE8;
	delete[] I18N.SpecialAction_TO_LAST_MODE;
	delete[] I18N.SpecialAction_BASE_TO_MODE1;
	delete[] I18N.SpecialAction_BASE_TO_MODE2;
	delete[] I18N.SpecialAction_BASE_TO_MODE3;
	delete[] I18N.SpecialAction_BASE_TO_MODE4;
	delete[] I18N.SpecialAction_BASE_TO_MODE5;
	delete[] I18N.SpecialAction_BASE_TO_MODE6;
	delete[] I18N.SpecialAction_BASE_TO_MODE7;
	delete[] I18N.SpecialAction_BASE_TO_MODE8;
	delete[] I18N.SpecialAction_TO_BASE_MODE;
	delete[] I18N.SpecialAction_IF_RELEASED_GOTO;
	delete[] I18N.SpecialAction_IF_PUSHED_GOTO;
	delete[] I18N.SpecialAction_RETURN_TO;
	delete[] I18N.SpecialAction_FORGOT_RELEASED;
	delete[] I18N.SpecialAction_INTERRUPT;
	delete[] I18N.SpecialAction_NO_SUSTAIN;
	delete[] I18N.SpecialAction_PAUSE;
	delete[] I18N.SpecialAction_CHANGE_POSITION;
	delete[] I18N.SpecialAction_STANCE1;
	delete[] I18N.SpecialAction_STANCE2;
	delete[] I18N.SpecialAction_STANCE3;
	delete[] I18N.SpecialAction_STANCE4;
	delete[] I18N.SpecialAction_STANCE5;
	delete[] I18N.SpecialAction_BEEP1;
	delete[] I18N.SpecialAction_BEEP2;
	delete[] I18N.SpecialAction_BEEP3;
	delete[] I18N.SpecialAction_RESET_STATS;
	delete[] I18N.SpecialAction_ADDSTAT1;
	delete[] I18N.SpecialAction_ADDSTAT2;
	delete[] I18N.SpecialAction_ADDSTAT3;
	delete[] I18N.SpecialAction_ADDSTAT4;
	delete[] I18N.SpecialAction_ADDSTAT5;
	delete[] I18N.SpecialAction_ADDSTAT6;
	delete[] I18N.SpecialAction_ADDSTAT7;
	delete[] I18N.SpecialAction_ADDSTAT8;
	delete[] I18N.SpecialAction_KBD_INPUT_ON;
	delete[] I18N.SpecialAction_KBD_INPUT_OFF;
	delete[] I18N.SpecialAction_MSE_INPUT_ON;
	delete[] I18N.SpecialAction_MSE_INPUT_OFF;
	delete[] I18N.SpecialAction_SCREENSHOT;
	delete[] I18N.SpecialAction_MINIMIZE;
	delete[] I18N.SpecialAction_RESTORE;
	delete[] I18N.SpecialAction_TRANSPARENCY;
	delete[] I18N.SpecialAction_INPUT_OFF;
	delete[] I18N.SpecialAction_DS4_INPUT_ON;
	delete[] I18N.SpecialAction_DS5_INPUT_ON;
	delete[] I18N.SpecialAction_DI_INPUT_ON;
	delete[] I18N.SpecialAction_XI_INPUT_ON;
	delete[] I18N.SpecialAction_EXIT;

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

	delete[] I18N.Effect_X_INV;
	delete[] I18N.Effect_Y_INV;
	delete[] I18N.Effect_Z_INV;
	delete[] I18N.Effect_RZ_INV;
	delete[] I18N.Effect_RX_INV;
	delete[] I18N.Effect_RY_INV;
	delete[] I18N.Effect_X_PLUS;
	delete[] I18N.Effect_Y_PLUS;
	delete[] I18N.Effect_Z_PLUS;
	delete[] I18N.Effect_RZ_PLUS;
	delete[] I18N.Effect_RX_PLUS;
	delete[] I18N.Effect_RY_PLUS;
	delete[] I18N.Effect_X_MINUS;
	delete[] I18N.Effect_Y_MINUS;
	delete[] I18N.Effect_Z_MINUS;
	delete[] I18N.Effect_RZ_MINUS;
	delete[] I18N.Effect_RX_MINUS;
	delete[] I18N.Effect_RY_MINUS;
	delete[] I18N.Effect_X_DIM;
	delete[] I18N.Effect_X_DIM_P1;
	delete[] I18N.Effect_X_DIM_P2;
	delete[] I18N.Effect_Y_DIM;
	delete[] I18N.Effect_Y_DIM_P1;
	delete[] I18N.Effect_Y_DIM_P2;
	delete[] I18N.Effect_Z_DIM;
	delete[] I18N.Effect_Z_DIM_P1;
	delete[] I18N.Effect_Z_DIM_P2;
	delete[] I18N.Effect_RZ_DIM;
	delete[] I18N.Effect_RZ_DIM_P1;
	delete[] I18N.Effect_RZ_DIM_P2;
	delete[] I18N.Effect_RX_DIM_P1;
	delete[] I18N.Effect_RX_DIM_P2;
	delete[] I18N.Effect_RY_DIM_P1;
	delete[] I18N.Effect_RY_DIM_P2;
	delete[] I18N.Effect_XY_DEL_12_1;
	delete[] I18N.Effect_XY_DEL_12_2;
	delete[] I18N.Effect_XY_DEL_12_3;
	delete[] I18N.Effect_XY_DEL_12_4;
	delete[] I18N.Effect_XY_DEL_12_5;
	delete[] I18N.Effect_XY_DEL_12_6;
	delete[] I18N.Effect_XY_DEL_12_7;
	delete[] I18N.Effect_XY_DEL_12_8;
	delete[] I18N.Effect_XY_DEL_12_9;
	delete[] I18N.Effect_XY_DEL_12_10;
	delete[] I18N.Effect_XY_DEL_12_11;
	delete[] I18N.Effect_XY_DEL_12_12;
	delete[] I18N.Effect_ZRZ_DEL_12_1;
	delete[] I18N.Effect_ZRZ_DEL_12_2;
	delete[] I18N.Effect_ZRZ_DEL_12_3;
	delete[] I18N.Effect_ZRZ_DEL_12_4;
	delete[] I18N.Effect_ZRZ_DEL_12_5;
	delete[] I18N.Effect_ZRZ_DEL_12_6;
	delete[] I18N.Effect_ZRZ_DEL_12_7;
	delete[] I18N.Effect_ZRZ_DEL_12_8;
	delete[] I18N.Effect_ZRZ_DEL_12_9;
	delete[] I18N.Effect_ZRZ_DEL_12_10;
	delete[] I18N.Effect_ZRZ_DEL_12_11;
	delete[] I18N.Effect_ZRZ_DEL_12_12;
	delete[] I18N.Effect_XY_DEL_16_1;
	delete[] I18N.Effect_XY_DEL_16_2;
	delete[] I18N.Effect_XY_DEL_16_3;
	delete[] I18N.Effect_XY_DEL_16_4;
	delete[] I18N.Effect_XY_DEL_16_5;
	delete[] I18N.Effect_XY_DEL_16_6;
	delete[] I18N.Effect_XY_DEL_16_7;
	delete[] I18N.Effect_XY_DEL_16_8;
	delete[] I18N.Effect_XY_DEL_16_9;
	delete[] I18N.Effect_XY_DEL_16_10;
	delete[] I18N.Effect_XY_DEL_16_11;
	delete[] I18N.Effect_XY_DEL_16_12;
	delete[] I18N.Effect_XY_DEL_16_13;
	delete[] I18N.Effect_XY_DEL_16_14;
	delete[] I18N.Effect_XY_DEL_16_15;
	delete[] I18N.Effect_XY_DEL_16_16;
	delete[] I18N.Effect_ZRZ_DEL_16_1;
	delete[] I18N.Effect_ZRZ_DEL_16_2;
	delete[] I18N.Effect_ZRZ_DEL_16_3;
	delete[] I18N.Effect_ZRZ_DEL_16_4;
	delete[] I18N.Effect_ZRZ_DEL_16_5;
	delete[] I18N.Effect_ZRZ_DEL_16_6;
	delete[] I18N.Effect_ZRZ_DEL_16_7;
	delete[] I18N.Effect_ZRZ_DEL_16_8;
	delete[] I18N.Effect_ZRZ_DEL_16_9;
	delete[] I18N.Effect_ZRZ_DEL_16_10;
	delete[] I18N.Effect_ZRZ_DEL_16_11;
	delete[] I18N.Effect_ZRZ_DEL_16_12;
	delete[] I18N.Effect_ZRZ_DEL_16_13;
	delete[] I18N.Effect_ZRZ_DEL_16_14;
	delete[] I18N.Effect_ZRZ_DEL_16_15;
	delete[] I18N.Effect_ZRZ_DEL_16_16;
	delete[] I18N.Effect_RX_DEL_3_1;
	delete[] I18N.Effect_RX_DEL_3_2;
	delete[] I18N.Effect_RX_DEL_3_3;
	delete[] I18N.Effect_RX_DEL_4_1;
	delete[] I18N.Effect_RX_DEL_4_2;
	delete[] I18N.Effect_RX_DEL_4_3;
	delete[] I18N.Effect_RX_DEL_4_4;
	delete[] I18N.Effect_RY_DEL_3_1;
	delete[] I18N.Effect_RY_DEL_3_2;
	delete[] I18N.Effect_RY_DEL_3_3;
	delete[] I18N.Effect_RY_DEL_4_1;
	delete[] I18N.Effect_RY_DEL_4_2;
	delete[] I18N.Effect_RY_DEL_4_3;
	delete[] I18N.Effect_RY_DEL_4_4;
	delete[] I18N.Effect_XY_DISTORT_U___;
	delete[] I18N.Effect_XY_DISTORT__U__;
	delete[] I18N.Effect_XY_DISTORT___U_;
	delete[] I18N.Effect_XY_DISTORT____U;
	delete[] I18N.Effect_XY_DISTORT_UU__;
	delete[] I18N.Effect_XY_DISTORT__UU_;
	delete[] I18N.Effect_XY_DISTORT___UU;
	delete[] I18N.Effect_XY_DISTORT_UUU_;
	delete[] I18N.Effect_XY_DISTORT__UUU;
	delete[] I18N.Effect_XY_DISTORT_UUUU;
	delete[] I18N.Effect_XY_DISTORT_D___;
	delete[] I18N.Effect_XY_DISTORT__D__;
	delete[] I18N.Effect_XY_DISTORT___D_;
	delete[] I18N.Effect_XY_DISTORT____D;
	delete[] I18N.Effect_XY_DISTORT_DD__;
	delete[] I18N.Effect_XY_DISTORT__DD_;
	delete[] I18N.Effect_XY_DISTORT___DD;
	delete[] I18N.Effect_XY_DISTORT_DDD_;
	delete[] I18N.Effect_XY_DISTORT__DDD;
	delete[] I18N.Effect_XY_DISTORT_DDDD;
	delete[] I18N.Effect_XY_DISTORT_U_____;
	delete[] I18N.Effect_XY_DISTORT__U____;
	delete[] I18N.Effect_XY_DISTORT___U___;
	delete[] I18N.Effect_XY_DISTORT____U__;
	delete[] I18N.Effect_XY_DISTORT_____U_;
	delete[] I18N.Effect_XY_DISTORT______U;
	delete[] I18N.Effect_XY_DISTORT_UU____;
	delete[] I18N.Effect_XY_DISTORT__UU___;
	delete[] I18N.Effect_XY_DISTORT___UU__;
	delete[] I18N.Effect_XY_DISTORT____UU_;
	delete[] I18N.Effect_XY_DISTORT_____UU;
	delete[] I18N.Effect_XY_DISTORT__UUU__;
	delete[] I18N.Effect_XY_DISTORT___UUU_;
	delete[] I18N.Effect_XY_DISTORT_UUUU__;
	delete[] I18N.Effect_XY_DISTORT__UUUU_;
	delete[] I18N.Effect_XY_DISTORT___UUUU;
	delete[] I18N.Effect_XY_DISTORT_UUUUU_;
	delete[] I18N.Effect_XY_DISTORT__UUUUU;
	delete[] I18N.Effect_XY_DISTORT_D_____;
	delete[] I18N.Effect_XY_DISTORT__D____;
	delete[] I18N.Effect_XY_DISTORT___D___;
	delete[] I18N.Effect_XY_DISTORT____D__;
	delete[] I18N.Effect_XY_DISTORT_____D_;
	delete[] I18N.Effect_XY_DISTORT______D;
	delete[] I18N.Effect_XY_DISTORT_DD____;
	delete[] I18N.Effect_XY_DISTORT__DD___;
	delete[] I18N.Effect_XY_DISTORT___DD__;
	delete[] I18N.Effect_XY_DISTORT____DD_;
	delete[] I18N.Effect_XY_DISTORT_____DD;
	delete[] I18N.Effect_XY_DISTORT__DDD__;
	delete[] I18N.Effect_XY_DISTORT___DDD_;
	delete[] I18N.Effect_XY_DISTORT_DDDD__;
	delete[] I18N.Effect_XY_DISTORT__DDDD_;
	delete[] I18N.Effect_XY_DISTORT___DDDD;
	delete[] I18N.Effect_XY_DISTORT_DDDDD_;
	delete[] I18N.Effect_XY_DISTORT__DDDDD;
	delete[] I18N.Effect_ZRZ_DISTORT_U___;
	delete[] I18N.Effect_ZRZ_DISTORT__U__;
	delete[] I18N.Effect_ZRZ_DISTORT___U_;
	delete[] I18N.Effect_ZRZ_DISTORT____U;
	delete[] I18N.Effect_ZRZ_DISTORT_UU__;
	delete[] I18N.Effect_ZRZ_DISTORT__UU_;
	delete[] I18N.Effect_ZRZ_DISTORT___UU;
	delete[] I18N.Effect_ZRZ_DISTORT_UUU_;
	delete[] I18N.Effect_ZRZ_DISTORT__UUU;
	delete[] I18N.Effect_ZRZ_DISTORT_UUUU;
	delete[] I18N.Effect_ZRZ_DISTORT_D___;
	delete[] I18N.Effect_ZRZ_DISTORT__D__;
	delete[] I18N.Effect_ZRZ_DISTORT___D_;
	delete[] I18N.Effect_ZRZ_DISTORT____D;
	delete[] I18N.Effect_ZRZ_DISTORT_DD__;
	delete[] I18N.Effect_ZRZ_DISTORT__DD_;
	delete[] I18N.Effect_ZRZ_DISTORT___DD;
	delete[] I18N.Effect_ZRZ_DISTORT_DDD_;
	delete[] I18N.Effect_ZRZ_DISTORT__DDD;
	delete[] I18N.Effect_ZRZ_DISTORT_DDDD;
	delete[] I18N.Effect_ZRZ_DISTORT_U_____;
	delete[] I18N.Effect_ZRZ_DISTORT__U____;
	delete[] I18N.Effect_ZRZ_DISTORT___U___;
	delete[] I18N.Effect_ZRZ_DISTORT____U__;
	delete[] I18N.Effect_ZRZ_DISTORT_____U_;
	delete[] I18N.Effect_ZRZ_DISTORT______U;
	delete[] I18N.Effect_ZRZ_DISTORT_UU____;
	delete[] I18N.Effect_ZRZ_DISTORT__UU___;
	delete[] I18N.Effect_ZRZ_DISTORT___UU__;
	delete[] I18N.Effect_ZRZ_DISTORT____UU_;
	delete[] I18N.Effect_ZRZ_DISTORT_____UU;
	delete[] I18N.Effect_ZRZ_DISTORT__UUU__;
	delete[] I18N.Effect_ZRZ_DISTORT___UUU_;
	delete[] I18N.Effect_ZRZ_DISTORT_UUUU__;
	delete[] I18N.Effect_ZRZ_DISTORT__UUUU_;
	delete[] I18N.Effect_ZRZ_DISTORT___UUUU;
	delete[] I18N.Effect_ZRZ_DISTORT_UUUUU_;
	delete[] I18N.Effect_ZRZ_DISTORT__UUUUU;
	delete[] I18N.Effect_ZRZ_DISTORT_D_____;
	delete[] I18N.Effect_ZRZ_DISTORT__D____;
	delete[] I18N.Effect_ZRZ_DISTORT___D___;
	delete[] I18N.Effect_ZRZ_DISTORT____D__;
	delete[] I18N.Effect_ZRZ_DISTORT_____D_;
	delete[] I18N.Effect_ZRZ_DISTORT______D;
	delete[] I18N.Effect_ZRZ_DISTORT_DD____;
	delete[] I18N.Effect_ZRZ_DISTORT__DD___;
	delete[] I18N.Effect_ZRZ_DISTORT___DD__;
	delete[] I18N.Effect_ZRZ_DISTORT____DD_;
	delete[] I18N.Effect_ZRZ_DISTORT_____DD;
	delete[] I18N.Effect_ZRZ_DISTORT__DDD__;
	delete[] I18N.Effect_ZRZ_DISTORT___DDD_;
	delete[] I18N.Effect_ZRZ_DISTORT_DDDD__;
	delete[] I18N.Effect_ZRZ_DISTORT__DDDD_;
	delete[] I18N.Effect_ZRZ_DISTORT___DDDD;
	delete[] I18N.Effect_ZRZ_DISTORT_DDDDD_;
	delete[] I18N.Effect_ZRZ_DISTORT__DDDDD;

	delete[] I18N.ModulesAction_NOTEPAD_DOWN;
	delete[] I18N.ModulesAction_NOTEPAD_UP;
	delete[] I18N.ModulesAction_WEB_DOWN;
	delete[] I18N.ModulesAction_WEB_UP;
	delete[] I18N.ModulesAction_WEB_LEFT;
	delete[] I18N.ModulesAction_WEB_RIGHT;
	delete[] I18N.ModulesAction_WEB_PREVIOUSTAB;
	delete[] I18N.ModulesAction_WEB_NEXTTAB;
	delete[] I18N.ModulesAction_WEB_CLOSETAB;
	delete[] I18N.ModulesAction_WEB_HOME;
	delete[] I18N.ModulesAction_WEB_FAVORITE1;
	delete[] I18N.ModulesAction_WEB_FAVORITE2;
	delete[] I18N.ModulesAction_WEB_FAVORITE3;
	delete[] I18N.ModulesAction_WEB_FAVORITE4;
	delete[] I18N.ModulesAction_WEB_FAVORITE5;
	delete[] I18N.ModulesAction_WEB_FAVORITE6;
	delete[] I18N.ModulesAction_WEB_FAVORITE7;
	delete[] I18N.ModulesAction_WEB_FAVORITE8;
	delete[] I18N.ModulesAction_WEB_FAVORITE9;
	delete[] I18N.ModulesAction_WEB_BACK;
	delete[] I18N.ModulesAction_WEB_NEXT;
	delete[] I18N.ModulesAction_WEB_REFRESH;
	delete[] I18N.ModulesAction_WEB_CANCEL;
	delete[] I18N.ModulesAction_WEB_AUTOREFRESH;
	delete[] I18N.ModulesAction_WEB_ZOOMMINUS;
	delete[] I18N.ModulesAction_WEB_ZOOMPLUS;
	delete[] I18N.ModulesAction_WEB_ZOOMRESET;
	delete[] I18N.ModulesAction_WEB_ZOOMSET;
	delete[] I18N.ModulesAction_WEB_VISIBILITY;
	delete[] I18N.ModulesAction_WEB_SCREENSHOT;
	delete[] I18N.ModulesAction_WEB_DARKMODE;
	delete[] I18N.ModulesAction_WEB_DARKMODE2;
	delete[] I18N.ModulesAction_LINKS_APPLICATION0;
	delete[] I18N.ModulesAction_LINKS_APPLICATION1;
	delete[] I18N.ModulesAction_LINKS_APPLICATION2;
	delete[] I18N.ModulesAction_LINKS_APPLICATION3;
	delete[] I18N.ModulesAction_LINKS_APPLICATION4;

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
	
	delete[] I18N.Dispatch_1_X;
	delete[] I18N.Dispatch_1_Y;
	delete[] I18N.Dispatch_1_Z;
	delete[] I18N.Dispatch_1_RX;
	delete[] I18N.Dispatch_1_RY;
	delete[] I18N.Dispatch_1_RZ;
	delete[] I18N.Dispatch_1_SL0;
	delete[] I18N.Dispatch_1_SL1;
	delete[] I18N.Dispatch_2_X;
	delete[] I18N.Dispatch_2_Y;
	delete[] I18N.Dispatch_2_Z;
	delete[] I18N.Dispatch_2_RX;
	delete[] I18N.Dispatch_2_RY;
	delete[] I18N.Dispatch_2_RZ;
	delete[] I18N.Dispatch_2_SL0;
	delete[] I18N.Dispatch_2_SL1;
	delete[] I18N.Dispatch_1_POV1;
	delete[] I18N.Dispatch_1_POV2;
	delete[] I18N.Dispatch_1_POV3;
	delete[] I18N.Dispatch_1_POV4;
	delete[] I18N.Dispatch_2_POV1;
	delete[] I18N.Dispatch_2_POV2;
	delete[] I18N.Dispatch_2_POV3;
	delete[] I18N.Dispatch_2_POV4;
	delete[] I18N.Dispatch_BUTTON;

	delete[] I18N.ABOUT_1;
	delete[] I18N.ABOUT_2;
	delete[] I18N.ABOUT_3;
	delete[] I18N.ABOUT_OK;
	delete[] I18N.SETTINGS_SOURCES;
	delete[] I18N.SETTINGS_DS4;
	delete[] I18N.SETTINGS_DS5;
	delete[] I18N.SETTINGS_DI;
	delete[] I18N.SETTINGS_XI;
	delete[] I18N.SETTINGS_KBD;
	delete[] I18N.SETTINGS_MSE;
	delete[] I18N.SETTINGS_COUNTRY;
	delete[] I18N.SETTINGS_VJOY_SHUTDOWN;
	delete[] I18N.SETTINGS_ON_EXIT;
	delete[] I18N.SETTINGS_TEXT_VJ_DEVICE;
	delete[] I18N.SETTINGS_TEXT_XI_DEVICE;
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
	delete[] I18N.SETTINGS_TEXT_DS_SERIAL;
	delete[] I18N.SETTINGS_DI_DEVICE_1;
	delete[] I18N.SETTINGS_DI_DEVICE_2;
	delete[] I18N.SETTINGS_DI_DEVICE_RELOAD;
	delete[] I18N.SETTINGS_TEXT_DI_DEVICE;
	delete[] I18N.SETTINGS_DI_DEVICE_CLEAR;
	delete[] I18N.SETTINGS_DARK_THEME;
	delete[] I18N.SETTINGS_TEXT_THRESHOLD;
	delete[] I18N.SETTINGS_TEXT_SIMULTANEOUS;
	delete[] I18N.SETTINGS_TEXT_LONG;
	delete[] I18N.SETTINGS_TEXT_VERY_LONG;
	delete[] I18N.SETTINGS_TEXT_WEBREFRESH;
	delete[] I18N.SETTINGS_TEXT_OPACITY;
	delete[] I18N.SETTINGS_UNIT_THRESHOLD;
	delete[] I18N.SETTINGS_UNIT_SIMULTANEOUS;
	delete[] I18N.SETTINGS_UNIT_LONG;
	delete[] I18N.SETTINGS_UNIT_VERY_LONG;
	delete[] I18N.SETTINGS_UNIT_WEB_REFRESH;
	delete[] I18N.SETTINGS_UNIT_OPACITY;
	delete[] I18N.SETTINGS_MULTIPLE_TOUCHPAD;
	delete[] I18N.SETTINGS_TEXT_FIRST_BUTTON;
	delete[] I18N.SETTINGS_TEXT_COLUMNS;
	delete[] I18N.SETTINGS_TEXT_ROWS;
	delete[] I18N.SETTINGS_LED;
	delete[] I18N.SETTINGS_WHEN_EXITING;
	delete[] I18N.SETTINGS_LED_BUTTON;
	delete[] I18N.SETTINGS_COLOR;
	delete[] I18N.VJOY_FAILED;
	delete[] I18N.VJOY_RESET_CONFIRM;
	delete[] I18N.VJOY_ADDDEV;
	delete[] I18N.VJOY_DELDEV;
	delete[] I18N.VJOY_AXIS;
	delete[] I18N.VJOY_CHK_X;
	delete[] I18N.VJOY_CHK_Y;
	delete[] I18N.VJOY_CHK_Z;
	delete[] I18N.VJOY_CHK_RX;
	delete[] I18N.VJOY_CHK_RY;
	delete[] I18N.VJOY_CHK_RZ;
	delete[] I18N.VJOY_CHK_SL0;
	delete[] I18N.VJOY_CHK_SL1;
	delete[] I18N.VJOY_BTN;
	delete[] I18N.VJOY_POV;
	delete[] I18N.VJOY_POV_DESC;
	delete[] I18N.VJOY_POV_CONT;
	delete[] I18N.VJOY_FFB;
	delete[] I18N.VJOY_CHK_FFB_CONST;
	delete[] I18N.VJOY_CHK_FFB_RAMP;
	delete[] I18N.VJOY_CHK_FFB_SQUARE;
	delete[] I18N.VJOY_CHK_FFB_SINE;
	delete[] I18N.VJOY_CHK_FFB_TRI;
	delete[] I18N.VJOY_CHK_FFB_STUP;
	delete[] I18N.VJOY_CHK_FFB_STDN;
	delete[] I18N.VJOY_CHK_FFB_SPRING;
	delete[] I18N.VJOY_CHK_FFB_DAMPER;
	delete[] I18N.VJOY_CHK_FFB_INERTIA;
	delete[] I18N.VJOY_CHK_FFB_FRICTION;
	delete[] I18N.VJOY_DEVICE_1;
	delete[] I18N.VJOY_DEVICE_2;
	delete[] I18N.VJOY_DEVICE_3;
	delete[] I18N.VJOY_DEVICE_4;
	delete[] I18N.VJOY_DEVICE_5;
	delete[] I18N.VJOY_DEVICE_6;
	delete[] I18N.VJOY_DEVICE_7;
	delete[] I18N.VJOY_DEVICE_8;
	delete[] I18N.VJOY_DEVICE_9;
	delete[] I18N.VJOY_DEVICE_10;
	delete[] I18N.VJOY_DEVICE_11;
	delete[] I18N.VJOY_DEVICE_12;
	delete[] I18N.VJOY_DEVICE_13;
	delete[] I18N.VJOY_DEVICE_14;
	delete[] I18N.VJOY_DEVICE_15;
	delete[] I18N.VJOY_DEVICE_16;
	delete[] I18N.VJOY_CANCEL;
	delete[] I18N.VJOY_DEVNUMBER;
	delete[] I18N.VJOY_CTRLPANEL;
	delete[] I18N.VJOY_APPLY;
	delete[] I18N.VJOY_ADDDEL;
	delete[] I18N.VJOY_RESET;
	delete[] I18N.DINPUT_CANCEL;
	delete[] I18N.DINPUT_LOAD1;
	delete[] I18N.DINPUT_LOAD2;
	delete[] I18N.DINPUT_LOAD3;
	delete[] I18N.DINPUT_SAVE1;
	delete[] I18N.DINPUT_SAVE2;
	delete[] I18N.DINPUT_SAVE3;
	delete[] I18N.DINPUT_CLEAR;
	delete[] I18N.DINPUT_CTRLPANEL;
	delete[] I18N.MAPPING_ALWAYS;
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
	delete[] I18N.KEYMAP_CLASS;
	delete[] I18N.KEYMAP_TITLE;
	delete[] I18N.KEYMAP_IDX;
	delete[] I18N.KEYMAP_IS_W_VISIBLE;
	delete[] I18N.KEYMAP_CLEAR2;
	delete[] I18N.KEYMAP_DELETE;
	delete[] I18N.KEYMAP_OK2;
	delete[] I18N.KEYMAP_CANCEL2;
	delete[] I18N.XOUTPUT_ACTIVE;
	delete[] I18N.XOUTPUT_VJOY_ACTIVE;
	delete[] I18N.XOUTPUT_PAD;
	delete[] I18N.XOUTPUT_X360;
	delete[] I18N.XOUTPUT_DS4;
	delete[] I18N.XOUTPUT_INSTALL;
	delete[] I18N.XOUTPUT_INSTALL_VJOY;
	delete[] I18N.XOUTPUT_STATUS;
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
	delete[] I18N.WEB_INJECT_SCRIPT_1;
	delete[] I18N.WEB_INJECT_SCRIPT_2;
	delete[] I18N.WEB_INJECT_SCRIPT_3;
	delete[] I18N.WEB_INITIALIZE_SCRIPT_1;
	delete[] I18N.WEB_INITIALIZE_SCRIPT_2;
	delete[] I18N.WEB_INITIALIZE_SCRIPT_3;
	delete[] I18N.WEB_POST_MESSAGE_STRING_1;
	delete[] I18N.WEB_POST_MESSAGE_STRING_2;
	delete[] I18N.WEB_POST_MESSAGE_STRING_3;
	delete[] I18N.WEB_POST_MESSAGE_JSON_1;
	delete[] I18N.WEB_POST_MESSAGE_JSON_2;
	delete[] I18N.WEB_POST_MESSAGE_JSON_3;
	delete[] I18N.WEB_SUBSCRIBE_CDP_EVENT_1;
	delete[] I18N.WEB_SUBSCRIBE_CDP_EVENT_2;
	delete[] I18N.WEB_SUBSCRIBE_CDP_EVENT_3;
	delete[] I18N.WEB_CALL_CDP_METHOD_1;
	delete[] I18N.WEB_CALL_CDP_METHOD_2;
	delete[] I18N.WEB_CALL_CDP_METHOD_3;
	delete[] I18N.WEB_COM_OBJECT_1;
	delete[] I18N.WEB_COM_OBJECT_2;
	delete[] I18N.WEB_COM_OBJECT_3;
	delete[] I18N.WEB_LANGUAGE_1;
	delete[] I18N.WEB_LANGUAGE_2;
	delete[] I18N.WEB_LANGUAGE_3;
	delete[] I18N.WEB_USERAGENT_1;
	delete[] I18N.WEB_USERAGENT_2;
	delete[] I18N.WEB_USERAGENT_3;
	delete[] I18N.WEB_BLACKLIST_1;
	delete[] I18N.WEB_BLACKLIST_2;
	delete[] I18N.WEB_BLACKLIST_3;
	delete[] I18N.WEB_SCRIPT_DIALOG_1;
	delete[] I18N.LINKS_TEXT1;
	delete[] I18N.LINKS_TEXT2;
	delete[] I18N.LINKS_TEXT3;
	delete[] I18N.LINKS_TEXT4;
	delete[] I18N.LINKS_DS2VJOY;
	delete[] I18N.LINKS_VJOY;
	delete[] I18N.LINKS_WEBVIEW2;
	delete[] I18N.LINKS_VIGEMBUS;
	delete[] I18N.LINKS_VIGEMCLIENT;
	delete[] I18N.LINKS_HIDGUARDIAN;
	delete[] I18N.LINKS_HIDCERBERUS;
	delete[] I18N.LINKS_URL_DS2VJOY;
	delete[] I18N.LINKS_URL_VJOY;
	delete[] I18N.LINKS_URL_WEBVIEW2;
	delete[] I18N.LINKS_URL_VIGEMBUS;
	delete[] I18N.LINKS_URL_VIGEMCLIENT;
	delete[] I18N.LINKS_URL_HIDGUARDIAN;
	delete[] I18N.LINKS_URL_HIDCERBERUS;
	delete[] I18N.NOTEPAD_UNSAVED;

	delete[] I18N.STATE_INSTALL;
	delete[] I18N.STATE_UNINSTALL;
	delete[] I18N.STATE_VJOY_INSTALL;
	delete[] I18N.STATE_VJOY_UNINSTALL;
	delete[] I18N.STATE_START;
	delete[] I18N.STATE_STOP;
	delete[] I18N.STATE_RESTART;
	delete[] I18N.STATE_ENABLE;
	delete[] I18N.STATE_VJOY_ENABLE;
	delete[] I18N.STATE_DISABLE;
	delete[] I18N.STATE_WAITING;

	delete[] I18N.FILE;
	delete[] I18N.EXIT;
	delete[] I18N.HELP;
	delete[] I18N.ABOUT;
	delete[] I18N.MENU_SEE_VIEW2;
	delete[] I18N.MENU_TO_MODE_0;
	delete[] I18N.MENU_TO_MODE_1;
	delete[] I18N.MENU_TO_MODE_2;
	delete[] I18N.MENU_TO_MODE_3;
	delete[] I18N.MENU_TO_MODE_4;
	delete[] I18N.MENU_TO_MODE_5;
	delete[] I18N.MENU_TO_MODE_6;
	delete[] I18N.MENU_TO_MODE_7;
	delete[] I18N.MENU_TO_MODE_8;
	delete[] I18N.CLONE_TO_MODE_0;
	delete[] I18N.CLONE_TO_MODE_1;
	delete[] I18N.CLONE_TO_MODE_2;
	delete[] I18N.CLONE_TO_MODE_3;
	delete[] I18N.CLONE_TO_MODE_4;
	delete[] I18N.CLONE_TO_MODE_5;
	delete[] I18N.CLONE_TO_MODE_6;
	delete[] I18N.CLONE_TO_MODE_7;
	delete[] I18N.CLONE_TO_MODE_8;
	delete[] I18N.MENU_ADD;
	delete[] I18N.MENU_EDIT;
	delete[] I18N.MENU_DEL;
	delete[] I18N.MENU_COPY;
	delete[] I18N.MENU_SEPARATOR;
	delete[] I18N.MENU_MOVE_TO_0;
	delete[] I18N.MENU_MOVE_TO_1;
	delete[] I18N.MENU_MOVE_TO_2;
	delete[] I18N.MENU_MOVE_TO_3;
	delete[] I18N.MENU_MOVE_TO_4;
	delete[] I18N.MENU_MOVE_TO_5;
	delete[] I18N.MENU_MOVE_TO_6;
	delete[] I18N.MENU_MOVE_TO_7;
	delete[] I18N.MENU_MOVE_TO_8;
	delete[] I18N.MENU_SWAP_VIEW;
	delete[] I18N.MENU_ADD_NOTICE;
	delete[] I18N.MENU_SEPARATORN;
	delete[] I18N.MENU_WEB_PDF_PORTRAIT;
	delete[] I18N.MENU_WEB_PDF_LANDSCAPE;
	delete[] I18N.MENU_WEB_SCREENSHOT;
	delete[] I18N.MENU_WEB_TOPMOST;
	delete[] I18N.MENU_WEB_VISIBILITY;
	delete[] I18N.MENU_WEB_DARK_MODE;
	delete[] I18N.MENU_WEB_DARK_MODE_2;
	delete[] I18N.MENU_WEB_BOUNDS_MODE;
	delete[] I18N.MENU_WEB_BLOCK_IMAGES;
	delete[] I18N.MENU_WEB_CLOSE_WEBVIEW;
	delete[] I18N.MENU_WEB_REINIT;
	delete[] I18N.MENU_WEB_NEW_WINDOW;
	delete[] I18N.MENU_WEB_NEW_THREAD;
	delete[] I18N.MENU_WEB_CLEAR_CACHE;
	delete[] I18N.MENU_WEB_CLEAR_COOKIES;
	delete[] I18N.MENU_WEB_DELETE_DATAFOLDER;
	delete[] I18N.MENU_WEB_INJECT_SCRIPT;
	delete[] I18N.MENU_WEB_INITIALIZE_SCRIPT;
	delete[] I18N.MENU_WEB_USE_DEFERRED_SCRIPT;
	delete[] I18N.MENU_WEB_COMPLETE_DEFERRED;
	delete[] I18N.MENU_WEB_POST_MESSAGE_STRING;
	delete[] I18N.MENU_WEB_POST_MESSAGE_JSON;
	delete[] I18N.MENU_WEB_SUBSCRIBE_CDP_EVENT;
	delete[] I18N.MENU_WEB_CALL_CDP_METHOD;
	delete[] I18N.MENU_WEB_COM_OBJECT;
	delete[] I18N.MENU_WEB_FLAGS;
	delete[] I18N.MENU_WEB_LANGUAGE;
	delete[] I18N.MENU_WEB_USERAGENT;
	delete[] I18N.MENU_WEB_BLACKLIST;
	delete[] I18N.MENU_WEB_TASK_MANAGER;
	delete[] I18N.MENU_WEB_FAV_0;
	delete[] I18N.MENU_WEB_FAV_1;
	delete[] I18N.MENU_WEB_FAV_2;
	delete[] I18N.MENU_WEB_FAV_3;
	delete[] I18N.MENU_WEB_FAV_4;
	delete[] I18N.MENU_WEB_FAV_5;
	delete[] I18N.MENU_WEB_FAV_6;
	delete[] I18N.MENU_WEB_FAV_7;
	delete[] I18N.MENU_WEB_FAV_8;
	delete[] I18N.MENU_WEB_FAV_9;

	delete[] I18N.HELP_DINPUT_1;
	delete[] I18N.HELP_DINPUT_P1;
	delete[] I18N.HELP_DINPUT_P2;
	delete[] I18N.HELP_DINPUT_P3;
	delete[] I18N.HELP_DINPUT_P4;
	delete[] I18N.HELP_DINPUT_6;
	delete[] I18N.HELP_DINPUT_7;
	delete[] I18N.HELP_DINPUT_8;
	delete[] I18N.HELP_DINPUT_9;
	delete[] I18N.HELP_DINPUT_10;
	delete[] I18N.HELP_DINPUT_11;
	delete[] I18N.HELP_DINPUT_12;
	delete[] I18N.HELP_DINPUT_13;
	delete[] I18N.HELP_DINPUT_14;
	delete[] I18N.HELP_DINPUT_15;
	delete[] I18N.HELP_DINPUT_16;
	delete[] I18N.HELP_DINPUT_17;
	delete[] I18N.HELP_DINPUT_18;
	delete[] I18N.HELP_DINPUT_19;
	delete[] I18N.HELP_DINPUT_20;
	delete[] I18N.HELP_DINPUT_21;
	delete[] I18N.HELP_DINPUT_22;
	delete[] I18N.HELP_DINPUT_23;
	delete[] I18N.HELP_DINPUT_24;
	delete[] I18N.HELP_DINPUT_25;
	delete[] I18N.HELP_DINPUT_26;
	delete[] I18N.HELP_DINPUT_27;
	delete[] I18N.HELP_DINPUT_28;
	delete[] I18N.HELP_DINPUT_29;
	delete[] I18N.HELP_DINPUT_30;
	delete[] I18N.HELP_DINPUT_31;
	delete[] I18N.HELP_DINPUT_32;
	delete[] I18N.HELP_DINPUT_L1;
	delete[] I18N.HELP_DINPUT_R1;
	delete[] I18N.HELP_DINPUT_L2;
	delete[] I18N.HELP_DINPUT_R2;
	delete[] I18N.HELP_DINPUT_LT;
	delete[] I18N.HELP_DINPUT_RT;
	delete[] I18N.HELP_DINPUT_LX;
	delete[] I18N.HELP_DINPUT_LY;
	delete[] I18N.HELP_DINPUT_RX;
	delete[] I18N.HELP_DINPUT_RY;
	delete[] I18N.HELP_DINPUT_S0;
	delete[] I18N.HELP_DINPUT_S1;

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

	delete[] I18N.HELP_SETTINGS_MOUSE;

	delete[] I18N.HELP_WEB_MENU;
	delete[] I18N.HELP_WEB_CLOSE;
	delete[] I18N.HELP_WEB_FAVORITES;
	delete[] I18N.HELP_WEB_HOME;
	delete[] I18N.HELP_WEB_BACK;
	delete[] I18N.HELP_WEB_FORWARD;
	delete[] I18N.HELP_WEB_REFRESH;
	delete[] I18N.HELP_WEB_GO;
	delete[] I18N.HELP_WEB_STOP;
	delete[] I18N.HELP_WEB_AUTOREFRESH;
	delete[] I18N.HELP_WEB_ZOOM_MINUS;
	delete[] I18N.HELP_WEB_ZOOM_PLUS;
}
