#pragma once

#include "crow.h"


void registerWebSocketRoutes(crow::SimpleApp& app, GameController& gameController);