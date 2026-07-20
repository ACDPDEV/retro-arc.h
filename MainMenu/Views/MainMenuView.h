#pragma once

#include <string>
#include <vector>

#include "../../Common/Components/SelectComponent.h"

#include "../Components/TitleComponent.h"
#include "../Database/Options.h"
#include "../Sprites/Clyde.h"
#include "../../Common/Sprite.h"
#include "../../Common/Utils.h"

namespace MainMenu {
    inline void MainMenuView() {
        Common::DrawBackground();
        TitleComponent();

        const int selectWidth = Common::Length(Common::MaxString(OPTIONS)) + 16;
        const int selectHeight = OPTIONS.size();
        const int selectX = Common::AlignedX(0, Common::WIDTH_SCREEN, selectWidth, "center");
        const int selectY = Common::AlignedY(0, Common::HEIGHT_SCREEN, selectHeight, "center");

        Common::DrawSprite(
            Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(Common::MaxString(Clyde[0])) , "left") + 32, Common::AlignedY(0, Common::HEIGHT_SCREEN, Clyde.size(), "center") + 6,
            Clyde[0]
        );

        Common::SelectComponent(
            selectX, selectY,
            Common::SELECTION_BACKGROUND, Common::ACCENT,
            OPTIONS, OPTION,
            {" [>>>]  ", "        "},
            {1, 1}, 1
        );

        Common::DrawAnimatedSprite(
            Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(Common::MaxString(Clyde[0])) , "left") + 32, Common::AlignedY(0, Common::HEIGHT_SCREEN, Clyde.size(), "center") + 6,
            Clyde,
            200,
            1
        );

        Common::GoToEnd();
    }
}
