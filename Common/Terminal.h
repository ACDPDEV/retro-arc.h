#pragma once
#include <windows.h>
#include <iostream>
#include <array>
using namespace std;

/**
 * @brief Habilita el procesamiento de terminal virtual (ANSI/VT100) para True Color.
 */
void EnableTrueColor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

/**
 * @brief Deshabilita el procesamiento de terminal virtual.
 */
void DisableTrueColor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

/**
 * @brief Verifica si el procesamiento de terminal virtual (ANSI) está habilitado.
 * @return true si ANSI/VT processing está activo, false en caso contrario.
 */
bool IsAnsiEnabled() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    return (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

/**
 * @brief Establece la página de códigos de entrada/salida a UTF-8 (65001).
 */
void EnableUTF8() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
}

/**
 * @brief Restaura la página de códigos por defecto del sistema (ANSI/ACP).
 */
void DisableUTF8() {
    SetConsoleCP(CP_ACP);
    SetConsoleOutputCP(CP_ACP);
}

/**
 * @brief Establece la visibilidad del cursor de consola.
 * @param visible true para mostrar, false para ocultar.
 */
void SetCursorVisible(bool visible) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hOut, &info);
    info.bVisible = visible;
    SetConsoleCursorInfo(hOut, &info);
}

/**
 * @brief Muestra el cursor de consola.
 */
void ShowCursor() {
    SetCursorVisible(true);
}

/**
 * @brief Oculta el cursor de consola.
 */
void HideCursor() {
    SetCursorVisible(false);
}

/**
 * @brief Mueve el cursor a una posición específica (0-indexed).
 * @param x Columna (0 = izquierda).
 * @param y Fila (0 = arriba).
 */
void MoveTo(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = static_cast<short>(x);
    dwPos.Y = static_cast<short>(y);
    SetConsoleCursorPosition(hCon, dwPos);
}

/**
 * @brief Limpia la pantalla y mueve el cursor al inicio.
 * Usa escape ANSI si está habilitado, sino system("cls").
 */
void Clear() {
    if (IsAnsiEnabled()) {
        cout << "\x1b[2J\x1b[H";
    } else {
        system("cls");
        MoveTo(0, 0);
    }
}

/**
 * @brief Obtiene el ancho actual del buffer de consola en columnas.
 * @return Ancho en caracteres.
 */
int GetConsoleWidth() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    return info.srWindow.Right - info.srWindow.Left + 1;
}

/**
 * @brief Obtiene el alto actual del buffer de consola en filas.
 * @return Alto en caracteres.
 */
int GetConsoleHeight() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    return info.srWindow.Bottom - info.srWindow.Top + 1;
}

/**
 * @brief Obtiene el tamaño actual de la consola.
 * @return array{width, height} en caracteres.
 */
array<int, 2> GetConsoleSize() {
    return {GetConsoleWidth(), GetConsoleHeight()};
}
