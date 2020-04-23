#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "linear_equations.h"
#include <math.h>
#include <logging.h>

#define MATRIX_SIZES (len_t[]){100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 15000, 20000}
#define MATRIX_SIZES_LEN (sizeof(MATRIX_SIZES)/sizeof(*(MATRIX_SIZES)))
#define BAND_VALUES (element_t[]){10, -1, -1}
#define BAND_VALUES_LEN 3
#define MAGIC_f 5

double perf_whole_time(struct lin_eq_sys_performance * data) {
        return data->init_time_seconds + data->hot_loop_time_seconds + data->cleaning_time_seconds;
}

void performance_data_to_csv(const char * path, struct lin_eq_sys_performance * data, len_t data_len) {
        FILE * output = fopen(path,"w");
        if (output == NULL) {
                LOG_ERROR("Failed to open file: %s\n", path);
                return;
        }

        fprintf(output, "%s,%s,%s,%s\r\n", "matrix_size", "iterations", "whole_time", "hot_loop_time");
        for (int i = 0; i < data_len; ++i) {
                fprintf(output, "%u,%u,%.8lf,%.8lf\r\n", data[i].matrix_size, data[i].iterations, perf_whole_time(&data[i]), data[i].hot_loop_time_seconds);
        }
        fclose(output);
}

void present_jacobi_performance() {
        len_t N_len = 400;
        len_t * N = malloc(N_len *sizeof(*N));
        for (int i = 0; i < N_len; ++i) {
                N[i] = (i+1) * 100;
        }
        struct lin_eq_sys_performance perf_data[N_len];
        const len_t w = 17; // field width
        printf("\rPerformance of Jacobi method.\n");
        printf("\r%*s\t%*s\t%*s\t%*s\n",w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u",n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);
//                debug_print_matrix_to_file(A, "A.txt", "w");
//                debug_print_matrix_to_file(b, "b.txt", "w");

                perf_data[i] = __lin_eq_sys_perf__jacobi(A, b);

                matrix__delete(A);
                matrix__delete(b);
                printf("\r%*u\t%*u\t%*.8lf\t%*.8lf ", w, perf_data[i].matrix_size, w, perf_data[i].iterations,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].hot_loop_time_seconds);

                printf("%*s\n", (int)(10*perf_whole_time(&perf_data[i])), "##");
        }
        free(N);
//        debug_print_matrix_to_file(perf_data->solution, "solution_jacobi.txt", "w+");
        performance_data_to_csv("jacobi_without_optimization_performance.csv", perf_data, N_len);
        for (int i = 0; i < N_len; ++i) {
                matrix__delete(perf_data[i].solution);
        }
}


void present_gauss_seidel_performance() {
        len_t N_len = 400;
        len_t * N = malloc(N_len *sizeof(*N));
        for (int i = 0; i < N_len; ++i) {
                N[i] = (i+1) * 100;
        }
        struct lin_eq_sys_performance perf_data[N_len];
        const len_t w = 17; // field width
        printf("\rPerformance of Gauss-Seidel method.\n");
        printf("\r%*s\t%*s\t%*s\t%*s\n",w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u",n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);
//                debug_print_matrix_to_file(A, "A.txt", "w");
//                debug_print_matrix_to_file(b, "b.txt", "w");

                perf_data[i] = __lin_eq_sys_perf__gauss_seidel(A, b);

                matrix__delete(A);
                matrix__delete(b);
                printf("\r%*u\t%*u\t%*.8lf\t%*.8lf ", w, perf_data[i].matrix_size, w, perf_data[i].iterations,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].hot_loop_time_seconds);

                printf("%*s\n", (int)(ceil(10*perf_whole_time(&perf_data[i]))), "##");

        }
        free(N);
        debug_print_matrix_to_file(perf_data->solution, "solution_gauss_seidel.txt", "w+");
        performance_data_to_csv("gauss_seidel_performance.csv", perf_data, N_len);
        for (int i = 0; i < N_len; ++i) {
                matrix__delete(perf_data[i].solution);
        }
}

void present_LU_decomposition_performance() {
        len_t N_len =40;
        len_t * N = malloc(N_len *sizeof(*N));
        for (int i = 0; i < N_len; ++i) {
                N[i] = (i+1) * 1000;
        }
        struct lin_eq_sys_performance perf_data[N_len];
        const len_t w = 17; // field width
        printf("\rPerformance of LU decomposition.\n");
        printf("\r%*s\t%*s\t%*s\n",w, "matrix size [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u",n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);
//                debug_print_matrix_to_file(A, "A.txt", "w");
//                debug_print_matrix_to_file(b, "b.txt", "w");

                perf_data[i] = __lin_eq_sys_perf__solve_using_LU_decomposition(A, b);

                matrix__delete(A);
                matrix__delete(b);
                printf("\r%*u\t%*.8lf\t%*.8lf ", w, perf_data[i].matrix_size,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].hot_loop_time_seconds);

                printf("%*s\n", (int)(10*perf_whole_time(&perf_data[i])), "##");
        }
        free(N);
//        debug_print_matrix_to_file(perf_data->solution, "solution_jacobi.txt", "w+");
        performance_data_to_csv("lu_performance.csv", perf_data, N_len);
        for (int i = 0; i < N_len; ++i) {
                matrix__delete(perf_data[i].solution);
        }
}


int main() {
        present_jacobi_performance();
        present_gauss_seidel_performance();
        present_LU_decomposition_performance();
}