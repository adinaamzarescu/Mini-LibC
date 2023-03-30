#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <string.h>
#include "read_write.c"

int puts(const char *str)
{
    // Get the length of the string
    size_t len = strlen(str);

    // Write the string and a newline character to the 
    // standard output using the write system call
    if (write(1, str, len) != ((ssize_t)len) || write(1, "\n", 1) != 1)
    {
        // If there is an error writing the string 
        // or newline character, return -1 to indicate failure.
        return -1;
    }

    // Success
    return 0;
}