#pragma once

#include "Item.h"
#include "Pokemon.h"
#include "Effect.h"

namespace PokemonGame
{
    /**
     * Item Restos
     */
    class Leftover : public PokemonGame::Item
    {
        private:
            int countActiveLeftovers = 0;

        public:
        
            Leftover(int id, int maxUses)
                :
                Item(id, maxUses)
            {
            }
        
            void Use(PokemonGame::Pokemon* target) override
            {
                PokemonGame::Effect* leftOver = new PokemonGame::Effect(PokemonGame::EffectName::LEFTOVER, 3);
                target->ApplyStartOfTheRoundEffect(leftOver);
            }
    };
}