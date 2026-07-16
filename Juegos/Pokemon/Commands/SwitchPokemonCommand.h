#pragma once

#include "Command.h"
#include "../Controllers/Battle.h"
#include "../Models/Pokemon.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class SwitchPokemonCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Pokemon* pokemon;
    
        public:
    
            SwitchPokemonCommand(PokemonGame::Pokemon* pokemon);
    
            void Execute(
                PokemonGame::Battle& battle,
                PokemonGame::Player& actor,
                PokemonGame::Player& opponent) override;
    };
}