#pragma once

#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/TransitionComponent.h"
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
    /// @brief Runs confetti animation (30 particles, Pokemon VictoryView pattern)
    inline void RunConfetti()
    {
        // Initialize random generator
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Particle structure
        struct Particle {
            int x;
            int y;
            std::string character;
            int r, g, b;
            int speed;
        };

        // 30 particles
        const int PARTICLE_COUNT = 30;
        Particle particles[PARTICLE_COUNT];

        // Initialize particles with random positions and colors
        for (int i = 0; i < PARTICLE_COUNT; i++) {
            particles[i].x = std::rand() % Common::WIDTH_SCREEN;
            particles[i].y = std::rand() % Common::HEIGHT_SCREEN;
            particles[i].character = (std::rand() % 2 == 0) ? "█" : "▀";
            particles[i].r = std::rand() % 256;
            particles[i].g = std::rand() % 256;
            particles[i].b = std::rand() % 256;
            particles[i].speed = 1 + (std::rand() % 3);
        }

        // Confetti animation loop until keypress
        while (true) {
            // Draw title "VICTORIA" with gradient
            std::vector<std::array<std::string, 9>> victoryChars = {
                Common::FONT9_V, Common::FONT9_I, Common::FONT9_C, Common::FONT9_T,
                Common::FONT9_O, Common::FONT9_R, Common::FONT9_I, Common::FONT9_A
            };
            const auto victoryFont = Common::ConcatFont(victoryChars, 2);
            const auto gradient = Common::Gradient(9, Common::YELLOW, Common::ORANGE);

            for (int i = 0; i < 9; i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(victoryFont[i]), "center"),
                    HUD_Y + 3 + i, -1, -1,
                    {victoryFont[i]},
                    gradient[i], Common::BACKGROUND
                );
            }

            // Bottom bar
            Common::keysHelper = {{"", "Presiona una tecla para continuar"}};
            Common::DrawBottomBar();

            // Check for keypress
            if (Common::Kbhit()) {
                Common::Getch();
                break;
            }

            // Update and draw each particle
            for (int i = 0; i < PARTICLE_COUNT; i++) {
                // Clear previous position
                Common::DrawText(particles[i].x, particles[i].y, 1, 1,
                    {" "}, Common::COLOR_DEFAULT, Common::BACKGROUND);

                // Move particle down
                particles[i].y += particles[i].speed;

                // Optional horizontal movement
                if (std::rand() % 3 == 0) {
                    particles[i].x += (std::rand() % 2 == 0) ? 1 : -1;
                }

                // Horizontal bounds
                if (particles[i].x < 0) particles[i].x = 0;
                if (particles[i].x >= Common::WIDTH_SCREEN) particles[i].x = Common::WIDTH_SCREEN - 1;

                // If particle below screen, reset at top
                if (particles[i].y >= Common::HEIGHT_SCREEN - 3) {
                    particles[i].y = 0;
                    particles[i].x = std::rand() % Common::WIDTH_SCREEN;
                    particles[i].r = std::rand() % 256;
                    particles[i].g = std::rand() % 256;
                    particles[i].b = std::rand() % 256;
                }

                // Draw particle at new position
                Common::DrawText(particles[i].x, particles[i].y, 1, 1,
                    {particles[i].character}, {particles[i].r, particles[i].g, particles[i].b}, Common::COLOR_DEFAULT);
            }

            Common::Sleep(50);
        }
    }

    /// @brief Result screen after winning or losing
    /// @param won true if victory, false if defeat
    /// @return 0=play again, 1=back to menu
    inline int GameOverView(bool won)
    {
        int selectedOption = 0;

        Common::EnableUTF8();

        if (won) {
            // Victory: background flash
            for (int flash = 0; flash < 3; flash++) {
                Common::DrawFillRectangle(0, 0, Common::WIDTH_SCREEN, Common::HEIGHT_SCREEN,
                    Common::EMPTY_BLOCK, Common::FOREGROUND_LIGHT,
                    (flash % 2 == 0) ? Common::YELLOW : Common::BACKGROUND);
                Common::Sleep(150);
            }
            Common::DrawBackground();

            // Confetti animation
            RunConfetti();

        } else {
            // Defeat: fade transition
            Common::TransitionComponent();
            Common::Clear();
            Common::DrawBackground();

            // "DERROTA" title with RED → DARK_RED gradient
            std::vector<std::array<std::string, 9>> defeatChars = {
                Common::FONT9_D, Common::FONT9_E, Common::FONT9_R, Common::FONT9_R,
                Common::FONT9_O, Common::FONT9_T, Common::FONT9_A
            };
            const auto defeatFont = Common::ConcatFont(defeatChars, 2);
            const auto gradient = Common::Gradient(9, Common::RED, Common::DARK_RED);

            for (int i = 0; i < 9; i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(defeatFont[i]), "center"),
                    HUD_Y + 3 + i, -1, -1,
                    {defeatFont[i]},
                    gradient[i], Common::BACKGROUND
                );
            }
        }

        // Options
        const std::vector<std::string> options = {"JUGAR DE NUEVO", "VOLVER AL MENÚ"};
        const std::vector<std::array<int, 3>> optColors = {Common::ORANGE, Common::GRAY};
        const int boxWidth = 30;
        const int BoxHeight = 3;
        const int Margin = 2;
        const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
        const int boxStartY = 24;
        const int boxGap = BoxHeight + Margin;

        do {
            Common::HideCursor();

            // Redraw options with selection
            for (int i = 0; i < 2; i++) {
                int y = boxStartY + i * boxGap;
                const std::array<int, 3>& fillColor = optColors[i];
                if (i == selectedOption) {
                    Common::PrintPrimaryBox(boxX, y, boxWidth, BoxHeight, {options[i]},
                        Common::FOREGROUND_LIGHT, Common::CURSOR, fillColor);
                } else {
                    Common::PrintPrimaryBox(boxX, y, boxWidth, BoxHeight, {options[i]},
                        Common::FOREGROUND_DARK, fillColor, fillColor);
                }
            }

            // Bottom bar with keysHelper
            Common::keysHelper = {
                {"\u2191 \u2193", "Navegar"},
                {"ENTER", "Seleccionar"}
            };
            Common::DrawBottomBar();

            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(selectedOption, 0, 1, Common::key);
            }
        } while (!Common::IsActionKey(Common::key));

        return selectedOption; // 0=play again, 1=menu
    }

} // namespace Buscaminas
