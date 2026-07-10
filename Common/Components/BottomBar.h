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
        Common::DrawFillRectangle(0, 48, WIDTH_SCREEN, 3, EMPTY_BLOCK, BLUE, BLUE);
    }
}