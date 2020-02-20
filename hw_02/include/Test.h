#ifndef TEST_H
#define TEST_H

#include <cstddef>


class Test {
protected:

    static void check(bool expr, const char *func, const char *filename, size_t lineNum);

public:
    static void showFinalResult();

    virtual void runAllTests() = 0;
};

#endif