#include <iostream>

#include <vector>
#include <iostream>

#include "board.hpp"

int main() {
    GameBoard *board = new GameBoard();
    board->initBoard();
    board->printBoard();
    std::vector<Position> moves = board->getLegalMoves({4, 0});
    for (Position p: moves)
    {
        p.print();
        std::cout << ", ";
    }

    return 0;
}