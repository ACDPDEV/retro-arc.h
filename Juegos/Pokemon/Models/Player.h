#pragma once

#include <string>
#include <vector>
#include "Bag.h"

class Pokemon;
class Bag;

class Player
{
    private:

        std::string name;

        std::vector<Pokemon*> team;

        Pokemon* activePokemon;

        Bag bag;

    public:

        Player(const std::string& name);

        ~Player();

        void addPokemon(Pokemon* pokemon);

        void switchPokemon(int index);

        Pokemon* getActivePokemon();

        Bag& getBag();
};