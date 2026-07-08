#pragma once

#include <array>
#include <vector>
#include <string>
#include "../../Common/Font.h"
#include "../../Common/Color.h"
#include "../../Common/Aligned.h"
#include "../../Common/Consts.h"
#include "../../Common/Theme.h"

inline void TitleComponent() {
    const array<string, 9> title = ConcatFont({FONT_R, FONT_E, FONT_T, FONT_R, FONT_O, FONT_A, FONT_R, FONT_C, FONT_DOT, FONT_H}, 2);
    vector<array<int, 3>> titleColor = Gradient(9, {247, 208, 58}, {247, 27, 27});

    DrawFillRectangle(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN, " ", FOREGROUND, BACKGROUND);
    for (int i = 0; i < title.size(); i++) {
        DrawText(AlignedX(0, WIDTH_SCREEN, Length(title[i]), "center"), RelativeY(0, i + 4), -1, -1, {title[i]}, titleColor[i], COLOR_DEFAULT);
    }
}
