#pragma once
#include "stdafx.h"
#include <shlobj.h>
#include <shlguid.h>

WCHAR* StartUpPath()
{
	static WCHAR lnkfile[MAX_PATH] = { 0 };
	if (lnkfile[0] != 0)
		return lnkfile;
	LPITEMIDLIST piil;
	if (SUCCEEDED(SHGetFolderLocation(NULL, CSIDL_STARTUP, NULL, NULL, &piil)))
	{
		WCHAR startuppath[MAX_PATH];
		if (SHGetPathFromIDList(piil, startuppath))
			wsprintf(lnkfile, L"%s\\Ds2vJoy.lnk", startuppath);
		CoTaskMemFree(piil);
	}
	return lnkfile;
}

HRESULT CreateLink(LPCWSTR lpszPathObj, LPCWSTR lpszPathLink, LPCWSTR lpszDesc)
{
	HRESULT hres;
	IShellLink* psl;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres))
	{
		WCHAR work[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, work);
		IPersistFile* ppf;
		psl->SetPath(lpszPathObj);
		psl->SetDescription(lpszDesc);
		psl->SetShowCmd(SW_SHOWMINNOACTIVE);
		psl->SetWorkingDirectory(work);
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if (SUCCEEDED(hres))
		{
			hres = ppf->Save(lpszPathLink, TRUE);
			ppf->Release();
		}
		psl->Release();
	}
	return hres;
}

BOOL CreateStartUp()
{
	WCHAR* lnk = StartUpPath();
	if (lnk[0] == 0)
		return FALSE;

	WCHAR exefile[MAX_PATH];
	GetModuleFileName(NULL, exefile, MAX_PATH);

	CoInitialize(NULL);
	CreateLink(exefile, lnk, L"Ds2vJoy");
	CoUninitialize();
	return TRUE;
}

BOOL CheckStartUp()
{
	WCHAR* lnk = StartUpPath();
	if (lnk[0] == 0)
		return FALSE;

	HANDLE hFile = CreateFile(lnk, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	CloseHandle(hFile);
	return TRUE;
}

BOOL DeleteStartUp()
{
	WCHAR* lnk = StartUpPath();
	if (lnk[0] == 0)
		return FALSE;
	DeleteFile(lnk);
	return TRUE;
}
