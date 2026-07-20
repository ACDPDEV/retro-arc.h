#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include "./Enums/PokemonType.h"
#include "Effect.h"
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
            bool isRunning = false;
            std::vector<PokemonGame::Move*> moves;
            std::vector<PokemonGame::Effect*> startOfTheRoundEffects{};

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
                
                return defense / (2.0 * defense + defenseScale);
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
    
            ~Pokemon()
            {
                for (PokemonGame::Move* move : moves)
                {
                    delete move;
                }
                moves.clear();

                for (PokemonGame::Effect* effect : startOfTheRoundEffects)
                {
                    delete effect;
                }
                startOfTheRoundEffects.clear();
            }

            int GetId() const
            {
                return id;
            }

            std::string GetName() const
            {
                return name;
            }

            void WearFocusBand()
            {
                hasFocusBand = true;
            }

            void Run()
            {
                isRunning = true;
            }

            bool IsRunning() const
            {
                return isRunning;
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

            void UpdateEndOfTheTurnEffects() 
            {
                if (startOfTheRoundEffects.empty()) return;

                double totalHealing = 0.0;

                for (auto it = startOfTheRoundEffects.begin(); it != startOfTheRoundEffects.end(); ) 
                {
                    PokemonGame::Effect* currentEffect = *it;

                    // Verificamos si el efecto aún tiene turnos usando el método público
                    if (!currentEffect->IsExpired()) 
                    {
                        if (currentEffect->GetName() == PokemonGame::EffectName::LEFTOVER) 
                        {
                            // Restos cura el 5% de la vida máxima
                            totalHealing += (maxHp * 0.05);
                        }
                        
                        // TODO: Agregar más condicionales o un switch si se añaden efectos como VENENO
                        
                        currentEffect->DecreaseTurn();
                        ++it;
                    } 
                    else 
                    {
                        delete currentEffect;
                        it = startOfTheRoundEffects.erase(it);
                    }
                }

                // Aplicamos la curación total usando el método nativo que protege el maxHp
                if (totalHealing > 0.0) 
                {
                    ReceiveHeal(totalHealing);
                }
            }

            void ApplyStartOfTheRoundEffect(PokemonGame::Effect* effect)
            {
                if (effect != nullptr) 
                {
                    startOfTheRoundEffects.push_back(effect);
                }
            }

            void ReceiveHeal(double heal)
            {
                currentHp += std::min(heal, maxHp-currentHp);
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

            double GetCurrentHp() const
            {
                return currentHp;
            }

            double GetMaxHp() const
            {
                return maxHp;
            }
    
            PokemonGame::PokemonType GetType() const
            {
                return type;
            }
    };
}