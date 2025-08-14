#pragma once

#include "position.hpp"

enum class MoveType {
    NORMAL,
    EN_PASSANT,
    CASTLE_KINGSIDE,
    CASTLE_QUEENSIDE,
    PROMOTION
};

struct Move
{
    Position initPos;
    Position destPos;
    MoveType type;
    bool take;
};
