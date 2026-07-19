#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../Database/State.h"
#include "../PokemonAnimatedSprites/PsyduckFront.h"

namespace Pokemon {

    /// @brief Pantalla de animacion de huida con Psyduck desplazandose de izquierda a derecha
    /// @details Muestra un cuadro de mensaje con el texto de huida, un sprite de Psyduck animado,
    ///          y el contador de rondas. La animacion completa antes de retornar.
    ///          Lee los valores de los globals: currentPokemonName, playerNames[currentSelectionPlayer], currentRound.
    inline void HuidaView() {
        Common::DrawBackground();

        // Cuadro de mensaje centrado (posicion center X, y=5, w=60, h=5)
        const int boxWidth = 60;
        const int boxHeight = 5;
        const int boxX = Common::AlignedX(0, Common::WIDTH_SCREEN, boxWidth, "center");
        const int boxY = 5;

        // Fondo del cuadro
        Common::DrawFillRectangle(
            boxX, boxY, boxWidth, boxHeight,
            Common::EMPTY_BLOCK,
            Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
        );

        // Borde del cuadro
        // Borde superior
        Common::DrawText(boxX, boxY, boxWidth, 1,
            {Common::RepeatString(Common::HORIZONTAL_BORDER, boxWidth - 2)},
            Common::GRAY, Common::SELECTION_BACKGROUND);
        // Borde inferior
        Common::DrawText(boxX, boxY + boxHeight - 1, boxWidth, 1,
            {Common::RepeatString(Common::HORIZONTAL_BORDER, boxWidth - 2)},
            Common::GRAY, Common::SELECTION_BACKGROUND);
        // Borde izquierdo
        for (int i = 1; i < boxHeight - 1; i++) {
            Common::DrawText(boxX, boxY + i, 1, 1,
                {Common::VERTICAL_BORDER}, Common::GRAY, Common::SELECTION_BACKGROUND);
        }
        // Borde derecho
        for (int i = 1; i < boxHeight - 1; i++) {
            Common::DrawText(boxX + boxWidth - 1, boxY + i, 1, 1,
                {Common::VERTICAL_BORDER}, Common::GRAY, Common::SELECTION_BACKGROUND);
        }

        // Texto de huida dentro del cuadro
        std::string message = "¡El " + currentPokemonName + " de " + playerNames[currentSelectionPlayer] + " ha huido!";
        const int messageWidth = Common::Length(message);
        const int messageX = Common::AlignedX(boxX, boxWidth, messageWidth, "center");
        const int messageY = boxY + 2;
        Common::DrawText(messageX, messageY, -1, -1, {message}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);

        // Contador de rondas (posicion x=150, y=2)
        std::string roundText = "Rondas jugadas: " + std::to_string(currentRound);
        Common::DrawText(150, 2, -1, -1, {roundText}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();

        // Animacion de Psyduck desplazandose de izquierda a derecha
        // PsyduckFront_ALL tiene 10 frames (PsyduckFront00 a PsyduckFront09)
        const int startX = 0;
        const int endX = 160;
        const int step = 8;
        const int spriteY = 28;
        const int frameDelay = 80; // ms por frame
        const int frameCount = PsyduckFront_ALL.size();

        for (int x = startX; x <= endX; x += step) {
            // Determinar frame actual (ciclico)
            int frameIndex = (x / step) % frameCount;

            // Limpiar posicion anterior (redibujar fondo)
            if (x > startX) {
                int prevX = x - step;
                // Redibujar fondo en la posicion anterior del sprite
                Common::DrawFillRectangle(
                    prevX, spriteY, 30, 15, // ancho aproximado del sprite
                    Common::EMPTY_BLOCK,
                    Common::FOREGROUND_LIGHT, Common::BACKGROUND
                );
            }

            // Dibujar sprite de Psyduck en posicion actual
            Common::DrawSprite(x, spriteY, PsyduckFront_ALL[frameIndex]);

            Common::Sleep(frameDelay);
        }

        // Pausa al final de la animacion
        Common::Sleep(500);
    }

} // namespace Pokemon
