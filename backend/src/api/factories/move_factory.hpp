#pragma once

#include "api/models/move.hpp"


/**
 * @brief Factory class for creating MoveRequest objects from JSON.
 * 
 */
class MoveFactory {

    public:

        /**
         * @brief Creates a MoveRequest from the given JSON data.
         * 
         * @param json The JSON data to parse.
         * @return The created MoveRequest object.
         */
        static MoveRequest from_json(const crow::json::rvalue& json);
};