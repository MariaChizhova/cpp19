#include "BoardTest.h"
#include "Board.h"

BoardTest::BoardTest() {}

void BoardTest::testIsWin() {
    Board b;
    b.move(0, 0, O_SIGN);
    b.move(0, 1, O_SIGN);
    b.move(1, 0, O_SIGN);
    b.move(4, 5, X_SIGN);
    b.move(5, 5, X_SIGN);
    DO_CHECK(b.getState() == CONTINUE);
}

void BoardTest::testRDiag() {
    Board b;
    b.move(9, 0, O_SIGN);
    b.move(8, 1, O_SIGN);
    b.move(7, 2, O_SIGN);
    b.move(6, 3, O_SIGN);
    b.move(5, 4, O_SIGN);
    DO_CHECK(b.getState() == O_WINS);
}

void BoardTest::testLDiag() {
    Board b;
    b.move(0, 0, O_SIGN);
    b.move(1, 1, O_SIGN);
    b.move(2, 2, O_SIGN);
    b.move(3, 3, O_SIGN);
    b.move(4, 4, O_SIGN);
    DO_CHECK(b.getState() == O_WINS);
}

void BoardTest::testXWins() {
    Board b;
    b.move(0, 0, X_SIGN);
    b.move(0, 1, X_SIGN);
    b.move(0, 2, X_SIGN);
    b.move(0, 3, X_SIGN);
    b.move(0, 4, X_SIGN);
    DO_CHECK(b.getState() == X_WINS);
}

void BoardTest::testCanMove() {
    Board b;
    b.move(0, 0, O_SIGN);
    DO_CHECK(b.canMove(1, 1, X_SIGN));
}

void BoardTest::testCannotMove1() {
    Board b;
    b.move(4, 4, O_SIGN);
    DO_CHECK(!b.canMove(4, 4, X_SIGN));
}

void BoardTest::testCannotMove2() {
    Board b;
    b.move(0, 0, X_SIGN);
    b.move(0, 1, X_SIGN);
    b.move(0, 2, X_SIGN);
    b.move(0, 3, X_SIGN);
    b.move(0, 4, X_SIGN);
    DO_CHECK(!b.canMove(9, 9, O_SIGN));
}

void BoardTest::testCanMoveOutOfBounds() {
    Board b;
    DO_CHECK(!b.canMove(-1, -1, O_SIGN));
    DO_CHECK(!b.canMove(-1, 0, O_SIGN));
    DO_CHECK(!b.canMove(0, -1, O_SIGN));
    DO_CHECK(!b.canMove(0, 10, O_SIGN));
    DO_CHECK(!b.canMove(10, 0, O_SIGN));
    DO_CHECK(!b.canMove(4321, 1234, O_SIGN));
}

void BoardTest::testMove1() {
    Board b;
    b.move(0, 0, O_SIGN);
    DO_CHECK(b.getCell(0, 0) == O_SIGN);
}

void BoardTest::testMove2() {
    Board b;
    b.move(3, 3, X_SIGN);
    DO_CHECK(b.getCell(3, 3) == X_SIGN);
}

void BoardTest::testMove3() {
    Board b;
    b.move(1, 1, O_SIGN);
    DO_CHECK(b.getCell(0, 0) == NONE_SIGN);
}

void BoardTest::runAllTests() {
    testIsWin();
    testLDiag();
    testRDiag();
    testXWins();
    testCanMove();
    testCannotMove1();
    testCannotMove2();
    testCanMoveOutOfBounds();
    testMove1();
    testMove2();
    testMove3();
}