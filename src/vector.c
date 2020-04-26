#include "vector.h"
#include <stdlib.h>



element_t vector__dot_product(const element_t *vecA, const element_t *vecB, int len) {
	element_t dot_product = 0;
	for (int i = 0; i < len; ++i) {
		dot_product += vecA[i] * vecB[i];
	}
	return dot_product;
}

static inline long double square(element_t val) {
        return val * val;
}

element_t vector__norm(struct vector *vec) {
        long double norm = 0;
        for (int i = 0; i < vec->len; ++i) {
                norm += square(vec->elements[i]);
        }
        return sqrt(norm);
}



