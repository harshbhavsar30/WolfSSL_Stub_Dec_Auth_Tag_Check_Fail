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
#include <cyassl/ctaocrypt/settings.h>

#ifdef HAVE_FIPS

#ifdef USE_WINDOWS_API
    #pragma code_seg(".fipsA$l")
    #pragma const_seg(".fipsB$l")
#endif


/* last function of text/code segment */
int wolfCrypt_FIPS_last(void);
int wolfCrypt_FIPS_last(void)
{
    return 0;
}


/* read only end address */
const unsigned int wolfCrypt_FIPS_ro_end[] =
{ 0x1a2b3c4d, 0xffffffff };


#endif /* HAVE_FIPS */

