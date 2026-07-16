#pragma once

#include <string>
#include <random>
#include "Pokemon.h"
#include "./Enums/PokemonType.h"
#include "../Database/Effectiveness.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class Move
    {
        private:

            int id;
        
            std::string name;

            PokemonGame::PokemonType type;
        
            double baseDamage;
        
            double accuracy;
        
        public:
        
            Move(
                const int id,
                const std::string& name,
                PokemonGame::PokemonType type,
                double baseDamage,
                double accuracy)
                : 
                id(id),
                name(name),
                type(type),
                baseDamage(baseDamage),
                accuracy(accuracy)
            {
                
            }

            Move()
            {

            }
        
            ~Move() = default;

            double GetEffectiveness(PokemonGame::PokemonType attackerType, PokemonGame::PokemonType defenderType)
            {
                return PokemonGame::EFFECTIVENESS[static_cast<int>(attackerType)][static_cast<int>(defenderType)];
            }
        
            void Execute(
                PokemonGame::Pokemon& attacker,
                PokemonGame::Pokemon& defender)
            {
                double damageEffectiveness = GetEffectiveness(attacker.GetType(), defender.GetType());
                double modifiedDamage = baseDamage * damageEffectiveness;

                defender.ReceiveDamage(modifiedDamage);
            }

            int GetId()
            {
                return id;
            }

            /**
             * Evalúa si un movimiento tiene nombre o no
             * @return true cuando el movimiento tiene nombre
             */
            bool HasName()
            {
                return !name.empty();
            }

            bool RollAccuracy()
            {
                static std::random_device rd;
                static std::mt19937 generator(rd());
                static std::uniform_int_distribution<int> distribution(1, 100);

                return distribution(generator) <= accuracy;
            }
    };
}