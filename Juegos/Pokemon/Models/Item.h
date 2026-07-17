#pragma once

#include <string>
#include "Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class Item
    {
        protected:
            int remainingUses;
        
        public:
        
            Item(int maxUses)
            :
            remainingUses(maxUses)
            {
            }
        
            virtual ~Item() = default;

            bool CanUse()
            {
                return remainingUses > 0;
            }

            virtual void RegisterUse() = 0;
        
            virtual void Use(PokemonGame::Pokemon& target) = 0;
    };
}