#pragma once

#include "../Components/TitleComponent.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Terminal.h"


namespace Pokemon {
    inline void MenuView() {

        Common::DrawBackground();

        TitleComponent();
        Common::DrawBottomBar();

        Common::GoToEnd();
    }
}
