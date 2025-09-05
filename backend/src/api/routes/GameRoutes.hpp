#pragma once

#include "crow.h"
#include "../controllers/GameController.hpp"


void registerGameRoutes(crow::SimpleApp& app, GameController &gameController);