#include "Juegos/Buscaminas/Buscaminas.h"
#include "Juegos/Pokemon/Pokemon.h"
#include "MainMenu/Database/Options.h"
#include "MainMenu/MainMenu.h"

int main() {
    Common::InitTerminalRawMode();

    MainMenu::MainMenu();
    switch (MainMenu::OPTION) {
        case 0:
            Pokemon::Pokemon();
            break;
        case 1:
            Minesweeper::PlayMinesweeper();
            break;
        case 2:
            // Batalla Naval
            break;
        case 3:
            // Invasion Espacial
            break;
        case 4:
            // Tictactoe
            break;
        case 5:
            // Créditos
            break;
    }
}
