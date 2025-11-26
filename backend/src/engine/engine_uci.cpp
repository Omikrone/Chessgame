// engine_uci.cpp

#include "engine/engine_uci.hpp"


EngineUCI::EngineUCI(const std::string engine_addr, const int engine_port, int game_id) :
    _engine_addr(engine_addr),
    _engine_port(engine_port),
    _game_id(game_id),
    _session(engine_addr, engine_port, game_id)
{
}


void EngineUCI::update_position(int game_id, bool is_startpos, const std::string fen, std::vector<Move> played_moves) {
    std::string cmd = "position ";
    if (is_startpos) {
        cmd += fen;
    } else {
        cmd += "fen " + fen;
    }
    cmd += " moves";
    for (const auto& move : played_moves) {
        cmd += " " + move.to_uci();
    }
    _session.send_command(cmd, false);
}


Move EngineUCI::find_best_move(int game_id, std::optional<int> depth) {
    std::string cmd = "go";
    if (depth.has_value()) {
        cmd += " depth " + std::to_string(depth.value());
    }
    else {
        cmd += " depth 3";
    }
    cmd = "go movetime 5000";
    std::string response = _session.send_command(cmd, true);
    std::cout << "Engine response: " << response << std::endl;
    std::string bestmove_prefix = "bestmove ";;
    if (response.rfind(bestmove_prefix, 0) == 0) {
        std::string uci_move = response.substr(bestmove_prefix.length(), 4);
        return Move::from_uci(uci_move);
    }
    return Move();
}

void EngineUCI::quit() {
    _session.close_connection();
}