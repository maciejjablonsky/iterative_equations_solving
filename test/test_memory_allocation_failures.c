#include "unity.h"
#include "matrix.h"
#include "matrix_internals.h"
#include "fff.h"

FAKE_VALUE_FUNC(void *, calloc, __u_long, __u_long);
FAKE_VALUE_FUNC(void*, malloc, size_t);

void test_givenElementsToCopy_whenMemoryFails_thenFalse(void) {

    // given
    matrix_t matrix;
    matrix_ctor_params_t params;

    // when
    calloc_fake.return_val = NULL;

    // then
    TEST_ASSERT_FALSE(MATRIX__copy_data(&matrix, &params));
}

void test_givenMatrixToCreate_whenMemoryFails_thenReturnNull(void) {
    // given
    matrix_ctor_params_t params;

    // when
    malloc_fake.return_val = NULL;

    // then
    TEST_ASSERT_NULL(MATRIX__new(&params));
}