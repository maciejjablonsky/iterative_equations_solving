#ifndef CONST_VECTOR_H
#define CONST_VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "matrix.h"


typedef unsigned int len_t;
typedef unsigned int uint;
typedef float element_t;

struct vector {
    element_t * elements;
    len_t len;
};




struct vector * vector_ones(len_t n);

element_t vector__dot_product(const element_t *vecA, const element_t *vecB, size_t len);

element_t *
vectors__dot_products(element_t *vectorsA, element_t *vectorsB, size_t number_of_vectors, size_t each_vector_length);

long double vector_norm(struct vector * vec);


#endif // CONST_VECTOR_H
