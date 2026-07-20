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
                playerOneTurn.GetPlayer().ResetForNewBattle();
                playerTwoTurn.GetPlayer().ResetForNewBattle();

                // Update battle state
                ::Pokemon::battleInProgress = true;
                ::Pokemon::currentRound = countRounds;

                // Start battle music once for the whole battle (not per-turn)
                ::Pokemon::StartBattleMusic();

                while (!finished)
                {
                    PokemonGame::Round round(playerOneTurn, playerTwoTurn);

                    round.Play(countRounds);

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
            
            /// @brief Returns the number of rounds played
            /// @return Round count
            int GetRoundCount() const
            {
                return countRounds;
            }
    };
}