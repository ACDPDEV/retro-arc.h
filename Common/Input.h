/// @file Input.h
/// @brief Utilidades de entrada y parsing cross-platform.
/// @details Usa Terminal.h (Kbhit/Getch) para abstracción Windows/Linux.
///          Prove: Validate, ParseInt, ParseIntStrict, ParseFloat, ParseChar, ParseBool,
///          Input (cin >>), TryInput (no bloqueante con backspace/echo).
///          Funciones marcadas `inline` para uso header-only.
#pragma once

#include <string>
#include "Terminal.h"

using namespace std;

/// @brief Valida si una entrada coincide con un tipo esperado
/// @param input String a validar
/// @param type Tipo esperado: "int", "float", "string", "char", "bool"
/// @return true si la entrada es válida para el tipo, false en caso contrario
inline bool Validate(string input, string type) {
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
inline int ParseInt(string str) {
    return stoi(str);
}

/// @brief Convierte string a int con validación estricta (sin decimales, notación científica, ni comas)
/// @param str String a convertir (solo dígitos, opcionalmente signo + o - al inicio)
/// @return Valor entero
/// @throws invalid_argument si contiene '.', ',', 'e', 'E' o no es un entero válido
/// @details A diferencia de ParseInt(), rechaza "1.5", "1,000", "1e3", "1E3", "10."
inline int ParseIntStrict(string str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.' || str[i] == ',' || str[i] == 'e' || str[i] == 'E') throw invalid_argument("No es un entero válido");
    }
    return stoi(str);
}

/// @brief Convierte string a float
/// @param str String a convertir
/// @return Valor flotante (lanza excepción si no es válido)
inline float ParseFloat(string str) {
    return stof(str);
}

/// @brief Convierte string a char (primer carácter)
/// @param str String a convertir
/// @return Primer carácter
inline char ParseChar(string str) {
    return str[0];
}

/// @brief Convierte string a bool
/// @param str String a convertir: "true"/"false" o "1"/"0"
/// @return true si "true" o "1", false si "false" o "0"
/// @throws invalid_argument si el string no es un bool válido
inline bool ParseBool(string str) {
    if (str == "true" || str == "1") return true;
    if (str == "false" || str == "0") return false;
    throw invalid_argument("Invalid bool string");
}

/// @brief Lee una palabra desde stdin (hasta espacio o salto de línea)
/// @return Palabra leída
inline string Input() {
    string line;
    cin >> line;
    return line;
}

/// @brief Intenta leer una línea completa de forma no bloqueante
/// @param[out] line Línea completa leída al presionar Enter
/// @return true si se completó la línea (se presionó Enter), false si no hay entrada lista
/// @details Maneja backspace y eco en pantalla. Usar en bucle para input interactivo.
inline bool TryInput(string& line) {
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


/**
 * @brief Valida que un caracter de 1 Byte esté entre al menos uno de los rangos permitidos
 * @param validCharRanges Rangos de caracteres válidos tuple<minimo, maximo>
 * @param character El número del caracter que se quiere evaluar
 * @returns true si el caracter está entre al menos uno de los rangos permitidos (inclusivo)
 */
inline bool IsValidChar(vector<tuple<int, int>>& validCharRanges, int character)
{
    bool isValid = false;
    int min;
    int max;
    for (const auto& range : validCharRanges)
    {
        tie(min, max) = range;
        if(min <= character && character <= max)
        {
            isValid = true;
            break;
        }
    }
    return isValid;
}

/**
 * @brief Verficia que el caracter de 1 o 2 bytes esté permitido
 * @param validCharRanges Secuencias UTF-8 de los caracteres permitidos
 * @param character El número del caracter que se quiere evaluar
 * @returns true si el caracter está permitido
 */
inline bool IsValidChar(vector<vector<int>>& validChars, vector<int>& character)
{
    for (auto& validChar : validChars)
    {
        if(validChar == character)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Lee una tecla presionada por el usuario y devuelve el código de caracter que representa
 * @param validCharRanges Rango de caracteres permitidos para lectura
 * @returns El código del último byte del caracter o -1 si es un caracter no permitido
 */
inline int ReadConsoleChar(vector<tuple<int, int>>& validCharRanges)
{
    int key;

    key = getch();

    // Compara con AND lógico bit a bit para validar si es un caracter de 2 bytes
    if((key & 0b11100000) == 0b11000000)
    {
        key = getch();
    }

    if (IsValidChar(validCharRanges, key))
    {
        return key;
    }
    else 
    {
        return -1;
    }
}

/**
 * @brief Lee una tecla presionada por el usuario y devuelve el código de caracter que representa
 * @returns La secuencia de bytes del caracter
 */
inline vector<int> ReadConsoleChar()
{
    vector<int> byteChar = {};
    int key;

    key = getch();
    byteChar.push_back(key);

    if (key == 0 || key == 224)
    {
        // Tecla especial
        byteChar.push_back(getch());
    }
    else
    {
        // Compara con AND lógico bit a bit para validar si es un caracter con cada cantidad de bytes
        if ((key & 0b11100000) == 0b11000000) // Para 2 bytes
            byteChar.push_back(getch());
        else if ((key & 0b11110000) == 0b11100000) // Para 3 bytes
            byteChar.push_back(getch()), byteChar.push_back(getch());
        else if ((key & 0b11111000) == 0b11110000) // Para 4 bytes
            byteChar.push_back(getch()), byteChar.push_back(getch()), byteChar.push_back(getch());
    }

    return byteChar;
}

/**
 * @brief Convierte un byteChar en un Caracter imprimible
 * @param byteChar bytes de la tecla presionada
 */
inline string CastKeyToChar(vector<int>& byteChar)
{
    string character;

    for (int& byte : byteChar)
    {
        character += static_cast<char>(byte);
    }

    return character;
}
