/* wolfcrypt_last.c
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* This file needs to be linked last in order to work correctly */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

/* in case user set HAVE_FIPS there */
#include <wolfssl/wolfcrypt/settings.h>

#ifdef HAVE_FIPS

#ifdef USE_WINDOWS_API
    #pragma code_seg(".fipsA$q")
    #pragma const_seg(".fipsB$q")
#endif


/* last function of text/code segment */
/* this function needs to be different than wolfCrypt_FIPS_first() */
int wolfCrypt_FIPS_last(void);
int wolfCrypt_FIPS_last(void)
{
    return 1;
}


/* read only end address */
const unsigned int wolfCrypt_FIPS_ro_end[] =
{ 0x1a2b3c4d, 0xffffffff };


#endif /* HAVE_FIPS */

