#include "matrix_internals.h"
#include <stdlib.h>
#include <matrix.h>
#include <logging.h>

bool matrix__ctor(struct matrix *self, struct matrix_ctor_params *params) {
        if (!MATRIX__are_params_valid(params)) {
                return false;
        }
        self->shape = params->shape;
        if (params->elements) {
                return MATRIX__copy_data(self, params);
        }
        return true;
}

bool matrix__dctor(struct matrix *self) {
        if (self->elements) {
                free(self->elements);
        }
        return true;
}

struct matrix *matrix__new(struct matrix_ctor_params *params) {
        struct matrix *self = calloc(1, sizeof(*self));
        if (self == NULL) {
                return NULL;
        }
        if (!matrix__ctor(self, params)) {
                free(self);
                return NULL;
        }
        return self;
}

struct matrix *matrix__delete(struct matrix *self) {
        if (self) {
                matrix__dctor(self);
                free(self);
        }
        return NULL;
}

struct matrix *matrix__transpose(struct matrix *self) {
        element_t *data = malloc(self->shape.rows * self->shape.cols * sizeof(*data));
        if (data == NULL) {
                return NULL;
        }
        struct mat2d_shape shape = self->shape;
        for (int r = 0; r < shape.rows; ++r) {
                for (int c = 0; c < shape.cols; ++c) {
                        data[r + shape.rows * c] = self->elements[c + shape.cols * r];
                }
        }
        struct matrix_ctor_params params = matrix_ctor_params(.elements = data,
                                                              .length = self->shape.rows * self->shape.cols,
                                                              .shape={ .rows=shape.cols, .cols=shape.rows });
        struct matrix *transposed = matrix__new(&params);
        free(data);
        return transposed;
}

element_t *
matrix__multiply_rows(element_t *mat_A, element_t *mat_B, size_t rows_A, size_t rows_B, size_t row_len) {
        size_t result_len = rows_A * rows_B;
        element_t * result = malloc(result_len * sizeof(*result));
        if (!result) {
                return NULL;
        }
        int k = 0;
        for (int i = 0; i < rows_A; ++i) {
                for (int j = 0; j < rows_B; ++j) {
                        result[k] = vector__dot_product(mat_A + i * row_len, mat_B + j * row_len, row_len);
                        ++k;
                }
        }
        return result;
}

struct matrix *matrix__multiplication(struct matrix *A, struct matrix *B) {
    if (A->shape.cols != B->shape.rows) {
        LOG_ERROR("Shapes don't match for multiplication.");
        return NULL;
    }
    struct matrix *B_T = matrix__transpose(B);
    struct mat2d_shape result_shape = {A->shape.rows, B->shape.cols};

    element_t * result_elements = matrix__multiply_rows(A->elements, B_T->elements, A->shape.rows, B_T->shape.rows, A->shape.cols);
    struct matrix_ctor_params params = matrix_ctor_params(.elements = result_elements, .shape=result_shape,
                                                     .length = result_shape.rows
                                                             * result_shape.cols);
    struct matrix *result = matrix__new(&params);
    matrix__delete(B_T);
    free(result_elements);
    return result;
}



