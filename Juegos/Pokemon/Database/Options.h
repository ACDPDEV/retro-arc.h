#pragma once

namespace Pokemon {

    /// @brief ID del Pokemon seleccionado actualmente (persiste entre vistas)
    inline int selectedCurrentPokemonId = 0;

    /// @brief Indica que jugador esta seleccionando (0 o 1)
    inline int currentSelectionPlayer = 0;

    /// @brief IDs de los Pokemon seleccionados por cada jugador
    /// @details [0] = jugador 1, [1] = jugador 2
    inline int pokemonPlayers[2] = {0, 0};

} // namespace Pokemon
