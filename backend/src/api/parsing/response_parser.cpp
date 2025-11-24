// response_parser.cpp

#include "api/parsing/response_parser.hpp"

const crow::json::wvalue ResponseParser::parse_game_state(const GameState game_state, const std::string& fen, Color current_turn) {
    crow::json::wvalue response;

    if (game_state == GameState::CONTINUING) {
        response["type"] = "fen";
        response["fen"] = fen;
    }
    else {
        response["type"] = "endgame";
        response["fen"] = fen;

        if (game_state == GameState::STALEMATE) response["result"] = "draw";
        else if (current_turn == Color::WHITE) {
            response["result"] = "checkmate";
            response["winner"] = "black";
        }
        else {
            response["result"] = "checkmate";
            response["winner"] = "white";      
        }
    }
    return response;
}