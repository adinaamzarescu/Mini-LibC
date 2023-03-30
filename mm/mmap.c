// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    // Call the mmap() system call (__NR_mmap = 9) 
	off_t result = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
    // Check if the system call succeeded or failed
	if (result < 0)
	{
        // Error occurred
		errno = -result;
		result = -1;
	}
    // Call succeeded 
	return (void *)result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
    // Call the mrmap() system call (__NR_mrmap = 25) 
    void *result = (void *) syscall(__NR_mremap, old_address, old_size, new_size, flags);
    // Check if the system call succeeded or failed
    if (result == MAP_FAILED) {
        // Error occurred
        errno = -syscall(__NR_mremap);
    }
    // Call succeeded 
    return result;
}

int munmap(void *addr, size_t length)
{
    // Call the munmap() system call (__NR_munmap = 11) 
    int result = syscall(__NR_munmap , addr, length);
    // Check if the system call succeeded or failed
    if (result < 0) {
        // Error occurred
        errno = -syscall(__NR_munmap );
    }
    // Call succeeded   
    return result;
}