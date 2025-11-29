#pragma once

#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
    private:
        int _code;

public:
    explicit GameException(const std::string& message, int code)
        : std::runtime_error(message), _code(code) {}

    int code() const {
        return _code;
    }
};