#pragma once

#include <iostream>
#include <array>
#include "../../Common/Color.h"
#include "../../Common/Graphics.h"
#include "../../Common/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"

namespace Common
{
    void DrawLifeBar(int x, int y, int gradientLength, std::array<int, 3> initColor, std::array<int, 3> endColor, std::array<int, 3> background)
    {
        std::vector<std::array<int, 3>> colors = Gradient(gradientLength, initColor, endColor);
        for (size_t i = 0; i < colors.size(); i++)
        {
            Common::DrawFillRectangle(x + i, y, 1, 1, Common::FULL_BLOCK, colors[i], Common::COLOR_DEFAULT);
        }
        std::cout.flush();
    }
}