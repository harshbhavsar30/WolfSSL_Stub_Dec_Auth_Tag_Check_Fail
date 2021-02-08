/* aes.h
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */



/*  aes.h defines mini des openssl compatibility layer
 *
 */


#ifndef WOLFSSL_AES_H_
#define WOLFSSL_AES_H_

#include <wolfssl/wolfcrypt/settings.h>

#ifndef NO_AES
#include <wolfssl/openssl/ssl.h> /* for size_t */

#ifdef __cplusplus
    extern "C" {
#endif

/* This structure wrapper is done because there is no aes_new function with
 * OpenSSL compatibility layer. This makes code working with an AES structure
 * to need the size of the structure. */
typedef struct WOLFSSL_AES_KEY {
    ALIGN16 void *buf[(sizeof(Aes) / sizeof(void *)) + 1];
} WOLFSSL_AES_KEY;
typedef WOLFSSL_AES_KEY AES_KEY;

WOLFSSL_API int wolfSSL_AES_set_encrypt_key
    (const unsigned char *, const int bits, AES_KEY *);
WOLFSSL_API int wolfSSL_AES_set_decrypt_key
    (const unsigned char *, const int bits, AES_KEY *);
WOLFSSL_API void wolfSSL_AES_cbc_encrypt
    (const unsigned char *in, unsigned char* out, size_t len,
     AES_KEY *key, unsigned char* iv, const int enc);
WOLFSSL_API void wolfSSL_AES_ecb_encrypt
    (const unsigned char *in, unsigned char* out,
     AES_KEY *key, const int enc);
WOLFSSL_API void wolfSSL_AES_cfb128_encrypt
    (const unsigned char *in, unsigned char* out, size_t len,
     AES_KEY *key, unsigned char* iv, int* num, const int enc);

#define AES_cbc_encrypt     wolfSSL_AES_cbc_encrypt
#define AES_ecb_encrypt     wolfSSL_AES_ecb_encrypt
#define AES_cfb128_encrypt  wolfSSL_AES_cfb128_encrypt
#define AES_set_encrypt_key wolfSSL_AES_set_encrypt_key
#define AES_set_decrypt_key wolfSSL_AES_set_decrypt_key

#ifdef WOLFSSL_AES_DIRECT
WOLFSSL_API void wolfSSL_AES_encrypt
    (const unsigned char* input, unsigned char* output, AES_KEY *);
WOLFSSL_API void wolfSSL_AES_decrypt
    (const unsigned char* input, unsigned char* output, AES_KEY *);

#define AES_encrypt         wolfSSL_AES_encrypt
#define AES_decrypt         wolfSSL_AES_decrypt
#endif /* HAVE_AES_DIRECT */

#ifndef AES_ENCRYPT
#define AES_ENCRYPT AES_ENCRYPTION
#endif
#ifndef AES_DECRYPT
#define AES_DECRYPT AES_DECRYPTION
#endif

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* NO_AES */

#endif /* WOLFSSL_AES_H_ */
