// websocket_routes.hpp

#pragma once

#include "api/controllers/game_controller.hpp"
#include "api/parsing/data_validator.hpp"

// Turns off the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#include "crow/middlewares/cors.h"
#pragma warning(pop)


/**
 * @brief Registers the websocket routes for the communication during the game.
 *
 * @param app The Crow app in which to register the routes.
 * @param gameController The controller of the multiple games.
 */
void register_websocket_routes(crow::App<crow::CORSHandler>& app, GameController& gameController);