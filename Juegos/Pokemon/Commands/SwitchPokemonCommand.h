#pragma once

#include "Command.h"
#include "../Controllers/Battle.h"
#include "../Models/Pokemon.h"
#include "../Models/Player.h"

namespace PokemonGame
{
    class PokemonGame::Pokemon;
    
    class SwitchPokemonCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Pokemon* pokemon;
    
        public:
    
            SwitchPokemonCommand(PokemonGame::Pokemon* pokemon)
                :
                pokemon(pokemon)
            {}
    
            void Execute(
                PokemonGame::Player& affectedPlayer) override
            {
                affectedPlayer.SwitchPokemon(pokemon);
            }

            bool CanExecute(PokemonGame::Player& actor)
            {
                bool playerCanPlay = actor.CanPlay();
                bool playerHasPokemon = actor.HasPokemonWithId(pokemon->GetId());
                bool pokemonIsAlive = !pokemon->IsFainted();
                if(playerCanPlay && playerHasPokemon & pokemonIsAlive)
                    return true;
                return false;
            }
    };
}