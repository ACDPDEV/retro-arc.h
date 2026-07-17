#pragma once
#include "Command.h"
#include "../Controllers/Battle.h"
#include "../Models/Move.h"

namespace PokemonGame
{
    class PokemonGame::Move;
    
    class AttackCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Move* move;
    
        public:
    
            AttackCommand(PokemonGame::Move* move)
            :
            move(move)
            {

            }
    
            void Execute(
                PokemonGame::Battle& battle,  // -------------------------- este parámetro no se está usando
                PokemonGame::Player& attacker,
                PokemonGame::Player& defender) override
            {                
                PokemonGame::Pokemon* defenderPokemon = defender.GetActivePokemon();

                double damageEffectiveness = GetEffectiveness(move->GetType(), defenderPokemon->GetType());
                
                double modifiedDamage = move->GetBaseDamage() * damageEffectiveness;
                defenderPokemon->ReceiveDamage(modifiedDamage);
            }

            bool CanExecute(PokemonGame::Player& attacker)
            {
                bool isValidMove = attacker.GetActivePokemon()->IsValidMove(move);
                if(isValidMove)
                {
                    return true;
                }
                return false;
            }


            double GetEffectiveness(PokemonGame::PokemonType attackerType, PokemonGame::PokemonType defenderType)
            {
                return PokemonGame::EFFECTIVENESS[static_cast<int>(attackerType)][static_cast<int>(defenderType)];
            }
    };
}