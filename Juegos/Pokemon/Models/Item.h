#pragma once

#include <string>
#include "Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class Item
    {
        
        public:
        
            Item()
            {
            }
        
            virtual ~Item() = default;
        
            virtual void use(PokemonGame::Pokemon& target) = 0;
    };
}