#include <stdio.h>
#include <stdlib.h>
#include "performance_test.h"
#include <math.h>
#include <logging.h>

#define MATRIX_SIZES (len_t[]){100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 15000, 20000}
#define MATRIX_SIZES_LEN (sizeof(MATRIX_SIZES)/sizeof(*(MATRIX_SIZES)))
#define BAND_VALUES (element_t[]){10, -1, -1}
#define BAND_VALUES_LEN 3
#define MAGIC_f 5

double perf_whole_time(struct lin_eq_sys_performance *data) {
        return data->init_time_seconds + data->kernel_time_seconds + data->cleaning_time_seconds;
}

void performance_data_to_csv(const char *path, struct lin_eq_sys_performance *data, len_t data_len) {
        FILE *output = fopen(path, "w");
        if (output == NULL) {
                LOG_ERROR("Failed to open file: %s\n", path);
                return;
        }

        fprintf(output, "%s,%s,%s,%s\r\n", "matrix_size", "iterations", "whole_time", "hot_loop_time");
        for (int i = 0; i < data_len; ++i) {
                fprintf(output, "%u,%u,%.8lf,%.8lf\r\n", data[i].matrix_size, data[i].iterations,
                        perf_whole_time(&data[i]), data[i].kernel_time_seconds);
        }
        fclose(output);
}

void present_jacobi_performance() {
        len_t N_len = 250;
        len_t *N = malloc(N_len * sizeof(*N));
        for (int i = 0; i < N_len; ++i) {
                N[i] = (i + 1) * 100;
        }
        struct lin_eq_sys_performance perf_data[N_len];
        const len_t w = 17; // field width
        printf("\rPerformance of Jacobi method.\n");
        printf("\r%*s\t%*s\t%*s\t%*s\n", w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u", n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);
//                debug_print_matrix_to_file(A, "A.txt", "w");
//                debug_print_matrix_to_file(b, "b.txt", "w");

                perf_data[i] = __lin_eq_sys_perf__jacobi(A, b);

                matrix__delete(A);
                matrix__delete(b);
                printf("\r%*u\t%*u\t%*.8lf\t%*.8lf ", w, perf_data[i].matrix_size, w, perf_data[i].iterations,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].kernel_time_seconds);

                printf("%*s\n", (int) (10 * perf_whole_time(&perf_data[i])), "##");
        }
        free(N);
//        debug_print_matrix_to_file(perf_data->solution, "solution_jacobi.txt", "w+");
        performance_data_to_csv("jacobi_performance.csv", perf_data, N_len);
        for (int i = 0; i < N_len; ++i) {
                matrix__delete(perf_data[i].solution);
        }
}


void present_gauss_seidel_performance() {
        len_t N_len = 250;
        len_t *N = malloc(N_len * sizeof(*N));
        for (int i = 0; i < N_len; ++i) {
                N[i] = (i + 1) * 100;
        }
        struct lin_eq_sys_performance perf_data[N_len];
        const len_t w = 17; // field width
        printf("\rPerformance of Gauss-Seidel method.\n");
        printf("\r%*s\t%*s\t%*s\t%*s\n", w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u", n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);
//                debug_print_matrix_to_file(A, "A.txt", "w");
//                debug_print_matrix_to_file(b, "b.txt", "w");

                perf_data[i] = __lin_eq_sys_perf__gauss_seidel(A, b);

                matrix__delete(A);
                matrix__delete(b);
                printf("\r%*u\t%*u\t%*.8lf\t%*.8lf ", w, perf_data[i].matrix_size, w, perf_data[i].iterations,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].kernel_time_seconds);

                printf("%*s\n", (int) (ceil(10 * perf_whole_time(&perf_data[i]))), "##");

        }
        free(N);
        debug_print_matrix_to_file(perf_data->solution, "solution_gauss_seidel.txt", "w+");
        performance_data_to_csv("gauss_seidel_performance.csv", perf_data, N_len);
        for (int i = 0; i < N_len; ++i) {
                matrix__delete(perf_data[i].solution);
        }
}

void present_LU_decomposition_performance() {
        len_t N_len = 25;
        len_t *N = malloc(N_len * sizeof(*N));
        for (int i = 0; i < N_len; ++i) {
                N[i] = (i + 1) * 1000;
        }
        struct lin_eq_sys_performance perf_data[N_len];
        const len_t w = 17; // field width
        printf("\rPerformance of LU decomposition.\n");
        printf("\r%*s\t%*s\t%*s\n", w, "matrix size [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        for (uint i = 0; i < N_len; ++i) {
                len_t n = N[i];
                printf("\rn: %u", n);
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
                struct matrix *b = matrix__b(n, MAGIC_f);
//                debug_print_matrix_to_file(A, "A.txt", "w");
//                debug_print_matrix_to_file(b, "b.txt", "w");

                perf_data[i] = __lin_eq_sys_perf__solve_using_LU_decomposition(A, b);

                matrix__delete(A);
                matrix__delete(b);
                printf("\r%*u\t%*.8lf\t%*.8lf ", w, perf_data[i].matrix_size,
                       w, perf_whole_time(&perf_data[i]), w, perf_data[i].kernel_time_seconds);

                printf("%*s\n", (int) (10 * perf_whole_time(&perf_data[i])), "##");
        }
        free(N);
//        debug_print_matrix_to_file(perf_data->solution, "solution_jacobi.txt", "w+");
        performance_data_to_csv("lu_performance_25000.csv", perf_data, N_len);
        for (int i = 0; i < N_len; ++i) {
                matrix__delete(perf_data[i].solution);
        }
}

void exercise_A(void) {
        printf("\r\n---------- Exercise A ----------\n\n");
        len_t n = 991;
        struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
        struct matrix *b = matrix__b(n, MAGIC_f);
        struct matrix *b_transposed = matrix__transpose(b);
        printf("Matrix A\n");
        matrix__print_compact(A, 5);
        printf("Vector b transposed\n");
        matrix__print_compact(b_transposed, 5);
        matrix__delete(b_transposed);
        matrix__delete(A);
        matrix__delete(b);
}

void exercise_B() {
        printf("\r\n---------- Exercise B ----------\n\n");
        len_t n = 991;
        struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, n, n);
        struct matrix *b = matrix__b(n, MAGIC_f);
        struct lin_eq_sys_performance jacobi = __lin_eq_sys_perf__jacobi(A, b);
        struct lin_eq_sys_performance jacobi_opt = __lin_eq_sys_perf__jacobi_optimized(A, b);
        struct lin_eq_sys_performance gauss_seidel = __lin_eq_sys_perf__gauss_seidel(A, b);
        int w = 20;
        printf("%*s\t%*s\t%*s\t%*s\t%*s\n", w, "method", w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]");
        printf("%*s\t%*u\t%*u\t%*.4lf\t%*.4lf\n", w, "Jacobi", w, jacobi.matrix_size, w, jacobi.iterations,
               w, perf_whole_time(&jacobi), w, jacobi.kernel_time_seconds);
        printf("%*s\t%*u\t%*u\t%*.4lf\t%*.4lf\n", w, "Jacobi optimized", w, jacobi_opt.matrix_size, w,
               jacobi_opt.iterations,
               w, perf_whole_time(&jacobi_opt), w, jacobi_opt.kernel_time_seconds);
        printf("%*s\t%*u\t%*u\t%*.4lf\t%*.4lf\n", w, "Gauss-Seidel", w, gauss_seidel.matrix_size, w,
               gauss_seidel.iterations,
               w, perf_whole_time(&gauss_seidel), w, gauss_seidel.kernel_time_seconds);

        printf("Solution Jacobi:\n");
        struct matrix * jacobi_transposed = matrix__transpose(jacobi.solution);
        matrix__print_compact(jacobi_transposed, 10);
        printf("Solution Gauss-Seidel:\n");
        struct matrix * gauss_seidel_transposed = matrix__transpose(gauss_seidel.solution);
        matrix__print_compact(gauss_seidel_transposed, 10);


        matrix__delete(A);
        matrix__delete(b);
        matrix__delete(jacobi_transposed);
        matrix__delete(jacobi.solution);
        matrix__delete(gauss_seidel.solution);
        matrix__delete(gauss_seidel_transposed);
}

void exercise_C(void) {
        printf("\r\n---------- Exercise C ----------\n\n");
        len_t n = 991;
        struct matrix *A = matrix__gen_band((element_t[]){3, -1, -1}, 3, n, n);
        struct matrix *b = matrix__b(n, MAGIC_f);
        int w = 20;
        printf("%*s\t%*s\t%*s\t%*s\t%*s\t%*s\n", w, "method", w, "matrix size [n]", w, "iterations [n]",
               w, "whole time [s]", w, "hot loop time [s]", w, "solution norm");

        struct lin_eq_sys_performance jacobi = __lin_eq_sys_perf__jacobi(A, b);
        printf("%*s\t%*u\t%*u\t%*.4lf\t%*.4lf\t%*.4Lf\n", w, "Jacobi", w, jacobi.matrix_size, w, jacobi.iterations,
               w, perf_whole_time(&jacobi), w, jacobi.kernel_time_seconds, w, jacobi.solution_norm);

        struct lin_eq_sys_performance jacobi_opt = __lin_eq_sys_perf__jacobi_optimized(A, b);
        printf("%*s\t%*u\t%*u\t%*.4lf\t%*.4lf\t%*.4Lf\n", w, "Jacobi optimized", w, jacobi_opt.matrix_size, w,
               jacobi_opt.iterations,
               w, perf_whole_time(&jacobi_opt), w, jacobi_opt.kernel_time_seconds, w, jacobi_opt.solution_norm);

        struct lin_eq_sys_performance gauss_seidel = __lin_eq_sys_perf__gauss_seidel(A, b);
        printf("%*s\t%*u\t%*u\t%*.4lf\t%*.4lf\t%*.4Lf\n", w, "Gauss-Seidel", w, gauss_seidel.matrix_size, w,
               gauss_seidel.iterations,
               w, perf_whole_time(&gauss_seidel), w, gauss_seidel.kernel_time_seconds, w, gauss_seidel.solution_norm);
}

void exercise_D(void) {
        printf("\r\n---------- Exercise D ----------\n\n");
        len_t n = 991;
        struct matrix *A = matrix__gen_band((element_t[]){3, -1, -1}, 3, n, n);
        struct matrix *b = matrix__b(n, MAGIC_f);
        struct lin_eq_sys_performance lu = __lin_eq_sys_perf__solve_using_LU_decomposition(A, b);
        int w = 20;
        printf("%*s\t%*s\t%*s\t%*s\t%*s\n", w, "method", w, "matrix size [n]",
               w, "whole time [s]", 26, "decomposition + kernel [s]", w, "solution norm");
        printf("%*s\t%*u\t%*.4lf\t%*.4lf\t%*.10Le\n", w, "LU decomposition", w, lu.matrix_size,
               w, lu.init_time_seconds + lu.decompositon_time_seconds + lu.kernel_time_seconds + lu.cleaning_time_seconds,
               26, lu.kernel_time_seconds + lu.decompositon_time_seconds, w, lu.solution_norm);

        printf("\r\nSolution vector:\n");
        struct matrix * solution_transposed = matrix__transpose(lu.solution);
        matrix__print_compact(solution_transposed,8);
        matrix__delete(solution_transposed);
        matrix__delete(lu.solution);

}

void exercise_E() {
        printf("\r\n---------- Exercise E ----------\n\n");
        len_t N[] = {100, 500, 1000, 2000, 3000};
        len_t N_len = sizeof(N) / sizeof(*N);
        struct lin_eq_sys_performance jacobi[N_len];
        struct lin_eq_sys_performance gauss_seidel[N_len];
        struct lin_eq_sys_performance lu[N_len];
        int w = 20;
        printf("%*s\t%*s\t%*s\t%*s\n", w, "matrix size [n]", w, "Jacobi [s]",
               w, "Gauss-Seidel [s]", w, "LU decomposition [s]");
        for (int i = 0; i < N_len; ++i) {
                struct matrix *A = matrix__gen_band(BAND_VALUES, BAND_VALUES_LEN, N[i], N[i]);
                struct matrix *b = matrix__b(N[i], MAGIC_f);
                printf("%*u\t", w, N[i]);
                jacobi[i] = __lin_eq_sys_perf__jacobi(A, b);
                printf("%*.4lf\t", w, jacobi[i].kernel_time_seconds);

                gauss_seidel[i] = __lin_eq_sys_perf__gauss_seidel(A,b);
                printf("%*.4lf\t", w, gauss_seidel[i].kernel_time_seconds);

                lu[i] = __lin_eq_sys_perf__solve_using_LU_decomposition(A, b);
                printf("%*.4lf", w, lu[i].kernel_time_seconds + lu[i].decompositon_time_seconds);

                putchar('\n');
                matrix__delete(A);
                matrix__delete(b);
        }


}

int main() {
         exercise_A();
         exercise_B();
         exercise_C();
         exercise_D();
         exercise_E();
}