#include "json_validator.hpp"

void JsonValidator::validate(const crow::json::rvalue& data) {
    std::vector<std::string> errors;
    if (!data.has("gameId")) {
        errors.push_back("Missing 'gameId' field");
    } else {
        try {
            data["gameId"].i();
        } catch (...) {
            errors.push_back("Invalid 'gameId' field");
        }
    }

    if (!data.has("msgType")) {
        errors.push_back("Missing 'msgType' field");
    } else {
        try {
            data["msgType"].s();
        } catch (...) {
            errors.push_back("Invalid 'msgType' field");
        }
    }
    if (data["msgType"].s() != "move" && data["msgType"].s() != "init") {
        errors.push_back("Invalid 'msgType' value");
    }

    if (data["msgType"].s() == "move") {
        if (!data.has("from")) {
            errors.push_back("Missing 'from' field");
        } else {
            try {
                data["from"].s();
            } catch (...) {
                errors.push_back("Invalid 'from' field");
            }
        }
        if (!data.has("to")) {
            errors.push_back("Missing 'to' field");
        } else {
            try {
                data["to"].s();
            } catch (...) {
                errors.push_back("Invalid 'to' field");
            }
        }
        if (data.has("promotion")) {
            try {
                data["promotion"].s();
            } catch (...) {
                errors.push_back("Invalid 'promotion' field");
            }
        }
    }

    if (!errors.empty()) {
        throw GameException(errors[0], 400);
    }
}