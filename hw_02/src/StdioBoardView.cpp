#include "StdioBoardView.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sstream>


StdioBoardView::StdioBoardView(Board &board, bool silent = false) : _board(board), _silent(silent) {
}

void StdioBoardView::showBoard() {
    for (int i = 0; i < _board.FIELD_SIZE; i++) {
        for (int j = 0; j < _board.FIELD_SIZE; j++)
            std::cout << _board.getCell(i, j);
        std::cout << '\n';
    }
}

void StdioBoardView::runGame() {
    sign sign = O_SIGN;
    std::cout << '\n';
    while (_board.getState() == CONTINUE) {
        if (!_silent)
            showBoard();
        int r, c;
        while (true) {
            std::string s;
            std::cout << (char)sign << " " << "move:" << " ";
            getline(std::cin, s);
            char tmp;
            int read = sscanf(s.c_str(), "%d%d%s", &r, &c, &tmp);
            if (read == 2 && (_board.canMove(r, c, sign) || (r == -1 && c == -1)))
                break;
            std::cout << "Bad move!" << '\n';
        }
        if (r == -1 && c == -1)
            exit(0);
        _board.move(r, c, sign);
        sign = (sign == O_SIGN ? X_SIGN : O_SIGN);
        std::cout << '\n';
    }
    game_state status = _board.getState();
    if (status == CONTINUE)
        return;
    showBoard();
    if (status == DRAW)
        printf("Draw.\n");
    if (status == O_WINS)
        printf("O wins!\n");
    if (status == X_WINS)
        printf("X wins!\n");
}



