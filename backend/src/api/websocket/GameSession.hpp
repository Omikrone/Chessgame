#pragma once

#include "game/Game.hpp"
#include "parsing/parser.hpp"
#include "game/Fen.hpp"
#include "crow.h"



class GameSession
{
private:
    Game _game;
    crow::websocket::connection* _ws;
public:
    GameSession();
    ~GameSession();
    void onMoveReceived(std::string rawMove);
};