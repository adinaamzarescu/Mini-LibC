// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
    // Copy the source and destination
    char *dest = destination;
    const char *src = source;

    // Copy the characters from one string to another 
    // until it reaches the null character '\0'
    while (*src != '\0') {
        *dest++ = *src++;
    }

    *dest = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
    // Copy the source and destination
    char *dest = destination;
    const char *src = source;

    // Copy the characters from one string to another 
    // until it reaches the null character '\0'
    // or until the desired length is reached
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
    // Copy the source and destination
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
    // Copy the source and destination
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
    // Check if both strings are not empty
    // and if the current character in both strings are equal
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    // The function returns 0 if the two strings are equal, 
    // -1 if the first string is less than the second string, 
    // and 1 if the first string is greater than the second string
    return (*str1 == *str2) ? 0 : ((*str1 < *str2) ? -1 : 1);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    // Check if both strings are not empty
    // and if the current character in both strings are equal
    // but also check if the desired length has been reached
    while (*str1 != '\0' && *str2 != '\0' && len > 0 && *str1 == *str2) {
        str1++;
        str2++;
        len--;
    }
    // Here the additional condition for the strings to be equal
    // is for the length variable to be 0
    return (len == 0 || *str1 == *str2) ? 0 : ((*str1 < *str2) ? -1 : 1);
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
    // Check if the current character
    // is not the NULL char
    while (*str != '\0') {
        // Check if the current char is
        // the one the function is searching for
        if (*str == c) {
            // In this case the function returns
            // a pointer to that character
            // The type cast is used because the
            // pointer is not modifying the contents of
            // the string
            return (char *)str;
        }
        
        str++;
    }
    // If the loop stops because it reached the end
    // of the string, a check is made in order
    // to see if c is the null character
    if (c == '\0') {
        return (char *)str;
    }
    // If the character is not inside the string return null
    return NULL;
}

char *strrchr(const char *str, int c)
{
    // Check if c is the null character
    if (c == '\0') {
        return (char *)str;
    }
    // In order to move from the end to the beginning
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
    
    // There is impossible for the needle to be located
    // inside the haystack
    if (needle_len > haystack_len) {
        return NULL;
    }
    
    // Loop until there are no more possible positions
    // for the needle to be located
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        // Compare the strings starting with i
        if (!memcmp(haystack + i, needle, needle_len)) {
            return (char *)(haystack + i);
        }
    }
    
    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);

    // There is impossible for the needle to be located
    // inside the haystack
    if (needle_len > haystack_len) {
        return NULL;
    }

    // Strart the search from the end of the string
    const char *p = haystack + haystack_len - needle_len;

    // Loop until there are no more possible positions
    // for the needle to be located
    while (p >= haystack) {
        // Compare the strings starting with i
        if (memcmp(p, needle, needle_len) == 0) {
            return (char *)p;
        }
        p--;
    }

    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
    // The pointers are cast to char because the function
    // copies bytes
    char *dst = (char *)destination;
    const char *src = (const char *)source;
    
    // Copy the byte at src to the location pointed
    // to by dst
    while (num--) {
        *dst++ = *src++;
    }
    
    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
    // The pointers are cast to char because the function
    // copies bytes
    char *dst = (char *)destination;
    const char *src = (const char *)source;
    
    // Check if the source and destination regions
    // overlap and the destination starts at a higher memory
    // address
    if (src < dst) {
        // Copy the bytes in reverse order to avoid
        // overwriting data
        src += num - 1;
        dst += num - 1;
        
        while (num--) {
            *dst-- = *src--;
        }
    } else {
        // Copy the bytes in the normal order
        // because data won't be overwritten
        while (num--) {
            *dst++ = *src++;
        }
    }
    
    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    // Ensure that the comparison is done on a byte-by-byte basis
    const unsigned char *p1 = (const unsigned char *)ptr1;
    const unsigned char *p2 = (const unsigned char *)ptr2;
    
    while (num--) {
        // If the bytes are not equal, the function
        // retruns -1 if the byte pointed by p1 is less than
        // p2 or 1 otherwise
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }
        
        p1++;
        p2++;
    }
    
    // The memory regions are equal
    return 0;
}

void *memset(void *source, int value, size_t num)
{
    // Ensure that the comparison is done on a byte-by-byte basis
    unsigned char *p = (unsigned char *)source;
    unsigned char val = (unsigned char)value;
    
    // Set the byte pointed by p to the value of val
    while (num--) {
        *p++ = val;
    }
    
    return source;
}
