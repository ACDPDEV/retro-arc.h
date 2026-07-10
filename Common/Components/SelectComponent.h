#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "../Input.h"
#include "../Color.h"
#include "../Graphics.h"
#include "../Utils.h"
#include "../Variables.h"

namespace Common {
    inline void StaticSelectComponent(
        int x, int y,
        std::array<int, 3> backgroundColor,
        std::array<int, 3> selectedColor,
        std::vector<std::string> &options, int selectedOption,
        std::array<std::string,2> selectedPadding = {"", ""},
        std::array<int, 2> verticalPadding = {0, 0},
        int innerGap = 0
    ) {
        std::string leftPadding = RepeatString(" ", selectedPadding[0].size());
        std::string rightPadding = RepeatString(" ", selectedPadding[1].size());

        const int selectWidth = Length(MaxString(options)) + Length(rightPadding) + Length(leftPadding);
        const int selectHeight = options.size() + innerGap * (options.size() - 1) + verticalPadding[0] + verticalPadding[1];

        DrawFillRectangle(
            x, y,
            selectWidth, selectHeight,
            EMPTY_BLOCK,
            FOREGROUND_LIGHT, SELECTION_BACKGROUND
        );

        for (int i = 0; i < options.size(); i++) {
            const std::string& rest = RepeatString(" ", selectWidth - Length(options[i]) - Length(leftPadding) - Length(rightPadding));

            if (selectedOption == i) {
                const std::string& option = selectedPadding[0] + options[i] + rest + selectedPadding[1];
                DrawText(
                    x, y + (i * (innerGap + 1) + verticalPadding[0]),
                    selectWidth, 1,
                    {option},
                    FOREGROUND_DARK, selectedColor
                );
            } else {
                const std::string& option = leftPadding + options[i] + rest + rightPadding;
                DrawText(
                    x, y + (i * (innerGap + 1) + verticalPadding[0]),
                    selectWidth, 1,
                    {option},
                    FOREGROUND_LIGHT, backgroundColor
                );
            }
        }
    }

    inline void SelectComponent(
        int x, int y,
        std::array<int, 3> backgroundColor,
        std::array<int, 3> selectedColor,
        std::vector<std::string> options, int &selectedOption,
        std::array<std::string,2> selectedPadding = {"", ""},
        std::array<int, 2> verticalPadding = {0, 0},
        int innerGap = 0
    ) {
        while (true) {
            StaticSelectComponent(
                x, y,
                backgroundColor, selectedColor,
                options, selectedOption,
                selectedPadding, verticalPadding, innerGap
            );

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                break;
            } else if (Common::key == Common::KEY_ARROW_TOP) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (Common::key == Common::KEY_ARROW_BOTTOM) {
                selectedOption = (selectedOption + 1) % options.size();
            }
        }
    }
}
