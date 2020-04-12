#include "unity.h"
#include "matrix.h"
#include "mock_matrix_internals.h"

void test_givenValidParameters_thenCtorInitializesProperly(void) {
    // given
    MATRIX__are_params_valid_fake.return_val = true;
    MATRIX__copy_data_fake.return_val = true;
    matrix_t matrix;
    matrix_ctor_params_t params = matrix_ctor_params();
    // when
    bool ret = MATRIX__ctor(&matrix, &params);

    // then
    TEST_ASSERT_TRUE(ret);
}

void test_givenValidParameters_whenUsingNew_thenMatrixCreated(void) {
    // given
    matrix_ctor_params_t params;
    MATRIX__copy_data_fake.return_val = true;
    MATRIX__are_params_valid_fake.return_val = true;
    // when
    matrix_t *matrix = MATRIX__new(&params);

    // then
    TEST_ASSERT_NOT_NULL(matrix);
    TEST_ASSERT_CALLED(MATRIX__are_params_valid);
}

