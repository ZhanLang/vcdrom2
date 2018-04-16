#pragma once
#include "shostdialogex.h"
class SBusyDialog :
	public SHostDialogEx
{
public:
	SBusyDialog();
	~SBusyDialog(void);

	virtual INT_PTR DoModal(const std::function<void()> &f,  HWND hParent=NULL);
};

