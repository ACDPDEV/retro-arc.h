/// @file Graphics.h
/// @brief Funciones de dibujo TUI de alto nivel para cuadros (boxes) en terminal.
/// @details Proporciona DrawRawBox() (bordes personalizados crudos) y DrawBox() (estilos predefinidos vía UnicodeGlyphs.h).
///          Requiere Terminal.h (GoToXY) y UnicodeGlyphs.h (BORDERS, CORNERS).
///          No valida límites de pantalla; el llamador debe asegurar coordenadas válidas.
#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "Consts.h"
#include "Terminal.h"
#include "Theme.h"
#include "UnicodeGlyphs.h"
#include "Color.h"
#include "Utils.h"
#include "Aligned.h"

namespace Common
{
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
    inline void DrawRawBox(
        int x, int y, int width, int height,
        std::string topBorder,
        std::string rightBorder,
        std::string bottomBorder,
        std::string leftBorder,
        std::string topLeftCorner,
        std::string topRightCorner,
        std::string BottomRightCorner,
        std::string BottomLeftCorner
    ) {
        std::string TopHorizontalLine;
        std::string BottomHorizontalLine;
        for (int i = 1; i < width; i++) {
            TopHorizontalLine += topBorder;
            BottomHorizontalLine += bottomBorder;
        }

        GoToXY(x, y);
        std::cout << topLeftCorner << TopHorizontalLine << topRightCorner;

        GoToXY(x, y + height);
        std::cout << BottomLeftCorner << BottomHorizontalLine << BottomRightCorner;

        for (int i = 1; i < height; i++) {
            GoToXY(x, y + i);         std::cout << leftBorder;
            GoToXY(x + width, y + i); std::cout << rightBorder;
        }

        std::cout.flush();
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
    inline void DrawBox(
        int x, int y, int width, int height,
        std::array<unsigned, 4> borders,
        std::array<unsigned, 4> corners
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

    /// @brief Dibuja una línea horizontal con extremos y centro personalizados.
    /// @param x Coordenada X inicial.
    /// @param y Coordenada Y.
    /// @param length Longitud total en caracteres (incluye extremos).
    /// @param left Carácter para el extremo izquierdo.
    /// @param center Carácter para el relleno central (repetido length-2 veces).
    /// @param right Carácter para el extremo derecho.
    /// @details Construye la línea completa y la imprime en una sola llamada a cout.
    inline void DrawRawHorizontalLine(
        int x, int y, int length,
        std::string left,
        std::string center,
        std::string right
    ) {
        std::string line = left;
        for (int i = 1; i < length; i++) {
            line += center;
        }
        line += right;
        GoToXY(x, y); std::cout << line;

        std::cout.flush();
    }

    /// @brief Dibuja una línea vertical con extremos y centro personalizados.
    /// @param x Coordenada X.
    /// @param y Coordenada Y inicial.
    /// @param length Longitud total en líneas (incluye extremos).
    /// @param top Carácter para el extremo superior.
    /// @param center Carácter para el relleno central (repetido length-2 veces).
    /// @param bottom Carácter para el extremo inferior.
    /// @details Imprime carácter a carácter moviendo el cursor con GoToXY().
    inline void DrawRawVerticalLine(
        int x, int y, int length,
        std::string top,
        std::string center,
        std::string bottom
    ) {
        GoToXY(x, y); std::cout << top;
        for (int i = 1; i < length; i++) {
            GoToXY(x, y + i); std::cout << center;
        }
        GoToXY(x, y + length); std::cout << bottom;

        std::cout.flush();
    }

    /// @brief Dibuja un rectángulo relleno con color.
    /// @param x Coordenada X de la esquina superior izquierda.
    /// @param y Coordenada Y de la esquina superior izquierda.
    /// @param width Ancho en caracteres.
    /// @param height Alto en líneas.
    /// @param fill Carácter/string de relleno (ej: "█", "░", " ").
    /// @param foreground Color de texto {R,G,B} 0-255 o TRANSPARENT (-1,-1,-1).
    /// @param background Color de fondo {R,G,B} 0-255 o TRANSPARENT (-1,-1,-1).
    /// @details Usa Color.h para generar escape ANSI. Imprime línea por línea con GoToXY().
    ///          No borra contenido previo fuera del rectángulo.
    inline void DrawFillRectangle(
        int x, int y, int width, int height,
        std::string fill,
        std::array<int, 3> foreground,
        std::array<int, 3> background
    ) {
        std::string line = fill;
        for (int i = 1; i < width; i++) {
            line += fill;
        }
        for (int i = 0; i < height; i++) {
            GoToXY(x, y + i); std::cout << Common::Color(foreground, background) << line;
        }

        std::cout.flush();
    }


    inline void DrawText(
        int x, int y,
        int width, int height,
        std::vector<std::string> text,
        std::array<int, 3> foreground,
        std::array<int, 3> background
    ) {
        for (size_t i = 0; i < text.size() && (static_cast<int>(i) < height || height == -1); i++) {
            if (Length(text[i]) > width && width != -1) {
                std::vector<std::string> lines = CutString(text[i], width);
                for (size_t j = 0; j < lines.size(); j++) {
                    GoToXY(x, y + static_cast<int>(i) + static_cast<int>(j)); std::cout << Common::Color(foreground, background) << lines[j];
                }
            } else {
                GoToXY(x, y + static_cast<int>(i)); std::cout << Common::Color(foreground, background) << text[i];
            }
        }

        std::cout.flush();
    }

    inline void DrawBackground() {
        DrawFillRectangle(
            0, 0,
            WIDTH_SCREEN, HEIGHT_SCREEN,
            EMPTY_BLOCK,
            FOREGROUND_DARK, BACKGROUND
        );
    }



    inline void PrintPrimaryBox(int x, int y, int width, int height, std::string text, std::array<int, 3> textColor, std::array<int, 3> borderColor, std::array<int, 3> fillColor)
    {
        const int textX = AlignedX(x, width, text.length(), "center");
        const int textY = AlignedY(y, height, 1, "center");

        Common::DrawFillRectangle(x, y - 1, width, 1, Common::LOWER_HALF_BLOCK, borderColor, {-1, -1, -1}); // borde superior
        Common::DrawFillRectangle(x, y + height, width, 1, Common::UPPER_HALF_BLOCK, borderColor, {-1, -1, -1}); // borde inferior
        Common::DrawFillRectangle(x, y, width, height, Common::FULL_BLOCK, borderColor, {-1, -1, -1}); // bordes de los costados
        Common::DrawFillRectangle(x + 1, y, width - 2, height, Common::FULL_BLOCK, fillColor, {-1, -1, -1}); // relleno del recuadro

        Common::DrawText(
            textX, textY,
            width, height,
            {text},
            textColor, fillColor);

    }
}
