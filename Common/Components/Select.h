#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "../Color.h"
#include "../Graphics.h"
#include "../Utils.h"

namespace Common
{
    inline void ComponentSelect(
        int x, int y,
        std::array<int, 3> backgroundColor,
        std::array<int, 3> selectedColor,
        std::vector<std::string> options, int selectedOption,
        std::array<std::string,2> selectedPadding = {"", ""}
    ) {
        std::string leftPadding = RepeatString(" ", selectedPadding[0].size());
        std::string rightPadding = RepeatString(" ", selectedPadding[1].size());
        DrawFillRectangle(x, y, MaxStringLength(options), options.size(), " ", COLOR_DEFAULT, backgroundColor);
        for (int i = 0; i < options.size(); i++) {
            GoToXY(x, y + i);
            if (selectedOption == i) {
                std::string paddedOption = selectedPadding[0] + options[i] + selectedPadding[1];
                std::cout << Color(COLOR_DEFAULT, selectedColor) << paddedOption;
            } else {
                std::cout << Color(COLOR_DEFAULT, backgroundColor) << leftPadding << options[i] << rightPadding;
            }
        }
    }
}