#pragma once
#include "Command.h"
#include "../Game/Battle.h"

namespace PokemonGame
{
    class RunCommand : public PokemonGame::Command
    {
        public:
    
            void execute(PokemonGame::Battle& battle) override;
    };
}