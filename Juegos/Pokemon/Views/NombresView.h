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

    /// @brief Dibuja un input estilizado con colores personalizados
    /// @param x Posición X del input
    /// @param y Posición Y del input
    /// @param w Ancho del input
    /// @param h Alto del input
    /// @param input Referencia al string de entrada
    /// @param bgColor Color de fondo del input
    /// @param txtColor Color del texto del input
    inline void DrawStyledInput(
        int x, int y, int w, int h,
        std::string& input,
        std::array<int, 3> bgColor,
        std::array<int, 3> txtColor
    ) {
        Common::DrawFillRectangle(x, y, w, h, " ", Common::FOREGROUND_DARK, bgColor);
        Common::TextBoxComponent(x, y, w, h, input, "", "", "", bgColor, txtColor);
    }

    /// @brief Pantalla de entrada de nombres para dos jugadores con paneles de color y sprites
    /// @details Muestra dos paneles apilados verticalmente: P1 con fondo crema y P2 con fondo rosa.
    ///          Cada panel contiene un sprite de entrenador y un subtitulo en FONT4 centrado debajo del sprite.
    ///          Bloquea hasta que ambos nombres sean ingresados.
    /// @param player1Name Referencia al nombre del jugador 1 (se modifica con el input)
    /// @param player2Name Referencia al nombre del jugador 2 (se modifica con el input)
    inline void NombresView(std::string& player1Name, std::string& player2Name) {
        Common::DrawBackground();

        // ─── Dimensiones compartidas de paneles ───
        const int panelWidth = 120;
        const int panelHeight = 20;
        const int panelX = Common::AlignedX(0, Common::WIDTH_SCREEN, panelWidth, "center");

        // ─── Posiciones Y de paneles ───
        const int panel1Y = Common::RelativeY(0, 2);
        const int panel2Y = Common::RelativeY(0, panelHeight + 4);

        // ─── Colores personalizados para inputs ───
        const std::array<int, 3> inputP1Bg = {220, 200, 130};  // Amarillo oscuro para P1
        const std::array<int, 3> inputP1Txt = Common::FOREGROUND_DARK;    // Texto crema para P1
        const std::array<int, 3> inputP2Bg = {220, 150, 160};  // Rosa oscuro para P2
        const std::array<int, 3> inputP2Txt = Common::FOREGROUND_DARK;     // Texto rosa para P2

        const std::vector<std::string> sub1 = Common::VectorSum({Common::ArrayToVector(Common::ConcatFont({
            Common::FONT4_i, Common::FONT4_n, Common::FONT4_g, Common::FONT4_r,
            Common::FONT4_e, Common::FONT4_s, Common::FONT4_e, Common::FONT4_blank,
            Common::FONT4_n, Common::FONT4_o, Common::FONT4_m, Common::FONT4_b,
            Common::FONT4_r, Common::FONT4_e
        }, 1)), {""}, Common::ArrayToVector(Common::ConcatFont({
            Common::FONT4_d, Common::FONT4_e, Common::FONT4_l, Common::FONT4_blank,
            Common::FONT4_j, Common::FONT4_u, Common::FONT4_g, Common::FONT4_a,
            Common::FONT4_d, Common::FONT4_o, Common::FONT4_r, Common::FONT4_blank,
            Common::FONT_1, Common::FONT4_colon
        }, 1))});

        const std::vector<std::string> sub2 = Common::VectorSum({Common::ArrayToVector(Common::ConcatFont({
            Common::FONT4_i, Common::FONT4_n, Common::FONT4_g, Common::FONT4_r,
            Common::FONT4_e, Common::FONT4_s, Common::FONT4_e, Common::FONT4_blank,
            Common::FONT4_n, Common::FONT4_o, Common::FONT4_m, Common::FONT4_b,
            Common::FONT4_r, Common::FONT4_e
        }, 1)), {""}, Common::ArrayToVector(Common::ConcatFont({
            Common::FONT4_d, Common::FONT4_e, Common::FONT4_l, Common::FONT4_blank,
            Common::FONT4_j, Common::FONT4_u, Common::FONT4_g, Common::FONT4_a,
            Common::FONT4_d, Common::FONT4_o, Common::FONT4_r, Common::FONT4_blank,
            Common::FONT_2, Common::FONT4_colon
        }, 1))});

        // ─── 2. Panel Jugador 1 (fondo crema) ───
        Common::PrintPrimaryBox(
            panelX, panel1Y, panelWidth, panelHeight,
            {},
            Common::FOREGROUND_DARK,
            Common::ACCENT,
            Common::CREAM
        );

        // Sprite Trainer1 (y+1, 10 lineas de alto)
        Common::DrawSprite(panelX + 3, panel1Y + 1, Trainer1);

        const int sub1Width = Common::Length(sub1[0]);
        const int sub1Height = sub1.size();
        const int sub1X = Common::AlignedX(panelX, panelWidth, sub1Width, "center") + 4;
        const int sub1Y = Common::AlignedY(panel1Y, panelHeight, sub1Height, "top") + 1;
        Common::DrawText(sub1X, sub1Y, -1, -1,
            sub1,
            Common::ORANGE, Common::CREAM);

        // Input jugador 1 (ultima linea del panel)
        const int input1Weight = 50;
        const int input1Height = 1;
        const int input1X = Common::AlignedX(panelX, panelWidth, input1Weight, "center");
        const int input1Y = Common::AlignedY(panel1Y, panelHeight, input1Height, "bottom") - 5;
        DrawStyledInput(input1X, input1Y, input1Weight, input1Height, player1Name, inputP1Bg, inputP1Txt);

        // ─── 3. Panel Jugador 2 (fondo rosa) ───
        Common::PrintPrimaryBox(
            panelX, panel2Y, panelWidth, panelHeight,
            {},
            Common::FOREGROUND_DARK,
            Common::ACCENT,
            Common::PINK
        );

        // Sprite Trainer2 (y+1, 10 lineas de alto)
        Common::DrawSprite(panelX + 3, panel2Y + 1, Trainer2);

        const int sub2Width = Common::Length(sub2[0]);
        const int sub2Height = sub2.size();
        const int sub2X = Common::AlignedX(panelX, panelWidth, sub2Width, "center") + 4;
        const int sub2Y = Common::AlignedY(panel2Y, panelHeight, sub2Height, "top") + 1;
        Common::DrawText(sub2X, sub2Y, -1, -1,
            sub2,
            Common::ORANGE, Common::PINK);

        // Input jugador 2 (ultima linea del panel)
        const int input2Weight = 50;
        const int input2Height = 1;
        const int input2X = Common::AlignedX(panelX, panelWidth, input2Weight, "center");
        const int input2Y = Common::AlignedY(panel2Y, panelHeight, input2Height, "bottom") - 5;
        DrawStyledInput(input2X, input2Y, input2Weight, input2Height, player2Name, inputP2Bg, inputP2Txt);

        // ─── 6. Barra inferior ───
        Common::DrawBottomBar();
        // ─── 4. Input bloqueante para jugador 1 ───
        Common::InputComponent(input1X, input1Y, input1Weight, input1Height, player1Name, "", "", "", inputP1Bg, inputP1Txt);

        // ─── 5. Input bloqueante para jugador 2 ───
        Common::InputComponent(input2X, input2Y, input2Weight, input2Height, player2Name, "", "", "", inputP2Bg, inputP2Txt);


        // ─── 7. Posicionar cursor al final ───
        Common::GoToEnd();
    }

} // namespace Pokemon
