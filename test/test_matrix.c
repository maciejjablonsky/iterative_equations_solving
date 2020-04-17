#include "unity.h"
#include "matrix.h"
#include "helper.h"

/*#undef givenMatrix
#define givenMatrix(mat)\
struct matrix * (mat);\
do {\
        struct matrix_ctor_params params = matrix_ctor_params(.elements=(element_t[]){\
                                                                      1, 2, 3, 4, 5,\
                                                                      6, 7, 8, 9, 10,\
                                                                      11, 12, 13, 14, 15\
                                                              }, .shape = { .rows = 3, .cols=5 }, .length = 15);\
        (mat) = matrix__new(&params);\
        TEST_ASSERT_NOT_NULL(mat);\
} while (0)

#undef expectedResult
#define expectedResult \
{\
        1, 6, 11,\
        2, 7, 12,\
        3, 8, 13,\
        4, 9, 14,\
        5, 10, 15\
}

#undef thenTransposedIs
#define thenTransposedIs(result) do {\
        element_t expected[] = expectedResult;\
        size_t num = sizeof(expected)/sizeof(*expected);\
        TEST_ASSERT_EQUAL_MEMORY(&((struct mat2d_shape){.rows = 5, .cols=3}), &result->shape, sizeof(struct mat2d_shape));\
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, result->elements, num);\
} while(0)

void test_givenMatrix_whenTransposing_thenResultMatrixIsValid(void) {
        givenMatrix(matA);

        struct matrix *result = matrix__transpose(matA);

        thenTransposedIs(result);
}


#undef givenTwoMatrixLikeArrays_SecondTransposed
#define givenTwoMatrixLikeArrays_SecondTransposed(mat_a, mat_b, rows_a, rows_b, row_len)\
element_t (mat_a)[] = {\
        1, 2, 3,\
        4, 5, 6\
};\
element_t (mat_b)[] = {\
        1, 5, 9,\
        2, 6, 10,\
        3, 7, 11,\
        4, 8, 12,\
};\
size_t (rows_a) = 2;\
size_t (rows_b) = 4;\
size_t (row_len) = 3;

#undef expectedResult
#define expectedResult \
{\
  38, 44, 50, 56,\
  83, 98, 113, 128\
};

#undef thenResultArrayIsValid
#define thenResultArrayIsValid(expected, actual) do {\
        size_t len = sizeof(expected)/sizeof(*(expected));\
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, len);\
} while (0)

void test_givenTwoMatrixLikeArray_whenScalarMultiplyingByRowsWithOrder_thenResultArrayIsValid(void) {
        givenTwoMatrixLikeArrays_SecondTransposed(matA, matB, rowsA, rowsB, row_len);

        element_t *result = matrix__multiply_rows(matA, matB, rowsA, rowsB, row_len);

        element_t expected[] = expectedResult;
        thenResultArrayIsValid(expected, result);
}


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

        struct matrix *result = matrix__multiplication(matA, matB);

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

        matrix_zero_out_diagonal(mat);
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

        struct matrix * diagonal = matrix__diagonal(mat);

        struct matrix * expected = expectedResult;
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected->elements, diagonal->elements, expected->rows * expected->cols);
}