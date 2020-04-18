#include "unity.h"
#include "vector.h"

#undef givenTwoVectorsOfSameLength
#define givenTwoVectorsOfSameLength(vecA, vecB, len) \
element_t (vecA)[] = {1,2,3,4,5};\
element_t (vecB)[] = {5,3,2,5,4};\
size_t (len) = 5;

#undef thenScalarProductIs
#define thenScalarProductIs(expected, actual) do {\
        TEST_ASSERT_EQUAL_DOUBLE(expected, actual);\
} while(0)

void test_givenTwoVectorsOfSameLength_whenDotProduct_thenResultIsValidDotProduct(void) {
	givenTwoVectorsOfSameLength(vecA, vecB, length);

	element_t dot_product = vector__dot_product(vecA, vecB, length);

	thenScalarProductIs(57, dot_product);
}

#undef givenTwoVectorsOfSameLength
#define givenTwoVectorsOfSameLength(vecA, vecB, len) \
element_t (vecA)[] = {54123,21245,3124,456542,52552};\
element_t (vecB)[] = {24325,33243,2435,55353,43452};\
size_t (len) = 5;

#undef thenScalarProductIs
#define thenScalarProductIs(expected, actual) do {\
        TEST_ASSERT_EQUAL_DOUBLE(expected, actual);\
} while(0)

void test_givenTwoVectorsOfSameLengthWithBigValues_whenDotProduct_thenResultIsValidDotProduct(void) {
        givenTwoVectorsOfSameLength(vecA, vecB, length);

        element_t dot_product = vector__dot_product(vecA, vecB, length);

        thenScalarProductIs(29584855280, dot_product);
}


#undef givenMatrixLikeArraysOfVectors
#define givenMatrixLikeArraysOfVectors(arrA, arrB, vectors_in_single_array, vec_len)\
element_t (arrA)[] = {  1, 2, 3, 4, 5,\
                        2, 3, 4, 5, 6,\
                        3, 4, 5, 6, 7};\
element_t (arrB)[] = {  9, 8, 7, 6, 5,\
                        8, 7, 6, 5, 4,\
                        7, 6, 5, 4, 3};\
size_t (vectors_in_single_array) = 3;\
size_t (vec_len) = 5;

#undef thenResultVectorIs
#define thenResultVectorIs(expected, actual) do {\
        size_t num = sizeof(expected) / sizeof(*(expected));\
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num);\
} while(0)

void test_givenTwoArraysOfVectors_whenScalarMultiplyingCorrespondingVectors_thenResultVectorIs(void) {
	givenMatrixLikeArraysOfVectors(arrA, arrB, vectors_in_single_array, vec_len);

	element_t *actual_result = vectors__dot_products(arrA, arrB, vectors_in_single_array, vec_len);

	element_t expected[] = {95, 110, 115};
	thenResultVectorIs(expected, actual_result);
}

#undef givenVector
#define givenVector(vec) struct vector * (vec) = &(struct vector) {\
                .elements=(element_t[]){\
                        4, 9, 16\
                },\
                .len = 3\
        }

void test_vectorNorm(void) {
        givenVector(vec);

        long double norm = vector__norm(vec);
        TEST_ASSERT_EQUAL_DOUBLE(18.788294228055936, norm);
}