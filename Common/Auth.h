/// @file Auth.h
/// @brief Autenticación simple con reintentos limitados.
/// @details Usa Input.h para leer entrada y Consts.h para CLAVE y MAX_ATTEMPTS.
///          Key() permite hasta MAX_ATTEMPTS intentos; WrongKey() muestra mensaje final.
#pragma once
#include "Color.h"
#include "Graphics.h"
#include "Input.h"
#include "Consts.h"
#include "Linux/Terminal.h"
#include "Theme.h"
#include "Aligned.h"
#include "Utils.h"
#include <string>

// Este es mi cambio :)

using namespace std;

/// @brief Verifica la clave permitiendo hasta MAX_ATTEMPTS intentos
/// @return true si la clave es correcta dentro de los intentos permitidos, false si se agotan
/// @details En cada intento fallido, vuelve a leer entrada. Usa CLAVE y MAX_ATTEMPTS de Consts.h
inline bool Key(int x, int y) {
    string input;
    string message = "Clave incorrecta. Intente de nuevo.";

    DrawText(AlignedX(0, WIDTH_SCREEN, MAX_PASSWORD_LEN, "center"), y - 1, MAX_PASSWORD_LEN, 1, {"Ingrese su contraseña:"}, FOREGROUND, BACKGROUND);
    DrawFillRectangle(x, y, MAX_PASSWORD_LEN, 1, " ", FOREGROUND, SELECTION_BACKGROUND);
    ShowCursor();
    GoToXY(x, y);
    for (int i = 1; i <= MAX_ATTEMPTS; i++) {
        while (true) {
            int key = Getch();

            if (key == -1) {
                break;
            }
            if (key == '\n') {
                break;
            }
            if (key == 127 || key == 8) {
                if (!input.empty()) {
                    input.pop_back();
                    DrawText(x + static_cast<int>(input.size()), y, -1, -1, {" "}, FOREGROUND, SELECTION_BACKGROUND);
                    GoToXY(x + static_cast<int>(input.size()), y);
                }
                continue;
            }
            if (32 <= key && key <= 126 && input.size() < MAX_PASSWORD_LEN) {
                input.push_back(static_cast<char>(key));
                cout << "*";
            }
        }
        if (input == CLAVE) {
            return true;
        } else {
            DrawText(AlignedX(0, WIDTH_SCREEN, Length(message), "center"), y + 1, -1, -1, {message}, {200, 150, 100}, BACKGROUND);
            DrawFillRectangle(x, y, static_cast<int>(input.size()), 1, " ", FOREGROUND, SELECTION_BACKGROUND);
            input.clear();
            GoToXY(x, y);
        }
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
