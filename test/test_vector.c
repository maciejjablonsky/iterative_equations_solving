#include "unity.h"
#include "vector.h"
#include "matrix.h"
#include "matrix_internals.h"

void givenTwoSameLengthVectors(element_t **A, element_t **B, size_t *length) {
    static element_t _A[] = {1, 2, 3, 4, 5};
    static element_t _B[] = {5, 3, 2, 5, 4};
    *A = _A;
    *B = _B;
    *length = 5;
}

void test_givenTwoSameLengthVector_whenDotProduct_thenResultIsValidDotProduct(void) {
    // given
    element_t *A, *B;
    size_t length;
    givenTwoSameLengthVectors(&A, &B, &length);

    // when
    element_t dot_product = vector__dot_product(A, B, length);

    // then
    TEST_ASSERT_EQUAL(57, dot_product);
}

void givenTwoArraysOfVectors(element_t **A, element_t **B, size_t *number, size_t *vec_len) {
    static element_t _A[] = {
            1, 2, 3, 4, 5,
            2, 3, 4, 5, 6,
            3, 4, 5, 6, 7
    };
    static element_t _B[] = {
            9, 8, 7, 6, 5,
            8, 7, 6, 5, 4,
            7, 6, 5, 4, 3
    };
    *A = _A;
    *B = _B;
    *number = 3;
    *vec_len = 5;
}

void thenElementsAre(element_t *expected, element_t *actual, size_t num) {
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, sizeof(element_t), num);
}

void test_givenTwoArraysOfVectors_whenScalarMultiplyingEachPairOfVectorsInArrays_thenElementsAre(void) {
    // given
    element_t *A, *B;
    size_t number, vec_len;
    givenTwoArraysOfVectors(&A, &B, &number, &vec_len);
    // when
    element_t *array_of_dot_products = vectors__dot_products(A, B, number, vec_len);

    // then
    thenElementsAre((element_t[]) {95, 110, 115}, array_of_dot_products, 3);
}


void test_givenTwoMatricesAsArrays_whenScalarMultiplyingWithGivenOrder_thenElementsAre(void) {
    // given
    element_t A[] = {
            1, 2, 3, 4, 5,
            2, 3, 4, 5, 6,
            3, 4, 5, 6, 7
    };
    element_t B_transposed[] = {
            1, 2, 3, 4, 5,
            2, 3, 4, 5, 6,
            3, 4, 5, 6, 7
    };
    size_t A_rows = 3, A_cols = 5, B_cols = 3;
    order_t *order_of_multiplying = matrix__generate_row_multiplication_order(A_rows, B_cols);
    TEST_ASSERT_NOT_NULL(order_of_multiplying);

    // when
    // B will be transposed
    element_t *actual = vectors__dot_products_with_order(A, B_transposed, A_rows, A_cols,
                                                         order_of_multiplying, A_rows * B_cols);

    // then
    element_t expected[] = {
            55, 70, 85,
            70, 90, 110,
            85, 110, 135
    };
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, A_rows * B_cols);
}

void thenOrderIs(order_t *expected, order_t *actual, size_t num) {
    char message[1024];
    for (int i = 0; i < num; ++i) {
        sprintf(message ,"\'a\' doesn't match in %d row.", i);
        TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].a, actual[i].a, message);
        sprintf(message, "\'b\' doesn't match in %d row.", i);
        TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].b, actual[i].b, message);
    }
}

void test_givenShapeOfTwoMatrices_whenGeneratingOrderOfRowMultiplication_thenOrderIs(void) {
    // given
    shape_t A_shape = {.rows=3, .cols=5};
    shape_t B_shape = {.rows=5, .cols=3};
    // when
    order_t *order = matrix__generate_row_multiplication_order(A_shape.rows, B_shape.cols);
    // then
    thenOrderIs((order_t[]) {
            {0, 0},
            {0, 1},
            {0, 2},
            {1, 0},
            {1, 1},
            {1, 2},
            {2, 0},
            {2, 1},
            {2, 2}}, order, A_shape.rows * B_shape.cols);
}