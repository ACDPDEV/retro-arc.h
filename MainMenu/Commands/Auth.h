/// @file Auth.h
/// @brief Autenticación simple con reintentos limitados.
/// @details Usa Input.h para leer entrada y Consts.h para CLAVE y MAX_ATTEMPTS.
///          Key() permite hasta MAX_ATTEMPTS intentos; WrongKey() muestra mensaje final.
#pragma once

#include "../../Common/Color.h"
#include "../../Common/Graphics.h"
#include "../../Common/Input.h"
#include "../../Common/Consts.h"
#include "../../Common/Linux/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/Aligned.h"
#include "../../Common/Utils.h"

#include "../Consts/Env.h"
#include "../Consts/Labels.h"
#include "../Components/InputComponent.h"

#include <string>

// Este es mi cambio :)

namespace MainMenu {

    /// @brief Verifica la clave permitiendo hasta MAX_ATTEMPTS intentos
    /// @return true si la clave es correcta dentro de los intentos permitidos, false si se agotan
    /// @details En cada intento fallido, vuelve a leer entrada. Usa CLAVE y MAX_ATTEMPTS de Consts.h

    inline bool Key(int x, int y) {
        std::string input;
        std::string message = WRONG_PASSWORD_MESSAGE;

        InputComponent(x, y, MAX_PASSWORD_LEN, 1, "", INPUT_LABEL, "", "*");
        for (int i = 1; i <= MAX_ATTEMPTS; i++) {
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
                        InputComponent(x, y, MAX_PASSWORD_LEN, 1, input, INPUT_LABEL, "", "*");
                    }
                    continue;
                }
                if (32 <= key && key <= 126 && input.size() < MAX_PASSWORD_LEN) {
                    input.push_back(static_cast<char>(key));
                    InputComponent(x, y, MAX_PASSWORD_LEN, 1, input, INPUT_LABEL, "", "*");
                }
            }
            if (input == CLAVE) {
                return true;
            } else {
                input = "";
                InputComponent(x, y, MAX_PASSWORD_LEN, 1, input, INPUT_LABEL, message, "*");
            }
        }
        return false;
    }
}
