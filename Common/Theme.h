// Matte Black Theme desde Omarchy
// https://omarchytheme.com/themes/matte-black/
#pragma once
#include <array>

namespace Common
{
    // Base
    /// @brief Color de fondo base (#333a40)
    const std::array<int, 3> BACKGROUND = {31, 34, 38};

    /// @brief Color de primer plano / texto principal (#bebebe)
    const std::array<int, 3> FOREGROUND_LIGHT = {255, 255, 255};

    /// @brief Color de primer plano / texto principal (#bebebe)
    const std::array<int, 3> FOREGROUND_DARK = {0, 0, 0};

    /// @brief Color de acento / highlight (#e68e0d)
    const std::array<int, 3> ACCENT = {230, 142, 13};

    /// @brief Color del cursor (#eaeaea)
    const std::array<int, 3> CURSOR = {234, 234, 234};

    /// @brief Fondo de selección (#515151)
    const std::array<int, 3> SELECTION_BACKGROUND = {51, 54, 54};

    /// @brief Texto de selección (#bebebe)
    const std::array<int, 3> SELECTION_FOREGROUND = {190, 190, 190};

    // Normal colors (0-7) - ANSI standard colors
    /// @brief Color 0: Negro (#333333)
    const std::array<int, 3> SOFT_GREEN = {178, 242, 187};

    /// @brief Color 1: Rojo (#D35F5F)
    const std::array<int, 3> LIGHT_GREEN = {105, 219, 124};

    /// @brief Color 2: Amarillo/Verde (#FFC107)
    const std::array<int, 3> GRAY = {206, 212, 218};

    /// @brief Color 3: Rojo oscuro (#b91c1c)
    const std::array<int, 3> LIGHT_BLUE = {153, 233, 242};

    /// @brief Color 4: Naranja/Acento (#e68e0d)
    const std::array<int, 3> BLUE = {25, 113, 194};

    /// @brief Color 5: Magenta/Rojo (#D35F5F)
    const std::array<int, 3> ORANGE = {255, 193, 7};

    /// @brief Color 6: Cian/Blanco suave (#bebebe)
    const std::array<int, 3> SOFT_RED = {255, 201, 201};

    /// @brief Color 7: Blanco (#bebebe)
    const std::array<int, 3> CREAM = {254, 236, 152};

    // Bright colors (8-15) - ANSI bright variants
    /// @brief Color 8: Gris medio (#8a8a8d)
    const std::array<int, 3> RED = {239, 75, 70};

    /// @brief Color 9: Rojo brillante (#B91C1C)
    const std::array<int, 3> DARK_RED = {182, 54, 59};
    
    /// @brief Color 10: Amarillo (#B91C1C)
    const std::array<int, 3> YELLOW = {255, 202, 2};

    /// @brief Color rosa/salmón para paneles de jugador (#FFB6C1)
    const std::array<int, 3> PINK = {255, 182, 193};
}
