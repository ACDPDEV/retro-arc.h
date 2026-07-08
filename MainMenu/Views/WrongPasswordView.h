#pragma once

#include "../../Common/Input.h"
#include "../../Common/Theme.h"
#include "../../Common/Graphics.h"
#include "../../Common/Aligned.h"

inline void WrongPasswordView() {
    string message =  "Intentó 3 veces ingresar con una clave incorrecta. Comuníquese con el administrador.";
    int messageX = AlignedX(0, WIDTH_SCREEN, Length(message), "center");
    int messageY = AlignedY(0, HEIGHT_SCREEN, 1, "center");

    HideCursor();
    DrawFillRectangle(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN, " ", FOREGROUND, BACKGROUND);
    DrawText(messageX, messageY, -1, -1, {message}, FOREGROUND, BACKGROUND);
}
