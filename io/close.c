// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd) {
    int result;
    
    // Call the close() system call (__NR_close = 3) and the fd as argument
    result = syscall(__NR_close , fd);
    
    // Check if the system call succeeded or failed
    if (result < 0) {
        // Error occurred
        errno = -result;
        return -1;
    } else {
        // Call succeeded
        return result;
    }
}