#include "StdAfx.h"
#include "dlgUpdate.h"
#include "Downloader.h"
#include <msapi\mswinapi.h>

#include <msapi/msapp.h>
#include <Def.h>


dlgUpdate::dlgUpdate(UPDATE_INFO updateInfo):SHostDialogEx(L"XML_DLG_UPDATE")
{
	m_updateInfo = updateInfo;
}

dlgUpdate::~dlgUpdate(void)
{

}



BOOL dlgUpdate::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{


	SCheckBox * pSkip = FindChildByName2<SCheckBox>(L"skipCheck");
	pSkip->SetCheck( IsSkip( m_updateInfo.strVersion ) );
	
	if ( m_updateInfo.strWebHost.GetLength() )
	{
		FindChildByName2<SLink>(L"updateWebUrl")->SetAttribute(L"href", m_updateInfo.strWebHost);
	}

	if ( m_updateInfo.strContent.GetLength() )
	{
		FindChildByName(L"updateContent")->SetWindowText( m_updateInfo.strContent);
	}

	return TRUE;
}

VOID dlgUpdate::SkinUpdate(LPCTSTR lpszVer)
{
	msapi::CApp(_DefAppName).SetSetting( L"skip", lpszVer);
}

BOOL dlgUpdate::IsSkip(LPCTSTR lpszVer)
{
	SStringT strVer;
	msapi::CApp(_DefAppName).GetSetting(L"skip", L"", strVer.GetBufferSetLength(MAX_PATH), MAX_PATH );
	strVer.ReleaseBuffer();

	return strVer.CompareNoCase(lpszVer) == 0;
}

VOID dlgUpdate::OnBtnUpdate()
{
	STabCtrl* pTable = FindChildByName2<STabCtrl>(L"tabUpdate");
	pTable->SetCurSel( 1 );

	m_downThread.Do([=]
	{ 
		BOOL bRet = DoUpdate();
		Post([=]{
			if ( bRet )
				pTable->SetCurSel( 2 );
			else
				pTable->SetCurSel( 3 );
		});
	});
}

VOID dlgUpdate::OnBtnOk()
{
	
	EndDialog( IDOK );
}

VOID dlgUpdate::OnBtnCancel()
{
	m_downThread.WaitForExit( 0 );
	EndDialog( IDCANCEL );
}

VOID dlgUpdate::OnBtnSkip()
{
	SCheckBox * pSkip = FindChildByName2<SCheckBox>(L"skipCheck");
	if ( pSkip->IsChecked() )
		SkinUpdate( m_updateInfo.strVersion );
	else
		SkinUpdate( L"" );
}

VOID dlgUpdate::OnDownload(INT Percent)
{
	FindChildByName2<SProgress>(L"prog")->SetValue(Percent);
}

LRESULT CALLBACK DownloadCallBack(int nCurrentSize, float fPercent, LPVOID lpParm)
{
	dlgUpdate* pThis = (dlgUpdate*)lpParm;
	pThis->Post([=]{
		pThis->OnDownload( fPercent*100 );
	});
	return 0;
}

BOOL dlgUpdate::DoUpdate()
{
	SStringT strTempFileName;
	GetTempPath( MAX_PATH, strTempFileName.GetBufferSetLength(MAX_PATH));
	strTempFileName.ReleaseBuffer();

	SStringT strFileName = m_updateInfo.strUrl;
	strFileName = strFileName.Mid( strFileName.ReverseFind(L'/') + 1);
	strTempFileName.Append(strFileName);

	DWORD dwRet = StartDownload( m_updateInfo.strUrl, strTempFileName, 1000*1000*2, DownloadCallBack, this);
	if( dwRet == DOWNLOAD_SUCCESS)
	{
		HANDLE hProcess = msapi::ShellProcess( strTempFileName, m_updateInfo.strParam, TRUE);
		if ( hProcess == NULL )
			return FALSE;
		
		WaitForSingleObject(hProcess, -1);
		return TRUE;
	}
	return FALSE;
}
