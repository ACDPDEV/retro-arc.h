#pragma once

#include "Command.h"

namespace PokemonGame
{
    class RunCommand : public Command
    {
        public:
    
            void execute(Match& match) override;
    };
}