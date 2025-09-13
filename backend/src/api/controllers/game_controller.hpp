#pragma once

#include <unordered_map>

#include "game/game.hpp"
#include "api/websocket/game_session.hpp"


class GameController
{
private:
    std::unordered_map<uint64_t, GameSession> _sessions;
    uint64_t _nextId = 1;
    
public:
    GameController() = default;
    ~GameController() = default;
    uint64_t create_game();
    GameSession* get_game_session(uint64_t gameId);
};
