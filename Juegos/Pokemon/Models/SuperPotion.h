#pragma once

#include "Potion.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class SuperPotion : public PokemonGame::Potion
    {
        public:
        
            SuperPotion(int id, int maxUses, int healPoints)
                    :
                    Potion(id, maxUses, healPoints)
            {
            }
    };
}