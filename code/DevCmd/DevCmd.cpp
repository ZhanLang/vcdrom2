// DevCmd.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "DevCmd.h"
#include <process/ParseCommand.h>
#include <VirtualCDClient.h>
#include <msapi/mspath.h>
#include <msapi/mswinapi.h>

using namespace msdk;

STDMETHODIMP UninstallDriver()
{
	if ( VirtualCDClient().Valid() )
		return S_OK;
	TCHAR szCurPath[ MAX_PATH] = { 0 };
	CString strCurPath = msapi::GetCurrentPath(szCurPath, MAX_PATH);
	CString strDevConPath;
	CString strCmd;

	if (msapi::IsWindowsX64())
		strDevConPath.Format(_T("%s\\drive\\devcon_x64.exe"), strCurPath.GetBuffer());
	else
		strDevConPath.Format(_T("%s\\drive\\devcon_x86.exe"), strCurPath.GetBuffer());

	strCmd.Format(_T("\"%s\" remove root\\vcdrombus" ), strDevConPath.GetBuffer());

	DWORD dwRet = msapi::Execute(strDevConPath, strCmd, TRUE, FALSE, INFINITE);
	if ( dwRet != 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL InstallDrv()
{
	if ( VirtualCDClient().Valid())
		return S_OK;

	UninstallDriver();
	TCHAR szCurPath[ MAX_PATH] = { 0 };
	CString strCurPath = msapi::GetCurrentPath(szCurPath, MAX_PATH);
	CString strDevConPath;
	CString strInfPath;
	CString strCmd;

	if (msapi::IsWindowsX64())
		strDevConPath.Format(_T("%s\\drive\\devcon_x64.exe"), strCurPath.GetBuffer());
	else
		strDevConPath.Format(_T("%s\\drive\\devcon_x86.exe"), strCurPath.GetBuffer());


	//���ȳ�sha1
	if ( msapi::IsWindowsX64() &&
		(msapi::GetMicroVersion() == msapi::MicroVersion_Win7 || msapi::GetMicroVersion() == msapi::MicroVersion_Win7_SP1))
	{
		strInfPath.Format(_T("%s\\drive\\sha1\\VCDRomBus.inf"), strCurPath.GetBuffer());
		strCmd.Format(_T("install \"%s\" root\\vcdrombus" ),strInfPath.GetBuffer());
	}
	else
	{
		strInfPath.Format(_T("%s\\drive\\sha256\\VCDRomBus.inf"), strCurPath.GetBuffer());
		strCmd.Format(_T("install \"%s\" root\\vcdrombus" ), strInfPath.GetBuffer());
	}

	OutputDebugString(L"���԰�װSHA1������");
	DWORD dwRet = WaitForSingleObject(msapi::ShellProcess(strDevConPath, strCmd,FALSE),INFINITE);

	Sleep(2000);

	if ( VirtualCDClient().Valid() )
	{
		OutputDebugString(L"���԰�װSHA1�����ɹ�");
		return TRUE;
	}
	else
		OutputDebugString(L"���԰�װSHA1����ʧ��");

	strInfPath.Format(_T("%s\\drive\\sha256\\VCDRomBus.inf"), strCurPath.GetBuffer());
	strCmd.Format(_T("install \"%s\" root\\vcdrombus" ), strInfPath.GetBuffer());

	OutputDebugString(L"���԰�װSHA256������");
	OutputDebugString(strDevConPath);
	OutputDebugString(strCmd);
	dwRet = WaitForSingleObject(msapi::ShellProcess(strDevConPath, strCmd,FALSE),INFINITE);
	Sleep(2000);
	if ( VirtualCDClient().Valid() )
	{
		OutputDebugString(L"���԰�װSHA256�����ɹ�");
		return TRUE;
	}
	else
		OutputDebugString(L"���԰�װSHA256����ʧ��");

	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CParseCommand ParseCmd(TRUE);
	if ( ParseCmd.IsExist(_T("install_drv")))
	{
			if ( VirtualCDClient().Valid() )
				return TRUE;

			InstallDrv();

			if ( VirtualCDClient().Valid())
				return TRUE;
	}

	return 0;
}