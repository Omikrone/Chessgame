#pragma once

#include "position.hpp"

enum class MoveType {
    TRAVEL,
    TAKE,
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
};
