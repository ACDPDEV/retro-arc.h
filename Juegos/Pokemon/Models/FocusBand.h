#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class FocusBand : public PokemonGame::Item
    {
        public:
        
            FocusBand(int id, int maxUses)
                :
                Item(id, maxUses)
            {
            }

            void RegisterUse() override
            {
                remainingUses = 0;
            }

            void Use(PokemonGame::Pokemon* target) override
            {
                target->WearFocusBand();
                RegisterUse();
            }
    };
}