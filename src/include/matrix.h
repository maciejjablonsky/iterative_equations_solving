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
};

enum matrix_storage_type {DEEP_COPY, SHALLOW_COPY};

struct matrix_ctor_params {
    struct mat2d_shape shape;
    element_t * elements;
    size_t length;
    enum matrix_storage_type storage;
};
#define matrix_ctor_params(...) ((struct matrix_ctor_params){__VA_ARGS__})


#define POWER_OF_2(N) ((size_t)1u<<(N))

bool matrix__ctor(struct matrix * self, struct matrix_ctor_params * params);

bool matrix__dctor(struct matrix * self);

struct matrix * matrix__new(struct matrix_ctor_params * params);

struct matrix * matrix__delete(struct matrix * self);

struct matrix * matrix__transpose(struct matrix * self);

struct matrix * matrix__multiplication(struct matrix * A, struct matrix * B);

bool matrix__are_params_valid(struct matrix_ctor_params *params);

bool matrix__copy_data(struct matrix *self, struct matrix_ctor_params *params);

element_t * matrix__direct_gauss(struct matrix * system_matrix, element_t * vectorB, size_t lenB);


element_t *
matrix__multiply_rows(element_t *mat_A, element_t *mat_B, size_t rows_A, size_t rows_B, size_t row_len);

struct matrix *matrix__new_band(struct matrix_ctor_params *params);

#endif // MATRIX_H
