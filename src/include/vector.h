#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef unsigned int len_t;
typedef unsigned int uint;
typedef double element_t;

struct vector {
    element_t * elements;
    len_t len;
};


#define vector_struct(...) (struct vector){__VA_ARGS__}

element_t vector__dot_product(const element_t *vecA, const element_t *vecB, int len);

element_t *
vectors__dot_products(element_t *vectorsA, element_t *vectorsB, size_t number_of_vectors, size_t each_vector_length);

long double vector__norm(struct vector * vec);


#endif //VECTOR_H
