// Matte Black Theme desde Omarchy
// https://omarchytheme.com/themes/matte-black/
#pragma once
#include <array>

<<<<<<< HEAD
<<<<<<< HEAD
using namespace std;

#include <array>

using namespace std;

// Base
/// @brief Color de fondo base (#121212)
const array<int, 3> BACKGROUND = {18, 18, 18};

/// @brief Color de primer plano / texto principal (#bebebe)
const array<int, 3> FOREGROUND = {190, 190, 190};

/// @brief Color de acento / highlight (#e68e0d)
const array<int, 3> ACCENT = {230, 142, 13};

/// @brief Color del cursor (#eaeaea)
const array<int, 3> CURSOR = {234, 234, 234};

/// @brief Fondo de selección (#515151)
const array<int, 3> SELECTION_BACKGROUND = {81, 81, 81};

/// @brief Texto de selección (#bebebe)
const array<int, 3> SELECTION_FOREGROUND = {190, 190, 190};

// Normal colors (0-7) - ANSI standard colors
/// @brief Color 0: Negro (#333333)
const array<int, 3> COLOR0 = {51, 51, 51};

/// @brief Color 1: Rojo (#D35F5F)
const array<int, 3> COLOR1 = {211, 95, 95};

/// @brief Color 2: Amarillo/Verde (#FFC107)
const array<int, 3> COLOR2 = {255, 193, 7};

/// @brief Color 3: Rojo oscuro (#b91c1c)
const array<int, 3> COLOR3 = {185, 28, 28};

/// @brief Color 4: Naranja/Acento (#e68e0d)
const array<int, 3> COLOR4 = {230, 142, 13};

/// @brief Color 5: Magenta/Rojo (#D35F5F)
const array<int, 3> COLOR5 = {211, 95, 95};

/// @brief Color 6: Cian/Blanco suave (#bebebe)
const array<int, 3> COLOR6 = {190, 190, 190};

/// @brief Color 7: Blanco (#bebebe)
const array<int, 3> COLOR7 = {190, 190, 190};

// Bright colors (8-15) - ANSI bright variants
/// @brief Color 8: Gris medio (#8a8a8d)
const array<int, 3> COLOR8 = {138, 138, 141};

/// @brief Color 9: Rojo brillante (#B91C1C)
const array<int, 3> COLOR9 = {185, 28, 28};

/// @brief Color 10: Amarillo brillante (#FFC107)
const array<int, 3> COLOR10 = {255, 193, 7};

/// @brief Color 11: Rojo muy oscuro (#b90a0a)
const array<int, 3> COLOR11 = {185, 10, 10};

/// @brief Color 12: Naranja brillante (#f59e0b)
const array<int, 3> COLOR12 = {245, 158, 11};

/// @brief Color 13: Rojo brillante (#B91C1C)
const array<int, 3> COLOR13 = {185, 28, 28};

/// @brief Color 14: Blanco suave (#eaeaea)
const array<int, 3> COLOR14 = {234, 234, 234};

/// @brief Color 15: Blanco puro (#ffffff)
const array<int, 3> COLOR15 = {255, 255, 255};
=======
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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
}
<<<<<<< HEAD
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
