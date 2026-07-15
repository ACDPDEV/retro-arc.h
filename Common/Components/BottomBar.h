#pragma once

#include <iostream>
#include "../../Common/Color.h"
#include "../../Common/Graphics.h"
#include "../../Common/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"

namespace Common
{
    void DrawBottomBar()
    {
        const int barWidth = WIDTH_SCREEN;
        const int barHeight = 3;
        const int barY = HEIGHT_SCREEN - barHeight;
        const int barX = 0;

        Common::DrawFillRectangle(
            barX, barY,
            barWidth, barHeight,
            EMPTY_BLOCK,
            BLUE, BLUE
        );
    }
}
