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
            _board[1][i] = new Pawn(Type::PAWN, {i, 1}, Color::WHITE);
        }
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[6][i] = new Pawn(Type::PAWN, {i, 1}, Color::BLACK);
        }

        const Position knightPositions[] = {{1, 7}, {6, 7}, {6, 0}, {1, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {knightPositions[i].file, knightPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Knight(Type::KNIGHT, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Knight(Type::KNIGHT, startPosition, Color::WHITE);
            }
        }

        const Position bishopPositions[] = {{2, 7}, {5, 7}, {5, 0}, {2, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {bishopPositions[i].file, bishopPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Bishop(Type::BISHOP, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Bishop(Type::BISHOP, startPosition, Color::WHITE);
            }
        }

        const Position rookPositions[] = {{0, 7}, {7, 7}, {7, 0}, {0, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {rookPositions[i].file, rookPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Rook(Type::ROOK, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Rook(Type::ROOK, startPosition, Color::WHITE);
            }
        }
        
        _board[0][3] = new Queen(Type::QUEEN, {3, 0}, Color::WHITE);
        _board[7][3] = new Queen(Type::QUEEN, {3, 7}, Color::BLACK);

        _board[0][4] = new King(Type::KING, {4, 0}, Color::WHITE);
        _board[7][4] = new King(Type::KING, {4, 7}, Color::BLACK);
    }


    std::vector<Position> getLegalMoves(Position piecePosition) {
        std::vector<Position> rawMoves = _board[piecePosition.rank][piecePosition.file]->getPossibleMoves();
        return rawMoves;
    }


    void printBoard() {
        for (int8_t j = BOARD_LENGTH - 1; j >= 0; j--)
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