// engine_session.hpp

#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "api/parsing/response_parser.hpp"

/**
 * @brief Class representing a session with the UCI engine over WebSocket.
 */
class EngineSession {
   private:
    const std::string _engine_addr = "localhost";
    const int _engine_port = 18080;
    websocketpp::client<websocketpp::config::asio_client> _cli;
    websocketpp::connection_hdl _hdl;
    std::condition_variable _cv;
    std::mutex _mutex;
    std::string _response;
    int _game_id;

    /**
     * @brief Handler for incoming messages from the engine.
     *
     * @param hdl The connection handle.
     * @param msg The message received.
     */
    void on_message(websocketpp::connection_hdl /*hdl*/,
                    websocketpp::client<websocketpp::config::asio_client>::message_ptr msg);

   public:
    EngineSession(std::string engine_addr, int engine_port, int game_id);
    ~EngineSession() = default;

    /**
     * @brief Sends a command to the engine.
     *
     * @param command The command string to send.
     * @param has_to_wait Whether to wait for a response.
     * @return The response from the engine.
     */
    std::string send_command(const std::string& command, bool has_to_wait);

    /**
     * @brief Closes the connection to the engine.
     *
     */
    void close_connection();
};