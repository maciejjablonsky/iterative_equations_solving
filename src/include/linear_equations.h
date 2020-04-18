#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H

#include "matrix.h"

#define SOLUTION_EPSILON (1e-14f)

struct matrix * lin_eq_sys__residuum(struct matrix * A, struct matrix * solution, struct matrix * b);


struct vector *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b);

bool lin_eq_sys__is_solution_close_enough(struct matrix * residuum);

struct matrix * lin_eq_sys__backward_substitution(struct matrix * A, struct matrix *b);

#endif // LINEAR_EQUATIONS_H
