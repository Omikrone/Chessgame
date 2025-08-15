#pragma once

#include <iostream>

#include "pieces/utils/type.hpp"
#include "pieces/utils/move.hpp"
#include "pieces/piece.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"
#include "pieces/bishop.hpp"
#include "pieces/knight.hpp"
#include "pieces/king.hpp"
#include "pieces/queen.hpp"


class GameBoard {
public:

    std::vector<std::vector<Piece*>> _board =
        std::vector<std::vector<Piece*>>(BOARD_LENGTH, std::vector<Piece*>(BOARD_LENGTH, nullptr));

    GameBoard();

    void initBoard();
    Piece getPieceAt(Square sq) const;
    Color getCurrentTurn() const;
    void makeMove(Move &move);

    Piece *findKing(std::vector<std::vector<Piece*>> &board, Color kingColor);

    void EnPassant(std::vector<std::vector<Piece*>> &board, Piece *pawn, Move move);

    void KingSideCastle(std::vector<std::vector<Piece*>> &board, Piece *king);

    void QueenSideCastle(std::vector<std::vector<Piece*>> &board, Piece *king);
    void printBoard(std::vector<std::vector<Piece*>> board);
};