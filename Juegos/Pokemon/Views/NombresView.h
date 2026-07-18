#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/InputComponent.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../Sprites/Trainer1.h"
#include "../Sprites/Trainer2.h"

namespace Pokemon {

    /// @brief Pantalla de entrada de nombres para dos jugadores con sprites de entrenadores
    /// @details Muestra dos paneles lado a lado: P1 con borde amarillo y P2 con borde rosa.
    ///          Bloquea hasta que ambos nombres sean ingresados.
    /// @param player1Name Referencia al nombre del jugador 1 (se modifica con el input)
    /// @param player2Name Referencia al nombre del jugador 2 (se modifica con el input)
    inline void NombresView(std::string& player1Name, std::string& player2Name) {
        Common::DrawBackground();

        // Logo "POKEMON" con ConcatFont (FONT9_P-FONT9_N) - 9-line font
        const std::array<std::string, 9> logo = Common::ConcatFont({
            Common::FONT9_P, Common::FONT9_O, Common::FONT9_K,
            Common::FONT9_E, Common::FONT9_M, Common::FONT9_O, Common::FONT9_N
        }, 1);

        // Gradiente: amarillo -> rojo para las 9 lineas del logo
        const std::vector<std::array<int, 3>> logoGradient = Common::Gradient(
            9, Common::YELLOW, Common::RED
        );

        // Centrar logo horizontalmente
        const int logoX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(logo[0]), "center");

        // Renderizar logo linea por linea con gradiente
        for (int i = 0; i < 9; i++) {
            Common::DrawText(
                logoX, 3 + i, -1, -1,
                {logo[i]}, logoGradient[i], Common::BACKGROUND
            );
        }

        // Sprite Trainer1 (jugador 1) - posicion x=15, y=16
        Common::DrawSprite(15, 16, Trainer1);

        // Sprite Trainer2 (jugador 2) - posicion x=130, y=16
        Common::DrawSprite(130, 16, Trainer2);

        // Etiqueta "Jugador 1:" centrada arriba de la caja de input
        const std::string label1 = "Jugador 1:";
        const int label1Width = Common::Length(label1);
        const int label1X = Common::AlignedX(30, 35, label1Width, "center");
        Common::DrawText(label1X, 24, -1, -1, {label1}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Etiqueta "Jugador 2:" centrada arriba de la caja de input
        const std::string label2 = "Jugador 2:";
        const int label2Width = Common::Length(label2);
        const int label2X = Common::AlignedX(135, 35, label2Width, "center");
        Common::DrawText(label2X, 24, -1, -1, {label2}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // InputComponent para jugador 1 (caja amarilla)
        Common::InputComponent(30, 26, 35, 3, player1Name, "", "Presiona ENTER para confirmar");

        // Dibujar nombre de P1 despues del input
        Common::DrawText(30, 26, 35, 3, {player1Name}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);

        // InputComponent para jugador 2 (caja rosa)
        Common::InputComponent(135, 26, 35, 3, player2Name, "", "Presiona ENTER para confirmar");

        // Dibujar nombre de P2 despues del input
        Common::DrawText(135, 26, 35, 3, {player2Name}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);

        // Texto de prompt centrado
        const std::string promptText = "Presiona ENTER para continuar";
        const int promptX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(promptText), "center");
        Common::DrawText(promptX, 40, -1, -1, {promptText}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();
    }

} // namespace Pokemon
