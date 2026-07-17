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
        private:
            int countActiveLeftovers = 0;

        public:
        
            Leftover(int id, int maxUses)
                :
                Item(id, maxUses)
            {
            }
        
            void Use(PokemonGame::Pokemon* target) override
            {
                
            }
    };
}