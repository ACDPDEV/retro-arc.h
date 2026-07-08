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
#include "MainMenuView.h"
#include "WrongPasswordView.h"

namespace MainMenu {
    inline void PasswordMenu() {
        std::string input;

        int inputX = Common::AlignedX(0, Common::WIDTH_SCREEN, MAX_PASSWORD_LEN, "center");
        int inputY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 1, "center") + 1;

        Common::HideCursor();
        TitleComponent();
        bool passed = Key(inputX, inputY);
        std::cout << passed;

        if (passed) {
            MainMenuView();
        } else {
            WrongPasswordView();
        }

        Common::HideCursor();
        Common::Color(Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);
        Common::GoToXY(0, Common::HEIGHT_SCREEN + 1);
    }
}
