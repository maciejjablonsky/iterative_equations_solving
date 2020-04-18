#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

struct matrix {
    element_t *elements;
    len_t rows;
    len_t cols;
};

#define matrix_struct(...) (struct matrix){__VA_ARGS__}

struct matrix *matrix__gen_band(element_t *first_row, len_t first_row_len, len_t rows, len_t cols);

struct matrix *matrix__triu(struct matrix *mat, uint start_diagonal);

struct matrix *matrix__tril(struct matrix *mat, uint start_diagonal);

struct matrix *matrix__ones(len_t n);

struct matrix *matrix__b(len_t n);

struct matrix *__malloc_matrix(len_t elements_length);

struct matrix *__calloc_matrix(len_t elements_length);

void matrix__zero_out_diagonal(struct matrix *mat);

void matrix__multiply_by_scalar(struct matrix *mat, element_t value);

// saves result to left matrix
struct matrix *matrix__sub(struct matrix *left, struct matrix *right);

struct matrix *matrix__multiply(struct matrix *A, struct matrix *B);

struct matrix *matrix__copy(const struct matrix *const original);

struct matrix *matrix__diagonal(struct matrix *mat);

struct matrix *matrix__transpose(struct matrix *mat);

len_t matrix__len(const struct matrix *mat);

struct matrix *
matrix__multiply_one_by_second_transposed(struct matrix *left, struct matrix *right_transposed);

struct matrix *matrix__delete(struct matrix *mat);

struct matrix * matrix__add(struct matrix * left, struct matrix *right);

void print_matrix_to_file(struct matrix *mat, const char *filename);

#endif // MATRIX_H
