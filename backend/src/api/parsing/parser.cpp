#include "api/parsing/parser.hpp"


bool Parser::is_valid_square(std::string sq) {
    return (sq.length() == 2 
        && sq.at(0) >= 'a'
        && sq.at(0) <= 'h'
        && sq.at(1) >= '1'
        && sq.at(1) <= '8');
}

Square Parser::parse_position(std::string pos) {
    Square position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = {file, rank};
    return position;
}

Parser::ParseResult Parser::try_parse_move(std::string from, std::string to) {
    Move move;
    if (!Parser::is_valid_square(from) || !Parser::is_valid_square(to)) {
        return {false, from + " or " + to + " is not a valid square", NULL};
    }

    move.initPos = Parser::parse_position(from.substr(0, 2));
    move.destPos = Parser::parse_position(to.substr(0, 2));
    move.take = false;
    move.type = MoveType::NORMAL;
    return {true, "", move};
}
