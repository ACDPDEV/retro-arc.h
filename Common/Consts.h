#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
    #include "Windows/Keys.h"
#else
    #include "Linux/Keys.h"
#endif

namespace Common {
    const std::string CLAVE = "1234";
    const int MAX_ATTEMPTS = 3;
    const int WIDTH_SCREEN = 200;
    const int HEIGHT_SCREEN = 50;
    const int MAX_FEEDBACK_MESSAGE_LENGTH = 80;
}
