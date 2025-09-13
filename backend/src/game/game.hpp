#pragma once

#include "game/board/board.hpp"
#include "game/rules/move_validator.hpp"
#include "game/rules/move_generator.hpp"
#include "game/components/square.hpp"
#include "game/game_history.hpp"
#include "game/game_constants.hpp"


class Game
{
private:    
    GameBoard _board;
    MoveValidator _moveValidator;
    GameHistory _history;
    Color _currentTurn;
    int _blackMovesNb;
    int _whiteMovesNb;
public:
    Game();
    ~Game() = default;
    bool try_apply_move(const Move& move);
    std::vector<Move> get_legal_moves(const Square sq);
    void next_turn();
    GameState get_game_state();
    Color get_current_turn() const;
    GameBoard& get_game_board();
    int get_nb_moves(const Color side) const;
};