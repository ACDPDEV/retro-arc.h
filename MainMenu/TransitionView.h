#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>

#include "../Common/Consts.h"
#include "../Common/Theme.h"
#include "../Common/Graphics.h"
#include "../Common/UnicodeGlyphs.h"
#include "../Common/Color.h"
#include "../Common/Terminal.h"


inline void TransitionView() {
    std::vector<std::array<int, 3>> gradient = Common::Gradient(Common::WIDTH_SCREEN / 8, {247, 27, 27}, {247, 208, 58});
    srand(time(0));

    Common::HideCursor();
    for (int k = 0; k < Common::WIDTH_SCREEN + Common::WIDTH_SCREEN / 4; k++) {
        for (int i = 0; i < Common::WIDTH_SCREEN / 8; i++) {
            for (int j = 0; j < Common::HEIGHT_SCREEN; j++) {
                if (k + i - Common::WIDTH_SCREEN / 8 < 0) continue;
                if (k + i - Common::WIDTH_SCREEN / 8 >= Common::WIDTH_SCREEN) continue;
                if (j < 0 || j >= Common::HEIGHT_SCREEN) continue;
                int random0 = gradient[i][0] - 25 * (i) / Common::WIDTH_SCREEN + rand() % 10 * (Common::WIDTH_SCREEN - i) / Common::WIDTH_SCREEN;
                int random1 = gradient[i][1] - 25 * (i) / Common::WIDTH_SCREEN + rand() % 10 * (Common::WIDTH_SCREEN - i) / Common::WIDTH_SCREEN;
                int random2 = gradient[i][2] - 25 * (i) / Common::WIDTH_SCREEN + rand() % 10 * (Common::WIDTH_SCREEN - i) / Common::WIDTH_SCREEN;
                int random3 = gradient[i][0] - 25 * (i) / Common::WIDTH_SCREEN + rand() % 10 * (Common::WIDTH_SCREEN - i) / Common::WIDTH_SCREEN;
                int random4 = gradient[i][1] - 25 * (i) / Common::WIDTH_SCREEN + rand() % 10 * (Common::WIDTH_SCREEN - i) / Common::WIDTH_SCREEN;
                int random5 = gradient[i][2] - 25 * (i) / Common::WIDTH_SCREEN + rand() % 10 * (Common::WIDTH_SCREEN - i) / Common::WIDTH_SCREEN;
                int transparentRandom1 = 1 + rand() % Common::WIDTH_SCREEN / 8;
                int transparentRandom2 = 1 + rand() % Common::WIDTH_SCREEN / 8;
                std::array<int, 3> colorForeground, colorBackground;
                if ((i + 1) * 0.75 > transparentRandom1) {
                    colorForeground = {random0, random1, random2};
                } else {
                    colorForeground = Common::BACKGROUND;
                }
                if ((i + 1) * 0.75 > transparentRandom2) {
                    colorBackground = {random3, random4, random5};
                } else {
                    colorBackground = Common::BACKGROUND;
                }
                Common::DrawFillRectangle(k + i - Common::WIDTH_SCREEN / 8, j, 1, 1, Common::LOWER_HALF_BLOCK, colorForeground, colorBackground);
            }
        }
    }
    Common::Color(Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);
    Common::GoToXY(0, Common::HEIGHT_SCREEN + 1);
}
