#include <iostream>

#include <vector>
#include <iostream>

#include "board.hpp"

int main() {
    GameBoard *board = new GameBoard();
    board->initBoard();

    std::string input;
    Position initPos, destPos;

    while (true) {
        board->printBoard();

        std::cout << "Enter the coordinates of the piece you want to play (col,row) : ";
        std::cin >> input;
        initPos = {static_cast<signed char>(input.at(0) - '0'), static_cast<signed char>(input[2] - '0')};
        std::vector<Position> moves = board->getLegalMoves(initPos);
        std::vector<Position> legalMoves = board->filterCheckMoves(&initPos, moves);

        std::cout << "Enter the destination of the piece (col,row) : ";
        std::cin >> input;
        destPos = {static_cast<signed char>(input.at(0) - '0'), static_cast<signed char>(input[2] - '0')};

        if(std::find(legalMoves.begin(), legalMoves.end(), destPos) != legalMoves.end()) {
            board->makeMove(initPos, destPos);
        } else {
            std::cout << "LEGAL MOVES : ";
            for (Position p: legalMoves) {
                p.print();
                std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}