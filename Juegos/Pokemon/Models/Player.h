#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Bag.h"
#include "Item.h"
#include "Pokemon.h"


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
    
            ~Player() = default;

            std::string GetName()
            {
                return name;
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

            PokemonGame::Pokemon* GetPokemonById(int id)
            {
                for (const auto& pokemonPtr : team)
                {
                    if (pokemonPtr != nullptr && pokemonPtr->GetId() == id)
                    {
                        return pokemonPtr.get();
                    }
                }
                
                return nullptr;
            }
    
            void SwitchPokemon(int pokemonId)
            {
                activePokemon = GetPokemonById(pokemonId);
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