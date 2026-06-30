#pragma once
#include <array>
#include <string>

/**
 * @brief Genera una secuencia de escape ANSI para color RGB real (24-bit / True Color)
 * @param foreground Color de primer plano como array RGB {R, G, B} (0-255)
 * @param background Color de fondo como array RGB {R, G, B} (0-255)
 * @return String con la secuencia de escape ANSI formateada
 * @details Requiere que la consola tenga habilitado ENABLE_VIRTUAL_TERMINAL_PROCESSING (ver Terminal.h)
 */
std::string color(std::array<int, 3> foreground, std::array<int, 3> background) {
    return
        "\033[38;2;"
        + std::to_string(foreground[0]) + ";"
        + std::to_string(foreground[1]) + ";"
        + std::to_string(foreground[2]) + ";48;2;"
        + std::to_string(background[0]) + ";"
        + std::to_string(background[1]) + ";"
        + std::to_string(background[2]) + "m";
}
