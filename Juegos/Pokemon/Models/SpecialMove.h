#pragma once

#include "Move.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class SpecialMove : public PokemonGame::Move
    {
    public:
    
        using PokemonGame::Move::Move;
    
        void execute(
            PokemonGame::Pokemon& attacker,
            PokemonGame::Pokemon& defender) override;
    };
}