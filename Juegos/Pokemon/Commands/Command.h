#pragma once
#include "../Controllers/Battle.h"
#include "../Models/Player.h"


namespace PokemonGame
{
    class PokemonGame::Battle;

    class Command
    {
        public:
        
            Command()
            {
                
            }
    
            virtual ~Command() = default;
    
            virtual void Execute(
                PokemonGame::Player& affectedPlayer) = 0;

            virtual bool CanExecute(PokemonGame::Player& actor) = 0;
    };
}