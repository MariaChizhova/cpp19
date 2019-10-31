#pragma once

#include <stddef.h>

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*));
