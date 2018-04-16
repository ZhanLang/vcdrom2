// VCDImgContextMenu.cpp : Implementation of CVCDImgContextMenu

#include "stdafx.h"
#include "VCDImgContextMenu.h"
#include "../vmnt/ContextMenuLabels.h"
#include "../vmnt/RegistryParams.h"
#include "../VirtualCDCtl/VirtualCDClient.h"
#include "VCDRomDef.h"

#define IDM_SELECTANDMOUNT	0
#define IDM_REMOUNTLTRBASE	1

// CVCDImgContextMenu

#include <bzscore/file.h>
using namespace BazisLib;
#include "DebugLog.h"
#include "util/globalevent.h"

extern HINSTANCE g_hModule;

HRESULT STDMETHODCALLTYPE CVCDImgContextMenu::Initialize(/* [unique][in] */ __in_opt PCIDLIST_ABSOLUTE pidlFolder, /* [unique][in] */ __in_opt IDataObject *pdtobj, /* [unique][in] */ __in_opt HKEY hkeyProgID)
{
	HRESULT hR =  ContextMenuBase::Initialize(pidlFolder, pdtobj, hkeyProgID);
	if (!SUCCEEDED(hR))
	{
		return hR;
	}

	m_pClientObject = NULL;
	CreateComX3();


	String ext = BazisLib::Path::GetExtensionExcludingDot(m_FileName);
	if (ext.length() > 0 && ext[0] == '.')
		ext = ext.substr(1);

	for each (LPCTSTR lpExt in lpSupportedExtensions)
		if (!ext.icompare(lpExt))
		{

			return S_OK;
		}


	return E_FAIL;
}

extern HINSTANCE g_hModule;
#include "TransparentMenuBitmap.h"

HRESULT STDMETHODCALLTYPE CVCDImgContextMenu::QueryContextMenu(/* [in] */ __in HMENU hmenu, /* [in] */ __in UINT indexMenu, /* [in] */ __in UINT idCmdFirst, /* [in] */ __in UINT idCmdLast, /* [in] */ __in UINT uFlags)
{
	if (uFlags & CMF_DEFAULTONLY)
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));

	DWORD lastCommand = IDM_SELECTANDMOUNT;
	InsertMenu(hmenu,
		indexMenu,
		MF_STRING | MF_BYPOSITION,
		idCmdFirst + IDM_SELECTANDMOUNT,
		_T("挂载")
		);


	HICON hIcon = (HICON)LoadImage(g_hModule, MAKEINTRESOURCE(IDI_MAINICON), IMAGE_ICON, 16, 16, LR_SHARED);
	if (hIcon)
	{
		CComPtr<IWICImagingFactory> pFactory;
		HRESULT hR = pFactory.CoCreateInstance(CLSID_WICImagingFactory);
		if (SUCCEEDED(hR))
		{
			AddIconToMenuItem(pFactory, hmenu, indexMenu, TRUE, hIcon, FALSE, NULL);
		}
	}

	/*
	VirtualCDClient clt;
	VirtualCDClient::VirtualCDList devs = clt.GetVirtualDiskList();
	if (!devs.empty())
	{
		HMENU hSubmenu = CreatePopupMenu();
		unsigned submenuPosition = 0;

		for each(const VirtualCDClient::VirtualCDEntry &entry in devs)
		{
			unsigned ID = IDM_REMOUNTLTRBASE + (entry.DriveLetter & ~0x40);
			TCHAR tszDrive[] = _T("?:");
			tszDrive[0] = entry.DriveLetter;
			InsertMenu(hSubmenu, submenuPosition++, MF_BYPOSITION, idCmdFirst + ID, tszDrive);
			lastCommand = max(lastCommand, ID);
		}
			
		MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
		mii.fMask = MIIM_SUBMENU | MIIM_STRING | MIIM_ID;
		mii.wID = idCmdFirst + IDM_REMOUNTLTRBASE;
		mii.hSubMenu = hSubmenu;
		mii.dwTypeData = const_cast<LPWSTR>(L"AAAAAAAA");
		InsertMenuItem(hmenu, indexMenu + 1, TRUE, &mii);
		
	}
	*/

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(lastCommand + 1));
}

HRESULT STDMETHODCALLTYPE CVCDImgContextMenu::InvokeCommand(/* [in] */ __in CMINVOKECOMMANDINFO *pici)
{
	if (!pici)
	{
		return E_NOTIMPL;
	}

	TCHAR tszPath[MAX_PATH] = { 0, };
	GetModuleFileName(g_hModule, tszPath, _countof(tszPath));
	BazisLib::String path = String::sFormat(L"%s\\%s", BazisLib::Path::GetDirectoryName(BazisLib::Path::GetDirectoryName(String(tszPath))).c_str(), VMNT_EXE_W);


	switch ((int)pici->lpVerb)
	{
	case IDM_SELECTANDMOUNT:
		{
			CGlobalMutex globalMutex;

			if (globalMutex.OpenMutex(MUTEX_MODIFY_STATE , FALSE, VCDROM_GLOBAL_MUTE_NAME))
			{
				if (m_pClientObject)
				{
					comx3_shell_contextmenu_info msg;
					ZeroMemory(&msg, sizeof(comx3_shell_contextmenu_info));
					msg.cmd = shell_contextmenu_cmd_search;

					wcscpy_s(msg.strFilePath, MAX_PATH, m_FileName.c_str());
					HRESULT hRet = m_pClientObject->SendMessage(COMX3_SHELL_CONTEXTMENU_DEFID_UI,COMX3_SHELL_CONTEXTMENU_MASKID_UI, COMX3_SHELL_CONTEXTMENU_SEARCH_MSG, &msg, sizeof(msg),0);
				}
			}
			else
			{
				ShellExecute(pici->hwnd, _T("open"), path.c_str(), String::sFormat(L"/ltrselect \"%s\"", m_FileName.c_str()).c_str(), NULL, pici->nShow);
			}
		}
		/*
		ShellExecute(pici->hwnd, _T("open"), path.c_str(), String::sFormat(L"\"%s\" /ltrselect", m_FileName.c_str()).c_str(), NULL, pici->nShow);

		break;
	default:
		{
			int letter = (int) pici->lpVerb - IDM_REMOUNTLTRBASE;
			letter |= 0x40;
			if (letter >= 'A' && letter <= 'Z')
			{

				HINSTANCE result = ShellExecute(pici->hwnd, _T("open"), path.c_str(), String::sFormat(L"\"%s\" /remount:%c", m_FileName.c_str(), (char)letter).c_str(), NULL, pici->nShow);

			}
			else
				return E_FAIL;
		}
		*/
	}
		
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CVCDImgContextMenu::GetCommandString(/* [in] */ __in UINT_PTR idCmd, /* [in] */ __in UINT uType, /* [in] */ __reserved UINT *pReserved, /* [out] */ __out_awcount(!(uType & GCS_UNICODE), cchMax) LPSTR pszName, /* [in] */ __in UINT cchMax)
{
	return E_NOTIMPL;
}


HRESULT CVCDImgContextMenu::CreateComX3()
{
	if (m_pClientObject)
	{
		return S_OK;
	}

	CString strNpcModulePaht;
	msapi::GetModulePath(g_hModule, strNpcModulePaht.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strNpcModulePaht.ReleaseBuffer();
	strNpcModulePaht.AppendFormat(_T("\\..\\common file\\mscom\\npc%d.dll"), sizeof(void*) == sizeof(int) ? 32 : 64);
	//ZM1_GrpDbgOutput(GroupName, _T("NpcModule Paht=%s"), strNpcModulePaht.GetBuffer());

	m_NpcLoader.SetMoudlePath(strNpcModulePaht.GetBuffer());
	BOOL bRet = m_NpcLoader.LoadMSCom();
	if (!bRet)
	{
		//ZM1_GrpDbgOutput(GroupName, _T("Load Npc Module Failed(%s)."), strNpcModulePaht.GetBuffer());
		return E_FAIL;
	}


	HRESULT hRet = m_NpcLoader.CreateInstance(CLSID_CComX3, NULL, NULL, __uuidof(IComX3), (void**)&m_pComX3);

	if (FAILED(hRet))
	{
		//ZM1_GrpDbgOutput(GroupName, _T("Create Npc Object Failed."));
		return E_FAIL;
	}


	//先用硬代码写死吧
	m_pCenter = m_pComX3->Initialize("VCDRom_Shell");
	RASSERT(m_pCenter, E_FAIL);

	//这里的 DEFID 和 MASKID 是随便设置的，COMX3的标准用法可不是这样的，千万不要效仿
	m_pClientObject = m_pCenter->Logon(COMX3_SHELL_CONTEXTMENU_DEFID , COMX3_SHELL_CONTEXTMENU_MASKID , this , CREATE_COMM_OBJECT_MULTI);
	RASSERT(m_pClientObject , E_FAIL);

	return S_OK;
}

HRESULT CVCDImgContextMenu::ReleaseComX3()
{
	//m_comX3impl.UnInit();
	if (m_pClientObject)
	{
		m_pCenter->Logoff(m_pClientObject);
	}

	if (m_pCenter)
	{
		m_pComX3->Uninitialize(m_pCenter);
		m_pCenter = NULL;
	}

	SAFE_RELEASE(m_pComX3);

	m_NpcLoader.UnloadMSCom();


	return S_OK;
}

HRESULT CVCDImgContextMenu::Dispatch(IMessage* pMsg)
{
	return S_OK;
}