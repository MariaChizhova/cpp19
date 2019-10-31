#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mergesort.h"
#include "my_memcpy.h"


int int_compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int char_compare(const void *a, const void *b) {
    return *(char *) a - *(char *) b;
}

int str_compare(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}

void sort_int(int *data, int len) {
    if (mergesort(data, len, sizeof(data[0]), int_compare)) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        printf("%d", data[i]);
        if (i != len - 1)
            printf(" ");
    }
    printf("\n");
}

void sort_char(char *data, int len) {
    if (mergesort(data, len, sizeof(data[0]), char_compare)) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        printf("%c", data[i]);
        if (i != len - 1)
            printf(" ");
    }
    printf("\n");
}

void sort_str(char **data, int len) {
    if (mergesort(data, len, sizeof(data[0]), str_compare)) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        printf("%s", data[i]);
        if (i != len - 1)
            printf(" ");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (!strcmp(argv[1], "int")) {
        int *data = (int *) malloc((argc - 2) * sizeof(int));
        for (int i = 2; i < argc; i++)
            data[i - 2] = atoi(argv[i]);
        sort_int(data, argc - 2);
        free(data);
    } else if (!strcmp(argv[1], "char")) {
        char *data = (char *) malloc((argc - 2) * sizeof(char));
        for (int i = 2; i < argc; i++)
            data[i - 2] = argv[i][0];
        sort_char(data, argc - 2);
        free(data);
    } else if (!strcmp(argv[1], "str")) {
        char **data = (char **) malloc((argc - 2) * sizeof(char *));
        my_memcpy(data, argv + 2, (argc - 2) * sizeof(char *));
        sort_str(data, argc - 2);
        free(data);
    } else {
        assert(!"Unknown type to sort");
    }
    return 0;
}
