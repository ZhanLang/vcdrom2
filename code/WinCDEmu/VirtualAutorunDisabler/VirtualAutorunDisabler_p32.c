

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Apr 16 11:49:22 2018
 */
/* Compiler settings for VirtualAutorunDisabler.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "VirtualAutorunDisabler_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   97                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _VirtualAutorunDisabler_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } VirtualAutorunDisabler_MIDL_TYPE_FORMAT_STRING;

typedef struct _VirtualAutorunDisabler_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } VirtualAutorunDisabler_MIDL_PROC_FORMAT_STRING;

typedef struct _VirtualAutorunDisabler_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } VirtualAutorunDisabler_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const VirtualAutorunDisabler_MIDL_TYPE_FORMAT_STRING VirtualAutorunDisabler__MIDL_TypeFormatString;
extern const VirtualAutorunDisabler_MIDL_PROC_FORMAT_STRING VirtualAutorunDisabler__MIDL_ProcFormatString;
extern const VirtualAutorunDisabler_MIDL_EXPR_FORMAT_STRING VirtualAutorunDisabler__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVirtualAutorunDisablingMonitor_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVirtualAutorunDisablingMonitor_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVirtualAutorunDisablingMonitorInternal_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVirtualAutorunDisablingMonitorInternal_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const VirtualAutorunDisabler_MIDL_PROC_FORMAT_STRING VirtualAutorunDisabler__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure InitializeMonitorAndResetWatchdog */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 24 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TerminateServer */

/* 30 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 32 */	NdrFcLong( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 46 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 54 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 56 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 58 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CheckForTimeout */

/* 60 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 62 */	NdrFcLong( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x3 ),	/* 3 */
/* 68 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 70 */	NdrFcShort( 0x8 ),	/* 8 */
/* 72 */	NdrFcShort( 0x8 ),	/* 8 */
/* 74 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 76 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter PID */

/* 84 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 86 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 92 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const VirtualAutorunDisabler_MIDL_TYPE_FORMAT_STRING VirtualAutorunDisabler__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IVirtualAutorunDisablingMonitor, ver. 0.0,
   GUID={0x57C052A7,0xAAD7,0x4230,{0x86,0x0D,0xF6,0x76,0x8C,0x8E,0xA5,0x9F}} */

#pragma code_seg(".orpc")
static const unsigned short IVirtualAutorunDisablingMonitor_FormatStringOffsetTable[] =
    {
    0,
    30
    };

static const MIDL_STUBLESS_PROXY_INFO IVirtualAutorunDisablingMonitor_ProxyInfo =
    {
    &Object_StubDesc,
    VirtualAutorunDisabler__MIDL_ProcFormatString.Format,
    &IVirtualAutorunDisablingMonitor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVirtualAutorunDisablingMonitor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    VirtualAutorunDisabler__MIDL_ProcFormatString.Format,
    &IVirtualAutorunDisablingMonitor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IVirtualAutorunDisablingMonitorProxyVtbl = 
{
    &IVirtualAutorunDisablingMonitor_ProxyInfo,
    &IID_IVirtualAutorunDisablingMonitor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVirtualAutorunDisablingMonitor::InitializeMonitorAndResetWatchdog */ ,
    (void *) (INT_PTR) -1 /* IVirtualAutorunDisablingMonitor::TerminateServer */
};

const CInterfaceStubVtbl _IVirtualAutorunDisablingMonitorStubVtbl =
{
    &IID_IVirtualAutorunDisablingMonitor,
    &IVirtualAutorunDisablingMonitor_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVirtualAutorunDisablingMonitorInternal, ver. 0.0,
   GUID={0x466a44dc,0xad3b,0x4573,{0xbd,0xc4,0x06,0x86,0xbb,0xfb,0x7a,0x23}} */

#pragma code_seg(".orpc")
static const unsigned short IVirtualAutorunDisablingMonitorInternal_FormatStringOffsetTable[] =
    {
    60
    };

static const MIDL_STUBLESS_PROXY_INFO IVirtualAutorunDisablingMonitorInternal_ProxyInfo =
    {
    &Object_StubDesc,
    VirtualAutorunDisabler__MIDL_ProcFormatString.Format,
    &IVirtualAutorunDisablingMonitorInternal_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVirtualAutorunDisablingMonitorInternal_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    VirtualAutorunDisabler__MIDL_ProcFormatString.Format,
    &IVirtualAutorunDisablingMonitorInternal_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IVirtualAutorunDisablingMonitorInternalProxyVtbl = 
{
    &IVirtualAutorunDisablingMonitorInternal_ProxyInfo,
    &IID_IVirtualAutorunDisablingMonitorInternal,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVirtualAutorunDisablingMonitorInternal::CheckForTimeout */
};

const CInterfaceStubVtbl _IVirtualAutorunDisablingMonitorInternalStubVtbl =
{
    &IID_IVirtualAutorunDisablingMonitorInternal,
    &IVirtualAutorunDisablingMonitorInternal_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    VirtualAutorunDisabler__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _VirtualAutorunDisabler_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IVirtualAutorunDisablingMonitorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVirtualAutorunDisablingMonitorInternalProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _VirtualAutorunDisabler_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IVirtualAutorunDisablingMonitorStubVtbl,
    ( CInterfaceStubVtbl *) &_IVirtualAutorunDisablingMonitorInternalStubVtbl,
    0
};

PCInterfaceName const _VirtualAutorunDisabler_InterfaceNamesList[] = 
{
    "IVirtualAutorunDisablingMonitor",
    "IVirtualAutorunDisablingMonitorInternal",
    0
};


#define _VirtualAutorunDisabler_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _VirtualAutorunDisabler, pIID, n)

int __stdcall _VirtualAutorunDisabler_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _VirtualAutorunDisabler, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _VirtualAutorunDisabler, 2, *pIndex )
    
}

const ExtendedProxyFileInfo VirtualAutorunDisabler_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _VirtualAutorunDisabler_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _VirtualAutorunDisabler_StubVtblList,
    (const PCInterfaceName * ) & _VirtualAutorunDisabler_InterfaceNamesList,
    0, /* no delegation */
    & _VirtualAutorunDisabler_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

