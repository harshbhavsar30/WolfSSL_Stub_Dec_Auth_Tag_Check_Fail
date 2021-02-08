# The ARMv7 is significanly faster due to the use of the hardware FPU
APP_ABI := armeabi arm64-v8a #armeabi-v7a

export ADDRESS_SANITIZER = false
ifeq ($(ADDRESS_SANITIZER),true)
NDK_TOOLCHAIN_VERSION=clang
else
NDK_TOOLCHAIN_VERSION=4.9
endif

APP_PLATFORM := android-21
APP_CFLAGS += -fmerge-constants -fno-unroll-loops -fno-unwind-tables -fno-asynchronous-unwind-tables -ffunction-sections -fdata-sections   -Wl,-gc-sections -Wl,--strip-all -Wformat -Wno-error=format-security
LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
TARGET_DISABLE_FORMAT_STRING_CFLAGS := -Wno-error=format-security
NDK_PROJECT_PATH := $(call my-dir)/
APP_BUILD_SCRIPT := $(call my-dir)/Android.mk


