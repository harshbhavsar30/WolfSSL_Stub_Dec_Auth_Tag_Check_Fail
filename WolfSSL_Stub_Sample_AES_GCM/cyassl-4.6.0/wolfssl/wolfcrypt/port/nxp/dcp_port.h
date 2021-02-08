/* dcp_port.h
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef _DCP_PORT_H_
#define _DCP_PORT_H_

#include <wolfssl/wolfcrypt/settings.h>
#ifdef USE_FAST_MATH
    #include <wolfssl/wolfcrypt/tfm.h>
#elif defined WOLFSSL_SP_MATH
    #include <wolfssl/wolfcrypt/sp_int.h>
#else
    #include <wolfssl/wolfcrypt/integer.h>
#endif

#include <wolfssl/wolfcrypt/aes.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_dcp.h"

int wc_dcp_init(void);

#ifndef NO_AES
int  DCPAesInit(Aes* aes);
void DCPAesFree(Aes *aes);

int  DCPAesSetKey(Aes* aes, const byte* key, word32 len, const byte* iv,
                          int dir);
int  DCPAesCbcEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
int  DCPAesCbcDecrypt(Aes* aes, byte* out, const byte* in, word32 sz);
#endif

#ifdef HAVE_AES_ECB
int  DCPAesEcbEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
int  DCPAesEcbDecrypt(Aes* aes, byte* out, const byte* in, word32 sz);
#endif

#ifndef NO_SHA256
typedef struct wc_Sha256_DCP {
    dcp_handle_t handle;
    dcp_hash_ctx_t ctx;
} wc_Sha256;
#define WC_SHA256_TYPE_DEFINED

void DCPSha256Free(wc_Sha256 *sha256);

#endif

#ifndef NO_SHA
typedef struct wc_Sha_DCP {
    dcp_handle_t handle;
    dcp_hash_ctx_t ctx;
} wc_Sha;
#define WC_SHA_TYPE_DEFINED

void DCPShaFree(wc_Sha *sha);
#endif

#endif
