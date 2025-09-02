#include "GameController.hpp"


GameController::GameController() {}

GameController::~GameController() {}


int GameController::createGame() {
    int id = _nextId++;
    games[id] = GameSession();
    return id;
}


GameSession* GameController::getGameSession(int gameId) {
    auto it = _sessions.find(gameId);
    if (it == _sessions.end()) return nullptr;
    return it->second.get();
}