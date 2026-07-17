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
                // Ejecutar acciones defensivas
                //----------------------------------
                if( ! dynamic_cast<AttackCommand*>(playerOneCommand.get()))
                {
                    if(playerOneCommand->CanExecute(turnOne.GetPlayer()))
                    {
                        playerOneCommand->Execute(turnOne.GetPlayer());
                    }
                    else
                    {
                        /**
                         * TODO:
                         * Mostrar mensaje que no se pudo ejecutar el comando
                         */
                    }
                }
                if( ! dynamic_cast<AttackCommand*>(playerTwoCommand.get()))
                {
                    if(playerTwoCommand->CanExecute(turnTwo.GetPlayer()))
                    {
                        playerTwoCommand->Execute(turnTwo.GetPlayer());
                    }
                    else
                    {
                        /**
                         * TODO:
                         * Mostrar mensaje que no se pudo ejecutar el comando
                         */
                    }
                }

                //----------------------------------
                // Ejecutar acciones ofensivas
                //----------------------------------
                if(dynamic_cast<AttackCommand*>(playerOneCommand.get()))
                {
                    if(playerOneCommand->CanExecute(turnOne.GetPlayer()))
                    {
                        playerOneCommand->Execute(turnTwo.GetPlayer());
                    }
                    else
                    {
                        /**
                         * TODO:
                         * Mostrar mensaje que no se pudo ejecutar el comando
                         */
                    }
                }
                if(dynamic_cast<AttackCommand*>(playerTwoCommand.get()))
                {
                    if(playerTwoCommand->CanExecute(turnTwo.GetPlayer()))
                    {
                        playerTwoCommand->Execute(turnOne.GetPlayer());
                    }
                    else
                    {
                        /**
                         * TODO:
                         * Mostrar mensaje que no se pudo ejecutar el comando
                         */
                    }
                }


                if (! turnOne.GetPlayer().CanPlay())
                    return;
                
                if (! turnTwo.GetPlayer().CanPlay())
                    return;                
            }
    };
}