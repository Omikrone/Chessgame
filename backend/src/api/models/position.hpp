#pragma once

#include "crow/json.h"
#include <string>
#include <optional>


/**
 * @brief Struct representing the response for a position request.
 * 
 */
struct PositionResponse{
    std::string fen;
    bool game_over;
    std::optional<std::string> winner;
    std::optional<std::string> result;
    std::optional<std::string> reason;

    crow::json::wvalue to_json() const {
        crow::json::wvalue response;
        response["fen"] = fen;
        response["game_over"] = game_over;
        if (winner.has_value()) {
            response["winner"] = winner.value();
        }
        if (result.has_value()) {
            response["result"] = result.value();
        }
        if (reason.has_value()) {
            response["reason"] = reason.value();
        }
        return response;
    }
};
