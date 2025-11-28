// websocket_routes.hpp

#pragma once

#include "api/controllers/game_controller.hpp"
#include "api/validators/move_json_validator.hpp"
#include "api/validators/move_request_validator.hpp"
#include "api/factories/bb_move_factory.hpp"
#include "api/factories/move_factory.hpp"

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