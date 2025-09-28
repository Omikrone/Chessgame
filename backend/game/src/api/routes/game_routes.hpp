// game_routes.hpp

#pragma once

#include "api/controllers/game_controller.hpp"

// Turns off the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#include "crow/middlewares/cors.h"
#pragma warning(pop)


/**
 * @brief Registers the http routes for the API.
 *
 * @param app The Crow app in which to register the routes.
 * @param gameController The controller of the multiple games.
 */
void register_game_routes(crow::App<crow::CORSHandler>& app, GameController &gameController);