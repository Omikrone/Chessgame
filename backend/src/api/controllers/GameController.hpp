#pragma once

#include <unordered_map>

#include "game.hpp"
#include "../websocket/GameSession.hpp"


class GameController
{
private:
    std::unordered_map<int, GameSession> _sessions;
    int _nextId = 1;
    
public:
    GameController();
    ~GameController();
    int createGame();
    GameSession* getGameSession(int gameId);
};
