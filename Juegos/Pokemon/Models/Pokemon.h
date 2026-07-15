#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "PokemonType.h"
#include "Move.h"

namespace PokemonGame
{
    class PokemonGame::Move;
    
    class Pokemon
    {
        private:
    
            std::string name;
    
            PokemonGame::PokemonType type;

            double maxHp;
            double currentHp;
            double defense;
            std::vector<PokemonGame::Move*> moves;

            double GetEffectiveDamage(double damage)
            {
                return damage / (damage + 60);
            }
    
        public:
    
            Pokemon(
                const std::string& name,
                PokemonGame::PokemonType type,
                double hp,
                double defense)
                :
                name(name),
                type(type),
                maxHp(hp),
                currentHp(hp),
                defense(defense)
            {
                
            }
    
            virtual ~Pokemon();
    
            void receiveDamage(double damage)
            {
                double effectiveDamage = GetEffectiveDamage(damage);
                if(effectiveDamage < currentHp)
                {
                    currentHp -= effectiveDamage;
                }
                else
                {
                    currentHp = 0;
                }
            }
    
            bool isFainted() const;
    
            void addMove(PokemonGame::Move* move);

            std::vector<PokemonGame::Move*> GetMoves()
            {
                return moves;
            }
    
            PokemonGame::Move* getMoveById(int index)
            {

            }
    
            PokemonGame::PokemonType getType() const
            {
                return type;
            }
    };
}