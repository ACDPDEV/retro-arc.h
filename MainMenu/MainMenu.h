#pragma once

#include <iostream>

#include "../Common/Components/TransitionComponent.h"

#include "Database/Env.h"
#include "Commands/Auth.h"
#include "Database/Labels.h"
#include "Views/MainMenuView.h"
#include "Views/PresentationView.h"
#include "Views/PasswordView.h"
#include "Views/WrongPasswordView.h"
#include "Views/CreditsView.h"

#include "../Juegos/Pokemon/Pokemon.h"
#include "../Juegos/Buscaminas/Buscaminas.h"
#include "../Juegos/Invasion Espacial/juego.h"
#include "../Juegos/Tictactoe/Tictactoe.h"

namespace MainMenu {
    inline void MainMenu() {
        PresentationView();
        Common::TransitionComponent();

        for (int i = 0; i < MAX_ATTEMPTS; i++) {
            PasswordView();
            if (isValidPassword()) {
                break;
            } else {
                MESSAGE = WRONG_PASSWORD_MESSAGE;
                INPUT = "";
            }
        }

        if (isValidPassword()) {
            BLOCKED = true;

            MESSAGE = AUTH_SUCCESS_MESSAGE + "(1s)";
            PasswordView();

            Common::Sleep(1000);

            MESSAGE = AUTH_SUCCESS_MESSAGE + "(0s)";
            PasswordView();

            Common::TransitionComponent();

                MainMenuView();

                switch (MainMenu::OPTION) {
                    case 0:
                        Pokemon::Pokemon();
                        break;
                    case 1:
                        Buscaminas::PlayMinesweeper();
                        break;
                    case 2:
                        InvasionEspacial::ejecutarJuego("COMANDANTE");
                        break;
                    case 3:
                        Tictactoe::PlayTicTacToe();
                        break;
                    case 4:
                        MainMenu::CreditsView();
                        return;
                }
        } else {
            WrongPasswordView();
        }
    }
    inline void MainMenuSelectView() {
        while (true) {
            MainMenuView();

            switch (MainMenu::OPTION) {
                case 0:
                    Pokemon::Pokemon();
                    break;
                case 1:
                    Buscaminas::PlayMinesweeper();
                    break;
                case 2:
                    InvasionEspacial::ejecutarJuego("COMANDANTE");
                    break;
                case 3:
                    Tictactoe::PlayTicTacToe();
                    break;
                case 4:
                    MainMenu::CreditsView();
                    return;
            }
        }
    }
}
