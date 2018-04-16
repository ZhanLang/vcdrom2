#include "StdAfx.h"
#include "VCDRomCtrl.h"


CVCDRomCtrl::CVCDRomCtrl(void)
{
}


CVCDRomCtrl::~CVCDRomCtrl(void)
{
}

HRESULT CVCDRomCtrl::DisMount(LPCWSTR lpszFile)
{
	wchar_t wszKernelPath[512];
	if (!VirtualCDClient::Win32FileNameToKernelFileName(lpszFile, wszKernelPath, __countof(wszKernelPath)))
		return FALSE;

	VirtualCDClient _VirtualCDClient;
	return _VirtualCDClient.DisconnectDisk(wszKernelPath).ConvertToHResult();
}


HRESULT CVCDRomCtrl::Mount(LPCWSTR lpDiskPath, CHAR cLatter, BOOL bMountRestart/* = TRUE*/)
{
	wchar_t wszKernelPath[512];
	if (!VirtualCDClient::Win32FileNameToKernelFileName(lpDiskPath, wszKernelPath, __countof(wszKernelPath)))
		return E_FAIL;

	VirtualCDClient _VirtualCDClient;
	RASSERT( _VirtualCDClient.Valid() , E_ACCESSDENIED);
	RASSERT(!_VirtualCDClient.IsDiskConnected(wszKernelPath), E_ABORT);

	BOOL bFindLatter = FALSE;
	VirtualCDClient::VirtualCDList _VirtualCDList = _VirtualCDClient.GetVirtualDiskList();
	for (VirtualCDClient::VirtualCDList::iterator it = _VirtualCDList.begin() ; it != _VirtualCDList.end() ; it++)
	{
		if ( it->DriveLetter == cLatter )
		{
			bFindLatter = TRUE;
			break;
		}
	}

	HRESULT hr = E_FAIL;
	if ( bFindLatter )
		hr = VirtualCDClient::MountImageOnExistingDrive(wszKernelPath, cLatter).ConvertToHResult();
	else
		hr = _VirtualCDClient.ConnectDisk(wszKernelPath, cLatter, 10000, false, bMountRestart ? true : false, NULL, mpInvalid).ConvertToHResult();

	if ( FAILED( hr ))
	{
		//GrpError(GroupName, MsgLevel_Error, _T("×°ÔØ¾µÏñÊ§°Ü:%s,%c"), wszKernelPath, cLatter);
	}

	return hr;
}

BOOL CVCDRomCtrl::IsMount(LPCWSTR lpDiskPath)
{
	wchar_t wszKernelPath[512];
	if (!VirtualCDClient::Win32FileNameToKernelFileName(lpDiskPath, wszKernelPath, __countof(wszKernelPath)))
		return FALSE;

	VirtualCDClient _VirtualCDClient;
	return _VirtualCDClient.IsDiskConnected(wszKernelPath) == true;
}