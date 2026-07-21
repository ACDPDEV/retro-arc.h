#include "Common/Terminal.h"
#include "Juegos/Buscaminas/Buscaminas.h"
#include "Juegos/Pokemon/Pokemon.h"
#include "Juegos/Invasion Espacial/pantallas.h"
#include "Juegos/Tictactoe/Tictactoe.h"
#include "MainMenu/Database/Options.h"
#include "MainMenu/MainMenu.h"
#include "MainMenu/Database/State.h"
#include "MainMenu/Views/CreditsView.h"

int main() {
    Common::InitTerminalRawMode();
    Common::EnableUTF8();
    Common::EnableTrueColor();

    while(MainMenu::isMainMenuIsRunning) {
        MainMenu::MainMenu();
        switch (MainMenu::OPTION) {
            case 0:
                Pokemon::Pokemon();
                break;
            case 1:
                Buscaminas::PlayMinesweeper();
                break;
            case 2:
                // Tictactoe
                InvasionEspacial::ejecutarJuego("COMANDANTE");
                break;
            case 3:
                Tictactoe::PlayTicTacToe();
                break;
            case 4:
                MainMenu::CreditsView();
                break;
            case 5:
                MainMenu::isMainMenuIsRunning = false;
                break;
        }
    }
}
