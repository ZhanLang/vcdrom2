// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "MainDlg.h"
#include "trayicon\SShellNotifyIcon.h"
//从PE文件加载，注意从文件加载路径位置
#define RES_TYPE 2
//#define SYSRES_TYPE 2
// #define RES_TYPE 0   //PE
// #define RES_TYPE 1   //ZIP
// #define RES_TYPE 2   //7z
// #define RES_TYPE 2   //文件
//去掉多项支持，以免代码显得混乱
#if (RES_TYPE==1)
#include "resprovider-zip\zipresprovider-param.h"
#else 
#if (RES_TYPE==2)
#include "resprovider-7zip\zip7resprovider-param.h"
#endif
#endif
#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif
#include "SRadioBox2.h"
#include "SRotateWindow.h"
#include "SChromeTabCtrl.h"
#include "SSkinNewScrollBar.h"
#include "gif\SGifPlayer.h"
#include "gif\SSkinGif.h"

#include <util/globalevent.h>
#include <process/ParseCommand.h>
#include "def.h"


//定义唯一的一个R,UIRES对象,ROBJ_IN_CPP是resource.h中定义的宏。
ROBJ_IN_CPP

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

	GrpError(GroupName, MsgLevel_Error, L"%s", GetCommandLineW());
	SStringT strFile = lpstrCmdLine;
	INT nArg = 0;
	LPTSTR* pArgv = CommandLineToArgvW(GetCommandLineW(), &nArg );
	if ( nArg >= 2)
		strFile = pArgv[1];

	LocalFree( pArgv );



	lpstrCmdLine = strFile.GetBuffer(0);
	CGlobalEvent globalEvent;
	if ( globalEvent.OpenEvent( EVENT_ALL_ACCESS, FALSE, _Def_HostClassName ))
	{
		TCHAR szParam[ MAX_PATH ] = { 0 };
		DWORD dwOutSize = 0;

		NamedPipeSendMessageToServer(NAMEDPIPE_NAME_VCDROM, lpstrCmdLine , (wcslen( lpstrCmdLine ) + 1) * 2, NULL, dwOutSize);
		return 0;
	}


	globalEvent.CreateEvent( NULL, FALSE, FALSE, _Def_HostClassName);

	int nRet = 0;

	SComMgr *pComMgr = new SComMgr;
	TCHAR szCurrentDir[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szCurrentDir, sizeof(szCurrentDir));

	LPTSTR lpInsertPos = _tcsrchr(szCurrentDir, _T('\\'));
#ifdef _DEBUG
	_tcscpy(lpInsertPos + 1, _T("..\\vcdrom"));
#else
	_tcscpy(lpInsertPos + 1, _T("\0"));
#endif
	SetCurrentDirectory(szCurrentDir);
	{
		BOOL bLoaded = FALSE;
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
		bLoaded = pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
		bLoaded = pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));

		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		SApplication *theApp = new SApplication(pRenderFactory, hInstance);
		theApp->RegisterSkinClass<SSkinNewScrollbar>();
		theApp->RegisterWindowClass<SGifPlayer>();//theApp中增加方法：RegisterWindowClass,替换RegisterWndFactory(TplSWindowFactory<SGifPlayer>())
		theApp->RegisterSkinClass<SSkinGif>();//注册SkinGif
#ifdef _DEBUG
		//选择了仅在Release版本打包资源则系统资源在DEBUG下始终使用DLL加载
		{
			HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
			if (hModSysResource)
			{
				CAutoRefPtr<IResProvider> sysResProvider;
				CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
				sysResProvider->Init((WPARAM)hModSysResource, 0);
				theApp->LoadSystemNamedResource(sysResProvider);
				FreeLibrary(hModSysResource);
			}
			else
			{
				SASSERT(0);
			}
		}
#else		
		//从DLL加载系统资源
		{
			HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
			if (hModSysResource)
			{
				CAutoRefPtr<IResProvider> sysResProvider;
				CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
				sysResProvider->Init((WPARAM)hModSysResource, 0);
				theApp->LoadSystemNamedResource(sysResProvider);
				FreeLibrary(hModSysResource);
			}
			else
			{
				SASSERT(0);
			}
		}
#endif

		CAutoRefPtr<IResProvider>   pResProvider;

#ifdef _DEBUG		
		//选择了仅在Release版本打包资源则在DEBUG下始终使用文件加载
		{
			CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
			bLoaded = pResProvider->Init((LPARAM)_T("uires"), 0);
			SASSERT(bLoaded);
		}
#else
		{
			bLoaded = pComMgr->CreateResProvider_7ZIP((IObjRef**)&pResProvider);
			SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));
			ZIP7RES_PARAM param;
			param.ZipFile(pRenderFactory, _T("uires.7z"), "CreateFile");
			bLoaded = pResProvider->Init((WPARAM)&param, 0);
			SASSERT(bLoaded);
		}
#endif
		theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);
		theApp->AddResProvider(pResProvider);

		theApp->RegisterWindowClass<SRadioBox2>();//注册RadioBox2
		theApp->RegisterWindowClass<SRotateWindow>();

		theApp->RegisterWindowClass<SShellNotifyIcon>();
		theApp->RegisterWindowClass<SChromeTabCtrl>();
		
		//加载多语言翻译模块。
		CAutoRefPtr<ITranslatorMgr> trans;
		bLoaded = pComMgr->CreateTranslator((IObjRef**)&trans);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("translator"));
		if (trans)
		{//加载语言翻译包
			theApp->SetTranslator(trans);
			pugi::xml_document xmlLang;
			if (theApp->LoadXmlDocment(xmlLang, _T("lang_cn"), _T("translator")))
			{
				CAutoRefPtr<ITranslator> langCN;
				trans->CreateTranslator(&langCN);
				langCN->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
				trans->InstallTranslator(langCN);
			}
		}
		
		LPCTSTR lpszFile = NULL;
		if ( wcslen(lpstrCmdLine ))
		{
			lpszFile = lpstrCmdLine;
		//	MessageBox(NULL, lpszFile, L"TS", MB_OK);
		}
		// BLOCK: Run application
		{
			CMainDlg dlgMain;
			dlgMain.Create(GetActiveWindow());
			dlgMain.SendMessage(WM_INITDIALOG, 0, (LPARAM)lpszFile);
			dlgMain.CenterWindow(dlgMain.m_hWnd);
			dlgMain.ShowWindow(SW_SHOWNORMAL);
			nRet = theApp->Run(dlgMain.m_hWnd);
		}

		delete theApp;
	}

	delete pComMgr;

	OleUninitialize();
	return nRet;
}
