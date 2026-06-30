#pragma once
#include <windows.h>

void EnableTrueColor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void DisableTrueColor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void EnableUTF8() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
}

void DisableUTF8() {
    SetConsoleCP(CP_ACP);
    SetConsoleOutputCP(CP_ACP);
}

void SetCursorVisible(bool visible) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hOut, &info);
    info.bVisible = visible;
    SetConsoleCursorInfo(hOut, &info);
}

void ShowCursor() {
    SetCursorVisible(true);
}

void HideCursor() {
    SetCursorVisible(false);
}
