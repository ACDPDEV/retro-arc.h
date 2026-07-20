#pragma once
#include <vector>
#include "Classes/PokemonSpecie.h"

namespace PokemonDb {

    const std::vector<PokemonSpecie> POKEMON_SPECIES_DB = {
        // 1. Psyduck (Equilibrado)
        PokemonSpecie(1, "Psyduck", PokemonGame::PokemonType::AGUA, 75.0, 6.0, {
            {"Pistola Agua", PokemonGame::PokemonType::AGUA, 18.0, 100.0},
            {"Arañazo", PokemonGame::PokemonType::NORMAL, 23.0, 100.0},
            {"Confusión", PokemonGame::PokemonType::PSIQUICO, 22.0, 100.0},
            {"Cabezazo Zen", PokemonGame::PokemonType::PSIQUICO, 16.0, 90.0}
        }),

        // 2. Pikachu (Ofensivo / Frágil)
        PokemonSpecie(2, "Pikachu", PokemonGame::PokemonType::ELECTRICO, 55.0, 4.0, {
            {"Impactrueno", PokemonGame::PokemonType::ELECTRICO, 23.0, 100.0},
            {"Rayo", PokemonGame::PokemonType::ELECTRICO, 16.0, 100.0},
            {"Trueno", PokemonGame::PokemonType::ELECTRICO, 16.0, 70.0},
            {"Ataque Rápido", PokemonGame::PokemonType::NORMAL, 18.0, 100.0}
        }),

        // 3. Chikorita (Tanque Defensivo)
        PokemonSpecie(3, "Chikorita", PokemonGame::PokemonType::PLANTA, 90.0, 11.0, {
            {"Hoja Afilada", PokemonGame::PokemonType::PLANTA, 16.0, 95.0},
            {"Látigo Cepa", PokemonGame::PokemonType::PLANTA, 15.0, 100.0},
            {"Placaje", PokemonGame::PokemonType::NORMAL, 26.0, 100.0},
            {"Tormenta Floral", PokemonGame::PokemonType::PLANTA, 20.0, 90.0}
        }),

        // 4. Rockruff (Ofensivo / Equilibrado)
        PokemonSpecie(4, "Rockruff", PokemonGame::PokemonType::ROCA, 65.0, 5.0, {
            {"Lanzarrocas", PokemonGame::PokemonType::ROCA, 24.0, 90.0},
            {"Avalancha", PokemonGame::PokemonType::ROCA, 25.0, 90.0},
            {"Mordisco", PokemonGame::PokemonType::SINIESTRO, 15.0, 100.0},
            {"Triturar", PokemonGame::PokemonType::SINIESTRO, 22.0, 100.0}
        }),

        // 5. Bulbasaur (Equilibrado / Tipo Único Planta)
        PokemonSpecie(5, "Bulbasaur", PokemonGame::PokemonType::PLANTA, 72.0, 7.0, {
            {"Látigo Cepa", PokemonGame::PokemonType::PLANTA, 25.0, 100.0},
            {"Hoja Afilada", PokemonGame::PokemonType::PLANTA, 21.0, 95.0},
            {"Bomba Lodo", PokemonGame::PokemonType::VENENO, 15.0, 100.0},
            {"Rayo Solar", PokemonGame::PokemonType::PLANTA, 15.0, 100.0}
        }),

        // 6. Squirtle (Tanque Defensivo)
        PokemonSpecie(6, "Squirtle", PokemonGame::PokemonType::AGUA, 88.0, 12.0, {
            {"Pistola Agua", PokemonGame::PokemonType::AGUA, 25.0, 100.0},
            {"Hidrobomba", PokemonGame::PokemonType::AGUA, 20.0, 80.0},
            {"Placaje", PokemonGame::PokemonType::NORMAL, 17.0, 100.0},
            {"Cabezazo", PokemonGame::PokemonType::NORMAL, 26.0, 100.0}
        }),

        // 7. Eevee (Equilibrado)
        PokemonSpecie(7, "Eevee", PokemonGame::PokemonType::NORMAL, 78.0, 6.0, {
            {"Placaje", PokemonGame::PokemonType::NORMAL, 18.0, 100.0},
            {"Ataque Rápido", PokemonGame::PokemonType::NORMAL, 22.0, 100.0},
            {"Mordisco", PokemonGame::PokemonType::SINIESTRO, 21.0, 100.0},
            {"Derribo", PokemonGame::PokemonType::NORMAL, 15.0, 85.0}
        }),

        // 8. Charmander (Ofensivo / Frágil)
        PokemonSpecie(8, "Charmander", PokemonGame::PokemonType::FUEGO, 58.0, 4.5, {
            {"Ascuas", PokemonGame::PokemonType::FUEGO, 24.0, 100.0},
            {"Arañazo", PokemonGame::PokemonType::NORMAL, 24.0, 100.0},
            {"Colmillo Ígneo", PokemonGame::PokemonType::FUEGO, 18.0, 95.0},
            {"Llamarada", PokemonGame::PokemonType::FUEGO, 15.0, 85.0}
        })
    };
}

namespace Pokemon {

    /// @brief Hardcoded mock-index to DB-ID mapping
    /// @details mockToDbId[mockIndex] = dbSpeciesId
    /// Mock indices: 0=Bulbasaur, 1=Charmander, 2=Squirtle, 3=Pikachu,
    ///              4=Psyduck, 5=Eevee, 6=Rockruff, 7=Chikorita
    /// @note Moved here from Bridge/PokemonBridge.h (REQ-4.5) so both the bridge and
    ///       MockData.h can share one mapping instead of duplicating it.
    const int mockToDbId[8] = {5, 8, 6, 2, 1, 7, 4, 3};

    /// @brief Returns the DB species ID for a given mock index
    /// @param mockIndex Index in the MOCK_POKEMON array (0-7)
    /// @return DB species ID, or -1 if out of range
    inline int MockToDbId(int mockIndex) {
        if (mockIndex < 0 || mockIndex >= 8) {
            return -1;
        }
        return mockToDbId[mockIndex];
    }
}