// engine_uci.hpp

#pragma once

#include "moves/move.hpp"
#include "engine/engine_session.hpp"

#include <optional>
#include <string>
#include <vector>


class EngineUCI
{

    private:

        const std::string _engine_addr;
        const int _engine_port;
        const int _game_id;
        std::string _response;
        EngineSession _session;

    public:

        EngineUCI(const std::string engine_addr, const int engine_port, int game_id);
        ~EngineUCI() = default;

        void update_position(int game_id, const std::string fen, std::vector<Move> played_moves);
        Move find_best_move(int game_id, std::optional<int> depth = std::nullopt);
};