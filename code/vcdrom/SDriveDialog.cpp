#include "StdAfx.h"
#include "SDriveDialog.h"
#include <msapi/mswinapi.h>
#include "VCDRomCtrl.h"

SDriveDialog::SDriveDialog(void):SHostDialogEx(L"XML_DLG_DRIVE")
{
}


SDriveDialog::~SDriveDialog(void)
{
}

BOOL SDriveDialog::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	m_tableCtrl = FindChildByName2<STabCtrl>(L"tblDrive");
	return TRUE;
}

VOID SDriveDialog::OnBtnInstall()
{
	m_tableCtrl->SetCurSel(L"install", FALSE);
	m_thread.Do([=]{
	
		BOOL bRet = InstallDrive();
		if ( bRet )
			Post([=]{m_tableCtrl->SetCurSel(L"finesh", FALSE);});
		else
			Post([=]{m_tableCtrl->SetCurSel(L"error", FALSE);});
	});
}

VOID SDriveDialog::OnBtnOk()
{
	EndDialog( );
}

VOID SDriveDialog::OnBtnCancel()
{
	EndDialog( );
}

VOID SDriveDialog::OnBtnRetry()
{
	OnBtnInstall();
}

void SDriveDialog::EndDialog()
{
	__super::EndDialog( CVCDRomCtrl().DeviceValid()?IDOK:IDCANCEL);
}

BOOL SDriveDialog::InstallDrive()
{
	if ( CVCDRomCtrl().DeviceValid() )
		return TRUE;
	
	SStringT strDevCmd;
	msapi::GetCurrentPath(strDevCmd.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strDevCmd.ReleaseBuffer();

	strDevCmd.Append(L"\\DevCmd.exe");

	msapi::ShellCommand(strDevCmd, -1, L"install_drv");

	return CVCDRomCtrl().DeviceValid();
}
