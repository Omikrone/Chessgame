#include "parser.hpp"


Square Parser::parsePosition(PossibleMovesReq req) {
    Square position;
    int8_t file = req.position.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = req.position.at(1) - '1';
    position = {file, rank};
    return position;
}

Move
