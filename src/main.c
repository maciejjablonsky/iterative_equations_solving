#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "linear_equations.h"

#define MATRIX_SIZES (len_t[]){100, 500, 1000, 2000, 3000}//, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000}
#define MATRIX_SIZES_LEN (sizeof(MATRIX_SIZES)/sizeof(*(MATRIX_SIZES)))
#define BAND_VALUES (element_t[]){10, -1, -1}
#define BAND_VALUES_LEN 3
#define MAGIC_f 5

double perf_whole_time(struct lin_eq_sys_performance * data) {
        return data->init_time_seconds + data->hot_loop_time_seconds + data->cleaning_time_seconds;
}

void print_performance_to_file(FILE * stream, struct lin_eq_sys_performance * perf_data, len_t len) {
        const len_t w = 17; // field width
        printf("\rPerformance of Jacobi method.\n");
        printf("%*s\t%*s\t%*s\t%*s\n",w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (int i = 0; i < len; ++i) {
                printf("%*u\t%*u\t%*.8lf\t%*.8lf\n", w, perf_data[i].matrix_size, w, perf_data[i].iterations,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].hot_loop_time_seconds);
        }
}

void present_jacobi_performance() {
        len_t  * N = MATRIX_SIZES;
        len_t N_len = MATRIX_SIZES_LEN;
        struct lin_eq_sys_performance perf_data[N_len];
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u\n",n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);

                perf_data[i] = __lin_eq_sys_perf__jacobi(A, b);

                matrix__delete(A);
                matrix__delete(b);

        }

        print_performance_to_file(stdin, perf_data, N_len);

}



int main() {
        present_jacobi_performance();
}