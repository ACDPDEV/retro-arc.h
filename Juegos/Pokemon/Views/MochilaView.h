#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/SelectPrimaryBox.h"
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
    inline void DescriptionBox(
        const std::string& description
    ) {
        const int descriptionWidth = Common::WIDTH_SCREEN - 8;
        const int descriptionHeight = 4;
        const int descriptionX = Common::AlignedX(0, Common::WIDTH_SCREEN, descriptionWidth, "center");
        const int descriptionY = Common::AlignedY(0, Common::HEIGHT_SCREEN, descriptionHeight, "bottom") - 5;
        Common::PrintPrimaryBox(descriptionX, descriptionY, descriptionWidth, descriptionHeight, {description}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
    }

    inline void SelectPrimaryBox1DWithDescription(
        int x, int y,
        std::vector<std::string>& options,
        std::vector<std::string>& descriptions,
        int& selectedOption,
        std::array<int, 3> textColor,
        std::array<int, 3> borderColor,
        std::array<int, 3> fillColor,
        std::array<int, 3> selectedColor,
        int slotWidth,
        int slotHeight
    ) {
        while (true) {
            Common::StaticSelectPrimaryBox1D(
                x, y,
                options, selectedOption,
                borderColor, fillColor, selectedColor,
                textColor,
                slotWidth, slotHeight
            );
            DescriptionBox(descriptions[selectedOption]);

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                break;
            } else if (Common::key == Common::KEY_ARROW_TOP) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (Common::key == Common::KEY_ARROW_BOTTOM) {
                selectedOption = (selectedOption + 1) % options.size();
            }

        }
    }

    /// @brief Pantalla estatica de mochila que muestra items y sus descripciones
    /// @details Muestra el sprite de la mochila a la izquierda, la lista de items a la derecha,
    ///          y la descripcion del ultimo item mostrado. No requiere interaccion; retorna inmediatamente.
    inline void MochilaView() {
        Common::DrawBackground();

        // Sprite de la mochila (posicion x=15, y=12)
        Common::DrawSprite(15, 12, Mochila);

        const std::vector<std::string> itemsTitle = Common::ArrayToVector(Common::ConcatFont({Common::FONT4_i, Common::FONT4_t, Common::FONT4_e, Common::FONT4_m, Common::FONT4_s}, 1));

        const int titlePanelWidth = Common::Length(Common::MaxString(itemsTitle)) + 16;
        const int titlePanelHeight = itemsTitle.size() + 2;
        const int titlePanelX = Common::RelativeX(0, 3);
        const int titlePanelY = Common::RelativeY(0, 2);

        Common::PrintPrimaryBox(titlePanelX, titlePanelY, titlePanelWidth, titlePanelHeight, itemsTitle, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
        Common::DrawBottomBar();

        // Read items from MockData.h BAG_ITEMS array
        std::vector<std::string> options;
        std::vector<std::string> descriptions;
        for (int i = 0; i < BAG_ITEM_COUNT; i++) {
            options.push_back(BAG_ITEMS[i].name);
            descriptions.push_back(BAG_ITEMS[i].description);
        }

        int selectedOption = 0;
        SelectPrimaryBox1DWithDescription(100, 15, options, descriptions, selectedOption, Common::FOREGROUND_DARK, Common::ORANGE, Common::PINK, Common::ORANGE, 50, 3);



        // Barra inferior

        Common::GoToEnd();
    }

} // namespace Pokemon
