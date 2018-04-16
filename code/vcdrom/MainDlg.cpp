// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include "CDListAdapterFix.h"
#include <shlobj.h>
#include "VCDRomCtrl.h"
#include <thread/threadex.h>
CMainDlg::CMainDlg() : SHostWndEx(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	SShellNotifyIcon *notify = FindChildByID2<SShellNotifyIcon>(110);
	notify->ShowNotify(L"Hello SOUI",L"这可能是一个提示");

	//VirtualCDClient _VirtualCDClient;
	//return _VirtualCDClient.Valid();
	
	RefReshList();
	return 0;
}

void CMainDlg::OnLanguageBtnCN()
{
	OnLanguage(1);
}
void CMainDlg::OnLanguageBtnJP()
{
	OnLanguage(0);
}



HICON QueryExeIcon(LPCTSTR lpszExePath)
{
	HICON hIcon = NULL;
	SHFILEINFO FileInfo;
	DWORD_PTR dwRet = ::SHGetFileInfo(lpszExePath, 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_ICON|SHGFI_LARGEICON);
	// 目标文件不存在
		
	if (dwRet)
	{
		hIcon = FileInfo.hIcon;	
	}

	return hIcon;
}

void CMainDlg::OnListUnMount()
{
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	int nIndex = pLstViewFix->GetSel();
	if ( nIndex == -1 ) return ;

	if ( nIndex > m_cdList.size() ) return ;
	
	CD_ITEM item = m_cdList[nIndex];

	DisMount(item);
	
}

void CMainDlg::OnListMount()
{
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	int nIndex = pLstViewFix->GetSel();
	if ( nIndex == -1 ) return ;
	if ( nIndex > m_cdList.size() ) return ;

	CD_ITEM item = m_cdList[nIndex];



}

void CMainDlg::OnListRemove()
{
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	int nIndex = pLstViewFix->GetSel();
	if ( nIndex == -1 ) return ;
	if ( nIndex > m_cdList.size() ) return ;

	CD_ITEM item = m_cdList[nIndex];
}

VOID CMainDlg::DisMount(CD_ITEM item)
{
	if ( CVCDRomCtrl().IsMount( item.strPath ) )
	{
		Post([=]{
				SBusyDialog dlg;
				dlg.DoModal([=]{ CVCDRomCtrl().DisMount( item.strPath );});
			 });
		
	}
}

VOID CMainDlg::Mount(CD_ITEM item)
{
	if ( CVCDRomCtrl().IsMount( item.strPath ))
	{
		MessageBox(NULL, L"cuowu", L"cuo", MB_OK);
	}
	else
	{
		CThreadEx().Do([=]{
			//Post([=]{m_dlgBusy.DoModal();});
			CVCDRomCtrl().Mount( item.strPath , item.cDrive, FALSE);
			Post([=]{
				//m_dlgBusy.EndDialog( 0 );
				RefReshList();
			});
		});
	}
}

VOID CMainDlg::RefReshList()
{
	GetCDList();

	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	ILvAdapter *pAdapter = new CCDListAdapterFix(pLstViewFix, m_cdList);
	pLstViewFix->SetAdapter(pAdapter);
	pAdapter->Release();

}


SStringT GetLabel(CHAR cLatter)
{
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentLength;
	DWORD dwFileSystemFlags;
	TCHAR szFileSystemNameBuffer[MAX_PATH];      // #define BUF 1024
	TCHAR szDirveName[MAX_PATH];

	TCHAR szRootPath[] = _T("?:\\");
	szRootPath[0] = cLatter;

	if(!GetVolumeInformation(szRootPath,szDirveName,MAX_PATH,&dwVolumeSerialNumber,&dwMaximumComponentLength,&dwFileSystemFlags,szFileSystemNameBuffer,MAX_PATH))
	{
		return L"";
	}

	return  szDirveName;
}


HICON GetAtuoRunIcon( TCHAR DriveLetter)
{
	SStringT strIniPath;
	strIniPath.Format(L"%c:\\autorun.inf", DriveLetter);

	SStringT strValue;
	GetPrivateProfileString(L"AutoRun", L"icon", L"", strValue.GetBufferSetLength(MAX_PATH), MAX_PATH, strIniPath);
	strValue.ReleaseBuffer();

	SStringT strIcon;
	strIcon.Format(L"%c:\\%s", DriveLetter, strValue);

	strIcon.MakeLower();
	if ( strIcon.Find(L".exe"))
	{
		INT nIndex = 0;
		INT nPos = strIcon.Find(',');
		if ( nPos != -1)
		{
			nIndex = _ttoi( strIcon.Mid(nPos));
			strIcon = strIcon.Left(nPos);
		}

		HICON hLargeIcon = NULL, hSmallIcon = NULL;
		ExtractIconEx(strIcon, nIndex, &hLargeIcon, NULL, 1);
		
		return hLargeIcon;
	}
	else
		return SOUI::SApplication::getSingleton().LoadIcon(strIcon,32,32,TRUE );
}

BOOL CMainDlg::GetCDList()
{
	m_cdList.clear();

	VirtualCDClient _VirtualCDClient;
	VirtualCDClient::VirtualCDList _VirtualCDList = _VirtualCDClient.GetVirtualDiskList();
	for (VirtualCDClient::VirtualCDList::iterator it = _VirtualCDList.begin() ; it != _VirtualCDList.end() ; it++)
	{
		CD_ITEM item;
		item.strPath = it->ImageFile.c_str();
		item.cDrive = it->DriveLetter;
		item.strLabel = GetLabel( item.cDrive);
		item.bMount = TRUE;
		item.hIcon = GetAtuoRunIcon( item.cDrive);
		m_cdList.push_back(item);
	}

	return TRUE;
}

void CMainDlg::OnLanguage(int nID)
{
	ITranslatorMgr *pTransMgr = SApplication::getSingletonPtr()->GetTranslator();
	SASSERT(pTransMgr);
	bool bCnLang = nID == 1;

	pugi::xml_document xmlLang;
	if (SApplication::getSingletonPtr()->LoadXmlDocment(xmlLang, bCnLang ? _T("lang_cn") : _T("lang_jp"), _T("translator")))
	{
		CAutoRefPtr<ITranslator> lang;
		pTransMgr->CreateTranslator(&lang);
		lang->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
		pTransMgr->SetLanguage(lang->name());
		pTransMgr->InstallTranslator(lang);
		SDispatchMessage(UM_SETLANGUAGE,0,0);
	}
}

//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}


//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}
