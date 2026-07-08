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
    
            std::vector<PokemonGame::Pokemon*> team;
    
            PokemonGame::Pokemon* activePokemon;
    
            PokemonGame::Bag bag;
    
        public:
    
            Player(const std::string& name);
    
            ~Player();
    
            void addPokemon(PokemonGame::Pokemon* pokemon);
    
            void switchPokemon(int index);
    
            PokemonGame::Pokemon* getActivePokemon();
    
            PokemonGame::Bag& getBag();
    };
}