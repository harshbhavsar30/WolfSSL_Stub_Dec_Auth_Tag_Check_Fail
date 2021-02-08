#include <port/inc/kn_asn_port.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>

#ifndef NO_ASN_TIME
#if defined( USER_TIME )
    
struct tm {
int tm_sec;     /* seconds after the minute [0-60] */
int tm_min;     /* minutes after the hour [0-59] */
int tm_hour;    /* hours since midnight [0-23] */
int tm_mday;    /* day of the month [1-31] */
int tm_mon;     /* months since January [0-11] */
int tm_year;    /* years since 1900 */
int tm_wday;    /* days since Sunday [0-6] */
int tm_yday;    /* days since January 1 [0-365] */
int tm_isdst;   /* Daylight Savings Time flag */
long    tm_gmtoff;  /* offset from CUT in seconds */
char    *tm_zone;   /* timezone abbreviation */
};

struct tm* KN_gmtime(const time_t* timer)
{
    #define YEAR0          1900
    #define EPOCH_YEAR     1970
    #define SECS_DAY       (24L * 60L * 60L)
    #define LEAPYEAR(year) (!((year) % 4) && (((year) % 100) || !((year) %400)))
    #define YEARSIZE(year) (LEAPYEAR(year) ? 366 : 365)

    static const int _ytab[2][12] =
    {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    static struct tm st_time;
    struct tm* ret = &st_time;
    time_t secs = *timer;
    unsigned long dayclock, dayno;
    int year = EPOCH_YEAR;

    dayclock = (unsigned long)secs % SECS_DAY;
    dayno    = (unsigned long)secs / SECS_DAY;

    ret->tm_sec  = (int) dayclock % 60;
    ret->tm_min  = (int)(dayclock % 3600) / 60;
    ret->tm_hour = (int) dayclock / 3600;
    ret->tm_wday = (int) (dayno + 4) % 7;        /* day 0 a Thursday */

    while(dayno >= (unsigned long)YEARSIZE(year)) {
        dayno -= YEARSIZE(year);
        year++;
    }

    ret->tm_year = year - YEAR0;
    ret->tm_yday = (int)dayno;
    ret->tm_mon  = 0;

    while(dayno >= (unsigned long)_ytab[LEAPYEAR(year)][ret->tm_mon]) {
        dayno -= _ytab[LEAPYEAR(year)][ret->tm_mon];
        ret->tm_mon++;
    }

    ret->tm_mday  = (int)++dayno;
    ret->tm_isdst = 0;

    return ret;
}
#endif
#endif

#if defined(NO_DEV_RANDOM)
#if defined(PJ_RTKE) || defined(PJ_THREADX) || defined (PJ_MTK)
int wc_GenerateSeed(OS_Seed* os, byte* output, word32 sz)
{
	KN_GenerateSeed(output);
    return 0;
}
#endif
#endif

#if defined(PJ_RTKE) || defined(PJ_THREADX) || defined(PJ_MTK)
int InitMutex(wolfSSL_Mutex* m)
{
	KN_MUTEX_TYPE eMtype = KN_MUTEX_NORMAL;
	if (KN_InitMutex(m,"CyaSSL Mutex",eMtype) == KN_FALSE)
		return BAD_MUTEX_E;
	else
		return 0;
}

int FreeMutex(wolfSSL_Mutex* m)
{
	KN_FreeMutex(m);
	return 0;
}

int LockMutex(wolfSSL_Mutex* m)
{
	if (KN_LockMutex(m) == KN_FALSE)
		return BAD_MUTEX_E;
	else
		return 0;
}

int UnLockMutex(wolfSSL_Mutex* m)
{
	if(KN_UnLockMutex(m) == KN_TRUE)
	return 0;
}
#endif


