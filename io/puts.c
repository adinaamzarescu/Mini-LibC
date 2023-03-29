#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include "read_write.c"

int puts(const char *str)
{
    /* TODO: Implement lseek(). */
    int len = 0;
    while (str[len])
    {
        len++;
    }
    if (write(1, str, len) == -1)
    {
        return -1;
    }
    if (write(1, "\n", 1) == -1)
    {
        return -1;
    }
    return 0;
}