/// @file Color.h
/// @brief Utilidades de color True Color (24-bit) para terminal ANSI.
/// @details Provee TRANSPARENT (-1,-1,-1) como centinela para "no tocar este color",
///          Color() para generar secuencias de escape, ResetColor() para resetear,
///          y SetTerminalColor() para cambiar fondo/texto de toda la consola limpiando pantalla.
///          Requiere EnableTrueColor() (Terminal.h) llamado una vez al inicio.
#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace Common
{
    /// @brief Valor centinela: indica "no cambiar este color" (transparencia)
    const std::array<int, 3> COLOR_DEFAULT = {-1, -1, -1};

    /// @brief Alias de COLOR_DEFAULT para claridad semántica
    const std::array<int, 3> COLOR_TRANSPARENT = {-1, -1, -1};
    
    /// @brief Verifica si un color es el centinela de transparencia
    inline bool isTransparent(const std::array<int, 3>& color) {
        return color[0] == -1 && color[1] == -1 && color[2] == -1;
    }
    
    /// @brief Genera secuencia(s) de escape ANSI para color RGB (24-bit True Color).
    ///        Si foreground o background es {-1,-1,-1}, se omite esa parte
    ///        y se conserva el color previamente establecido en la terminal.
    /// @param foreground Color de primer plano {R,G,B} (0-255) o {-1,-1,-1} para no tocar
    /// @param background Color de fondo {R,G,B} (0-255) o {-1,-1,-1} para no tocar
    /// @return String con la(s) secuencia(s) de escape ANSI necesarias (puede ser "")
    /// @example Color({255,100,50}, {-1,-1,-1}); // solo cambia el foreground
    inline std::string Color(std::array<int, 3> foreground, std::array<int, 3> background) {
        std::string result;
    
        if (!isTransparent(foreground)) {
            result += "\033[38;2;"
                + std::to_string(foreground[0]) + ";"
                + std::to_string(foreground[1]) + ";"
                + std::to_string(foreground[2]) + "m";
        }
    
        if (!isTransparent(background)) {
            result += "\033[48;2;"
                + std::to_string(background[0]) + ";"
                + std::to_string(background[1]) + ";"
                + std::to_string(background[2]) + "m";
        }
    
        return result;
    }
    
    /// @brief Resetea todos los atributos de color/formato de la terminal a los valores por defecto
    /// @return String con la secuencia de escape ANSI de reset
    /// @example cout << ResetColor(); // vuelve a colores por defecto
    inline std::string ResetColor() {
        return "\033[0m";
    }
    
    /// @brief Cambia el color de fondo y/o texto de TODA la consola
    ///        (limpia la pantalla aplicando los colores dados).
    ///        Usa {-1,-1,-1} en cualquiera de los dos para dejarlo sin cambios.
    ///        Funciona igual en Windows y Linux, siempre que EnableAnsiSupport()
    ///        se haya llamado antes (una sola vez, al inicio del programa).
    /// @param foreground Color de texto {R,G,B} (0-255) o TRANSPARENT para no tocar
    /// @param background Color de fondo {R,G,B} (0-255) o TRANSPARENT para no tocar
    /// @example SetTerminalColor({255,255,255}, {20,20,40}); // texto blanco, fondo azul oscuro
    /// @example SetTerminalColor(TRANSPARENT, {40,0,0});      // solo cambia el fondo (flash rojo)
    inline void SetTerminalColor(std::array<int, 3> foreground, std::array<int, 3> background) {
        // 1. Fija el/los color(es) que apliquen (respeta la regla -1 = transparente)
        std::cout << Color(foreground, background);
    
        // 2. Limpia la pantalla (\033[2J) y mueve el cursor al inicio (\033[H)
        //    para que TODAS las celdas queden repintadas con los nuevos colores
        std::cout << "\033[2J\033[H";
    
        std::cout.flush();
    }
    
    inline std::vector<std::array<int, 3>> Gradient(
        int steps,
        std::array<int, 3> start,
        std::array<int, 3> end
    ) {
        std::vector<std::array<int, 3>> result;
    
        for (int i = 0; i < steps; i++) {
            std::array<int, 3> color = {
                start[0] + (end[0] - start[0]) * i / steps,
                start[1] + (end[1] - start[1]) * i / steps,
                start[2] + (end[2] - start[2]) * i / steps
            };
            result.push_back(color);
        }
    
        return result;
    }
}
