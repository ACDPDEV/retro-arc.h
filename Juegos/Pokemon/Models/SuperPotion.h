#pragma once

#include "Potion.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class SuperPotion : public PokemonGame::Potion
    {
        public:
        
            SuperPotion(int maxUses)
                    :
                    Potion(maxUses)
                {
                }
    };
}