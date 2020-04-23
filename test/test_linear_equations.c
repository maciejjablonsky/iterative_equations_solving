#include "unity.h"
#include "linear_equations.h"
#include "matrix.h"
#include "vector.h"
#include "matrix_test_helper.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
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
#define expectedResult &(struct matrix){\
                .elements=(element_t[]){\
                        0,\
                        0,\
                        0}, .rows = 3, .cols = 1\
        }

void test_givenSystemOfEquations_whenCountedResiduum_thenResultIsValid(void) {
        givenSystemOfEquations(A, x, b);

        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, residuum);
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
#define expectedResult &matrix_struct(\
                .elements=(element_t[]){\
                        1.,\
                        0.,\
                        1.75\
                }, .rows=3, .cols=1)

void test_givenLeftTriangularMatrixAndBVector_whenSolvingWithForwardSubstitution_thenResultIsVector(void) {
        givenSystemAndB(A, b);

        struct matrix *result = lin_eq_sys__forward_substitution(A, b);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, result);
}


#undef givenSystemAndB
#define givenSystemAndB(A, b) struct matrix *(A) = &matrix_struct(\
                        .elements=(element_t[]){\
                                1, 2, 3, 4,\
                                0, 5, 6, 7,\
                                0, 0, 8, 9,\
                                0, 0, 0, 10\
                        }, .rows = 4, .cols=4);\
                struct matrix *(b) = &matrix_struct(\
                        .elements=(element_t[]){\
                        1.,\
                        2.,\
                        3.,\
                        4\
                        }, .rows = 4, .cols = 1);

#undef expectedResult
#define expectedResult &matrix_struct(\
                .elements=(element_t[]){\
                        -0.235,\
                        -0.07,\
                        -0.075,\
                         0.4\
                }, .rows=4, .cols=1)

void test_givenUpperTriangularMatrixAndBVector_whenSolvingWithBackwardSubstitution_thenResultIsCorrectSolution(void) {
        givenSystemAndB(A, b);
        struct matrix *solution = lin_eq_sys__backward_substitution(A, b);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, solution);
}


#undef givenSystemOfLinearEquations
#define givenSystemOfLinearEquations(mat_a, mat_b) \
                struct matrix *(mat_a) = &(struct matrix) {\
                        .elements=(element_t[]) {\
                                 10, -1, -1,  0,  0,\
                                -1,  10, -1, -1,  0,\
                                -1,  -1, 10, -1, -1,\
                                 0,  -1, -1, 10, -1,\
                                 0,   0, -1, -1, 10\
                        }, .rows = 5, .cols = 5\
                };\
                struct matrix *(mat_b) = &(struct matrix) {\
                        .elements=(element_t[]){\
                                1,\
                                2,\
                                4,\
                                -2,\
                                -1\
                        }, .rows = 5, .cols = 1\
                }

#undef expectedResult
#define expectedResult &(struct matrix){\
                .elements = (element_t[]){\
                         1.664358663666262e-01,\
                         2.445473429115458e-01,\
                         4.198113207547168e-01,\
                        -1.407737580058854e-01,\
                        -7.209624372511686e-02\
                }, .rows = 5, .cols = 1\
        }


void test_givenSystemOfLinearEquations_whenSolvingWithJacobiMethod_thenResultIsCorrectSolution(void) {
        givenSystemOfLinearEquations(A, b);
        struct matrix *solution = lin_eq_sys__jacobi(A, b);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, solution);
}


void test_givenSystemOfLinearEquations_whenSolvingWithGaussSeidelMethod_thenResultIsCorrectSolution(void) {
        givenSystemOfLinearEquations(A, b);
        int iterations = 0;

        struct matrix *solution = lin_eq_sys__gauss_seidel(A, b, &iterations);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, solution);
}


void test_givenSystemOfLinearEquations_whenSolvingWithLUDecomposition_thenResultIsCorrectSolution(void) {
        givenSystemOfLinearEquations(A, b);
        struct matrix *solution = lin_eq_sys__solve_using_LU_decomposition(A, b);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, solution);
}


#undef givenSystemMatrix
#define givenSystemMatrix(mat_a) struct matrix *(mat_a) = &(struct matrix) {\
                .elements = (element_t[]) {\
                        3, 2, 1, 3,\
                        4, 1, 1, 2,\
                        2, 1, 4, 3,\
                        3, 2, 1, 4\
                }, .rows = 4, .cols = 4\
        }


#undef expectedResult
#define expectedResult &(struct matrix){\
                .elements=(element_t[]){\
                        1.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,\
                        1.333333333333333e+00,   1.000000000000000e+00,   0.000000000000000e+00,   0.000000000000000e+00,\
                        6.666666666666666e-01,   2.000000000000000e-01,   1.000000000000000e+00,   0.000000000000000e+00,\
                        1.000000000000000e+00,  -0.000000000000000e+00,   0.000000000000000e+00,   1.000000000000000e+00,\
                }, .rows = 4, .cols = 4\
        }

void test_givenSystemMatrix_whenLUDecompositionUsed_thenLIsValid(void) {
        givenSystemMatrix(A);
        struct matrix *U = matrix__deep_copy(A);
        struct matrix *L = matrix__eye(A->rows);

        lin_eq_sys__LU_decomposition(L, U);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, L);
}


#undef expectedResult
#define expectedResult &(struct matrix) {\
                .elements=(element_t[]) {\
                        3.000000000000000e+00,  2.000000000000000e+00,  1.000000000000000e+00,  3.000000000000000e+00,\
                        0.000000000000000e+00, -1.666666666666667e+00, -3.333333333333333e-01, -2.000000000000000e+00,\
                        0.000000000000000e+00,  0.000000000000000e+00,  3.400000000000000e+00,  1.400000000000000e+00,\
                        0.000000000000000e+00,  0.000000000000000e+00,  0.000000000000000e+00,  1.000000000000000e+00,\
                }, .rows = 4, .cols = 4\
        }

void test_givenSystemMatrix_whenLUDecompositionUsed_thenUIsValid(void) {
        givenSystemMatrix(A);
        struct matrix *U = matrix__deep_copy(A);
        struct matrix *L = matrix__eye(A->rows);

        lin_eq_sys__LU_decomposition(L, U);

        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(expectedResult, U);
}


#undef givenSystemMatrix
#define givenSystemMatrix(mat_a) struct matrix *(mat_a) = &(struct matrix) {\
                .elements = (element_t[]) {\
                        3, 2, 1, 3,\
                        4, 1, 1, 2,\
                        2, 1, 4, 3,\
                        3, 2, 1, 4\
                }, .rows = 4, .cols = 4\
        }

void test_givenSystemMatrix_whenLUDecompositionUsed_thenLTimesUEqualsSystemMatrix(void) {
        givenSystemMatrix(A);
        struct matrix *U = matrix__deep_copy(A);
        struct matrix *L = matrix__eye(A->rows);
        lin_eq_sys__LU_decomposition(L, U);

        struct matrix *result = matrix__mul(L, U);
        ASSERT_MATRIX_VALID_AND_AS_EXPECTED(A, result);
}

#pragma clang diagnostic pop