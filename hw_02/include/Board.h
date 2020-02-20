#ifndef BOARD_H
#define BOARD_H

#include "Board.h"

enum game_state {
    CONTINUE, DRAW, X_WINS, O_WINS
};

enum sign {
    NONE_SIGN = '.', X_SIGN = 'X', O_SIGN = 'O'
};


class Board {
public:
    static constexpr int FIELD_SIZE = 10;

    Board();

    bool canMove(int x, int y, sign player) const;

    void move(int x, int y, sign player);

    game_state getState() const;

    bool check(int x, int y, int dr, int dc) const;

    char getCell(int row, int col) const;

    ~Board() = default;

private:
    int row;
    int col;
    sign field[FIELD_SIZE][FIELD_SIZE];

};

#endif
