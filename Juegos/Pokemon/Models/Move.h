#pragma once

#include <string>
#include "Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class Move
    {
        protected:
        
            std::string name;

            PokemonGame::PokemonType type;
        
            int baseDamage;
        
            int accuracy;
        
        public:
        
            Move(
                const std::string& name,
                int damage,
                int accuracy);
        
            virtual ~Move() = default;
        
            virtual void execute(
                PokemonGame::Pokemon& attacker,
                PokemonGame::Pokemon& defender) = 0;
    };
}