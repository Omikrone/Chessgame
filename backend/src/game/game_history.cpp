#include "game_history.hpp"


void GameHistory::addMove(Move move) {
    _history.push_back(move);
}

bool GameHistory::isTripleRepetition() {
    return false;
}
