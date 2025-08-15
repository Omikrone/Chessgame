#pragma once

#include "square.hpp"

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
};
