

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IVirtualAutorunDisablingMonitor,0x57C052A7,0xAAD7,0x4230,0x86,0x0D,0xF6,0x76,0x8C,0x8E,0xA5,0x9F);


MIDL_DEFINE_GUID(IID, IID_IVirtualAutorunDisablingMonitorInternal,0x466a44dc,0xad3b,0x4573,0xbd,0xc4,0x06,0x86,0xbb,0xfb,0x7a,0x23);


MIDL_DEFINE_GUID(IID, LIBID_VirtualAutorunDisablerLib,0xD2243491,0xB0DF,0x40CC,0x99,0x73,0x9E,0x40,0x16,0x31,0xD7,0x70);


MIDL_DEFINE_GUID(CLSID, CLSID_VirtualAutorunDisablingMonitor,0x04DDC073,0x352E,0x447D,0x8A,0x83,0x3E,0x1F,0xD9,0xD4,0x1E,0x61);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



