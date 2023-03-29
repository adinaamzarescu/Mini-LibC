// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <errno.h>
#include <internal/syscall.h>

int fstat(int fd, struct stat *st) {
    int result;
    
    if (fd < 0) {
        errno = EBADF;
        return -1;
    }

    // Call the fstat() system call (__NR_fstat = 5) 
	// and the fd and st as arguments
    result = syscall(__NR_fstat, fd, st);
    
    // Check if the system call succeeded or failed
    if (result == -1) {
        // Error occurred
        errno = -result;
		return -1;
    }
    
    // Return the result
    return result;
}
