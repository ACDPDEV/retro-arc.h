#pragma once

// ─────────────────────────────────────────────────────────────────────────
// TictactoeUI.h — Forwarding header
// Thin header that defines shared constants and includes all view files.
// ─────────────────────────────────────────────────────────────────────────

// 1. Librerías estándar
#include <array>
#include <iostream>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../Common/Aligned.h"
#include "../../Common/Color.h"
#include "../../Common/Components/SelectPrimaryBox.h"
#include "../../Common/Consts.h"
#include "../../Common/Font.h"
#include "../../Common/Graphics.h"
#include "../../Common/Input.h"
#include "../../Common/Navigation.h"
#include "../../Common/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"

namespace Tictactoe
{
    // ── Shared Layout Constants ──

    /// @brief Tamaño del tablero lógico (13x13)
    const int TAM = 13;

    /// @brief Ancho de cada celda en caracteres
    const int CELL_W = 7;
    /// @brief Alto de cada celda en líneas
    const int CELL_H = 4;
    /// @brief Ancho visual total del tablero (3*7 + 4 bordes)
    const int BOARD_W = 25;
    /// @brief Alto visual total del tablero (1 top + 12 celdas + 2 separadores + 1 bottom)
    const int BOARD_H = 16;

    /// @brief Coordenada X centrada del tablero (25 chars)
    inline int BoardX() {
        return Common::AlignedX(0, Common::WIDTH_SCREEN, BOARD_W, "center");
    }

    /// @brief Coordenada Y centrada del tablero (16 líneas)
    inline int BoardY() {
        return Common::AlignedY(0, Common::HEIGHT_SCREEN, BOARD_H, "center");
    }

    /// @brief Coordenada X del panel de quiz (derecha del tablero)
    inline int QuizX() {
        return BoardX() + BOARD_W + 2;
    }

    /// @brief Coordenada Y del panel de quiz (alineado con el tablero)
    inline int QuizY() {
        return BoardY();
    }

    /// @brief Ancho del panel de quiz
    const int QuizW = 42;
    /// @brief Alto del panel de quiz
    const int QuizH = 14;

    /// @brief Mapea cursorPos (0-8) a fila interna del tablero (2,6,10)
    inline int cellRow(int cursorPos) {
        const int rows[3] = {2, 6, 10};
        return rows[cursorPos / 3];
    }

    /// @brief Mapea cursorPos (0-8) a columna interna del tablero (2,6,10)
    inline int cellCol(int cursorPos) {
        const int cols[3] = {2, 6, 10};
        return cols[cursorPos % 3];
    }

} // namespace Tictactoe

// ── View Files ──
// Order: ExitConfirmView before GameBoardView (GameBoardView calls ExitConfirmView)

#include "Views/MainMenuView.h"
#include "Views/InstructionsView.h"
#include "Views/ExitConfirmView.h"
#include "Views/GameBoardView.h"
#include "Views/GameOverView.h"
#include "Views/QuizPanelView.h"
