#include "unity.h"
#include "matrix.h"
#include "helper.h"
#include <stdbool.h>
#include "vector.h"
#include "matrix_test_helper.h"

#undef givenMatrix
#define givenMatrix(mat) struct matrix * (mat) = &(struct matrix){\
                .elements = (element_t[]){\
                        1, 2, 3, 4,\
                        5, 6, 7, 8,\
                        9, 10, 11, 12\
                }, .rows = 3, .cols = 4\
        }

#undef expectedResult
#define expectedResult(expected) struct matrix * (expected) = &(struct matrix){\
                .elements = (element_t[]){\
                        1, 5, 9,\
                        2, 6, 10, \
                        3, 7, 11,\
                        4, 8, 12\
                }, .rows= 4, .cols = 3\
        }

#undef thenTransposedIsValid
#define thenTransposedIsValid(expected, actual) do {\
                len_t num = matrix__len(expected);\
                TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected->elements, actual->elements, num);\
                TEST_ASSERT_EQUAL(expected->rows, actual->rows);\
                TEST_ASSERT_EQUAL(expected->cols, actual->cols);\
        } while(0)

void test_givenMatrix_whenTransposing_thenResultMatrixIsValid(void) {
        givenMatrix(matA);

        struct matrix *result = matrix__transpose(matA);

        expectedResult(expected);
        thenTransposedIsValid(expected, result);
}

#undef givenMatrix
#define givenMatrix(mat) struct matrix * (mat) = &(struct matrix){\
                .elements = (element_t[]){\
                        1, 2, 3, 4,\
                        5, 6, 7, 8,\
                        9, 10, 11, 12\
                }, .rows = 3, .cols = 4\
        }

void test_givenSourceMatrix_whenTransposing_thenSourceIsUntouched(void) {
        givenMatrix(src);
        struct matrix *copy_src = matrix__copy(src);

        struct matrix *transposed = matrix__transpose(src);

        one_is_another_deep_copy(src, copy_src);
}


#undef givenLeftMatrixAndTransposedRightMatrix
#define givenLeftMatrixAndTransposedRightMatrix(left, right) struct matrix *(left) = &(struct matrix) {\
                .elements = (element_t[]) {\
                        1, 2, 3,\
                        4, 5, 6\
                }, .rows=2, .cols=3\
        };\
        struct matrix *(right) = &(struct matrix) {\
                .elements = (element_t[]) {\
                        1, 5, 9,\
                        2, 6, 10,\
                        3, 7, 11,\
                        4, 8, 12,\
                }, .rows = 4, .cols = 3\
        };

#undef expectedResult
#define expectedResult(expected) struct matrix * (expected) = &(struct matrix){\
                .elements=(element_t[]){\
                        38, 44, 50, 56,\
                        83, 98, 113, 128\
                }, .rows = 2, .cols = 4\
        }

#define thenResultMatrixIs(expected, actual) do {\
                one_is_another_deep_copy(expected, actual);\
        } while(0)


void test_givenTwoMatricesWhileSecondIsTransposed_whenScalarMultiplyingByRows_thenResultArrayIsValid(void) {
        givenLeftMatrixAndTransposedRightMatrix(left, right_transposed);

        struct matrix *result = matrix__multiply_one_by_second_transposed(left, right_transposed);
        expectedResult(expected);
        thenResultMatrixIs(expected, result);
}


#undef thenResultBandMatrixIs
#define thenResultBandMatrixIs(expected, actual) do {\
        len_t num = sizeof(expected)/sizeof(*expected);\
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num);\
} while(0)

#undef expectedResult
#define expectedResult \
{\
        1,2,3,0,0,\
        2,1,2,3,0,\
        3,2,1,2,3,\
        0,3,2,1,2,\
        0,0,3,2,1\
}

void test_bandMatrixPatternValidity(void) {
        struct matrix *actual = matrix__gen_band((element_t[]) {1, 2, 3}, 3, 5, 5);
        element_t expected[] = expectedResult;
        thenResultBandMatrixIs(expected, actual->elements);
}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix (mat) = {\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult (struct matrix) {\
                .elements = (element_t[]){\
                        1, 2, 3, 4,\
                        0, 2, 3, 4,\
                        0, 0, 3, 4,\
                        0, 0, 0, 4\
                },\
                .rows = 4, .cols = 4\
        }

void test_triuWithDiagonal(void) {
        givenMatrix(mat);

        struct matrix *result = matrix__triu(&mat, 0);

        struct matrix expected = expectedResult;

        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);
}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix (mat) = {\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult (struct matrix) {\
                .elements = (element_t[]){\
                        0, 2, 3, 4,\
                        0, 0, 3, 4,\
                        0, 0, 0, 4,\
                        0, 0, 0, 0\
                },\
                .rows = 4, .cols = 4\
        }

void test_triuRowAboveDiagonal(void) {
        givenMatrix(mat);

        struct matrix *result = matrix__triu(&mat, 1);

        struct matrix expected = expectedResult;

        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);

}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix (mat) = {\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult (struct matrix) {\
                .elements = (element_t[]){\
                        1, 0, 0, 0,\
                        1, 2, 0, 0,\
                        1, 2, 3, 0,\
                        1, 2, 3, 4\
                },\
                .rows = 4, .cols = 4\
        }

void test_trilWithDiagonal(void) {
        givenMatrix(mat);

        struct matrix *result = matrix__tril(&mat, 0);

        struct matrix expected = expectedResult;
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);
}


#undef givenMatrix
#define givenMatrix(mat) \
struct matrix (mat) = {\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult (struct matrix) {\
                .elements = (element_t[]){\
                        0, 0, 0, 0,\
                        1, 0, 0, 0,\
                        1, 2, 0, 0,\
                        1, 2, 3, 0\
                },\
                .rows = 4, .cols = 4\
        }

void test_trilWithOneRowBelowDiagonal(void) {
        givenMatrix(mat);

        struct matrix *result = matrix__tril(&mat, 1);

        struct matrix expected = expectedResult;
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);
}

#undef expectedResult
#define expectedResult(expected) struct matrix *(expected) = &matrix_struct(\
                .elements = (element_t[]){1,1,1,1,1}, \
                .rows = 5, .cols=1)

#define thenResultIsOnes(expected, actual) do {\
                one_is_another_deep_copy(expected, actual);\
        } while(0)

void test_generatingOnes(void) {
        len_t len = 5;
        struct matrix *result = matrix__ones(len);

        expectedResult(expected);
        thenResultIsOnes(expected, result);
}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix * (mat) = &(struct matrix){\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult &(struct matrix) {\
                .elements = (element_t[]){\
                        0, 2, 3, 4,\
                        1, 0, 3, 4,\
                        1, 2, 0, 4,\
                        1, 2, 3, 0\
                },\
                .rows = 4, .cols = 4\
        }

void test_givenMatrix_whenZeroOutDiagonal_thenResultIs(void) {
        givenMatrix(mat);

        matrix__zero_out_diagonal(mat);
        struct matrix *expected = expectedResult;
        one_is_another_deep_copy(expected, mat);
}


#undef givenMatrix
#define givenMatrix(mat) \
struct matrix * (mat) = &(struct matrix){\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult &(struct matrix) {\
                .elements = (element_t[]){\
                        2, 4, 6, 8,\
                        2, 4, 6, 8,\
                        2, 4, 6, 8,\
                        2, 4, 6, 8,\
                },\
                .rows = 4, .cols = 4\
        }

void test_givenMatrix_whenMultipliedBy2_thenResultIs(void) {
        givenMatrix(mat);

        matrix__multiply_by_scalar(mat, 2);

        struct matrix *expected = expectedResult;
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected->elements, mat->elements,
                                       expected->rows * expected->cols);
}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix * (mat) = &(struct matrix){\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

#undef expectedResult
#define expectedResult &(struct matrix) {\
                .elements = (element_t[]){\
                        1, 0, 0, 0,\
                        0, 2, 0, 0,\
                        0, 0, 3, 0,\
                        0, 0, 0, 4\
                },\
                .rows = 4, .cols = 4\
        }

void test_givenMatrix_thenDiagonalIs(void) {
        givenMatrix(mat);

        struct matrix *diagonal = matrix__diagonal(mat);

        struct matrix *expected = expectedResult;
        one_is_another_deep_copy(expected,diagonal);
}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix * (mat) = &(struct matrix){\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

void test_givenMatrixToCopy_whenDeepCopying_thenSourceMatrixIsUntouched(void) {
        givenMatrix(src);
        givenMatrix(src_to_test);
        void *elements_addr = src->elements;

        struct matrix *dst = matrix__copy(src);

        TEST_ASSERT_EQUAL(src_to_test->rows, src->rows);
        TEST_ASSERT_EQUAL(src_to_test->cols, src->cols);
        TEST_ASSERT_EQUAL_PTR(elements_addr, src->elements);
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(src_to_test->elements, src->elements, matrix__len(src));
}

#undef givenMatrix
#define givenMatrix(mat) \
struct matrix * (mat) = &(struct matrix){\
        .elements = (element_t[]){\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4,\
                1, 2, 3, 4\
        },\
        .rows = 4,\
        .cols = 4\
}

void test_givenMatrixToCopy_whenDeepCopying_thenDestinationIsValidCopy(void) {
        givenMatrix(src);

        struct matrix *dst = matrix__copy(src);

        TEST_ASSERT_EQUAL(src->rows, dst->rows);
        TEST_ASSERT_EQUAL(src->cols, dst->cols);
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(src->elements, dst->elements, matrix__len(src));

        // not equal pointers
        TEST_ASSERT_NOT_EQUAL(src->elements, dst->elements);
}

#undef givenTwoMatrices
#define givenTwoMatrices(mat_a, mat_b) \
                struct matrix *(mat_b) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                2, 2, 2,\
                                2, 2, 2,\
                        }, .rows = 2, .cols = 3\
                };\
                struct matrix *(mat_a) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                4, 3, 2,\
                                6, 5, 4\
                        }, .rows = 2, .cols = 3\
                };

#undef expectedResult
#define expectedResult(expected) struct matrix * (expected) = &(struct matrix){\
                .elements = (element_t[]){\
                        2, 1, 0,\
                        4, 3, 2\
                }, .rows = 2, .cols = 3\
        }

#undef thenResultIsStoredInFirstOne
#define thenResultIsStoredInFirstOne(expected, actual, src) do {\
                TEST_ASSERT_EQUAL_PTR(src, actual);\
                one_is_another_deep_copy(expected, actual);\
        } while(0)

void test_givenTwoMatrices_whenSubtracting_thenResultIsStoredInFirstOne(void) {
        givenTwoMatrices(matA, matB);

        struct matrix *result = matrix__sub(matA, matB);

        expectedResult(expected);
        thenResultIsStoredInFirstOne(expected, result, matA);
}

#undef givenTwoMatrices
#define givenTwoMatrices(mat_a, mat_b) \
                struct matrix *(mat_b) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                2, 2, 2,\
                                2, 2, 2,\
                        }, .rows = 2, .cols = 3\
                };\
                struct matrix *(mat_a) = &(struct matrix) {\
                        .elements = (element_t[]) {\
                                4, 3, 2,\
                                6, 5, 4\
                        }, .rows = 2, .cols = 3\
                };

#undef expectedResult
#define expectedResult(expected) struct matrix * (expected) = &(struct matrix){\
                .elements = (element_t[]){\
                        6, 5, 4,\
                        8, 7, 6\
                }, .rows = 2, .cols = 3\
        }


void test_givenTwoMatrices_whenAdding_thenResultIsStoredInFirstOne(void) {
        givenTwoMatrices(matA, matB);

        struct matrix *result = matrix__add(matA, matB);

        expectedResult(expected);
        thenResultIsStoredInFirstOne(expected, result, matA);
}