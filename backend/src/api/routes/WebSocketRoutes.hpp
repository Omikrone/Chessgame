#pragma once

#include "crow.h"
#include "../controllers/GameController.hpp"


void registerWebSocketRoutes(crow::SimpleApp& app, GameController& gameController);