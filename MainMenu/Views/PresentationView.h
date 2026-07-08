#pragma once

#include <iostream>
#include <ratio>
#include <string>

#include "../../Common/Consts.h"
#include "../../Common/Aligned.h"
#include "../../Common/Graphics.h"
#include "../../Common/Font.h"
#include "../../Common/Color.h"
#include "../../Common/Utils.h"
#include "../../Common/Theme.h"
#include "../../Common/Sprite.h"
#include "../Components/ArcadeLeft.h"
#include "../Components/ArcadeRight.h"


namespace MainMenu {
    inline void PresentationView() {
        const std::array<std::string, 9> title = Common::ConcatFont({Common::FONT_R, Common::FONT_E, Common::FONT_T, Common::FONT_R, Common::FONT_O, Common::FONT_A, Common::FONT_R, Common::FONT_C, Common::FONT_DOT, Common::FONT_H}, 2);
        std::vector<std::array<int, 3>> titleColor = Common::Gradient(9, {247, 208, 58}, {247, 27, 27});

        Common::EnableUTF8();
        Common::Clear();
        Common::HideCursor();
        Common::DrawFillRectangle(0, 0, Common::WIDTH_SCREEN, Common::HEIGHT_SCREEN, " ", Common::FOREGROUND, Common::BACKGROUND);
        Common::DrawSprite(2, Common::AlignedY(0, Common::HEIGHT_SCREEN, ArcadeLeft.size(), "bottom") - 1, ArcadeLeft);
        Common::DrawSprite(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(Common::MaxString(ArcadeRight)), "right") - 2, Common::AlignedY(0, Common::HEIGHT_SCREEN, ArcadeRight.size(), "bottom") - 1, ArcadeRight);
        for (int k = 0; k < 100; k++) {
            for (int i = 0; i < title.size(); i++) {
                Common::DrawText(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[i]), "center"), Common::AlignedY(-5, Common::HEIGHT_SCREEN, 9, "center") + i, -1, -1, {title[i]}, {Common::BACKGROUND[0] + (titleColor[i][0] - Common::BACKGROUND[0]) * k / 100, Common::BACKGROUND[1] + (titleColor[i][1] - Common::BACKGROUND[1]) * k / 100, Common::BACKGROUND[2] + (titleColor[i][2] - Common::BACKGROUND[2]) * k / 100}, Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(400 / (k + 1));
        }
        Common::GoToXY(0, Common::HEIGHT_SCREEN + 1);
        Common::Color(Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);
        Common::Sleep(1000);
    }
}
