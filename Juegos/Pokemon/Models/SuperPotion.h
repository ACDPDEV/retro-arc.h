#pragma once

#include "Potion.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class SuperPotion : public PokemonGame::Potion
    {
        public:
        
            SuperPotion(int id, int maxUses)
                    :
                    Potion(id, maxUses)
            {
            }

            void Use(PokemonGame::Pokemon* target) override
            {
                target->ReceiveHeal(healPoints * 3);
            }
    };
}