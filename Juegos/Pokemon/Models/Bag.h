#pragma once

#include <vector>

class Item;
class Pokemon;

class Bag
{
    private:

        std::vector<Item*> items;

    public:

        Bag();

        ~Bag();

        void addItem(Item* item);

        void useItem(
            int index,
            Pokemon& target);
};