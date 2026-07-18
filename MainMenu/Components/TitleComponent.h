#pragma once

#include <array>
#include <vector>
#include <string>

#include "../../Common/Font.h"
#include "../../Common/Color.h"
#include "../../Common/Aligned.h"
#include "../../Common/Consts.h"
#include "../../Common/Theme.h"
#include "../../Common/Graphics.h"

namespace MainMenu {
    inline int calculateTitleX(
        std::array<std::string, 9> title,
        int i
    ) {
        return Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[i]), "center");
    }

    inline int calculateTitleY(
        std::array<std::string, 9> title,
        int i
    ) {
        return Common::RelativeY(0, i + 4);
    }

    inline void TitleComponent() {
        const std::array<std::string, 9> title = Common::ConcatFont({
            Common::FONT9_R,
            Common::FONT9_E,
            Common::FONT9_T,
            Common::FONT9_R,
            Common::FONT9_O,
            Common::FONT9_A,
            Common::FONT9_R,
            Common::FONT9_C,
            Common::FONT9_DOT,
            Common::FONT9_H
        }, 2);

        const std::vector<std::array<int, 3>> titleColor = Common::Gradient(
            9,
            {247, 208, 58},
            {247, 27, 27}
        );

        for (int i = 0; i < title.size(); i++) {
            Common::DrawText(
                calculateTitleX(title, i),
                calculateTitleY(title, i),
                -1, -1,
                {title[i]},
                titleColor[i],
                Common::BACKGROUND
            );
        }
    }
}
