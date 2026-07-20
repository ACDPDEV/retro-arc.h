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
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Variables.h"

#include "../TictactoeUI.h"

namespace Tictactoe
{
    /// @brief Confirmation dialog when quitting a game
    /// @return true=confirm exit, false=cancel
    inline bool ExitConfirmView()
    {
        const int boxWidth = 40;
        const int boxHeight = 5;
        const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
        const int boxY = (Common::HEIGHT_SCREEN - boxHeight) / 2;

        const int slotWidth = 12;
        const int slotHeight = 3;
        const int gap = 4;
        const int totalWidth = 2 * slotWidth + gap;
        const int optStartX = (Common::WIDTH_SCREEN - totalWidth) / 2;
        const int optY = boxY + boxHeight + 2;

        int option = 1; // default: NO (right)

        do {
            Common::EnableUTF8();
            Common::DrawBackground();
            Common::HideCursor();

            // Message box
            Common::PrintPrimaryBox(boxX, boxY, boxWidth, boxHeight,
                {"Quieres abandonar", "la partida?"},
                Common::FOREGROUND_LIGHT, Common::GRAY, Common::SELECTION_BACKGROUND);

            // SÍ button (left)
            const bool siSelected = (option == 0);
            const std::array<int, 3>& siBg = siSelected ? Common::CURSOR : Common::SELECTION_BACKGROUND;
            const std::array<int, 3>& siText = siSelected ? Common::FOREGROUND_DARK : Common::FOREGROUND_LIGHT;
            Common::PrintPrimaryBox(optStartX, optY, slotWidth, slotHeight, {"SÍ"},
                siText, Common::GRAY, siBg);

            // NO button (right)
            const bool noSelected = (option == 1);
            const std::array<int, 3>& noBg = noSelected ? Common::CURSOR : Common::SELECTION_BACKGROUND;
            const std::array<int, 3>& noText = noSelected ? Common::FOREGROUND_DARK : Common::FOREGROUND_LIGHT;
            Common::PrintPrimaryBox(optStartX + slotWidth + gap, optY, slotWidth, slotHeight, {"NO"},
                noText, Common::GRAY, noBg);

            // Bottom bar
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

} // namespace Tictactoe
