#pragma once

#include "game/components/square.hpp"
#include "game/components/move.hpp"
#include "api/models/requests.hpp"


class Parser {
public:

    struct ParseResult {
        bool valid;
        std::string error;
        Move move;
    };

    static bool isValidSquare(std::string sq);

    static Square parsePosition(std::string pos);
    static ParseResult tryParseMove(std::string from, std::string to);
};
