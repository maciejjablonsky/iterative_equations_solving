#include "unity.h"
#include "matrix.h"
#include "matrix_internals.h"

void givenValidMatrix(matrix_t **A) {
    element_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix_ctor_params_t params = matrix_ctor_params(.shape={ 3, 3 }, .length=sizeof(data)/sizeof(*data),
                                                     .elements=data);
    *A = MATRIX__new(&params);
}

void thenMatrixProperlyTransposed(matrix_t *A_transposed) {
    element_t transposed_data[] = {
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
    };
    shape_t trans_shape = {3, 3};
    TEST_ASSERT_EQUAL_MEMORY(transposed_data, A_transposed->elements,
                             (A_transposed->shape.rows * A_transposed->shape.cols) * sizeof(element_t));
    TEST_ASSERT_EQUAL_MEMORY(&trans_shape, &A_transposed->shape, sizeof(shape_t));
}

void test_givenMatrixToTranspose_thenMatrixTransposed(void) {
    // given
    matrix_t *A;
    givenValidMatrix(&A);
    //when
    matrix_t *A_transposed = MATRIX__transpose(A);
    // then
    thenMatrixProperlyTransposed(A_transposed);
}

void givenTwoValidMatrices(matrix_t **A, matrix_t **B) {
    element_t dataA[] = {
            1, 2, 3,
            4, 5, 6
    };
    matrix_ctor_params_t paramsA = matrix_ctor_params(.elements=dataA, .length=6,
                                                      .shape={ 2, 3 });
    element_t dataB[] = {
            4, 5,
            6, 7,
            8, 9
    };
    matrix_ctor_params_t paramsB = matrix_ctor_params(.elements=dataB, .length=6,
                                                      .shape={ 3, 2 });
    *A = MATRIX__new(&paramsA);
    *B = MATRIX__new(&paramsB);
}

void givenTwoMatrices(matrix_t **A, matrix_t **B, element_t *A_elements, shape_t A_shape, element_t *B_elements,
                      shape_t
                      B_shape) {
    *A = MATRIX__new(&matrix_ctor_params(.elements=A_elements, .shape=A_shape,
                                         .length=(A_shape.rows * A_shape.cols)));
    *B = MATRIX__new(&matrix_ctor_params(.elements=B_elements, .shape=B_shape,
                                         .length=(B_shape.rows * A_shape.cols)));
}

void thenResultMatrixIs(matrix_t *expected, matrix_t *actual) {
    size_t elements_size = expected->shape.rows * expected->shape.cols * sizeof(element_t);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected->elements, actual->elements,
                                   elements_size, sizeof(element_t));
    // shape equal
    TEST_ASSERT_EQUAL_MEMORY(&expected->shape, &actual->shape, sizeof(shape_t));
}

void test_givenTwoMatrices_whenMultiply_thenResultMatrixIsValid(void) {
    // given
    matrix_t *A, *B;
    givenTwoMatrices(&A, &B,
                     (element_t[]) {
                             1, 2, 3,
                             4, 5, 6},
                     (shape_t) {.rows=2, .cols=3},
                     (element_t[]) {
                             4, 5,
                             6, 7,
                             8, 9},
                     (shape_t) {.rows=3, .cols=3});
    // when
    matrix_t *result = matrix__multiplication(A, B);
    // then
    thenResultMatrixIs(&(matrix_t) {
                               .elements=(element_t[])
                                       {40, 46,
                                        94, 109},
                               .shape={2, 2}
                       }, result);
}