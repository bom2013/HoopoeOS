#include "Unity/unity_helper.h"
#include "libc/stdio.h"

DEFAULT_FUNCTIONS();

#define TEST_BUFFER_SIZE 128
char test_buffer[TEST_BUFFER_SIZE] = {'\0'};

void test_sprintf()
{
    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    int len = sprintf(test_buffer, "Hello, %s!", "World");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, World!", test_buffer, "Expected output for 'Hello, %s!', 'World!'");
    TEST_ASSERT_EQUAL_MESSAGE(13, len, "Expected length for 'Hello, %s!'");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    len = sprintf(test_buffer, "Value: %d", 42);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Value: 42", test_buffer, "Expected output for 'Value: %d', 42");
    TEST_ASSERT_EQUAL_MESSAGE(9, len, "Expected length for 'Value: %d', 42");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    len = sprintf(test_buffer, "Value: %c", 'T');
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Value: T", test_buffer, "Expected output for 'Value: %c', 'T'");
    TEST_ASSERT_EQUAL_MESSAGE(8, len, "Expected length for 'Value: %c', 'T'");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    len = sprintf(test_buffer, "Value: 0x%x", 42);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Value: 0x2a", test_buffer, "Expected output for 'Value: 0x%x', 42");
    TEST_ASSERT_EQUAL_MESSAGE(11, len, "Expected length for 'Value: 0x%x', 42");

    reset_buffer(test_buffer, TEST_BUFFER_SIZE, "");
    len = sprintf(test_buffer, "Int: %d, Hex: 0x%x, Char: %c", 42, 42, 42);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Int: 42, Hex: 0x2a, Char: *", test_buffer, "Expected output for 'Int: %d, Hex: 0x%x, Char: %c', 42, 42, 42");
    TEST_ASSERT_EQUAL_MESSAGE(27, len, "Expected length for 'Int: %d, Hex: 0x%x, Char: %c', 42, 42, 42");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sprintf);

    return UNITY_END();
}