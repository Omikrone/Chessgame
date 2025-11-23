// engine_uci.cpp

#include "engine/engine_uci.hpp"


EngineUCI::EngineUCI(const std::string engine_addr, const int engine_port, int game_id) :
    _engine_addr(engine_addr),
    _engine_port(engine_port),
    _game_id(game_id)
{
    _cli.clear_access_channels(websocketpp::log::alevel::all);
    _cli.clear_error_channels(websocketpp::log::elevel::all);
    _cli.init_asio();

    
    websocketpp::lib::error_code ec;
    auto con = _cli.get_connection("ws://" + _engine_addr + ":" + std::to_string(_engine_port) + "/ws", ec);
    if (ec) {
        std::cout << "Connection error: " << ec.message() << std::endl;
        return;
    }

    _hdl = con->get_handle();
    _cli.connect(con);
    _cli.run();
}

void EngineUCI::update_position(int game_id, const std::string fen, Move move) {
    std::string cmd = "position fen " + fen + " moves " + move.to_uci();
    _cli.send(_hdl, cmd, websocketpp::frame::opcode::text);
}


Move EngineUCI::find_best_move(int game_id, std::optional<int> depth) {
    std::string cmd = "go";
    if (depth.has_value()) {
        cmd += " depth " + std::to_string(depth.value());
    }
    else {
        cmd += " depth 3";
    }
    _cli.send(_hdl, cmd, websocketpp::frame::opcode::text);
}


void EngineUCI::close_ws_connection() {
    _cli.close(_hdl, websocketpp::close::status::normal, "Client closed connection");
}