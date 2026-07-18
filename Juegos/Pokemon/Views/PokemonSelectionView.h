#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/LifeBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/UnicodeGlyphs.h"
#include "../../../Common/Utils.h"
#include "../Database/MockData.h"
#include "../PokemonStaticSprites/BulbasaurFront.h"
#include "../PokemonStaticSprites/CharmanderFront.h"
#include "../PokemonStaticSprites/ChikoritaFront.h"
#include "../PokemonStaticSprites/EeveeFront.h"
#include "../PokemonStaticSprites/PikachuFront.h"
#include "../PokemonStaticSprites/PsyduckFront.h"
#include "../PokemonStaticSprites/RockruffFront.h"
#include "../PokemonStaticSprites/SquirtleFront.h"

namespace Pokemon {

    /// @brief Pantalla de seleccion de Pokemon con cuadricula 4x2 y barras de vida
    /// @details Muestra 8 Pokemon en una cuadricula interactiva. El usuario navega con flechas y confirma con ENTER.
    /// @param selectedPokemon Referencia al indice del Pokemon seleccionado (0-7)
    inline void PokemonSelectionView(int& selectedPokemon) {
        Common::DrawBackground();

        // Titulo "SELECCIONA" con ConcatFont (FONT9_S-FONT9_A) - 9-line font
        const std::array<std::string, 9> title = Common::ConcatFont({
            Common::FONT9_S, Common::FONT9_E, Common::FONT9_L, Common::FONT9_E,
            Common::FONT9_C, Common::FONT9_C, Common::FONT9_I, Common::FONT9_O,
            Common::FONT9_N, Common::FONT9_A
        }, 1);

        // Centrar titulo horizontalmente
        const int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[0]), "center");

        // Renderizar titulo linea por linea con color naranja
        for (int i = 0; i < 9; i++) {
            Common::DrawText(
                titleX, 2 + i, -1, -1,
                {title[i]}, Common::ORANGE, Common::BACKGROUND
            );
        }

        // Configuracion de la cuadricula
        const int gridX = 10;
        const int gridY = 14;
        const int cellWidth = 40;
        const int cellHeight = 12;
        const int cols = 4;
        const int rows = 2;

        // Array de sprites de Pokemon (ordenado por spriteIndex)
        const std::vector<std::string>* pokemonSprites[] = {
            &BulbasaurFront, &CharmanderFront, &SquirtleFront, &PikachuFront,
            &PsyduckFront, &EeveeFront, &RockruffFront, &ChikoritaFront
        };

        // Dibujar celda de Pokemon
        auto drawCell = [&](int col, int row, int index, bool isSelected) {
            const int cellX = gridX + col * cellWidth;
            const int cellY = gridY + row * cellHeight;

            // Borde de celda: naranja si esta seleccionada, gris si no
            std::array<int, 3> borderColor = isSelected ? Common::ORANGE : Common::GRAY;

            // Fondo de celda
            Common::DrawFillRectangle(
                cellX, cellY, cellWidth, cellHeight,
                Common::EMPTY_BLOCK,
                Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
            );

            // Borde de celda (solo borde, no relleno)
            // Borde superior
            Common::DrawText(cellX, cellY, cellWidth, 1,
                {Common::RepeatString(Common::HORIZONTAL_BORDER, cellWidth - 2)},
                borderColor, Common::SELECTION_BACKGROUND);
            // Borde inferior
            Common::DrawText(cellX, cellY + cellHeight - 1, cellWidth, 1,
                {Common::RepeatString(Common::HORIZONTAL_BORDER, cellWidth - 2)},
                borderColor, Common::SELECTION_BACKGROUND);
            // Borde izquierdo
            for (int i = 1; i < cellHeight - 1; i++) {
                Common::DrawText(cellX, cellY + i, 1, 1,
                    {Common::VERTICAL_BORDER}, borderColor, Common::SELECTION_BACKGROUND);
            }
            // Borde derecho
            for (int i = 1; i < cellHeight - 1; i++) {
                Common::DrawText(cellX + cellWidth - 1, cellY + i, 1, 1,
                    {Common::VERTICAL_BORDER}, borderColor, Common::SELECTION_BACKGROUND);
            }

            // Indicador pokeball (posicion cell_x+2, cell_y+1)
            std::string pokeball = isSelected ? "\033[38;2;239;75;70m●\033[0m" : "\033[38;2;206;212;218m●\033[0m";
            Common::DrawText(cellX + 2, cellY + 1, -1, -1, {pokeball}, Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);

            // Sprite de Pokemon (posicion cell_x+5, cell_y+1)
            if (index < POKEMON_COUNT) {
                Common::DrawSprite(cellX + 5, cellY + 1, *pokemonSprites[index]);
            }

            // Nombre de Pokemon (posicion cell_x+2, cell_y+8)
            if (index < POKEMON_COUNT) {
                Common::DrawText(cellX + 2, cellY + 8, cellWidth - 4, 1,
                    {MOCK_POKEMON[index].name}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
            }

            // Barra de vida (posicion cell_x+2, cell_y+10, w=30, gradiente 15 pasos)
            if (index < POKEMON_COUNT) {
                int hp = MOCK_POKEMON[index].hp;
                int maxHp = MOCK_POKEMON[index].maxHp;
                float hpRatio = static_cast<float>(hp) / static_cast<float>(maxHp);

                // Colores de barra: rojo -> amarillo -> verde claro
                std::array<int, 3> barStart, barEnd;
                if (hpRatio > 0.5f) {
                    barStart = Common::YELLOW;
                    barEnd = Common::LIGHT_GREEN;
                } else if (hpRatio > 0.2f) {
                    barStart = Common::RED;
                    barEnd = Common::YELLOW;
                } else {
                    barStart = Common::DARK_RED;
                    barEnd = Common::RED;
                }

                Common::DrawLifeBar(cellX + 2, cellY + 10, 30, barStart, barEnd, Common::SELECTION_BACKGROUND);
            }
        };

        // Dibujar todas las celdas
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int index = row * cols + col;
                bool isSelected = (index == selectedPokemon);
                drawCell(col, row, index, isSelected);
            }
        }

        // Instrucciones de navegacion (centrado, y=44)
        const std::string navText = "← → ↑ ↓  ENTER";
        const int navX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(navText), "center");
        Common::DrawText(navX, 44, -1, -1, {navText}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();

        // Loop de navegacion
        while (true) {
            Common::key = Common::ReadConsoleChar();

            // Navegacion con flechas
            if (Common::IsKeyArrowTop(Common::key)) {
                // Mover arriba: de fila 1 a fila 0 (wrap)
                selectedPokemon = (selectedPokemon - cols + POKEMON_COUNT) % POKEMON_COUNT;
            } else if (Common::IsKeyArrowBottom(Common::key)) {
                // Mover abajo: de fila 0 a fila 1 (wrap)
                selectedPokemon = (selectedPokemon + cols) % POKEMON_COUNT;
            } else if (Common::IsKeyArrowLeft(Common::key)) {
                // Mover izquierda: wrap dentro de la fila
                int row = selectedPokemon / cols;
                int col = selectedPokemon % cols;
                col = (col - 1 + cols) % cols;
                selectedPokemon = row * cols + col;
            } else if (Common::IsKeyArrowRight(Common::key)) {
                // Mover derecha: wrap dentro de la fila
                int row = selectedPokemon / cols;
                int col = selectedPokemon % cols;
                col = (col + 1) % cols;
                selectedPokemon = row * cols + col;
            } else if (Common::IsActionKey(Common::key)) {
                // Confirmar seleccion
                break;
            }

            // Redibujar cuadricula con nueva seleccion
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    int index = row * cols + col;
                    bool isSelected = (index == selectedPokemon);
                    drawCell(col, row, index, isSelected);
                }
            }

            Common::GoToEnd();
        }
    }

} // namespace Pokemon
