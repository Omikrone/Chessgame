#include <iostream>

#include <vector>
#include <iostream>

#include "board.hpp"

int main() {
    GameBoard *board = new GameBoard();
    board->initBoard();
    board->printBoard();
    std::vector<Position> moves = board->getLegalMoves({0, 1});

    std::cout << "RAW POSSIBLE MOVES : ";
    for (Position p: moves) {
        p.print();
        std::cout << ", ";
    }

    return 0;
}