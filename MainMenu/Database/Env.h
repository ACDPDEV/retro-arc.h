#pragma once

#include <string>

#include "Labels.h"

namespace MainMenu {
    const std::string CLAVE = "1234";
    inline std::string INPUT = "";
    inline std::string MESSAGE = "";
    const std::string LABEL = INPUT_LABEL;

    const int MAX_ATTEMPTS = 3;
    const int MAX_PASSWORD_LEN = 24;
    inline bool BLOCKED = false;
    inline bool HIDDEN_PASSWORD = true;
    const std::string HIDDEN_CHAR = "*";
}
