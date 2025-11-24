// response_parser.hpp

#pragma once

#include "game.hpp"
#include <string>
#include "crow.h"

class ResponseParser {
    public:
        static const crow::json::wvalue parse_game_state(const GameState game_state, const std::string& fen, Color current_turn);
        static const crow::json::wvalue parse_command(const std::string& command, const int game_id);
};