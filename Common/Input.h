#pragma once

#include <string>
#include <iostream>

#include "Terminal.h"

using namespace std;

/// @brief Valida si una entrada coincide con un tipo esperado
/// @param input String a validar
/// @param type Tipo esperado: "int", "float", "string", "char", "bool"
/// @return true si la entrada es válida para el tipo, false en caso contrario
bool Validate(string input, string type) {
    if (type == "int") {
        return isdigit(input[0]);
    } else if (type == "float") {
        return isdigit(input[0]) || input[0] == '.';
    } else if (type == "string") {
        return true;
    } else if (type == "char") {
        return isalpha(input[0]);
    } else if (type == "bool") {
        return input == "true" || input == "false";
    }
    return false;
}

/// @brief Convierte string a int
/// @param str String a convertir
/// @return Valor entero (lanza excepción si no es válido)
int ParseInt(string str) {
    return stoi(str);
}

/// @brief Convierte string a int con validación estricta (sin decimales, notación científica, ni comas)
/// @param str String a convertir (solo dígitos, opcionalmente signo + o - al inicio)
/// @return Valor entero
/// @throws invalid_argument si contiene '.', ',', 'e', 'E' o no es un entero válido
/// @details A diferencia de ParseInt(), rechaza "1.5", "1,000", "1e3", "1E3", "10."
int ParseIntStrict(string str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.' || str[i] == ',' || str[i] == 'e' || str[i] == 'E') throw invalid_argument("No es un entero válido");
    }
    return stoi(str);
}

/// @brief Convierte string a float
/// @param str String a convertir
/// @return Valor flotante (lanza excepción si no es válido)
float ParseFloat(string str) {
    return stof(str);
}

/// @brief Convierte string a char (primer carácter)
/// @param str String a convertir
/// @return Primer carácter
char ParseChar(string str) {
    return str[0];
}

/// @brief Convierte string a bool
/// @param str String a convertir: "true"/"false" o "1"/"0"
/// @return true si "true" o "1", false si "false" o "0"
/// @throws invalid_argument si el string no es un bool válido
bool ParseBool(string str) {
    if (str == "true" || str == "1") return true;
    if (str == "false" || str == "0") return false;
    throw invalid_argument("Invalid bool string");
}

/// @brief Lee una palabra desde stdin (hasta espacio o salto de línea)
/// @return Palabra leída
string Input() {
    string line;
    cin >> line;
    return line;
}

/// @brief Intenta leer una línea completa de forma no bloqueante
/// @param[out] line Línea completa leída al presionar Enter
/// @return true si se completó la línea (se presionó Enter), false si no hay entrada lista
/// @details Maneja backspace y eco en pantalla. Usar en bucle para input interactivo.
bool TryInput(string& line) {
    static string buffer;

    while (Kbhit()) {
        char c = Getch();

        switch (c) {
            case '\r': // Enter
                line = buffer;
                buffer.clear();
                return true;

            case '\b': // Backspace
                if (!buffer.empty()) {
                    buffer.pop_back();
                    cout << "\b \b";
                }
                break;

            default:
                if (c >= 32 && c <= 126) { // Caracteres imprimibles
                    buffer += c;
                    cout << c; // Eco en pantalla
                }
                break;
        }
    }

    return false;
}
