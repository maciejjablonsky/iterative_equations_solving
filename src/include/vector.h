#ifndef CONST_VECTOR_H
#define CONST_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t a;
    size_t b;
} order_t;

typedef float element_t;

element_t vector__dot_product(const element_t *A, const element_t *B, size_t len);

element_t *vectors__dot_products(element_t *A_vectors, element_t *B_vectors,
                                 size_t number_of_vectors, size_t each_vector_length);

element_t *
vectors__dot_products_with_order(element_t *A_vectors, element_t *B_vectors, size_t number_of_vectors, size_t each_vector_length, const order_t *order,
                                 size_t order_len);


order_t * matrix__generate_row_multiplication_order(size_t A_rows, size_t B_cols);


#endif // CONST_VECTOR_H
