#pragma once
#include "Command.h"
#include "../Game/Battle.h"
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
    
            void execute(PokemonGame::Battle& battle) override;
    };
}