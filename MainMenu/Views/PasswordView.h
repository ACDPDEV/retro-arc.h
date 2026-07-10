#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../../Common/Consts.h"
#include "../../Common/Aligned.h"
#include "../../Common/Graphics.h"
#include "../../Common/Font.h"
#include "../../Common/Color.h"
#include "../../Common/Utils.h"
#include "../../Common/Theme.h"
#include "../../Common/Input.h"

#include "../Commands/Auth.h"
#include "../Components/TitleComponent.h"
#include "../Components/InputComponent.h"
#include "../BD/Env.h"

namespace MainMenu {
    inline void PasswordView() {
        const int inputX = Common::AlignedX(0, Common::WIDTH_SCREEN, MAX_PASSWORD_LEN, "center");
        const int inputY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 1, "center") + 1;
        const int inputWidth = MAX_PASSWORD_LEN;
        const int inputHeight = 1;

        Common::HideCursor();
        TitleComponent();

        if (BLOCKED) {
            if (HIDDEN_PASSWORD) {
                TextBoxComponent(
                    inputX, inputY,
                    inputWidth, inputHeight,
                    INPUT,
                    LABEL, MESSAGE, HIDDEN_CHAR
                );
            } else {
                TextBoxComponent(
                    inputX, inputY,
                    inputWidth, inputHeight,
                    INPUT,
                    LABEL, MESSAGE
                );
            }
        } else {
            if (HIDDEN_PASSWORD) {
                InputComponent(
                    inputX, inputY,
                    inputWidth, inputHeight,
                    INPUT,
                    LABEL, MESSAGE, HIDDEN_CHAR
                );
            } else {
                InputComponent(
                    inputX, inputY,
                    inputWidth, inputHeight,
                    INPUT,
                    LABEL, MESSAGE
                );
            }
        }

        Common::GoToXY(0, Common::HEIGHT_SCREEN + 1);
    }
}
