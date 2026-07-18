#pragma once

#include <memory>
#include "../Models/Pokemon.h"

namespace PokemonGame
{
    class PokemonFactory
    {
        private:
            // static int totalDbPokemon;
        public:
            static std::unique_ptr<PokemonGame::Pokemon> Create(int pokemonId)
            {
                return nullptr;
            }
    };
}