// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "SHostWndEx.h"
#include "CDListAdapterFix.h"
#include "SBusyDialog.h"
#include "dlgUpdate.h"

#include <cscomm/ICommunicateFunc.h>

 #define NAMEDPIPE_NAME_VCDROM					L"\\\\.\\Pipe\\{A9FA3E63-39DB-4FFA-B68E-02F806C95B25}"

class CMainDlg : public SHostWndEx
{
public:
	CMainDlg( );
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	//托盘通知消息处理函数
	//LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
	//演示如何响应菜单事件
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	//virtual void RequestRelayout(SWindow *pSource ,BOOL bSourceResizable );
protected:
	void OnLanguage(int nID);
	void OnLanguageBtnCN();
	void OnLanguageBtnJP();
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"zh_cn", OnLanguageBtnCN)
		EVENT_NAME_COMMAND(L"jp", OnLanguageBtnJP)

		EVENT_NAME_COMMAND(L"listUnmount", OnListUnMount)
		EVENT_NAME_COMMAND(L"listMount", OnListMount)
		EVENT_NAME_COMMAND(L"ListRemove", OnListRemove)
		EVENT_NAME_COMMAND(L"listOpen", OnListOpen)
		EVENT_NAME_COMMAND(L"BtnselImage", OnBtnSelImage)
		EVENT_NAME_COMMAND(L"BtnRemoveAll", OnBtnRemoveAll)
		EVENT_NAME_COMMAND(L"BtnUnMountAll", OnBtnUnMountAll)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
	//托盘消息处理
		//MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
		MSG_WM_COMMAND(OnCommand)
		MESSAGE_HANDLER(WM_DEVICECHANGE, OnDeviceChange)
		CHAIN_MSG_MAP(SHostWndEx)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	void OnListUnMount();
	void OnListMount();
	void OnListRemove();
	void OnListOpen();
	VOID OnBtnSelImage();
	VOID OnBtnRemoveAll();
	VOID OnBtnUnMountAll();

	LRESULT OnDeviceChange( UINT msg, WPARAM wCode, LPARAM hwndCtl, BOOL& bHandled);
public:
	VOID DisMount( CD_ITEM item);
	VOID Mount( LPCTSTR lpszFile, TCHAR cLetter, BOOL bOpen);
	VOID Mount( LPCTSTR lpszFile);
	VOID NewAppRun( LPCTSTR lpstrParam);
	BOOL ShowActiveWindow();
private:
	VOID RefReshList();

	VOID GetHistroyList( CCDList& hList);
	VOID GetMountList( CCDList& mList, const CCDList& hList);
	VOID SaveHistory(CCDList& List);

	BOOL GetCDList();
	VOID ModifyHistory( CD_ITEM item, BOOL bDel =FALSE);
	VOID LoadHistory();

	
private:
	BOOL DoUpdate( BOOL bForce = FALSE);
	BOOL CheckUpdate();
	DWORD GetOper();
	VOID ActiveReport();
private:
	BOOL			m_bLayoutInited;	
	CCDList			m_cdList;
	UPDATE_INFO		m_updateInfo;

	ICommunicateFunc* m_CommFunc;
};
