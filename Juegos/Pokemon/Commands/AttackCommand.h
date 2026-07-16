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
                PokemonGame::Battle& battle,
                PokemonGame::Player& actor,
                PokemonGame::Player& opponent) override
            {
                // actor.activePokemon->getMove()->execute(actor, opponent);
            }
    };
}