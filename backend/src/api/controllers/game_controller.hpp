// game_controller.hpp

#pragma once

#include "api/websocket/game_session.hpp"

#include <unordered_map>


/**
 * @brief Class responsible for the management of the games.
 *
 * Handles the validation of received data.
 */
class GameController
{
    private:

        std::unordered_map<uint64_t, std::unique_ptr<GameSession>> _sessions;
        uint64_t _next_id = 1;
        
    public:

        GameController() = default;

        ~GameController() = default;

        /**
         * @brief Creates a new game session and adds it to map.
         *
         * @return The game ID of the new game session.
         */
        GameSession* create_game();

        /**
         * @brief Gets a game session by its ID.
         *
         * @return A pointer to the corresponding game session.
         */
        GameSession* get_game_session(uint64_t game_id);


        void remove_idle_games();
};
