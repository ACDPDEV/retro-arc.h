#pragma once
#include <string>
#include <conio.h>

/**
 * @brief Valida si una entrada coincide con un tipo esperado.
 * @param input String a validar.
 * @param type Tipo esperado: "int", "float", "string", "char", "bool".
 * @return true si la entrada es válida para el tipo, false en caso contrario.
 */
inline bool Validate(const std::string& input, const std::string& type) {
    if (type == "int") {
        return std::isdigit(input[0]);
    } else if (type == "float") {
        return std::isdigit(input[0]) || input[0] == '.';
    } else if (type == "string") {
        return true;
    } else if (type == "char") {
        return std::isalpha(input[0]);
    } else if (type == "bool") {
        return input == "true" || input == "false";
    }
    return false;
}

/**
 * @brief Convierte string a int.
 * @param str String a convertir.
 * @return Valor entero.
 */
inline int parseInt(const std::string& str) {
    return std::stoi(str);
}

/**
 * @brief Convierte string a float.
 * @param str String a convertir.
 * @return Valor flotante.
 */
inline float parseFloat(const std::string& str) {
    return std::stof(str);
}

/**
 * @brief Convierte string a char (primer carácter).
 * @param str String a convertir.
 * @return Primer carácter.
 */
inline char parseChar(const std::string& str) {
    return str[0];
}

/**
 * @brief Convierte string a bool.
 * @param str String a convertir ("true"/"false").
 * @return Valor booleano.
 */
inline bool parseBool(const std::string& str) {
    return str == "true";
}

/**
 * @brief Lee una línea completa desde stdin.
 * @param prompt Mensaje opcional a mostrar antes de leer.
 * @return Línea leída (sin newline final).
 */
inline std::string Input(const std::string& prompt = "") {
    if (!prompt.empty()) std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

/**
 * @brief Intenta leer y validar entrada del usuario con reintentos.
 * @param prompt Mensaje a mostrar.
 * @param type Tipo esperado ("int", "float", "string", "char", "bool").
 * @param out Referencia donde almacenar el valor parseado (string crudo).
 * @param maxRetries Máximo de intentos antes de fallar (default 3).
 * @return true si se obtuvo entrada válida, false si se agotaron reintentos.
 */
inline bool TryInput(const std::string& prompt, const std::string& type, std::string& out, int maxRetries = 3) {
    for (int i = 0; i < maxRetries; ++i) {
        std::string input = Input(prompt);
        if (Validate(input, type)) {
            out = input;
            return true;
        }
        std::cout << "Entrada inválida. Intente de nuevo (" << (maxRetries - i - 1) << " intentos restantes).\n";
    }
    return false;
}
