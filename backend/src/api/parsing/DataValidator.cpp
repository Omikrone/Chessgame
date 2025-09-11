#include "DataValidator.hpp"


DataValidator::Result DataValidator::isMessageValid(const crow::json::rvalue& data) {
    Result result;
    result.valid = true;

    if (!data) {
        result.valid = false;
        result.error = "Missing or invalid JSON data";
    }

    if (!data.has("type")) {
        return {false, "Missing 'type' field"};
    }
    else {
        try {data["type"].s();}
        catch(const std::runtime_error& e) {return {false, "Invalid 'type' field"};}
    }

    if (!data.has("gameId")) {
        return {false, "Missing 'gameId' field"};
    }
    else {
        try {data["gameId"].u();}
        catch(const std::runtime_error& e) {return {false, "Invalid 'gameId' field"};}
    }

    if (!data.has("from")) {
        return {false, "Missing 'from' field"};
    }
    else {
        try {data["from"].s();}
        catch(const std::runtime_error& e) {return {false, "Invalid 'from' field"};}
    }

    if (!data.has("to")) {
        return {false, "Missing 'to' field"};
    }
    else {
        try {data["to"].s();}
        catch(const std::runtime_error& e) {return {false, "Invalid 'to' field"};}
    }

    return result;
}