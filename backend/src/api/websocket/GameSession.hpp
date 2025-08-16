#pragma once

#include "game/Game.hpp"


class GameSession
{
private:
    Game _game;
    crow::websocket::connection* ws;
public:
    GameSession();
    ~GameSession();
};