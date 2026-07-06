// Matte Black Theme desde Omarchy
// https://omarchytheme.com/themes/matte-black/
#pragma once
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
