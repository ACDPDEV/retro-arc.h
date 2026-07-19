#pragma once
#include "Command.h"
#include "../Controllers/Battle.h"
#include "../Models/Player.h"

namespace PokemonGame
{
    class RunCommand : public PokemonGame::Command
    {
        public:
    
            void Execute(
                PokemonGame::Player& affectedPlayer) override
            {
                affectedPlayer.GetActivePokemon()->Run();
                
            }

            bool  CanExecute(PokemonGame::Player& actor)
            {
                actor.GetActivePokemon()->Run();
            }
    };
}