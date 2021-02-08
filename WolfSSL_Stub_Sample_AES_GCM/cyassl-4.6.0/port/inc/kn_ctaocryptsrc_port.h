#ifndef KN_CTAOCRYPT_SRC_PORT_H
#define KN_CTAOCRYPT_SRC_PORT_H

//#include <wolfssl/ssl.h>
#include <cyassl/ctaocrypt/types.h>
#include <cyassl/ctaocrypt/settings.h>


//91_fips.c
#ifdef WINDOWS
#include <stdio.h>
#ifdef _MSC_VER

#define CCALL __cdecl
#pragma section(".CRT$XCU",read)
#define INITIALIZER(f) \
   static void __cdecl f(void); \
   __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
   static void __cdecl f(void)
#endif

#endif
//91_fips.c


//CYASSL_API const char* wolfCrypt_GetVerifyCoreHash_fips(void);

//cyassl/ssl.h
#define CyaSSL_set_quiet_shutdown wolfSSL_set_quiet_shutdown
#define CyaSSL_get_libversion wolfSSL_get_libversion
#define CyaSSL_ErrorCodes wolfSSL_ErrorCodes
#define CyaCrypt_GetCoreHash_fips wolfCrypt_GetCoreHash_fips
#define CyaCrypt_GetStatus_fips wolfCrypt_GetStatus_fips
//cyassl/ssl.h --end

//#ifdef HAVE_FIPS
//#ifdef HAVE_THREAD_LS

//int GetThisThreadInPOS(void);
//void SetThisThreadInPOS(int inPOS);
//int InitThisThreadInPOS(void);

//#endif
//#endif

/* Merging from 7.10 branch to 7.10 64-bit branch - Begin */
#if defined(PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK)
#include "_kn_plt_cstd_lib_wrap.h"
#define SIZEOF_LONG KN_SIZEOF_LONG
#define SIZEOF_LONG_LONG KN_SIZEOF_LONGLONG
#endif

#endif//KN_CTAOCRYPT_SRC_PORT_H
