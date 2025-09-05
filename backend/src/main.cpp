#include <iostream>
#include <vector>
#include <iostream>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "api/controllers/GameController.hpp"
#include "game/Game.hpp"
#include "api/routes/GameRoutes.hpp"
#include "api/routes/WebSocketRoutes.hpp"


using namespace crow;

int main() {
    crow::SimpleApp app;
    std::vector<std::unique_ptr<Game>> games;

    GameController controller = GameController();
    registerGameRoutes(app, controller);
    registerWebSocketRoutes(app, controller);

    app.port(18080).multithreaded().run();
}
