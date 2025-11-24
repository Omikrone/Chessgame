// engine_session.cpp

#include "engine/engine_session.hpp"


EngineSession::EngineSession(std::string engine_addr, int engine_port, int game_id) :
    _engine_addr(engine_addr),
    _engine_port(engine_port), 
    _game_id(game_id)
{
    _cli.clear_access_channels(websocketpp::log::alevel::all);
    _cli.clear_error_channels(websocketpp::log::elevel::all);
    _cli.init_asio();
    _cli.set_message_handler(std::bind(&EngineSession::on_message, this, std::placeholders::_1, std::placeholders::_2));
    
    websocketpp::lib::error_code ec;
    auto con = _cli.get_connection("ws://" + _engine_addr + ":" + std::to_string(_engine_port) + "/engine/" + std::to_string(_game_id), ec);
    if (ec) {
        std::cout << "Connection error: " << ec.message() << std::endl;
        return;
    }

    _hdl = con->get_handle();
    _cli.connect(con);

    std::thread ws_thread([this]() {
        _cli.run();
    });
    ws_thread.detach();
}

void EngineSession::on_message(websocketpp::connection_hdl hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg) {
    std::unique_lock<std::mutex> lock(_mutex);
    _response = msg->get_payload();
    std::cout << "Received message: " << _response << std::endl;
    if (_response.rfind("info", 0) == 0) {
        std::cout << "Engine info: " << _response << std::endl;
    }
    else {
        _cv.notify_one();
    }
}

std::string EngineSession::send_command(const std::string& command, bool has_to_wait) {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _response.clear();
    }

    std::string json_command = ResponseParser::parse_command(command, _game_id).dump();
    _cli.send(_hdl, json_command, websocketpp::frame::opcode::text);

    if (has_to_wait) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this]{ return !_response.empty(); });
        std::cout << "Received response: " << _response << std::endl;
    }

    return _response;
}

void EngineSession::close_connection() {
    _cli.close(_hdl, websocketpp::close::status::normal, "Client closed connection");
}