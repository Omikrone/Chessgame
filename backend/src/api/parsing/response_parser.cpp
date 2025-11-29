// response_parser.cpp

#include "api/parsing/response_parser.hpp"

const crow::json::wvalue ResponseParser::parse_command(const std::string& command, const int game_id) {
    crow::json::wvalue response;
    response["session_id"] = game_id;
    response["command"] = command;
    return response;
}