// game_session.hpp

#pragma once

#include "engine/engine_uci.hpp"
#include "api/parsing/response_parser.hpp"
#include "api/models/move.hpp"

#include "game.hpp"
#include "uci/fen.hpp"
#include "crow.h"
#include <chrono>


/**
 * @brief Class representing the link between a websocket and a chess game.
 *
 * Handles the messages from the client and the game.
 */
class GameSession
{
    private:

        Game _game;
        EngineUCI _engine;
        const int _id;
        std::chrono::steady_clock::time_point _last_activity;

        void reset_idle();

    public:

        GameSession(int id);

        ~GameSession();

        /**
         * @brief Handles a move request sent by a client.
         *
         * @param ws The websocket connection with the client.
         * @param from The initial position of the move request.
         * @param to The destination of the move request.
         */
        void on_move_received(crow::websocket::connection& ws, BitboardMove move);

        bool is_idle() const;
};