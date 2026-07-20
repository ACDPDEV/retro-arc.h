/// @file VirtualScreen.h
/// @brief Buffer virtual portable para doble buffer (reemplaza consola2.h Win32).
/// @details Provee struct VirtualScreen + funciones inline para:
///          init, clear, writeCell, setCursor, setColor, print, present.
///          Present() usa ANSI escapes para flush atómico a la terminal.
///          Compatible Windows/Linux sin dependencias Win32.
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Output.h"

namespace Common {

/// @brief Ancho del buffer virtual en caracteres
const int VS_WIDTH = 200;

/// @brief Alto del buffer virtual en caracteres
const int VS_HEIGHT = 60;

/// @brief Struct simple de buffer virtual (sin métodos, AGENTS.md compliant)
struct VirtualScreen {
    std::vector<std::string> buffer;
    std::vector<std::vector<int>> colors;
    int cursorX;
    int cursorY;
    int currentColor;
};

/// @brief Inicializa el buffer virtual con espacios y color por defecto
/// @param screen Referencia al struct VirtualScreen a inicializar
inline void VirtualScreenInit(VirtualScreen& screen) {
    screen.buffer.resize(VS_HEIGHT, std::string(VS_WIDTH, ' '));
    screen.colors.resize(VS_HEIGHT, std::vector<int>(VS_WIDTH, 15));
    screen.cursorX = 0;
    screen.cursorY = 0;
    screen.currentColor = 15;
}

/// @brief Limpia todo el buffer: rellena con espacios y color 15
/// @param screen Referencia al struct VirtualScreen
inline void VirtualScreenClear(VirtualScreen& screen) {
    for (int y = 0; y < VS_HEIGHT; y++) {
        for (int x = 0; x < VS_WIDTH; x++) {
            screen.buffer[y][x] = ' ';
            screen.colors[y][x] = 15;
        }
    }
}

/// @brief Escribe un caracter en una posición del buffer (bounds-checked)
/// @param screen Referencia al struct VirtualScreen
/// @param x Columna (0-indexed)
/// @param y Fila (0-indexed)
/// @param c Caracter a escribir
/// @param color Código de color (0-15)
inline void VirtualScreenWriteCell(
    VirtualScreen& screen,
    int x, int y,
    char c, int color
) {
    if (x < 0 || x >= VS_WIDTH || y < 0 || y >= VS_HEIGHT)
        return;

    screen.buffer[y][x] = c;
    screen.colors[y][x] = color;
}

/// @brief Establece la posición de escritura del cursor
/// @param screen Referencia al struct VirtualScreen
/// @param x Columna
/// @param y Fila
inline void VirtualScreenSetCursor(
    VirtualScreen& screen,
    int x, int y
) {
    screen.cursorX = x;
    screen.cursorY = y;
}

/// @brief Establece el color actual para escrituras futuras
/// @param screen Referencia al struct VirtualScreen
/// @param color Código de color (0-15)
inline void VirtualScreenSetColor(
    VirtualScreen& screen,
    int color
) {
    screen.currentColor = color;
}

/// @brief Escribe texto en la posición actual del cursor y avanza
/// @param screen Referencia al struct VirtualScreen
/// @param text Texto a escribir
inline void VirtualScreenPrint(
    VirtualScreen& screen,
    const std::string& text
) {
    for (size_t i = 0; i < text.size(); i++) {
        VirtualScreenWriteCell(
            screen,
            screen.cursorX + (int)i,
            screen.cursorY,
            text[i],
            screen.currentColor
        );
    }
    screen.cursorX += (int)text.size();
}

/// @brief Presenta el buffer completo a la terminal (flush atómico)
/// @param screen Referencia al struct VirtualScreen
/// @details Recorre cada fila, posiciona cursor con GoToXY,
///          construye string con ANSI_FG + contenido + RESET, y flush
inline void VirtualScreenPresent(VirtualScreen& screen) {
    // Win32 4-bit → ANSI SGR foreground mapping
    const int ANSI_FG_TABLE[16] = {
        30, 34, 32, 36, 31, 35, 33, 37,
        90, 94, 92, 96, 91, 95, 93, 97
    };

    for (int y = 0; y < VS_HEIGHT; y++) {
        GoToXY(0, y);

        int lastColor = -1;
        std::string line;

        for (int x = 0; x < VS_WIDTH; x++) {
            int c = screen.colors[y][x];

            if (c != lastColor) {
                int idx = c;
                if (idx < 0) idx = 0;
                if (idx > 15) idx = 15;
                line += "\033[" + std::to_string(ANSI_FG_TABLE[idx]) + "m";
                lastColor = c;
            }

            line += screen.buffer[y][x];
        }

        line += "\033[0m";
        std::cout << line;
    }

    std::cout.flush();
}

} // namespace Common
