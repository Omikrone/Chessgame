// engine_uci.cpp

#include "engine/engine_uci.hpp"


EngineUCI::EngineUCI(const std::string engine_addr, const int engine_port, int game_id) :
    _engine_addr(engine_addr),
    _engine_port(engine_port),
    _game_id(game_id),
    _session(engine_addr, engine_port)
{
}


void EngineUCI::update_position(int game_id, const std::string fen, std::vector<Move> played_moves) {
    std::string cmd = "position fen " + fen + " moves";
    for (const auto& move : played_moves) {
        cmd += " " + move.to_uci();
    }
}


Move EngineUCI::find_best_move(int game_id, std::optional<int> depth) {
    std::string cmd = "go";
    if (depth.has_value()) {
        cmd += " depth " + std::to_string(depth.value());
    }
    else {
        cmd += " depth 3";
    }
}