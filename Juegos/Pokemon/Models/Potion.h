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
        
            Potion(int healPoints);
        
            void use(PokemonGame::Pokemon& target) override;
    };
}