#include <iostream>
#include <vector>
#include <iostream>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "game/game.hpp"



using namespace crow;

int main() {
    crow::SimpleApp app;
    std::vector<std::unique_ptr<Game>> games;


    app.port(18080).multithreaded().run();
}
