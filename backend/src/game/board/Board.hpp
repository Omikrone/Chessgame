#pragma once

#include <iostream>

#include "game/pieces/piece.hpp"
#include "game/pieces/pawn.hpp"
#include "game/pieces/rook.hpp"
#include "game/pieces/bishop.hpp"
#include "game/pieces/knight.hpp"
#include "game/pieces/king.hpp"
#include "game/pieces/queen.hpp"
#include "game/components/move.hpp"
#include "game/components/square.hpp"
#include "game/game_constants.hpp"


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

    Piece *get_piece_at(Square sq) const;
    void make_move(const Move &move);
    King& get_king(Color kingColor);
    bool is_square_attacked(std::vector<Move>& ennemyMoves, Square position);
    std::unique_ptr<GameBoard> clone() const;
    void print_board();

private:
    void move_piece(Square from, Square to);
    void enpassant(Piece *pawn, Move move);

    void kingside_castle(Piece *king);

    void queenside_castle(Piece *king);
    void promotion(Piece *pawnToPromote, PieceType pieceType);
};