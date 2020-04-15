#ifndef CONST_VECTOR_H
#define CONST_VECTOR_H

#include <stddef.h>
#include <stdbool.h>


typedef float element_t;



element_t vector__dot_product(const element_t *vecA, const element_t *vecB, size_t len);

element_t *
vectors__dot_products(element_t *vectorsA, element_t *vectorsB, size_t number_of_vectors, size_t each_vector_length);

element_t *vectors__dot_products_with_order(element_t *A_vectors, element_t *B_vectors, size_t number_of_vectors,
                                            size_t each_vector_length, const struct matrix_multiplication_order *order,
                                            size_t order_len);


struct matrix_multiplication_order *matrix__order_for_multiplication_with_2nd_transformed(size_t rows_A, size_t rows_B);


#endif // CONST_VECTOR_H
