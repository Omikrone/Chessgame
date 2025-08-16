#include "MoveParser.hpp"


Square convertInputToPos(std::string pos) {
    Square position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = {file, rank};
    return position;
}
