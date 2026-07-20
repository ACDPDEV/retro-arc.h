#pragma once

#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/SelectComponent.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Utils.h"
#include "../Components/MenuOptions.h"
#include "../Components/TitleComponent.h"

namespace Pokemon {

    /// @brief Renderiza el menu principal de Pokemon con opciones navegables
    /// @return Indice de la opcion seleccionada por el usuario
    inline int MenuView() {
        OPTION = 0;

        Common::DrawBackground();

        TitleComponent();

        const int selectWidth = Common::Length(Common::MaxString(OPTIONS)) + 16;
        const int selectHeight = OPTIONS.size();
        const int selectX = Common::AlignedX(0, Common::WIDTH_SCREEN, selectWidth, "center");
        const int selectY = Common::AlignedY(0, Common::HEIGHT_SCREEN, selectHeight, "center");

        Common::SelectComponent(
            selectX, selectY,
            Common::SELECTION_BACKGROUND, Common::ACCENT,
            OPTIONS, OPTION,
            {" [>>>]  ", "        "},
            {1, 1}, 1
        );

        Common::DrawBottomBar();

        Common::GoToEnd();

        return OPTION;
    }
}
