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

    std::vector<std::vector<std::unique_ptr<Piece>>> _board;
    King *_whiteKing;
    King *_blackKing;

    GameBoard();
    GameBoard(const GameBoard&) = delete;
    GameBoard& operator=(const GameBoard&) = delete;
    
    GameBoard(GameBoard&&) = default;
    GameBoard& operator=(GameBoard&&) = default;

    Piece *getPieceAt(Square sq) const;
    void makeMove(const Move &move);
    King& getKing(Color kingColor);
    bool isSquareAttacked(std::vector<Move>& ennemyMoves, Square position);
    void printBoard();

private:
    void movePiece(Square from, Square to);
    void enPassant(Piece *pawn, Move move);

    void kingSideCastle(Piece *king);

    void queenSideCastle(Piece *king);
    void promotion(Piece *pawnToPromote, Type pieceType);
};