#include "../MainMenu/MainMenu.h"


int main() {
    Common::InitTerminalRawMode();
    MainMenu::MainMenu();
    Common::ShowCursor();
    return 0;
}
