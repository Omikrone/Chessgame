#include "square_validator.hpp"


bool SquareValidator::is_valid_square(const std::string& square) {
    if (square.length() != 2) {
        return false;
    }

    char file = square[0];
    char rank = square[1];

    if (file < 'a' || file > 'h') {
        return false;
    }

    if (rank < '1' || rank > '8') {
        return false;
    }

    return true;
}