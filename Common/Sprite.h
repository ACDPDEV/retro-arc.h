/// @file Sprite.h
/// @brief Renderizado simple de sprites ASCII/UTF-8 en terminal.
/// @details DrawSprite() imprime cada línea del vector; DrawSprites() anima secuencia
///          de frames con Sleep() entre frames (ms). Requiere Linux/Terminal.h para Sleep().
///          TODO: paralelismo opcional entre frames (comentado).
#pragma once

#include "Terminal.h"
#include "UnicodeGlyphs.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// @brief Dibuja un sprite (vector de strings, una línea por fila) en la posición actual del cursor.
/// @param sprite Vector de strings, cada string = una línea del sprite.
/// @details No posiciona el cursor; imprime línea a línea con endl. El llamador debe usar GoToXY() antes si necesita posición específica.
inline void DrawSprite(int x, int y, string sprite) {
    GoToXY(x, y);
    cout << sprite;
}

/// @brief Animación simple: dibuja secuencia de sprites (frames) con delay entre frames.
/// @param sprites Vector de frames, cada frame = vector<string> (sprite).
/// @param gapTime Delay en milisegundos entre frames.
/// @details Usa Sleep() de Linux/Terminal.h (usleep en Linux, Sleep en Windows).
///          Comentado: intento de paralelismo con this_thread::sleep_for (no implementado).
///          No limpia frames anteriores; el llamador debe manejar Clear() o posicionamiento.
inline void DrawAnimatedSprite(int x, int y, vector<string> sprites, int gapTime) {
    for (int i = 0; i < sprites.size(); i++) {
        DrawSprite(x, y, sprites[i]);
        // Necesita paralelismo a veces (no implementado)
        /* if (i < sprites.size() - 1) {
            this_thread::sleep_for(chrono::milliseconds(gapTime));
        } */
        Sleep(gapTime);
    }
}

inline string repeat_pixel(int count, string c = QUADRANTS[12]) {
    string result;
    for (int i = 0; i < count; i++) {
        result += c;
    }
    return result;
}
