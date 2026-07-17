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

            void ExecuteIfIsDefensiveCommand(PokemonGame::Command* command, PokemonGame::TurnController& affectedTurn)
            {
                if( ! dynamic_cast<AttackCommand*>(command))
                {
                    command->Execute(affectedTurn.GetPlayer());
                }
            }

            void ExecuteIfIsAttackCommand(PokemonGame::Command* command, PokemonGame::TurnController& defenderTurn)
            {
                if(PokemonGame::AttackCommand* attackCommand = dynamic_cast<AttackCommand*>(command))
                {
                    attackCommand->Execute(defenderTurn.GetPlayer());
                }
            }
    
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
                // Validar comandos
                //----------------------------------
                bool bothCanExecute = true;
                if( ! playerOneCommand->CanExecute(turnOne.GetPlayer()))
                    bothCanExecute = false;

                if( ! playerTwoCommand->CanExecute(turnTwo.GetPlayer()))
                    bothCanExecute = false;

                if( ! bothCanExecute)
                {
                    /**
                     * TODO:
                     * Mostrar mensaje que no se pudo ejecutar el comando
                     */
                    return;
                }

                //----------------------------------
                // Ejecutar acciones defensivas
                //----------------------------------
                ExecuteIfIsDefensiveCommand(playerOneCommand.get(), turnOne);
                ExecuteIfIsDefensiveCommand(playerTwoCommand.get(), turnTwo);

                //----------------------------------
                // Ejecutar acciones ofensivas
                //----------------------------------
                ExecuteIfIsAttackCommand(playerOneCommand.get(), turnTwo);
                ExecuteIfIsAttackCommand(playerTwoCommand.get(), turnOne);


                if (! turnOne.GetPlayer().CanPlay())
                    return;
                
                if (! turnTwo.GetPlayer().CanPlay())
                    return;                
            }
    };
}