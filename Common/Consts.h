#pragma once
#include <string>
#include <vector>

#ifdef _WIN32
    #pragma once

    #include "Windows/Keys.h"
#else
    #pragma once

    #include "Linux/Keys.h"
#endif

namespace Common {
    const int WIDTH_SCREEN = 200;
    const int HEIGHT_SCREEN = 50;
    const int MAX_FEEDBACK_MESSAGE_LENGTH = 80;

}
