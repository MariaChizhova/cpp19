#include <cstring>
#include "StdioBoardView.h"

int main(int argc, char **argv) {
    bool silent = false;
    if (argc > 1 && !strcmp(argv[1], "silent"))
        silent = true;
    Board board;
    StdioBoardView StdioBoardView(board, silent);
    StdioBoardView.runGame();
    return 0;
}