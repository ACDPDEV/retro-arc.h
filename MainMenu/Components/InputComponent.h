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

#include "../BD/Env.h"
#include "../BD/Labels.h"

namespace MainMenu {
    inline void TextBoxComponent(
        int x, int y,
        int width, int height,
        std::string &input,
        std::string label = "",
        std::string message = "",
        std::string replaceChar = ""
    ) {
        const std::vector<std::string> formatedInput = Common::CutString(input, width);
        const std::vector<std::string> formatedLabel = Common::CutString(label, width);
        const std::vector<std::string> formatedMessage = {message};

        const int labelWidth = Common::Length(Common::MaxString(formatedLabel));
        const int labelHeight = formatedLabel.size();
        const int labelX = Common::AlignedX(x, width, labelWidth, "center");
        const int labelY = Common::RelativeY(y, - labelHeight);

        const int messageWidth = Common::Length(Common::MaxString(formatedMessage));
        const int messageHeight = formatedMessage.size();
        const int messageX = Common::AlignedX(x, width, messageWidth, "center");
        const int messageY = Common::RelativeY(y, + height);
        int cursorX, cursorY;

        if (input == "") {
            cursorX = x;
            cursorY = y;
        } else {
            cursorX = Common::RelativeX(x, Common::Length(formatedInput[formatedInput.size() - 1]));
            cursorY = y;
        }

        Common::DrawText(
            labelX, labelY,
            labelWidth, labelHeight,
            {label},
            Common::FOREGROUND_LIGHT, Common::BACKGROUND
        );
        Common::DrawFillRectangle(
            x, y,
            width, height,
            Common::EMPTY_BLOCK,
            Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
        );
        Common::DrawText(
            messageX, messageY,
            messageWidth, messageHeight,
            formatedMessage,
            {200, 150, 100}, Common::BACKGROUND
        );

        if (replaceChar == "") {
            Common::DrawText(
                x, y,
                width, height,
                formatedInput,
                Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
            );
        } else {
            Common::DrawText(
                x, y,
                width, height,
                {Common::RepeatString(
                    replaceChar,
                    Common::Length(input)
                )},
                Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
            );
        }

        Common::DrawText(cursorX, cursorY, -1, -1, {Common::QUADRANTS[5]}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
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

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                break;
            } else if (Common::key == Common::KEY_BACKSPACE) {
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
            } else if (input.size() < MAX_PASSWORD_LEN && Common::IsAlphaNumChar(Common::key)) {
                for (char c : Common::CastKeyToString(Common::key)) input.push_back(c);
                TextBoxComponent(
                    x, y, width, height,
                    input,
                    label, message, replaceChar
                );
            }
        }
    }
}
