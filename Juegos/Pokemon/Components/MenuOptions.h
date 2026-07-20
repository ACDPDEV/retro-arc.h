#pragma once

#include <string>
#include <vector>

namespace Pokemon {

    /// @brief Opciones del menu principal de Pokemon
    inline std::vector<std::string> OPTIONS = {"JUGAR", "INSTRUCCIONES", "CONFIGURACIONES", "VOLVER"};

    /// @brief Indice de la opcion actualmente seleccionada en el menu
    inline int OPTION = 0;

} // namespace Pokemon
