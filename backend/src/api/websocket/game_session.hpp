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

        const int _id;
        Game _game;
        EngineUCI _engine;
        std::chrono::steady_clock::time_point _last_activity;
        Color _player_color = Color::WHITE;

        /**
         * @brief Resets the idle timer of the session.
         * 
         */
        void reset_idle();

        /**
         * @brief Applies a move made by the player.
         * 
         * @param ws The websocket connection with the client.
         * @param move The move made by the player.
         */
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

        /**
         * @brief Applies the engine move and sends it to the client.
         * 
         * @param ws The websocket connection with the client.
         */
        void apply_engine_move(crow::websocket::connection& ws);

        /**
         * @brief Checks if the session is idle.
         * 
         * @return true if the session is idle, else false.
         */
        bool is_idle() const;

        /**
         * @brief Gets the color of the player.
         * 
         * @return The Color of the player.
         */
        Color get_player_color() const;

        /**
         * @brief Gets the id of the session.
         * 
         * @return The id.
         */
        int get_id() const;
};