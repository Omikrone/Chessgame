// response_parser.hpp

#pragma once

#include "game.hpp"
#include <string>
#include "crow.h"

/**
 * @brief Class for parsing responses from the UCI engine.
 * 
 */
class ResponseParser {
    public:
        /**
         * @brief Parses a command response from the engine into a JSON object.
         * 
         * @param command The command response string from the engine.
         * @param game_id The ID of the game associated with the response.
         * @return A JSON object representing the parsed response.
         */
        static const crow::json::wvalue parse_command(const std::string& command, const int game_id);
};