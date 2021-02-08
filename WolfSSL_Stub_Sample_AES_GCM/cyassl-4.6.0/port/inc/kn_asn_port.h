#ifndef KN_ASN_PORT_H
#define KN_ASN_PORT_H

#include <stdio.h>
//#include <wolfssl/wolfcrypt/visibility.h>
#include <wolfssl/ssl.h>
//#include <wolfssl/internal.h>
//#include <wolfssl/wolfcrypt/types.h>

#ifdef POC_CDE_BREW //changed for iOS local builds with FIPS disabled
#ifndef HAVE_FIPS
#include "kn_plt_cstd_lib_wrap.h" 
#define wc_GenerateSeed	KN_GenerateSeed
#endif //have_fips
#endif  //poc_cde_brew

#ifndef NO_ASN_TIME
//#include <time.h>
#if defined(USER_TIME)
#ifndef POC_CDE_BREW
    typedef long time_t;
#else
	#define time_t unsigned long
#endif 
   /* Merging from 7.10 branch to 7.10 64-bit branch - Begin */
	    /* forward declaration */
    struct tm* KN_gmtime(const time_t* timer);
    //extern time_t XTIME(time_t * timer);
    #define XTIME(tl)  KN_TIME(tl)
    #define XGMTIME(c, t) KN_gmtime((c))
    #define XVALIDATE_DATE(d, f, t) ValidateDate((d), (f), (t))
#endif
#endif 

//#include <wolfssl/internal.h>

#if defined(POC_CDE_BREW)
   WOLFSSL_LOCAL
    int KN_IO_EmbedReceive(WOLFSSL *ssl, char *buf, int sz, void *ctx);
    WOLFSSL_LOCAL 
    int KN_IO_EmbedSend(WOLFSSL *ssl, char *buf, int sz, void *ctx);
   #ifdef WOLFSSL_DTLS
    WOLFSSL_LOCAL
    int KN_IO_EmbedReceiveFrom(WOLFSSL *ssl, char *buf, int sz, void *ctx);
    WOLFSSL_LOCAL 
    int KN_IO_EmbedSendTo(WOLFSSL *ssl, char *buf, int sz, void *ctx);
    #endif /*WOLFSSL_DTLS*/
#endif

/*
#ifdef POC_CDE_BREW
typedef struct WOLFSSL_DTLS_CTX {
    WOLFSSL_SOCKADDR peer;
    unsigned int rfd;
    int wfd;
}WOLFSSL_DTLS_CTX;
#endif
*/

#ifndef WOLFSSL_USER_IO //CYASSL_USER_IO
/* default IO callbacks to be declared here*/
#endif

#ifdef WOLFSSL_USER_IO //CYASSL_USER_IO

  #if defined(PJ_RTKE) || defined(PJ_THREADX) || defined(PJ_MTK)
    WOLFSSL_LOCAL
    int KN_IO_EmbedReceive(WOLFSSL *ssl, char *buf, int sz, void *ctx);
    WOLFSSL_LOCAL 
    int KN_IO_EmbedSend(WOLFSSL *ssl, char *buf, int sz, void *ctx);

   #ifdef WOLFSSL_DTLS
    WOLFSSL_LOCAL
    int KN_IO_EmbedReceiveFrom(WOLFSSL *ssl, char *buf, int sz, void *ctx);
    WOLFSSL_LOCAL 
    int KN_IO_EmbedSendTo(WOLFSSL *ssl, char *buf, int sz, void *ctx);
 //   CYASSL_LOCAL
 //   int KN_IO_EmbedGenerateCookie(byte *buf, int sz, void *ctx); /*Check the need*/
    #endif /*CYASSL_DTLS*/

  #endif /*PJ_RTKE || PJ_THREADX || PJ_MTK*/
#endif /*CYASSL_USER_IO*/


//wolfssl/wolfio.h
#if defined(POC_CDE_BREW)
	#define EWOULDBLOCK			AEE_NET_EWOULDBLOCK
	#define EAGAIN				AEE_NET_ERROR
	#define ECONNRESET			AEE_NET_ECONNRESET
	#define EINTR				AEE_NET_ERROR
	#define EPIPE				AEE_NET_EPIPE
	#define ECONNREFUSED		AEE_NET_ECONNREFUSED
	#define ECONNABORTED		AEE_NET_ECONNABORTED	
#endif
//wolfssl/wolfio.h

#if 0	
//wolfssl/wolfcrypt/settings.h
#if defined(POC_CDE_BREW)
#include "_kn_plt_cstd_lib_wrap.h"

#define SIZEOF_LONG KN_SIZEOF_LONG
#define SIZEOF_LONG_LONG KN_SIZEOF_LONGLONG
#define memcpy KN_MEMCPY
    #define XMEMCPY(d,s,l)    KN_Memcpy((KN_VOID*)(d),(KN_VOID*)(s),(KN_INT32)(l))
    #define XMEMSET(b,c,l)    KN_Memset((b),(c),(l))
    #define XMEMCMP(s1,s2,n)  KN_Memcmp((KN_CHAR*)(s1),(KN_CHAR*)(s2),(KN_INT32)(n))
    #define XMEMMOVE(d,s,l)   KN_Memmove((d),(s),(l))

    #define XSTRLEN(s1)       KN_STRLEN((s1))
    #define XSTRNCPY(s1,s2,n) KN_STRNCPY((s1),(s2),(n))
    /* strstr, strncmp, and strncat only used by CyaSSL proper, not required for
       CTaoCrypt only */
    #define XSTRSTR(s1,s2)    KN_STRSTR((s1),(s2))
    #define XSTRNSTR(s1,s2,n) KN_STRNSTR((s1),(s2),(n))
    #define XSTRNCMP(s1,s2,n) KN_STRNCMP((s1),(s2),(n))
    #define XSTRNCAT(s1,s2,n) KN_STRNCAT((s1),(s2),(n))
    #define XSTRNCASECMP(s1,s2,n) KN_STRNCASECMP((s1),(s2),(n))
	#define XTOLOWER(c)		  KN_TOLOWER((c))
#endif

/* Merging from 7.10 branch to 7.10 64-bit branch - Begin */
#if defined(PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK)
#include "_kn_plt_cstd_lib_wrap.h"
#define SIZEOF_LONG KN_SIZEOF_LONG
#define SIZEOF_LONG_LONG KN_SIZEOF_LONGLONG
/* Merging from 7.10 branch to 7.10 64-bit branch - End */
#endif
////wolfssl/wolfcrypt/settings.h
#endif

#endif