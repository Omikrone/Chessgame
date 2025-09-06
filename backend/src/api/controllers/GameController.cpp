#include "GameController.hpp"


int GameController::createGame() {
    int id = _nextId++;
    _sessions.try_emplace(id);
    return id;
}


GameSession* GameController::getGameSession(int gameId) {
    auto it = _sessions.find(gameId);
    if (it == _sessions.end()) return nullptr;
    return &it->second;
}