#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Battle.h"
#include "../Models/Player.h"
#include "../Models/Bag.h"
#include "../Models/Item.h"
#include "../Models/Pokemon.h"
#include "../Models/Player.h"
#include "../Enums/ChooseCommandOption.h"
#include "../Commands/Command.h"
#include "../Commands/AttackCommand.h"
#include "../Commands/SwitchPokemonCommand.h"
#include "../Commands/RunCommand.h"
#include "../Commands/BagCommand.h"

namespace PokemonGame
{
    
    class TurnController
    {
        private:
            PokemonGame::Player& player;
    
        public:
    
            TurnController(PokemonGame::Player& player)
                :player(player)
            {
            }

            std::unique_ptr<PokemonGame::Command> ChooseCommand()
            {
                while (true)
                {
                    int option = 0; // ShowBattleMenu();
                    switch (option)
                    {
                        case static_cast<int>(PokemonGame::ChooseCommandOption::FIGTH):
                        {
                            /**
                             * TODO:
                             * incluir el ShowMoveMenu() que retorna int moveId
                             */
                            int moveId = 0; // ShowMoveMenu(PokemonGame::Pokemon* activePokemon) retorna int moveId;

                            if (moveId != -1)
                            {
                                PokemonGame::Move* move = player.GetActivePokemon()->GetMoveById(moveId);
                                return std::make_unique<PokemonGame::AttackCommand>(move);
                            }

                            break;
                        }

                        case static_cast<int>(PokemonGame::ChooseCommandOption::BAG):
                        {
                            /**
                             * TODO:
                             * Implementar función para vista
                             */
                            int itemId = 0; // ShowBagMenu(); retorna int itemId;

                            if (itemId != -1)
                            {
                                PokemonGame::Item* item = player.GetBag().GetItemById(itemId);
                                return std::make_unique<PokemonGame::BagCommand>(item);
                            }

                            break;
                        }

                        case static_cast<int>(PokemonGame::ChooseCommandOption::POKEMON):
                        {
                            /**
                             * TODO:
                             * Implementar la vista para seleccionar el pokemon retorna -1
                             */
                            int pokemonId = 0; // ShowSwitchPokemonMeny(); retorn int pokemonId;

                            if (pokemonId != -1)
                                PokemonGame::Pokemon* selectedPokemon = player.GetPokemonById(pokemonId);
                                /**
                                 * TODO:
                                 * Pasar el pokemon por parámetro del constructor de switchCommand
                                 */
                                return std::make_unique<PokemonGame::SwitchPokemonCommand>();

                            break;
                        }

                        case static_cast<int>(PokemonGame::ChooseCommandOption::RUN):
                        {
                            /**
                             * TODO:
                             * Hacer ventana para confirmar la opción de huir
                             */
                            if (true)
                                return std::make_unique<PokemonGame::RunCommand>();

                            break;
                        }
                    }
                }
            }
    
            ~TurnController() = default;

            PokemonGame::Player& GetPlayer()
            {
                return player;
            }


            bool HasLost()
            {
                /**
                 * TODO: implementar
                 */
            }

    };
}