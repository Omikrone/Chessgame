#pragma once

#include "crow/json.h"

/**
 * @brief Struct representing an error response.
 *
 */
struct ErrorResponse {
    int code;
    std::string message;

    /**
     * @brief Converts the ErrorResponse to a JSON object.
     *
     * @return A JSON representation of the ErrorResponse.
     */
    crow::json::wvalue to_json() const {
        crow::json::wvalue response;
        response["error"] = message;
        response["code"] = code;
        return response;
    }
};