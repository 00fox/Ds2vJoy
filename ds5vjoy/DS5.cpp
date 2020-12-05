#include "stdafx.h"
#include "DS5.h"
#include "Log.h"
#include "Language.h"
#include "../external/crc32/crc32.h"
unsigned __stdcall inputloop(void  *v)
{
	((DS5Device*)v)->InputLoop();
	return 0;
}
unsigned __stdcall outputloop(void  *v)
{
	((DS5Device*)v)->OutputLoop();
	return 0;
}

DS5Device::DS5Device():
	m_callback(0),m_callbackdata(0)
	, hDS5Handle(INVALID_HANDLE_VALUE)
	, m_hThread(NULL)
	, m_Red(60),m_Green(0),m_Blue(0)
{
	memset(m_DS5Serial, 0, sizeof(m_DS5Serial));
	m_oRead.hEvent = m_hREvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_oWrite.hEvent = m_hWEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_buttons[DS5Button::none].setBit(m_receivedData , 0);
	m_buttons[DS5Button::SQUARE].setBit(m_receivedData + OffsetSquare, 0b10000);
	m_buttons[DS5Button::TRIANGLE].setBit(m_receivedData + OffsetTriangle, 0b10000000);
	m_buttons[DS5Button::CROSS].setBit(m_receivedData + OffsetCross, 0b100000);
	m_buttons[DS5Button::CIRCLE].setBit(m_receivedData + OffsetCircle, 0b1000000);
	m_buttons[DS5Button::L1].setBit(m_receivedData + OffsetL1, 0b1);
	m_buttons[DS5Button::R1].setBit(m_receivedData + OffsetR1, 0b10);
	m_buttons[DS5Button::L2].setBit(m_receivedData + OffsetL2, 0b100);
	m_buttons[DS5Button::R2].setBit(m_receivedData + OffsetR2, 0b1000);
	m_buttons[DS5Button::L3].setBit(m_receivedData + OffsetL3, 0b1000000);
	m_buttons[DS5Button::R3].setBit(m_receivedData + OffsetR3, 0b10000000);
	m_buttons[DS5Button::CREATE].setBit(m_receivedData + OffsetCreate, 0b10000);
	m_buttons[DS5Button::OPTIONS].setBit(m_receivedData + OffsetOption, 0b100000);
	m_buttons[DS5Button::PS].setBit(m_receivedData + OffsetPS, 0b1);
	m_buttons[DS5Button::TOUCH].setBit(m_receivedData + OffsetTouchPadClick, 0b10);
	m_buttons[DS5Button::MUTE].setBit(m_receivedData + OffsetMute, 0b100);
	m_buttons[DS5Button::LX].setStick(m_receivedData + OffsetLX);
	m_buttons[DS5Button::LY].setStick(m_receivedData + OffsetLY);
	m_buttons[DS5Button::RX].setStick(m_receivedData + OffsetRX);
	m_buttons[DS5Button::RY].setStick(m_receivedData + OffsetRY);
	m_buttons[DS5Button::L2TRIGGER].setTrigger(m_receivedData + OffsetLeftTrigger);
	m_buttons[DS5Button::R2TRIGGER].setTrigger(m_receivedData + OffsetRightTrigger);
	m_buttons[DS5Button::DPAD].setDPad(m_receivedData + OffsetDPad);
	m_buttons[DS5Button::DPAD_UP].setDPadType(m_receivedData + OffsetDPad, DS5Button::typeDPadUP);
	m_buttons[DS5Button::DPAD_RIGHT].setDPadType(m_receivedData + OffsetDPad, DS5Button::typeDPadRIGHT);
	m_buttons[DS5Button::DPAD_DOWN].setDPadType(m_receivedData + OffsetDPad, DS5Button::typeDPadDOWN);
	m_buttons[DS5Button::DPAD_LEFT].setDPadType(m_receivedData + OffsetDPad, DS5Button::typeDPadLEFT);

}

DS5Device::~DS5Device()
{
	Close();
	CloseHandle(m_hREvent);
	CloseHandle(m_hWEvent);
}


bool DS5Device::Active()
{
	return hDS5Handle != INVALID_HANDLE_VALUE;
}

bool DS5Device::Open()
{
	if (hDS5Handle != INVALID_HANDLE_VALUE)
		return false;
	Close();
	GUID guid;// = { 0x4D1E55B2L, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 };
	HidD_GetHidGuid(&guid);
	bool ret = false;
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&guid,NULL,NULL,DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == 0) {
		SetupDiDestroyDeviceInfoList(hDevInfo);
		return false;
	}
	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
	DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);

	HIDD_ATTRIBUTES Attributes;
	PSP_DEVICE_INTERFACE_DETAIL_DATA detail=0;
	DWORD RequiredSize;

	for (int i = 0; SetupDiEnumDeviceInterfaces(hDevInfo, 0, &guid, i, &DeviceInterfaceData) != 0; i++) {
		RequiredSize = 0;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, NULL, 0, &RequiredSize, NULL);
		if (RequiredSize == 0)
			continue;
		if (detail != 0)
			free(detail);
		if (hDS5Handle != INVALID_HANDLE_VALUE) {
			CloseHandle(hDS5Handle);
			hDS5Handle = INVALID_HANDLE_VALUE;
		}
		if (m_OutputBuf != NULL) {
			free(m_OutputBuf);
			m_OutputBuf = NULL;
		}
		if (m_InputBuf != NULL) {
			free(m_InputBuf);
			m_InputBuf = NULL;
		}
		detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(RequiredSize);
		if (detail == 0)
			continue;
		detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		DWORD dwRequiredSize;
		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, detail, RequiredSize, &dwRequiredSize, NULL))
			continue;

		hDS5Handle = CreateFile(
			detail->DevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL);
		if (hDS5Handle == INVALID_HANDLE_VALUE)
			continue;

		Attributes.Size = sizeof(Attributes);
		if (!HidD_GetAttributes(hDS5Handle, &Attributes))
			continue;

		if (DS5_VenderID != Attributes.VendorID)
			continue;

		if (0x0CE6 != Attributes.ProductID)
			continue;

		PHIDP_PREPARSED_DATA PreparsedData;
		if (!HidD_GetPreparsedData(hDS5Handle, &PreparsedData))
			continue;

		HIDP_CAPS cap;
		NTSTATUS r = HidP_GetCaps(PreparsedData, &cap);
		HidD_FreePreparsedData(PreparsedData);
		if (r != HIDP_STATUS_SUCCESS)
			continue;

		//送受信用のバッファの設定
		m_inputLen = cap.InputReportByteLength;
		m_outputLen = cap.OutputReportByteLength;
		m_bBluetooth = m_inputLen > 64;

		//シリアル判定
		memset(m_DS5Serial, 0, sizeof(m_DS5Serial));
		if (m_bBluetooth) {
			if (m_outputLen < 78) {
				LogPrintf(L"not support DS controller(%d)", m_outputLen);
				continue;
			}
			if (!HidD_GetSerialNumberString(hDS5Handle, m_DS5Serial, sizeof(m_DS5Serial)))
				continue;
			unsigned char buf[78] = { 5 };
			if (!HidD_GetFeature(hDS5Handle, buf, sizeof(buf)))
				continue;

		}else{
			unsigned char buf[78] = { 9 };
			if (!HidD_GetFeature(hDS5Handle, buf, sizeof(buf)))
				continue;
			wsprintf(m_DS5Serial, L"%02x%02x%02x%02x%02x%02x", buf[6], buf[5], buf[4], buf[3], buf[2], buf[1]);
		}
		if (0 != m_TargetSerial[0] && _wcsicmp(m_TargetSerial, m_DS5Serial) != 0) {
			LogPrintf(I18N.SkipController,L"DualSense", m_DS5Serial);
			continue;
		}
		LogPrintf(I18N.ConnectController, L"DualSense", m_DS5Serial);
		char buf[64] = { 0x20 };
		if (!HidD_GetFeature(hDS5Handle, buf, sizeof(buf))) {
			LogPrintf(L"cannot get firmware version");

			DWORD errorcode = GetLastError();
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
			LogPrintf(L"%d = %s", errorcode, (LPTSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
			continue;
		}

		WCHAR text[21];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buf, 20, text, 21);
		text[20] = 0;
		LogPrintf(L"Firmware Ver%02X%02X (%s )", buf[45], buf[44], text);

		//送受信バッファ確保
		m_InputBuf = (BYTE*)malloc(m_inputLen);
		m_OutputBuf = (BYTE*)malloc(m_outputLen);
		memset(m_OutputBuf, 0, m_outputLen);
		memset(m_InputBuf, 0, m_inputLen);
		if (m_bBluetooth) {
			m_OutputBuf[0] = 0x31;
			m_outputOffset = 1;
		}
		else {
			m_outputOffset = 0;
		}
		m_crcerrorcount = 0;
		m_write_count = m_write_count2 = 0;

		m_hThread = (HANDLE)_beginthreadex(NULL, 0, inputloop, this, 0, &m_threadID);
		m_hThread2 = (HANDLE)_beginthreadex(NULL, 0, outputloop, this, 0, &m_threadID2);
		if (m_hThread != 0 && m_hThread2 != 0) {
			SetThreadAffinityMask(m_hThread, 1);
			ret = true;
			break;
		}
		else {
			LogPrintf(I18N.FailedCreateThread);
		}
	}
	if (detail != 0)
		free(detail);
	if (!ret && hDS5Handle != INVALID_HANDLE_VALUE) {
		CloseHandle(hDS5Handle);
		hDS5Handle = INVALID_HANDLE_VALUE;
	}


	SetupDiDestroyDeviceInfoList(hDevInfo);
	return ret;
}

bool DS5Device::Close()
{
	if (m_hThread) {
		m_threadShutdown = true;
		WaitForSingleObject(m_hThread, INFINITE);
		m_write_cv.notify_one();
		WaitForSingleObject(m_hThread2, INFINITE);
		m_threadShutdown = false;
		m_hThread = NULL;
		m_hThread2 = NULL;
		m_write_count = m_write_count2 = 0;
	}
	if (hDS5Handle != INVALID_HANDLE_VALUE) {
		HANDLE tmp = hDS5Handle;
		hDS5Handle = INVALID_HANDLE_VALUE;
		CloseHandle(tmp);
	}
	if (m_OutputBuf != NULL) {
		free(m_OutputBuf);
		m_OutputBuf = NULL;
	}
	if (m_InputBuf != NULL) {
		free(m_InputBuf);
		m_InputBuf = NULL;
	}

	memset(m_DS5Serial, 0, sizeof(m_DS5Serial));
	return false;
}


//DS5からの受信ループ
void DS5Device::InputLoop()
{
	bool firstflag = true;
	while (!m_threadShutdown) {
		if (!_read()) {
			break;
		}
		if (m_receivedLength == 0) {
			LogPrintf(I18N.DisconnectController,L"DualSense");
			break;
		}
		if (!_parse()) {
			LogPrintf(I18N.FailedParse, L"DualSense");
			break;
		}
		if (firstflag) {
			LogPrintf(I18N.ConnectionStarted,L"DualSense");
			Write();
			firstflag = false;
		}
	}
	m_threadShutdown = true;

	if (hDS5Handle != INVALID_HANDLE_VALUE) {
		CloseHandle(hDS5Handle);
		hDS5Handle = INVALID_HANDLE_VALUE;
	}

}
//DS5への送信ループ
void DS5Device::OutputLoop()
{
	while (!m_threadShutdown) {
		while (m_write_count != m_write_count2) {
			m_write_count2 = m_write_count;
			if (!_prewrite()) {
				goto EndOutputLoop;
			}
		}
		std::unique_lock<std::mutex> lk(m_write_mutex);
		m_write_cv.wait(lk);
	}
	EndOutputLoop:
	m_threadShutdown = true;

}

//受信コールバック
void DS5Device::SetCallback(DS5InputCallback cb, void * param)
{
	m_callback = cb;
	m_callbackdata = param;
}


WCHAR * DS5Device::GetSerial()
{
	return m_DS5Serial;
}
//接続するDS5を指定
bool DS5Device::SetTargetSerial(const WCHAR * szTarget)
{
	if (lstrlenW(szTarget) + 1 > MAX_Serial_Length)
		return false;
	lstrcpyW(m_TargetSerial, szTarget);
	return true;
}

bool DS5Device::SetLED(BYTE R, BYTE G, BYTE B)
{
	m_Red = R;
	m_Green = G;
	m_Blue = B;
	return true;
}

bool DS5Device::SetMoter(BYTE left, BYTE right)
{
	m_Left = left;
	m_Right = right;
	return true;
}
//LEDとMotor情報を送信
bool DS5Device::_prewrite()
{
	if (hDS5Handle == INVALID_HANDLE_VALUE)
		return false;
	m_OutputBuf[m_outputOffset] = 0x02;
	m_OutputBuf[m_outputOffset+1] = 0x01 | 0x02;
	m_OutputBuf[m_outputOffset + 2] =  0x04 | 0x10 | 0x01;

	m_OutputBuf[m_outputOffset + 3] = m_Left;
	m_OutputBuf[m_outputOffset + 4] = m_Right;
	m_OutputBuf[m_outputOffset + 9] =0;

	m_OutputBuf[m_outputOffset + 39] = 2;
	m_OutputBuf[m_outputOffset + 42] = 2;
	m_OutputBuf[m_outputOffset + 45] = m_Red;
	m_OutputBuf[m_outputOffset + 46] = m_Green;
	m_OutputBuf[m_outputOffset + 47] = m_Blue;
	return _write();
}

//LEDとMotor情報を送信
bool DS5Device::_write()
{
	if (m_bBluetooth) {
		UINT32 crc = crc32_16bytes(m_OutputBuf, 74, 0xEADA2D49);
		m_OutputBuf[74] = (crc );
		m_OutputBuf[75] = (crc >> 8 );
		m_OutputBuf[76] = (crc >> 16);
		m_OutputBuf[77] = (crc >> 24);
	}
	ResetEvent(m_oWrite.hEvent);
	DWORD n;
	if (WriteFile(hDS5Handle, m_OutputBuf, m_bBluetooth?78:m_outputLen, &n, &m_oWrite)) {
		return true;
	}
	else if (GetLastError() == ERROR_IO_PENDING) {
		if (WaitForSingleObject(m_oWrite.hEvent, 5000) != WAIT_OBJECT_0) {
			if (hDS5Handle != INVALID_HANDLE_VALUE) {
				CancelIo(hDS5Handle);
				WaitForSingleObject(m_oWrite.hEvent, INFINITE);
			}
		}
		else {
			if (GetOverlappedResult(hDS5Handle, &m_oWrite, &n, false)) {
				return true;
			}
		}
	}
	DWORD errorcode = GetLastError();
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	switch (errorcode)
	{
	default:
		if (!m_threadShutdown && hDS5Handle != INVALID_HANDLE_VALUE)
			LogPrintf(I18N.FailedSendCmd, m_bBluetooth? L"DS5(BT)" :L"DS5(USB)", errorcode);
		break;
	}
	LogPrintf(L"%d = %s",errorcode,(LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
	return false;
}

//送信スレッドに命令するだけ
bool DS5Device::Write() {
	m_write_count++;
	m_write_cv.notify_one();
	return true;
}
//受信
bool DS5Device::_read()
{
	if (hDS5Handle == INVALID_HANDLE_VALUE)
		return false;
	DWORD n;
	ResetEvent(m_oRead.hEvent);
	if (ReadFile(hDS5Handle, m_InputBuf, m_inputLen, &n, &m_oRead)) {
		m_receivedLength = n;
		return true;
	}
	if (GetLastError() == ERROR_IO_PENDING) {
		if (WaitForSingleObject(m_oRead.hEvent, 5000) != WAIT_OBJECT_0) {
			if (hDS5Handle != INVALID_HANDLE_VALUE) {
				CancelIo(hDS5Handle);
				WaitForSingleObject(m_oRead.hEvent, INFINITE);
			}
		}
		else {
			if (GetOverlappedResult(hDS5Handle, &m_oRead, &n, false)) {
				m_receivedLength = n;
				return true;
			}
		}
	}
	DWORD errorcode = GetLastError();
	switch (errorcode)
	{
	case ERROR_DEVICE_NOT_CONNECTED:
		if (!m_threadShutdown&&hDS5Handle != INVALID_HANDLE_VALUE)
			LogPrintf(I18N.DeviceNotConnected);
		break;
	default:
		if (!m_threadShutdown&&hDS5Handle != INVALID_HANDLE_VALUE)
			LogPrintf(I18N.FailedRecv,L"DS5", errorcode);
		break;
	}
	return false;
}

//受信データのCRCチェック
bool DS5Device::_btcrc(){
	UINT32 crc = crc32_16bytes(m_InputBuf, 74, 0x73D37CF3);
	UINT32 src = *(UINT32*)&m_InputBuf[74];
	return crc == src;
}
//受信データの解析
bool DS5Device::_parse()
{

	//頭出し
	BYTE *buffer = m_InputBuf,
		*bufferEnd = m_InputBuf+ m_receivedLength;
	if (m_bBluetooth) {
		if (m_InputBuf[0] != 0x31) {
			return true;
		}
		buffer += 2;
	}
	else {
		if (m_InputBuf[0] != 0x01) {
			return true;
		}
		buffer += 1;
	}

	if (m_receivedLength < 42) {
		LogPrintf(L"受信データのサイズが足りませんでした。");
		return false;
	}

	//ボタンの状態
	memcpy(m_receivedData, buffer , 10);
	//m_receivedData[0] = buffer[0];
	m_receivedData[6] = 0;

	//Battery残量 タッチパッド
	memcpy(m_receivedData + 31, buffer + 31, 9);
	m_receivedData[52] = buffer[52];
	m_receivedData[53] = buffer[53];
	m_receivedData[54] = buffer[54];
	m_receivedData[55] = buffer[55];

	//状態が変化しているか判定
	BOOL updateflag = false;
	if (memcmp(m_receivedData, m_receivedLastData, MAX_Input_Length) != 0) {
		if (m_bBluetooth) {
			if (_btcrc()) {
				updateflag = true;
				if (m_crcerrorcount > 0) {
					LogPrintf(L"bt received data with crc error:%d", m_crcerrorcount);
				}
				m_crcerrorcount = 0;
			}
			else {
				m_crcerrorcount++;
				if (m_crcerrorcount % 500 == 0) {
					LogPrintf(L"bt received data with crc error=>%d", m_crcerrorcount);
				}
			}
		}
		else {
			updateflag = true;
		}
		if(updateflag)
			memcpy(m_receivedLastData, m_receivedData, MAX_Input_Length);
	}

	//コールバック
	if (m_callback) {
		m_callback(this,updateflag, m_callbackdata);
	}

	return true;
}
#pragma region get state

bool DS5Device::isBT()
{
	return m_bBluetooth;
}

int DS5Device::Battery()
{
	return (m_receivedData[OffsetBatteryLevel] & 0x0F) * 10;
}

bool DS5Device::BatteryCharge()
{
	return m_receivedData[OffsetBatteryLevel]&0x10 ? true : false;
}

bool DS5Device::BatteryFull()
{
	return m_receivedData[OffsetBatteryLevel] & 0x20 ? true : false;
}

void DS5Device::DisconnectBT()
{
	if (!Active() || !isBT())
		return;

	BLUETOOTH_ADDRESS ds5addr;
	int ic = 5;
	for (int i = 0; i < 12; i++) {
		BYTE hex = (BYTE)m_DS5Serial[i];
		if ('0' <= hex && hex <= '9') {
			hex -= '0';
		}
		else if ('a' <= hex && hex <= 'f') {
			hex -= 'a' - 10;
		}
		else if ('A' <= hex && hex <= 'F') {
			hex -= 'A' - 10;
		}
		else {
			hex = 0;
		}
		if (i & 1) {
			ds5addr.rgBytes[ic] |= hex;
			ic--;
		}
		else {
			ds5addr.rgBytes[ic] = hex << 4;
		}
	}
	Close();

	BLUETOOTH_FIND_RADIO_PARAMS param = { 0 };
	param.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);

	HANDLE radio = 0;
	HBLUETOOTH_RADIO_FIND find = BluetoothFindFirstRadio(&param, &radio);
	if (find) {
		do {
			BLUETOOTH_RADIO_INFO info = { 0 };
			info.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
			if (BluetoothGetRadioInfo(radio, &info) == ERROR_SUCCESS) {
				DWORD n;
				if (DeviceIoControl(radio, 0x41000c, &ds5addr, sizeof(ds5addr), 0, 0, &n, 0)) {
					CloseHandle(radio);
					return;
				}
			}
			CloseHandle(radio);
		} while (BluetoothFindNextRadio(find, &radio));
	}
}

DS5Button * DS5Device::GetButton(DS5ButtonID id)
{
	if(id >= DS5ButtonID::none && id < DS5ButtonID::button_Count && m_buttons[id].Enable())
		return &m_buttons[id];
	return &m_buttons[0];

}

bool DS5Device::TouchActive(int i)
{
	if (i != 0)i = 4;
	return (m_receivedData[OffsetTouch + i] & 0b10000000) == 0;
}

BYTE DS5Device::TouchId(int i)
{
	if (i != 0)i = 4;
	return m_receivedData[OffsetTouch + i] & 0b1111111;
}

int DS5Device::TouchX(int i)
{
	if (i != 0)i = 4;
	return ((m_receivedData[OffsetTouch + 2 + i] & 0x0F) << 8) | m_receivedData[OffsetTouch + 1 + i];
}

int DS5Device::TouchY(int i)
{
	if (i != 0)i = 4;
	return (m_receivedData[OffsetTouch + 2 + i] >> 4) | (m_receivedData[OffsetTouch + 3 + i] << 4);
}

void DS5Device::String()
{

	wchar_t buf[256];
	wchar_t *offset = buf;
	offset += wsprintfW(offset, L"F(%d(%d)%d,%d  %d(%d)%d,%d) ", TouchActive(0), TouchId(0), TouchX(0), TouchY(0)
		, TouchActive(1), TouchId(1), TouchX(1), TouchY(1));
	if (buf != offset) {
		LogPrintf(buf);
	}
}

#pragma endregion

