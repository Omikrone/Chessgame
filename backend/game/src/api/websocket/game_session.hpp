// game_session.hpp

#pragma once

#include "api/parsing/parser.hpp"
#include "players/bot.hpp"
#include "game.hpp"
#include "fen.hpp"

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
        Bot _bot;
        const int _id;
        std::chrono::steady_clock::time_point _last_activity;

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
        void on_move_received(crow::websocket::connection& ws, std::string from, std::string to);

        void bot_new_game(uint64_t game_id);

        void select_bot(uint64_t game_id);

        void send_bot_move(crow::websocket::connection& ws);

        void update_bot_position(BBMove bb_move);

        void bot_quit_game(uint64_t game_id);

        void send_game_state(crow::websocket::connection& ws, EndGame game_state);

        bool is_idle() const;

        void reset_idle();
};