#ifndef KN_SRC_PORT_H
#define KN_SRC_PORT_H
#include "_kn_plt_cstd_lib_wrap.h"
#include <wolfssl/internal.h>
//#include <stdio.h>

#if defined(POC_CDE_BREW)			
#include <AEEstd.h>
#include <AEENetErr.h>
#include <AEENetAddrTypes.h>
#endif

#ifndef NO_FILESYSTEM
    #if !defined(USE_WINDOWS_API) && !defined(NO_WOLFSSL_DIR) \
            && !defined(EBSNET) && (!defined POC_CDE_BREW) && (!defined(PJ_MTK) && !defined(PJ_RTKE) &&!defined(PJ_THREADX)) /* Merging from 7.10 branch to 7.10 64-bit branch */
        #include <dirent.h>
        #include <sys/stat.h>
    #endif
    #ifdef EBSNET
        #include "vfapi.h"
        #include "vfile.h"
    #endif
#endif /* NO_FILESYSTEM */

//ssl.c
#if defined(PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK) || defined (POC_CDE_BREW)
	#define	XFOPEN KN_CFOPEN
	#define XFILE 	KN_FILE* 
	#define close(s) KN_Sock_Close(s)
#endif

#ifdef USE_WINDOWS_API
	//	#ifndef POC_CDE_BREW
    //	#define CloseSocket(s) closesocket(s)
	//	#endif

	#ifdef POC_CDE_BREW
    	#define closesocket(s) CloSock(s)
	#else
		//In other cases it should closesocket(s) as it is
	#endif
#endif
//end from ssl.c


//internal.c
uint32 kn_port_time();
void InitSSL_Ctx_CDE_Port(WOLFSSL_CTX* ctx, WOLFSSL_METHOD* method);
#endif