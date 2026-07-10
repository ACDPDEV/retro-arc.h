#pragma once
#include "../Models/Player.h"
#include "Round.h"

namespace PokemonGame
{
    class PokemonGame::Player;
    
    class Battle
    {
        private:
    
            PokemonGame::Player& playerOne;
            PokemonGame::Player& playerTwo;
            bool finished = false;
    
        public:
    
            Battle(
                PokemonGame::Player& playerOne,
                PokemonGame::Player& playerTwo)
                :
                playerOne(playerOne),
                playerTwo(playerTwo)
            {
            }
    
            void Start()
            {
                while (!finished)
                {
                    PokemonGame::Round round(*this, playerOne, playerTwo);

                    round.Play();

                    EvaluateBattle();
                }
            }


            void EvaluateBattle()
            {
                if (playerOne.HasLost())
                {
                    finished = true;
                }

                if (playerTwo.HasLost())
                {
                    finished = true;
                }
            }
            
            bool IsFinished()
            {
                /**
                 * TODO: Implementar método
                 */
            }
    
            void NextRound();
    
            void Finish();
    };
}