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
    if (self->data) {
        free(self->data);
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
    matrix_e_t *data = (matrix_e_t *) malloc(matrix->shape.rows * matrix->shape.cols * sizeof(matrix_e_t));
    if (data == NULL) {
        return NULL;
    }
    matrix_shape_t shape = matrix->shape;
    for (int r = 0; r < shape.rows; ++r) {
        for (int c = 0; c < shape.cols; ++c) {
            data[r + shape.rows * c] = matrix->data[c + shape.rows * r];
        }
    }
    matrix_ctor_params_t params = matrix_ctor_params(.elements = data,
                                                     .length = matrix->shape.rows * matrix->shape.cols,
                                                     .shape=shape);
    matrix_t *transposed = MATRIX__new(&params);
    free(data);
    return transposed;
}

matrix_t *MATRIX__dot(matrix_t *A, matrix_t *B) {
    if (A->shape.cols != B->shape.rows) {
        LOG_ERROR("Shapes don't match for multiplication.");
        return NULL;
    }
    matrix_t * B_T = MATRIX__transpose(B);
    matrix_shape_t new_shape = {A->shape.rows, B->shape.cols};
    matrix_e_t * new_data =  (matrix_e_t*)malloc(new_shape.rows * new_shape.cols * sizeof(matrix_e_t));
    if (new_data == NULL) {
        return NULL;
    }
    for (int i = 0, length = new_shape.rows * new_shape.cols; i < length; ++i) {
        matrix_e_t sum = 0;
        for (int j = 0; j < A->shape.cols; ++j) {
            sum += A->data[i*new_shape.cols + j] * B_T->data[i*new_shape.cols + j];
        }
        new_data[i*new_shape.cols] = sum;
    }
    matrix_ctor_params_t params = matrix_ctor_params(.elements = new_data, .shape=new_shape, .length = new_shape.rows
            * new_shape.cols);
    matrix_t * C = MATRIX__new(&params);
    MATRIX__delete(B_T);
    free(new_data);
    return C;
}

