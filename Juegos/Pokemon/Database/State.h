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

} // namespace Pokemon