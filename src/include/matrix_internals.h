#ifndef MATRIX_INTERNALS_H
#define MATRIX_INTERNALS_H

#include "matrix.h"

bool MATRIX__are_params_valid(struct matrix_ctor_params *params);

bool MATRIX__copy_data(struct matrix *self, struct matrix_ctor_params *params);

#endif //MATRIX_INTERNALS_H