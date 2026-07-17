#pragma once
#include <memory>
#include "Player.h"
#include "TurnController.h"
#include "Battle.h"
#include "../Commands/Command.h"

namespace PokemonGame
{    
    class Round
    {
        private:
            PokemonGame::TurnController& turnOne;
            PokemonGame::TurnController& turnTwo;

            std::unique_ptr<PokemonGame::Command> playerOneCommand;
            std::unique_ptr<PokemonGame::Command> playerTwoCommand;
    
        public:
            Round(
                PokemonGame::TurnController& turnOne, 
                PokemonGame::TurnController& turnTwo)
                :
                turnOne(turnOne),
                turnTwo(turnTwo)
            {
            }
    
            void Play()
            {
                //----------------------------------
                // Turno del jugador 1
                //----------------------------------

                playerOneCommand = turnOne.ChooseCommand();

                //----------------------------------
                // Turno del jugador 2
                //----------------------------------

                playerTwoCommand = turnTwo.ChooseCommand();

                //----------------------------------
                // Ejecutar acciones
                //----------------------------------

                if(playerOneCommand->CanExecute(turnOne.GetPlayer()))
                    playerOneCommand->Execute(turnOne.GetPlayer(), turnTwo.GetPlayer());

                if (! turnOne.GetPlayer().CanPlay())
                    return;
                
                if(playerTwoCommand->CanExecute(turnTwo.GetPlayer()))
                    playerTwoCommand->Execute(turnTwo.GetPlayer(), turnOne.GetPlayer());

                if (! turnTwo.GetPlayer().CanPlay())
                    return;                
            }
    };
}