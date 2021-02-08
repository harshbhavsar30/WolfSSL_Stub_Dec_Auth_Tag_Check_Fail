/* deos_malloc.c
 *
 * Copyright (C) 2006-2020 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>

#define ROUND_UP(x, align)  (((int) (x) + (align - 1)) & ~(align - 1))
#define SIZEOF_HEADER sizeof(size_t)  /* tracks size of allocated block */

#define HEAP_SIZE_MAX   (1*1024*1024)

static size_t allocatedMemory = 0;

size_t getMemAllocatedSize_deos(size_t* size){

    if (size)
        *size = allocatedMemory;

    return allocatedMemory;
}

/* Simply returns without freeing any memory. */

void free_deos(void *ptr) {
    //printf("fake free_deos()\n");
    return;
}

void *realloc_deos(void *ptr, size_t size) {
    void *newptr;

    if (size == 0)
        return ptr;
    newptr = malloc_deos(size);

    if (ptr != NULL && newptr != NULL) {

        if ( *((char *)ptr - SIZEOF_HEADER) < *((char *)newptr - SIZEOF_HEADER))
            size = *((char *)ptr - SIZEOF_HEADER);

        XMEMCPY((char *) newptr, (const char *) ptr, size);
        free_deos(ptr);
    }

    return newptr;
}

void *malloc_deos(size_t size) {
    PDEOS_SYSTEM_INFO systemInfoPtr;
    static VirtualAddressTYP heapAddr = NULL;
    static VirtualAddressTYP freeAddr = NULL;
    VirtualAddressTYP retAddr = NULL;
    DWORD allocationSize = 0;
    static int initialized = 0;

    if (size <= 0)
        return NULL;

    if (!initialized) {
        systemInfoPtr = (PDEOS_SYSTEM_INFO)getSystemInfoDEOS();
        freeAddr = (VirtualAddressTYP)getNextLibraryStartAddress();
        allocationSize = (((HEAP_SIZE_MAX - 1) / systemInfoPtr->dwPageSize) + 1) *
                         systemInfoPtr->dwPageSize;

        if (virtualAllocDEOS(freeAddr, allocationSize) != allocSuccess){
            printf("ERROR: virtualAllocDEOS failed\n");
            return NULL;
        }

        setNextLibraryStartAddress(freeAddr + allocationSize);
        heapAddr = freeAddr;

        initialized = 1;
    }

    size = ROUND_UP(size, sizeof(size_t));

    if ((size + SIZEOF_HEADER) > (HEAP_SIZE_MAX - (freeAddr - heapAddr))){
        printf("ERROR: malloc_deos cannot allocate from heap memory anymore\n");
        return NULL;
    }

    *freeAddr = size;
    freeAddr += SIZEOF_HEADER;
    retAddr = freeAddr;
    XMEMSET(retAddr, 0, size);
    freeAddr += size;
    allocatedMemory += size;

    return retAddr;
}
