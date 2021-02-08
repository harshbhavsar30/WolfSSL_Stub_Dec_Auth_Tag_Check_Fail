/* wolfcrypt_first.c
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


/* This file needs to be linked first in order to work correctly */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

/* in case user set HAVE_FIPS there */
#include <cyassl/ctaocrypt/settings.h>

#ifdef HAVE_FIPS

#ifdef USE_WINDOWS_API
    #pragma code_seg(".fipsA$a")
    #pragma const_seg(".fipsB$a")
#endif


/* read only start address */
const unsigned int wolfCrypt_FIPS_ro_start[] =
{ 0x1a2b3c4d, 0x00000001 };


/* first function of text/code segment */
int wolfCrypt_FIPS_first(void);
int wolfCrypt_FIPS_first(void)
{
    return 0;
}


#endif /* HAVE_FIPS */

