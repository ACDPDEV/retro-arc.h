#pragma once

#include <iostream>
#include <ratio>
#include <string>

#include "../Common/Consts.h"
#include "../Common/Aligned.h"
#include "../Common/Graphics.h"
#include "../Common/Font.h"
#include "../Common/Color.h"
#include "../Common/Utils.h"
#include "../Common/Theme.h"


using namespace std;

inline void PresentationView() {
    const array<string, 9> title = ConcatFont({FONT_R, FONT_E, FONT_T, FONT_R, FONT_O, FONT_A, FONT_R, FONT_C, FONT_DOT, FONT_H}, 2);
    vector<array<int, 3>> titleColor = Gradient(9, {247, 208, 58}, {247, 27, 27});

    HideCursor();
    DrawFillRectangle(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN, " ", FOREGROUND, BACKGROUND);
    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < title.size(); i++) {
            DrawText(AlignedX(0, WIDTH_SCREEN, Length(title[i]), "center"), AlignedY(-5, HEIGHT_SCREEN, 9, "center") + i, -1, -1, {title[i]}, {BACKGROUND[0] + (titleColor[i][0] - BACKGROUND[0]) * k / 100, BACKGROUND[1] + (titleColor[i][1] - BACKGROUND[1]) * k / 100, BACKGROUND[2] + (titleColor[i][2] - BACKGROUND[2]) * k / 100}, COLOR_DEFAULT);
        }
        cout.flush();
        Sleep(300 / (k + 1));
    }
    GoToXY(0, HEIGHT_SCREEN + 1);
    Color(COLOR_DEFAULT, COLOR_DEFAULT);
}
