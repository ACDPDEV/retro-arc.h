#pragma once

#include "Move.h"
#include "Pokemon.h"

namespace PokemonGame
{
    class StatusMove : public PokemonGame::Move
    {
    public:
    
        using Move::Move;
    
        void execute(
            PokemonGame::Pokemon& attacker,
            PokemonGame::Pokemon& defender) override;
    };
}