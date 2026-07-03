/// @file Linux/Terminal.h
/// @brief Implementación Linux/POSIX de la API de terminal cross-platform.
/// @details Usa termios para modo raw (ICANON/ECHO off), ioctl(TIOCGWINSZ) para tamaño,
///          códigos escape ANSI para cursor/color/clear, setlocale para UTF-8,
///          atexit + SIGINT handler para restauración automática.
///          Requiere llamar InitTerminalRawMode() una vez al inicio de main() para Kbhit/Getch.
///          Funciones marcadas `inline` para uso header-only.
///          API idéntica a Windows/Terminal.h.
#pragma once

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <iostream>
#include <array>

using namespace std;

/// @brief Guarda el estado original de la terminal (modo canónico, con eco)
/// @details Se usa para restaurar la terminal a su estado normal al salir del programa
inline termios g_oldTermios;

/// @brief Restaura la terminal a su estado original (modo canónico, con eco)
/// @details Debe ejecutarse siempre antes de que el programa termine, sea cual sea el motivo
///          (return normal, exit(), Ctrl+C). Se registra automáticamente en InitTerminalRawMode().
inline void RestoreTerminalMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &g_oldTermios);
}

/// @brief Handler de SIGINT (Ctrl+C): restaura la terminal antes de terminar el programa
/// @param signum Número de señal recibida (no se usa, requerido por la firma de signal())
inline void HandleSigint(int signum) {
    RestoreTerminalMode();
    exit(0);
}

/// @brief Pone la terminal en modo no-canónico y sin eco (equivalente al modo que usa conio.h en Windows)
/// @details Necesario para que _kbhit()/_getch() funcionen tecla por tecla sin esperar Enter.
///          Registra la restauración automática al salir (atexit) y ante Ctrl+C (SIGINT).
///          Llamar una sola vez, al inicio de main().
inline void InitTerminalRawMode() {
    tcgetattr(STDIN_FILENO, &g_oldTermios);
    termios newt = g_oldTermios;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    atexit(RestoreTerminalMode);
    signal(SIGINT, HandleSigint);
}

/// @brief Verifica si hay una tecla presionada esperando en el buffer, sin bloquear
/// @return true si hay input disponible para leer con _getch()
/// @details Equivalente a _kbhit() de conio.h. Requiere que InitTerminalRawMode() se haya llamado antes.
inline bool Kbhit() {
    timeval tv{0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

/// @brief Lee un carácter sin esperar Enter y sin hacer eco automático
/// @return El carácter leído
/// @details Equivalente a _getch() de conio.h. Requiere que InitTerminalRawMode() se haya llamado antes.
inline char Getch() {
    return getchar();
}

/// @brief Habilita el procesamiento de color verdadero (True Color / ANSI)
/// @details En Linux esto depende del terminal (xterm, kitty, alacritty, etc).
///          No existe un "modo" que activar como en Windows: los códigos de escape
///          \x1b[38;2;R;G;Bm funcionan siempre que el terminal los soporte.
///          Esta función existe solo por compatibilidad de interfaz con la versión Windows.
inline void EnableTrueColor() {
    // No-op en Linux: el soporte ANSI/True Color es intrínseco al terminal.
    // Se deja vacío para mantener la misma firma de función en ambos SO.
}

/// @brief Deshabilita el procesamiento de terminal virtual
/// @details No-op en Linux, se mantiene por compatibilidad de interfaz.
inline void DisableTrueColor() {
    // No-op en Linux
}

/// @brief Verifica si el terminal soporta color verdadero (True Color)
/// @return true si la variable de entorno COLORTERM indica soporte 24-bit
inline bool IsAnsiEnabled() {
    if (!isatty(STDOUT_FILENO)) return false;
    const char* colorterm = getenv("COLORTERM");
    if (colorterm && (string(colorterm) == "truecolor" || string(colorterm) == "24bit"))
        return true;
    const char* term = getenv("TERM");
    return term != nullptr; // si hay TERM definido, asumimos soporte ANSI básico
}

/// @brief Establece la configuración regional a UTF-8
/// @details En Linux la mayoría de terminales ya usan UTF-8 por defecto,
///          pero esto asegura que cin/cout y las funciones de ancho de caracteres
///          se comporten correctamente con Unicode/emojis.
inline void EnableUTF8() {
    setlocale(LC_ALL, "en_US.UTF-8");
}

/// @brief Restaura la configuración regional por defecto ("C")
inline void DisableUTF8() {
    setlocale(LC_ALL, "C");
}

/// @brief Establece la visibilidad del cursor de terminal
/// @param visible true para mostrar, false para ocultar
inline void SetCursorVisible(bool visible) {
    cout << (visible ? "\x1b[?25h" : "\x1b[?25l") << flush;
}

/// @brief Muestra el cursor de terminal
inline void ShowCursor() {
    SetCursorVisible(true);
}

/// @brief Oculta el cursor de terminal
inline void HideCursor() {
    SetCursorVisible(false);
}

/// @brief Mueve el cursor a una posición específica (0-indexed)
/// @param x Columna (0 = izquierda)
/// @param y Fila (0 = arriba)
inline void GoToXY(int x, int y) {
    // ANSI usa coordenadas 1-indexed: fila;columna
    cout << "\x1b[" << (y + 1) << ";" << (x + 1) << "H";
}

/// @brief Limpia la pantalla y mueve el cursor al inicio
inline void Clear() {
    system("clear");
    GoToXY(0, 0);
}

/// @brief Obtiene el ancho actual del terminal en columnas
/// @return Ancho en caracteres
inline int GetConsoleWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

/// @brief Obtiene el alto actual del terminal en filas
/// @return Alto en caracteres
inline int GetConsoleHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

/// @brief Obtiene el tamaño actual del terminal
/// @return array{width, height} en caracteres
inline array<int, 2> GetConsoleSize() {
    return {GetConsoleWidth(), GetConsoleHeight()};
}

inline void Sleep(int ms) {
    usleep(ms / 1000);
}
