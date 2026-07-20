#pragma once

#include <memory>
#include <vector>
#include "Pokemon.h"
#include "Item.h"

namespace PokemonGame
{
    class Bag
    {
        private:
    
            std::vector<std::shared_ptr<PokemonGame::Item>> items;
    
        public:
    
            Bag()
            {

            }
    
            ~Bag() = default;

            void ClearBag()
            {
                items.clear();
            }
    
            void AddItem(std::shared_ptr<PokemonGame::Item> item)
            {
                items.push_back(item);
            }
            
            PokemonGame::Item* GetItemById(int id)
            {
                for (auto& item : items)
                {
                    if (item != nullptr && item->GetId() == id)
                    {
                        return item.get();
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