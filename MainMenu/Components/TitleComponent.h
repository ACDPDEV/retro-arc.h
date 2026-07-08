#pragma once

#include <array>
#include <vector>
#include <string>
#include "../../Common/Font.h"
#include "../../Common/Color.h"
#include "../../Common/Aligned.h"
#include "../../Common/Consts.h"
#include "../../Common/Theme.h"

namespace MainMenu {
    inline void TitleComponent() {
        const std::array<std::string, 9> title = Common::ConcatFont({Common::FONT_R, Common::FONT_E, Common::FONT_T, Common::FONT_R, Common::FONT_O, Common::FONT_A, Common::FONT_R, Common::FONT_C, Common::FONT_DOT, Common::FONT_H}, 2);
        std::vector<std::array<int, 3>> titleColor = Common::Gradient(9, {247, 208, 58}, {247, 27, 27});

        Common::DrawFillRectangle(0, 0, Common::WIDTH_SCREEN, Common::HEIGHT_SCREEN, " ", Common::FOREGROUND, Common::BACKGROUND);
        for (int i = 0; i < title.size(); i++) {
            Common::DrawText(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[i]), "center"), Common::RelativeY(0, i + 4), -1, -1, {title[i]}, titleColor[i], Common::COLOR_DEFAULT);
        }
    }
}
