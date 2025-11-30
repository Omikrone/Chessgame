// game_session.hpp

#pragma once

#include "engine/engine_uci.hpp"
#include "api/parsing/response_parser.hpp"
#include "api/mappers/position_mapper.hpp"
#include "api/models/move.hpp"
#include "api/exceptions/game_exception.hpp"

#include "game.hpp"
#include "uci/fen.hpp"
#include "crow.h"
#include <chrono>
#include <random>


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
        Color _player_color = Color::WHITE;

        void reset_idle();

        void apply_player_move(crow::websocket::connection& ws, BitboardMove move);

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

        void apply_engine_move(crow::websocket::connection& ws);

        bool is_idle() const;

        Color get_player_color() const;

        int get_id() const;
};