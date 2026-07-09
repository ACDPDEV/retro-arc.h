#pragma once

#include "../Consts/Options.h"

namespace MainMenu {
    void IncreaseOption(){
        MainMenu::OPTION + 1;
    }

    void DecreaseOption() {
        MainMenu::OPTION - 1;
    }
}
