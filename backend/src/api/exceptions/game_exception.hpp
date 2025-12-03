#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Exception class for game-related errors.
 * 
 */
class GameException : public std::runtime_error {
    private:
        int _code;

public:
    /**
     * @brief Constructs a new GameException object.
     * 
     * @param message The error message.
     * @param code The error code.
     */
    explicit GameException(const std::string& message, int code)
        : std::runtime_error(message), _code(code) {}

    /**
     * @brief Gets the error code.
     * 
     * @return The error code.
     */
    int code() const {
        return _code;
    }
};