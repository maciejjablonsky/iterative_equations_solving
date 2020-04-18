#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H

#include "matrix.h"

#define SOLUTION_EPSILON (10e-9f)

struct matrix * lin_eq_sys__residuum(struct matrix * A, struct matrix * solution, struct matrix * b);


struct matrix *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b, int *iterations);

bool lin_eq_sys__is_solution_close_enough(struct matrix *A, struct matrix *x, struct matrix *b);

struct matrix * lin_eq_sys__forward_substitution(struct matrix * L, struct matrix *b);

struct matrix * lin_eq_sys__forward_substitution_when_left_diagonal(struct matrix *L, struct matrix *b);

#endif // LINEAR_EQUATIONS_H
