#pragma once

// Deactivate the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#pragma warning(pop)

#include "crow/middlewares/cors.h"
#include "api/controllers/game_controller.hpp"
#include "api/parsing/data_validator.hpp"


void register_websocket_routes(crow::App<crow::CORSHandler>& app, GameController& gameController);