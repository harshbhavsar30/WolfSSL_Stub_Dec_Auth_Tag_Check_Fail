
TOP_PATH   := $(call my-dir)/../../../../

# Compile wolfSSL shared library
# Assumes wolfcrypt-android-ndk directory is placed at:
# <wolfssl_package>/IDE/Android/wolfcrypt-android-ndk
include $(CLEAR_VARS)
LOCAL_PATH              := $(TOP_PATH)
LOCAL_MODULE            := libwolfssl
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES        := $(LOCAL_PATH)
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/../../platform/inc/
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/../../build/kodiak/android/platform/inc
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/../../GHdr
LOCAL_CFLAGS            := -DNO_DSA -DNO_PSK -DNO_MD4 -DNO_HC128 \
                           -DNO_RABBIT -DWOLFSSL_SHA512 -DWOLFSSL_SHA384 \
                           -DHAVE_AESGCM -DHAVE_FIPS -DHAVE_FIPS_VERSION=2 -DHAVE_HASHDRBG \
						   -DWOLFSSL_DTLS -DOPENSSL_EXTRA -DHAVE_SNI \
                           -DHAVE_TLS_EXTENSIONS -DWOLFSSL_STATIC_RSA \
						   -DMSI_E2E -DWOLFSSL_KEY_GEN -DWOLFSSL_AES_DIRECT -DHAVE_AES_KEYWRAP \
						   -DWOLFSSL_PUB_PEM_TO_DER -DHAVE_RSA4096_SUPPORT -DHAVE_PKCS7 -DHAVE_X963_KDF \
                           -DHAVE_ECC -DWOLFSSL_JNI -DUSE_FAST_MATH -DWOLFSSL_ALLOW_TLSV10 -DWOLFSSL_DTLS_ALLOW_FUTURE \
						   -DWOLFSSL_AES_COUNTER -DHAVE_AES_ECB -DWC_RSA_PSS -DWOLFSSL_EVP_INCLUDED -Wall -Wno-unused -O2
						   
LOCAL_SRC_FILES         := wolfcrypt/src/wolfcrypt_first.c \
                           wolfcrypt/src/hmac.c \
                           wolfcrypt/src/random.c \
                           wolfcrypt/src/sha256.c \
						   wolfcrypt/src/hash.c \
                           wolfcrypt/src/rsa.c \
                           wolfcrypt/src/aes.c \
                           wolfcrypt/src/des3.c \
                           wolfcrypt/src/sha.c \
                           wolfcrypt/src/sha512.c \
						   wolfcrypt/src/fips.c \
                           wolfcrypt/src/fips_test.c \
						   wolfcrypt/src/wolfcrypt_last.c \
                           wolfcrypt/src/logging.c \
                           wolfcrypt/src/wc_encrypt.c \
                           wolfcrypt/src/wc_port.c \
                           wolfcrypt/src/error.c \
                           wolfcrypt/src/signature.c \
                           wolfcrypt/src/memory.c \
                           wolfcrypt/src/dh.c \
                           wolfcrypt/src/asn.c \
					       wolfcrypt/src/coding.c \
                           wolfcrypt/src/arc4.c \
                           wolfcrypt/src/md5.c \
                           wolfcrypt/src/tfm.c \
                           wolfcrypt/src/ecc.c \
			   			   wolfcrypt/src/wolfmath.c \
						   wolfcrypt/src/pwdbased.c \
						   wolfcrypt/src/pkcs7.c \
						   wolfcrypt/src/pkcs12.c \
                           src/internal.c \
                           src/wolfio.c \
                           src/keys.c \
                           src/ssl.c \
                           src/tls.c \
						   port/src/kn_asn_port.c \
						   port/src/kn_src_port.c 
						   
include $(BUILD_SHARED_LIBRARY)
