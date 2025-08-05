#pragma once

#include "pieces/piece.hpp"

#define BOARD_LENGTH 8


class GameBoard {
public:
    GameBoard();
    void printBoard();
private:
    Piece *_board[BOARD_LENGTH][BOARD_LENGTH];
};