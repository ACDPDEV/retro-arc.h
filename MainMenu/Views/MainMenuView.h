#pragma once

#include

#include "../Components/TitleComponent.h"
#include <string>
#include <vector>

namespace MainMenu {
    inline void MainMenuView() {
        Common::DrawBackground();
        TitleComponent();

        const int selectWidth = Common::Length(Common::MaxString(OPTIONS));
        const int selectHeight = OPTIONS.size();
        const int selectX = Common::AlignedX(0, Common::WIDTH_SCREEN, selectWidth, "center");
        const int selectY = Common::AlignedY(0, Common::HEIGHT_SCREEN, selectHeight, "center");

        Common::SelectComponent(selectX, selectY, Common::SELECTION_BACKGROUND, Common::ACCENT, OPTIONS, 0, {"[>>>]  ", ""});
    }
}
