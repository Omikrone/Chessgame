// engine_uci.hpp

#pragma once

#include "moves/move.hpp"

#include <optional>
#include <string>
#include <vector>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>


class EngineUCI
{

    private:

        const std::string _engine_addr;
        const int _engine_port;
        const int _game_id;
        websocketpp::client<websocketpp::config::asio_client> _cli;
        websocketpp::connection_hdl _hdl;

    public:

        EngineUCI(const std::string engine_addr, const int engine_port, int game_id);
        ~EngineUCI() = default;

        void init_ws_connection();
        void update_position(int game_id, const std::string fen, Move played_move);
        Move find_best_move(int game_id, std::optional<int> depth = std::nullopt);
        void close_ws_connection();
};