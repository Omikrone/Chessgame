#pragma once

#include "game/components/square.hpp"
#include "game/components/move.hpp"


class Parser {
public:

    struct ParseResult {
        bool valid;
        std::string error;
        Move move;
    };

    static bool is_valid_square(std::string sq);

    static Square parse_position(std::string pos);
    static ParseResult try_parse_move(std::string from, std::string to);
};
