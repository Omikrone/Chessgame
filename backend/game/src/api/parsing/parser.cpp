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

int Parser::pos_to_int(std::string pos) {
    int position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = rank * 8 + file;
    return position;
}

std::string Parser::int_to_pos(int pos) {
    std::string pos_str;
    char rank = pos / 8 + '1';
    char file = pos % 8 + 'a';
    pos_str.push_back(file);
    pos_str.push_back(rank);
    return pos_str;
}

Parser::ParseIntResult Parser::move_to_int(std::string from, std::string to) {
    int from_i, to_i;
    if (!Parser::is_valid_square(from) || !Parser::is_valid_square(to)) {
        return {false, from + " or " + to + " is not a valid square", NULL};
    }

    // Creates the corresponding move
    // TODO: Create an alternative structure without take and type
    from_i = Parser::pos_to_int(from.substr(0, 2));
    to_i = Parser::pos_to_int(to.substr(0, 2));
    return {true, "", from_i, to_i};
}
