#include "direct_gauss.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


element_t *direct_gauss__solve(struct matrix *system_matrix, element_t *vectorB, size_t len_B) {
        size_t rows = system_matrix->shape.rows;
        size_t cols = system_matrix->shape.cols;
        element_t *system = system_matrix->elements;
        __direct_gauss__zeros_below_diagonal(system, rows, cols, vectorB, len_B);
        return system;
}



void __direct_gauss__zeros_below_diagonal(element_t *system, len_t rows, len_t cols, element_t *vectorB, len_t len_B) {
        for (uint n = 0; n < rows; ++n) {
                __direct_gauss__zeroing_step(n, system, rows, cols, vectorB);
        }
}

// TODO malloc check
void __direct_gauss__zeroing_step(uint step, element_t *system, len_t rows, len_t cols, element_t *vectorB) {
        for (uint r = step + 1, thr = 0; r < rows; ++r, ++thr) {
                float alpha = system[r * cols + step] / system[step * cols + step];
                for (int c = 0; c < cols; ++c) {
                        system[r * cols + c] -= alpha * system[step * cols + c];
                }
                vectorB[r] -= alpha * vectorB[step];
        }
}

void *__direct_gauss__subtraction_job(void *data) {
        struct __subtraction_job_data *__data = (struct __subtraction_job_data *) data;
        element_t *i_th_row = __data->i_th_row;
        element_t *subtrahend = __data->subtrahend;
        float alpha = __data->alpha;
        for (int c = 0; c < __data->row_len; ++c) {
                i_th_row[c] -= alpha * subtrahend[c];
        }
        return NULL;
}

