#include "str.h"
#include <stddef.h>

int min(int a, int b) {
    return a < b ? a : b;
}

char *my_strcpy(char *restrict dest, const char *restrict src) {
    int len_src = my_strlen(src);
    for (int i = 0; i <= len_src; i++) {
        *(dest + i) = *(src + i);
    }
    return dest;
}

char *my_strcat(char *restrict dest, const char *restrict src) {
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    for (int i = 0; i <= len_src; i++) {
        *(dest + i + len_dest) = *(src + i);
    }
    return dest;
} 

int my_strcmp(const char *str1, const char *str2) {
    int n = min(my_strlen(str1), my_strlen(str2));
    for (int i = 0; i < n; i++) {
        if (*(str1 + i) != *(str2 + i))
            return str1[i] - str2[i];
    }
    return str1[n] - str2[n];
}

size_t  my_strlen(const char *str) {
    int i = 0;
    while (*(str + i))
        i++;
    return i;
}

