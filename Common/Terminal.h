/// @file Terminal.h
/// @brief Fachada cross-platform para API de terminal.
/// @details Incluye Windows/Terminal.h (Win32 Console API) o Linux/Terminal.h (POSIX/ANSI) según _WIN32.
///          API unificada: EnableTrueColor, DisableTrueColor, IsAnsiEnabled, EnableUTF8, DisableUTF8,
///          SetCursorVisible, ShowCursor, HideCursor, GoToXY, Clear, GetConsoleWidth, GetConsoleHeight,
///          GetConsoleSize, Kbhit, Getch, Sleep.
///          Linux requiere InitTerminalRawMode() al inicio para Kbhit/Getch.
#ifdef _WIN32
    #include "Windows/Terminal.h"
#else
    #include "Linux/Terminal.h"
#endif
