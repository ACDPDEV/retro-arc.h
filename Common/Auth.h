#include "Input.h"
#include "Consts.h"

/// @brief Verifica la clave permitiendo hasta MAX_ATTEMPTS intentos
/// @return true si la clave es correcta dentro de los intentos permitidos, false si se agotan
/// @details En cada intento fallido, vuelve a leer entrada. Usa CLAVE y MAX_ATTEMPTS de Consts.h
bool Key() {
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
void WrongKey() {
    // TODO: Enmarcar
    // Esto es una interfaz
    // Considerar mover a interfaces
    cout << "Intentó 3 veces ingresar con una clave incorrecta. Comuníquese con el administrador." << endl;
}