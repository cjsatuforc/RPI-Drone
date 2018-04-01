#pragma once
#include <stddef.h>

size_t strlen(const char* str);

void *memset(void* dst, int val, size_t len);
void *memcpy(void* dst, const void * src, size_t len);

//dst -> pointer to destination, val -> value to be stored (first 2 bytes), len -> size in (bytes * 2) to be set
void *memset16(void* dst, int val, size_t len);

//dst -> pointer to destination, val -> value to be stored (first 3 bytes), len -> size in (bytes * 3) to be set
void *memset24(void* dst, int val, size_t len);

//dst -> pointer to destination, val -> value to be stored, len -> size in (bytes * 4) to be set
void *memset32(void* dst, int val, size_t len);