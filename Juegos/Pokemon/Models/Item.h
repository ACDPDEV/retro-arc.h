#pragma once

#include <string>
#include "Pokemon.h"

namespace PokemonGame
{
    class Item
    {
        protected:
            int id;
            int maxUses;
            int remainingUses;
        
        public:
        
            Item(
                int id,
                int maxUses)
            :
            id(id),
            maxUses(maxUses),
            remainingUses(maxUses)
            {
            }
        
            virtual ~Item() = default;

            bool CanUse()
            {
                return remainingUses > 0;
            }

            int GetId()
            {
                return id;
            }

            virtual void RegisterUse() = 0;
        
            virtual void Use(PokemonGame::Pokemon* target) = 0;
    };
}