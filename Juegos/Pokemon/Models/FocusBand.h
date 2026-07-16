#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class FocusBand : public PokemonGame::Item
    {
        private:
            bool canActive = true;

        public:
        
            FocusBand()
            {
            }
        
            void use(PokemonGame::Pokemon& target) override
            {
                
            }
    };
}