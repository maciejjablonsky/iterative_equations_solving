#include "vector.h"
#include <stdlib.h>

element_t vector__dot_product(const element_t *vecA, const element_t *vecB, size_t len) {
	element_t dot_product = 0;
	for (int i = 0; i < len; ++i) {
		dot_product += vecA[i] * vecB[i];
	}
	return dot_product;
}

element_t *
vectors__dot_products(element_t *vectorsA, element_t *vectorsB, size_t number_of_vectors, size_t each_vector_length) {
	element_t *result = malloc(number_of_vectors * sizeof(*result));
	if (!result) {
		return NULL;
	}

	for (int i = 0; i < number_of_vectors; ++i) {
		size_t offset = i * each_vector_length;
		result[i] = vector__dot_product(vectorsA + offset, vectorsB + offset, each_vector_length);
	}
	return result;
}

//element_t *vectors__dot_products_with_order(element_t *A_vectors, element_t *B_vectors, size_t number_of_vectors,
//                                            size_t each_vector_length, const order_t *order, size_t order_len) {
//	element_t *result = (element_t *) malloc(order_len * sizeof(element_t));
//	if (!result) {
//		return NULL;
//	}
//
//	for (int i = 0; i < order_len; ++i) {
//		size_t a_offset = order[i].row_a * each_vector_length;
//		size_t b_offset = order[i].row_b * each_vector_length;
//		result[i] = vector__dot_product(A_vectors + a_offset, B_vectors + b_offset, each_vector_length);
//	}
//	return result;
//}

