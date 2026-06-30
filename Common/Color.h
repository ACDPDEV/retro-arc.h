#pragma once
#include <array>
#include <string>

/**
 * @brief Genera una secuencia de escape ANSI para color RGB real (24-bit).
 * @param foreground Color de primer plano como array RGB {R, G, B}.
 * @param background Color de fondo como array RGB {R, G, B}.
 * @return String con la secuencia de escape ANSI formateada.
 */
inline std::string color(std::array<int, 3> foreground, int background[]) {
    return
        "\033[38;2;"
        + std::to_string(foreground[0]) + ";"
        + std::to_string(foreground[1]) + ";"
        + std::to_string(foreground[2]) + ";48;2;"
        + std::to_string(background[0]) + ";"
        + std::to_string(background[1]) + ";"
        + std::to_string(background[2]) + "m";
}
