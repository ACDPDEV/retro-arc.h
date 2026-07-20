#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

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

#include "../BuscaminasUI.h"

namespace Buscaminas
{
    /// @brief Draws a single option box at the given index
    /// @param options Array of option labels
    /// @param optionColors Colors for each option
    /// @param index Index of the option to draw
    /// @param isSelected Whether this option is currently selected
    /// @param gridX X position of the grid
    /// @param gridY Y position of the grid
    /// @param BoxWidth Width of each box
    /// @param BoxHeight Height of each box
    /// @param Margin Margin between boxes
    /// @param optCount Number of options (3 or 4)
    inline void DrawOptionBox(
        const std::vector<std::string>& options,
        const std::vector<std::array<int, 3>>& optionColors,
        int index, bool isSelected,
        int gridX, int gridY, int BoxWidth, int BoxHeight, int Margin
    ) {
        int boxX = gridX;
        int boxY = gridY + index * (BoxHeight + Margin);
        const std::array<int, 3>& fillColor = optionColors[index];
        if (isSelected) {
            Common::PrintPrimaryBox(boxX, boxY, BoxWidth, BoxHeight, {options[index]},
                Common::FOREGROUND_DARK, Common::CURSOR, fillColor);
        } else {
            Common::PrintPrimaryBox(boxX, boxY, BoxWidth, BoxHeight, {options[index]},
                Common::FOREGROUND_DARK, fillColor, fillColor);
        }
    }

    /// @brief Main menu — title + 4 options in vertical layout (no-flicker)
    /// @return 0=Jugar, 1=Instrucciones, 2=Config, 3=Volver
    inline int MainMenuView()
    {
        const std::vector<std::string> options = {"JUGAR", "INSTRUCCIONES", "CONFIGURACIONES", "VOLVER"};
        const std::vector<std::array<int, 3>> optionColors = {
            Common::ORANGE, Common::ACCENT, Common::LIGHT_BLUE, Common::LIGHT_GREEN
        };
        const int optCount = static_cast<int>(options.size());
        int option = 0;
        int prevOption = -1;
        const int minOption = 0;
        const int maxOption = optCount - 1;

        // Font title: "BUSCAMINAS"
        std::vector<std::array<std::string, 9>> fontChars = {
            Common::FONT9_B, Common::FONT9_U, Common::FONT9_S, Common::FONT9_C,
            Common::FONT9_A, Common::FONT9_M, Common::FONT9_I, Common::FONT9_N,
            Common::FONT9_A, Common::FONT9_S
        };
        const auto titleFont = Common::ConcatFont(fontChars, 2);
        const auto titleGradient = Common::Gradient(9, Common::YELLOW, Common::ORANGE);

        // Grid positions — vertical list centered
        const int BoxWidth = Common::WIDTH_SCREEN / 3;
        const int BoxHeight = 3;
        const int Margin = 1;
        const int gridX = (Common::WIDTH_SCREEN - BoxWidth) / 2;
        const int gridY = 22;

        // ── Draw static elements ONCE (before loop) ──
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // Title
        for (int i = 0; i < 9; i++) {
            Common::DrawText(
                Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(titleFont[i]), "center"),
                2 + 2 + i, -1, -1,
                {titleFont[i]},
                titleGradient[i], Common::BACKGROUND
            );
        }

        // All option boxes (initial state)
        for (int i = 0; i < optCount; i++) {
            DrawOptionBox(options, optionColors, i, i == option,
                gridX, gridY, BoxWidth, BoxHeight, Margin);
        }

        // Bottom bar
        Common::keysHelper = {{"\u2190 \u2192 \u2191 \u2193", "Navegar"}, {"ENTER", "Seleccionar"}};
        Common::DrawBottomBar();

        // ── Input loop — only redraw changed boxes ──
        do {
            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(option, minOption, maxOption, Common::key);
            }

            // Only redraw if selection changed
            if (option != prevOption) {
                if (prevOption >= 0 && prevOption < optCount) {
                    DrawOptionBox(options, optionColors, prevOption, false,
                        gridX, gridY, BoxWidth, BoxHeight, Margin);
                }
                DrawOptionBox(options, optionColors, option, true,
                    gridX, gridY, BoxWidth, BoxHeight, Margin);
                prevOption = option;
            }

        } while (!Common::IsActionKey(Common::key));

        return option;
    }

} // namespace Buscaminas
