// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
    // Default mode
    mode_t mode = 0;
    
    // If the O_CREAT flag is set, 
	// If flags exist and if the O_CREAT flag exist
    if (flags && O_CREAT) {
        // Used to define a list of arguments
        // whose number and types is not known
        va_list valist;
        // Initialize the list with the mode_t type
        va_start(valist, flags);
        // va_arg returns the next argument
        mode = va_arg(valist, mode_t);
        // Clean up the valist
        va_end(valist);
    }
    int result;
    
    // Call the open() system call (__NR_open = 2) and the fd as argument
    result = syscall(__NR_open , filename, flags, mode);
    
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