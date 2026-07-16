#pragma once
#include "Command.h"
#include "../Controllers/Battle.h"
#include "../Models/Item.h"

namespace PokemonGame
{
    class PokemonGame::Item;
    
    class BagCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Item* item;
    
        public:
    
            BagCommand(PokemonGame::Item* item);
    
            void Execute(
                PokemonGame::Battle& battle,
                PokemonGame::Player& actor,
                PokemonGame::Player& opponent) override;
    };
}