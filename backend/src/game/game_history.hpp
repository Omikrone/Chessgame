#pragma once

#include <vector>
#include <cassert>

#include "board/pieces/utils/Move.hpp"
#include "board/pieces/utils/Color.hpp"



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