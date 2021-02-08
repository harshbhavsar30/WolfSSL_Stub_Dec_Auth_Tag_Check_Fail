/* sha3.h
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* sha3.h for openssl */


#ifndef WOLFSSL_SHA3_H_
#define WOLFSSL_SHA3_H_

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/types.h>

#ifdef WOLFSSL_PREFIX
#include "prefix_sha.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


/* Using ALIGN16 because when AES-NI is enabled digest and buffer in Sha3
 * struct are 16 byte aligned. Any dereference to those elements after casting
 * to Sha3 is expected to also be 16 byte aligned addresses.  */
struct WOLFSSL_SHA3_CTX {
    /* big enough to hold wolfcrypt Sha3, but check on init */
    ALIGN16 void* holder[(424 + WC_ASYNC_DEV_SIZE) / sizeof(void*)];
};

#ifndef WOLFSSL_NOSHA3_224
typedef struct WOLFSSL_SHA3_CTX WOLFSSL_SHA3_224_CTX;

WOLFSSL_API int wolfSSL_SHA3_224_Init(WOLFSSL_SHA3_224_CTX*);
WOLFSSL_API int wolfSSL_SHA3_224_Update(WOLFSSL_SHA3_224_CTX*, const void*,
                                     unsigned long);
WOLFSSL_API int wolfSSL_SHA3_224_Final(unsigned char*, WOLFSSL_SHA3_224_CTX*);

enum {
    SHA3_224_DIGEST_LENGTH = 28
};

typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX;

#define SHA3_224_Init   wolfSSL_SHA3_224_Init
#define SHA3_224_Update wolfSSL_SHA3_224_Update
#define SHA3_224_Final  wolfSSL_SHA3_224_Final
#if defined(NO_OLD_WC_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    #define SHA3_224 wolfSSL_SHA3_224
#endif
#endif /* WOLFSSL_NOSHA3_224 */


#ifndef WOLFSSL_NOSHA3_256
typedef struct WOLFSSL_SHA3_CTX WOLFSSL_SHA3_256_CTX;


WOLFSSL_API int wolfSSL_SHA3_256_Init(WOLFSSL_SHA3_256_CTX*);
WOLFSSL_API int wolfSSL_SHA3_256_Update(WOLFSSL_SHA3_256_CTX*, const void*,
                                     unsigned long);
WOLFSSL_API int wolfSSL_SHA3_256_Final(unsigned char*, WOLFSSL_SHA3_256_CTX*);

enum {
    SHA3_256_DIGEST_LENGTH = 32
};


typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX;

#define SHA3_256_Init   wolfSSL_SHA3_256_Init
#define SHA3_256_Update wolfSSL_SHA3_256_Update
#define SHA3_256_Final  wolfSSL_SHA3_256_Final
#if defined(NO_OLD_WC_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    #define SHA3_256 wolfSSL_SHA3_256
#endif
#endif /* WOLFSSL_NOSHA3_256 */


typedef struct WOLFSSL_SHA3_CTX WOLFSSL_SHA3_384_CTX;

WOLFSSL_API int wolfSSL_SHA3_384_Init(WOLFSSL_SHA3_384_CTX*);
WOLFSSL_API int wolfSSL_SHA3_384_Update(WOLFSSL_SHA3_384_CTX*, const void*,
	                                 unsigned long);
WOLFSSL_API int wolfSSL_SHA3_384_Final(unsigned char*, WOLFSSL_SHA3_384_CTX*);

enum {
    SHA3_384_DIGEST_LENGTH = 48
};

typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX;

#define SHA3_384_Init   wolfSSL_SHA3_384_Init
#define SHA3_384_Update wolfSSL_SHA3_384_Update
#define SHA3_384_Final  wolfSSL_SHA3_384_Final
#if defined(NO_OLD_WC_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    #define SHA3_384 wolfSSL_SHA3_384
#endif


#ifndef WOLFSSL_NOSHA3_512

typedef struct WOLFSSL_SHA3_CTX WOLFSSL_SHA3_512_CTX;

WOLFSSL_API int wolfSSL_SHA3_512_Init(WOLFSSL_SHA3_512_CTX*);
WOLFSSL_API int wolfSSL_SHA3_512_Update(WOLFSSL_SHA3_512_CTX*, const void*,
	                                 unsigned long);
WOLFSSL_API int wolfSSL_SHA3_512_Final(unsigned char*, WOLFSSL_SHA3_512_CTX*);

enum {
    SHA3_512_DIGEST_LENGTH = 64
};


typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX;

#define SHA3_512_Init   wolfSSL_SHA3_512_Init
#define SHA3_512_Update wolfSSL_SHA3_512_Update
#define SHA3_512_Final  wolfSSL_SHA3_512_Final
#if defined(NO_OLD_WC_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    #define SHA3_512 wolfSSL_SHA3_512
#endif
#endif /* WOLFSSL_NOSHA3_512 */




#ifdef __cplusplus
    }  /* extern "C" */
#endif


#endif /* WOLFSSL_SHA3_H_ */

