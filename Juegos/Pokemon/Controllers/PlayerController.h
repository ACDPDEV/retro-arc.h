#pragma once

#include "../Models/Player.h"
#include "../Models/FocusBand.h"
#include "../Models/Leftover.h"
#include "../Models/Potion.h"
#include "../Models/SuperPotion.h"
#include "Game.h"

namespace PokemonGame
{
    class PlayerController
    {
        public:

            static void FillBag(PokemonGame::Player& player)
            {
                std::unique_ptr<PokemonGame::Item> focusBand = std::make_unique<PokemonGame::FocusBand>(1, 1);
                player.GetBag().AddItem(std::move(focusBand));

                std::unique_ptr<PokemonGame::Item> leftOver = std::make_unique<PokemonGame::Leftover>(2, 3);
                player.GetBag().AddItem(std::move(leftOver));

                std::unique_ptr<PokemonGame::Item> potion = std::make_unique<PokemonGame::Potion>(3, 3);
                player.GetBag().AddItem(std::move(potion));

                std::unique_ptr<PokemonGame::Item> superPotion = std::make_unique<PokemonGame::SuperPotion>(4, 3);
                player.GetBag().AddItem(std::move(superPotion));
            }

            /**
             * @brief Permite que el jugador seleccione los pokemon de su equipo
             * @return true Cuando el jugador completa su equipo
             * @return false Cuando el jugador elije salir
             */
            static bool BuildTeam(PokemonGame::Player& player)
            {
                player.ClearTeam();
            
                while (player.TeamSize() < PokemonGame::Game::maxPokemon)
                {
                    // Mostrar lista de Pokémon
            
                    /**
                     * TODO: Referenciar al menú de selección de pokemon
                     */

                    int pokemonId = 0; // ShowPokemonMenu()

                    if(pokemonId == -1)
                    {
                        return false;
                    }
            
                    std::unique_ptr<PokemonGame::Pokemon> pokemon = PokemonGame::PokemonFactory::Create(pokemonId);
            
                    player.AddPokemon(std::move(pokemon));
                }

                return true;
            }
    };
}