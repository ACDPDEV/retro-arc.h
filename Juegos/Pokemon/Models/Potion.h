#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class Potion : public PokemonGame::Item
    {
        private:
        
            int healPoints;
        
        public:
        
            Potion(int maxUses)
                :
                Item(maxUses)
            {
            }
        
            void Use(PokemonGame::Pokemon& target) override;
    };
}