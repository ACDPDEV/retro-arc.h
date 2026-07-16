#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "./Enums/PokemonType.h"
#include "Move.h"

namespace PokemonGame
{   
    class Pokemon
    {
        private:
    
            std::string name;
    
            PokemonGame::PokemonType type;

            double maxHp;
            double currentHp;
            double defense;
            bool hasFocusBand = false;
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

            Pokemon()
            {
                
            }
    
            virtual ~Pokemon();
    
            void ReceiveDamage(double incomingDamage)
            {
                double effectiveDamage = GetEffectiveDamage(incomingDamage);
                if(effectiveDamage < currentHp)
                {
                    currentHp -= effectiveDamage;
                }
                else if(hasFocusBand)
                {
                    currentHp = 1;
                    hasFocusBand = false;
                }
                else
                {
                    currentHp = 0;
                }
            }
    
            bool isFainted() const;

            void AddMove(PokemonGame::Move* move)
            {
                moves.push_back(move);
            }

            std::vector<PokemonGame::Move*> GetMoves()
            {
                return moves;
            }
    
            PokemonGame::Move* GetMoveById(int index)
            {
                for (PokemonGame::Move* move : moves)
                {
                    if (move != nullptr && move->GetId() == index)
                    {
                        return move;
                    }
                }
                
                return nullptr;
            }
    
            PokemonGame::PokemonType GetType() const
            {
                return type;
            }
    };
}