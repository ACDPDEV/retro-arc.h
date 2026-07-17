#pragma once
#include "../Commands/Command.h"
#include <memory>
#include "Player.h"
#include "Battle.h"

namespace PokemonGame
{    
    class Round
    {
        private:
            PokemonGame::Player& player1;
            PokemonGame::Player& player2;
            PokemonGame::Battle& battle;

            std::unique_ptr<PokemonGame::Command> playerOneCommand;
            std::unique_ptr<PokemonGame::Command> playerTwoCommand;
    
        public:
            Round(
                PokemonGame::Battle& battle,
                PokemonGame::Player& player1, 
                PokemonGame::Player& player2)
                :
                battle(battle),
                player1(player1),
                player2(player2)
            {
            }
    
            void Play()
            {
                //----------------------------------
                // Turno del jugador 1
                //----------------------------------

                playerOneCommand = player1.ChooseCommand(battle);

                //----------------------------------
                // Turno del jugador 2
                //----------------------------------

                playerTwoCommand = player2.ChooseCommand(battle);

                //----------------------------------
                // Ejecutar acciones
                //----------------------------------

                if(playerOneCommand->CanExecute(player1))
                    playerOneCommand->Execute(battle, player1, player2);

                if (battle.IsFinished())
                    return;
                
                if(playerTwoCommand->CanExecute(player2))
                    playerTwoCommand->Execute(battle, player2, player1);

                if (battle.IsFinished())
                    return;                
            }
    };
}