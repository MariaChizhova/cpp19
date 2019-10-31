#include "mergesort.h"
#include <stdlib.h>
#include <string.h>
#include "my_memcpy.h"

int merge(void *result, void *l, size_t l_size, void *r, size_t r_size, size_t element_size,
          int (*comparator)(const void *, const void *)) {
    size_t elements_total = l_size + r_size;
    void *temp = malloc(elements_total * element_size);
    if (!temp)
        return -1;
    size_t l_pos = 0, r_pos = 0;
    for (size_t i = 0; i < elements_total; i++) {
        if (l_pos < l_size &&
            (r_pos >= r_size || comparator((char *) l + element_size * l_pos, (char *) r + element_size * r_pos) < 0)) {
            my_memcpy(temp + i * element_size, (char *) l + l_pos * element_size, element_size);
            ++l_pos;
        } else {
            my_memcpy(temp + i * element_size, (char *) r + r_pos * element_size, element_size);
            ++r_pos;
        }
    }
    my_memcpy(result, temp, elements_total * element_size);
    free(temp);
    return 0;
}

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
    if (elements <= 1)
        return 0;
    size_t len = elements / 2;
    if (mergesort(array, len, element_size, comparator))
        return -1;
    if (mergesort(array + element_size * len, elements - len, element_size, comparator))
        return -1;
    if (merge(array, array, len, array + element_size * len, elements - len, element_size, comparator))
        return -1;
    return 0;
}
