#ifndef BOARD_TEST_H
#define BOARD_TEST_H

#include "Test.h"

#define DO_CHECK(EXPR) BoardTest::check(EXPR, __FUNCTION__, __FILE__, __LINE__);

class BoardTest : public Test {
public:
    BoardTest();

    void testIsWin();

    void testLDiag();

    void testRDiag();

    void testXWins();

    void testCanMove();

    void testCannotMove1();

    void testCannotMove2();

    void testCanMoveOutOfBounds();

    void testMove1();

    void testMove2();

    void testMove3();

    void runAllTests();
};

#endif
