#ifndef UNITY_TEST_H_
#define UNITY_TEST_H_

void reset_buffer(char *buffer, int buffer_size, char *initial_string);

#define DEFAULT_FUNCTIONS() \
    void setUp() {}         \
    void tearDown() {}

#define UNITY_OUTPUT_COLOR

#include "unity.h"

#endif // UNITY_TEST_H_