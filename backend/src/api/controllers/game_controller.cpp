#include "api/controllers/game_controller.hpp"

#include "api/exceptions/game_exception.hpp"

GameSession* GameController::create_game() {
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    uint64_t id = _next_id++;
    _sessions.try_emplace(id, std::make_unique<GameSession>(id));
    return _sessions[id].get();
}

GameSession* GameController::get_game_session(uint64_t game_id) {
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    auto it = _sessions.find(game_id);
    if (it == _sessions.end()) throw GameException("Game session not found", 404);
    return it->second.get();
}

void GameController::remove_idle_games() {
    std::lock_guard<std::mutex> lock(_sessions_mutex);
    for (auto it = _sessions.begin(); it != _sessions.end();) {
        GameSession* s = it->second.get();
        if (s->is_idle() || _sessions.size() > MAX_GAMES) {
            it = _sessions.erase(it);
        } else {
            ++it;
        }
    }
}