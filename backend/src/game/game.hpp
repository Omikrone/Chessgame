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
    bool tryApplyMove(const Move& move);
    std::vector<Move> getLegalMoves(Square sq);
    void Game::nextTurn();
    GameState getGameState();
    Color getCurrentTurn() const;
    GameBoard& getGameBoard();
    int getNbMoves(Color side) const;
};