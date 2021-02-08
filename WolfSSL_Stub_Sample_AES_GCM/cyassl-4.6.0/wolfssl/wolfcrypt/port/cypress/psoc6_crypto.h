/* psoc6_crypto.h
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _PSOC6_CRYPTO_PORT_H_
#define _PSOC6_CRYPTO_PORT_H_

#include <wolfssl/wolfcrypt/settings.h>
#ifdef USE_FAST_MATH
    #include <wolfssl/wolfcrypt/tfm.h>
#elif defined WOLFSSL_SP_MATH
    #include <wolfssl/wolfcrypt/sp_int.h>
#else
    #include <wolfssl/wolfcrypt/integer.h>
#endif
#include "cy_crypto_core_sha.h"
#include "cy_device_headers.h"
#include "psoc6_02_config.h"
#include "cy_crypto_common.h"
#include "cy_crypto_core.h"

#ifdef WOLFSSL_SHA512
typedef struct wc_Sha512 {
    cy_stc_crypto_sha_state_t hash_state;
    cy_en_crypto_sha_mode_t sha_mode;
    cy_stc_crypto_v2_sha512_buffers_t sha_buffers;
} wc_Sha512;

#define WC_SHA512_TYPE_DEFINED
#include <wolfssl/wolfcrypt/sha512.h>
#endif

#ifndef NO_SHA256

typedef struct wc_Sha256 {
    cy_stc_crypto_sha_state_t hash_state;
    cy_en_crypto_sha_mode_t sha_mode;
    cy_stc_crypto_v2_sha256_buffers_t sha_buffers;
} wc_Sha256;

#include <wolfssl/wolfcrypt/sha.h>
#include <wolfssl/wolfcrypt/sha256.h>
#endif /* !def NO_SHA256 */


#ifdef HAVE_ECC
#include <wolfssl/wolfcrypt/ecc.h>
int psoc6_ecc_verify_hash_ex(mp_int *r, mp_int *s, const byte* hash,
                    word32 hashlen, int* verif_res, ecc_key* key);
#endif /* HAVE_ECC */

#define PSOC6_CRYPTO_BASE ((CRYPTO_Type*) CRYPTO_BASE)

/* Crypto HW engine initialization */
int psoc6_crypto_port_init(void);

#endif /* _PSOC6_CRYPTO_PORT_H_ */
