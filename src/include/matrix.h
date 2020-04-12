#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>
#include <stdbool.h>
#include "vector.h"

typedef struct {
    size_t rows;
    size_t cols;
} shape_t;

typedef struct {
    element_t * elements;
    shape_t shape;
} matrix_t;

typedef struct {
    shape_t shape;
    element_t * elements;
    size_t length;
} matrix_ctor_params_t;
#define matrix_ctor_params(...) ((matrix_ctor_params_t){__VA_ARGS__})


#define POWER_OF_2(N) ((size_t)1u<<(N))

bool MATRIX__ctor(matrix_t * self, matrix_ctor_params_t * params);

bool MATRIX__dctor(matrix_t * self);

matrix_t * MATRIX__new(matrix_ctor_params_t * params);

matrix_t * MATRIX__delete(matrix_t * matrix);

matrix_t * MATRIX__transpose(matrix_t * matrix);

matrix_t * matrix__multiplication(matrix_t * A, matrix_t * B);


#endif // MATRIX_H
