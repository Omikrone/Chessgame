#pragma once

#include <string>


enum class MessageType {
    MOVE_REQUEST,
    MAKE_MOVE
};

struct PossibleMovesReq
{
    MessageType type;
    std::string position;

    static PossibleMovesReq fromJson(const crow::json::rvalue& json) {
        PossibleMovesReq req;
        req.type = json["type"];
        req.position = json["position"];
        return req;
    }
};


struct MakeMoveReq 
{
    MessageType type;
    std::string move;

    static MakeMoveReq fromJson(const crow::json::rvalue& json) {
        MakeMoveReq req;
        req.type = json["type"];
        req.move = json["move"];
        return req;
    }
};
