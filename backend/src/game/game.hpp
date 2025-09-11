#pragma once

#include "board/Board.hpp"
#include "move/MoveGenerator.hpp"
#include "move/MoveValidator.hpp"
#include "board/pieces/utils/color.hpp"
#include "board/pieces/utils/Square.hpp"
#include "board/pieces/utils/GameState.hpp"
#include "game_history.hpp"


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