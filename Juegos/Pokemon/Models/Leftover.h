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
        
            Leftover(int maxUses)
                :
                Item(maxUses)
            {
            }
        
            void Use(PokemonGame::Pokemon& target) override
            {
                
            }
    };
}