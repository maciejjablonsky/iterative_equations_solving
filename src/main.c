#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "linear_equations.h"

#define givenSystemOfEquations(A, solutions, b) \
                struct matrix *(A) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                2, 3, 5,\
                                6, 4, 2,\
                                5, -2, 1\
                        }, .rows=3, .cols=3\
                };\
                struct matrix *(solutions) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                0.5,\
                                -0.5,\
                                0.5\
                        }, .rows=3, .cols=1\
                };\
                struct matrix *(b) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                2,\
                                2,\
                                4\
                        }, .rows = 3, .cols = 1\
                };

#undef expectedResult
#define expectedResult(expected) struct matrix * (expected) = &(struct matrix){\
                .elements=(element_t[]){\
                        0,\
                        0,\
                        0}, .rows = 3, .cols = 1\
        }

int main() {
        givenSystemOfEquations(A, x, b);
        struct matrix * res = lin_eq_sys__residuum(A, x, b);
        for (int i = 0; i < res->rows; ++i) {
                printf("%Lg ", res->elements[i]);
        }
        putchar('\n');
        lin_eq_sys__jacobi(A, b);
}