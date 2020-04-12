#include "matrix_internals.h"
#include <stdlib.h>
#include <matrix.h>
#include <logging.h>

bool MATRIX__ctor(matrix_t *self, matrix_ctor_params_t *params) {
    if (!MATRIX__are_params_valid(params)) {
        return false;
    }
    self->shape = params->shape;
    if (params->elements) {
        return MATRIX__copy_data(self, params);
    }
    return true;
}

bool MATRIX__dctor(matrix_t *self) {
    if (self->elements) {
        free(self->elements);
    }
    return true;
}

matrix_t *MATRIX__new(matrix_ctor_params_t *params) {
    matrix_t *self = (matrix_t *) calloc(1, sizeof(matrix_t));
    if (self == NULL) {
        return NULL;
    }
    if (!MATRIX__ctor(self, params)) {
        free(self);
        return NULL;
    }
    return self;
}

matrix_t *MATRIX__delete(matrix_t *matrix) {
    if (matrix) {
        MATRIX__dctor(matrix);
        free(matrix);
    }
    return NULL;
}

matrix_t *MATRIX__transpose(matrix_t *matrix) {
    element_t *data = (element_t *) malloc(matrix->shape.rows * matrix->shape.cols * sizeof(element_t));
    if (data == NULL) {
        return NULL;
    }
    shape_t shape = matrix->shape;
    for (int r = 0; r < shape.rows; ++r) {
        for (int c = 0; c < shape.cols; ++c) {
            data[r + shape.rows * c] = matrix->elements[c + shape.rows * r];
        }
    }
    matrix_ctor_params_t params = matrix_ctor_params(.elements = data,
                                                     .length = matrix->shape.rows * matrix->shape.cols,
                                                     .shape=shape);
    matrix_t *transposed = MATRIX__new(&params);
    free(data);
    return transposed;
}

order_t * matrix__generate_row_multiplication_order(size_t A_rows, size_t B_cols) {
    size_t len = A_rows * B_cols;
    order_t *order = (order_t *) malloc(len * sizeof(order_t));
    if (!order) {
        return NULL;
    }
    int i = 0;
    for (int row_a = 0; row_a < A_rows; ++row_a) {
        for (int row_b = 0; row_b < B_cols; ++row_b) {
            order[i].a= row_a;
            order[i].b= row_b;
            i += 1;
        }
    }
    return order;
}

//matrix_t *matrix__multiplication(matrix_t *A, matrix_t *B) {
//    if (A->shape.cols != B->shape.rows) {
//        LOG_ERROR("Shapes don't match for multiplication.");
//        return NULL;
//    }
//    matrix_t *B_T = MATRIX__transpose(B);
//    shape_t result_shape = {A->shape.rows, B->shape.cols};
//
////    element_t *result_elements = vectors__dot_products(A->elements, B->elements, A->shape.cols);
////
////
////    matrix_ctor_params_t params = matrix_ctor_params(.elements = result_elements, .shape=dot_shape,
////                                                     .length = dot_shape.rows
////                                                             * dot_shape.cols);
//    matrix_t *DOT = MATRIX__new(&params);
//    MATRIX__delete(B_T);
//    free(result_elements);
//    return DOT;
//}



