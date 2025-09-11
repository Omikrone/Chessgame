#pragma once

#include <vector>
#include <cassert>

#include "game/components/move.hpp"
#include "game/game_constants.hpp"



class GameHistory {
private:
    std::vector<Move> _history;
public:
    GameHistory() = default;
    ~GameHistory() = default;
    void push(Move move);
    const Move& last() const;
    bool empty() const;
};