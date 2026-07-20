#pragma once

#include <string>

namespace Pokemon {

    /// @brief Nombres de los dos jugadores (índices 0 y 1)
    inline std::string playerNames[2] = {"", ""};

    /// @brief ID del Pokemon seleccionado actualmente por cada jugador
    /// @details [0] = jugador 1, [1] = jugador 2
    inline int selectedCurrentPokemonId[2] = {0, 0};

    /// @brief Indica qué jugador está seleccionando (0 o 1)
    inline int currentSelectionPlayer = 0;

    /// @brief IDs de los Pokemon seleccionados por cada jugador (compatibilidad)
    /// @details [0] = jugador 1, [1] = jugador 2
    inline int pokemonPlayers[2] = {0, 0};

    /// @brief Nombre del Pokemon actual (para huida/victoria)
    inline std::string currentPokemonName = "";

    /// @brief Número de rondas jugadas
    inline int currentRound = 0;

    /// @brief Nombre del jugador ganador
    inline std::string winnerName = "";

    // ============================================================
    // Battle State
    // ============================================================

    /// @brief HP actual del Pokemon activo del jugador 1
    inline double battleHp1 = 0.0;

    /// @brief HP maximo del Pokemon activo del jugador 1
    inline double battleMaxHp1 = 0.0;

    /// @brief HP actual del Pokemon activo del jugador 2
    inline double battleHp2 = 0.0;

    /// @brief HP maximo del Pokemon activo del jugador 2
    inline double battleMaxHp2 = 0.0;

    /// @brief ID del Pokemon activo del jugador 1 (DB ID)
    inline int battleActivePokemonId1 = 0;

    /// @brief ID del Pokemon activo del jugador 2 (DB ID)
    inline int battleActivePokemonId2 = 0;

    /// @brief Indica si la batalla esta en curso
    inline bool battleInProgress = false;

    /// @brief Turno actual (0 = jugador 1, 1 = jugador 2)
    inline int currentTurn = 0;

} // namespace Pokemon