#include "parser.hpp"


Square Parser::parsePosition(std::string pos) {
    Square position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = {file, rank};
    return position;
}

Move Parser::parseMove(std::string from, std::string to) {
    Move move;
    move.initPos = Parser::parsePosition(from.substr(0, 1));
    move.destPos = Parser::parsePosition(to.substr(0, 1));
    move.take = false;
    move.type = MoveType::NORMAL;
    return move;
}
