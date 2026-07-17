#pragma once

#include <string>
#include <algorithm>
#include <vector>
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

            void UseFocusBand()
            {
                currentHp = std::max(currentHp, 1.0);
                hasFocusBand = false;
            }
            
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

            void WearFocusBand()
            {
                hasFocusBand = true;
            }
    
            void ReceiveDamage(double incomingDamage)
            {
                double effectiveDamage = GetEffectiveDamage(incomingDamage);
                if(effectiveDamage < currentHp)
                {
                    currentHp -= effectiveDamage;
                }
                else
                {
                    currentHp = 0;
                }

                if(hasFocusBand)
                {
                    UseFocusBand();
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