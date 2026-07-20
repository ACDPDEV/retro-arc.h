#pragma once
#include <memory>
#include "TurnController.h"
#include "Round.h"
#include "../Factories/PokemonFactory.h"
#include "../Sound/PokemonSound.h"
#include "../Database/State.h"

namespace PokemonGame
{
    
    class Battle
    {
        private:
    
            PokemonGame::TurnController playerOneTurn;
            PokemonGame::TurnController playerTwoTurn;
            bool finished = false;
            int countRounds = 0;
    
        public:
    
            Battle(
                PokemonGame::Player& playerOne,
                PokemonGame::Player& playerTwo)
                :
                playerOneTurn(playerOne),
                playerTwoTurn(playerTwo)
            {
            }

            ~Battle() = default;
    
            void Start()
            {
                ++countRounds;
                playerOneTurn.GetPlayer().ResetForNewBattle();
                playerTwoTurn.GetPlayer().ResetForNewBattle();

                // Update battle state
                ::Pokemon::battleInProgress = true;
                ::Pokemon::currentRound = countRounds;

                while (!finished)
                {
                    PokemonGame::Round round(playerOneTurn, playerTwoTurn);

                    round.Play();

                    ++countRounds;
                    ::Pokemon::currentRound = countRounds;

                    EvaluateBattle();
                }

                // Battle ended
                ::Pokemon::battleInProgress = false;
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

                // Stop battle music when battle ends
                if (finished)
                {
                    ::Pokemon::StopBattleMusic();
                }
            }
            
            /// @brief Checks if the battle is over
            /// @return true if one player has lost (all Pokemon fainted or ran)
            bool IsFinished()
            {
                return playerOneTurn.HasLost() || playerTwoTurn.HasLost();
            }

            /// @brief Returns the number of rounds played
            /// @return Round count
            int GetRoundCount() const
            {
                return countRounds;
            }
    
            void NextRound();
    
            void Finish();
    };
}