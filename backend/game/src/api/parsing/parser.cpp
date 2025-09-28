// parser.cpp

#include "api/parsing/parser.hpp"


bool Parser::is_valid_square(std::string sq) {

    // Checks the range
    return (sq.length() == 2 
        && sq.at(0) >= 'a'
        && sq.at(0) <= 'h'
        && sq.at(1) >= '1'
        && sq.at(1) <= '8');
}

int Parser::parse_position(std::string pos) {
    int position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = rank * 8 + file;
    return position;
}

Parser::ParseResult Parser::try_parse_move(std::string from, std::string to) {
    int from_i, to_i;
    if (!Parser::is_valid_square(from) || !Parser::is_valid_square(to)) {
        return {false, from + " or " + to + " is not a valid square", NULL};
    }

    // Creates the corresponding move
    // TODO: Create an alternative structure without take and type
    from_i = Parser::parse_position(from.substr(0, 2));
    to_i = Parser::parse_position(to.substr(0, 2));
    return {true, "", from_i, to_i};
}
