#pragma once

#include "./Enums/EffectName.h"

namespace PokemonGame
{    
    class Effect 
    {
        private:
            PokemonGame::EffectName name;
            int maxTurns;
            int turnsLeft;

        public:
            Effect(PokemonGame::EffectName name, int maxTurns)
                :
                name(name),
                maxTurns(maxTurns),
                turnsLeft(maxTurns)
            {}

            ~Effect() = default;

            PokemonGame::EffectName GetName() const 
            { 
                return name; 
            }

            int GetTurnsLeft() const 
            { 
                return turnsLeft; 
            }

            void DecreaseTurn() 
            {
                if (turnsLeft > 0) {
                    turnsLeft--;
                }
            }
            
            bool IsExpired() const 
            {
                return turnsLeft <= 0;
            }
    };
}