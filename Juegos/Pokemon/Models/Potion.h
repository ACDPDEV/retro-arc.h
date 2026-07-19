#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class Potion : public PokemonGame::Item
    {
        protected:
        
            int healPoints = 20;
        
        public:
        
            Potion(int id, int maxUses)
                :
                Item(id, maxUses)
            {
            }
        
            void Use(PokemonGame::Pokemon* target) override
            {
                target->ReceiveHeal(healPoints);
            }
    };
}