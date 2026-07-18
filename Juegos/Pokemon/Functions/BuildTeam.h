#include "../Controllers/Game.h"
#include "../Models/Player.h"
#include "../Factories/PokemonFactory.h"

namespace PokemonGame
{

    /**
     * TODO:
     * ELIMIAR ESTE ARCHIVO
     */

    /**
     * NO USAR ESTA FUNCIÓN SE VA A ELMINAR
     */
    void BuildTeam(PokemonGame::Player& player)
    {
        player.ClearTeam();
    
        while (player.TeamSize() < PokemonGame::Game::maxPokemon)
        {
            // Mostrar lista de Pokémon
    
            /**
             * TODO: Referenciar al menú de selección de pokemon
             */

            int option = 0; // ShowPokemonMenu()
    
            std::unique_ptr<PokemonGame::Pokemon> pokemon = PokemonGame::PokemonFactory::Create(option);
    
            player.AddPokemon(std::move(pokemon));
        }
    }
}