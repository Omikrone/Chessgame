#include "api/parsing/parser.hpp"


bool Parser::isValidSquare(std::string sq) {
    return (sq.length() == 2 
        && sq.at(0) >= 'a'
        && sq.at(0) <= 'h'
        && sq.at(1) >= '1'
        && sq.at(1) <= '8');
}

Square Parser::parsePosition(std::string pos) {
    Square position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = {file, rank};
    return position;
}

Parser::ParseResult Parser::tryParseMove(std::string from, std::string to) {
    Move move;
    if (!Parser::isValidSquare(from) || !Parser::isValidSquare(to)) {
        return {false, from + " or " + to + " is not a valid square", NULL};
    }

    move.initPos = Parser::parsePosition(from.substr(0, 2));
    move.destPos = Parser::parsePosition(to.substr(0, 2));
    move.take = false;
    move.type = MoveType::NORMAL;
    return {true, "", move};
}
