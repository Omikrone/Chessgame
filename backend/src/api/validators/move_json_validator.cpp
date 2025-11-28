#include "move_json_validator.hpp"


Result<crow::json::rvalue> MoveJsonValidator::validate(const crow::json::rvalue& data) {
    std::vector<std::string> errors;

    if (!data.has("from")) {
        errors.push_back("Missing 'from' field");
    }
    else {
        try {data["from"].s();} catch (...) {errors.push_back("Invalid 'from' field");}
    }
    if (!data.has("to")) {
        errors.push_back("Missing 'to' field");
    }
    else {
        try {data["to"].s();} catch (...) {errors.push_back("Invalid 'to' field");}
    }
    if (data.has("promotion")) {
        try {data["promotion"].s();} catch (...) {errors.push_back("Invalid 'promotion' field");}
    }

    if (!errors.empty()) {
        return Result<crow::json::rvalue>::failure(errors);
    }
    return Result<crow::json::rvalue>::success(data);
}