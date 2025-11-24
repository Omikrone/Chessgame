// engine_session.hpp

#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <condition_variable>
#include <mutex>

class EngineSession
{
    private:
        const std::string _engine_addr = "localhost";
        const int _engine_port = 18080;
        websocketpp::client<websocketpp::config::asio_client> _cli;
        websocketpp::connection_hdl _hdl;
        std::condition_variable _cv;
        std::mutex _mutex;
        std::string _response;

        void on_message(websocketpp::connection_hdl hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg);

    public:
        EngineSession(std::string engine_addr, int engine_port);
        ~EngineSession() = default;

        std::string send_command(const std::string& command, bool has_to_wait);
        void close_connection();
};