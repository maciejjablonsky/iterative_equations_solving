#ifndef DIRECT_GAUSS_H
#define DIRECT_GAUSS_H

#include "matrix.h"
#include <stdint.h>

struct __subtraction_job_data {
    element_t * i_th_row;
    element_t * subtrahend;
    len_t row_len;
    element_t alpha;
};
#define __subtraction_job_data(...) ((struct __subtraction_job_data){__VA_ARGS__})

element_t *direct_gauss__solve(struct matrix *system_matrix, element_t *vectorB, size_t len_B);

void __direct_gauss__zeros_below_diagonal(element_t *system, len_t rows, len_t cols, element_t *vectorB, len_t len_B);

void __direct_gauss__subtract_row_from_other(element_t * minuend, element_t * subtrahend, size_t row_len, element_t alpha);

void __direct_gauss__zeroing_step(uint step, element_t *system, len_t rows, len_t cols, element_t *vectorB);

void * __direct_gauss__subtraction_job(void * data);

#endif // DIRECT_GAUSS_H
