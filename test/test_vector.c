#include <matrix.h>
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


#undef givenVector
#define givenVector(vec) struct vector * (vec) = &(struct vector) {\
                .elements=(element_t[]){\
                        4, 9, 16\
                },\
                .len = 3\
        }

void test_vectorNorm(void) {
        givenVector(vec);
        struct matrix hua;
        element_t norm = vector__norm(vec);
        TEST_ASSERT_EQUAL_DOUBLE(18.788294228055936, norm);
}