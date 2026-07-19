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
            
            ~Round() = default;
    
            void Play()
            {
                //----------------------------------
                // Turno del jugador 1
                //----------------------------------

                /**
                 * TODO:
                 * Vista que retorna ChooseCommandOption y recibe entityId como parámetro por referencia
                 */
                int entityId1; // Se debe pasar esta variable como parámetro
                PokemonGame::ChooseCommandOption p1Option = PokemonGame::ChooseCommandOption::QUIT; // AQUÍ VA LA VISTA <<<----------
                if(p1Option == PokemonGame::ChooseCommandOption::QUIT)
                {
                    return;
                }
                playerOneCommand = turnOne.ChooseCommand(p1Option, entityId1);
                
                //----------------------------------
                // Turno del jugador 2
                //----------------------------------
                
                /**
                 * TODO:
                 * Vista que retorna ChooseCommandOption y recibe entityId como parámetro por referencia
                 */
                int entityId2; // Se debe pasar esta variable como parámetro
                PokemonGame::ChooseCommandOption p2Option = PokemonGame::ChooseCommandOption::QUIT; // AQUÍ VA LA VISTA <<<----------
                if(p2Option == PokemonGame::ChooseCommandOption::QUIT)
                {
                    return;
                }
                playerTwoCommand = turnTwo.ChooseCommand(p2Option, entityId2);

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
                if (! turnOne.GetPlayer().CanPlay())
                    return;
                
                if (! turnTwo.GetPlayer().CanPlay())
                    return;                

                //----------------------------------
                // Ejecutar acciones ofensivas
                //----------------------------------
                ExecuteIfIsAttackCommand(playerOneCommand.get(), turnTwo);
                ExecuteIfIsAttackCommand(playerTwoCommand.get(), turnOne);


            }
    };
}