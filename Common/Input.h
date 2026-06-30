#pragma once
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

/**
 * @brief Valida si una entrada coincide con un tipo esperado.
 * @param input String a validar.
 * @param type Tipo esperado: "int", "float", "string", "char", "bool".
 * @return true si la entrada es válida para el tipo, false en caso contrario.
 */
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

/**
 * @brief Convierte string a int.
 * @param str String a convertir.
 * @return Valor entero.
 */
int parseInt(string str) {
    return stoi(str);
}

/**
 * @brief Convierte string a float.
 * @param str String a convertir.
 * @return Valor flotante.
 */
float parseFloat(string str) {
    return stof(str);
}

/**
 * @brief Convierte string a char (primer carácter).
 * @param str String a convertir.
 * @return Primer carácter.
 */
char parseChar(string str) {
    return str[0];
}

/**
 * @brief Convierte string a bool.
 * @param str String a convertir ("true"/"false").
 * @return Valor booleano.
 */
bool parseBool(string str) {
    return str == "true";
}

/**
 * @brief Lee una línea completa desde stdin.
 * @param prompt Mensaje opcional a mostrar antes de leer.
 * @return Línea leída (sin newline final).
 */
string Input(string prompt = "") {
    if (!prompt.empty()) cout << prompt;
    string line;
    getline(cin, line);
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
bool TryInput(string prompt, string type, string out, int maxRetries = 3) {
    for (int i = 0; i < maxRetries; ++i) {
        string input = Input(prompt);
        if (Validate(input, type)) {
            out = input;
            return true;
        }
        cout << "Entrada inválida. Intente de nuevo (" << (maxRetries - i - 1) << " intentos restantes).\n";
    }
    return false;
}
