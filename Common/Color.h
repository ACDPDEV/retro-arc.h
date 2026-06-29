#pragma once
#include <array>
#include <string>
using namespace std;

inline string color(array<int, 3> foreground, int background[]) {
    return
        "\033[38;2;"
        + to_string(foreground[0]) + ";"
        + to_string(foreground[1]) + ";"
        + to_string(foreground[2]) + ";48;2;"
        + to_string(background[0]) + ";"
        + to_string(background[1]) + ";"
        + to_string(background[2]) + "m";
}
