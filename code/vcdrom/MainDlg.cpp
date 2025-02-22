// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include "CDListAdapterFix.h"
#include <shlobj.h>
#include "VCDRomCtrl.h"
#include <thread/threadex.h>
#include <commdlg.h>
#include "SMountDialog.h"
#include <msapi/mswinapi.h>
#include <msapi/shellext.h>
#include <Dbt.h>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <msapi/msapp.h>
#include <msapi/mstime.h>
#include <iterator>
#include "SDriveDialog.h"
#include <network/HttpImplement.h>
#include "EnumAntivirus.h"
#include <util/cconv.h>
#include <util/vercmp.h>
#include <arith/AES.h>
#include <def.h>
#include "SErrorDialog.h"



#define _Def_AesKey "asdfwetyhjuytrfd" //str_encode_embed<19,'a','s','d','f','w','e','t','y','h','j','u','y','t','r','f','d'>()
#define _Def_AesVi  "gfdertfghjkuyrtg"// str_encode_embed<20,'g','f','d','e','r','t','f','g','h','j','k','u','y','r','t','g'>()
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

DWORD WINAPI PipeNotifyCallBack(LPVOID lpThis,LPVOID lpInBuff,DWORD dwInBuffSize,LPVOID lpOutBuff,DWORD& dwOutBuffSize)
{
	CMainDlg* pDlg = (CMainDlg*)lpThis;
	if ( pDlg )
	{
		//MessageBox(NULL, (LPWSTR)lpInBuff, L"TS", MB_OK);

		LPCTSTR lpszFileName = NULL;
		if ( dwInBuffSize > 4 )
		{
			lpszFileName = (LPWSTR)lpInBuff;
		}
		pDlg->NewAppRun( lpszFileName );
	}
	return 0;
}

#include<util/msvector.h>
VOID CMainDlg::ActiveReport()
{
	msdk::network::CUrlParamValueMap ParamValueMap;
	ParamValueMap["apiver"]			=		1;					//当前API版本
	ParamValueMap["hdd"]			=		msapi::CApp::GetDiskSerial();
	ParamValueMap["uguid"]			=		msapi::CApp::GetUserGuid();
	ParamValueMap["mac"]			=		CGetNetAdapterInfo::GetMac();

	ParamValueMap["osver"]			=		msapi::GetMicroVersion();
	ParamValueMap["wow64"]			=		msapi::IsWindowsX64();

	ParamValueMap["ant"]			=		msapi::CEnumAntivirus().Enum();
	ParamValueMap["prod"]			=		_Def_Prod;
	ParamValueMap["packet"]			=		_Def_Packet;
	ParamValueMap["subprod"]		=		0;	//当前模块的子产品
	ParamValueMap["idate"]			=		msapi::GetCurrentDateStr(FALSE);
	ParamValueMap["itime"]			=		msapi::GetCurrentDateStr(FALSE);
	ParamValueMap["prodver"]		=		_Def_Version;
	ParamValueMap["oper"]			=		GetOper();
	ParamValueMap["random"]			=		GetTickCount();
	msdk::network::CHttpImplement HttpImpl;
	HttpImpl.GetRequest(_Def_UpdateHost, 80, "active" , ParamValueMap);
	CApiVector<DWORD> kVector;
	for (DWORD i = 0; i < 10; i++)
	{
		//kVector.Insert(0, i);
	}
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	SShellNotifyIcon *notify = FindChildByID2<SShellNotifyIcon>(110);
	//notify->ShowNotify(L"Hello SOUI",L"这可能是一个提示");

	CThreadEx().Do([=]{ActiveReport();});
	m_CommFunc = GetStaticCommonObject();
	if ( m_CommFunc )
	{
		m_CommFunc->ICFStartNamedPipeServer( NAMEDPIPE_NAME_VCDROM, 100, PipeNotifyCallBack, this);
	}

	TCHAR strFile[ MAX_PATH ] = { 0 };
	GetModuleFileName( NULL, strFile, MAX_PATH );

	msapi::GetPeFileDetail( strFile, L"080404b0", m_updateInfo.strLocVer.GetBufferSetLength(MAX_PATH), MAX_PATH );
	m_updateInfo.strLocVer.ReleaseBuffer();

	//这里的逻辑需要优化
	if ( !CVCDRomCtrl().DeviceValid() )
	{
		Post([=]{
			SDriveDialog dlg;
			if ( dlg.DoModal(hWnd) == IDOK)
			{
				if ( lParam )
					Mount( (LPCTSTR) lParam);
				
				RefReshList();
			}

			DoUpdate( FALSE );
		});	
	}
	else
	{
		DoUpdate( FALSE );
		if ( lParam )
		{
			Post([=]{
				Mount( (LPCTSTR) lParam);
			});
		}
		
		RefReshList();
	}
	
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

BOOL ShowMountDlg( SStringT sTitle,TCHAR& cMount, BOOL& bAutoRun)
{
	SMountDialog dlg;
	dlg.SetFileName(sTitle);
	UINT nRet = dlg.DoModal();
	cMount = dlg.GetMountLetter();
	bAutoRun = dlg.IsOpen();
	return nRet == IDOK;
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

	Post([=]{
		DisMount(item);
	});
	
	
}

void CMainDlg::OnListMount()
{
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	int nIndex = pLstViewFix->GetSel();
	if ( nIndex == -1 ) return ;
	if ( nIndex > m_cdList.size() ) return ;

	CD_ITEM item = m_cdList[nIndex];

	if ( !CVCDRomCtrl().IsMount( item.strPath ))
	{
		BOOL bRun = FALSE;
		TCHAR cLetter = 0;
		if ( ShowMountDlg(PathFindFileName(item.strPath), cLetter, bRun))
		{
			Post([=]{
					Mount( item.strPath, cLetter, bRun);
			});

		}
	}
}

void CMainDlg::OnListRemove()
{
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	int nIndex = pLstViewFix->GetSel();
	if ( nIndex == -1 ) return ;
	if ( nIndex > m_cdList.size() ) return ;

	CD_ITEM item = m_cdList[nIndex];

	Post([=]{

		m_cdList.erase(remove(m_cdList.begin(),m_cdList.end(),item),m_cdList.end());//重点  

		SaveHistory(m_cdList);
		if ( CVCDRomCtrl().IsMount( item.strPath ))
			DisMount(item);
		else
			RefReshList();
	});
}



void CMainDlg::OnListOpen()
{
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	int nIndex = pLstViewFix->GetSel();
	if ( nIndex == -1 ) return ;
	if ( nIndex > m_cdList.size() ) return ;

	CD_ITEM item = m_cdList[nIndex];

	msapi::ShellOpenFolder(SStringT().AppendFormat(L"%c:\\", item.cDrive));
}

VOID CMainDlg::OnBtnSelImage()
{
	TCHAR szBuffer[MAX_PATH] = {0};   
	OPENFILENAME ofn= {0};   
	ofn.lStructSize = sizeof(ofn);   
	ofn.hwndOwner = m_hWnd;   
	ofn.lpstrFilter = _T("所有支持的文件(*.iso;*.nrg;*.mds;*.mdf;*.img;*.cue;*.ccd)\0*.iso;*.nrg;*.mds;*.mdf;*.img;*.cue;*.ccd\0")\
		_T("ISO文件(*.iso)\0*.iso\0")\
		_T("NRG文件(*.nrg)\0*.nrg\0")\
		_T("MDS文件(*.mds)\0*.mds\0")\
		_T("MDF文件(*.mdf)\0*.mdf\0")\
		_T("IMG文件(*.img)\0*.img\0")\
		_T("CUE文件(*.cue)\0*.cue\0")\
		_T("CCD文件(*.ccd)\0*.ccd\0");


	TCHAR szDocPath[MAX_PATH] = { 0 };
	SHGetSpecialFolderPath(NULL, szDocPath, CSIDL_MYDOCUMENTS ,FALSE);

	ofn.lpstrInitialDir = szDocPath;//默认的文件路径   
	ofn.lpstrFile = szBuffer;//存放文件的缓冲区   
	ofn.nMaxFile = sizeof(szBuffer)/sizeof(*szBuffer);   
	ofn.nFilterIndex = 0;   
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER ;//标志如果是多选要加上OFN_ALLOWMULTISELECT  

	if ( GetOpenFileName(&ofn) )
	{
		Mount( szBuffer );
	}
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

SStringT GetCurrentTimeStr()
{
	SStringT strTime;
	msapi::GetCurrentDataTimeStr(strTime.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strTime.ReleaseBuffer();
	return strTime;
}



VOID CMainDlg::OnBtnRemoveAll()
{
	OnBtnUnMountAll();
	m_cdList.clear();

	SaveHistory(m_cdList);
	RefReshList();
}

VOID CMainDlg::OnBtnUnMountAll()
{
	if ( CVCDRomCtrl().DeviceValid() )
	{
		SBusyDialog dlg;
		dlg.DoModal([=]{ CVCDRomCtrl().DisMountAll( );});
		RefReshList();
	}
}

LRESULT CMainDlg::OnDeviceChange(UINT msg, WPARAM wCode, LPARAM hwndCtl, BOOL& bHandled)
{
	switch( wCode )
	{
	case DBT_DEVICEREMOVECOMPLETE:
	case DBT_DEVICEARRIVAL:
		{

		}
		RefReshList();
	}
	return 0;
}

VOID CMainDlg::DisMount(CD_ITEM item)
{
	if ( CVCDRomCtrl().IsMount( item.strPath ) )
	{
		SBusyDialog dlg;
		dlg.DoModal([=]{ CVCDRomCtrl().DisMount( item.strPath );});
		RefReshList();
	}
}



VOID CMainDlg::Mount(LPCTSTR lpszFile, TCHAR cLetter, BOOL bOpen)
{
	if ( CVCDRomCtrl().IsMount( lpszFile ))
	{
		msapi::ShellOpenFolder(SStringT().AppendFormat(L"%c:\\", cLetter));
	}
	else
	{
		SBusyDialog busyDlg;
		HRESULT hRet = S_FALSE;
		busyDlg.DoModal( [=,&hRet]{
			hRet = CVCDRomCtrl().Mount( lpszFile , cLetter, FALSE);
		} );

		if ( hRet != S_OK )
		{
			SErrorDialog e;
			e.DoModal();
		}
		else
		{
			CD_ITEM item;
			item.strPath = lpszFile;
		
			//只要从history中移除就行了
			CCDList::iterator pos = find(m_cdList.begin(), m_cdList.end(), item);
			if ( pos != m_cdList.end() )
			{
				pos->strTime = GetCurrentTimeStr();
				SaveHistory(m_cdList);
			}

			RefReshList();
			//需要修改一下挂载时间

			if ( bOpen )
			{
				msapi::ShellOpenFolder(SStringT().AppendFormat(L"%c:\\", cLetter));
			}
		}
	}
}

VOID CMainDlg::Mount(LPCTSTR lpszFile)
{
	if ( CVCDRomCtrl().IsMount( lpszFile ) )
	{
		msapi::ShellOpenFolder(SStringT().AppendFormat(L"%c:\\", CVCDRomCtrl().GetMountLatter(lpszFile)));
	}
	else
	{
		BOOL bRun = FALSE;
		TCHAR cLetter = 0;
		if ( ShowMountDlg(PathFindFileName(lpszFile), cLetter, bRun))
		{
			Mount( lpszFile, cLetter, bRun);
		}
	}
}

VOID CMainDlg::RefReshList()
{
	if ( !CVCDRomCtrl().DeviceValid() )
		return ;

	GetCDList();
	SListView *pLstViewFix = FindChildByName2<SListView>("lv_cd_fix");
	ILvAdapter *pAdapter = new CCDListAdapterFix(pLstViewFix, m_cdList);
	pLstViewFix->SetAdapter(pAdapter);
	pAdapter->Release();
}




VOID CMainDlg::GetHistroyList(CCDList& hList)
{
	SStringT strJsonFile;
	SHGetSpecialFolderPath(NULL, strJsonFile.GetBufferSetLength(MAX_PATH), CSIDL_APPDATA, TRUE);
	strJsonFile.ReleaseBuffer();
	strJsonFile.Append(L"\\VCDRom\\history.json");
	msapi::CreateDirectoryEx( strJsonFile);

	ifstream  sstream(strJsonFile);
	Json::Value Root;
	if ( Json::Reader().parse(sstream, Root, true) )
	{
		for ( int nLoop = 0 ; nLoop < Root.size() ; nLoop++)
		{
			Json::Value item = Root[nLoop];
			CD_ITEM cdItem;
			cdItem.strLabel = item["label"].asWString().c_str();
			cdItem.strPath = item["path"].asWString().c_str();
			cdItem.strTime = item["time"].asWString().c_str();

			hList.push_back(cdItem);
		}
	}
}

VOID CMainDlg::GetMountList(CCDList& mList, const CCDList& hList)
{
	std::function<CD_ITEM( LPCTSTR lpszFile )> FindHistory = [=]( LPCTSTR lpszFile) -> CD_ITEM
	{
		CD_ITEM item;
		item.strPath = lpszFile;
		CCDList::const_iterator it = find(hList.begin(), hList.end(), item);
		if ( it != hList.end() )
		{
			return *it;
		}
		
		return CD_ITEM();
	};


	VirtualCDClient _VirtualCDClient;
	VirtualCDClient::VirtualCDList _VirtualCDList = _VirtualCDClient.GetVirtualDiskList();
	for (VirtualCDClient::VirtualCDList::iterator it = _VirtualCDList.begin() ; it != _VirtualCDList.end() ; it++)
	{
		CD_ITEM item = FindHistory( it->ImageFile.c_str());
		item.strPath = it->ImageFile.c_str();
		item.cDrive = it->DriveLetter;
		item.strLabel = GetLabel( item.cDrive);
		item.bMount = TRUE;
		item.hIcon = GetAtuoRunIcon( item.cDrive);
		if ( item.strTime.GetLength() == 0)
		{
			msapi::GetCurrentDataTimeStr(item.strTime.GetBufferSetLength(MAX_PATH), MAX_PATH);
			item.strTime.ReleaseBuffer();
		}
		mList.push_back(item);
	}
}



VOID CMainDlg::SaveHistory(CCDList& List)
{
	Json::Value values;
	for ( int nLoop = 0 ; nLoop < List.size() ; nLoop++)
	{
		CD_ITEM item = List[nLoop];
		Json::Value value;
		value["time"] = (LPCTSTR)item.strTime;
		value["label"] = (LPCTSTR)item.strLabel;
		value["path"] = (LPCTSTR)item.strPath;
		values[nLoop] = value;
	}

	SStringT strJsonFile;
	SHGetSpecialFolderPath(NULL, strJsonFile.GetBufferSetLength(MAX_PATH), CSIDL_APPDATA, TRUE);
	strJsonFile.ReleaseBuffer();
	strJsonFile.Append(L"\\VCDRom\\history.json");
	msapi::CreateDirectoryEx( strJsonFile);

	ofstream  sstream(strJsonFile);
	Json::StyledStreamWriter().write(sstream, values);
}

bool static decrease(const CD_ITEM &foo1, const CD_ITEM &foo2)
{
	if ( foo1.bMount && foo2.bMount )
	{
		if ( foo1.cDrive < foo2.cDrive)
			return true;
		else
			return false;
	}

	if ( foo1.bMount )
	{
		return true;
	}

	
	return false;
}

BOOL CMainDlg::GetCDList()
{

	std::function<bool(CCDList& listMount, CD_ITEM& item )> IsExist = [=](CCDList& listMount, CD_ITEM& item) -> bool
	{
		CCDList::const_iterator it = find(listMount.begin(), listMount.end(), item);
		if ( it != listMount.end() )
			return true;

		return false;
	};

	m_cdList.clear();
	CCDList listMount, listHistory;
	GetHistroyList(listHistory);
	GetMountList(listMount, listHistory);
	
	m_cdList = listMount;

	for ( CCDList::iterator it = listHistory.begin() ; it != listHistory.end() ; it++)
	{
		if ( !IsExist(listMount, *it))
		{
			m_cdList.push_back(*it);
		}
	}
	

	
	sort(m_cdList.begin(), m_cdList.end(), decrease);
	return TRUE;
}



VOID CMainDlg::NewAppRun(LPCTSTR lpstrParam)
{
	ShowActiveWindow();
	if ( PathFileExists( lpstrParam ) )
	{
		SStringT strFile = lpstrParam;
		Post([=]{
			Mount(strFile);
		});
	}
}

BOOL CMainDlg::ShowActiveWindow()
{
	BOOL isZoom = ::IsZoomed(this->m_hWnd);
	this->ShowWindow( SW_SHOW );
	SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); 
	::SetForegroundWindow(m_hWnd);
	::SetActiveWindow(m_hWnd);
	return TRUE;
}

BOOL CMainDlg::DoUpdate(  BOOL bForce /*= FALSE*/ )
{
	CThreadEx().Do([=]{
		if ( CheckUpdate() )
		{
			if ( CVerCmp::CompareStr( m_updateInfo.strVersion , m_updateInfo.strLocVer ) > 0 )
			{
				if( !bForce && dlgUpdate::IsSkip( m_updateInfo.strVersion ) )
					return ;
	
				Post([=]{

					dlgUpdate dlg( m_updateInfo );
					if ( dlg.DoModal( m_hWnd) == IDCANCEL)
					{
						if ( m_updateInfo.bForce )
						{
							TerminateProcess( GetCurrentProcess(), 0);
						}
					}
				});
			}
		}
		//判断升级
	});

	return TRUE;
}

BOOL CMainDlg::CheckUpdate()
{
	network::CHttpImplement HttpImpl;
	network::CUrlParamValueMap ParamValueMap;

	ParamValueMap["apiver"]			=		1;					//当前API版本
	ParamValueMap["hdd"]			=		msapi::CApp::GetDiskSerial();
	ParamValueMap["uguid"]			=		msapi::CApp::GetUserGuid();
	ParamValueMap["mac"]			=		CGetNetAdapterInfo::GetMac();

	ParamValueMap["osver"]			=		msapi::GetMicroVersion();
	ParamValueMap["wow64"]			=		msapi::IsWindowsX64();

	ParamValueMap["ant"]			=		msapi::CEnumAntivirus().Enum();
	ParamValueMap["prod"]			=		_Def_Prod;
	ParamValueMap["packet"]			=		_Def_Packet;
	ParamValueMap["subprod"]		=		0;	//当前模块的子产品
	ParamValueMap["idate"]			=		msapi::GetCurrentDateStr(FALSE);
	ParamValueMap["itime"]			=		msapi::GetCurrentDateStr(FALSE);
	ParamValueMap["prodver"]		=		_Def_Version;
	ParamValueMap["oper"]			=		GetOper();

	Json::Value Root;
	if ( HttpImpl.PostRequest( _Def_ApiHost, 80, _Def_Update_NetApi,ParamValueMap) )
	{
		return FALSE;
	}

	if ( !(HttpImpl.GetRequestLength() && HttpImpl.GetRequestData()) )
	{
		return FALSE;
	}
	std::string sJson = (const char*)HttpImpl.GetRequestData();
	sJson = AES::DecryptionAES(_Def_AesKey, _Def_AesVi,sJson);
	if ( !Json::Reader().parse( sJson, Root) )
		return FALSE;

	if ( Root["version"].isString() )
	{
		m_updateInfo.strVersion	= utf82w(Root["version"].asString()).c_str();
	}

	if ( Root["url"].isString())
	{
		m_updateInfo.strUrl	= utf82w(Root["url"].asString()).c_str();
	}
	if ( Root["Param"].isString())
	{
		m_updateInfo.strParam	= utf82w(Root["Param"].asString()).c_str();
	}

	if ( Root["content"].isString())
	{
		m_updateInfo.strContent	= utf82w(Root["content"].asString()).c_str();
	}

	if ( Root["webhost"].isString())
	{
		m_updateInfo.strWebHost	= utf82w(Root["webhost"].asString()).c_str();
	}

	if ( Root["force"].asBool() )
	{
		m_updateInfo.bForce	= Root["force"].asBool();
	}

	return TRUE;
}

DWORD CMainDlg::GetOper()
{
	SStringT strIniFile;
	msapi::GetCurrentPath(strIniFile.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strIniFile.ReleaseBuffer();
	strIniFile.Append(L"\\setting.ini");

	return GetPrivateProfileInt( L"Setting", L"Oper", _Def_Oper, strIniFile);
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
		//pTransMgr->SetLanguage(lang->name());
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
