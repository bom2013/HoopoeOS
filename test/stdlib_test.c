#include "Unity/unity_helper.h"
#include "libc/stdlib.h"

DEFAULT_FUNCTIONS()

void test_itoa()
{
    char buffer[20];
    TEST_ASSERT_EQUAL_STRING_MESSAGE("123", itoa(123, buffer, 10), "itoa should convert 123 to '123'");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("-123", itoa(-123, buffer, 10), "itoa should convert -123 to '-123'");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("0", itoa(0, buffer, 10), "itoa should convert 0 to '0'");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("7b", itoa(123, buffer, 16), "itoa should convert 123 to '7b' in base 16");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("1111011", itoa(123, buffer, 2), "itoa should convert 123 to '1111011' in base 2");
}

void test_atoi()
{
    TEST_ASSERT_EQUAL_MESSAGE(123, atoi("123"), "atoi should convert '123' to 123");
    TEST_ASSERT_EQUAL_MESSAGE(-123, atoi("-123"), "atoi should convert '-123' to -123");
    TEST_ASSERT_EQUAL_MESSAGE(0, atoi("0"), "atoi should convert '0' to 0");
    TEST_ASSERT_EQUAL_MESSAGE(123, atoi("   123"), "atoi should convert '   123' to 123");
    TEST_ASSERT_EQUAL_MESSAGE(-123, atoi("   -123"), "atoi should convert '   -123' to -123");
    TEST_ASSERT_EQUAL_MESSAGE(0, atoi("abc"), "atoi should return 0 for invalid input 'abc'");
    TEST_ASSERT_EQUAL_MESSAGE(123, atoi("123abc"), "atoi should parse '123abc' to 123");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_itoa);
    RUN_TEST(test_atoi);

    return UNITY_END();
}