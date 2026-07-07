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
    vector<array<int, 3>> gradient = Gradient(WIDTH_SCREEN / 8, {247, 27, 27}, {247, 208, 58});
    srand(time(0));

    HideCursor();
    for (int k = 0; k < WIDTH_SCREEN + WIDTH_SCREEN / 4; k++) {
        for (int i = 0; i < WIDTH_SCREEN / 8; i++) {
            for (int j = 0; j < HEIGHT_SCREEN; j++) {
                if (k + i - WIDTH_SCREEN / 8 < 0) continue;
                if (k + i - WIDTH_SCREEN / 8 >= WIDTH_SCREEN) continue;
                if (j < 0 || j >= HEIGHT_SCREEN) continue;
                int random0 = gradient[i][0] - 25 * (i) / WIDTH_SCREEN + rand() % 10 * (WIDTH_SCREEN - i) / WIDTH_SCREEN;
                int random1 = gradient[i][1] - 25 * (i) / WIDTH_SCREEN + rand() % 10 * (WIDTH_SCREEN - i) / WIDTH_SCREEN;
                int random2 = gradient[i][2] - 25 * (i) / WIDTH_SCREEN + rand() % 10 * (WIDTH_SCREEN - i) / WIDTH_SCREEN;
                int random3 = gradient[i][0] - 25 * (i) / WIDTH_SCREEN + rand() % 10 * (WIDTH_SCREEN - i) / WIDTH_SCREEN;
                int random4 = gradient[i][1] - 25 * (i) / WIDTH_SCREEN + rand() % 10 * (WIDTH_SCREEN - i) / WIDTH_SCREEN;
                int random5 = gradient[i][2] - 25 * (i) / WIDTH_SCREEN + rand() % 10 * (WIDTH_SCREEN - i) / WIDTH_SCREEN;
                int transparentRandom1 = 1 + rand() % WIDTH_SCREEN / 8;
                int transparentRandom2 = 1 + rand() % WIDTH_SCREEN / 8;
                array<int, 3> colorForeground, colorBackground;
                if ((i + 1) * 0.75 > transparentRandom1) {
                    colorForeground = {random0, random1, random2};
                } else {
                    colorForeground = BACKGROUND;
                }
                if ((i + 1) * 0.75 > transparentRandom2) {
                    colorBackground = {random3, random4, random5};
                } else {
                    colorBackground = BACKGROUND;
                }
                DrawFillRectangle(k + i - WIDTH_SCREEN / 8, j, 1, 1, LOWER_HALF_BLOCK, colorForeground, colorBackground);
            }
        }
    }
    Color(COLOR_DEFAULT, COLOR_DEFAULT);
    GoToXY(0, HEIGHT_SCREEN + 1);
}
