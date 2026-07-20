#pragma once
// #include <iostream>
#include <string>
#include <memory>
#include "../../../Common/Variables.h"
#include "../Models/Player.h"
#include "PlayerController.h"
#include "Battle.h"


namespace PokemonGame
{
    class Game
    {
    private:

        /// @brief Round count from the last Start() call
        int lastRoundCount = 0;

    public:

        /**
         * @brief Cantidad de pokemon que puede tener cada jugador
         */
        static inline int maxPokemon = 1;

        Game()
        {
        }
        ~Game() = default;

        /// @brief Starts a game with pre-built players (bridge integration)
        /// @details Skips team building, bag filling, and menu loop.
        ///          Players must be fully initialized before calling this.
        /// @param playerOne First player (already initialized)
        /// @param playerTwo Second player (already initialized)
        void Start(PokemonGame::Player& playerOne, PokemonGame::Player& playerTwo)
        {
            PokemonGame::Battle battle(playerOne, playerTwo);
            battle.Start();
            lastRoundCount = battle.GetRoundCount();
        }

        /// @brief Returns the round count from the last Start() call
        /// @return Number of rounds played
        int GetLastRoundCount() const
        {
            return lastRoundCount;
        }
    };
}