/// @file Graphics.h
/// @brief Funciones de dibujo TUI de alto nivel para cuadros (boxes) en terminal.
/// @details Proporciona DrawRawBox() (bordes personalizados crudos) y DrawBox() (estilos predefinidos vía UnicodeGlyphs.h).
///          Requiere Terminal.h (GoToXY) y UnicodeGlyphs.h (BORDERS, CORNERS).
///          No valida límites de pantalla; el llamador debe asegurar coordenadas válidas.
#pragma once

#include <array>
#include <iostream>
#include <string>

#include "Terminal.h"
#include "UnicodeGlyphs.h"

using namespace std;

/// @brief Dibuja un cuadro (box) crudo en la terminal con bordes y esquinas personalizados.
/// @param x Coordenada X de la esquina superior izquierda.
/// @param y Coordenada Y de la esquina superior izquierda.
/// @param width Ancho del cuadro en caracteres (sin contar bordes verticales).
/// @param height Alto del cuadro en líneas (sin contar bordes horizontales).
/// @param topBorder Carácter/string para borde superior horizontal.
/// @param rightBorder Carácter/string para borde derecho vertical.
/// @param bottomBorder Carácter/string para borde inferior horizontal.
/// @param leftBorder Carácter/string para borde izquierdo vertical.
/// @param topLeftCorner Carácter para esquina superior izquierda.
/// @param topRightCorner Carácter para esquina superior derecha.
/// @param BottomRightCorner Carácter para esquina inferior derecha.
/// @param BottomLeftCorner Carácter para esquina inferior izquierda.
/// @details Usa GoToXY() de Terminal.h para posicionar el cursor y escribe a cout.
///          No valida límites de pantalla; el llamador debe asegurar que quepa.
/// @note El orden de parámetros es: top, right, bottom, left (sentido horario desde arriba).
void DrawRawBox(
    int x, int y, int width, int height,
    string topBorder,
    string rightBorder,
    string bottomBorder,
    string leftBorder,
    string topLeftCorner,
    string topRightCorner,
    string BottomRightCorner,
    string BottomLeftCorner
) {
    string TopHorizontalLine;
    string BottomHorizontalLine;
    for (int i = 1; i < width; i++) {
        TopHorizontalLine += topBorder;
        BottomHorizontalLine += bottomBorder;
    }

    GoToXY(x, y);
    cout << topLeftCorner << TopHorizontalLine << topRightCorner;

    GoToXY(x, y + height);
    cout << BottomLeftCorner << BottomHorizontalLine << BottomRightCorner;

    for (int i = 1; i < height; i++) {
        GoToXY(x, y + i);         cout << leftBorder;
        GoToXY(x + width, y + i); cout << rightBorder;
    }
}

/// @brief Dibuja un cuadro usando índices de estilo predefinidos de UnicodeGlyphs.h.
/// @param x Coordenada X de la esquina superior izquierda.
/// @param y Coordenada Y de la esquina superior izquierda.
/// @param width Ancho del cuadro en caracteres.
/// @param height Alto del cuadro en líneas.
/// @param borders Índices (0-6) para [top, right, bottom, left] en BORDERS[][0/1].
///        0=vacío, 1=punteado fino, 2=punteado, 3=simple, 4=grueso, 5=doble, 6=cuadrantes.
/// @param corners Índices (0-5) para [top-left, top-right, bottom-right, bottom-left] en CORNERS[].
///        0=vacío, 1=simple, 2=grueso, 3=doble, 4=redondeado, 5=cuadrantes.
/// @details Delega en DrawRawBox() resolviendo strings desde BORDERS y CORNERS.
///          Nota: el orden de esquinas en corners[] es TL, TR, BR, BL (horario desde arriba-izq).
void DrawBox(
    int x, int y, int width, int height,
    array<unsigned, 4> borders,
    array<unsigned, 4> corners
) {
    DrawRawBox(x, y, width, height,
        BORDERS[borders[0]][0],
        BORDERS[borders[1]][1],
        BORDERS[borders[2]][2],
        BORDERS[borders[3]][3],
        CORNERS[corners[0]][0],
        CORNERS[corners[1]][1],
        CORNERS[corners[2]][2],
        CORNERS[corners[3]][3]
    );
}
