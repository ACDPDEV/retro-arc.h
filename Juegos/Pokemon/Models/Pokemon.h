#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Move.h"

namespace PokemonGame
{
    class PokemonGame::Move;
    
    enum class PokemonType
    {
        Normal,
        Fire,
        Water,
        Grass,
        Electric,
        Rock,
        Ice,
        Psychic,
        Ghost
    };
    
    class Pokemon
    {
        private:
    
            std::string name;
    
            PokemonGame::PokemonType type;
    
            int maxHp;
            int currentHp;
    
            int attack;
            int defense;
            int speed;
    
            std::vector<PokemonGame::Move*> moves;
    
        public:
    
            Pokemon(
                const std::string& name,
                PokemonGame::PokemonType type,
                int hp,
                int attack,
                int defense,
                int speed);
    
            virtual ~Pokemon();
    
            void receiveDamage(int damage);
    
            bool isFainted() const;
    
            void addMove(PokemonGame::Move* move);
    
            PokemonGame::Move* getMove(int index);
    
            PokemonGame::PokemonType getType() const;
    };
}