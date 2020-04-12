#include "unity.h"
#include "matrix_internals.h"
#include "fff.h"

void test_givenCtorParamsShapeNotMatchingElementsLength__thenParamsArentValid(void) {
    matrix_ctor_params_t params = matrix_ctor_params(.shape={5,6}, .length=29, .elements=(void*)0x12345678);
    TEST_ASSERT_FALSE(MATRIX__are_params_valid(&params));
}

void test_givenCtorParamsWithAxisOfZeroLength_thenParamsArentValid(void) {
    matrix_ctor_params_t params = matrix_ctor_params(.shape={0,4});
    TEST_ASSERT_FALSE(MATRIX__are_params_valid(&params));

    params = matrix_ctor_params(.shape={5,0});
    TEST_ASSERT_FALSE(MATRIX__are_params_valid(&params));
}