#pragma once

#include <string>
#include <vector>

namespace Pokemon {

    struct MockPokemon {
        std::string name;
        int hp;
        int maxHp;
        int spriteIndex;
    };

    struct MockItem {
        std::string name;
        std::string description;
        int quantity;
    };

    const int POKEMON_COUNT = 8;

    const MockPokemon MOCK_POKEMON[POKEMON_COUNT] = {
        {"Bulbasaur",  45, 45, 0},
        {"Charmander", 39, 39, 1},
        {"Squirtle",   44, 44, 2},
        {"Pikachu",    35, 35, 3},
        {"Psyduck",    50, 50, 4},
        {"Eevee",      55, 55, 5},
        {"Rockruff",   45, 45, 6},
        {"Chikorita",  45, 45, 7}
    };

    const int BAG_ITEM_COUNT = 4;

    const MockItem BAG_ITEMS[BAG_ITEM_COUNT] = {
        {"Pocion",       "Restaura 20 PS de un Pokemon.", 3},
        {"Super Pocion", "Restaura 50 PS de un Pokemon.", 2},
        {"Antidoto",     "Cura un estado alterado de un Pokemon.", 1},
        {"Revivir",      "Revive a un Pokemon debilitado con la mitad de sus PS.", 0}
    };

} // namespace Pokemon
