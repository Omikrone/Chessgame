#include "move_validator.hpp"


std::vector<std::string> MoveValidator::validate(const crow::json::rvalue& data) {
    std::vector<std::string> errors;

    std::string from = data["from"].s();
    std::string to = data["to"].s();

    if (!SquareValidator::is_valid_square(from)) {
        errors.push_back("Invalid 'from' square");
    }

    if (!SquareValidator::is_valid_square(to)) {
        errors.push_back("Invalid 'to' square");
    }

    if (data.has("promotion")) {
        std::string promotion = data["promotion"].s();
        if (promotion != "q" && promotion != "r" && promotion != "b" && promotion != "n") {
            errors.push_back("Invalid 'promotion' piece");
        }
    }

    return errors;
}