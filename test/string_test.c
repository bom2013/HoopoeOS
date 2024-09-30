#include "Unity/unity_helper.h"
#include "libc/string.h"

DEFAULT_FUNCTIONS();

#define TEST_BUFFER_SIZE 128
char test_buffer[TEST_BUFFER_SIZE];

void test_strlen()
{
    TEST_ASSERT_EQUAL_MESSAGE(0, strlen(""), "Empty string");
    TEST_ASSERT_EQUAL_MESSAGE(11, strlen("Test string"), "Normal string");
    TEST_ASSERT_EQUAL_MESSAGE(9, strlen("Test1@ \t,"), "Special characters string");
}

void test_strrev()
{
    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "Test");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("tseT", strrev(test_buffer), "Normal string");
    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", strrev(test_buffer), "Empty string");
    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "A");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("A", strrev(test_buffer), "One character");
}

void test_strcat()
{
    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "Hello");
    char *result = strcat(test_buffer, ", World!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, World!", test_buffer, "Buffer should contain the concatenated result");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(&test_buffer, result, "strcat should return destination ptr");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "Hello");
    result = strcat(test_buffer, "");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello", test_buffer, "Buffer should be unchanged when adding empty string");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(&test_buffer, result, "strcat should return destination ptr");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    result = strcat(test_buffer, "");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", test_buffer, "Adding empty string to empty string");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(&test_buffer, result, "strcat should return destination ptr");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "This");
    strcat(test_buffer, " is");
    strcat(test_buffer, " a");
    strcat(test_buffer, " great");
    strcat(test_buffer, " test");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("This is a great test", test_buffer, "Adding empty string to empty string");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(&test_buffer, result, "strcat should return destination ptr");
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
    RUN_TEST(test_strcat);
    RUN_TEST(test_memcpy);

    return UNITY_END();
}