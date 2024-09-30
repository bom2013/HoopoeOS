#include "Unity/unity_helper.h"
#include "libc/string.h"

void setUp()
{
}

void tearDown()
{
}

void test_strlen()
{
    TEST_ASSERT_EQUAL_MESSAGE(0, strlen(""), "Empty string");
    TEST_ASSERT_EQUAL_MESSAGE(11, strlen("Test string"), "Normal string");
    TEST_ASSERT_EQUAL_MESSAGE(9, strlen("Test1@ \t,"), "Special characters string");
}

void test_strrev()
{
    char normal_string[128] = "Test";
    TEST_ASSERT_EQUAL_STRING_MESSAGE("tseT", strrev(normal_string), "Normal string");
    char empty_string[128] = "";
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", strrev(empty_string), "Empty string");
    char one_char_string[128] = "A";
    TEST_ASSERT_EQUAL_STRING_MESSAGE("A", strrev(one_char_string), "One character");
}

void test_memcpy()
{
    char first_buffer[128] = {0};
    char second_buffer[] = "Test string";
    void *result = memcpy(first_buffer, second_buffer, 4);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Test", first_buffer, "Copy size");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(&first_buffer, result, "Memcpy should return the destination address");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_strlen);
    RUN_TEST(test_strrev);
    RUN_TEST(test_memcpy);

    return UNITY_END();
}