#include "unity.h"
#include "matrix.h"
#include "helper.h"
#include <stdbool.h>
#include "vector.h"

void one_is_another_deep_copy(struct matrix *one, struct matrix *another) {
        TEST_ASSERT_EQUAL(one->rows, another->rows);
        TEST_ASSERT_EQUAL(one->cols, another->cols);

        len_t len = matrix__len(one);
        len = matrix__len(another) > len ? matrix__len(another) : len;
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(one->elements, another->elements, len);
        TEST_ASSERT_NOT_EQUAL(one->elements, another->elements);
}

bool one_is_another_shallow_copy(struct matrix *one, struct matrix *another) {
        TEST_ASSERT_EQUAL(one->rows, another->rows);
        TEST_ASSERT_EQUAL(one->cols, another->cols);
        TEST_ASSERT_EQUAL_PTR(one->elements, another->elements);
}

#define print_matrix(mat) \
do {\
        char message[128];\
        for (int i = 0; i < (mat)->rows; ++i) {\
                for (int j = 0; j < (mat)->cols; ++j) {\
                        sprintf(message, "e[%dx%d] = %.3f", i, j, (mat)->elements[i * (mat)->cols + j]);\
                        TEST_MESSAGE(message);\
                }\
        }\
} while (0)


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
                TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected->elements, actual->elements, num);\
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

/*
#undef givenTwoMatricesForMultiplication
#define givenTwoMatricesForMultiplication(mat_a, mat_b)\
struct matrix * (mat_a);\
struct matrix * (mat_b);\
do {\
        struct matrix_ctor_params params_a = {\
                .elements = (element_t[]) {\
                        1, 2, 3,\
                        4, 5, 6},\
                .shape = {.rows = 2, .cols=3},\
                .length = 6};\
        struct matrix_ctor_params params_b = {\
                .elements = (element_t[]) {\
                        1, 2, 3, 4,\
                        5, 6, 7, 8,\
                        9, 10, 11, 12},\
                .shape = {.rows = 3, .cols=4},\
                .length = 12};\
        (mat_a) = matrix__new(&params_a);\
        (mat_b) = matrix__new(&params_b);\
        TEST_ASSERT_NOT_NULL(mat_a);\
        TEST_ASSERT_NOT_NULL(mat_b);\
} while (0)

#undef thenResultMatrixIs
#define thenResultMatrixIs(expected, actual) do {\
        size_t num = expected->shape.cols * expected->shape.rows;\
        TEST_ASSERT_EQUAL_FLOAT_ARRAY((expected)->elements, (actual)->elements, num);\
} while(0)

#undef expectedResult
#define expectedResult(expected) \
struct matrix * (expected);\
do {\
        struct matrix_ctor_params params = {\
                .elements = (element_t[])\
                        {38, 44, 50, 56,\
                         83, 98, 113, 128},\
                         .shape = {.rows = 2, .cols = 4}, .length = 8};\
        (expected) = matrix__new(&params);\
        TEST_ASSERT_NOT_NULL(expected);\
} while(0)


void test_givenTwoMatrices_whenMultiplyingThem_thenResultMatrixIsValid(void) {
        givenTwoMatricesForMultiplication(matA, matB);

        struct matrix *result = matrix__multiply(matA, matB);

        expectedResult(expected);
        thenResultMatrixIs(expected, result);
}*/

#undef thenResultBandMatrixIs
#define thenResultBandMatrixIs(expected, actual) do {\
        len_t num = sizeof(expected)/sizeof(*expected);\
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num);\
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

        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);
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

        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);

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
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);
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
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected.elements, result->elements, expected.rows * expected.cols);
}


void test_generatingOnes(void) {
        len_t len = 5;
        struct matrix *result = matrix__ones(len);

        TEST_ASSERT_EACH_EQUAL_FLOAT(1., result->elements, len);
        TEST_ASSERT_EQUAL(1, result->cols);
        TEST_ASSERT_EQUAL(len, result->rows);
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
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected->elements, mat->elements, expected->rows * expected->cols);

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

        matrix_multiply_by_scalar(mat, 2);

        struct matrix *expected = expectedResult;
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected->elements, mat->elements,
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
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected->elements, diagonal->elements, expected->rows * expected->cols);
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
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(src_to_test->elements, src->elements, matrix__len(src));
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
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(src->elements, dst->elements, matrix__len(src));

        // not equal pointers
        TEST_ASSERT_NOT_EQUAL(src->elements, dst->elements);
}