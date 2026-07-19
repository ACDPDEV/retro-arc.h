/// @file Terminal.h
/// @brief API unificada de terminal cross-platform (Windows/Linux).
/// @details Fachada que incluye la implementación específica por SO:
///          - Windows: Common/Windows/Terminal.h (Win32 Console API, conio.h)
///          - Linux:   Common/Linux/Terminal.h (POSIX termios, ANSI nativo)
///          En Linux, InitTerminalRawMode() se llama automáticamente al incluir.
///          API común: EnableTrueColor, DisableTrueColor, IsAnsiEnabled,
///          EnableUTF8, DisableUTF8, SetCursorVisible, ShowCursor, HideCursor,
///          GoToXY, Clear, GetConsoleWidth, GetConsoleHeight, GetConsoleSize,
///          Kbhit, Getch, Sleep.
/// @note En Linux, Kbhit/Getch requieren que la terminal esté en modo raw
///       (InitTerminalRawMode() se auto-llama al incluir este header en Linux).
#ifdef _WIN32
    #pragma once

    #include "Windows/Terminal.h"
#else
    #pragma once

    #include "Linux/Terminal.h"
#endif

namespace Common {
    inline void GoToEnd() {
        GoToXY(0, HEIGHT_SCREEN + 1);
    }
}
