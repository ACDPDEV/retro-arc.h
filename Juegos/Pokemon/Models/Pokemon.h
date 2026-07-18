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

            int id;
    
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

            double CalulateDamageReduction(double defense)
            {
                double defenseScale = 10.0;
                if(defense <= 0)
                    return 0.0;
                
                return defense / (defense + defenseScale);
            }
            
            double GetEffectiveDamage(double damage)
            {
                return damage * (1.0 - CalulateDamageReduction(defense));
            }
    
        public:
    
            Pokemon(
                const int id,
                const std::string& name,
                PokemonGame::PokemonType type,
                double hp,
                double defense)
                :
                id(id),
                name(name),
                type(type),
                maxHp(hp),
                currentHp(hp),
                defense(defense)
            {
                
            }
    
            ~Pokemon() = default;

            int GetId() const
            {
                return id;
            }

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
    
            bool IsFainted() const
            {
                return currentHp == 0;
            }

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
            
            bool IsValidMove(PokemonGame::Move* move)
            {
                auto it = std::find(moves.begin(), moves.end(), move);

                if (! (it == moves.end()) )
                {
                    return true;
                }
                return false;
            }
    
            PokemonGame::PokemonType GetType() const
            {
                return type;
            }
    };
}