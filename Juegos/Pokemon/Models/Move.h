#pragma once

#include <string>
#include "Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class Move
    {
        private:
        
            std::string name;

            PokemonGame::PokemonType type;
        
            double baseDamage;
        
            double accuracy;
        
        public:
        
            Move(
                const std::string& name,
                PokemonGame::PokemonType type,
                double baseDamage,
                double accuracy)
                : 
                name(name),
                type(type),
                baseDamage(baseDamage),
                accuracy(accuracy)
            {
                
            }
        
            ~Move() = default;
        
            void execute(
                PokemonGame::Pokemon& attacker,
                PokemonGame::Pokemon& defender);

            bool HasValue();
    };
}