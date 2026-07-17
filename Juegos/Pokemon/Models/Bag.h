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
    
            Bag()
            {

            }
    
            ~Bag() = default;
    
            void addItem(PokemonGame::Item* item);
    
            void useItem(
                int index,
                PokemonGame::Pokemon& target);
            
            PokemonGame::Item* GetItemById(int id)
            {
                for (PokemonGame::Item* item : items)
                {
                    if (item != nullptr && item->GetId() == id)
                    {
                        return item;
                    }
                }
                
                return nullptr;
            }

            bool HasItemWithId(int itemId)
            {
                for (const auto& itemPtr : items)
                {
                    if (itemPtr != nullptr && itemPtr->GetId() == itemId)
                    {
                        return true;
                    }
                }
                
                return false;
            }
    };
}