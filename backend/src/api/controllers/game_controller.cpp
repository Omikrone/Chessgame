// game_controller.cpp

#include "api/controllers/game_controller.hpp"


uint64_t GameController::create_game() {
    uint64_t id = _nextId++;
    _sessions.try_emplace(id);
    return id;
}


GameSession* GameController::get_game_session(uint64_t gameId) {
    auto it = _sessions.find(gameId);
    if (it == _sessions.end()) return nullptr;
    return &it->second;
}