

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __VirtualAutorunDisabler_i_h__
#define __VirtualAutorunDisabler_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVirtualAutorunDisablingMonitor_FWD_DEFINED__
#define __IVirtualAutorunDisablingMonitor_FWD_DEFINED__
typedef interface IVirtualAutorunDisablingMonitor IVirtualAutorunDisablingMonitor;
#endif 	/* __IVirtualAutorunDisablingMonitor_FWD_DEFINED__ */


#ifndef __IVirtualAutorunDisablingMonitorInternal_FWD_DEFINED__
#define __IVirtualAutorunDisablingMonitorInternal_FWD_DEFINED__
typedef interface IVirtualAutorunDisablingMonitorInternal IVirtualAutorunDisablingMonitorInternal;
#endif 	/* __IVirtualAutorunDisablingMonitorInternal_FWD_DEFINED__ */


#ifndef __VirtualAutorunDisablingMonitor_FWD_DEFINED__
#define __VirtualAutorunDisablingMonitor_FWD_DEFINED__

#ifdef __cplusplus
typedef class VirtualAutorunDisablingMonitor VirtualAutorunDisablingMonitor;
#else
typedef struct VirtualAutorunDisablingMonitor VirtualAutorunDisablingMonitor;
#endif /* __cplusplus */

#endif 	/* __VirtualAutorunDisablingMonitor_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IVirtualAutorunDisablingMonitor_INTERFACE_DEFINED__
#define __IVirtualAutorunDisablingMonitor_INTERFACE_DEFINED__

/* interface IVirtualAutorunDisablingMonitor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVirtualAutorunDisablingMonitor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57C052A7-AAD7-4230-860D-F6768C8EA59F")
    IVirtualAutorunDisablingMonitor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitializeMonitorAndResetWatchdog( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TerminateServer( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVirtualAutorunDisablingMonitorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVirtualAutorunDisablingMonitor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVirtualAutorunDisablingMonitor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVirtualAutorunDisablingMonitor * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeMonitorAndResetWatchdog )( 
            IVirtualAutorunDisablingMonitor * This);
        
        HRESULT ( STDMETHODCALLTYPE *TerminateServer )( 
            IVirtualAutorunDisablingMonitor * This);
        
        END_INTERFACE
    } IVirtualAutorunDisablingMonitorVtbl;

    interface IVirtualAutorunDisablingMonitor
    {
        CONST_VTBL struct IVirtualAutorunDisablingMonitorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVirtualAutorunDisablingMonitor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualAutorunDisablingMonitor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualAutorunDisablingMonitor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualAutorunDisablingMonitor_InitializeMonitorAndResetWatchdog(This)	\
    ( (This)->lpVtbl -> InitializeMonitorAndResetWatchdog(This) ) 

#define IVirtualAutorunDisablingMonitor_TerminateServer(This)	\
    ( (This)->lpVtbl -> TerminateServer(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVirtualAutorunDisablingMonitor_INTERFACE_DEFINED__ */


#ifndef __IVirtualAutorunDisablingMonitorInternal_INTERFACE_DEFINED__
#define __IVirtualAutorunDisablingMonitorInternal_INTERFACE_DEFINED__

/* interface IVirtualAutorunDisablingMonitorInternal */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVirtualAutorunDisablingMonitorInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("466a44dc-ad3b-4573-bdc4-0686bbfb7a23")
    IVirtualAutorunDisablingMonitorInternal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckForTimeout( 
            /* [in] */ int PID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVirtualAutorunDisablingMonitorInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVirtualAutorunDisablingMonitorInternal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVirtualAutorunDisablingMonitorInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVirtualAutorunDisablingMonitorInternal * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckForTimeout )( 
            IVirtualAutorunDisablingMonitorInternal * This,
            /* [in] */ int PID);
        
        END_INTERFACE
    } IVirtualAutorunDisablingMonitorInternalVtbl;

    interface IVirtualAutorunDisablingMonitorInternal
    {
        CONST_VTBL struct IVirtualAutorunDisablingMonitorInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVirtualAutorunDisablingMonitorInternal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualAutorunDisablingMonitorInternal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualAutorunDisablingMonitorInternal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualAutorunDisablingMonitorInternal_CheckForTimeout(This,PID)	\
    ( (This)->lpVtbl -> CheckForTimeout(This,PID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVirtualAutorunDisablingMonitorInternal_INTERFACE_DEFINED__ */



#ifndef __VirtualAutorunDisablerLib_LIBRARY_DEFINED__
#define __VirtualAutorunDisablerLib_LIBRARY_DEFINED__

/* library VirtualAutorunDisablerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VirtualAutorunDisablerLib;

EXTERN_C const CLSID CLSID_VirtualAutorunDisablingMonitor;

#ifdef __cplusplus

class DECLSPEC_UUID("04DDC073-352E-447D-8A83-3E1FD9D41E61")
VirtualAutorunDisablingMonitor;
#endif
#endif /* __VirtualAutorunDisablerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


