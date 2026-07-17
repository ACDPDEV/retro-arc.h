#pragma once
// #include <iostream>
#include <string>
#include <memory>
#include "Battle.h"
#include "../../../Common/Variables.h"
#include "../Models/Player.h"
#include "../Functions/BuildTeam.h"
#include "../Enums/GameOption.h"


namespace PokemonGame
{
    class Game
    {
    public:

        /**
         * @brief Cantidad de pokemon que puede tener cada jugador
         */
        static inline int maxPokemon = 6;

        Game()
        {
        }
    
        void Start()
        {
            /**
             * TODO: Asignar los valores de las variables globales y volver a asignar cualquier cambio de los objetos
             * al terminar el programa
             */
            std::string playerNameOne = Common::playerName; 
            std::string playerNameTwo = "Jugador 2";
            bool running = true;
            PokemonGame::Player playerOne(playerNameOne);
            PokemonGame::Player playerTwo(playerNameTwo);
            while (running)
            {

                /**
                 * 
                 * TODO: 
                 * Invocar a la clase o función que contiene la lógica de vista para seleccionar la opción. 
                 * return : Debe devolver la opción
                 * 
                 * 
                 */
                int option = 0;

                switch (option)
                {
                    // iniciar batalla
                    case static_cast<int>(PokemonGame::GameOption::BATTLE):
                    {
                        PokemonGame::BuildTeam(playerOne);
                        PokemonGame::BuildTeam(playerTwo);

                        PokemonGame::Battle battle(playerOne, playerTwo);

                        battle.Start();
                        break;
                    }

                    // Salir
                    case static_cast<int>(PokemonGame::GameOption::QUIT):
                    {
                        running = false;
                        break;
                    }
                    
                    // Configuraciones (nombre, maximo de pokemones)
                    case static_cast<int>(PokemonGame::GameOption::CONFIG):
                    {
                        break;
                    }
                }
            }

            Common::playerName = playerOne.GetName();
            /**
             * TODO: Implementar variable global playerNameTwo y reasignar su valor
             */
            Common::playerName = playerTwo.GetName();
        }
    };
}