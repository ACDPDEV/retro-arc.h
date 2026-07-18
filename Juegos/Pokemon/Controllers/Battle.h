#pragma once
#include <memory>
#include "Game.h"
#include "TurnController.h"
#include "Round.h"
#include "../Factories/PokemonFactory.h"

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

            /**
             * @brief Permite que el jugador seleccione los pokemon de su equipo
             * @return true Cuando el jugador completa su equipo
             * @return false Cuando el jugador elije salir
             */
            bool BuildTeam(PokemonGame::Player& player)
            {
                player.ClearTeam();
            
                while (player.TeamSize() < PokemonGame::Game::maxPokemon)
                {
                    // Mostrar lista de Pokémon
            
                    /**
                     * TODO: Referenciar al menú de selección de pokemon
                     */

                    int pokemonId = 0; // ShowPokemonMenu()

                    if(pokemonId == -1)
                    {
                        return false;
                    }
            
                    std::unique_ptr<PokemonGame::Pokemon> pokemon = PokemonGame::PokemonFactory::Create(pokemonId);
            
                    player.AddPokemon(std::move(pokemon));
                }

                return true;
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