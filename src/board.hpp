#pragma once

#include "pieces/piece.hpp"
#include "pieces/type.hpp"

#define BOARD_LENGTH 8


class GameBoard {
public:
    GameBoard();
    void printBoard();
private:
    Piece *_board[BOARD_LENGTH][BOARD_LENGTH];

    void initBoard() {
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            
        }
        
    }
};