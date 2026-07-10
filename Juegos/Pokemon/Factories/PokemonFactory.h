#include "../Models/Pokemon.h"

namespace PokemonGame
{
    class PokemonFactory
    {
        private:
            // static int totalDbPokemon;
        public:
            static std::unique_ptr<PokemonGame::Pokemon> Create(int option)
            {
                switch (option)
                {
                    // case 0:
                    //     return std::make_unique<Pikachu>();

                    // case 1:
                    //     return std::make_unique<Charmander>();

                    // case 2:
                    //     return std::make_unique<Bulbasaur>();

                    default:
                        return nullptr;
                }
            }
    };
}