#pragma once

#include "game/components/square.hpp"

enum class MoveType {
    NORMAL,
    EN_PASSANT,
    CASTLE_KINGSIDE,
    CASTLE_QUEENSIDE,
    PROMOTION
};

struct Move
{
    Square initPos;
    Square destPos;
    MoveType type;
    bool take;

    bool operator==(const Move& other) const {
        return (this->initPos == other.initPos && this->destPos == other.destPos);
    }
};
