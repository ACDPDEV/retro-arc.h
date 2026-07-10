#pragma once

#include <string>
#include <vector>
#include "Bag.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    class PokemonGame::Bag;
    
    class Player
    {
        private:
    
            std::string name;
    
            std::vector<std::unique_ptr<PokemonGame::Pokemon>> team;
    
            PokemonGame::Pokemon* activePokemon = nullptr;
    
            PokemonGame::Bag bag;
    
        public:
    
            Player(const std::string& name)
                :name(name)
            {
            }

            std::unique_ptr<PokemonGame::Command> ChooseCommand(Battle& battle)
            {
                /**
                 * TODO: UI para seleccionar la opción
                 */
                int option = 0; // ShowBattleMenu();  <<--- FUNCIÓN QUE MUESTRA LA VISTA PARA OBTENER LA OPCIÓN

                switch(option)
                {
                    case 1:
                        // return std::make_unique<AttackCommand>(ChooseMove());

                    case 2:
                        // return std::make_unique<BagCommand>(ChooseItem());

                    case 3:
                        // return std::make_unique<SwitchPokemonCommand>(ChoosePokemon());

                    case 4:
                        // return std::make_unique<RunCommand>();
                }

                return nullptr;
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