#ifndef STDIO_BOARD_VIEW_H
#define STDIO_BOARD_VIEW_H

#include "Board.h"

class StdioBoardView {
public:
    StdioBoardView(Board &board, bool silent);

    void runGame();

    void showBoard();

private:
    Board &_board;
    bool _silent;
};

#endif
