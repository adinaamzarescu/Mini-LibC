// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/types.h>

int truncate(const char *path, off_t length) {
    int result;

    // Check if length is valid
    if (length < 0) {
        // Error occurred
        errno = EINVAL;
        return -1;
    }
    
    // Call the truncate() system call (__NR_ftrunctae = 76) 
	// and the path and length as arguments
    result = syscall(__NR_truncate, path, length);
    
    // Check if the system call succeeded or failed
    if (result < 0) {
        // Error occurred
        errno = -result;
		return -1;
    }
    
    // Return the result
    return result;
}
