#pragma once

#include "crow.h"
#include "game/Game.hpp"


class GameSession
{
private:
    Game _game;
    crow::websocket::connection* _ws;
public:
    GameSession();
    ~GameSession();
    onMoveReceived(std::string rawMove);
};