#include <iostream>
#include <vector>
#include <iostream>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "game/game.hpp"



using namespace crow;

int main() {
    crow::SimpleApp app;
    Game game(app);

    CROW_ROUTE(app, "/game").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        std::string from = body["from"].s();
        std::string to = body["to"].s();
        std::cout << "New game !" << std::endl;

        return crow::response(200, "ok");
    });

    app.port(18080).multithreaded().run();
}
