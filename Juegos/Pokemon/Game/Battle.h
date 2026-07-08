#pragma once
#include "../Models/Player.h"

namespace PokemonGame
{
    class PokemonGame::Player;
    
    class Battle
    {
        private:
    
            PokemonGame::Player* playerOne;
            PokemonGame::Player* playerTwo;
    
        public:
    
            Battle(
                PokemonGame::Player* playerOne,
                PokemonGame::Player* playerTwo)
                :playerOne(playerOne),
                playerTwo(playerTwo)
            {
            }
    
            void Start();

            void Play()
            {
                
            }
    
            void NextRound();
    
            void Finish();
    };
}