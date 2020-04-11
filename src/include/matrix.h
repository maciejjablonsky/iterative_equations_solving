#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>
#include <stdbool.h>

typedef double matrix_e_t;

typedef struct {
    size_t rows;
    size_t cols;
} matrix_shape_t;

typedef struct {
    matrix_e_t * data;
    matrix_shape_t shape;
} matrix_t;

typedef struct {
    matrix_shape_t shape;
    matrix_e_t * elements;
    size_t length;
} matrix_ctor_params_t;

bool MATRIX__ctor(matrix_t * self, matrix_ctor_params_t * params);




#endif // MATRIX_H
