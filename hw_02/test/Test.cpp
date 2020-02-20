#include "Test.h"
#include <iostream>

static int failedNum;
static int totalNum;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    totalNum++;
    failedNum += !expr;
    if (!expr)
        std::cout << "test failed: " << func << " in " << filename << ":" << lineNum << '\n';
}

void Test::showFinalResult() {
    if (!failedNum)
        std::cout << "All tests passed." << '\n';
    else
        std::cout << "Failed " << failedNum << " of " << totalNum << " tests." << '\n';
}