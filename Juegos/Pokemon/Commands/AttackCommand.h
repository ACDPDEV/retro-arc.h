#pragma once
#include "Command.h"
#include "../Models/Move.h"
#include "../Models/Player.h"

namespace PokemonGame
{
    
    class AttackCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Move* move;
            
            double GetEffectiveness(PokemonGame::PokemonType attackerType, PokemonGame::PokemonType defenderType)
            {
                return PokemonGame::EFFECTIVENESS[static_cast<int>(attackerType)][static_cast<int>(defenderType)];
            }
    
        public:
    
            AttackCommand(PokemonGame::Move* move)
            :
            move(move)
            {

            }
    
            void Execute(
                PokemonGame::Player& defender) override
            {                
                PokemonGame::Pokemon* defenderPokemon = defender.GetActivePokemon();

                double damageEffectiveness = GetEffectiveness(move->GetType(), defenderPokemon->GetType());
                
                double modifiedDamage = move->GetBaseDamage() * damageEffectiveness;
                defenderPokemon->ReceiveDamage(modifiedDamage);
            }

            bool CanExecute(PokemonGame::Player& attacker) override
            {
                bool isValidMove = attacker.GetActivePokemon()->IsValidMove(move);
                bool isFainted = attacker.GetActivePokemon()->IsFainted();
                if(isValidMove && !isFainted)
                {
                    return true;
                }
                return false;
            }

            /// @brief Returns the move used by this attack command
            /// @return Pointer to the Move object
            PokemonGame::Move* GetMove()
            {
                return move;
            }
    };
}