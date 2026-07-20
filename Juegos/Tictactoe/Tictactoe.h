#pragma once

// ─────────────────────────────────────────────────────────────────────────
// Tictactoe.h — Entry point for TicTacToe game
// Include this single file to integrate TicTacToe into a main project.
// Call Tictactoe::PlayTicTacToe() to start the game.
// ─────────────────────────────────────────────────────────────────────────

// 1. Librerías estándar
#include <array>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../Common/Aligned.h"
#include "../../Common/Color.h"
#include "../../Common/Components/BottomBar.h"
#include "../../Common/Components/SelectPrimaryBox.h"
#include "../../Common/Consts.h"
#include "../../Common/Font.h"
#include "../../Common/Graphics.h"
#include "../../Common/Input.h"
#include "../../Common/Navigation.h"
#include "../../Common/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"
#include "../../Common/Variables.h"

// 3. UI views
#include "TictactoeUI.h"

// 4. Game logic (header-only)
#include "game.h"

namespace Tictactoe
{
    /// @brief Entry point — call this to start the TicTacToe game
    inline void PlayTicTacToe()
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        Common::EnableUTF8();

        while (true)
        {
            int opcion = MainMenuView();

            if (opcion == 0)
            {
                DrawTransition();
                do
                {
                    Common::Clear();
                    Common::DrawBackground();
                    jugarOriginal();
                } while (jugarNuevamente());
            }
            else if (opcion == 1)
            {
                DrawTransition();
                do
                {
                    Common::Clear();
                    Common::DrawBackground();
                    jugarFutbol();
                } while (jugarNuevamente());
            }
            else if (opcion == 2)
            {
                Common::Clear();
                Common::DrawBackground();
                InstructionsView(false);
            }
            else
            {
                break;
            }
        }

        Common::ShowCursor();
    }

} // namespace Tictactoe
