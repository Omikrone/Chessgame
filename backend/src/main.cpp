#include <iostream>
#include <vector>

#include "api/controllers/game_controller.hpp"
#include "api/routes/game_routes.hpp"
#include "api/routes/websocket_routes.hpp"
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "game.hpp"

using namespace crow;

int main() {
    crow::App<crow::CORSHandler> app;
    std::vector<std::unique_ptr<Game>> games;

    // Registers the routes
    GameController controller = GameController();
    register_game_routes(app, controller);
    register_websocket_routes(app, controller);

    // Runs the app on port 18080
    app.port(18080).multithreaded().run();
}
