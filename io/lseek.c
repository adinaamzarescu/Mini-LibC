// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/types.h>

off_t lseek(int fd, off_t offset, int whence) {
    off_t result;

    // Here I included the errors manually
    // instead of using the (if (result < 0)) option
    // in order to debug the code easier

    // Check if the whence value is valid and if the offset
    // is non-negative
    // SEEK_SET 0
    // SEEK_CUR 1
    // SEEK_END 2

    // If not, the error should be invalid argument error
    if (whence < 0 || whence > 2 || offset < 0) {
        errno = EINVAL;
        return (off_t)-1;
    }

    // If the file descriptor is negative then the error
    // should be bad file descriptor
    if (fd < 0) {
        errno = EBADF;
        return (off_t)-1;
    }
    
    // Call the lseek() system call (__NR_lseek = 8)
	// passing the file descriptor, offset, and whence as arguments
    result = syscall(__NR_lseek , fd, offset, whence);
    
    // Check if the system call succeeded or failed
    if (result == -1) {
        // Error occurred
        errno = -result;
        return -1;
    } else {
        // Call succeeded
        return result;
    }
}