#ifndef KN_WCPORT_PORT_H
#define KN_WCPORT_PORT_H

#ifndef NO_FILESYSTEM
#if defined(POC_CDE_BREW) || defined(PJ_RTKE) || defined(PJ_THREADX) || defined(PJ_MTK)
#include <stdio.h>
    #include "_kn_plt_cstd_lib_wrap.h"
    #define XFILE      KN_FILE*
//    #define XFOPEN     KN_FOPEN 
    #define XFSEEK     KN_FSEEK
    #define XFTELL     KN_FTELL
    #define XREWIND    KN_REWIND
    #define XFREAD     KN_FREAD
    #define XFWRITE    KN_FWRITE
    #define XFCLOSE    KN_FCLOSE
    #define XSEEK_SET  KN_SEEK_SET
	#define XSEEK_CUR  KN_SEEK_CUR
	#define XSEEK_END  KN_SEEK_END
    #define XBADFILE   NULL
#endif 
#endif
/* Merging from 7.10 branch to 7.10 64-bit branch - End */	

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


//wfcryptypes
#if defined(XMALLOC_USER)
/* Merging from 7.10 branch to 7.10 64-bit branch - Begin */
#if defined(POC_CDE_BREW) || defined (PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK)
    #include "_kn_plt_cstd_lib_wrap.h"
    #define XMALLOC(s, h, t)     ((void)h, (void)t, KN_MALLOC((s)))
    #define XFREE(p, h, t)       {void* xp = (p); if((xp)) KN_FREE((xp));}
    #define XREALLOC(p, n, h, t) ((void)h, (void)t, KN_Realloc((KN_VOID*)(p),(KN_INT32)(n)))
#endif	
#endif

#if defined(POC_CDE_BREW)
	#include "_kn_plt_cstd_lib_wrap.h"
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
	#define GenerateSeed	KN_GenerateSeed
	#define size_t unsigned int
	#define NULL 0
	#define malloc KN_MALLOC
	#define free KN_FREE
	#define realloc KN_REALLOC
#endif	

#if defined (PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK)
    	#include "_kn_plt_cstd_lib_wrap.h"
	    #define XMEMCPY(d,s,l)    KN_Memcpy((KN_VOID*)(d),(KN_VOID*)(s),(KN_INT32)(l))
    	#define XMEMSET(b,c,l)    KN_Memset((b),(c),(l))
	    #define XMEMCMP(s1,s2,n)  KN_Memcmp((KN_CHAR*)(s1),(KN_CHAR*)(s2),(KN_INT32)(n))
    	#define XMEMMOVE(d,s,l)   KN_Memmove((d),(s),(l))

	    #define XSTRLEN(s1)       KN_STRLEN((s1))
    	#define XSTRNCPY(s1,s2,n) KN_STRNCPY((s1),(s2),(n))
    	/* strstr, strncmp, and strncat only used by CyaSSL proper, not required for
       	CTaoCrypt only */
	    #define XSTRSTR(s1,s2)    KN_STRSTR((s1),(s2))
    	#define XSTRNSTR(s1,s2,n) mystrnstr((s1),(s2),(n))
	    #define XSTRNCMP(s1,s2,n) KN_STRNCMP((s1),(s2),(n))
    	#define XSTRNCAT(s1,s2,n) KN_STRNCAT((s1),(s2),(n))
	    #define XSTRNCASECMP(s1,s2,n) KN_STRNCASECMP((s1),(s2),(n))
		#define XTOLOWER(c)		  KN_TOLOWER((c))
/* Merging from 7.10 branch to 7.10 64-bit branch - End */	
#endif

#if defined (PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK)
    	#include "_kn_plt_cstd_lib_wrap.h"	
		#define XTOLOWER(c)		  KN_TOLOWER((c))
	/* Merging from 7.10 branch to 7.10 64-bit branch - End */
#endif
// --

#endif//KN_WCPORT_PORT_H