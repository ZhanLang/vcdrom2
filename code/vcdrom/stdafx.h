// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#define  _CRT_SECURE_NO_WARNINGS
#define	 DLL_SOUI
#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/souictrls.h>
#include <res.mgr/sobjdefattr.h>
#include <com-cfg.h>
#include "trayicon/SShellNotifyIcon.h"
#include "resource.h"
#define R_IN_CPP	//定义这个开关来
#include "res\resource.h"
using namespace SOUI;


#include <atlstr.h>

#include <VirtualCDClient.h>

#include <mscom/mscominc.h>
using namespace mscom;

#include <mslog/stdlog.h>
#define GroupName L"VCDRom"