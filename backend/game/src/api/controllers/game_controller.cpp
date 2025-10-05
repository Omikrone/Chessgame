// game_controller.cpp

#include "api/controllers/game_controller.hpp"


uint64_t GameController::create_game() {
    uint64_t id = _next_id++;
    _sessions.try_emplace(id, std::make_unique<GameSession>(id));
    return id;
}


GameSession* GameController::get_game_session(uint64_t game_id) {
    auto it = _sessions.find(game_id);
    if (it == _sessions.end()) return nullptr;
    return it->second.get();
}


void GameController::remove_idle_games() {
    for (auto it = _sessions.begin(); it != _sessions.end(); ) {
        GameSession* s = it->second.get();
        if (s->is_idle()) {
            it = _sessions.erase(it);
        } else {
            ++it;
        }
    }
}