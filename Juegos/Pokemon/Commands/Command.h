#pragma once
#include "../Controllers/Battle.h"
#include "../Controllers/Player.h"


namespace PokemonGame
{
    class PokemonGame::Battle;

    class Command
    {
        public:
    
            virtual ~Command() = default;
    
            virtual void Execute(
                PokemonGame::Battle& battle,
                PokemonGame::Player& actor,
                PokemonGame::Player& opponent) = 0;
    };
}