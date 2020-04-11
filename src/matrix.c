#include "matrix.h"
#include "matrix_internals.h"
#include "log.h"
#include <stdlib.h>

bool MATRIX__ctor(matrix_t *self, matrix_ctor_params_t *params) {
    if (!MATRIX__are_params_valid(params)) {
        return false;
    }
    self->shape = params->shape;
    self->data = calloc(params->shape.rows * params->shape.cols, sizeof(matrix_e_t));


}

bool MATRIX__are_params_valid(matrix_ctor_params_t *params) {
    if (params == NULL) {
        LOG_ERROR("Initial parameters for full matrix not given.");
        return false;
    }
    if (params->shape.rows == 0 || params->shape.cols == 0) {
        LOG_ERROR("Matrix cannot have zero rows or columns.");
        return false;
    }
    if (params->elements != NULL
        && params->shape.rows * params->shape.cols != params->length) {
        LOG_ERROR("Matrix shape doesn't match number of elements.");
        return false;
    }
    return true;
}