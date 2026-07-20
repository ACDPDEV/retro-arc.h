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
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Variables.h"

#include "../BuscaminasUI.h"

namespace Buscaminas
{
    /// @brief Confirmation dialog when quitting a game
    /// @return true=confirm exit, false=cancel
    inline bool ExitConfirmView()
    {
        const int boxWidth = 40;
        const int boxHeight = 5;
        const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
        const int boxY = (Common::HEIGHT_SCREEN - boxHeight) / 2;

        std::vector<std::string> options = {"SÍ", "NO"};
        int option = 1; // default: NO
        const int slotWidth = 12;
        const int slotHeight = 3;
        const int margin = 2;

        do {
            Common::EnableUTF8();
            Common::DrawBackground();
            Common::HideCursor();

            // Message box
            Common::PrintPrimaryBox(boxX, boxY, boxWidth, boxHeight,
                {"¿Quieres abandonar", "la partida?"},
                Common::FOREGROUND_LIGHT, Common::GRAY, Common::SELECTION_BACKGROUND);

            // Options using SelectPrimaryBox1D rendering
            const int optY = boxY + boxHeight + margin;
            const int totalOptWidth = 2 * slotWidth + 4;
            const int optStartX = (Common::WIDTH_SCREEN - totalOptWidth) / 2;

            Common::StaticSelectPrimaryBox1D(
                optStartX, optY,
                options, option,
                Common::GRAY, Common::SELECTION_BACKGROUND,
                Common::CURSOR, Common::FOREGROUND_LIGHT,
                slotWidth, slotHeight
            );

            // Bottom bar with keysHelper
            Common::keysHelper = {
                {"\u2190 \u2192", "Navegar"},
                {"ENTER", "Confirmar"},
                {"ESC", "Cancelar"}
            };
            Common::DrawBottomBar();

            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(option, 0, 1, Common::key);
            } else if (Common::key == Common::KEY_ESCAPE) {
                return false;
            }
        } while (!Common::IsActionKey(Common::key));

        return (option == 0); // true if SÍ selected
    }

} // namespace Buscaminas
