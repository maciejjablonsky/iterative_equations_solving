#include "matrix_internals.h"
#include <stdlib.h>
#include <matrix.h>
#include <logging.h>

bool MATRIX__ctor(struct matrix *self, struct matrix_ctor_params *params) {
	if (!MATRIX__are_params_valid(params)) {
		return false;
	}
	self->shape = params->shape;
	if (params->elements) {
		return MATRIX__copy_data(self, params);
	}
	return true;
}

bool MATRIX__dctor(struct matrix *self) {
	if (self->elements) {
		free(self->elements);
	}
	return true;
}

struct matrix *MATRIX__new(struct matrix_ctor_params *params) {
	struct matrix *self = calloc(1, sizeof(*self));
	if (self == NULL) {
		return NULL;
	}
	if (!MATRIX__ctor(self, params)) {
		free(self);
		return NULL;
	}
	return self;
}

struct matrix *MATRIX__delete(struct matrix *matrix) {
	if (matrix) {
		MATRIX__dctor(matrix);
		free(matrix);
	}
	return NULL;
}

struct matrix *MATRIX__transpose(struct matrix *matrix) {
	element_t *data = malloc(matrix->shape.rows * matrix->shape.cols * sizeof(element_t));
	if (data == NULL) {
		return NULL;
	}
	struct mat2d_shape shape = matrix->shape;
	for (int r = 0; r < shape.rows; ++r) {
		for (int c = 0; c < shape.cols; ++c) {
			data[c + shape.rows * r] = matrix->elements[r + shape.rows * c];
		}
	}
	struct matrix_ctor_params params = matrix_ctor_params(.elements = data,
	                                                 .length = matrix->shape.rows * matrix->shape.cols,
	                                                 .shape=shape);
	struct matrix *transposed = MATRIX__new(&params);
	free(data);
	return transposed;
}

struct matrix_multiplication_order *matrix__order_for_multiplication_with_2nd_transformed(size_t rows_A, size_t rows_B) {
	struct matrix_multiplication_order *order = malloc(rows_A * rows_B * sizeof(*order));
	if (!order) {
		return NULL;
	}
	int i = 0;
	for (int row_a = 0; row_a < rows_A; ++row_a) {
		for (int row_b = 0; row_b < rows_B; ++row_b) {
			order[i].row_a = row_a;
			order[i].row_b = row_b;
			i += 1;
		}
	}
	return order;
}

//struct matrix *matrix__multiplication(struct matrix *A, struct matrix *B) {
//    if (A->shape.cols != B->shape.rows) {
//        LOG_ERROR("Shapes don't match for multiplication.");
//        return NULL;
//    }
//    struct matrix *B_T = MATRIX__transpose(B);
//    struct mat2d_shape result_shape = {A->shape.rows, B->shape.cols};
//
////    element_t *result_elements = vectors__dot_products(A->elements, B->elements, A->shape.cols);
////
////
////    matrix_ctor_params_t params = matrix_ctor_params(.elements = result_elements, .shape=dot_shape,
////                                                     .length = dot_shape.rows
////                                                             * dot_shape.cols);
//    struct matrix *DOT = MATRIX__new(&params);
//    MATRIX__delete(B_T);
//    free(result_elements);
//    return DOT;
//}



