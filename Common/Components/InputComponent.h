#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../../Common/Graphics.h"
#include "../../Common/Aligned.h"
#include "../../Common/Theme.h"
#include "../../Common/Consts.h"
#include "../../Common/Variables.h"
#include "../../Common/Input.h"

namespace Common {
    inline void TextBoxComponent(
        int x, int y,
        int width, int height,
        std::string &input,
        std::string label = "",
        std::string message = "",
        std::string replaceChar = ""
    ) {
        const std::vector<std::string> formatedInput = CutString(input, width);
        const std::vector<std::string> formatedLabel = CutString(label, width);
        const std::vector<std::string> formatedMessage = {message};

        const int labelWidth = Length(MaxString(formatedLabel));
        const int labelHeight = formatedLabel.size();
        const int labelX = AlignedX(x, width, labelWidth, "center");
        const int labelY = RelativeY(y, - labelHeight);

        const int messageWidth = Length(MaxString(formatedMessage));
        const int messageHeight = formatedMessage.size();
        const int messageX = AlignedX(x, width, messageWidth, "center");
        const int messageY = RelativeY(y, + height);
        int cursorX, cursorY;
        std::string cursorChar = QUADRANTS[5];


        if (Length(input) == 0) {
            cursorX = x;
            cursorY = y;
        } else if (Length(input) >= width - 1) {
            cursorX = RelativeX(x, width - 1);
            cursorY = y;
            cursorChar = "";
        } else {
            cursorX = RelativeX(x, Length(formatedInput[formatedInput.size() - 1]));
            cursorY = y;
        }

        DrawText(
            labelX, labelY,
            labelWidth, labelHeight,
            {label},
            FOREGROUND_LIGHT, BACKGROUND
        );
        DrawFillRectangle(
            x, y,
            width, height,
            EMPTY_BLOCK,
            FOREGROUND_LIGHT, SELECTION_BACKGROUND
        );
        DrawText(
            messageX, messageY,
            messageWidth, messageHeight,
            formatedMessage,
            {200, 150, 100}, BACKGROUND
        );

        if (replaceChar == "") {
            DrawText(
                x, y,
                width, height,
                formatedInput,
                FOREGROUND_LIGHT, SELECTION_BACKGROUND
            );
        } else {
            DrawText(
                x, y,
                width, height,
                {RepeatString(
                    replaceChar,
                    Length(input)
                )},
                FOREGROUND_LIGHT, SELECTION_BACKGROUND
            );
        }

        DrawText(cursorX, cursorY, -1, -1, {QUADRANTS[5]}, FOREGROUND_LIGHT, SELECTION_BACKGROUND);
    }

    inline void InputComponent(
        int x, int y,
        int width, int height,
        std::string& input,
        std::string label = "",
        std::string message = "",
        std::string replaceChar = ""
    ) {
        while (true) {
            TextBoxComponent(
                x, y,
                width, height,
                input,
                label, message, replaceChar
            );

            key = ReadConsoleChar();

            if (key == KEY_ENTER) {
                break;
            } else if (key == KEY_BACKSPACE) {
                if (!input.empty()) {
                    input.pop_back();
                    TextBoxComponent(
                        x, y,
                        width, height,
                        input,
                        label, message, replaceChar
                    );
                }
                continue;
            } else if (input.size() < width && IsAlphaNumChar(key)) {
                for (char c : CastKeyToString(key)) input.push_back(c);
                TextBoxComponent(
                    x, y, width, height,
                    input,
                    label, message, replaceChar
                );
            }
        }
    }
}
