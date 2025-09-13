// game_session.hpp

#pragma once

#include "api/parsing/parser.hpp"
#include "game/game.hpp"
#include "game/fen.hpp"

#include "crow.h"


/**
 * @brief Class representing the link between a websocket and a chess game.
 *
 * Handles the messages from the client and the game.
 */
class GameSession
{
    private:

        Game _game;

    public:

        GameSession();

        ~GameSession() = default;

        /**
         * @brief Handles a move request sent by a client.
         *
         * @param ws The websocket connection with the client.
         * @param from The initial position of the move request.
         * @param to The destination of the move request.
         */
        void on_move_received(crow::websocket::connection& ws, std::string from, std::string to);
};