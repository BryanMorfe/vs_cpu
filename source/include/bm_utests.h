/**
 *          Created by: Bryan Morfe
 *          Created on: 11/20/2019
 */

#ifndef BM_UTESTS_H
#define BM_UTESTS_H

#if defined(__cplusplus)
extern "C"
{
#else
#include <stdbool.h>
#endif

/** Helper Functions **/
#define SS(str) #str
#define S(str)  SS(str)

#define FLOAT_PRECISION(f, p) (round((double)f * pow(10, p)) / pow(10, p))

#define TEST_BEGIN()                             \
    bool __pass                          = true; \
    bool __equal __attribute__((unused)) = true;

#define RUN_TEST(a, b) printf(__FILE__ ":" S(__LINE__) ":" S(a) ":%s\r\n", b ? "PASS" : "FAIL")

/**
 * General Asserts
 */
#define ASSERT(a)                                                              \
    if (!(a))                                                                  \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == false\n", S(a)); \
    }

#define ASSERT_EQUAL(a, b)                                                        \
    if (a != b)                                                                   \
    {                                                                             \
        __pass = false;                                                           \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %s\n", S(a), S(b)); \
    }

#define ASSERT_NOT_EQUAL(a, b)                                                    \
    if (a == b)                                                                   \
    {                                                                             \
        __pass = false;                                                           \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %s\n", S(a), S(b)); \
    }

/**
 * Integers
 */
#define ASSERT_EQUAL_INT(a, b)                                                 \
    if (a != b)                                                                \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %d\n", S(a), b); \
    }

#define ASSERT_NOT_EQUAL_INT(a, b)                                             \
    if (a == b)                                                                \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %d\n", S(a), b); \
    }

#define ASSERT_GREATER_THAN_INT(a, b)                                          \
    if (a <= b)                                                                \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s <= %d\n", S(a), b); \
    }

#define ASSERT_GREATER_THAN_OR_EQUAL_INT(a, b)                                \
    if (a < b)                                                                \
    {                                                                         \
        __pass = false;                                                       \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s < %d\n", S(a), b); \
    }

#define ASSERT_LESS_THAN_INT(a, b)                                             \
    if (a >= b)                                                                \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s >= %d\n", S(a), b); \
    }

#define ASSERT_LESS_THAN_OR_EQUAL_INT(a, b)                                   \
    if (a > b)                                                                \
    {                                                                         \
        __pass = false;                                                       \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s > %d\n", S(a), b); \
    }

#define ASSERT_EQUAL_UINT(a, b)                                                \
    if (a != b)                                                                \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %u\n", S(a), b); \
    }

#define ASSERT_NOT_EQUAL_UINT(a, b)                                            \
    if (a == b)                                                                \
    {                                                                          \
        __pass = false;                                                        \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %u\n", S(a), b); \
    }

#define ASSERT_EQUAL_INT8(a, b) ASSERT_EQUAL_INT(a, b)

#define ASSERT_NOT_EQUAL_INT8(a, b) ASSERT_NOT_EQUAL_INT(a, b)

#define ASSERT_EQUAL_UINT8(a, b) ASSERT_EQUAL_UINT(a, b)

#define ASSERT_NOT_EQUAL_UINT8(a, b) ASSERT_NOT_EQUAL_UINT(a, b)

#define ASSERT_EQUAL_INT16(a, b) ASSERT_EQUAL_INT(a, b)

#define ASSERT_NOT_EQUAL_INT16(a, b) ASSERT_NOT_EQUAL_INT(a, b)

#define ASSERT_EQUAL_UINT16(a, b) ASSERT_EQUAL_UINT(a, b)

#define ASSERT_NOT_EQUAL_UINT16(a, b) ASSERT_NOT_EQUAL_UINT(a, b)

#define ASSERT_EQUAL_INT32(a, b) ASSERT_EQUAL_INT(a, b)

#define ASSERT_NOT_EQUAL_INT32(a, b) ASSERT_NOT_EQUAL_INT(a, b)

#define ASSERT_EQUAL_UINT32(a, b) ASSERT_EQUAL_UINT(a, b)

#define ASSERT_NOT_EQUAL_UINT32(a, b) ASSERT_NOT_EQUAL_UINT(a, b)

#define ASSERT_EQUAL_INT64(a, b)                                                \
    if (a != b)                                                                 \
    {                                                                           \
        __pass = false;                                                         \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %ld\n", S(a), b); \
    }

#define ASSERT_NOT_EQUAL_INT64(a, b)                                            \
    if (a == b)                                                                 \
    {                                                                           \
        __pass = false;                                                         \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %ld\n", S(a), b); \
    }

#define ASSERT_EQUAL_UINT64(a, b)                                               \
    if (a != b)                                                                 \
    {                                                                           \
        __pass = false;                                                         \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %lu\n", S(a), b); \
    }

#define ASSERT_NOT_EQUAL_UINT64(a, b)                                           \
    if (a == b)                                                                 \
    {                                                                           \
        __pass = false;                                                         \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %lu\n", S(a), b); \
    }

#define ASSERT_EQUAL_LONG(a, b) ASSERT_EQUAL_INT64(a, b)

#define ASSERT_NOT_EQUAL_LONG(a, b) ASSERT_NOT_EQUAL_INT64(a, b)

#define ASSERT_EQUAL_ULONG(a, b) ASSERT_EQUAL_UINT64(a, b)

#define ASSERT_NOT_EQUAL_ULONG(a, b) ASSERT_NOT_EQUAL_UINT64(a, b)

#define ASSERT_EQUAL_LONG_LONG(a, b)                                             \
    if (a != b)                                                                  \
    {                                                                            \
        __pass = false;                                                          \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %lld\n", S(a), b); \
    }

#define ASSERT_NOT_EQUAL_LONG_LONG(a, b)                                         \
    if (a == b)                                                                  \
    {                                                                            \
        __pass = false;                                                          \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %lld\n", S(a), b); \
    }

#define ASSERT_EQUAL_ULONG_LONG(a, b)                                            \
    if (a != b)                                                                  \
    {                                                                            \
        __pass = false;                                                          \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %llu\n", S(a), b); \
    }

#define ASSERT_NOT_EQUAL_ULONG_LONG(a, b)                                        \
    if (a == b)                                                                  \
    {                                                                            \
        __pass = false;                                                          \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %llu\n", S(a), b); \
    }

/**
 * Floats
 */
#define ASSERT_EQUAL_FLOAT(a, b, p)                                                             \
    if (fabs(FLOAT_PRECISION(a, p) - FLOAT_PRECISION(b, p)) > 0.00000001)                       \
    {                                                                                           \
        __pass = false;                                                                         \
        printf(                                                                                 \
            __FILE__ ":" S(__LINE__) ":assert failed:%s != %f\n", S(a), FLOAT_PRECISION(b, p)); \
    }

#define ASSERT_NOT_EQUAL_FLOAT(a, b, p)                                                         \
    if (fabs(FLOAT_PRECISION(a, p) - FLOAT_PRECISION(b, p)) <= 0.00000001)                      \
    {                                                                                           \
        __pass = false;                                                                         \
        printf(                                                                                 \
            __FILE__ ":" S(__LINE__) ":assert failed:%s == %f\n", S(a), FLOAT_PRECISION(b, p)); \
    }

/**
 * Strings
 */
#define ASSERT_EQUAL_STRING(s1, s2)                                           \
    if (strcmp(s1, s2) != 0)                                                  \
    {                                                                         \
        __pass = false;                                                       \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %s\n", s1, s2); \
    }

#define ASSERT_NOT_EQUAL_STRING(s1, s2)                                       \
    if (strcmp(s1, s2) == 0)                                                  \
    {                                                                         \
        __pass = false;                                                       \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %s\n", s1, s2); \
    }

/**
 * Arrays
 */
#define ASSERT_EQUAL_INT_ARRAY(a, b, n)                                           \
    __equal = true;                                                               \
    for (size_t i = 0; i < n && __equal; ++i)                                     \
    {                                                                             \
        __equal = (a[i] == b[i]);                                                 \
    }                                                                             \
    if (!__equal)                                                                 \
    {                                                                             \
        __pass = false;                                                           \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %s\n", S(a), S(b)); \
    }

#define ASSERT_NOT_EQUAL_INT_ARRAY(a, b, n)                                       \
    __equal = false;                                                              \
    for (size_t i = 0; i < n && !__equal; ++i)                                    \
    {                                                                             \
        __equal = (a[i] == b[i]);                                                 \
    }                                                                             \
    if (__equal)                                                                  \
    {                                                                             \
        __pass = false;                                                           \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %s\n", S(a), S(b)); \
    }

#define ASSERT_EQUAL_FLOAT_ARRAY(a, b, n, p)                                                 \
    __equal = true;                                                                          \
    for (size_t i = 0; i < n && __equal; ++i)                                                \
    {                                                                                        \
        __equal = (fabs(FLOAT_PRECISION(a[i], p) - FLOAT_PRECISION(b[i], p)) <= 0.00000001); \
    }                                                                                        \
    if (!__equal)                                                                            \
    {                                                                                        \
        __pass = false;                                                                      \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s != %s\n", S(a), S(b));            \
    }

#define ASSERT_NOT_EQUAL_FLOAT_ARRAY(a, b, n)                                     \
    __equal = false;                                                              \
    for (size_t i = 0; i < n && !__equal; ++i)                                    \
    {                                                                             \
        __equal = (fabs(a[i] - b[i]) > 0.00000001);                               \
    }                                                                             \
    if (__equal)                                                                  \
    {                                                                             \
        __pass = false;                                                           \
        printf(__FILE__ ":" S(__LINE__) ":assert failed:%s == %s\n", S(a), S(b)); \
    }

#define TEST_END() __pass

#if defined(__cplusplus)
}
#endif

#endif /* BM_UTESTS_H */