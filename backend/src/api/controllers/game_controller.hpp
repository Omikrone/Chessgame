#pragma once

#include <unordered_map>

#include "game/game.hpp"
#include "api/websocket/game_session.hpp"


class GameController
{
private:
    std::unordered_map<int, GameSession> _sessions;
    int _nextId = 1;
    
public:
    GameController() = default;
    ~GameController() = default;
    int createGame();
    GameSession* getGameSession(int gameId);
};
