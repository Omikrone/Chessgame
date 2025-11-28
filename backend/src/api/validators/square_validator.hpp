#pragma once

#include "crow/json.h"
#include <string>


class SquareValidator {
    public:
        static bool is_valid_square(const std::string& square);
};