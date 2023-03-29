https://danluu.com/malloc-tutorial/
https://www.javatpoint.com/calloc-in-c
https://port70.net/~nsz/c/c11/n1570.html#7.22.3.5
https://man7.org/linux/man-pages/man2/sbrk.2.html
https://man7.org/linux/man-pages/man3/memcpy.3.html
https://man7.org/linux/man-pages/man3/malloc_usable_size.3.html
https://man.openbsd.org/reallocarray.3


MM
* Library added: errno.h

## Malloc

* size = number of bytes to allocate

* The function allocates memory using **sbrk** (the return value is a pointer to the start of the newly allocated memory block)
* sbrk fails if it returns the special value (void*)-1

Source: https://man7.org/linux/man-pages/man2/sbrk.2.html

## Calloc

* nmemb = number of elements to allocate
* size = the size of each element

* Firstly the function calculates the total size of the memory block
* Now that malloc is implemented, calloc will use the malloc function to allocate memory
* If the allocation was sucessful the memory will be set to 0

Source: https://port70.net/~nsz/c/c11/n1570.html#7.22.3.1

## Free

* ptr = pointer to the memory block to free

* Since the memory was allocated with sbrk the free will also use sbrk
* The free function returns no value
* sbrk moves the program forward to allocate the requested memory so when free() is called the program needs to be moved back

Source: https://man7.org/linux/man-pages/man2/sbrk.2.html

## Realloc

* ptr = pointer to the memory block to realloc
* size = number of bytes to allocate

* If the pointer is null the memory is allocated directly using malloc
* If the requested size is zero, free the memory block and return NULL
* Allocate memory using malloc()
* Copy memory using memcpy()
* Free the old pointer
* Return the new pointers

Source: https://man7.org/linux/man-pages/man3/malloc_usable_size.3.html

## Reallocarray

* ptr = pointer to the memory block to realloc
* nmemb = number of members in the new block of memory
* size = size of each member

* This function is similar to the realloc function but in addition it checks 
for integer overflow using __builtin_mul_overflow()
* __builtin_mul_overflow() : the first argument is the first 2 arguments are the values of the integers to be multiplied and the 3rd argument is a pointer to the variable where the result will be stored in. If the function return 0 then there is no overflow and the result is stored in the **new_size** variable

Source: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html


IO

For those functions I used the exit(long exit_code) function as
a refference. Then I searched in the syscall_list.h for each 
syscall function as well as using the man pages for them.

## Close

* fd = the file descriptor to be closed
* The function uses the syscall for close (number 3)
* If the system call succeeds it returns the new file offset

* It returns 0 on success and -1 on failure

Source: https://man7.org/linux/man-pages/man2/close.2.html


## Ftruncate

* fd = the file descriptor of the file to be truncated
* length = length after the file is truncated

* The function uses the syscall for ftruncate (number 77)
* If the system call succeeds it returns the new file offset, else it returns -1

Source: https://man7.org/linux/man-pages/man3/ftruncate.3p.html


## Lseek

* fd = file descriptor to be operated on
* offset = the offset to seek on
* whence = the reference point for the seek operation

* The function uses the syscall for lseek (number 8)
* If the system call succeeds it returns the new file offset, else it returns -1

Source: https://man7.org/linux/man-pages/man2/lseek.2.html

## Open

* using O_CREAT from include/fcntl.h that expands to 0100
if this flag is set then the file mode is not 0
* Since the <stdarg.h> library is included the **mode** argument is
extracted using the va_start() and va_arg() macros.

* fd = the file descriptor to be opened
* The function uses the syscall for open (number 3)
* If the system call succeeds it returns the new file offset

* It returns 0 on success and -1 on failure

Sources: 
1. https://man7.org/linux/man-pages/man2/open.2.html
2. https://en.wikipedia.org/wiki/Stdarg.h

## Truncate

* path = the path of the file to be truncated
* length = length after the file is truncated

* The function uses the syscall for truncate (number 76)
* If the system call succeeds it returns the new file offset, else it returns -1

Source: https://man7.org/linux/man-pages/man1/truncate.1.html


STAT

* I included the library #include <internal/syscall.h>

* I included the library #include <internal/types.h>

Those are not external libraries, they are from the skel.
Then I searched in the syscall_list.h for each 
syscall function as well as using the man pages for them.

## Fstat

* fd = the file descriptor of the opened file
* st = a pointer to the struct stat object (information about the file)

* The function uses the syscall for fstat (number 5)
* It returns 0 on success and -1 on failure

Source: https://linux.die.net/man/2/fstat

## Stat

* path = the path of the file to be examinated
* buf = a pointer to a struct stat object(information about the file)

* The function uses the syscall for stat (number 4)
* It returns 0 on success and -1 on failure

Source: https://man7.org/linux/man-pages/man2/lstat.2.html

String

## Strcpy

* The function copies the source and destination in 2 new variables.
* The destination will get each character from the source for as long
as the source still has charecters. 

## Strncpy

* The function copies the source and destination in 2 new variables
* The destination will get each character from the source for as long as the source still has characters or until len is 0
* If all chars from the source were copied and len is not yet 0 then all other chars will ne NULL

## Strcat 

* dest will point to the end in order to get the start ponter for the
source to start appending. Then each char will be appended

## Strncat

* Similar to strcat but this time if len becomes 0 the appending will stop

## Strcmp

* For as long as the 2 strings have characters and each character is the same in both strings, the pointer will increment.
* When the loop stops there are 3 cases:
    * 0 if the strings are equal
    * -1 if str2 is greater
    * 1 if str1 is greater

## Strncmp

* This is similar to the strcmp function but in this case the code 
is in a for loop that only checks for len characters

## Strchr

* The pointer will incremet until the character c is found or until
the end of the string
* If c is '\0' then the return value will be the end of the string
* If no character is found then the function will return NULL

## Strrchr

* The function is similar but the pointer decreseas

## Strstr !!!

* The function stores the length of the needle and the haystack
* if the second string is longer then the function will return NULL
* Using memcmp the function tests if the needle is in the haystack 

## Strrstr !!!

## Memcpy 

* Each value is copied step by step and the pointers are incremented;

## Memmove

* 