#pragma once

#include "../Models/Player.h"
#include "../Models/FocusBand.h"
#include "../Models/Leftover.h"
#include "../Models/Potion.h"
#include "../Models/SuperPotion.h"
#include "../Factories/PokemonFactory.h"

namespace PokemonGame
{
    /// @brief Maximum Pokemon per team (mirrors Game::maxPokemon)
    /// @details Decoupled from Game.h to break circular include dependency
    constexpr int DEFAULT_MAX_POKEMON = 1;

    class PlayerController
    {
        public:

            static void FillBag(PokemonGame::Player& player)
            {
                std::shared_ptr<PokemonGame::Item> focusBand = std::make_shared<PokemonGame::FocusBand>(1, 1);
                player.GetBag().AddItem(focusBand);

                std::shared_ptr<PokemonGame::Item> leftOver = std::make_shared<PokemonGame::Leftover>(2, 3);
                player.GetBag().AddItem(leftOver);

                std::shared_ptr<PokemonGame::Item> potion = std::make_shared<PokemonGame::Potion>(3, 3, 10);
                player.GetBag().AddItem(potion);

                std::shared_ptr<PokemonGame::Item> superPotion = std::make_shared<PokemonGame::SuperPotion>(4, 1, 30);
                player.GetBag().AddItem(superPotion);
            }

            /**
             * @brief Permite que el jugador seleccione los pokemon de su equipo
             * @return true Cuando el jugador completa su equipo
             * @return false Cuando el jugador elije salir
             */
            static bool BuildTeam(PokemonGame::Player& player)
            {
                player.ClearTeam();
            
                while (player.TeamSize() < PokemonGame::DEFAULT_MAX_POKEMON)
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
            
                    std::shared_ptr<PokemonGame::Pokemon> pokemon = PokemonGame::PokemonFactory::Create(pokemonId);
            
                    player.AddPokemon(pokemon);
                }

                return true;
            }

            static void SetInitialActivePokemon(PokemonGame::Player& player)
            {
                if(player.TeamSize() == 0)
                    return;
                auto& team = player.GetTeam();
                player.SwitchPokemon(team[0].get());
            }
    };
}