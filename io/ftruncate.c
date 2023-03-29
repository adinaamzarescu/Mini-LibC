// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/types.h>

int ftruncate(int fd, off_t length) {
    int result;

    // if (length < 0 || !fd) {
    //     errno = EINVAL;
    //     return -1;
    // }
    // if (fd < 0) {
    //     errno = EBADF;
    //     return -1;
    // }

    // Call the ftruncate) system call (__NR_ftrunctae = 77) 
	// and the fd and length as arguments
	result = syscall(__NR_ftruncate , fd, length);
    
    // Check if the system call succeeded or failed.
    if (result < 0) {
        // Error occurred
        errno = -result;
        return -1;
    } else {
        // Call succeeded
        return result;
    }
}