#pragma once
#include "shostdialogex.h"

#include <thread/threadex.h>
class SDriveDialog :
	public SHostDialogEx
{
public:
	SDriveDialog(void);
	~SDriveDialog(void);

	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btnInstall", OnBtnInstall)
		EVENT_NAME_COMMAND(L"btnRetry", OnBtnRetry)
		EVENT_NAME_COMMAND(L"btnOk", OnBtnOk)
		EVENT_NAME_COMMAND(L"btnCancel", OnBtnCancel)
		EVENT_ID_COMMAND(IDOK,OnBtnOk)
		EVENT_ID_COMMAND(IDCANCEL,OnBtnCancel)
	EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SMountDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
	CHAIN_MSG_MAP(SHostDialogEx)
	REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()


protected:
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	VOID OnBtnInstall();
	VOID OnBtnOk();
	VOID OnBtnCancel();
	VOID OnBtnRetry();

	void EndDialog();
private:
	BOOL InstallDrive();
private:
	STabCtrl* m_tableCtrl;
	CThreadEx m_thread;
};

