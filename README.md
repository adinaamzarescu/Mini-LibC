# Mini LibC
#### Copyright Adina-Maria Amzarescu
__________________________________________________________

A minimalistic standard C library implementation for 
Linux systems, that can be used as a replacement for the 
system libc (glibc in Linux). 

The goal is to have a minimally functional libc with 
features such as string management, basic memory 
support and POSIX file I/O.

__________________________________________________________

## Strings

### strcpy

The function copies the source and destination in 2 new variables.

The destination will get each character from the source for as long
as the source still has charecters. 

### strncpy

The function copies the source and destination in 2 new variables

The destination will get each character from the source for as long as the 
source still has characters or until len is 0

If all chars from the source were copied and len is not yet 0 then all other 
chars will ne NULL

### strcat 

dest will point to the end in order to get the start pointer for the 
source to start appending. Then each char will be appended in a similar 
way as strcpy()

### strncat

Similar to strcat() but this time if len becomes 0 the appending will stop

### strcmp

For as long as the 2 strings have characters and each character is the same 
in both strings, the pointer will increment

* When the loop stops there are 3 cases:

    * 0 if the strings are equal

    * -1 if the char in str2 is greater

    * 1 if the char in str1 is greater

### strncmp

This is similar to the strcmp function but in this case the code has an 
aditional variable, the length

### strchr

The pointer will incremet until the character c is found or until 
the reach of the end of the string

If c is '\0' then the return value will be the end of the string

The type cast (char *) is used to return a pointer to 
a non constant value because the function is not 
modifying the content of the string

If no character is found then the function will return NULL

### strrchr

The function is similar but the pointer decreseas

### strstr

The function searches for a substring withing another 
string

The function stores the length of the needle and the haystack

If the len of the needle is greater than the len of 
the haystack, the function returns NULL because it is 
impossible for the haystack to contain the needle

The loop will continue until there are no more possible positions within 
the haystack for needle to be found in.

The memcmp() function is used to compare the substring 
of the haystack depending on the iterator i

If memcmp() returns 0 then the needle has been found

### strrstr

The function searches for a substring withing another 
string

This is similar to the strstr() function but the search will 
start at the end of the string this time

### memcpy 

Each value is copied step by step and the pointers are incremented

The pointers are cast to char* and const char* because 
the function copies bytes and char is one byte

### memmove

The function copies a specified number of bytes from a source 
memory location to a destination memory location, and is designed 
to handle cases where the source and destination memory regions overlap

There are 2 cases. One in which the scr start is 
lesser than the dest start. In this case the copying 
must be done in reverse order to avoid overwriting data. 
The second case is the one in which the data won't be overwritten

### memcmp

The function compares the first num bytes of two memory regions

First of all the pointers are cast to const unsigned char * 
because unsigned char is a one-byte type and this 
ensures that the comparison is done on a byte-by-byte basis

The function returns 0 if the memory regions are equal, 
-1 if p1 is less than p2 or 1 otherwise

### memset

The function sets the first num bytes of the memory 
region pointed by source to the given value

_______________________________________________________________________________

## IO

For those functions I used the exit(long exit_code) function as 
a refference. Then I searched in the syscall_list.h for each 
syscall function as well as using the man pages for them.

The source for error handling is the GitHub repo for the GNU C Library:

https://github.com/ysat0/uClibc/blob/cf0b3a3342f24dbf601ba639bdce5b2a2f001c7a/libc/sysdeps/linux/i386/sigaction.c

I found out it is easier to set the errno variable like this __set_errno(-result); 
instead of checking for each case like this:

        if (length < 0 || !fd) {
            errno = EINVAL;
            return -1;
        }

### close

The function closes a file descriptor.

* fd = the file descriptor to be closed

The function uses the syscall for close (number 3)

If the system call succeeds it returns the new file offset

* It returns -1 on failure

Source: https://man7.org/linux/man-pages/man2/close.2.html

### ftruncate

The function truncates a file to a specified length

* fd = the file descriptor of the file to be truncated

* length = length after the file is truncated

The function uses the syscall for ftruncate (number 77)

* If the system call succeeds it returns the new file offset, else it 
returns -1

Source: https://man7.org/linux/man-pages/man3/ftruncate.3p.html


### lseek

I had some problems with this function so I decided to add the
errors manually in order to debug the code better. Instead of that
another option would be:

        if (result < 0) {
            // Error occurred
            errno = -result;
            return -1;
        }

* fd = file descriptor to be operated on

* offset = the offset to seek on

* whence = the reference point for the seek operation

The function uses the syscall for lseek (number 8)

* If the system call succeeds it returns the new file offset, else it 
returns -1

Source: https://man7.org/linux/man-pages/man2/lseek.2.html

### open

This function opens and possibly creates a file.

* Using O_CREAT from include/fcntl.h that expands to 0100 
if this flag is set then the file mode is not 0

Since the <stdarg.h> library is included the **mode** argument is 
extracted using the va_start() and va_arg() macros.

* fd = the file descriptor to be opened

The function uses the syscall for open (number 2). If the system 
call succeeds it returns the new file offset

* It returns the new file descriptor on success and -1 on failure

Sources: 
1. https://man7.org/linux/man-pages/man2/open.2.html
2. https://codebrowser.dev/glibc/glibc/sysdeps/unix/sysv/linux/open.c.html
3. https://man7.org/linux/man-pages/man3/stdarg.3.html

### truncate

This function shrinks or extends the size of a file to the specified size

* path = the path of the file to be truncated

* length = length after the file is truncated

The function uses the syscall for truncate (number 76)

* If the system call succeeds it returns the new file offset, else it 
returns -1

Source: https://man7.org/linux/man-pages/man1/truncate.1.html


### puts

I added the header in the <stdio.h> library

The function writes the string s and a trailing newline to stdout.

* str = the string to be written to stdout

Write the string and a newline character to the standard output using the 
write system call from read_write.c

Sources: 
1. https://port70.net/~nsz/c/c11/n1570.html#7.21.7.3
2. https://man7.org/linux/man-pages/man3/puts.3.html



_______________________________________________________________________________


## STAT

Get file status

* I included the library <internal/syscall.h>

* I included the library <internal/types.h>

Those are not external libraries, they are from the skel. 
Then I searched in the syscall_list.h for each 
syscall function as well as using the man pages for them.

### fstat

This function stats the file pointed to by fd and fills in st

* fd = the file descriptor of the opened file

* st = a pointer to the struct stat object (information about the file)

The function uses the syscall for fstat (number 5)

* It returns the result on success and -1 on failure

Source: https://linux.die.net/man/2/fstat

### stat

This function stats the file pointed to by path and fills in buf.

* path = the path of the file to be examinated

* buf = a pointer to a struct stat object(information about the file)

The function uses the syscall for stat (number 4)

* It returns the result on success and -1 on failure

Source: https://man7.org/linux/man-pages/man2/lstat.2.html


_______________________________________________________________________________

## Process

### exit

The function is used to terminate a C program and return a status code to the operating system

### sleep

The sleep function suspends the execution of the calling thread for a 
specified number of seconds.

* seconds = the number of seconds to sleep

Source: https://pubs.opengroup.org/onlinepubs/9699919799/functions/sleep.html

### nanosleep

The function suspends the execution of the calling thread for a specified amount of time

_______________________________________________________________________________


## Memory Management


* Library added: errno.h

### malloc

* size = number of bytes to allocate

* mmap();

    * MAP_PRIVATE means that changes to the memory are not visible to other processes

    * MAP_ANONYMOUS means that the memory is not backed by a file

    * -1 means to use the default file descriptor (which is not used in this case)

    * 0 means to use an offset of 0 from the beginning of the file

After the memory has been allocated, the memory block will be added to the list.

Source: https://man7.org/linux/man-pages/man2/mmap.2.html

### calloc

* nmemb = number of elements to allocate

* size = the size of each element

This function is similar to the malloc() function but in this case all 
blocks are set to 0


### free

* ptr = pointer to the memory block to free

* The steps for the free are:

    * Search for the memory block in the memory list

    * Unmap the memory block using the munmap function

    * Remove the block from the list using mem_list_del()


### realloc

* ptr = pointer to the memory block to realloc

* size = number of bytes to allocate

The function checks if the pointer is empty n which 
case it will behave like a normal malloc.

Then it checks if the size is 0, in which 
case it will behave like a free.

If not, it will then search for the pointer in 
the list of memory blocks. When found, if the 
requested size is smaller than the current size, 
it will return the pointer because there is enough 
memory.

If the requested size is greater then a new pointer 
is created and memory will be allocated to that pointer.

Then the contents of the old pointer will be copied 
to the new one and the old memory block will be 
removed from the list.

The new memory block will be added to the list and 
the old pointer will be freed.


### reallocarray

* ptr = pointer to the memory block to realloc

* nmemb = number of members in the new block of memory

* size = size of each member


builtin_mul_overflow is used to check for integer overflow

Then the function behaves like realloc() with total_size bytes of memory allocation

Source: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html


### mmap

Function used to map files or devices into memory. 
It returns a pointer to the mapped memory or -1 on error.

* The function uses the syscall() function

The function has the following parameters:

* addr: the starting address of the memory region to be allocated

* length: the size of the memory region to be allocated, in bytes

* prot: the memory protection flags for the allocated region

* flags: additional flags that control the behavior of the allocation

* fd: a file descriptor for a file that will be mapped into the memory region

* offset: the offset within the file at which the mapping will start

Source: https://man7.org/linux/man-pages/man2/mmap.2.html

### mremap

This function is similar to the mmap function but it is used to 
remap an existing memory mapping to a new address, potentially 
changing its size.

The function takes four parameters:

* old_address: a pointer to the start of the existing memory mapping

* old_size: the size of the existing memory mapping

* new_size: the new size for the memory mapping

* flags: flags to control the behavior of the remapping operation

Source: https://man7.org/linux/man-pages/man2/mremap.2.html

### munmap

Function used to release a range of memory that was previously 
allocated using mmap() 

It takes two arguments:

* addr: a pointer to the start of the memory range to be unmapped
* length: the length of the memory range to be unmapped

Source: https://man7.org/linux/man-pages/man2/munmap.2.html


_______________________________________________________________________________

General resources:

1. https://kremlin.cc/k&r.pdf
2. https://musl.libc.org/
3. https://ocw.cs.pub.ro/courses/so
4. https://openai.com/blog/chatgpt

_______________________________________________________________________________
