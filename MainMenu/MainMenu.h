#include "TransitionView.h"
#include "Views/PresentationView.h"
#include "Views/PasswordView.h"

namespace MainMenu {
    inline void MainMenu() {
        PresentationView();
        TransitionView();
        PasswordView();
    }
}
