#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H
#include "matrix.h"

#ifdef TEST
#define SOLUTION_EPSILON (1e-15)
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

struct matrix * lin_eq_sys__lu_decomposition(struct matrix * U, struct matrix *b);

#endif // LINEAR_EQUATIONS_H
