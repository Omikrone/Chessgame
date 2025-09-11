#pragma once

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "api/controllers/game_controller.hpp"


void registerGameRoutes(crow::App<crow::CORSHandler>& app, GameController &gameController);