#include "linear_equations.h"
#include "logging.h"

struct matrix *lin_eq_sys__residuum(struct matrix *A, struct matrix *solution, struct matrix *b) {
        struct matrix *residuum = matrix__multiply(A, solution);
        if (residuum == NULL) {
                LOG_ERROR("Can't calculate residuum, multiplication returned NULL.");
                return NULL;
        }
        if (matrix__subtraction(residuum, b) == NULL) {
                LOG_ERROR("Can't calculate residuum, subtraction returned NULL.");
                matrix__delete(residuum);
                return NULL;
        };
        return residuum;
}

struct matrix * lin_eq_sys__backward_substitution(struct matrix * A, struct matrix *b) {
        return NULL;
}

struct vector *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b) {
        struct matrix *x = matrix__ones(b->rows);

//        struct matrix *D = matrix__diagonal(A);
        struct matrix *L_U = matrix__copy(A);
        matrix__zero_out_diagonal(L_U);

        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        while (lin_eq_sys__is_solution_close_enough(residuum)) {
                LOG_ERROR("hua");
                break;
        }
        return NULL;
}


bool lin_eq_sys__is_solution_close_enough(struct matrix *residuum) {
       return vector__norm(&vector_struct(.elements = residuum->elements, .len = residuum->rows)) >= SOLUTION_EPSILON;
}