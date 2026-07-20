#pragma once

#include <array>
#include <string>
#include <vector>

#include "PokemonDatabase.h"

namespace Pokemon {

    /// @brief Numero total de Pokemon disponibles en el juego
    const int POKEMON_COUNT = 8;

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

    /// @brief Builds the mock Pokemon table with hp/maxHp derived from
    ///        PokemonDb::POKEMON_SPECIES_DB (REQ-4.5: single source of truth for stats).
    ///        `name` and `spriteIndex` stay as literals — they already match the DB and
    ///        aren't gameplay-affecting stats.
    inline std::array<MockPokemon, POKEMON_COUNT> BuildMockPokemonTable() {
        struct Entry { std::string name; int spriteIndex; };
        const std::array<Entry, POKEMON_COUNT> entries = {{
            {"Bulbasaur",  0},
            {"Charmander", 1},
            {"Squirtle",   2},
            {"Pikachu",    3},
            {"Psyduck",    4},
            {"Eevee",      5},
            {"Rockruff",   6},
            {"Chikorita",  7}
        }};

        std::array<MockPokemon, POKEMON_COUNT> table{};
        for (int i = 0; i < POKEMON_COUNT; ++i) {
            int dbId = MockToDbId(i);
            int baseHp = (dbId >= 1)
                ? static_cast<int>(PokemonDb::POKEMON_SPECIES_DB[dbId - 1].GetBaseHp())
                : 0;
            table[i] = MockPokemon{entries[i].name, baseHp, baseHp, entries[i].spriteIndex};
        }
        return table;
    }

    inline const std::array<MockPokemon, POKEMON_COUNT> MOCK_POKEMON = BuildMockPokemonTable();

    const int BAG_ITEM_COUNT = 4;

    const MockItem BAG_ITEMS[BAG_ITEM_COUNT] = {
        {"Pocion",       "Restaura 20 PS de un Pokemon.", 3},
        {"Super Pocion", "Restaura 50 PS de un Pokemon.", 2},
        {"Antidoto",     "Cura un estado alterado de un Pokemon.", 1},
        {"Revivir",      "Revive a un Pokemon debilitado con la mitad de sus PS.", 0}
    };

} // namespace Pokemon
