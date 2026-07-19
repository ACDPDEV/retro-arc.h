#pragma once

#include <array>
#include <vector>
#include <string>

#include "../Input.h"
#include "../Graphics.h"
#include "../Utils.h"
#include "../Color.h"
#include "../Variables.h"

namespace Common {

    /// @brief Renderiza un selector vertical usando estilo PrintPrimaryBox (sin interacción)
    /// @param x Coordenada X del borde izquierdo
    /// @param y Coordenada Y del primer slot
    /// @param options Vector de opciones a mostrar
    /// @param selectedOption Índice de la opción seleccionada (0-based)
    /// @param borderColor Color de borde {R,G,B}
    /// @param fillColor Color de relleno {R,G,B}
    /// @param selectedColor Color de relleno de opción seleccionada {R,G,B}
    /// @param textColor Color del texto {R,G,B}
    /// @param slotWidth Ancho fijo de cada slot
    /// @param slotHeight Alto fijo del contenido de cada slot (sin bordes)
    inline void StaticSelectPrimaryBox1D(
        int x, int y,
        std::vector<std::string>& options,
        int selectedOption,
        std::array<int, 3> borderColor,
        std::array<int, 3> fillColor,
        std::array<int, 3> selectedColor,
        std::array<int, 3> textColor,
        int slotWidth,
        int slotHeight
    ) {
        for (int i = 0; i < static_cast<int>(options.size()); i++) {
            const int slotY = y + i * (slotHeight + 2);
            const std::array<int, 3>& bg = (i == selectedOption) ? selectedColor : fillColor;

            PrintPrimaryBox(
                x, slotY,
                slotWidth, slotHeight,
                {options[i]},
                textColor, borderColor, bg
            );
        }
    }

    /// @brief Selector vertical con estilo PrintPrimaryBox (bloquea hasta ENTER)
    /// @param x Coordenada X del borde izquierdo
    /// @param y Coordenada Y del primer slot
    /// @param options Vector de opciones a mostrar
    /// @param selectedOption Índice seleccionado (referencia, se modifica con flechas)
    /// @param borderColor Color de borde {R,G,B}
    /// @param fillColor Color de relleno {R,G,B}
    /// @param selectedColor Color de relleno de opción seleccionada {R,G,B}
    /// @param textColor Color del texto {R,G,B}
    /// @param slotWidth Ancho fijo de cada slot
    /// @param slotHeight Alto fijo del contenido de cada slot (sin bordes)
    inline void SelectPrimaryBox1D(
        int x, int y,
        std::vector<std::string>& options,
        int& selectedOption,
        std::array<int, 3> borderColor,
        std::array<int, 3> fillColor,
        std::array<int, 3> selectedColor,
        std::array<int, 3> textColor,
        int slotWidth,
        int slotHeight
    ) {
        while (true) {
            StaticSelectPrimaryBox1D(
                x, y,
                options, selectedOption,
                borderColor, fillColor, selectedColor,
                textColor,
                slotWidth, slotHeight
            );

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                break;
            } else if (Common::key == Common::KEY_ARROW_TOP) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (Common::key == Common::KEY_ARROW_BOTTOM) {
                selectedOption = (selectedOption + 1) % options.size();
            }
        }
    }

    /// @brief Renderiza un selector 2×2 usando estilo PrintPrimaryBox (sin interacción)
    /// @param x Coordenada X de la esquina superior izquierda del grid
    /// @param y Coordenada Y de la esquina superior izquierda del grid
    /// @param options Array de 4 opciones (layout: [0][1] / [2][3])
    /// @param selectedOption Índice de la opción seleccionada (0-3)
    /// @param borderColor Color de borde {R,G,B}
    /// @param fillColor Color de relleno {R,G,B}
    /// @param selectedColor Color de relleno de opción seleccionada {R,G,B}
    /// @param textColor Color del texto {R,G,B}
    /// @param slotWidth Ancho de cada celda
    /// @param slotHeight Alto del contenido de cada celda (sin bordes)
    inline void StaticSelectPrimaryBox2D(
        int x, int y,
        std::array<std::string, 4>& options,
        int selectedOption,
        std::array<int, 3> borderColor,
        std::array<int, 3> fillColor,
        std::array<int, 3> selectedColor,
        std::array<int, 3> textColor,
        int slotWidth,
        int slotHeight
    ) {
        const int colOffsets[2] = {0, slotWidth + 1};
        const int rowOffsets[2] = {0, slotHeight + 2};

        for (int i = 0; i < 4; i++) {
            const int col = i % 2;
            const int row = i / 2;
            const int slotX = x + colOffsets[col];
            const int slotY = y + rowOffsets[row];
            const std::array<int, 3>& bg = (i == selectedOption) ? selectedColor : fillColor;

            PrintPrimaryBox(
                slotX, slotY,
                slotWidth, slotHeight,
                {options[i]},
                textColor, borderColor, bg
            );
        }
    }

    /// @brief Selector 2×2 con estilo PrintPrimaryBox (bloquea hasta ENTER)
    /// @param x Coordenada X de la esquina superior izquierda del grid
    /// @param y Coordenada Y de la esquina superior izquierda del grid
    /// @param options Array de 4 opciones (layout: [0][1] / [2][3])
    /// @param selectedOption Índice seleccionado (0-3, referencia)
    /// @param borderColor Color de borde {R,G,B}
    /// @param fillColor Color de relleno {R,G,B}
    /// @param selectedColor Color de relleno de opción seleccionada {R,G,B}
    /// @param textColor Color del texto {R,G,B}
    /// @param slotWidth Ancho de cada celda
    /// @param slotHeight Alto del contenido de cada celda (sin bordes)
    inline void SelectPrimaryBox2D(
        int x, int y,
        std::array<std::string, 4>& options,
        int& selectedOption,
        std::array<int, 3> borderColor,
        std::array<int, 3> fillColor,
        std::array<int, 3> selectedColor,
        std::array<int, 3> textColor,
        int slotWidth,
        int slotHeight
    ) {
        while (true) {
            StaticSelectPrimaryBox2D(
                x, y,
                options, selectedOption,
                borderColor, fillColor, selectedColor,
                textColor,
                slotWidth, slotHeight
            );

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                break;
            }

            const int col = selectedOption % 2;
            const int row = selectedOption / 2;

            if (Common::key == Common::KEY_ARROW_TOP) {
                selectedOption = ((row - 1 + 2) % 2) * 2 + col;
            } else if (Common::key == Common::KEY_ARROW_BOTTOM) {
                selectedOption = ((row + 1) % 2) * 2 + col;
            } else if (Common::key == Common::KEY_ARROW_LEFT) {
                selectedOption = row * 2 + (col - 1 + 2) % 2;
            } else if (Common::key == Common::KEY_ARROW_RIGHT) {
                selectedOption = row * 2 + (col + 1) % 2;
            }
        }
    }

}
