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
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../../../Common/Variables.h"

#include "../BuscaminasUI.h"

namespace Buscaminas
{
    /// @brief Configuration screen with player name input
    inline void ConfigView()
    {
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        const std::string title = "CONFIGURACIONES";
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title), "center"), HUD_Y + 4);
        std::cout << Common::Color(Common::YELLOW, Common::BACKGROUND) << title;

        // Label
        const std::string label = "Nombre del jugador:";
        const int labelX = 40;
        const int labelY = 12;
        Common::GoToXY(labelX, labelY);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << label;

        // Input field
        const int inputWidth = 30;
        const int inputX = labelX + Common::Length(label) + 2;
        const int inputY = labelY;
        std::string input = Common::playerName;

        // Bottom bar with keysHelper
        Common::keysHelper = {{"ENTER", "Guardar"}, {"ESC", "Volver"}};

        while (true) {
            // Draw bottom bar each frame
            Common::DrawBottomBar();

            // Draw input box
            Common::DrawFillRectangle(
                inputX, inputY,
                inputWidth, 1,
                Common::EMPTY_BLOCK,
                Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
            );

            // Draw input text
            Common::GoToXY(inputX, inputY);
            std::string displayInput = input;
            if (displayInput.size() > static_cast<size_t>(inputWidth)) {
                displayInput = displayInput.substr(0, inputWidth);
            }
            std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << displayInput
                      << Common::ResetColor();
            std::cout.flush();

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                Common::playerName = input;
                return;
            } else if (Common::key == Common::KEY_ESCAPE) {
                return;
            } else if (Common::key == Common::KEY_BACKSPACE) {
                if (!input.empty()) {
                    input.pop_back();
                }
            } else if (input.size() < static_cast<size_t>(inputWidth) && Common::IsAlphaNumChar(Common::key)) {
                for (char c : Common::CastKeyToString(Common::key)) {
                    input.push_back(c);
                }
            }
        }
    }

} // namespace Buscaminas
