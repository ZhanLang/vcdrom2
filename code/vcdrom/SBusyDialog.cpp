#include "StdAfx.h"
#include "SBusyDialog.h"
#include "thread\threadex.h"


SBusyDialog::SBusyDialog():SHostDialogEx(L"XML_DLG_BUSY")
{

}


SBusyDialog::~SBusyDialog(void)
{
}

INT_PTR SBusyDialog::DoModal(const std::function<void()> &f, HWND hParent/*=NULL*/)
{
	CThreadEx().Do([=]{
		f();
		while( !this->IsWindow())
			Sleep(1);

		Sleep(1000);
		Post([=]{OnOK();});
	});

  return SHostDialogEx::DoModal(hParent);
}
