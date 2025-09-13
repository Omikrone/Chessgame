#pragma once

#include <vector>

#include "game/components/move.hpp"
#include "game/pieces/piece.hpp"
#include "game/board/Board.hpp"
#include "game/rules/move_generator.hpp"
#include "game/game_history.hpp"


class MoveValidator
{
private:
    GameBoard& _board;
    GameHistory& _history;
    bool check_kingside_castle(Piece *king, std::vector<Move>& ennemyPossibleMoves);
    bool check_queenside_castle(Piece *king, std::vector<Move>& ennemyPossibleMoves);
    std::vector<Move> filter_enpassant_moves(std::vector<Move>& possibleMoves, Color side);
    std::vector<Move> filter_castle_moves(std::vector<Move>& possibleMoves, Color side);
    std::vector<Move> filter_check_moves(std::vector<Move>& possibleMoves, Color side);
public:
    MoveValidator(GameBoard& board, GameHistory& history);
    ~MoveValidator() = default;
    std::vector<Move> filter_legal_moves(std::vector<Move>& rawPossibleMoves, Color side);
};