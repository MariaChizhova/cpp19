#include <form.h>
#include <StdioBoardView.h>
#include "Board.h"

const int FIVE = 5;

Board::Board() : row(FIELD_SIZE), col(FIELD_SIZE) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            field[i][j] = NONE_SIGN;
        }
    }
}

bool Board::canMove(int x, int y, sign player) const {
    (void) player;
    if (x < 0 || x >= row || y < 0 || y >= col)
        return false;
    if (getState() != CONTINUE)
        return false;
    if (field[x][y] != NONE_SIGN)
        return false;
    return true;
}

void Board::move(int x, int y, sign player) {
    if (canMove(x, y, player))
        field[x][y] = player;
}

game_state Board::getState() const {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ((i + FIVE <= row && check(i, j, 1, 0)) ||                 /**5 in row **/
                (j + FIVE <= col && check(i, j, 0, 1)) ||                 /**5 in column**/
                (i + FIVE <= row && j + FIVE <= col && check(i, j, 1, 1)) || /**5 in main diagonal**/
                (i - FIVE + 1 >= 0 && j + FIVE <= col && check(i, j, -1, 1)))  /**5 in secondary diagonal**/
                return field[i][j] == O_SIGN ? O_WINS : X_WINS;
        }
    }

    bool exists_move = false;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            exists_move |= field[i][col] == NONE_SIGN;
    if (!exists_move)
        return DRAW;

    return CONTINUE;
}

/** 5 equal signs stand together **/

bool Board::check(int x, int y, int dr, int dc) const {
    if (field[x][y] == NONE_SIGN)
        return false;
    bool wins = true;
    for (int i = 1; i < 5 && wins; i++)
        wins &= field[x][y] == field[x + i * dr][y + i * dc];
    return wins;
}

char Board::getCell(int row, int col) const {
    return field[row][col];
}
