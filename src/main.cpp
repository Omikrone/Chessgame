#include <iostream>

#include <vector>
#include <iostream>

#include "board.hpp"

int main() {
    GameBoard *board = new GameBoard();
    board->initBoard();
    board->printBoard();
    std::vector<std::vector<Position>> moves = board->getLegalMoves({4, 0});

    std::cout << "RAW POSSIBLE MOVES : ";
    for (std::vector<Position> v: moves)
    {
        std::cout << "[ ";
        for (Position p: v) {
            p.print();
            std::cout << ", ";
        }
        std::cout << " ], ";
    }

    return 0;
}