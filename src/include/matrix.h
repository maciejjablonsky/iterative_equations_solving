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
#define matrix_ctor_params(...) ((matrix_ctor_params_t){__VA_ARGS__})

bool MATRIX__ctor(matrix_t * self, matrix_ctor_params_t * params);

bool MATRIX__dctor(matrix_t * self);

matrix_t * MATRIX__new(matrix_ctor_params_t * params);

matrix_t * MATRIX__delete(matrix_t * matrix);

matrix_t * MATRIX__transpose(matrix_t * matrix);

matrix_t * MATRIX__dot(matrix_t * A, matrix_t * B);



#endif // MATRIX_H
