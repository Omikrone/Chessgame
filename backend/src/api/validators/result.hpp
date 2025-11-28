#pragma once

#include <string>
#include <optional>
#include <vector>


template<typename T>
struct Result {
    bool ok;
    std::optional<T> value;
    std::optional<std::vector<std::string>> error;

    static Result<T> success(const T& val) {
        return Result<T>{true, val, std::nullopt};
    }

    static Result<T> failure(const std::vector<std::string>& errors) {
        return Result<T>{false, std::nullopt, errors};
    }
};