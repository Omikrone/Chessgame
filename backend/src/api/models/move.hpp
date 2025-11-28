#pragma once

#include "crow/json.h"
#include <string>


struct MoveRequest
{
    int game_id;
    std::string from;
    std::string to;
    std::string promotion;

    static MoveRequest from_json(const crow::json::rvalue& json) {
        MoveRequest req;
        req.game_id = json["game_id"].i();
        req.from = json["from"].s();
        req.to = json["to"].s();
        if (json.has("promotion")) {
            req.promotion = json["promotion"].s();
        } else {
            req.promotion = "";
        }
        return req;
    }
};
