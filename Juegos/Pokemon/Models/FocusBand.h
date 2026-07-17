#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class FocusBand : public PokemonGame::Item
    {
        public:
        
            FocusBand(int maxUses)
                :
                Item(maxUses)
            {
            }

            void RegisterUse() override
            {
                remainingUses = 0;
            }

            void Use(PokemonGame::Pokemon& target) override
            {
                target.WearFocusBand();
                RegisterUse();
            }
    };
}