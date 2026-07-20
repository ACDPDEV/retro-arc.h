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
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Variables.h"

#include "../TictactoeUI.h"

namespace Tictactoe
{
    bool ganar(char ficha);

    /// @brief Draws the game result line below the board
    inline void DrawResult() {
        int ry = BoardY() + 3 * (CELL_H + 1);  // below bottom border
        std::string text;
        std::array<int, 3> color;
        if (ganar('X')) {
            text = " \u2500 \u2715 Gana X \u2715 \u2500 ";
            color = Common::RED;
        } else if (ganar('O')) {
            text = " \u2500 \u25CB Gana O \u25CB \u2500 ";
            color = Common::BLUE;
        } else {
            text = " \u2500 Empate \u2500 ";
            color = Common::FOREGROUND_LIGHT;
        }
        int textLen = Common::Length(text);
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, textLen, "center"), ry);
        std::cout << Common::Color(color, Common::BACKGROUND) << text;
        std::cout.flush();
        Common::DrawBottomBar();
    }

    /// @brief Full victory screen with FONT9 "WINNER" fade-in/out and FONT4 winner text
    inline void DrawVictoryScreen() {
        Common::Clear();
        Common::DrawBackground();

        // Title FONT9 "WINNER"
        std::array<std::string, 9> winTitle = Common::ConcatFont({
            Common::FONT9_W, Common::FONT9_I, Common::FONT9_N, Common::FONT9_N,
            Common::FONT9_E, Common::FONT9_R
        }, 2);

        std::vector<std::array<int, 3>> winColors = Common::Gradient(9, Common::DARK_RED, Common::ACCENT);

        // Fade in (8 steps, 60ms each)
        for (int k = 0; k < 8; k++) {
            for (int i = 0; i < static_cast<int>(winTitle.size()); i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(winTitle[i]), "center"),
                    5 + i, -1, -1, {winTitle[i]},
                    {
                        Common::BACKGROUND[0] + (winColors[i][0] - Common::BACKGROUND[0]) * (k + 1) / 8,
                        Common::BACKGROUND[1] + (winColors[i][1] - Common::BACKGROUND[1]) * (k + 1) / 8,
                        Common::BACKGROUND[2] + (winColors[i][2] - Common::BACKGROUND[2]) * (k + 1) / 8
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(60);
        }
        Common::Sleep(400);

        // Fade out (reverse)
        for (int k = 8; k > 0; k--) {
            for (int i = 0; i < static_cast<int>(winTitle.size()); i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(winTitle[i]), "center"),
                    5 + i, -1, -1, {winTitle[i]},
                    {
                        Common::BACKGROUND[0] + (winColors[i][0] - Common::BACKGROUND[0]) * k / 8,
                        Common::BACKGROUND[1] + (winColors[i][1] - Common::BACKGROUND[1]) * k / 8,
                        Common::BACKGROUND[2] + (winColors[i][2] - Common::BACKGROUND[2]) * k / 8
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(60);
        }

        Common::Clear();
        Common::DrawBackground();

        // Winner text with FONT4
        std::string winStr = ganar('X') ? "gana jugador x" : (ganar('O') ? "gana jugador o" : "empate");
        std::vector<std::array<std::string, 4>> wg = Common::Font4String(winStr);
        std::array<std::string, 4> winText = Common::ConcatFont(wg, 1);
        int ww = Common::Length(winText[0]);
        int wx = Common::AlignedX(0, Common::WIDTH_SCREEN, ww, "center");
        int winY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 4, "center") - 3;

        std::array<int, 3> winColor = ganar('X') ? Common::RED :
                                      (ganar('O') ? Common::BLUE : Common::FOREGROUND_LIGHT);

        for (int i = 0; i < 4; i++)
            Common::DrawText(wx, winY + i, -1, -1, {winText[i]}, winColor, Common::BACKGROUND);

        // Prompt centered below winner text
        std::string promptText = "Presiona una tecla...";
        int promptLen = Common::Length(promptText);
        int promptX = Common::AlignedX(0, Common::WIDTH_SCREEN, promptLen, "center");
        int promptY = winY + 6;
        Common::GoToXY(promptX, promptY);
        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << promptText;

        Common::DrawBottomBar();
        std::cout.flush();
        Common::ReadConsoleChar();
    }

    /// @brief Play again prompt below the board
    inline void DrawPlayAgainPrompt() {
        int ry = BoardY() + 3 * (CELL_H + 1) + 1;
        const int x = Common::AlignedX(0, Common::WIDTH_SCREEN, 36, "center");
        Common::GoToXY(x, ry);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND)
                  << "\u2500\u2500\u2500 \u00BFJugar de nuevo? (S/N) \u2500\u2500\u2500";
        std::cout.flush();
        Common::DrawBottomBar();
    }

} // namespace Tictactoe
