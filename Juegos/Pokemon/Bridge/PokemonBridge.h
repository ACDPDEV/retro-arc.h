#pragma once

#include <string>
#include <utility>
#include "../Database/State.h"
#include "../Models/Player.h"
#include "../Factories/PokemonFactory.h"
#include "../Controllers/PlayerController.h"
#include "../Controllers/Game.h"

namespace Pokemon {

    /// @brief Hardcoded mock-index to DB-ID mapping
    /// @details mockToDbId[mockIndex] = dbSpeciesId
    /// Mock indices: 0=Bulbasaur, 1=Charmander, 2=Squirtle, 3=Pikachu,
    ///              4=Psyduck, 5=Eevee, 6=Rockruff, 7=Chikorita
    const int mockToDbId[8] = {5, 8, 6, 2, 1, 7, 4, 3};

    /// @brief Returns the DB species ID for a given mock index
    /// @param mockIndex Index in the MOCK_POKEMON array (0-7)
    /// @return DB species ID, or -1 if out of range
    inline int MockToDbId(int mockIndex) {
        if (mockIndex < 0 || mockIndex >= 8) {
            return -1;
        }
        return mockToDbId[mockIndex];
    }

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
    ///          converts mock indices to DB IDs, creates Player objects with Pokemon,
    ///          and returns an initialized Game. Note: Game::Start(Player&, Player&)
    ///          overload is required for full integration; this creates the Game shell.
    /// @return PokemonGame::Game with default configuration
    inline PokemonGame::Game CreateGameFromState() {
        // Build players from globals (stored locally for future integration)
        auto players = BuildPlayers();

        // Create and return Game object
        // Note: Players are not yet integrated into Game because
        // Game::Start(Player&, Player&) overload doesn't exist yet.
        // Full integration will happen in Phase 3.
        PokemonGame::Game game;
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
