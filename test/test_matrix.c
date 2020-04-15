#include "unity.h"
#include "matrix.h"
#include "matrix_internals.h"

#undef givenShapesOfTwoMatrices
#define givenShapesOfTwoMatrices(shape_a, shape_b)\
struct mat2d_shape (shape_a) = {.rows = 3, .cols = 5};\
struct mat2d_shape (shape_b) = {.rows = 5, .cols = 3};

#undef expectedResult
#define expectedResult {\
{0, 0},\
{0, 1},\
{0, 2},\
{1, 0},\
{1, 1},\
{1, 2},\
{2, 0},\
{2, 1},\
{2, 2}}

#undef thenOrderIs
#define thenOrderIs(expected, actual) do {\
        char message[256];\
        size_t orders = sizeof(expected) / sizeof(*expected);\
        for (int i = 0; i < orders; ++i) {\
                sprintf(message,  "row_a: %lu != %lu in %d row\n", expected[i].row_a, actual[i].row_b, i);\
                TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].row_a, actual[i].row_a, message);\
                sprintf(message,  "row_b: %lu != %lu in %d row\n", expected[i].row_b, actual[i].row_b, i);\
                TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].row_b, actual[i].row_b, message);\
        }\
} while(0)

void test_givenShapeOfTwoMatrices_whenGeneratingOrderOfRowMultiplication_thenOrderIs(void) {
        givenShapesOfTwoMatrices(shapeA, shapeB);

        struct matrix_multiplication_order *actual_order = matrix__order_for_multiplication_with_2nd_transformed(
                shapeA.rows, shapeB.cols);

        struct matrix_multiplication_order expected[] = expectedResult;
        thenOrderIs(expected, actual_order);
}

#undef givenMatrix
#define givenMatrix(mat)\
struct matrix * (mat);\
do {\
        struct matrix_ctor_params params = matrix_ctor_params(.elements=(element_t[]){\
                                                                      1, 2, 3, 4, 5,\
                                                                      2, 3, 4, 5, 6,\
                                                                      3, 4, 5, 6, 7\
                                                              }, .shape = { .rows = 3, .cols=5 }, .length = 15);\
        (mat) = MATRIX__new(&params);\
        TEST_ASSERT_NOT_NULL(mat);\
} while (0)

#undef expectedResult
#define expectedResult \
{\
        1,2,3,\
        2,3,4,\
        3,4,5,\
        4,5,6,\
        5,6,7\
}

#undef thenTransposedIs
#define thenTransposedIs(expected, actual)\
do {\
        size_t num = sizeof(expected)/sizeof(*(expected));\
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num);\
} while(0)

        //TODO figure out why it fails
void test_givenMatrix_whenTransposing_thenResultMatrixIsValid(void) {
        givenMatrix(matA);
        
        struct matrix * result = MATRIX__transpose(matA);
        
        element_t expected[] = expectedResult;
        thenTransposedIs(expected, result->elements);
}


#undef givenTwoMatrices
#define givenTwoMatrices(mat_a, mat_b)\
struct matrix * (mat_a);\
struct matrix * (mat_b);\
do {\
        struct matrix_ctor_params params_a = matrix_ctor_params(.elements = (element_t[]){\
                                                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },\
                                                                .shape = { .rows = 3, .cols=4 }, .length = 12);\
        mat_a = MATRIX__new(&params_a);\
        struct matrix_ctor_params params_b = matrix_ctor_params(.elements = (element_t[]){\
                                                                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },\
                                                                .shape = { .rows = 3, .cols=4 }, .length = 12);\
        mat_b = MATRIX__new(&params_b);\
        TEST_ASSERT_NOT_NULL(mat_a);\
        TEST_ASSERT_NOT_NULL(mat_b);\
} while (0);


void test_givenTwoMatrices_whenMultiplyingThem_thenResultMatrixIsValid(void) {
        givenTwoMatrices(matA, matB);

//	struct matrix * actual_result = MATRIX__
}

