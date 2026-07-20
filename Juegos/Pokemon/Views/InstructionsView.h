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
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"

namespace Pokemon {

    /// @brief Seccion de instrucciones con titulo en ACCENT y lineas de cuerpo indentadas
    struct InstructionSection {
        std::string title;
        std::vector<std::string> lines;
    };

    /// @brief Vista de instrucciones — explica las reglas de Pokemon
    /// @return siempre 0 (vuelve al menu)
    inline int InstructionsView() {
        // ── Constantes de layout ──
        const int contentX = Common::AlignedX(0, Common::WIDTH_SCREEN, 50, "center");
        int y = 14;

        // ── Dibujar pantalla estatica UNA VEZ ──
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // ── Titulo (FONT4) ──
        std::vector<std::array<std::string, 4>> titleGlyphs = Common::Font4String("pokemon");
        std::array<std::string, 4> titleComposed = Common::ConcatFont(titleGlyphs, 1);
        int titleW = Common::Length(titleComposed[0]);
        int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, titleW, "center");
        for (int i = 0; i < 4; i++)
            Common::DrawText(titleX, 2 + i, -1, -1, {titleComposed[i]}, Common::ACCENT, Common::BACKGROUND);

        // ── Subtitulo (FONT4 "instrucciones") ──
        std::vector<std::array<std::string, 4>> subGlyphs = Common::Font4String("instrucciones");
        std::array<std::string, 4> subComposed = Common::ConcatFont(subGlyphs, 1);
        int subW = Common::Length(subComposed[0]);
        int subX = Common::AlignedX(0, Common::WIDTH_SCREEN, subW, "center");
        for (int i = 0; i < 4; i++)
            Common::DrawText(subX, 8 + i, -1, -1, {subComposed[i]}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // ── Secciones ──
        const std::vector<InstructionSection> sections = {
            {
                "OBJETIVO",
                {
                    "Pokemon es una batalla local para 2 jugadores (PvP).",
                    "Cada jugador elige un Pokemon y ambos se enfrentan",
                    "por turnos hasta que uno de los dos se desmaye."
                }
            },
            {
                "OPCIONES DE BATALLA",
                {
                    "LUCHAR    Elegir un ataque para golpear al rival",
                    "POKEMON   Cambiar de Pokemon activo",
                    "MOCHILA   Usar un objeto de la mochila",
                    "HUIDA     Abandonar la batalla"
                }
            },
            {
                "EFECTIVIDAD DE TIPOS",
                {
                    "Cada ataque tiene un tipo (agua, fuego, planta, etc).",
                    "Algunos ataques hacen mas o menos daño segun el",
                    "tipo del Pokemon rival, igual que en el juego original."
                }
            }
        };

        for (const auto& section : sections) {
            Common::DrawText(contentX, y, Common::WIDTH_SCREEN - contentX * 2, 1,
                {section.title},
                Common::ACCENT, Common::BACKGROUND);
            y += 2;

            for (const auto& line : section.lines) {
                Common::DrawText(contentX + 2, y, Common::WIDTH_SCREEN - contentX * 2, 1,
                    {line},
                    Common::FOREGROUND_LIGHT, Common::BACKGROUND);
                y += 1;
            }
            y += 1; // espacio entre secciones
        }

        // ── Barra inferior ──
        Common::keysHelper = {{"ESC", "Volver"}};
        Common::DrawBottomBar();

        // ── Esperar cualquier tecla ──
        Common::ReadConsoleChar();

        Common::Clear();
        return 0;
    }

} // namespace Pokemon
