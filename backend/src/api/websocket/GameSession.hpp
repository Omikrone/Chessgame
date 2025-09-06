#pragma once

#include "../../game/Game.hpp"
#include "../parsing/parser.hpp"
#include "../../game/Fen.hpp"
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