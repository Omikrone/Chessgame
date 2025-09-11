#pragma once

#include "api/parsing/parser.hpp"
#include "game/game.hpp"
#include "game/fen.hpp"
#include "crow.h"



class GameSession
{
private:
    Game _game;
public:
    GameSession();
    ~GameSession() = default;
    void onMoveReceived(crow::websocket::connection& ws, std::string from, std::string to);
};