#pragma once

#include "../../Common/Components/SelectComponent.h"

#include "../Components/TitleComponent.h"
#include <string>
#include <vector>

namespace MainMenu {
    inline void MainMenuView() {
        Common::DrawBackground();
        TitleComponent();

        const std::vector<std::string> options = {
            "Pokemon",
            "Buscaminas",
            "Batalla Naval",
            "Tic Tac Toe",
            "Invasores Espaciales",
            "Creditos"
        };


        const int selectWidth = Common::Length(Common::MaxString(options));
        const int selectHeight = options.size();
        const int selectX = Common::AlignedX(0, Common::WIDTH_SCREEN, selectWidth, "center");
        const int selectY = Common::AlignedY(0, Common::HEIGHT_SCREEN, selectHeight, "center");

        Common::SelectComponent(selectX, selectY, Common::SELECTION_BACKGROUND, Common::ACCENT, options, 0, {"[>>>]  ", ""});
    }
}
