#pragma once
#include "TurnController.h"
#include "Round.h"

namespace PokemonGame
{
    
    class Battle
    {
        private:
    
            PokemonGame::TurnController playerOneTurn;
            PokemonGame::TurnController playerTwoTurn;
            bool finished = false;
    
        public:
    
            Battle(
                PokemonGame::Player& playerOne,
                PokemonGame::Player& playerTwo)
                :
                playerOneTurn(playerOne),
                playerTwoTurn(playerTwo)
            {
            }
    
            void Start()
            {
                while (!finished)
                {
                    PokemonGame::Round round(playerOneTurn, playerTwoTurn);

                    round.Play();

                    EvaluateBattle();
                }
            }


            void EvaluateBattle()
            {
                if (playerOneTurn.HasLost())
                {
                    finished = true;
                }

                if (playerTwoTurn.HasLost())
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