#include <iostream>
#include <vector>
#include <iostream>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "api/controllers/game_controller.hpp"
#include "game/game.hpp"
#include "api/routes/game_routes.hpp"
#include "api/routes/websocket_routes.hpp"


using namespace crow;

int main() {
    crow::App<crow::CORSHandler> app;
    std::vector<std::unique_ptr<Game>> games;

    GameController controller = GameController();
    registerGameRoutes(app, controller);
    registerWebSocketRoutes(app, controller);

    app.port(18080).multithreaded().run();
}
