#include <gtest/gtest.h>

#include "../source/MiniJavaScanner.h"

TEST(memleak_tests, memleak_tests) {
    int* unused_var = new int;
}
