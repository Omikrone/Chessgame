#pragma once

#include "crow/json.h"


struct ErrorResponse {
    int code;
    std::string message;

    crow::json::wvalue to_json() const {
        crow::json::wvalue response;
        response["error"] = message;
        response["code"] = code;
        return response;
    }
};