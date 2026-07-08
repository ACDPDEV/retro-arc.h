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
#include "../../Common/Auth.h"

#include "../Components/TitleComponent.h"
#include "MainMenuView.h"
#include "WrongPasswordView.h"

using namespace std;

inline void PasswordMenu() {
    string input;

    int inputX = AlignedX(0, WIDTH_SCREEN, MAX_PASSWORD_LEN, "center");
    int inputY = AlignedY(0, HEIGHT_SCREEN, 1, "center") + 1;

    HideCursor();
    TitleComponent();
    bool passed = Key(inputX, inputY);
    cout << passed;

    if (passed) {
        MainMenuView();
    } else {
        WrongPasswordView();
    }

    HideCursor();
    Color(COLOR_DEFAULT, COLOR_DEFAULT);
    GoToXY(0, HEIGHT_SCREEN + 1);
}
