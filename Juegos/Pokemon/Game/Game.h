#pragma once
// #include <iostream>
#include <string>
#include <memory>
#include "Battle.h"


namespace PokemonGame
{
    class Game
    {
    public:
    
        void start()
        {
            std::string playerName1 = "Jugador 1";
            std::string playerName2 = "Jugador 2";
            bool running = true;
            while (running)
            {
                // Invocar a la clase o función que contiene la lógica de vista para seleccionar la opción. 
                // return : Debe devolver la opción
                int option = 0;

                switch (option)
                {
                    case 0:
                    {
                        auto player1 = std::make_unique<PokemonGame::Player>(playerName1);
                        auto player2 = std::make_unique<PokemonGame::Player>(playerName2);
                        
                        auto battle = std::make_unique<PokemonGame::Battle>(player1, player2);

                        battle->Play();
                        break;
                    }

                    case 1:
                    {
                        running = false;
                        break;
                    }
                }
            }
        }
    };
}