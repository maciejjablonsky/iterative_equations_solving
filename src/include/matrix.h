#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>
#include <stdbool.h>
#include "vector.h"

struct mat2d_shape {
	size_t rows;
	size_t cols;
};

struct matrix {
    element_t * elements;
    struct mat2d_shape shape;
} ;

struct matrix_multiplication_order {
    size_t row_a;
    size_t row_b;
};

struct matrix_ctor_params {
    struct mat2d_shape shape;
    element_t * elements;
    size_t length;
} ;
#define matrix_ctor_params(...) ((struct matrix_ctor_params){__VA_ARGS__})


#define POWER_OF_2(N) ((size_t)1u<<(N))

bool matrix__ctor(struct matrix * self, struct matrix_ctor_params * params);

bool matrix__dctor(struct matrix * self);

struct matrix * matrix__new(struct matrix_ctor_params * params);

struct matrix * matrix__delete(struct matrix * self);

struct matrix * matrix__transpose(struct matrix * self);

struct matrix * matrix__multiplication(struct matrix * A, struct matrix * B);

bool MATRIX__are_params_valid(struct matrix_ctor_params *params);

bool MATRIX__copy_data(struct matrix *self, struct matrix_ctor_params *params);


element_t *
matrix__multiply_rows(element_t *mat_A, element_t *mat_B, size_t rows_A, size_t rows_B, size_t row_len);


#endif // MATRIX_H
