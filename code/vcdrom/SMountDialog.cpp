#include "StdAfx.h"
#include "SMountDialog.h"


SMountDialog::SMountDialog(void):SHostDialogEx(L"XML_DLG_MOUNT")
{
}


SMountDialog::~SMountDialog(void)
{
}

void SMountDialog::OnOK()
{
	SComboBox* pCombox = FindChildByName2<SComboBox>(L"lv_letter_fix");
	SStringT sWndText = pCombox->GetWindowText();
	if ( sWndText.GetLength() )
		m_Letter = sWndText[0];
	
	SCheckBox* pCheck = FindChildByName2<SCheckBox>(L"checkOpen");
	m_bOpen = pCheck->IsChecked();
	SHostDialogEx::OnOK();
}

void SMountDialog::OnCancel()
{
	SHostDialogEx::OnCancel();
}

TCHAR SMountDialog::GetMountLetter()
{
	

	return m_Letter;
}

BOOL SMountDialog::IsOpen()
{
	return m_bOpen;
}

VOID SMountDialog::SetFileName(LPCTSTR lpszFileName)
{
	m_strFileName = lpszFileName;
}

BOOL SMountDialog::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	SComboBox* pCombox = FindChildByName2<SComboBox>(L"lv_letter_fix");
	TCHAR szUseLetter[MAX_PATH] = { 0 };
	DWORD dwUseLetterCount = 0;
	TCHAR szLogicalDriveStrings[512] = { 0 };
	DWORD dwLen = GetLogicalDriveStrings(_countof(szLogicalDriveStrings), szLogicalDriveStrings);
	for ( DWORD dwLoop = 0 ; dwLoop < dwLen ; dwLoop += 4)
	{
		TCHAR lpszLetter = szLogicalDriveStrings[dwLoop];
		szUseLetter[dwUseLetterCount] = lpszLetter;
		dwUseLetterCount++;
	}

	//´ÓCÅÌ¿ªÊ¼
	for ( TCHAR cLatter = 'D' ; cLatter <= 'Z' ; cLatter++)
	{
		BOOL bFind = FALSE;
		for ( DWORD dwLoop = 0 ; dwLoop < dwUseLetterCount ; dwLoop++)
		{
			if ( szUseLetter[dwLoop] == cLatter)
			{
				bFind = TRUE;
				break;
			}
		}

		if ( !bFind )
		{
			TCHAR szLetter[] = _T("?:");
			szLetter[0] = cLatter;
			pCombox->InsertItem(pCombox->GetCount(), szLetter, 0, NULL);
		}
	}

	
	pCombox->SetCurSel(0);

	FindChildByName2<SStatic>(L"title")->SetWindowText(m_strFileName);
	return TRUE;
}
