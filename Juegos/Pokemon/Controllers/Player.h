#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Battle.h"
#include "../Commands/Command.h"
#include "../Models/Bag.h"
#include "../Models/Item.h"
#include "../Models/Pokemon.h"
#include "../Enums/MenuOption.h"
#include "../Commands/AttackCommand.h"
#include "../Commands/SwitchPokemonCommand.h"
#include "../Commands/RunCommand.h"
#include "../Commands/BagCommand.h"

namespace PokemonGame
{
    
    class Player
    {
        private:
    
            std::string name;
    
            std::vector<std::unique_ptr<PokemonGame::Pokemon>> team;
            
            PokemonGame::Pokemon* activePokemon = nullptr;
            
            PokemonGame::Bag bag;
            
            bool canUseFocusBand = true;
    
        public:
    
            Player(const std::string& name)
                :name(name)
            {
            }

            std::unique_ptr<PokemonGame::Command> ChooseCommand(PokemonGame::Battle& battle)
            {
                while (true)
                {
                    int option = 0; // ShowBattleMenu();
                    switch (option)
                    {
                        case static_cast<int>(PokemonGame::MenuOption::FIGTH):
                        {
                            /**
                             * TODO:
                             * incluir el ShowMoveMenu() que retorna un Move con parámetros
                             */
                            int moveIndex = 0; // ShowMoveMenu(PokemonGame::Pokemon* activePokemon) retorna Move(name, type, baseDamage, accuracy);

                            if (moveIndex != -1)
                            {
                                PokemonGame::Move move();
                                return std::make_unique<PokemonGame::AttackCommand>(move);
                            }

                            break;
                        }

                        case static_cast<int>(PokemonGame::MenuOption::BAG):
                        {
                            auto item = PokemonGame::Move(); // ShowBagMenu(); retorna Item(name);

                            if (item.HasName())
                                return std::make_unique<PokemonGame::BagCommand>(item);

                            break;
                        }

                        case static_cast<int>(PokemonGame::MenuOption::POKEMON):
                        {
                            auto pokemon = *team[0]; //ShowPokemonMenu();

                            /**
                             * TODO:
                             * Controlar el flujo de que efectivamente se ha seleccionado esta opción
                             */
                            if (true)
                                return std::make_unique<PokemonGame::SwitchPokemonCommand>(pokemon);

                            break;
                        }

                        case static_cast<int>(PokemonGame::MenuOption::RUN):
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
    
            ~Player() = default;

            std::string GetName()
            {
                return name;
            }

            bool HasLost()
            {
                /**
                 * TODO: implementar
                 */
            }

            /**
             * @brief Elimina todos los Pokemon que pertenecen al jugador
             */
            void ClearTeam()
            {
                team.clear();
                activePokemon = nullptr;
            }
    
            /**
             * Obtiene la cantidad de pokemones dentro del equipo
             * @returns La cantidad de pokemones dentro del equipo
             */
            int TeamSize() const
            {
                return team.size();
            }

            /**
             * Agrega un pokemon al equipo del jugador
             * @param pokemon Pokemon que se va a agregar al equipo
             */
            void AddPokemon(std::unique_ptr<PokemonGame::Pokemon> pokemon)
            {
                if (team.empty())
                {
                    activePokemon = pokemon.get();
                }
                team.push_back(std::move(pokemon));
            }

            PokemonGame::Pokemon* GetPokemon(size_t index)
            {
                return team.at(index).get();
            }
    
            void SwitchPokemon(size_t index)
            {
                activePokemon = team.at(index).get();
            }
    
            PokemonGame::Pokemon* GetActivePokemon()
            {
                return activePokemon;
            }
    
            PokemonGame::Bag& GetBag()
            {
                return bag;
            }
    };
}