#pragma once

#include "Item.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class Antidote : public PokemonGame::Item
    {
        public:
        
            Antidote();
        
            void use(PokemonGame::Pokemon& target) override;
    };
}