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

        struct matrix * residuum = lin_eq_sys__residuum(A, x, b);
        expectedResult(expected);
        thenResultIsValid(expected, residuum);
}