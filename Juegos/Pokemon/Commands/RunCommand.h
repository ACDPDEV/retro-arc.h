#pragma once
#include "Command.h"
#include "../Controllers/Battle.h"

namespace PokemonGame
{
    class RunCommand : public PokemonGame::Command
    {
        public:
    
            void Execute(
                PokemonGame::Battle& battle,
                PokemonGame::Player& actor,
                PokemonGame::Player& opponent) override;
    };
}