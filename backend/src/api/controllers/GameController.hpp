#pragma once

#include "game.hpp"



class GameController
{
private:
    Game& _game;
    GameSession& _gameSession;
public:
    GameController();
    ~GameController();
    int createGame();
    GameSession* getGameSession();
};
