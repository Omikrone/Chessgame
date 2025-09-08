#pragma once

#include <vector>

#include "board/pieces/utils/Move.hpp"
#include "board/pieces/utils/Color.hpp"


class GameHistory {
private:
    std::vector<Move> _history;
public:
    GameHistory() = default;
    ~GameHistory() = default;
    void addMove(Move move);
    bool isTripleRepetition();
};