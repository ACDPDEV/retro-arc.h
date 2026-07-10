#include "BD/Env.h"
#include "Commands/Auth.h"
#include "BD/Labels.h"
#include "BD/Labels.h"
#include "TransitionView.h"
#include "Views/MainMenuView.h"
#include "Views/PresentationView.h"
#include "Views/PasswordView.h"
#include "Views/WrongPasswordView.h"
#include <iostream>

namespace MainMenu {
    inline void MainMenu() {
        PresentationView();
        TransitionView();

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

            TransitionView();

            MainMenuView();
        } else {
            WrongPasswordView();
        }
    }
}
