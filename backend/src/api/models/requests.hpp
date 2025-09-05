#pragma once

#include <string>
#include <crow.h>


struct PossibleMovesReq
{
    std::string type;
    std::string position;

    static PossibleMovesReq fromJson(const crow::json::rvalue& json) {
        PossibleMovesReq req;
        req.type = json["type"].s();
        req.position = json["position"].s();
        return req;
    }
};


struct MakeMoveReq 
{
    std::string type;
    std::string move;

    static MakeMoveReq fromJson(const crow::json::rvalue& json) {
        MakeMoveReq req;
        req.type = json["type"].s();
        req.move = json["move"].s();
        return req;
    }
};
