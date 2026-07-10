#pragma once

#include <vector>
#include "Pokemon.h"
#include "Item.h"

namespace PokemonGame
{
    class PokemonGame::Item;
    class PokemonGame::Pokemon;
    
    class Bag
    {
        private:
    
            std::vector<Item*> items;
    
        public:
    
            Bag();
    
            ~Bag();
    
            void addItem(PokemonGame::Item* item);
    
            void useItem(
                int index,
                PokemonGame::Pokemon& target);
    };
}