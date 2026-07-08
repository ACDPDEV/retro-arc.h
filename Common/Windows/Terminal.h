/// @file Windows/Terminal.h
/// @brief Implementación Windows de la API de terminal cross-platform.
/// @details Usa Win32 Console API: GetStdHandle, SetConsoleMode, SetConsoleCursorPosition,
///          GetConsoleScreenBufferInfo, _kbhit/_getch (conio.h), CP_UTF8/CP_ACP.
///          Funciones marcadas `inline` para uso header-only.
///          API idéntica a Linux/Terminal.h.
#pragma once

#include <synchapi.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <array>
#include <string>

namespace Common {

inline void InitTerminalRawMode();

/// @brief Habilita el procesamiento de terminal virtual (ANSI/VT100) para True Color
/// @details Permite usar códigos de escape como \x1b[38;2;R;G;Bm para colores RGB reales
inline void EnableTrueColor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

/// @brief Deshabilita el procesamiento de terminal virtual
/// @details Restaura el modo de consola anterior sin ENABLE_VIRTUAL_TERMINAL_PROCESSING
inline void DisableTrueColor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

/// @brief Verifica si el procesamiento de terminal virtual (ANSI) está habilitado
/// @return true si ANSI/VT processing está activo, false en caso contrario
inline bool IsAnsiEnabled() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    return (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

/// @brief Establece la página de códigos de entrada/salida a UTF-8 (65001)
/// @details Necesario para mostrar correctamente caracteres Unicode/emojis
inline void EnableUTF8() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
}

/// @brief Restaura la página de códigos por defecto del sistema (ANSI/ACP)
inline void DisableUTF8() {
    SetConsoleCP(CP_ACP);
    SetConsoleOutputCP(CP_ACP);
}

/// @brief Establece la visibilidad del cursor de consola
/// @param visible true para mostrar, false para ocultar
inline void SetCursorVisible(bool visible) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hOut, &info);
    info.bVisible = visible;
    SetConsoleCursorInfo(hOut, &info);
}

/// @brief Muestra el cursor de consola
inline void ShowCursor() {
    SetCursorVisible(true);
}

/// @brief Oculta el cursor de consola
inline void HideCursor() {
    SetCursorVisible(false);
}

/// @brief Mueve el cursor a una posición específica (0-indexed)
/// @param x Columna (0 = izquierda)
/// @param y Fila (0 = arriba)
inline void GoToXY (int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = static_cast<short>(x);
    dwPos.Y = static_cast<short>(y);
    SetConsoleCursorPosition(hCon, dwPos);
}

/// @brief Limpia la pantalla y mueve el cursor al inicio
/// @details Usa escape ANSI si está habilitado, sino system("cls")
inline void Clear() {
    system("cls");
    GoToXY(0, 0);
}

/// @brief Obtiene el ancho actual del buffer de consola en columnas
/// @return Ancho en caracteres
inline int GetConsoleWidth() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    return info.srWindow.Right - info.srWindow.Left + 1;
}

/// @brief Obtiene el alto actual del buffer de consola en filas
/// @return Alto en caracteres
inline int GetConsoleHeight() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    return info.srWindow.Bottom - info.srWindow.Top + 1;
}

/// @brief Obtiene el tamaño actual de la consola
/// @return array{width, height} en caracteres
inline std::array<int, 2> GetConsoleSize() {
    return {GetConsoleWidth(), GetConsoleHeight()};
}

/// @brief Verifica si hay una tecla presionada
/// @return true si hay una tecla, false si no
inline bool Kbhit() {
    return _kbhit();
}

/// @brief Obtiene el carácter presionado
/// @return Carácter presionado
inline char Getch() {
    return _getch();
}

inline void Sleep(int ms) {
    ::Sleep(static_cast<DWORD>(ms));
}

/**
 * @brief Limpia una línea de la consola imprimiendo una cantidad determinada de espacios en blanco.
 * * @param lineLength Número de espacios en blanco que se van a generar e imprimir para limpiar la línea.
 */
inline void ClearConsoleLine(int lineLength)
{
    std::string blankSpace = "";
    for(int i = 0; i <= lineLength; i++)
    {
        std::string blankSpace = "";
        for(int i = 0; i <= lineLength; i++)
        {
            blankSpace += " ";
        }
        std::cout << blankSpace;
    }
    std::cout << blankSpace;
}

} // namespace Common
