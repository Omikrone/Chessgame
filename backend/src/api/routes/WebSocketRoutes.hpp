#pragma once

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "../controllers/GameController.hpp"
#include "../parsing/DataValidator.hpp"


void registerWebSocketRoutes(crow::App<crow::CORSHandler>& app, GameController& gameController);