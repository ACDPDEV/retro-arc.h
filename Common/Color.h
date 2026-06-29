#pragma once
#include <array>
#include <string>
using namespace std;

/// Generates an ANSI escape sequence for colored terminal output.
/// @param foreground Foreground RGB color array [r, g, b] (0-255 each)
/// @param background Background RGB color array [r, g, b] (0-255 each)
/// @return ANSI escape sequence string for 24-bit true color (foreground + background)
string color(int foreground[3], int background[3]) {
    return
        "\033[38;2;"
        + to_string(foreground[0]) + ";"
        + to_string(foreground[1]) + ";"
        + to_string(foreground[2]) + ";48;2;"
        + to_string(background[0]) + ";"
        + to_string(background[1]) + ";"
        + to_string(background[2]) + "m";
}
