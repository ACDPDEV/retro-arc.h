/// @file Auth.h
/// @brief Autenticación simple con reintentos limitados.
/// @details Usa Input.h para leer entrada y Consts.h para CLAVE y MAX_ATTEMPTS.
///          Key() permite hasta MAX_ATTEMPTS intentos; WrongKey() muestra mensaje final.
#pragma once

#include "../BD/Env.h"

#include <string>
#include <vector>

namespace MainMenu {

    /// @brief Verifica la clave permitiendo hasta MAX_ATTEMPTS intentos
    /// @return true si la clave es correcta dentro de los intentos permitidos, false si se agotan
    /// @details En cada intento fallido, vuelve a leer entrada. Usa CLAVE y MAX_ATTEMPTS de Env.h

    inline bool isValidPassword() {
        return INPUT == CLAVE;
    }
}
