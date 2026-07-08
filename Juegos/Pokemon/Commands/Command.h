#pragma once
#include "../Game/Battle.h"


namespace PokemonGame
{
    class PokemonGame::Battle;

    class Command
    {
        public:
    
            virtual ~Command() = default;
    
            virtual void Execute(PokemonGame::Battle& battle) = 0;
    };
}