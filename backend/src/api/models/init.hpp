#pragma once

#include <string>


/**
 * @brief Struct representing the initialization message for a game session.
 * 
 */
struct Init {
    int game_id;
    std::string msg_type;
};