#pragma once

#include <string>
#include <vector>

#include "../../Common/Components/SelectComponent.h"

#include "../Components/TitleComponent.h"
#include "../BD/Options.h"

namespace MainMenu {
    inline void MainMenuView() {
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

        Common::GoToXY(0, Common::HEIGHT_SCREEN + 1);
    }
}
