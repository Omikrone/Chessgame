#pragma once

#include <optional>
#include <string>
#include <vector>

#include "engine/engine_session.hpp"
#include "moves/move.hpp"

/**
 * @brief Class representing a UCI chess engine.
 */
class EngineUCI {
   private:
    const std::string _engine_addr;
    const int _engine_port;
    const int _game_id;
    std::string _response;
    std::shared_ptr<EngineSession> _session;

   public:
    EngineUCI(const std::string engine_addr, const int engine_port, int game_id);
    ~EngineUCI() = default;

    /**
     * @brief Updates the position in the engine.
     *
     * @param is_startpos True if the position is the starting position, else false.
     * @param fen The FEN string representing the position (if not startpos).
     * @param played_moves The list of moves played to reach the position.
     */
    void update_position(bool is_startpos, const std::string fen, std::vector<Move> played_moves);

    /**
     * @brief Finds the best move from the current position.
     *
     * @param depth Optional depth to which the engine should search.
     * @return The best Move found by the engine.
     */
    Move find_best_move(std::optional<int> depth = std::nullopt);

    /**
     * @brief Quits the engine session.
     *
     */
    void quit();
};