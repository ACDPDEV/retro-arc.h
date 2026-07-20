#pragma once

#include <string>
#include <utility>
#include "../Database/State.h"
#include "../Database/PokemonDatabase.h"
#include "../Models/Player.h"
#include "../Factories/PokemonFactory.h"
#include "../Controllers/PlayerController.h"
#include "../Controllers/Game.h"

namespace Pokemon {

    // mockToDbId / MockToDbId moved to Database/PokemonDatabase.h (REQ-4.5) so
    // MockData.h can also derive from it without duplicating the mapping.

    /// @brief Creates Player objects initialized from State.h globals
    /// @details Reads playerNames and selectedCurrentPokemonId from Pokemon:: namespace,
    ///          converts mock indices to DB IDs, creates Player objects with Pokemon,
    ///          fills bags, and sets initial active Pokemon.
    /// @return Pair of Player objects (playerOne, playerTwo)
    inline std::pair<PokemonGame::Player, PokemonGame::Player> BuildPlayers() {
        // 1. Read player names with fallback defaults
        std::string name1 = playerNames[0].empty() ? "Jugador 1" : playerNames[0];
        std::string name2 = playerNames[1].empty() ? "Jugador 2" : playerNames[1];

        // 2. Create Player objects
        PokemonGame::Player playerOne(name1);
        PokemonGame::Player playerTwo(name2);

        // 3. Convert mock indices to DB IDs and add Pokemon
        int dbId1 = MockToDbId(selectedCurrentPokemonId[0]);
        int dbId2 = MockToDbId(selectedCurrentPokemonId[1]);

        // 4. Add Pokemon to each player (with fallback to BuildTeam if invalid)
        if (dbId1 != -1) {
            auto pokemon1 = PokemonGame::PokemonFactory::Create(dbId1);
            if (pokemon1) {
                playerOne.AddPokemon(std::move(pokemon1));
            } else {
                // Factory failed: use BuildTeam for interactive selection
                PokemonGame::PlayerController::BuildTeam(playerOne);
            }
        } else {
            // Invalid mock index: use BuildTeam for interactive selection
            PokemonGame::PlayerController::BuildTeam(playerOne);
        }

        if (dbId2 != -1) {
            auto pokemon2 = PokemonGame::PokemonFactory::Create(dbId2);
            if (pokemon2) {
                playerTwo.AddPokemon(std::move(pokemon2));
            } else {
                // Factory failed: use BuildTeam for interactive selection
                PokemonGame::PlayerController::BuildTeam(playerTwo);
            }
        } else {
            // Invalid mock index: use BuildTeam for interactive selection
            PokemonGame::PlayerController::BuildTeam(playerTwo);
        }

        // 5. Fill bags and set initial active Pokemon
        PokemonGame::PlayerController::FillBag(playerOne);
        PokemonGame::PlayerController::FillBag(playerTwo);
        PokemonGame::PlayerController::SetInitialActivePokemon(playerOne);
        PokemonGame::PlayerController::SetInitialActivePokemon(playerTwo);

        return std::make_pair(std::move(playerOne), std::move(playerTwo));
    }

    /// @brief Creates a Game object initialized from State.h globals
    /// @details Reads playerNames and selectedCurrentPokemonId from Pokemon:: namespace,
    ///          converts mock indices to DB IDs, creates Player objects with Pokemon, and
    ///          runs the battle synchronously via Game::Start(Player&, Player&) before
    ///          returning. The returned Game already reflects a completed battle — there is
    ///          no deferred/async variant, since Game has no argument-less Start() to resume
    ///          later.
    /// @return PokemonGame::Game with the battle already played out
    inline PokemonGame::Game CreateGameFromState() {
        // Build players from globals
        auto players = BuildPlayers();

        // Create the Game and run the battle synchronously, same as Pokemon.h's own
        // direct-construction path.
        PokemonGame::Game game;
        game.Start(players.first, players.second);
        return game;
    }

    /// @brief Writes battle results back to State.h globals
    /// @param winnerName Name of the winning player
    /// @param roundCount Number of rounds played
    inline void WriteBackState(const std::string& winnerName, int roundCount) {
        Pokemon::winnerName = winnerName;
        Pokemon::currentRound = roundCount;
    }

} // namespace Pokemon
