// parser.hpp

#pragma once

#include "api/parsing/parser.hpp"

#include <string>


struct UCIMove
{
    const std::string move;
};

struct BBMove
{
    int from;
    int to;
};

/**
 * @brief Static class representing the parsing from the client's data.
 *
 * Handles the parsing of position and moves.
 */
class UCIParser {

    public:

        /**
         * @brief Tries to parse two given positions into a move.
         *
         * @param from A string representing the initial position.
         * @param to A string representing the destination.
         * @return The result of the parse.
         */
        static BBMove uci_to_bb(UCIMove uci_move);


        static UCIMove bb_to_uci(BBMove bb_move);
};
