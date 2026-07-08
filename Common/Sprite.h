/// @file Sprite.h
/// @brief Renderizado simple de sprites ASCII/UTF-8 en terminal.
/// @details DrawSprite() imprime un sprite (string ya renderizado, con sus saltos de
///          línea internos); DrawAnimatedSprite() anima una secuencia de frames con
///          Sleep() entre frames (ms). Requiere Linux/Terminal.h para Sleep().
///          TODO: paralelismo opcional entre frames (comentado).
#pragma once
#include "Color.h"
#include "Graphics.h"
#include "Terminal.h"
#include "UnicodeGlyphs.h"
#include <iostream>
#include <string>
#include <vector>
/// @brief Dibuja un sprite (string ya renderizado, p. ej. una constante generada
///        por el pipeline de assets) en la posición actual del cursor.
/// @param sprite String completo del sprite, con sus propios saltos de línea.
/// @details No posiciona el cursor más que una vez; imprime con cout <<. El llamador
///          debe usar GoToXY() antes si necesita una posición específica.
inline void DrawSprite(int x, int y, const std::vector<std::string>& sprite) {
    for (int i = 0; i < sprite.size(); i++) {
        Common::GoToXY(x, y + i);
        Common::DrawText(x, y, -1, -1, sprite, Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);
    }
}

/// @brief Animación simple: dibuja una secuencia de sprites (frames) con delay entre frames.
/// @param sprites Vector de frames; cada frame ya es un string completo (ver DrawSprite).
/// @param gapTime Delay en milisegundos entre frames.
/// @details Usa Sleep() de Linux/Terminal.h (usleep en Linux, Sleep en Windows).
///          No hace Sleep() después del último frame.
///          No limpia frames anteriores; el llamador debe manejar Clear() o posicionamiento.
inline void DrawAnimatedSprite(int x, int y, const std::vector<std::vector<std::string>>& sprites, int gapTime, int iterations) {
    for (int i = 1; i <= iterations; i++) {
        for (int i = 0; i < sprites.size(); i++) {
            DrawSprite(x, y, sprites[i]);
            if (i + 1 < sprites.size()) {
                Common::Sleep(gapTime);
            }
        }
    }
}
