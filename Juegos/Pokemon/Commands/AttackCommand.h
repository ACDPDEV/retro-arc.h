#pragma once
#include "Command.h"
#include "../Game/Battle.h"
#include "../Models/Move.h"

namespace Pokemon
{
    class PokemonGame::Move;
    
    class AttackCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Move* move;
    
        public:
    
            AttackCommand(PokemonGame::Move* move);
    
            void Execute(
                PokemonGame::Battle& battle,
                PokemonGame::Player& actor,
                PokemonGame::Player& opponent) override;
    };
}