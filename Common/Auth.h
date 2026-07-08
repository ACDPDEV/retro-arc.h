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

/// @brief Verifica la clave permitiendo hasta MAX_ATTEMPTS intentos
/// @return true si la clave es correcta dentro de los intentos permitidos, false si se agotan
/// @details En cada intento fallido, vuelve a leer entrada. Usa CLAVE y MAX_ATTEMPTS de Consts.h
inline bool Key(int x, int y) {
    std::string input;
    std::string message = "Clave incorrecta. Intente de nuevo.";

    Common::DrawText(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::MAX_PASSWORD_LEN, "center"), y - 1, Common::MAX_PASSWORD_LEN, 1, {"Ingrese su contraseña:"}, Common::FOREGROUND, Common::BACKGROUND);
    Common::DrawFillRectangle(x, y, Common::MAX_PASSWORD_LEN, 1, " ", Common::FOREGROUND, Common::SELECTION_BACKGROUND);
    Common::ShowCursor();
    Common::GoToXY(x, y);
    for (int i = 1; i <= Common::MAX_ATTEMPTS; i++) {
        while (true) {
            int key = Common::Getch();

            if (key == -1) {
                break;
            }
            if (key == '\n') {
                break;
            }
            if (key == 127 || key == 8) {
                if (!input.empty()) {
                    input.pop_back();
                    Common::DrawText(x + static_cast<int>(input.size()), y, -1, -1, {" "}, Common::FOREGROUND, Common::SELECTION_BACKGROUND);
                    Common::GoToXY(x + static_cast<int>(input.size()), y);
                }
                continue;
            }
            if (32 <= key && key <= 126 && input.size() < Common::MAX_PASSWORD_LEN) {
                input.push_back(static_cast<char>(key));
                std::cout << "*";
            }
        }
        if (input == Common::CLAVE) {
            return true;
        } else {
            Common::DrawText(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(message), "center"), y + 1, -1, -1, {message}, {200, 150, 100}, Common::BACKGROUND);
            Common::DrawFillRectangle(x, y, static_cast<int>(input.size()), 1, " ", Common::FOREGROUND, Common::SELECTION_BACKGROUND);
            input.clear();
            Common::GoToXY(x, y);
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
    std::cout << "Intentó 3 veces ingresar con una clave incorrecta. Comuníquese con el administrador." << std::endl;
}
