#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../../../Common/Variables.h"

#include "../BuscaminasUI.h"

namespace Buscaminas
{
    /// @brief Draws a single level option box
    inline void DrawLevelBox(
        const std::vector<std::string>& levels,
        const std::vector<std::string>& levelDescs,
        const std::vector<std::array<int, 3>>& levelColors,
        int index, bool isSelected,
        int boxX, int boxStartY, int boxWidth, int BoxHeight, int boxGap
    ) {
        int y = boxStartY + index * boxGap;
        std::string boxText = levels[index] + "  " + levelDescs[index];
        const std::array<int, 3>& fillColor = levelColors[index];
        if (isSelected) {
            Common::PrintPrimaryBox(boxX, y, boxWidth, BoxHeight, {boxText},
                Common::FOREGROUND_DARK, Common::CURSOR, fillColor);
        } else {
            Common::PrintPrimaryBox(boxX, y, boxWidth, BoxHeight, {boxText},
                Common::FOREGROUND_DARK, fillColor, fillColor);
        }
    }

    /// @brief Difficulty selection screen (no-flicker)
    /// @return 0=Easy, 1=Intermediate, 2=Hard, -1=Back (Esc)
    inline int LevelSelectView()
    {
        const std::vector<std::string> levels = {"FACIL", "INTERMEDIO", "DIFICIL"};
        const std::vector<std::string> levelDescs = {"9x9  -  ~4 minas", "16x16  -  ~21 minas", "16x30  -  ~60 minas"};
        const std::vector<std::array<int, 3>> levelColors = {
            Common::LIGHT_GREEN, Common::ACCENT, Common::RED
        };
        const int optCount = static_cast<int>(levels.size());
        int option = 0;
        int prevOption = -1;
        const int minOption = 0;
        const int maxOption = optCount - 1;

        const int boxWidth = 40;
        const int BoxHeight = 3;
        const int Margin = 2;
        const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
        const int boxStartY = 12;
        const int boxGap = BoxHeight + Margin;

        // ── Draw static elements ONCE ──
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // Title
        const std::string title = "SELECCIONA DIFICULTAD";
        Common::DrawText(
            Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title), "center"),
            HUD_Y + 4, -1, -1,
            {title},
            Common::ACCENT, Common::BACKGROUND
        );

        // All level boxes (initial state)
        for (int i = 0; i < optCount; i++) {
            DrawLevelBox(levels, levelDescs, levelColors, i, i == option,
                boxX, boxStartY, boxWidth, BoxHeight, boxGap);
        }

        // Bottom bar
        Common::keysHelper = {
            {"\u2191 \u2193", "Navegar"},
            {"ENTER", "Seleccionar"},
            {"ESC", "Volver"}
        };
        Common::DrawBottomBar();

        // ── Input loop — only redraw changed boxes ──
        do {
            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(option, minOption, maxOption, Common::key);
            } else if (Common::key == Common::KEY_ESCAPE) {
                return -1;
            }

            // Only redraw if selection changed
            if (option != prevOption) {
                if (prevOption >= 0 && prevOption < optCount) {
                    DrawLevelBox(levels, levelDescs, levelColors, prevOption, false,
                        boxX, boxStartY, boxWidth, BoxHeight, boxGap);
                }
                DrawLevelBox(levels, levelDescs, levelColors, option, true,
                    boxX, boxStartY, boxWidth, BoxHeight, boxGap);
                prevOption = option;
            }

        } while (!Common::IsActionKey(Common::key));

        return option;
    }

} // namespace Buscaminas
