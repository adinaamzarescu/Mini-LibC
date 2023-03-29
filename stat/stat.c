// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <internal/syscall.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
    int result;

    // Call the stat() system call (__NR_stat = 4) 
	// and the fd and buf as arguments
    result = syscall(__NR_stat, path, buf);
    
    // Check if the system call succeeded or failed
    if (result < 0) {
        // Error occurred
        errno = -result;
		return -1;
    }
    
    // Return the result
    return result;
}