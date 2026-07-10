#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "../Color.h"
#include "../Graphics.h"
#include "../Utils.h"

namespace Common {
    inline void SelectComponent(
        int x, int y,
        std::array<int, 3> backgroundColor,
        std::array<int, 3> selectedColor,
        std::vector<std::string> options, int selectedOption,
        std::array<std::string,2> selectedPadding = {"", ""}
    ) {
        std::string leftPadding = RepeatString(" ", selectedPadding[0].size());
        std::string rightPadding = RepeatString(" ", selectedPadding[1].size());

        const int selectWidth = Length(MaxString(options)) + Length(rightPadding) + Length(leftPadding);
        const int selectHeight = options.size();

        DrawFillRectangle(
            x, y,
            selectWidth, selectHeight,
            EMPTY_BLOCK,
            FOREGROUND_DARK, backgroundColor
        );

        for (int i = 0; i < options.size(); i++) {
            if (selectedOption == i) {
                const std::string& option = selectedPadding[0] + options[i] + selectedPadding[1];
                DrawFillRectangle(
                    x, y + i,
                    selectWidth, 1,
                    EMPTY_BLOCK, FOREGROUND_DARK, selectedColor
                );
                DrawText(
                    x, y + i,
                    selectWidth, 1,
                    std::vector<std::string>{option},
                    FOREGROUND_DARK, selectedColor
                );
            } else {
                const std::string& option = leftPadding + options[i] + rightPadding;
                DrawText(
                    x, y + i,
                    selectWidth, 1,
                    std::vector<std::string>{option},
                    FOREGROUND_DARK, backgroundColor
                );
            }
        }
    }
}
