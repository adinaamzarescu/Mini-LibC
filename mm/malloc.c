/* SPDX-License-Identifier: BSD-3-Clause */

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <internal/syscall.h>

void *malloc(size_t size)
{
	void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == MAP_FAILED)
	{
		return NULL;
	}

	if (mem_list_add(mem, size) != 0)
	{
		munmap(mem, size);
		return NULL;
	}

	return mem;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement malloc(). */
	size_t total_size = nmemb * size;
	void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
	{
		return NULL;
	}
	memset(ptr, 0, total_size);
	mem_list_add(ptr, total_size);
	return ptr;
}

void free(void *ptr)
{
   if (ptr == NULL) {
       return;
   }
    struct mem_list *list = mem_list_find(ptr);
    if (list == NULL) {
        return;
    }
    int r = munmap(list->start, list->len);
    if (r < 0) {
//        errno = -r;
        return;
    }

    int res = mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	if (ptr == NULL)
	{
		// If ptr is NULL, realloc should behave like malloc.
		return malloc(size);
	}

	if (size == 0)
	{
		// If size is zero, realloc should behave like free.
		free(ptr);
		return NULL;
	}

	struct mem_list *mem_block = mem_list_find(ptr);
	if (mem_block == NULL)
	{
		// ptr does not point to a block allocated by mem_list_add.
		return NULL;
	}

	if (size <= mem_block->len)
	{
		// The new size is smaller or equal to the current size.
		return ptr;
	}

	// Allocate a new memory block with the desired size.
	void *new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		return NULL;
	}

	// Copy the contents of the old block to the new block.
	memcpy(new_ptr, ptr, mem_block->len);

	// Free the old memory block.
	int result = mem_list_del(ptr);
	if (result != 0)
	{
		free(new_ptr);
		return NULL;
	}

	// Add the new memory block to the memory list.
	result = mem_list_add(new_ptr, size);
	if (result != 0)
	{
		free(new_ptr);
		return NULL;
	}

	return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	size_t total_size;
	void *new_ptr;

	/* Check for multiplication overflow */
	if (__builtin_mul_overflow(nmemb, size, &total_size))
	{
		return NULL;
	}

	/* Check for integer overflow */
	if (__builtin_add_overflow(total_size, sizeof(size_t), &total_size))
	{
		return NULL;
	}

	/* Reallocate memory */
	new_ptr = syscall(__NR_mmap, ptr, total_size, PROT_READ | PROT_WRITE,
					  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_ptr == MAP_FAILED)
	{
		return NULL;
	}

	/* Copy old data to new memory if necessary */
	if (ptr != NULL)
	{
		size_t old_size = *(size_t *)ptr;
		if (old_size < total_size)
		{
			memcpy(new_ptr, ptr, old_size);
		}
		else
		{
			memcpy(new_ptr, ptr, total_size);
		}
		/* Free old memory */
		syscall(__NR_munmap, ptr, old_size);
	}

	/* Store the size of the new allocation */
	*(size_t *)new_ptr = total_size;

	return (void *)((size_t)new_ptr + sizeof(size_t));
}