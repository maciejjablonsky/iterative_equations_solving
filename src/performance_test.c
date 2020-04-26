#include <time.h>
#include "performance_test.h"

struct lin_eq_sys_performance __lin_eq_sys_perf__jacobi(struct matrix *A, struct matrix *b) {
        struct lin_eq_sys_performance perf;
        perf.matrix_size = A->rows;

        perf.init_time_seconds = clock();
        struct matrix *x, *D, *L_U;
        __lin_eq_sys_jacobi__init(A, b, &x, &D, &L_U);
        perf.init_time_seconds = (clock() - perf.init_time_seconds) / CLOCKS_PER_SEC;

        perf.iterations = 0;
        perf.kernel_time_seconds = clock();
        while (!lin_eq_sys__is_solution_close_enough(A, x, b)) {
                __lin_eq_sys_jacobi__hot_loop_step(L_U, D, b, &x);
                perf.iterations++;

//                struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
//                element_t norm = vector__norm(&vector_struct(
//                        .elements = residuum->elements, .len = residuum->rows)
//                );
//                matrix__delete(residuum);
                //printf("\rnorm: %-20.10lf", norm);
        }
        perf.kernel_time_seconds = (clock() - perf.kernel_time_seconds) / CLOCKS_PER_SEC;
        perf.solution = x;

        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
        );
        matrix__delete(residuum);
        perf.solution_norm = norm;

        perf.cleaning_time_seconds = clock();
        __lin_eq_sys_jacobi__end(&D, &L_U);
        perf.cleaning_time_seconds = (clock() - perf.cleaning_time_seconds) / CLOCKS_PER_SEC;
        return perf;
}

struct lin_eq_sys_performance __lin_eq_sys_perf__gauss_seidel(struct matrix *A, struct matrix *b) {
        struct lin_eq_sys_performance perf;
        perf.matrix_size = A->rows;
        perf.init_time_seconds = clock();
        struct matrix *x, *D_L, *U;
        __lin_eq_sys_gauss_seidel__init(A, b, &x, &D_L, &U);
        perf.init_time_seconds = (clock() - perf.init_time_seconds)/CLOCKS_PER_SEC;

        perf.iterations = 0;
        perf.kernel_time_seconds = clock();
        while (!lin_eq_sys__is_solution_close_enough(A, x, b)) {
                __lin_eq_sys_gauss_seidel__hot_loop_step(U, D_L, b, &x);
                perf.iterations++;
        }
        perf.kernel_time_seconds = (clock() - perf.kernel_time_seconds) / CLOCKS_PER_SEC;

        perf.solution = x;
        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
        );
        matrix__delete(residuum);
        perf.solution_norm = norm;

        perf.cleaning_time_seconds = clock();
        __lin_eq_sys_gauss_seidel__end(&D_L, &U);
        perf.cleaning_time_seconds = (clock() - perf.cleaning_time_seconds) / CLOCKS_PER_SEC;
        return perf;
}

struct lin_eq_sys_performance __lin_eq_sys_perf__solve_using_LU_decomposition(struct matrix *A, struct matrix *b) {
        struct lin_eq_sys_performance perf;
        perf.matrix_size = b->rows;
        perf.iterations = 1;
        perf.init_time_seconds = clock();
        struct matrix * U = A;
        struct matrix * L = matrix__eye(b->rows);
        struct matrix * b_copy = matrix__deep_copy(b);
        perf.init_time_seconds = (clock() - perf.init_time_seconds)/CLOCKS_PER_SEC;

        perf.decompositon_time_seconds = clock();
        lin_eq_sys__LU_decomposition(L, U);
        perf.decompositon_time_seconds = (clock() - perf.decompositon_time_seconds)/CLOCKS_PER_SEC;

        perf.kernel_time_seconds = clock();
        struct matrix * y = lin_eq_sys__forward_substitution(L, b_copy);
        struct matrix * x = lin_eq_sys__backward_substitution(U, y);
        perf.kernel_time_seconds = (clock() - perf.kernel_time_seconds) / CLOCKS_PER_SEC;

        perf.cleaning_time_seconds = clock();
        matrix__delete(L);
        matrix__delete(b_copy);
        perf.cleaning_time_seconds = (clock() - perf.cleaning_time_seconds)/CLOCKS_PER_SEC;
        perf.solution = x;
        return perf;
}

struct lin_eq_sys_performance __lin_eq_sys_perf__jacobi_optimized(struct matrix *A, struct matrix *b) {
        struct lin_eq_sys_performance perf;
        perf.matrix_size = A->rows;

        perf.init_time_seconds = clock();
        struct matrix *x, *D, *L_U;
        __lin_eq_sys_jacobi__init(A, b, &x, &D, &L_U);
        perf.init_time_seconds = (clock() - perf.init_time_seconds) / CLOCKS_PER_SEC;

        perf.iterations = 0;
        perf.kernel_time_seconds = clock();
        while (!lin_eq_sys__is_solution_close_enough(A, x, b)) {
                __lin_eq_sys_jacobi_optimized__hot_loop_step(L_U, D, b, &x);
                perf.iterations++;
        }
        perf.kernel_time_seconds = (clock() - perf.kernel_time_seconds) / CLOCKS_PER_SEC;
        perf.solution = x;

        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
        );
        matrix__delete(residuum);
        perf.solution_norm = norm;

        perf.cleaning_time_seconds = clock();
        __lin_eq_sys_jacobi__end(&D, &L_U);
        perf.cleaning_time_seconds = (clock() - perf.cleaning_time_seconds) / CLOCKS_PER_SEC;
        return perf;
}