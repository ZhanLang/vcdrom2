#pragma once
#include "shostdialogex.h"
class SMountDialog :
	public SHostDialogEx
{
public:
	SMountDialog(void);
	~SMountDialog(void);
	EVENT_MAP_BEGIN()
		EVENT_ID_COMMAND(IDOK,OnOK)
		EVENT_ID_COMMAND(IDCANCEL,OnCancel)
		EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SMountDialog)
		
		MSG_WM_INITDIALOG(OnInitDialog)
	
	CHAIN_MSG_MAP(SHostDialogEx)
	REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()



	
public:
	TCHAR GetMountLetter();
	BOOL  IsOpen();
	VOID  SetFileName( LPCTSTR lpszFileName);
protected:
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnOK();
	void OnCancel();
private:
	TCHAR m_Letter;
	BOOL  m_bOpen;
	SStringT m_strFileName;
};

