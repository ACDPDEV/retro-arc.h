#pragma once

// 1. Librerías estándar
#include <array>
#include <iostream>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Variables.h"

#include "../TictactoeUI.h"

namespace Tictactoe
{
    /// @brief Draws the football quiz panel (border + title at top)
    inline void DrawQuizPanel() {
        // Draw box border and fill (no text — we position the title manually)
        Common::DrawFillRectangle(QuizX(), QuizY() - 1, QuizW, 1, Common::LOWER_HALF_BLOCK, Common::GRAY, Common::BACKGROUND);
        Common::DrawFillRectangle(QuizX(), QuizY() + QuizH, QuizW, 1, Common::UPPER_HALF_BLOCK, Common::GRAY, Common::BACKGROUND);
        Common::DrawFillRectangle(QuizX(), QuizY(), QuizW, QuizH, Common::FULL_BLOCK, Common::GRAY, Common::BACKGROUND);
        Common::DrawFillRectangle(QuizX() + 1, QuizY(), QuizW - 2, QuizH, Common::FULL_BLOCK, Common::SELECTION_BACKGROUND, Common::BACKGROUND);
        // Title at top of panel (centered horizontally)
        const std::string title = "QUIZ FUTBOLERO";
        const int titleX = QuizX() + (QuizW - static_cast<int>(title.length())) / 2;
        Common::GoToXY(titleX, QuizY() + 1);
        std::cout << Common::Color(Common::YELLOW, Common::SELECTION_BACKGROUND) << title;
        Common::DrawBottomBar();
    }

    /// @brief Clears the quiz panel interior (content area only)
    inline void ClearQuizPanel() {
        Common::DrawFillRectangle(
            QuizX() + 1, QuizY() + 1,
            QuizW - 2, QuizH - 2,
            Common::FULL_BLOCK,
            Common::SELECTION_BACKGROUND, Common::BACKGROUND);
        std::cout.flush();
    }

    /// @brief Shows correct answer indicator in the quiz panel
    inline void DrawCorrectAnswer() {
        Common::GoToXY(QuizX() + 2, QuizY() + 13);
        std::cout << Common::Color(Common::LIGHT_GREEN, Common::SELECTION_BACKGROUND) << "\u2714 Correcto!";
        std::cout.flush();
    }

    /// @brief Prompt to place piece after answering correctly
    inline void DrawSelectCellPrompt() {
        Common::GoToXY(QuizX() + 2, QuizY() + 15);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND)
                  << "Enter para colocar";
        std::cout.flush();
    }

} // namespace Tictactoe
