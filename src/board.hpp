#pragma once

#include <iostream>

#include "pieces/piece.hpp"
#include "pieces/type.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"
#include "pieces/bishop.hpp"
#include "pieces/knight.hpp"
#include "pieces/king.hpp"
#include "pieces/queen.hpp"


class GameBoard {
public:
    GameBoard() {
        for (int8_t j = 0; j < BOARD_LENGTH; j++)
        {
            for (int8_t i = 0; i < BOARD_LENGTH; i++)
            {
                _board[j][i] = nullptr;
            }
        }   
    }

    Piece *_board[BOARD_LENGTH][BOARD_LENGTH];

    void initBoard() {
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[1][i] = new Pawn(Type::PAWN, {1, i}, Color::BLACK);
        }
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[6][i] = new Pawn(Type::PAWN, {1, i}, Color::WHITE);
        }

        const Position knightPositions[] = {{7, 1}, {7, 6}, {0, 6}, {0, 1}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {knightPositions[i].x, knightPositions[i].y};
            if (i < 2) {
                _board[startPosition.x][startPosition.y] = new Knight(Type::KNIGHT, startPosition, Color::WHITE);
            }
            else {
                _board[startPosition.x][startPosition.y] = new Knight(Type::KNIGHT, startPosition, Color::BLACK);
            }
        }

        const Position bishopPositions[] = {{7, 2}, {7, 5}, {0, 5}, {0, 2}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {bishopPositions[i].x, bishopPositions[i].y};
            if (i < 2) {
                _board[startPosition.x][startPosition.y] = new Bishop(Type::BISHOP, startPosition, Color::WHITE);
            }
            else {
                _board[startPosition.x][startPosition.y] = new Bishop(Type::BISHOP, startPosition, Color::BLACK);
            }
        }

        const Position rookPositions[] = {{7, 0}, {7, 7}, {0, 7}, {0, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {rookPositions[i].x, rookPositions[i].y};
            if (i < 2) {
                _board[startPosition.x][startPosition.y] = new Rook(Type::ROOK, startPosition, Color::WHITE);
            }
            else {
                _board[startPosition.x][startPosition.y] = new Rook(Type::ROOK, startPosition, Color::BLACK);
            }
        }
        
        _board[0][3] = new Queen(Type::QUEEN, {0, 3}, Color::BLACK);
        _board[7][3] = new Queen(Type::QUEEN, {7, 3}, Color::WHITE);

        _board[0][4] = new King(Type::KING, {0, 4}, Color::BLACK);
        _board[7][4] = new King(Type::KING, {7, 4}, Color::WHITE);
    }


    void printBoard() {
        for (int8_t j = 0; j < BOARD_LENGTH; j++)
        {
            for (int8_t i = 0; i < BOARD_LENGTH; i++)
            {
                if (_board[j][i] != nullptr) {
                    std::cout << " " << _board[j][i]->symbol() << " ";
                }
                else {
                    std::cout << "   ";
                }
            }
            std::cout << std::endl;
            
        }
    }
};