#pragma once

#include "../../game/board/pieces/utils/Square.hpp"
#include "../../game/board/pieces/utils/Move.hpp"
#include "../models/requests.hpp"


class Parser {
public:
    static Square parsePosition(std::string pos);
    static Move parseMove(std::string from, std::string to);
};
