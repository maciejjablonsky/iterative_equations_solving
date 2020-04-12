#include "unity.h"
#include "matrix.h"
#include "matrix_internals.h"

void test_givenMatrixToTranspose_thenMatrixTransposed(void) {
    // given
    matrix_e_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix_ctor_params_t params = matrix_ctor_params(.shape={ 3, 3 }, .length=sizeof(data)/sizeof(*data),
    .elements=data);
    matrix_t *matrix = MATRIX__new(&params);


    //when
    matrix_t *transposed = MATRIX__transpose(matrix);

    // then
    matrix_e_t transposed_data[] = {
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
    };
    matrix_shape_t trans_shape = {3, 3};
    TEST_ASSERT_EQUAL_MEMORY(transposed_data, transposed->data, params.length * sizeof(matrix_e_t));
    TEST_ASSERT_EQUAL_MEMORY(&trans_shape, &transposed->shape, sizeof(matrix_shape_t));
}

void test_givenMatrices_whenMultiply_thenTransposedSecondAndMultipliedByRows(void){
    // given
    matrix_e_t dataA[] = {
            1, 2,3,
            4,5,6
    };
    matrix_ctor_params_t paramsA = matrix_ctor_params(.elements=dataA, .length=sizeof(dataA)/sizeof(*dataA),
            .shape={2, 3});

    matrix_e_t dataB[] = {
            4,5,
            6,7,
            8,9
    };
    matrix_ctor_params_t paramsB = matrix_ctor_params(.elements=dataB, .length=sizeof(dataB)/sizeof(*dataB),
            .shape={3,2});
    matrix_t * A = MATRIX__new(&paramsA);
    matrix_t * B = MATRIX__new(&paramsB);

    // when
    matrix_t * C = MATRIX__dot(A, B);

    // then
    matrix_e_t multiplied_data[] = {40, 45, 94, 89};
    TEST_ASSERT_EQUAL_MEMORY(multiplied_data, C->data, sizeof(multiplied_data) / sizeof(*multiplied_data));
}