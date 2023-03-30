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
	// Use the mmap() system call to allocate size bytes of memory with read and write permissions
	void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// Check if the mmap() call was successful
	if (mem == MAP_FAILED)
	{
		return NULL;
	}

	// Add the allocated memory to a list of memory blocks
	if (mem_list_add(mem, size))
	{
		// If adding to the list failed, unmap the memory and return NULL
		munmap(mem, size);
		return NULL;
	}

	return mem;
}

void *calloc(size_t nmemb, size_t size)
{
	// Calculate the total size of the memory block to be allocated
	size_t size_total = nmemb * size;
	
	// Use mmap() to allocate the memory block with read and write permissions
	void *mem = mmap(NULL, size_total, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// Check if mmap() call was successful
	if (mem == MAP_FAILED)
	{
		return NULL;
	}

	// Set all the bytes in the memory block to 0
	memset(mem, 0, size_total);

	// Add the allocated memory to a list of memory blocks
	if (mem_list_add(mem, size_total))
	{
		// If adding to the list failed, unmap the memory and return NULL
		munmap(mem, size_total);
		return NULL;
	}

	return mem;
}

void free(void *ptr)
{
   if (!ptr) {
       return;
   }
	// Find the memory block in the memory list
	struct mem_list *list = mem_list_find(ptr);

	// If the memory block is not found, return
	if (!list) {
		return;
	}

	// Unmap the memory block using munmap()
	int result = munmap(list->start, list->len);

	// If munmap() fails, set errno and return
	if (result < 0) {
		errno = -result;
		return;
	}

	// Remove the memory block from the memory list
	int res = mem_list_del(ptr);
	if (!res) {
		return;
	}
}

void *realloc(void *ptr, size_t size)
{
	// Behave like malloc() with size bytes of memory allocation
	if (!ptr)
	{
		return malloc(size);
	}

	// Realloc() behaves like free()
	if (!size)
	{
		free(ptr);
		return NULL;
	}

	// Find the memory block associated with ptr in the list of memory blocks
	struct mem_list *mem_block = mem_list_find(ptr);
	if (!mem_block)
	{
		return NULL;
	}

	// If the requested size is smaller than or equal to the current size of the memory block, return ptr
	if (size <= mem_block->len)
	{
		return ptr;
	}

	// Allocate a new memory block of size bytes using malloc()
	void *new_ptr = malloc(size);
	if (!new_ptr)
	{
		return NULL;
	}

	// Copy the contents of the old memory block to the new memory block
	memcpy(new_ptr, ptr, mem_block->len);

	// Remove the old memory block from the list of memory blocks
	int result = mem_list_del(ptr);
	if (result)
	{
		free(new_ptr);
		return NULL;
	}

	// Add the new memory block to the list of memory blocks
	result = mem_list_add(new_ptr, size);
	if (result)
	{
		free(new_ptr);
		return NULL;
	}

	return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    // Check for integer overflow
    size_t total_size;
    if (__builtin_mul_overflow(nmemb, size, &total_size))
    {
        return NULL;
    }

    // Behave like realloc() with total_size bytes of memory allocation
    return realloc(ptr, total_size);
}