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
    /// @brief Instruction section with ACCENT-colored title and indented body lines
    struct InstructionSection {
        std::string title;
        std::vector<std::string> lines;
    };

    /// @brief Instructions view — shows how to play TicTacToe
    /// @param isFootball true for football quiz mode instructions, false for original
    /// @return always returns 0 (back to menu)
    inline int InstructionsView(bool isFootball)
    {
        // ── Layout constants ──
        const int contentX = Common::AlignedX(0, Common::WIDTH_SCREEN, 50, "center");
        int y = 14;

        // ── Draw static screen ONCE ──
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // ── Title (FONT4) ──
        std::string titleStr = isFootball ? "tic tac toe futbol" : "tic tac toe";
        std::vector<std::array<std::string, 4>> titleGlyphs = Common::Font4String(titleStr);
        std::array<std::string, 4> titleComposed = Common::ConcatFont(titleGlyphs, 1);
        int titleW = Common::Length(titleComposed[0]);
        int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, titleW, "center");
        for (int i = 0; i < 4; i++)
            Common::DrawText(titleX, 2 + i, -1, -1, {titleComposed[i]}, Common::ACCENT, Common::BACKGROUND);

        // ── Subtitle (FONT4 "instrucciones") ──
        std::vector<std::array<std::string, 4>> subGlyphs = Common::Font4String("instrucciones");
        std::array<std::string, 4> subComposed = Common::ConcatFont(subGlyphs, 1);
        int subW = Common::Length(subComposed[0]);
        int subX = Common::AlignedX(0, Common::WIDTH_SCREEN, subW, "center");
        for (int i = 0; i < 4; i++)
            Common::DrawText(subX, 8 + i, -1, -1, {subComposed[i]}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // ── Determine sections based on mode ──
        std::vector<InstructionSection> sections;

        if (isFootball) {
            sections.push_back({"REGLAS DEL MODO FUTBOL", {
                "1. Cada jugador debe responder una pregunta de futbol.",
                "2. Si responde correctamente puede colocar su ficha.",
                "3. Si responde mal pierde su turno.",
                "4. Forma una linea de 3 fichas para ganar."
            }});
            sections.push_back({"CATEGORIAS", {
                "Mundiales",
                "Champions League",
                "Balon de Oro",
                "Futbol internacional"
            }});
        } else {
            sections.push_back({"REGLAS DEL JUEGO", {
                "1. El jugador X comienza la partida.",
                "2. Use flechas para moverse y Enter para colocar.",
                "3. No puede elegir una casilla ocupada.",
                "4. Gana quien forme una linea de 3 fichas."
            }});
            sections.push_back({"DISTRIBUCION DE CASILLAS", {
                "El tablero se compone de 9 casillas numeradas",
                "del 1 al 9 en formato tradicional 3x3."
            }});
        }

        // ── Render sections ──
        for (const auto& section : sections) {
            // Section title in ACCENT
            Common::DrawText(contentX, y, Common::WIDTH_SCREEN - contentX * 2, 1,
                {section.title},
                Common::ACCENT, Common::BACKGROUND);
            y += 2;

            // Section body lines indented
            for (const auto& line : section.lines) {
                Common::DrawText(contentX + 2, y, Common::WIDTH_SCREEN - contentX * 2, 1,
                    {line},
                    Common::FOREGROUND_LIGHT, Common::BACKGROUND);
                y += 1;
            }
            y += 1; // gap between sections
        }

        // ── Bottom bar ──
        Common::keysHelper = {{"ESC", "Volver"}};
        Common::DrawBottomBar();

        // ── Wait for any key (ReadConsoleChar, no Getch) ──
        Common::ReadConsoleChar();

        Common::Clear();
        return 0;
    }

} // namespace Tictactoe
