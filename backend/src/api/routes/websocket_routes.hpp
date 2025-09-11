#pragma once

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "api/controllers/game_controller.hpp"
#include "api/parsing/data_validator.hpp"


void registerWebSocketRoutes(crow::App<crow::CORSHandler>& app, GameController& gameController);