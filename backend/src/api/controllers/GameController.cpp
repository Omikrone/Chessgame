#include "GameController.hpp"


int GameController::createGame() {
    int id = _nextId++;
    _sessions.emplace(id, GameSession());
    return id;
}


GameSession* GameController::getGameSession(int gameId) {
    auto it = _sessions.find(gameId);
    if (it == _sessions.end()) return nullptr;
    return &it->second;
}