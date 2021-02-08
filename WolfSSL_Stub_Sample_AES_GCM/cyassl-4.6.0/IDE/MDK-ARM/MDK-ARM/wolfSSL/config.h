/* config.h
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef MDK_CONFIG_H__
#define MDK_CONFIG_H__
/**** wolfSSL for KEIL-RL Configuration ****/

#define __CORTEX_M3__
#define WOLFSSL_MDK_ARM

#define NO_WRITEV
#define NO_WOLFSSL_DIR
#define NO_MAIN_DRIVER

/* for Retarget.c */
#define  STDIO
#define BENCH_EMBEDDED

#define WOLFSSL_DER_LOAD
#define HAVE_NULL_CIPHER
#define WOLFSSL_USER_TIME
#define NO_TIME_H
static  int ValidateDate(const unsigned char* date, unsigned char format, int dateType){ return 1; }

#if    defined(MDK_CONF_RTX_TCP_FS)
#include "config-RTX-TCP-FS.h"
#elif  defined(MDK_CONF_TCP_FS)
#include "config-TCP-FS.h"
#elif  defined(MDK_CONF_FS)
#include "config-FS.h"
#elif  defined(MDK_CONF_BARE_METAL)
#include "config-BARE-METAL.h"
#elif  defined(MDK_WOLFLIB)
#include "config-WOLFLIB.h"
#endif

#endif
