#ifndef MATRIX_INTERNALS_H
#define MATRIX_INTERNALS_H
#include "matrix.h"

bool MATRIX__are_params_valid(matrix_ctor_params_t * params);

bool MATRIX__copy_data(matrix_t * self, matrix_ctor_params_t * params);

#endif //MATRIX_INTERNALS_H