#include "Juegos/Buscaminas/Buscaminas.h"
#include "Juegos/Pokemon/Pokemon.h"
#include "Juegos/Invasion Espacial/pantallas.h"
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
            Buscaminas::PlayMinesweeper();
            break;
        case 2:
            // Batalla Naval
            break;
        case 3:
            InvasionEspacial::ejecutarJuego("COMANDANTE");
            break;
        case 4:
            // Tictactoe
            break;
        case 5:
            // Créditos
            break;
    }
}
