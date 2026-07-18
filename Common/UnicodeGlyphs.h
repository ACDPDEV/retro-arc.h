/// @file UnicodeGlyphs.h
/// @brief Glifos Unicode para graficador TUI: bloques de relleno + caracteres de borde.
/// @details Pensado para usarse junto a EnableUTF8() (UTF-8).
///          IMPORTANTE: guardar este archivo como UTF-8.
///          Si compilás con MSVC (cl.exe), agregar el flag /utf-8 para que los literales se interpreten correctamente.
///          Provee constantes y catálogos (BORDERS, CORNERS) usados por DrawBox() en Graphics.h.
#pragma once
#include <array>
#include <string>

using namespace std;

/// @brief Bloques de octavos verticales (9 niveles: 0/8 vacío a 8/8 lleno)
/// @details Uso típico: sparklines, barras, gráficos donde cada columna = 1 muestra.
///          Índice 0 = " ", 1 = ▁, 2 = ▂, 3 = ▃, 4 = ▄, 5 = ▅, 6 = ▆, 7 = ▇, 8 = █
const array<string, 9> VERTICAL_EIGHTH_BLOCKS = {
    " ",        // 0/8   vacío
    "\u2581",   // 1/8 ▁
    "\u2582",   // 2/8 ▂
    "\u2583",   // 3/8 ▃
    "\u2584",   // 4/8 ▄
    "\u2585",   // 5/8 ▅
    "\u2586",   // 6/8 ▆
    "\u2587",   // 7/8 ▇
    "\u2588"    // 8/8 █ bloque completo
};

/// @brief Bloque vacío (espacio)
const string EMPTY_BLOCK = " ";

/// @brief Medio bloque superior (▀)
const string UPPER_HALF_BLOCK = "\u2580";

/// @brief Medio bloque inferior (▄)
const string LOWER_HALF_BLOCK = "\u2584";

/// @brief Bloque completo (█)
const string FULL_BLOCK = "\u2588";

/// @brief Medio bloque izquierdo (▌)
const string LEFT_HALF_BLOCK = "\u258C";

/// @brief Medio bloque derecho (▐)
const string RIGHT_HALF_BLOCK = "\u2590";

/// @brief Sombrado: 4 niveles de densidad (claro → sólido)
/// @details Uso típico: mapas de calor, histogramas 2D.
///          Índice 0 = ░ (25%), 1 = ▒ (50%), 2 = ▓ (75%), 3 = █ (100%)
const array<string, 4> SHADING = {
    "\u2591", // ░ claro (25%)
    "\u2592", // ▒ medio (50%)
    "\u2593", // ▓ oscuro (75%)
    "\u2588"  // █ sólido (100%)
};

/// @brief Cuadrantes: resolución 2x2 por celda (16 combinaciones)
/// @details Índice = bitmask de 4 bits: bit0=sup-izq, bit1=sup-der, bit2=inf-izq, bit3=inf-der.
///          Ejemplo: QUADRANTS[0b0110] -> diagonal sup-der + inf-izq (▞)
const array<string, 16> QUADRANTS = {
    " ",        // 0000   0
    "\u2598",   // 0001 ▘ 1 sup-izq
    "\u259D",   // 0010 ▝ 2 sup-der
    "\u2580",   // 0011 ▀ 3 superior completo
    "\u2596",   // 0100 ▖ 4 inf-izq
    "\u258C",   // 0101 ▌ 5 izquierda completa
    "\u259E",   // 0110 ▞ 6 diagonal (sup-der + inf-izq)
    "\u259B",   // 0111 ▛ 7 todo menos inf-der
    "\u2597",   // 1000 ▗ 8 inf-der
    "\u259A",   // 1001 ▚ 9 diagonal inversa (sup-izq + inf-der)
    "\u2590",   // 1010 ▐ 10 derecha completa
    "\u259C",   // 1011 ▜ 11 todo menos inf-izq
    "\u2584",   // 1100 ▄ 12 inferior completo
    "\u2599",   // 1101 ▙ 13 todo menos sup-der
    "\u259F",   // 1110 ▟ 14 todo menos sup-izq
    "\u2588"    // 1111 █ 15 completo
};

/// @brief Línea horizontal simple (─)
const string HORIZONTAL_BORDER = "\u2500";

/// @brief Línea vertical simple (│)
const string VERTICAL_BORDER = "\u2502";

/// @brief Esquina superior izquierda simple (┌)
const string TOP_LEFT_CORNER = "\u250C";

/// @brief Esquina superior derecha simple (┐)
const string TOP_RIGHT_CORNER = "\u2510";

/// @brief Esquina inferior izquierda simple (└)
const string BOTTOM_LEFT_CORNER = "\u2514";

/// @brief Esquina inferior derecha simple (┘)
const string BOTTOM_RIGHT_CORNER = "\u2518";

/// @brief T hacia la izquierda (├)
const string LEFT_TEE = "\u251C";

/// @brief T hacia la derecha (┤)
const string RIGHT_TEE = "\u2524";

/// @brief T hacia arriba (┬)
const string TOP_TEE = "\u252C";

/// @brief T hacia abajo (┴)
const string BOTTOM_TEE = "\u2534";

/// @brief Cruz (┼)
const string CROSS = "\u253C";

/// @brief Línea horizontal doble (═)
const string DOUBLE_HORIZONTAL_BORDER = "\u2550";

/// @brief Línea vertical doble (║)
const string DOUBLE_VERTICAL_BORDER = "\u2551";

/// @brief Esquina sup-izq doble (╔)
const string DOUBLE_TOP_LEFT_CORNER = "\u2554";

/// @brief Esquina sup-der doble (╗)
const string DOUBLE_TOP_RIGHT_CORNER = "\u2557";

/// @brief Esquina inf-izq doble (╚)
const string DOUBLE_BOTTOM_LEFT_CORNER = "\u255A";

/// @brief Esquina inf-der doble (╝)
const string DOUBLE_BOTTOM_RIGHT_CORNER = "\u255D";

/// @brief T izquierda doble (╠)
const string DOUBLE_LEFT_TEE = "\u2560";

/// @brief T derecha doble (╣)
const string DOUBLE_RIGHT_TEE = "\u2563";

/// @brief T arriba doble (╦)
const string DOUBLE_TOP_TEE = "\u2566";

/// @brief T abajo doble (╩)
const string DOUBLE_BOTTOM_TEE = "\u2569";

/// @brief Cruz doble (╬)
const string DOUBLE_CROSS = "\u256C";

/// @brief Esquina sup-izq redondeada (╭)
const string ROUNDED_TOP_LEFT_CORNER = "\u256D";

/// @brief Esquina sup-der redondeada (╮)
const string ROUNDED_TOP_RIGHT_CORNER = "\u256E";

/// @brief Esquina inf-izq redondeada (╰)
const string ROUNDED_BOTTOM_LEFT_CORNER = "\u2570";

/// @brief Esquina inf-der redondeada (╯)
const string ROUNDED_BOTTOM_RIGHT_CORNER = "\u256F";

/// @brief Línea horizontal gruesa/heavy (━)
const string HEAVY_HORIZONTAL_BORDER = "\u2501";

/// @brief Línea vertical gruesa/heavy (┃)
const string HEAVY_VERTICAL_BORDER = "\u2503";

/// @brief Esquina sup-izq heavy (┏)
const string HEAVY_TOP_LEFT_CORNER = "\u250F";

/// @brief Esquina sup-der heavy (┓)
const string HEAVY_TOP_RIGHT_CORNER = "\u2513";

/// @brief Esquina inf-izq heavy (┗)
const string HEAVY_BOTTOM_LEFT_CORNER = "\u2517";

/// @brief Esquina inf-der heavy (┛)
const string HEAVY_BOTTOM_RIGHT_CORNER = "\u251B";

/// @brief T izquierda heavy (┣)
const string HEAVY_LEFT_TEE = "\u2523";

/// @brief T derecha heavy (┫)
const string HEAVY_RIGHT_TEE = "\u252B";

/// @brief T arriba heavy (┳)
const string HEAVY_TOP_TEE = "\u2533";

/// @brief T abajo heavy (┻)
const string HEAVY_BOTTOM_TEE = "\u253B";

/// @brief Cruz heavy (╋)
const string HEAVY_CROSS = "\u254B";

/// @brief Línea horizontal punteada (┄)
const string DOTTED_HORIZONTAL = "\u2504";

/// @brief Línea vertical punteada (┆)
const string DOTTED_VERTICAL = "\u2506";

/// @brief Línea horizontal punteada fina (┈)
const string THIN_DOTTED_HORIZONTAL = "\u2508";

/// @brief Línea vertical punteada fina (┊)
const string THIN_DOTTED_VERTICAL = "\u250A";

/// @brief Cruz de ejes (╂) - vertical resaltada, útil para marcar eje y=0
const string AXIS_CROSS = "\u2542";

/// @brief Catálogo de estilos de borde indexados por [estilo][orientación].
/// @details Dimensiones: 7 estilos × 4 entradas (top, right, bottom, left).
///          Índices de estilo (filas):
///          - 0: vacío (sin borde)
///          - 1: punteado fino (┄ ┆ ┄ ┆)
///          - 2: punteado (┈ ┊ ┈ ┊)
///          - 3: simple (─ │ ─ │)
///          - 4: grueso/heavy (━ ┃ ━ ┃)
///          - 5: doble (═ ║ ═ ║)
///          - 6: cuadrantes (▀ ▐ ▄ ▌) — usa QUADRANTS[3,10,12,5]
/// @see DrawBox() usa borders[0..3] como índices de fila para top/right/bottom/left.
const array<array<string, 4>, 7> BORDERS = {{
    { EMPTY_BLOCK, EMPTY_BLOCK, EMPTY_BLOCK, EMPTY_BLOCK },
    { THIN_DOTTED_HORIZONTAL, THIN_DOTTED_VERTICAL, THIN_DOTTED_HORIZONTAL, THIN_DOTTED_VERTICAL },
    { DOTTED_HORIZONTAL, DOTTED_VERTICAL, DOTTED_HORIZONTAL, DOTTED_VERTICAL },
    { HORIZONTAL_BORDER, VERTICAL_BORDER, HORIZONTAL_BORDER, VERTICAL_BORDER },
    { HEAVY_HORIZONTAL_BORDER, HEAVY_VERTICAL_BORDER, HEAVY_HORIZONTAL_BORDER, HEAVY_VERTICAL_BORDER },
    { DOUBLE_HORIZONTAL_BORDER, DOUBLE_VERTICAL_BORDER, DOUBLE_HORIZONTAL_BORDER, DOUBLE_VERTICAL_BORDER },
    { QUADRANTS[3], QUADRANTS[10], QUADRANTS[12], QUADRANTS[5] }
}};

/// @brief Catálogo de esquinas indexado por [estilo][esquina].
/// @details Dimensiones: 6 estilos × 4 esquinas (top-left, top-right, bottom-right, bottom-left).
///          Índices de estilo (filas):
///          - 0: vacío (sin esquina)
///          - 1: simple (┌ ┐ ┘ └)
///          - 2: grueso/heavy (┏ ┓ ┛ ┗)
///          - 3: doble (╔ ╗ ╝ ╚)
///          - 4: redondeada (╭ ╮ ╯ ╰)
///          - 5: cuadrantes (▛ ▜ ▟ ▙) — usa QUADRANTS[7,11,14,13]
/// @see DrawBox() usa corners[0..3] como índices de fila para TL, TR, BR, BL.
const array<array<string, 4>, 6> CORNERS = {{
    { EMPTY_BLOCK, EMPTY_BLOCK, EMPTY_BLOCK, EMPTY_BLOCK },
    { TOP_LEFT_CORNER, TOP_RIGHT_CORNER, BOTTOM_RIGHT_CORNER, BOTTOM_LEFT_CORNER },
    { HEAVY_TOP_LEFT_CORNER, HEAVY_TOP_RIGHT_CORNER, HEAVY_BOTTOM_RIGHT_CORNER, HEAVY_BOTTOM_LEFT_CORNER },
    { DOUBLE_TOP_LEFT_CORNER, DOUBLE_TOP_RIGHT_CORNER, DOUBLE_BOTTOM_RIGHT_CORNER, DOUBLE_BOTTOM_LEFT_CORNER },
    { ROUNDED_TOP_LEFT_CORNER, ROUNDED_TOP_RIGHT_CORNER, ROUNDED_BOTTOM_RIGHT_CORNER, ROUNDED_BOTTOM_LEFT_CORNER },
    { QUADRANTS[7], QUADRANTS[11], QUADRANTS[14], QUADRANTS[13] }
}};
