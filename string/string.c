// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
    char *dest = destination;
    const char *src = source;

    while (*src != '\0') {
        *dest++ = *src++;
    }

    *dest = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
    char *dest = destination;
    const char *src = source;

    while (len > 0 && (*src != '\0')) {
        *dest++ = *src++;
        len--;
    }

	// Complete with 0 until the end
    while (len > 0) {
        *dest++ = '\0';
        len--;
    }

    return destination;
}

char *strcat(char *destination, const char *source)
{
    char *dest = destination;
    const char *src = source;

    // Point to the end
    while (*dest != '\0') {
        dest++;
    }

    // Append characters
    while (*src != '\0') {
        *dest++ = *src++;
    }

    *dest = '\0';

    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
    char *dest = destination;
    const char *src = source;

    // Point to the end
    while (*dest != '\0') {
        dest++;
    }

    // Append characters
    while (*src != '\0' && len-- > 0) {
        *dest++ = *src++;
    }

    *dest = '\0';

    return destination;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    return (*str1 == *str2) ? 0 : ((*str1 < *str2) ? -1 : 1);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    for (size_t i = 0; i < len; i++) {
		// If the characters differ
        if (str1[i] != str2[i]) {
            return (str1[i] < str2[i]) ? -1 : 1;
        }
		// End of the first string
        if (str1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
    while (*str != '\0') {
        if (*str == c) {
            return (char *)str;
        }
        
        str++;
    }
    
    if (c == '\0') {
        return (char *)str;
    }
    
    return NULL;
}

char *strrchr(const char *str, int c)
{
    if (c == '\0') {
        return (char *)str;
    }

    const char *final = str + strlen(str);
    
    while (final >= str) {
        if (*final == c) {
            return (char *)final;
        }
        
        final--;
    }
    
    return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
    size_t needle_len = strlen(needle);
    size_t haystack_len = strlen(haystack);
    
    if (needle_len > haystack_len) {
        return NULL;
    }
    
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        if (memcmp(haystack + i, needle, needle_len) == 0) {
            return (char *)(haystack + i);
        }
    }
    
    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);

    if (needle_len > haystack_len) {
        return NULL;
    }

    const char *p = haystack + haystack_len - needle_len;

    while (p >= haystack) {
        if (memcmp(p, needle, needle_len) == 0) {
            return (char *)p;
        }
        p--;
    }

    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
    char *dst = (char *)destination;
    const char *src = (const char *)source;
    
    while (num--) {
        *dst++ = *src++;
    }
    
    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
    char *dst = (char *)destination;
    const char *src = (const char *)source;
    
    if (src < dst) {
        src += num - 1;
        dst += num - 1;
        
        while (num--) {
            *dst-- = *src--;
        }
    } else {
        while (num--) {
            *dst++ = *src++;
        }
    }
    
    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    const unsigned char *p1 = (const unsigned char *)ptr1;
    const unsigned char *p2 = (const unsigned char *)ptr2;
    
    while (num--) {
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }
        
        p1++;
        p2++;
    }
    
    return 0;
}

void *memset(void *source, int value, size_t num)
{
    unsigned char *p = (unsigned char *)source;
    unsigned char v = (unsigned char)value;
    
    while (num--) {
        *p++ = v;
    }
    
    return source;
}
