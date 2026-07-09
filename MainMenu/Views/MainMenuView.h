#pragma once

#include <string>
#include <vector>

#include "../../Common/Components/SelectComponent.h"

#include "../Components/TitleComponent.h"
#include "../Consts/Options.h"
#include "../Commands/Select.h"

namespace MainMenu {
    inline void MainMenuView() {
        Common::DrawBackground();
        TitleComponent();


        const int selectWidth = Common::Length(Common::MaxString(OPTIONS));
        const int selectHeight = OPTIONS.size();
        const int selectX = Common::AlignedX(0, Common::WIDTH_SCREEN, selectWidth, "center");
        const int selectY = Common::AlignedY(0, Common::HEIGHT_SCREEN, selectHeight, "center");


    }
}
