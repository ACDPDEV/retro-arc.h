#pragma once

#include <string>
#include "Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class Item
    {
        protected:
        
            std::string name;
        
        public:
        
            Item(const std::string& name);
        
            virtual ~Item() = default;
        
            virtual void use(PokemonGame::Pokemon& target) = 0;
    };
}