#pragma once

#include <array>
#include <vector>
#include <string>

#include "../../../Common/Font.h"
#include "../../../Common/Color.h"
#include "../../../Common/Aligned.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Graphics.h"

namespace Pokemon {
    inline int calculateTitleX(
        std::array<std::string, 4> title,
        int i
    ) {
        return Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[i]), "center");
    }

    inline int calculateTitleY(
        std::array<std::string, 4> title,
        int i
    ) {
        return Common::RelativeY(0, i + 4);
    }

    inline void TitleComponent() {
        const std::array<std::string, 4> title = Common::ConcatFont({
            Common::FONT_i,
            Common::FONT_n,
            Common::FONT_g,
            Common::FONT_r,
            Common::FONT_e,
            Common::FONT_s,
            Common::FONT_e,
            Common::FONT_blank,
            Common::FONT_s,
            Common::FONT_u,
            Common::FONT_blank,
            Common::FONT_n,
            Common::FONT_o,
            Common::FONT_m,
            Common::FONT_b,
            Common::FONT_r,
            Common::FONT_e,
            Common::FONT_blank,
            Common::FONT_j,
            Common::FONT_u,
            Common::FONT_g,
            Common::FONT_a,
            Common::FONT_d,
            Common::FONT_o,
            Common::FONT_r,
            Common::FONT_blank,
            Common::FONT_1
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
