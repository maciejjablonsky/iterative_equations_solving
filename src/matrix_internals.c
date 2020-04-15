#include "matrix_internals.h"
#include "logging.h"
#include <stdlib.h>
#include <string.h>

bool MATRIX__are_params_valid(struct matrix_ctor_params *params) {
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

bool MATRIX__copy_data(struct matrix *self, struct matrix_ctor_params *params) {
    self->elements = calloc(params->length, sizeof(element_t));
    if (self->elements == NULL) {
        return false;
    }
    memcpy(self->elements, params->elements, params->length * sizeof(element_t));
    return true;
}

