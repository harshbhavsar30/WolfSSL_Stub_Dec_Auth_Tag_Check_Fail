/* crypto.h
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* crypto.h for openSSL */

#ifndef WOLFSSL_CRYPTO_H_
#define WOLFSSL_CRYPTO_H_

#include <wolfssl/wolfcrypt/settings.h>

#include <wolfssl/openssl/opensslv.h>
#include <wolfssl/openssl/conf.h>

#ifdef WOLFSSL_PREFIX
#include "prefix_crypto.h"
#endif

typedef struct WOLFSSL_INIT_SETTINGS {
    char* appname;
} WOLFSSL_INIT_SETTINGS;

typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS;

WOLFSSL_API const char*   wolfSSLeay_version(int type);
WOLFSSL_API unsigned long wolfSSLeay(void);
WOLFSSL_API unsigned long wolfSSL_OpenSSL_version_num(void);

#ifdef OPENSSL_EXTRA
#include <stdint.h>

WOLFSSL_API void wolfSSL_OPENSSL_free(void*);
WOLFSSL_API void *wolfSSL_OPENSSL_malloc(size_t a);

WOLFSSL_API int wolfSSL_OPENSSL_init_crypto(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings);
#endif

#define CRYPTO_THREADID void

#define SSLeay_version wolfSSLeay_version
#define SSLeay wolfSSLeay
#define OpenSSL_version_num wolfSSL_OpenSSL_version_num

#ifdef WOLFSSL_QT
    #define SSLEAY_VERSION 0x10001000L
#else
    #define SSLEAY_VERSION 0x0090600fL
#endif
#define SSLEAY_VERSION_NUMBER SSLEAY_VERSION
#define CRYPTO_lock wc_LockMutex_ex

/* this function was used to set the default malloc, free, and realloc */
#define CRYPTO_malloc_init() 0 /* CRYPTO_malloc_init is not needed */

#define OPENSSL_free wolfSSL_OPENSSL_free
#define OPENSSL_malloc wolfSSL_OPENSSL_malloc

#define OPENSSL_INIT_ENGINE_ALL_BUILTIN 0x00000001L
#define OPENSSL_INIT_ADD_ALL_CIPHERS    0x00000004L
#define OPENSSL_INIT_ADD_ALL_DIGESTS    0x00000008L
#define OPENSSL_INIT_LOAD_CONFIG        0x00000040L

#define OPENSSL_init_crypto wolfSSL_OPENSSL_init_crypto


#if defined(OPENSSL_ALL) || defined(HAVE_STUNNEL) || defined(WOLFSSL_NGINX) || \
    defined(WOLFSSL_HAPROXY) || defined(OPENSSL_EXTRA) || defined(HAVE_EX_DATA)
#define CRYPTO_set_mem_ex_functions      wolfSSL_CRYPTO_set_mem_ex_functions
#define FIPS_mode                        wolfSSL_FIPS_mode
#define FIPS_mode_set                    wolfSSL_FIPS_mode_set
typedef struct CRYPTO_EX_DATA            CRYPTO_EX_DATA;
typedef void (CRYPTO_free_func)(void*parent, void*ptr, CRYPTO_EX_DATA *ad, int idx,
        long argl, void* argp);
#define CRYPTO_THREADID_set_callback wolfSSL_THREADID_set_callback
#define CRYPTO_THREADID_set_numeric wolfSSL_THREADID_set_numeric

#define CRYPTO_r_lock wc_LockMutex_ex
#define CRYPTO_unlock wc_LockMutex_ex

#define CRYPTO_THREAD_lock wc_LockMutex
#define CRYPTO_THREAD_r_lock wc_LockMutex
#define CRYPTO_THREAD_unlock wc_UnLockMutex

#endif /* OPENSSL_ALL || HAVE_STUNNEL || WOLFSSL_NGINX || WOLFSSL_HAPROXY || HAVE_EX_DATA */

#endif /* header */
