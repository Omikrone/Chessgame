// data_validator.hpp

#pragma once

// Turns off the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#pragma warning(pop)

#include <string>


/**
 * @brief Static class responsible for the validation of the received data.
 *
 * Handles the validation of received data.
 */
class DataValidator {

    public:

        /**
         * @brief Represents a result of the validation.
         *
         */
        struct Result
        {
            bool valid;         // If the data is valid or not
            std::string error;  // Optionnal: The detailled error
        }; 

        /**
         * @brief Checks if the received message from the websocket is valid or not.
         *
         * @param data The received message.
         * @return The result of the validation.
         */
        static Result is_message_valid(const crow::json::rvalue& data);
};
