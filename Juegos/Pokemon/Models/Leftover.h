#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    /**
     * Item Restos
     */
    class Leftover : public PokemonGame::Item
    {
        public:
        
            Leftover();
        
            void use(PokemonGame::Pokemon& target) override
            {
                
            }
    };
}