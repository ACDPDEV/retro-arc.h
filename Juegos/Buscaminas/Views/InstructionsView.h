#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
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
    /// @brief Instructions view — shows how to play Buscaminas
    /// @return always returns 0 (back to menu)
    inline int InstructionsView()
    {
        // ── Layout constants ──
        const int contentX = 8;
        int y = 2;

        // ── Draw static screen ONCE ──
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // ── Title (FONT4 with spacing) ──
        auto titleGlyphs = Common::Font4String("INSTRUCCIONES");
        const std::string SPACE = "        "; // 8 spaces between characters

        for (int line = 0; line < 4; line++) {
            std::string composed;
            for (size_t i = 0; i < titleGlyphs.size(); i++) {
                if (i > 0) composed += SPACE;
                composed += titleGlyphs[i][line];
            }
            int titleWidth = Common::Length(composed);
            Common::DrawText(
                Common::AlignedX(0, Common::WIDTH_SCREEN, titleWidth, "center"),
                y + line, -1, -1,
                {composed},
                Common::ACCENT, Common::BACKGROUND
            );
        }
        y += 7;

        // ── Instructions content ──
        struct InstructionSection {
            std::string title;
            std::vector<std::string> lines;
        };

        const std::vector<InstructionSection> sections = {
            {
                "OBJETIVO",
                {
                    "Revelar todas las celdas seguras del tablero sin",
                    "pisar ninguna mina. Las minas estan escondidas",
                    "y solo se revelan cuando se hace click en ellas."
                }
            },
            {
                "CONTROLES",
                {
                    "FLECHAS    Mover el cursor por el tablero",
                    "ENTER      Revelar celda seleccionada",
                    "F          Poner / quitar bandera en una celda",
                    "ESC        Salir al menu principal"
                }
            },
            {
                "CODIGO DE COLORES",
                {
                    "  1  Azul       5  Purpura",
                    "  2  Verde      6  Celeste",
                    "  3  Rojo       7  Gris oscuro",
                    "  4  Rojo osc.  8  Gris"
                }
            },
            {
                "BANDERAS",
                {
                    "Use la bandera para marcar celdas que sospecha",
                    "que contienen minas. Las celdas con bandera no",
                    "pueden ser reveladas accidentalmente.",
                    "El contador de banderas muestra cuantas le quedan."
                }
            },
            {
                "CONSEJOS",
                {
                    "Los numeros indican cuantas minas hay alrededor",
                    "de esa celda. Uselos para deducir donde estan",
                    "las minas. Empiece por las esquinas y bordes."
                }
            }
        };

        for (const auto& section : sections) {
            // Section title
            Common::DrawText(contentX, y, Common::WIDTH_SCREEN - contentX * 2, 1,
                {section.title},
                Common::ACCENT, Common::BACKGROUND);
            y += 2;

            // Section lines
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

        // ── Wait for any key ──
        Common::ReadConsoleChar();

        return 0;
    }

} // namespace Buscaminas
