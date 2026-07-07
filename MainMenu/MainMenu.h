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

inline void MainMenu() {
    const array<string, 9> title = ConcatFont({FONT_R, FONT_E, FONT_T, FONT_R, FONT_O, FONT_A, FONT_R, FONT_C, FONT_DOT, FONT_H}, 2);
    vector<array<int, 3>> titleColor = Gradient(9, {247, 208, 58}, {247, 27, 27});
    string input;

    HideCursor();
    DrawFillRectangle(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN, " ", FOREGROUND, BACKGROUND);
    for (int i = 0; i < title.size(); i++) {
        DrawText(AlignedX(0, WIDTH_SCREEN, Length(title[i]), "center"), RelativeY(0, i + 4), -1, -1, {title[i]}, titleColor[i], COLOR_DEFAULT);
    }


    DrawText(AlignedX(0, WIDTH_SCREEN, 24, "center"), AlignedY(0, HEIGHT_SCREEN, 1, "center"), 24, 1, {"Ingrese su contraseña:"}, FOREGROUND, BACKGROUND);
    DrawFillRectangle(AlignedX(0, WIDTH_SCREEN, 24, "center"), AlignedY(0, HEIGHT_SCREEN, 1, "center") + 1, 24, 1, " ", FOREGROUND, SELECTION_BACKGROUND);

    ShowCursor();
    GoToXY(AlignedX(0, WIDTH_SCREEN, 24, "center"), AlignedY(0, HEIGHT_SCREEN, 1, "center") + 1); cin >> input;
    HideCursor();

    Color(COLOR_DEFAULT, COLOR_DEFAULT);
    GoToXY(0, HEIGHT_SCREEN + 1);
}
