#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "linear_equations.h"

struct lin_eq_sys_performance {
    len_t matrix_size;
    len_t iterations;
    double kernel_time_seconds;
    double decompositon_time_seconds;
    long double solution_norm;
    double init_time_seconds;
    double cleaning_time_seconds;
    struct matrix *solution;
};

struct lin_eq_sys_performance __lin_eq_sys_perf__jacobi(struct matrix *A, struct matrix *b);

struct lin_eq_sys_performance __lin_eq_sys_perf__jacobi_optimized(struct matrix *A, struct matrix *b);

struct lin_eq_sys_performance __lin_eq_sys_perf__gauss_seidel(struct matrix *A, struct matrix *b);

struct lin_eq_sys_performance __lin_eq_sys_perf__solve_using_LU_decomposition(struct matrix *A,  struct matrix *b);


#endif //PERFORMANCE_H
