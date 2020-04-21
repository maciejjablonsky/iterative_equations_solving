#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H
#include "matrix.h"

#ifdef TEST
#define SOLUTION_EPSILON (1e-9)
#else
#define SOLUTION_EPSILON (1e-9)
#endif

struct matrix * lin_eq_sys__residuum(struct matrix * A, struct matrix * solution, struct matrix * b);


struct matrix *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b, int *iterations);

struct matrix * lin_eq_sys__gauss_seidel(struct matrix * A, struct matrix *b, int *iterations);

bool lin_eq_sys__is_solution_close_enough(struct matrix *A, struct matrix *x, struct matrix *b);

struct matrix * lin_eq_sys__forward_substitution(struct matrix * L, struct matrix *b);

struct matrix * lin_eq_sys__forward_substitution_when_left_diagonal(struct matrix *diagonal, struct matrix *b);

struct matrix * lin_eq_sys__backward_substitution(struct matrix * U, struct matrix * b);

struct matrix * lin_eq_sys__solve_using_LU_decomposition(struct matrix * A, struct matrix *b);

/**
 * @brief takes two matrices of the same size and does LU decomposition
 * @param[in, out] L eye matrix, after call stores lower triangular matrix of decomposition
 * @param[in, out] U square matrix initialized to system matrix, after call stores upper triangular matrix of decomposition
 */
void lin_eq_sys__LU_decomposition(struct matrix * L, struct matrix *U);

#endif // LINEAR_EQUATIONS_H
