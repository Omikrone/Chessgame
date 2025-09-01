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
    King& _whiteKing;
    King& _blackKing;

    GameBoard();

    void initBoard();
    Piece *getPieceAt(Square sq) const;
    void makeMove(Move &move);
    King& getKing(Color kingColor);
    bool isSquareAttacked(std::vector<Move&> possibleMoves, Square position);
    void printBoard();

private:
    void movePiece(Square from, Square to);
    void enPassant(Piece *pawn, Move move);

    void kingSideCastle(Piece *king);

    void queenSideCastle(Piece *king);
    void promotion(Piece *pawnToPromote, Type pieceType);
};