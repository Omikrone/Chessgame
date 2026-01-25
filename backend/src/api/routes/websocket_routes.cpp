#include "api/routes/websocket_routes.hpp"

void register_websocket_routes(crow::App<crow::CORSHandler>& app, GameController& game_controller) {
    // Creates a new websocket route
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([](crow::websocket::connection& /*conn*/) { CROW_LOG_INFO << "Client connected!"; })
        .onmessage([&game_controller](crow::websocket::connection& conn, const std::string& data, bool /*is_binary*/) {
            try {
                // Parses the data received to a rvalue
                crow::json::rvalue body = crow::json::load(data);

                // Validates the different fields of the message
                JsonValidator::validate(body);

                if (body["msgType"].s() == "init") {
                    // Initialization message
                    int game_id = body["gameId"].i();
                    GameSession* session = game_controller.get_game_session(game_id);

                    conn.userdata(new uint64_t(game_id));

                    if (session->get_player_color() == Color::BLACK) {
                        // If the player is black, engine plays first move
                        session->apply_engine_move(conn);
                        return;
                    }
                }

                if (body["msgType"].s() == "move") {
                    MoveRequest move = MoveFactory::from_json(body);

                    // Searches for the corresponding game
                    uint64_t game_id = move.game_id;
                    GameSession* session = game_controller.get_game_session(game_id);

                    // Validates the move request
                    MoveRequestValidator::validate(move);

                    BitboardMove bb_move = BitboardMoveFactory::from_move_request(move);

                    session->on_move_received(conn, bb_move);
                }
            } catch (const GameException& e) {
                ErrorResponse error = ErrorMapper::to_error_response(e);
                conn.send_text(error.to_json().dump());
            } catch (const std::exception& e) {
                std::cout << "Internal server error: " << e.what() << std::endl;
                ErrorResponse error;
                error.code = 500;
                error.message = "Internal server error";
                conn.send_text(error.to_json().dump());
            }
        })
        .onclose([&game_controller](crow::websocket::connection& conn, const std::string& reason) {
            auto game_id_ptr = static_cast<uint64_t*>(conn.userdata());
            if (game_id_ptr) {
                game_controller.remove_session(*game_id_ptr);
                delete game_id_ptr;
            }
            game_controller.remove_idle_games();
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
