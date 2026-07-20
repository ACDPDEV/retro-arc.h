#pragma once

// 1. Librerías estándar
#include <array>
#include <iostream>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/SelectPrimaryBox.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Variables.h"

#include "../TictactoeUI.h"

namespace Tictactoe
{
    /// @brief Draws a single option box at the given grid position
    /// @param options Array of 4 option labels
    /// @param optionColors Colors for each option box
    /// @param index Index of the option to draw (0-3)
    /// @param isSelected Whether this option is currently selected
    /// @param gridX X position of the 2x2 grid
    /// @param gridY Y position of the 2x2 grid
    /// @param slotW Width of each box
    /// @param slotH Height of each box
    inline void DrawMenuOption(
        const std::vector<std::string>& options,
        const std::vector<std::array<int, 3>>& optionColors,
        int index, bool isSelected,
        int gridX, int gridY, int slotW, int slotH
    ) {
        const int colOffsets[2] = {0, slotW + 1};
        const int rowOffsets[2] = {0, slotH + 2};
        const int col = index % 2;
        const int row = index / 2;
        int boxX = gridX + colOffsets[col];
        int boxY = gridY + rowOffsets[row];
        const std::array<int, 3>& fillColor = optionColors[index];

        if (isSelected) {
            Common::PrintPrimaryBox(boxX, boxY, slotW, slotH, {options[index]},
                Common::FOREGROUND_DARK, Common::CURSOR, fillColor);
        } else {
            Common::PrintPrimaryBox(boxX, boxY, slotW, slotH, {options[index]},
                Common::FOREGROUND_DARK, fillColor, fillColor);
        }
    }

    /// @brief Main menu — FONT9 title + 2x2 option grid with per-option colors
    /// @return 0=Original, 1=Futbol, 2=Instrucciones, 3=Salir
    inline int MainMenuView()
    {
        const std::vector<std::string> options = {"Original", "Futbol", "Instrucciones", "Salir"};
        const std::vector<std::array<int, 3>> optionColors = {
            Common::ORANGE, Common::ACCENT, Common::RED, Common::BLUE
        };
        const int optCount = static_cast<int>(options.size());
        const int minOption = 0;
        const int maxOption = optCount - 1;
        int option = 0;
        int prevOption = -1;

        // Grid layout — 2x2 centered
        const int slotW = 25;
        const int slotH = 3;
        const int gridX = Common::AlignedX(0, Common::WIDTH_SCREEN, slotW * 2 + 4, "center");
        const int gridY = 16;

        // ── Title (FONT9 "TIC TAC TOE" with gradient fade-in) ──
        std::array<std::string, 9> titleFont = Common::ConcatFont({
            Common::FONT9_T, Common::FONT9_I, Common::FONT9_C,
            Common::FONT9_BLANK,
            Common::FONT9_T, Common::FONT9_A, Common::FONT9_C,
            Common::FONT9_BLANK,
            Common::FONT9_T, Common::FONT9_O, Common::FONT9_E
        }, 2);

        std::vector<std::array<int, 3>> titleColors = Common::Gradient(9, Common::DARK_RED, Common::ACCENT);

        // ── Draw static elements ONCE (before input loop) ──
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // Title fade-in
        for (int k = 0; k < 6; k++) {
            for (int i = 0; i < static_cast<int>(titleFont.size()); i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(titleFont[i]), "center"),
                    3 + i, -1, -1, {titleFont[i]},
                    {
                        Common::BACKGROUND[0] + (titleColors[i][0] - Common::BACKGROUND[0]) * (k + 1) / 6,
                        Common::BACKGROUND[1] + (titleColors[i][1] - Common::BACKGROUND[1]) * (k + 1) / 6,
                        Common::BACKGROUND[2] + (titleColors[i][2] - Common::BACKGROUND[2]) * (k + 1) / 6
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(50);
        }

        // All option boxes (initial state)
        for (int i = 0; i < optCount; i++) {
            DrawMenuOption(options, optionColors, i, i == option,
                gridX, gridY, slotW, slotH);
        }

        // Bottom bar
        Common::keysHelper = {
            {"\u2190 \u2192 \u2191 \u2193", "Navegar"},
            {"ENTER", "Seleccionar"}
        };
        Common::DrawBottomBar();
        std::cout.flush();

        // ── Input loop — only redraw changed boxes ──
        do {
            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                // Grid-aware navigation for 2x2 layout
                int row = option / 2;
                int col = option % 2;
                if (Common::IsKeyArrowTop(Common::key) && row > 0) row--;
                else if (Common::IsKeyArrowBottom(Common::key) && row < 1) row++;
                else if (Common::IsKeyArrowLeft(Common::key) && col > 0) col--;
                else if (Common::IsKeyArrowRight(Common::key) && col < 1) col++;
                option = row * 2 + col;
            }

            // Only redraw if selection changed
            if (option != prevOption) {
                if (prevOption >= 0 && prevOption < optCount) {
                    DrawMenuOption(options, optionColors, prevOption, false,
                        gridX, gridY, slotW, slotH);
                }
                DrawMenuOption(options, optionColors, option, true,
                    gridX, gridY, slotW, slotH);
                prevOption = option;
            }
        } while (!Common::IsActionKey(Common::key));

        return option;
    }

} // namespace Tictactoe
