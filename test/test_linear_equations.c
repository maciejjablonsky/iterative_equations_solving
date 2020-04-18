#include "unity.h"
#include "linear_equations.h"
#include "matrix.h"
#include "vector.h"
#include "helper.h"
#include "matrix_test_helper.h"

#undef givenSystemOfEquations
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

#define thenResultIsValid(expected, actual) do {\
                one_is_another_deep_copy(expected, actual);\
        } while(0)


void test_givenSystemOfEquations_whenCountedResiduum_thenResultIsValid(void) {
        givenSystemOfEquations(A, x, b);

        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        expectedResult(expected);
        thenResultIsValid(expected, residuum);
}

#define givenSystemAndB(A, b) struct matrix *(A) = &matrix_struct(\
                        .elements=(element_t[]){\
                        1., 0., 0.,\
                        2., 3., 0.,\
                        -3., 1., 4.\
                        }, .rows = 3, .cols=3);\
                struct matrix *(b) = &matrix_struct(\
                        .elements=(element_t[]){\
                        1.,\
                        2.,\
                        4.\
                        }, .rows = 3, .cols = 1);

#undef expectedResult
#define expectedResult(expected) struct matrix * (expected) = &matrix_struct(\
                .elements=(element_t[]){\
                        1.,\
                        0.,\
                        1.75\
                }, .rows=3, .cols=1)

#define thenResultIsSolution(expected, actual) do {\
                one_is_another_deep_copy(expected, actual);\
        } while (0)

void test_givenLeftTriangularMatrixAndBVector_whenSolvingWithForwardSubstitution_thenResultIsVector(void) {
        givenSystemAndB(A, b);

        struct matrix *result = lin_eq_sys__forward_substitution(A, b);
        print_matrix(result);
        expectedResult(expected);
        thenResultIsSolution(expected, result);
}