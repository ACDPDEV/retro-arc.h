#pragma once

#include "../../Common/Input.h"
#include "../../Common/Theme.h"
#include "../../Common/Graphics.h"
#include "../../Common/Aligned.h"

namespace MainMenu {
    inline void WrongPasswordView() {
        std::string message =  "Intentó 3 veces ingresar con una clave incorrecta. Comuníquese con el administrador.";
        int messageX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(message), "center");
        int messageY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 1, "center");

        Common::HideCursor();
        Common::DrawFillRectangle(0, 0, Common::WIDTH_SCREEN, Common::HEIGHT_SCREEN, " ", Common::FOREGROUND_DARK, Common::BACKGROUND);
        Common::DrawText(messageX, messageY, -1, -1, {message}, Common::FOREGROUND_DARK, Common::BACKGROUND);
    }
}
