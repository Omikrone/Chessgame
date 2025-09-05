#pragma once

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "../controllers/GameController.hpp"


void registerWebSocketRoutes(crow::App<crow::CORSHandler>& app, GameController& gameController);