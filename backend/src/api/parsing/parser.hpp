// parser.hpp

#pragma once

#include <string>


/**
 * @brief Static class representing the parsing from the client's data.
 *
 * Handles the parsing of position and moves.
 */
class Parser {

    public:

        /**
         * @brief Represents a Result of a parse.
         *
         */
        struct ParseIntResult {
            bool valid;         // If the parse was succesful or not 
            std::string error;  // Optionnal: the detailled error
            int from;         // Optionnal: the corresponding Move after the parse
            int to;
        };

        /**
         * @brief Checks if the given position is valid on a game board.
         *
         * @param sq A string representing the position.
         * @return true if the position is valid, else false.
         */
        static bool is_valid_square(std::string sq);

        /**
         * @brief Parses the given position into a square.
         *
         * @param pos A string representing the position.
         * @return the corresponding square.
         */
        static int pos_to_int(std::string pos);

        /**
         * @brief Tries to parse two given positions into a move.
         *
         * @param from A string representing the initial position.
         * @param to A string representing the destination.
         * @return The result of the parse.
         */
        static ParseIntResult move_to_int(std::string from, std::string to);

        static std::string int_to_pos(int pos);
};
