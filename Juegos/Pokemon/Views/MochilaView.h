#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/UnicodeGlyphs.h"
#include "../../../Common/Utils.h"
#include "../../../Common/Variables.h"
#include "../../../Common/Navigation.h"
#include "../Database/MockData.h"
#include "../Sprites/Mochila.h"

namespace Pokemon {

    /// @brief Pantalla estatica de mochila que muestra items y sus descripciones
    /// @details Muestra el sprite de la mochila a la izquierda, la lista de items a la derecha,
    ///          y la descripcion del ultimo item mostrado. No requiere interaccion; retorna inmediatamente.
    inline void MochilaView() {
        Common::DrawBackground();

        // Titulo "MOCHILA" con ConcatFont (FONT_M-FONT_A) - 9-line font
        const std::array<std::string, 9> title = Common::ConcatFont({
            Common::FONT_M, Common::FONT_O, Common::FONT_C, Common::FONT_H,
            Common::FONT_I, Common::FONT_L, Common::FONT_A
        }, 1);

        // Centrar titulo horizontalmente
        const int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[0]), "center");

        // Renderizar titulo linea por linea con color gris
        for (int i = 0; i < 9; i++) {
            Common::DrawText(
                titleX, 2 + i, -1, -1,
                {title[i]}, Common::GRAY, Common::BACKGROUND
            );
        }

        // Sprite de la mochila (posicion x=15, y=12)
        Common::DrawSprite(15, 12, Mochila);

        // Panel de items (posicion x=80, y=10, w=110, h=30)
        const int panelX = 80;
        const int panelY = 10;
        const int panelWidth = 110;
        const int panelHeight = 30;

        // Fondo del panel
        Common::DrawFillRectangle(
            panelX, panelY, panelWidth, panelHeight,
            Common::EMPTY_BLOCK,
            Common::FOREGROUND_LIGHT, Common::BACKGROUND
        );

        // Encabezado "ITEMS"
        Common::DrawText(panelX + 2, panelY + 1, -1, -1,
            {"ITEMS"}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Lista de items
        int lastDescriptionY = 0;
        for (int i = 0; i < BAG_ITEM_COUNT; i++) {
            const int itemY = panelY + 3 + i * 3;

            // Icono del item (posicion x=panelX+2)
            std::string icon = (BAG_ITEMS[i].quantity > 0) ? "\033[38;2;178;242;187m●\033[0m" : "\033[38;2;255;201;201m■\033[0m";
            Common::DrawText(panelX + 2, itemY, -1, -1, {icon}, Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);

            // Nombre del item (posicion x=panelX+8)
            Common::DrawText(panelX + 8, itemY, -1, -1,
                {BAG_ITEMS[i].name}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

            // Cantidad "x{N}" (posicion x=panelX+85, color acento)
            std::string quantityText = "x" + std::to_string(BAG_ITEMS[i].quantity);
            Common::DrawText(panelX + 85, itemY, -1, -1,
                {quantityText}, Common::ACCENT, Common::BACKGROUND);

            lastDescriptionY = itemY;
        }

        // Cuadro de descripcion (posicion x=80, y=40, w=110, h=5)
        const int descBoxX = 80;
        const int descBoxY = 40;
        const int descBoxWidth = 110;
        const int descBoxHeight = 5;

        // Fondo del cuadro de descripcion
        Common::DrawFillRectangle(
            descBoxX, descBoxY, descBoxWidth, descBoxHeight,
            Common::EMPTY_BLOCK,
            Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
        );

        // Borde del cuadro de descripcion
        // Borde superior
        Common::DrawText(descBoxX, descBoxY, descBoxWidth, 1,
            {Common::RepeatString(Common::HORIZONTAL_BORDER, descBoxWidth - 2)},
            Common::GRAY, Common::SELECTION_BACKGROUND);
        // Borde inferior
        Common::DrawText(descBoxX, descBoxY + descBoxHeight - 1, descBoxWidth, 1,
            {Common::RepeatString(Common::HORIZONTAL_BORDER, descBoxWidth - 2)},
            Common::GRAY, Common::SELECTION_BACKGROUND);
        // Borde izquierdo
        for (int i = 1; i < descBoxHeight - 1; i++) {
            Common::DrawText(descBoxX, descBoxY + i, 1, 1,
                {Common::VERTICAL_BORDER}, Common::GRAY, Common::SELECTION_BACKGROUND);
        }
        // Borde derecho
        for (int i = 1; i < descBoxHeight - 1; i++) {
            Common::DrawText(descBoxX + descBoxWidth - 1, descBoxY + i, 1, 1,
                {Common::VERTICAL_BORDER}, Common::GRAY, Common::SELECTION_BACKGROUND);
        }

        // Texto de descripcion del ultimo item (centrado en el cuadro)
        if (BAG_ITEM_COUNT > 0) {
            std::string description = BAG_ITEMS[BAG_ITEM_COUNT - 1].description;
            const int descWidth = Common::Length(description);
            const int descX = Common::AlignedX(descBoxX, descBoxWidth, descWidth, "center");
            const int descY = descBoxY + 2;
            Common::DrawText(descX, descY, -1, -1,
                {description}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
        }

        // Texto "Presiona ENTER" (centrado, y=46)
        const std::string enterText = "Presiona ENTER";
        const int enterX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(enterText), "center");
        Common::DrawText(enterX, 46, -1, -1, {enterText}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();

        // Esperar ENTER para salir (aunque es estatica, espera input para continuar)
        while (true) {
            Common::key = Common::ReadConsoleChar();
            if (Common::IsActionKey(Common::key)) {
                break;
            }
        }
    }

} // namespace Pokemon
