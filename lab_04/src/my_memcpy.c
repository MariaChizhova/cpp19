#include "my_memcpy.h"

void *my_memcpy(void *dest, const void *src, size_t data) {
    char *arr_dest = (char *) dest;
    const char *arr_src = (char *) src;
    for (size_t i = 0; i < data; i++)
        *arr_dest++ = *arr_src++;
    return dest;
}

