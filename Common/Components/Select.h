#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "../Color.h"
#include "../Graphics.h"
#include "../Utils.h"

using namespace std;

inline void ComponentSelect(
    int x, int y,
    array<int, 3> backgroundColor,
    array<int, 3> selectedColor,
    vector<string> options, int selectedOption,
    array<string,2> selectedPadding = {"", ""}
) {
    string leftPadding = RepeatString(" ", selectedPadding[0].size());
    string rightPadding = RepeatString(" ", selectedPadding[1].size());
    DrawFillRectangle(x, y, MaxStringLength(options), options.size(), " ", COLOR_DEFAULT, backgroundColor);
    for (int i = 0; i < options.size(); i++) {
        GoToXY(x, y + i);
        if (selectedOption == i) {
            string paddedOption = selectedPadding[0] + options[i] + selectedPadding[1];
            cout << Color(COLOR_DEFAULT, selectedColor) << paddedOption;
        } else {
            cout << Color(COLOR_DEFAULT, backgroundColor) << leftPadding << options[i] << rightPadding;
        }
    }
}
