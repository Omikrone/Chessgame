#include <iostream>

#include "board.hpp"

int main() {
    GameBoard *board = new GameBoard();
    board->initBoard();
    board->printBoard();
    return 0;
}