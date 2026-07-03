/// @file Auth.h
/// @brief Autenticación simple con reintentos limitados.
/// @details Usa Input.h para leer entrada y Consts.h para CLAVE y MAX_ATTEMPTS.
///          Key() permite hasta MAX_ATTEMPTS intentos; WrongKey() muestra mensaje final.
#pragma once
#include "Input.h"
#include "Consts.h"
#include <string>

// Este es mi cambio :)

using namespace std;

/// @brief Verifica la clave permitiendo hasta MAX_ATTEMPTS intentos
/// @return true si la clave es correcta dentro de los intentos permitidos, false si se agotan
/// @details En cada intento fallido, vuelve a leer entrada. Usa CLAVE y MAX_ATTEMPTS de Consts.h
inline bool Key() {
    string input = Input();
    for (int i = 1; i <= MAX_ATTEMPTS; i++) {
        if (input == CLAVE) {
            return true;
        }
        input = Input();
    }
    return false;
}

/// @brief Muestra mensaje de error tras agotar los intentos de clave
/// @details Imprime mensaje indicando contactar al administrador.
///          TODO: Enmarcar visualmente. Considerar mover a módulo de interfaces.
inline void WrongKey() {
    // TODO: Enmarcar
    // Esto es una interfaz
    // Considerar mover a interfaces
    cout << "Intentó 3 veces ingresar con una clave incorrecta. Comuníquese con el administrador." << endl;
}
