#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H

#include "matrix.h"

#ifdef TEST
#define SOLUTION_EPSILON (1e-12)
#else
#define SOLUTION_EPSILON (1e-9)
#endif

struct lin_eq_sys_performance {
    len_t matrix_size;
    len_t iterations;
    double hot_loop_time_seconds;
    long double solution_norm;
    double init_time_seconds;
    double cleaning_time_seconds;
    struct matrix *solution;
};

/**
 *
 * @param A
 * @param solution
 * @param b
 * @return
 */
struct matrix *lin_eq_sys__residuum(const struct matrix *A, const struct matrix *solution, const struct matrix *b);


struct matrix *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b);

void __lin_eq_sys_jacobi__init(struct matrix *A, struct matrix *b, struct matrix **x, struct matrix **D,
                               struct matrix **L_U);

void __lin_eq_sys_jacobi__end(struct matrix **D, struct matrix **L_U);

void __lin_eq_sys_jacobi__hot_loop_step(struct matrix *L_U, struct matrix *D, struct matrix *b, struct matrix **x);

struct lin_eq_sys_performance __lin_eq_sys_perf__jacobi(struct matrix *A, struct matrix *b);

struct matrix *lin_eq_sys__gauss_seidel(struct matrix *A, struct matrix *b);

struct lin_eq_sys_performance __lin_eq_sys_perf__gauss_seidel(struct matrix *A, struct matrix *b);

void __lin_eq_sys_gauss_seidel__init(struct matrix *A, struct matrix *b, struct matrix **x, struct matrix **D_L,
                                     struct matrix **U);

void __lin_eq_sys_gauss_seidel__hot_loop_step(struct matrix *U, struct matrix *D_L,
                                              struct matrix *b, struct matrix **x);

void __lin_eq_sys_gauss_seidel__end(struct matrix **D_L, struct matrix **U);

bool lin_eq_sys__is_solution_close_enough(struct matrix *A, struct matrix *x, struct matrix *b);

struct matrix *lin_eq_sys__forward_substitution(struct matrix *L, struct matrix *b);

struct matrix *lin_eq_sys__forward_substitution_when_left_diagonal(struct matrix *diagonal, struct matrix *b);

struct matrix *lin_eq_sys__backward_substitution(struct matrix *U, struct matrix *b);

struct matrix *lin_eq_sys__solve_using_LU_decomposition(struct matrix *A, struct matrix *b);

struct lin_eq_sys_performance __lin_eq_sys_perf__solve_using_LU_decomposition(struct matrix *A,  struct matrix *b);

/**
 * @brief takes two matrices of the same size and does LU decomposition
 * @param[in, out] L eye matrix, after call stores lower triangular matrix of decomposition
 * @param[in, out] U square matrix initialized to system matrix, after call stores upper triangular matrix of decomposition
 */
void lin_eq_sys__LU_decomposition(struct matrix *L, struct matrix *U);

#endif // LINEAR_EQUATIONS_H
