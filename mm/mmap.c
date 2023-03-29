// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	off_t result = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
	if (result < 0)
	{
		errno = -result;
		result = -1;
	}

	return result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
    void *result = (void *) syscall(__NR_mremap, old_address, old_size, new_size, flags);
    if (result == MAP_FAILED) {
        errno = -syscall(__NR_mremap);
    }
    return result;
}

int munmap(void *addr, size_t length)
{
	// __NR_munmap 
    int result = syscall(__NR_munmap , addr, length);
    if (result < 0) {
        errno = -syscall(__NR_munmap );
    }
    return result;
}