#pragma once

// ─────────────────────────────────────────────────────────────────────────
// BuscaminasUI.h — Forwarding header
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
#include "../../Common/Components/BottomBar.h"
#include "../../Common/Consts.h"
#include "../../Common/Font.h"
#include "../../Common/Graphics.h"
#include "../../Common/Input.h"
#include "../../Common/Navigation.h"
#include "../../Common/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"
#include "../../Common/Utils.h"
#include "../../Common/Variables.h"
#include "BuscaminasService.h"

namespace Buscaminas
{
    // ── Shared Layout Constants ──

    /// @brief Y-offset of the HUD text row
    const int HUD_Y = 2;

    /// @brief Width of each board cell in characters (was 2, now 3)
    const int CELL_WIDTH = 3;

    /// @brief Colors for revealed number cells 1-8
    const std::array<std::array<int, 3>, 8> NUMBER_COLORS = {{
        Common::BLUE,             // 1
        Common::LIGHT_GREEN,       // 2
        Common::RED,               // 3
        Common::DARK_RED,          // 4
        {128, 0, 128},            // 5 — purple (not in Theme.h)
        Common::LIGHT_BLUE,        // 6
        Common::FOREGROUND_DARK,   // 7
        Common::GRAY               // 8
    }};

    // ── Dynamic Layout Functions ──

    /// @brief Computes X position for board centering
    /// @param cols Number of board columns
    /// @return X coordinate for the left edge of the board
    inline int BoardX(int cols) {
        const int boardWidth = cols * CELL_WIDTH;
        return (Common::WIDTH_SCREEN - boardWidth) / 2;
    }

    /// @brief Computes Y position for board centering (below HUD)
    /// @param rows Number of board rows (unused, kept for API consistency)
    /// @return Y coordinate for the top edge of the board
    inline int BoardY(int /*rows*/) {
        return HUD_Y + 3;
    }

} // namespace Buscaminas

// ── View Files ──
// Order: ExitConfirmView before GameBoardView (GameBoardView calls ExitConfirmView)

#include "Views/MainMenuView.h"
#include "Views/LevelSelectView.h"
#include "Views/ExitConfirmView.h"
#include "Views/GameBoardView.h"
#include "Views/GameOverView.h"
#include "Views/InstructionsView.h"
#include "Views/ConfigView.h"
