#include "string.h"

void *memset(void* dst, int val, size_t n)
{
	char* d = (char*)dst;
	while (n--)
		*d++ = val;
	return dst;
}

void *memset16(void *dst, int val, size_t n)
{
	short* d = (short*)dst;
	while (n--)
		*d++ = val;
	return dst;
}

struct int24_t
{
	int24_t(int v) {
		memcpy(data, &v, 3);
	}
	unsigned char data[3];
};

void *memset24(void* dst, int val, size_t n)
{
	int24_t* d = (int24_t*)dst;
	while (n--)
		*d++ = val;
	return dst;
}

void *memset32(void *dst, int val, size_t n)
{
	long* d = (long*)dst;
	while (n--)
		*d++ = val;
	return dst;
}

void *memcpy(void* dst, const void* src, size_t n)
{
	char* d = (char*)dst;
	char* s = (char*)src;
	while (n--)
		*d++ = *s++;
	return dst;
}

size_t strlen(const char* str)
{
	const char* s;
	for (s = str; *s; ++s)
		;
	return (s - str);
}